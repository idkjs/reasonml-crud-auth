// Generated by ReScript, PLEASE EDIT WITH CARE

import * as Curry from "../../../../../../usr/local/lib/node_modules/bs-platform/lib/es6/curry.js";
import * as Caml_option from "../../../../../../usr/local/lib/node_modules/bs-platform/lib/es6/caml_option.js";
import * as Js_null_undefined from "../../../../../../usr/local/lib/node_modules/bs-platform/lib/es6/js_null_undefined.js";

function unwrapValue(param) {
  if (param.NAME === "Enum") {
    throw {
          RE_EXN_ID: "Assert_failure",
          _1: [
            "blueprintjs.re",
            14,
            16
          ],
          Error: new Error()
        };
  }
  return param.VAL;
}

function toInt(x) {
  return x - 1 | 0;
}

function fromOpt(o) {
  if (o !== undefined) {
    return o - 1 | 0;
  }
  
}

var Intent = {
  toInt: toInt,
  fromOpt: fromOpt
};

function optionMap(fn, option) {
  if (option !== undefined) {
    return Caml_option.some(Curry._1(fn, Caml_option.valFromOption(option)));
  }
  
}

function toString(param) {
  if (param) {
    return "right";
  } else {
    return "left";
  }
}

var NavbarAlign = {
  toString: toString
};

function toString$1(param) {
  if (param) {
    return "submit";
  } else {
    return "button";
  }
}

var ButtonType = {
  toString: toString$1
};

var Navbar = {};

var NavbarGroup = {};

var NavbarHeading = {};

var Button = {};

var NavbarDivider = {};

var Tabs = {};

var Tab = {};

var Dialog = {};

var Label = {};

var FormGroup = {};

var InputGroup = {};

var Spinner = {};

function toInt$1(x) {
  return x;
}

function fromOpt$1(o) {
  if (o !== undefined) {
    return o;
  }
  
}

var Position = {
  toInt: toInt$1,
  fromOpt: fromOpt$1
};

var ActionProps = {};

function create(message, action, intent, iconName, onDismiss, timeout, param) {
  return {
          iconName: Js_null_undefined.fromOption(iconName),
          intent: Js_null_undefined.fromOption(optionMap(toInt, intent)),
          message: message,
          action: Js_null_undefined.fromOption(action),
          onDismiss: Js_null_undefined.fromOption(onDismiss),
          timeout: Js_null_undefined.fromOption(timeout)
        };
}

var ToastPropsOld = {
  create: create
};

var ToastProps = {};

var IToaster = {};

var ToasterProps = {};

var Toaster = {};

export {
  unwrapValue ,
  Intent ,
  optionMap ,
  NavbarAlign ,
  ButtonType ,
  Navbar ,
  NavbarGroup ,
  NavbarHeading ,
  Button ,
  NavbarDivider ,
  Tabs ,
  Tab ,
  Dialog ,
  Label ,
  FormGroup ,
  InputGroup ,
  Spinner ,
  Position ,
  ActionProps ,
  ToastPropsOld ,
  ToastProps ,
  IToaster ,
  ToasterProps ,
  Toaster ,
  
}
/* No side effect */
