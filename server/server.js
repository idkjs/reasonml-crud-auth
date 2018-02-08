const express = require("express");
const bodyParser = require("body-parser");
const companies = require("./companies");
const app = express();
const port = process.env.PORT || 3001;

app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

app
  .route("/api/companies")
  .get(companies.getAll)
  .post(companies.create);

app
  .route("/api/companies/:companyId")
  .get(companies.get)
  .put(companies.update)
  .delete(companies.remove);

app.use(function(req, res) {
  res.status(404).send({ url: req.originalUrl + " not found" });
});

app.listen(port);

console.log("ReasonML CRUD example API server started on: " + port);
