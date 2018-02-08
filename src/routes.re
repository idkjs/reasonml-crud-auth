type t =
  | Home
  | Companies
  | Company(int)
  | NotFound;

module Home = {
  let url = () => "/";
};

module Companies = {
  let url = () => "/companies";
};

module Company = {
  let url = id => {j|/companies/$id|j};
};

let getRoute = path =>
  /* TODO - make "pattern matching" so that you don't have to define urls twice in this file */
  switch path {
  | ["companies", id] => Company(int_of_string(id))
  | ["companies"] => Companies
  | [] => Home
  | _ => NotFound
  };

let convertToUrl = path =>
  List.fold_right((x, acc) => "/" ++ x ++ acc, path, "");