// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';

var Utils = require("./utils.bs.js");
var React = require("react");
var Routes = require("./routes.bs.js");
var Caml_exceptions = require("bs-platform/lib/js/caml_exceptions.js");
var RescriptReactRouter = require("@rescript/react/src/RescriptReactRouter.bs.js");

var CannotCreateLinkToNotFound = /* @__PURE__ */Caml_exceptions.create("Link.CannotCreateLinkToNotFound");

function Link(Props) {
  var route = Props.route;
  var className = Props.className;
  var children = Props.children;
  var isModifiedEvent = function ($$event) {
    if ($$event.metaKey || $$event.altKey || $$event.ctrlKey) {
      return true;
    } else {
      return $$event.shiftKey;
    }
  };
  var isLinkEvent = function ($$event) {
    if ($$event.button === 0) {
      return !isModifiedEvent($$event);
    } else {
      return false;
    }
  };
  var url;
  if (typeof route === "number") {
    switch (route) {
      case /* Home */0 :
          url = Routes.Home.url(undefined);
          break;
      case /* Companies */1 :
          url = Routes.Companies.url(undefined);
          break;
      case /* NotFound */2 :
          throw {
                RE_EXN_ID: CannotCreateLinkToNotFound,
                Error: new Error()
              };
      
    }
  } else {
    url = Routes.Company.url(route._0);
  }
  var handleClick = function ($$event) {
    if (isLinkEvent($$event)) {
      $$event.preventDefault();
      return RescriptReactRouter.push(url);
    }
    
  };
  var props = {
    className: Utils.optStringOrEmpty(className),
    href: url,
    onClick: handleClick
  };
  return React.createElement("a", props, children);
}

var make = Link;

exports.CannotCreateLinkToNotFound = CannotCreateLinkToNotFound;
exports.make = make;
/* Utils Not a pure module */
