const loki = require("lokijs");
const db = new loki("companies.json");

function loadCollection(colName, callback) {
  db.loadDatabase({}, function() {
    let col = db.getCollection(colName);

    if (!col) {
      console.log("Collection %s does not exit. Creating ...", colName);
      col = db.addCollection("companies");
    }

    callback(col);
  });
}

exports.getAll = (req, res) => {
  loadCollection("companies", companies => {
    console.log("Getting all companies", companies.data);
    res.json(companies.data);
  });
};
exports.get = (req, res) => {
  loadCollection("companies", companies => {
    const id = parseInt(req.params.companyId);
    console.log("Get company", id);
    const company = companies.findOne({ id: id });
    res.json(company);
  });
};
exports.create = (req, res) => {
  loadCollection("companies", companies => {
    const obj = req.body;
    obj.id = getNextId(companies.data);
    console.log("Inserting company", obj);
    const company = companies.insert(obj);
    db.saveDatabase();
    res.json(company);
  });
};
exports.update = (req, res) => {
  loadCollection("companies", companies => {
    const id = parseInt(req.params.companyId);
    console.log("Updating company with id", id);
    const company = companies.findOne({ id: id });
    company.name = req.body.name;
    companies.update(company);
    db.saveDatabase();
    res.sendStatus(200);
  });
};
exports.remove = (req, res) => {
  loadCollection("companies", companies => {
    const id = parseInt(req.params.companyId);
    console.log("Removing company with id", id);
    const company = companies.findOne({ id: id });
    companies.remove(company);
    db.saveDatabase();
    res.sendStatus(200);
  });
};

function getNextId(companiesData) {
  let id = 1;
  if (companiesData && companiesData.length > 0) {
    let ids = companiesData.map(c => c.id);
    let max = Math.max(...ids);
    console.log("next id", max, ids);
    id = max + 1;
  }
  return id;
}
