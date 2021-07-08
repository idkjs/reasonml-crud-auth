type t = {
  id: option(int),
  name: string,
  /* location: string,
     address: string,
     youtube: string,
     url: string,
     description: string,
     employees: string,
     sector: string,
     logo: string,
     tranch: string,
     jobs: string,
     twitter: string,
     joblinks: string,
     facebook: string,
     instagram: string */
};

module Decode = {
  let company = json =>
    Json.Decode.{
      id: json |> optional(field("id", int)),
      name: json |> field("name", string),
      /* location: json |> field("location", string),
         address: json |> field("address", string),
         youtube: json |> field("youtube", string),
         url: json |> field("url", string),
         description: json |> field("description", string),
         employees: json |> field("employees", string),
         sector: json |> field("sector", string),
         logo: json |> field("logo", string),
         tranch: json |> field("tranch", string),
         jobs: json |> field("jobs", string),
         twitter: json |> field("twitter", string),
         joblinks: json |> field("joblinks", string),
         facebook: json |> field("facebook", string),
         instagram: json |> field("instagram", string) */
    };
  let company_array = json => json |> Json.Decode.array(company);
};

/*
 /* prints { x: 42, foo: 'bar' } */
 Json.Encode.(object_([("x", int(42)), ("foo", string("bar"))]) |> Js.log);
 */
/* Json.Encode.(object_([("x", int(42)), ("foo", string("bar"), ("boom", string("baz"))]) |> Js.log); */
module Encode = {
  let company = companyObj =>
    Json.Encode.(
      object_([
        (
          "id",
          switch (companyObj.id) {
          | Some(id) => int(id)
          | None => null
          },
        ),
        ("name", string(companyObj.name)),
        /* ("location", string(companyObj.location)),
           ("address", string(companyObj.address)),
           ("youtube", string(companyObj.youtube)),
           ("instagram", string(companyObj.instagram)),
           ("facebook", string(companyObj.facebook)),
           ("twitter", string(companyObj.twitter)),
           ("logo", string(companyObj.logo)),
           ("tranch", string(companyObj.tranch)),
           ("jobs", string(companyObj.jobs)),
           ("joblinks", string(companyObj.joblinks)),
           ("sector", string(companyObj.sector)),
           ("employees", string(companyObj.employees)),
           ("description", string(companyObj.description)),
           ("url", string(companyObj.url)) */
      ])
    );
};

module Api = {
  let baseUrl = Constants.apiUrl;
  let companiesUrl = {j|$baseUrl/companies|j};
  let companyUrl = id => {j|$baseUrl/companies/$id|j};
  let fetch = (id: int) =>
    Js.Promise.(
      Fetch.fetch(companyUrl(id))
      |> then_(Fetch.Response.json)
      |> then_(json => json |> Decode.company |> resolve)
    );
  let fetchAll = () =>
    Js.Promise.(
      Fetch.fetch(companiesUrl)
      |> then_(Fetch.Response.json)
      |> then_(json => json |> Decode.company_array |> resolve)
    );
  let add = company => {
    let body =
      Fetch.BodyInit.make(company |> Encode.company |> Js.Json.stringify);
    let headers = Common.Request.getDefaultHeaders();
    let request = Fetch.RequestInit.make(~method_=Post, ~body, ~headers, ());
    Js.Promise.(
      Fetch.fetchWithInit(companiesUrl, request)
      |> then_(Fetch.Response.json)
      |> then_(json => json |> Decode.company |> resolve)
    );
  };
  let edit = company => {
    let body =
      Fetch.BodyInit.make(company |> Encode.company |> Js.Json.stringify);
    let headers = Common.Request.getDefaultHeaders();
    let request = Fetch.RequestInit.make(~method_=Put, ~body, ~headers, ());
    Js.Promise.(
      Fetch.fetchWithInit(companyUrl(company.id), request)
      |> then_(Common.Response.statusOk)
    );
  };
  let remove = id =>
    Js.Promise.(
      Fetch.fetchWithInit(
        companyUrl(id),
        Fetch.RequestInit.make(~method_=Delete, ()),
      )
      |> then_(Common.Response.statusOk)
    );
};

/* Reducer helper methods */
let append = (companies, company: t) =>
  Some(Array.concat([Utils.optToArrayOrEmpty(companies), [|company|]]));

let replace = (companies, company: t) =>
  Some(
    Array.map(
      c => c.id === company.id ? {...company, id: c.id} : c,
      Utils.optToArrayOrEmpty(companies),
    ),
  );

let removeWithId = (companies, id) => {
  let companyList = Array.to_list(Utils.optToArrayOrEmpty(companies));
  let filteredList =
    List.filter(
      company => Utils.optIntOrRaise(company.id) !== id,
      companyList,
    );
  Some(Array.of_list(filteredList));
};
