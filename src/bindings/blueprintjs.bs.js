// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var Js_null_undefined = require("bs-platform/lib/js/js_null_undefined.js");

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

exports.unwrapValue = unwrapValue;
exports.Intent = Intent;
exports.optionMap = optionMap;
exports.NavbarAlign = NavbarAlign;
exports.ButtonType = ButtonType;
exports.Navbar = Navbar;
exports.NavbarGroup = NavbarGroup;
exports.NavbarHeading = NavbarHeading;
exports.Button = Button;
exports.NavbarDivider = NavbarDivider;
exports.Tabs = Tabs;
exports.Tab = Tab;
exports.Dialog = Dialog;
exports.Label = Label;
exports.FormGroup = FormGroup;
exports.InputGroup = InputGroup;
exports.Spinner = Spinner;
exports.Position = Position;
exports.ActionProps = ActionProps;
exports.ToastPropsOld = ToastPropsOld;
exports.ToastProps = ToastProps;
exports.IToaster = IToaster;
exports.ToasterProps = ToasterProps;
exports.Toaster = Toaster;
/* No side effect */