open Utils;

open Model;

type state = {company: option(Company.t)};

type action =
  | Loaded(Company.t);

[@react.component]("Company");

let make = (~id, ()) => {
  let renderCompany = (company: Company.t) =>
    <div className="margin-left-md">
      <p> <strong> (textEl("ID: ")) </strong> (optIntEl(company.id)) </p>
      <p> <strong> (textEl("Name: ")) </strong> (textEl(company.name)) </p>
    </div>;
  {
     
    initialState: () => {company: None},
    render: self => {
      let companyContent =
        switch state.company {
        | Some(company) => renderCompany(company)
        | None => React.string("Loading company")
        };
      <div>
        <div className="margin-bottom-lg">
          <Link route=Routes.Companies> (textEl("< Back")) </Link>
        </div>
        <h1 className="pt-running-text"> (textEl("Company")) </h1>
        <div> companyContent </div>
      </div>;
    },
    didMount: self => {
      let handleCompanyLoaded = company => self.send(Loaded(company));
      Js.Promise.(
        Company.Api.fetch(id)
        |> then_(company => {
             handleCompanyLoaded(company);
             resolve();
           })
        |> catch(_err => {
             Notify.showError(
               "Failed to fetch companies! Check network connection!"
             )
             |> ignore;
             resolve();
           })
        |> ignore
      );
      NoUpdate;
    },
    reducer: (action, _state) =>
      switch action {
      | Loaded(company) => Update({company: Some(company)})
      }
  };
};