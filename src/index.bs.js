// Generated by ReScript, PLEASE EDIT WITH CARE
'use strict';

var App = require("./app.bs.js");
var Utils = require("./utils.bs.js");
var React = require("react");
var ReactDom = require("react-dom");

require("./index.css");

Utils.registerServiceWorker(undefined);

var root = document.querySelector("#root");

if (root == null) {
  console.log("Coudn't find #root element to mount the React app.");
} else {
  ReactDom.render(React.createElement(App.make, {}), root);
}

/*  Not a pure module */
