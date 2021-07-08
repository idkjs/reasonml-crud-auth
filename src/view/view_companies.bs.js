// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';

var Link = require("../link.bs.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Utils = require("../utils.bs.js");
var React = require("react");
var Notify = require("../notify.bs.js");
var $$String = require("bs-platform/lib/js/string.js");
var Model_company = require("../model/model_company.bs.js");
var Core = require("@blueprintjs/core");

require("./view_companies.css");

function initialState(data) {
  if (data !== undefined) {
    return {
            company: data,
            hasError: false
          };
  } else {
    return {
            company: {
              id: undefined,
              name: ""
            },
            hasError: false
          };
  }
}

function View_companies$CompanyDialog(Props) {
  var onSubmit = Props.onSubmit;
  var onClose = Props.onClose;
  var data = Props.data;
  var match = React.useReducer((function (state, action) {
          if (action.TAG !== /* Changed */0) {
            return {
                    company: state.company,
                    hasError: action._0
                  };
          }
          var name = action._0;
          var hasError = state.hasError && $$String.trim(name).length === 0;
          var init = state.company;
          return {
                  company: {
                    id: init.id,
                    name: name
                  },
                  hasError: hasError
                };
        }), initialState(data));
  var dispatch = match[1];
  var state = match[0];
  var internalSubmit = function (evt) {
    var trimmed = $$String.trim(state.company.name);
    if (trimmed.length !== 0) {
      Curry._1(onSubmit, state.company);
      return Curry._1(onClose, evt);
    } else {
      return Curry._1(dispatch, {
                  TAG: /* SetError */1,
                  _0: true
                });
    }
  };
  var intent = state.hasError ? /* DANGER */4 : /* NONE */0;
  return React.createElement("div", {
              className: "dialog-container"
            }, React.createElement(Core.FormGroup, {
                  helperText: state.hasError ? Utils.textEl("Enter valid company name") : null,
                  inline: true,
                  intent: intent,
                  label: Utils.textEl("Name "),
                  labelFor: "company-name-input",
                  requiredLabel: {
                    NAME: "Bool",
                    VAL: true
                  },
                  required: true,
                  children: React.createElement(Core.InputGroup, {
                        id: "company-name-input",
                        intent: intent,
                        onChange: (function ($$event) {
                            return Curry._1(dispatch, {
                                        TAG: /* Changed */0,
                                        _0: Utils.getValueFromEvent($$event)
                                      });
                          }),
                        placeholder: "Enter company name...",
                        type: "text",
                        value: state.company.name
                      })
                }), React.createElement("div", {
                  className: "dialog-button-container"
                }, React.createElement(Core.Button, {
                      onClick: onClose,
                      children: Utils.textEl("Cancel")
                    }), React.createElement(Core.Button, {
                      intent: /* PRIMARY */1,
                      onClick: internalSubmit,
                      children: data !== undefined ? Utils.textEl("Edit") : Utils.textEl("Add")
                    })));
}

var CompanyDialog = {
  initialState: initialState,
  make: View_companies$CompanyDialog
};

function View_companies(Props) {
  var match = React.useReducer((function (state, action) {
          if (typeof action === "number") {
            if (action === /* LoadError */0) {
              return {
                      companies: state.companies,
                      addDialogOpen: state.addDialogOpen,
                      editCompany: state.editCompany,
                      hasLoadError: true
                    };
            } else {
              return {
                      companies: state.companies,
                      addDialogOpen: !state.addDialogOpen,
                      editCompany: state.editCompany,
                      hasLoadError: state.hasLoadError
                    };
            }
          }
          switch (action.TAG | 0) {
            case /* Loaded */0 :
                return {
                        companies: action._0,
                        addDialogOpen: state.addDialogOpen,
                        editCompany: state.editCompany,
                        hasLoadError: false
                      };
            case /* AddCompany */1 :
                return {
                        companies: Model_company.append(state.companies, action._0),
                        addDialogOpen: state.addDialogOpen,
                        editCompany: state.editCompany,
                        hasLoadError: state.hasLoadError
                      };
            case /* EditCompany */2 :
                return {
                        companies: Model_company.replace(state.companies, action._0),
                        addDialogOpen: state.addDialogOpen,
                        editCompany: state.editCompany,
                        hasLoadError: state.hasLoadError
                      };
            case /* RemoveCompany */3 :
                return {
                        companies: Model_company.removeWithId(state.companies, action._0),
                        addDialogOpen: state.addDialogOpen,
                        editCompany: state.editCompany,
                        hasLoadError: state.hasLoadError
                      };
            case /* ToggleEditDialog */4 :
                return {
                        companies: state.companies,
                        addDialogOpen: state.addDialogOpen,
                        editCompany: action._0,
                        hasLoadError: state.hasLoadError
                      };
            
          }
        }), {
        companies: undefined,
        addDialogOpen: false,
        editCompany: undefined,
        hasLoadError: false
      });
  var dispatch = match[1];
  var state = match[0];
  var renderCompanies = function (companies, removeCompany, openEditDialog) {
    return React.createElement("table", {
                className: "pt-table pt-striped company-table"
              }, React.createElement("thead", undefined, React.createElement("tr", undefined, React.createElement("th", undefined, Utils.textEl("Id")), React.createElement("th", undefined, Utils.textEl("Name")), React.createElement("th", undefined, React.createElement("div", {
                                className: "company-remove-icon-header"
                              })))), React.createElement("tbody", undefined, Utils.arrayEl($$Array.map((function (company) {
                              var id = Utils.optIntOrRaise(company.id);
                              return React.createElement("tr", {
                                          key: String(id),
                                          className: "company-table-row"
                                        }, React.createElement("td", undefined, React.createElement(Link.make, {
                                                  route: /* Company */{
                                                    _0: id
                                                  },
                                                  children: Utils.intEl(id)
                                                })), React.createElement("td", undefined, Utils.textEl(company.name)), React.createElement("td", undefined, React.createElement("div", {
                                                  className: "company-icon-container"
                                                }, React.createElement("span", {
                                                      className: "pt-icon-standard pt-icon-edit",
                                                      title: "Edit",
                                                      onClick: (function (_e) {
                                                          return Curry._1(openEditDialog, company);
                                                        })
                                                    }), React.createElement("span", {
                                                      className: "pt-icon-standard pt-icon-trash margin-left-md",
                                                      title: "Remove",
                                                      onClick: (function (_e) {
                                                          return Curry._1(removeCompany, company);
                                                        })
                                                    }))));
                            }), companies))));
  };
  var renderLoading = function (param) {
    return React.createElement("div", {
                className: "align-middle"
              }, React.createElement(Core.Spinner, {
                    className: "pt-small"
                  }), React.createElement("span", {
                    className: "margin-left-md"
                  }, Utils.textEl("Loading")));
  };
  var fetchAll = function (handleCompaniesLoaded, handleError) {
    Model_company.Api.fetchAll(undefined).then(function (companies) {
            Curry._1(handleCompaniesLoaded, companies);
            return Promise.resolve(undefined);
          }).catch(function (_err) {
          Notify.showError("Failed to fetch companies! Check network connection!");
          Curry._1(handleError, undefined);
          return Promise.resolve(undefined);
        });
    
  };
  var toggleAddDialog = function (_event) {
    return Curry._1(dispatch, /* ToggleAddDialog */1);
  };
  var openEditDialog = function (company) {
    return Curry._1(dispatch, {
                TAG: /* ToggleEditDialog */4,
                _0: company
              });
  };
  var closeEditDialog = function (_event) {
    return Curry._1(dispatch, {
                TAG: /* ToggleEditDialog */4,
                _0: undefined
              });
  };
  var removeCompany = function (company) {
    var handleCompanyRemoved = function (removedId) {
      return Curry._1(dispatch, {
                  TAG: /* RemoveCompany */3,
                  _0: removedId
                });
    };
    var companyId = company.id;
    if (companyId !== undefined) {
      Model_company.Api.remove(companyId).then(function (param) {
              Curry._1(handleCompanyRemoved, companyId);
              return Promise.resolve(undefined);
            }).catch(function (_err) {
            Notify.showError("Failed to delete company! Check network connection!");
            return Promise.resolve(undefined);
          });
      return ;
    } else {
      Notify.showError("Internal error! Attempting to remove company without id!");
      return ;
    }
  };
  var addCompany = function (company) {
    var handleCompanyAdded = function (company) {
      return Curry._1(dispatch, {
                  TAG: /* AddCompany */1,
                  _0: company
                });
    };
    Model_company.Api.add(company).then(function (addedCompany) {
            Curry._1(handleCompanyAdded, addedCompany);
            return Promise.resolve(undefined);
          }).catch(function (_err) {
          Notify.showError("Failed to add company! Check network connection!");
          return Promise.resolve(undefined);
        });
    
  };
  var editCompany = function (company) {
    var handleCompanyEdited = function (company) {
      return Curry._1(dispatch, {
                  TAG: /* EditCompany */2,
                  _0: company
                });
    };
    Model_company.Api.edit(company).then(function (param) {
            Curry._1(handleCompanyEdited, company);
            return Promise.resolve(undefined);
          }).catch(function (_err) {
          Notify.showError("Failed to edit company! Check network connection!");
          return Promise.resolve(undefined);
        });
    
  };
  var companies = state.companies;
  var companiesContent = companies !== undefined ? renderCompanies(companies, removeCompany, openEditDialog) : renderLoading(undefined);
  React.useEffect((function () {
          fetchAll((function (companies) {
                  return Curry._1(dispatch, {
                              TAG: /* Loaded */0,
                              _0: companies
                            });
                }), (function (param) {
                  return Curry._1(dispatch, /* LoadError */0);
                }));
          
        }), []);
  if (state.hasLoadError) {
    return React.createElement("h2", {
                className: "pt-running-text"
              }, Utils.textEl("Error loading companies! Check network connection and reload!"));
  } else {
    return React.createElement("div", undefined, React.createElement("h1", {
                    className: "pt-running-text"
                  }, Utils.textEl("Companies")), state.companies !== undefined ? React.createElement("div", undefined, React.createElement(Core.Button, {
                          onClick: toggleAddDialog,
                          children: Utils.textEl("Add company")
                        })) : null, React.createElement("div", undefined, companiesContent), React.createElement(Core.Dialog, {
                    isOpen: state.addDialogOpen,
                    onClose: toggleAddDialog,
                    title: Utils.textEl("Add new company"),
                    children: React.createElement(View_companies$CompanyDialog, {
                          onSubmit: addCompany,
                          onClose: toggleAddDialog,
                          data: state.editCompany
                        })
                  }), React.createElement(Core.Dialog, {
                    isOpen: state.editCompany !== undefined,
                    onClose: closeEditDialog,
                    title: Utils.textEl("Edit company"),
                    children: React.createElement(View_companies$CompanyDialog, {
                          onSubmit: editCompany,
                          onClose: closeEditDialog,
                          data: state.editCompany
                        })
                  }));
  }
}

var make = View_companies;

exports.CompanyDialog = CompanyDialog;
exports.make = make;
/*  Not a pure module */