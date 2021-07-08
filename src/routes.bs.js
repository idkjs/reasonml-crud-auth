// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Caml_format = require("bs-platform/lib/js/caml_format.js");

function url(param) {
  return "/";
}

var Home = {
  url: url
};

function url$1(param) {
  return "/companies";
}

var Companies = {
  url: url$1
};

function url$2(id) {
  return "/companies/" + id;
}

var Company = {
  url: url$2
};

function getRoute(path) {
  if (!path) {
    return /* Home */0;
  }
  if (path.hd !== "companies") {
    return /* NotFound */2;
  }
  var match = path.tl;
  if (match) {
    if (match.tl) {
      return /* NotFound */2;
    } else {
      return /* Company */{
              _0: Caml_format.caml_int_of_string(match.hd)
            };
    }
  } else {
    return /* Companies */1;
  }
}

function convertToUrl(path) {
  return List.fold_right((function (x, acc) {
                return "/" + (x + acc);
              }), path, "");
}

exports.Home = Home;
exports.Companies = Companies;
exports.Company = Company;
exports.getRoute = getRoute;
exports.convertToUrl = convertToUrl;
/* No side effect */