open Model;

open Utils;

requireCSS("./view_companies.css");

/**
 * This is CompanyDialog module which is used to add and edit companies
 */
module CompanyDialog = {
  type state = {
    company: Company.t,
    hasError: bool
  };
  type action =
    | Changed(string)
    | SetError(bool);
  let component = ReasonReact.reducerComponent("CompanyDialog");
  let make = (~onSubmit, ~onClose, ~data: option(Company.t)=None, _) => {
    ...component,
    initialState: () =>
      switch data {
      | Some(company) => {company, hasError: false}
      | None => {
          company: {
            id: None,
            name: ""
          },
          hasError: false
        }
      },
    render: self => {
      let internalSubmit = (evt: ReactEventRe.Mouse.t) => {
        let trimmed: string = String.trim(self.state.company.name);
        if (String.length(trimmed) > 0) {
          onSubmit(self.state.company);
          onClose(evt);
        } else {
          self.send(SetError(true));
        };
      };
      let intent =
        self.state.hasError ?
          Blueprintjs.Intent.DANGER : Blueprintjs.Intent.NONE;
      <div className="dialog-container">
        <Blueprintjs.FormGroup
          label=(textEl("Name "))
          labelFor="company-name-input"
          requiredLabel=(`Bool(true))
          intent
          inline=true
          helperText=(
            self.state.hasError ?
              textEl("Enter valid company name") : ReasonReact.nullElement
          )
          required=true>
          <Blueprintjs.InputGroup
            _type="text"
            id="company-name-input"
            intent
            value=self.state.company.name
            placeholder="Enter company name..."
            onChange=(event => self.send(Changed(getValueFromEvent(event))))
          />
        </Blueprintjs.FormGroup>
        <div className="dialog-button-container">
          <Blueprintjs.Button onClick=onClose>
            (textEl("Cancel"))
          </Blueprintjs.Button>
          <Blueprintjs.Button
            onClick=internalSubmit intent=Blueprintjs.Intent.PRIMARY>
            (
              switch data {
              | Some(_c) => textEl("Edit")
              | None => textEl("Add")
              }
            )
          </Blueprintjs.Button>
        </div>
      </div>;
    },
    reducer: (action, state) =>
      switch action {
      | Changed(name) =>
        let hasError =
          state.hasError && String.length(String.trim(name)) === 0;
        ReasonReact.Update({
          hasError,
          company: {
            ...state.company,
            name
          }
        });
      | SetError(hasError) => ReasonReact.Update({...state, hasError})
      }
  };
};

/**
 * Here is the View_companies module implementation itself
 */
type state = {
  companies: option(array(Company.t)),
  addDialogOpen: bool,
  editCompany: option(Company.t),
  hasLoadError: bool
};

type action =
  | Loaded(array(Company.t))
  | LoadError
  | AddCompany(Company.t)
  | EditCompany(Company.t)
  | RemoveCompany(int)
  | ToggleAddDialog
  | ToggleEditDialog(option(Company.t));

let component = ReasonReact.reducerComponent("Companies");

let make = _children => {
  /**
   * "Private" functions are introduced first
   */
  let renderCompany = (company: Company.t, removeCompany, openEditDialog) => {
    let id = optIntOrRaise(company.id);
    <tr className="company-table-row" key=(string_of_int(id))>
      <td> <Link route=(Routes.Company(id))> (intEl(id)) </Link> </td>
      <td> (textEl(company.name)) </td>
      <td>
        <div className="company-icon-container">
          <span
            title="Edit"
            onClick=(_e => openEditDialog(Some(company)))
            className="pt-icon-standard pt-icon-edit"
          />
          <span
            title="Remove"
            onClick=(_e => removeCompany(company))
            className="pt-icon-standard pt-icon-trash margin-left-md"
          />
        </div>
      </td>
    </tr>;
  };
  let renderCompanies =
      (companies: array(Company.t), removeCompany, openEditDialog) =>
    <table className="pt-table pt-striped company-table">
      <thead>
        <tr>
          <th> (textEl("Id")) </th>
          <th> (textEl("Name")) </th>
          <th> <div className="company-remove-icon-header" /> </th>
        </tr>
      </thead>
      <tbody>
        (
          arrayEl(
            Array.map(
              company => renderCompany(company, removeCompany, openEditDialog),
              companies
            )
          )
        )
      </tbody>
    </table>;
  let renderLoading = () =>
    <div className="align-middle">
      <Blueprintjs.Spinner className="pt-small" />
      <span className="margin-left-md"> (textEl("Loading")) </span>
    </div>;
  let handleAdd = (company, handleCompanyAdded) => {
    Js.Promise.(
      Company.Api.add(company)
      |> then_(addedCompany => {
           handleCompanyAdded(addedCompany);
           resolve();
         })
      |> catch(_err => {
           Notify.showError("Failed to add company! Check network connection!")
           |> ignore;
           resolve();
         })
      |> ignore
    );
    ReasonReact.NoUpdate;
  };
  let handleEdit = (company, handleCompanyEdited) =>
    Js.Promise.(
      Company.Api.edit(company)
      |> then_(() => {
           handleCompanyEdited(company);
           resolve();
         })
      |> catch(_err => {
           Notify.showError(
             "Failed to edit company! Check network connection!"
           )
           |> ignore;
           resolve();
         })
      |> ignore
    );
  let handleRemove = (company: Company.t, handleCompanyRemoved) => {
    let doRemove = companyId =>
      Js.Promise.(
        Company.Api.remove(companyId)
        |> then_(() => {
             handleCompanyRemoved(companyId);
             resolve();
           })
        |> catch(_err => {
             Notify.showError(
               "Failed to delete company! Check network connection!"
             )
             |> ignore;
             resolve();
           })
        |> ignore
      );
    switch company.id {
    | Some(companyId) => doRemove(companyId)
    | None =>
      Notify.showError(
        "Internal error! Attempting to remove company without id!"
      )
      |> ignore
    };
  };
  let fetchAll = (handleCompaniesLoaded, handleError) => {
    Js.Promise.(
      Company.Api.fetchAll()
      |> then_(companies => {
           handleCompaniesLoaded(companies);
           resolve();
         })
      |> catch(_err => {
           Notify.showError(
             "Failed to fetch companies! Check network connection!"
           )
           |> ignore;
           handleError();
           resolve();
         })
      |> ignore
    );
    ReasonReact.NoUpdate;
  };
  /**
   * Implementation for the View_companies React component
   */
  {
    ...component,
    initialState: () => {
      companies: None,
      addDialogOpen: false,
      editCompany: None,
      hasLoadError: false
    },
    render: self => {
      let toggleAddDialog = _event => self.send(ToggleAddDialog);
      let openEditDialog = company => self.send(ToggleEditDialog(company));
      let closeEditDialog = _event => self.send(ToggleEditDialog(None));
      let removeCompany = company =>
        handleRemove(company, removedId =>
          self.send(RemoveCompany(removedId))
        );
      let addCompany = company =>
        handleAdd(company, company => self.send(AddCompany(company)));
      let editCompany = company =>
        handleEdit(company, company => self.send(EditCompany(company)));
      let companiesContent =
        switch self.state.companies {
        | Some(companies) =>
          renderCompanies(companies, removeCompany, openEditDialog)
        | None => renderLoading()
        };
      self.state.hasLoadError ?
        <h2 className="pt-running-text">
          (
            textEl(
              "Error loading companies! Check network connection and reload!"
            )
          )
        </h2> :
        <div>
          <h1 className="pt-running-text"> (textEl("Companies")) </h1>
          (
            self.state.companies != None ?
              <div>
                <Blueprintjs.Button onClick=toggleAddDialog>
                  (textEl("Add company"))
                </Blueprintjs.Button>
              </div> :
              ReasonReact.nullElement
          )
          <div> companiesContent </div>
          <Blueprintjs.Dialog
            isOpen=self.state.addDialogOpen
            onClose=toggleAddDialog
            title=(textEl("Add new company"))>
            <CompanyDialog onSubmit=addCompany onClose=toggleAddDialog />
          </Blueprintjs.Dialog>
          <Blueprintjs.Dialog
            isOpen=(self.state.editCompany !== None)
            onClose=closeEditDialog
            title=(textEl("Edit company"))>
            <CompanyDialog
              onSubmit=editCompany
              onClose=closeEditDialog
              data=self.state.editCompany
            />
          </Blueprintjs.Dialog>
        </div>;
    },
    didMount: self =>
      fetchAll(
        companies => self.send(Loaded(companies)),
        () => self.send(LoadError)
      ),
    /* This is the add dialog */
    reducer: (action, state) =>
      switch action {
      | Loaded(companies) =>
        ReasonReact.Update({
          ...state,
          hasLoadError: false,
          companies: Some(companies)
        })
      | LoadError => ReasonReact.Update({...state, hasLoadError: true})
      | ToggleAddDialog =>
        ReasonReact.Update({...state, addDialogOpen: ! state.addDialogOpen})
      | ToggleEditDialog(editCompany) =>
        ReasonReact.Update({...state, editCompany})
      | AddCompany(company) =>
        ReasonReact.Update({
          ...state,
          companies: Company.append(state.companies, company)
        })
      | EditCompany(company) =>
        ReasonReact.Update({
          ...state,
          companies: Company.replace(state.companies, company)
        })
      | RemoveCompany(removedId) =>
        ReasonReact.Update({
          ...state,
          companies: Company.removeWithId(state.companies, removedId)
        })
      }
    /* This is the edit dialog */
  };
};