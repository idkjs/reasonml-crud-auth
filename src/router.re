let getPageFromPath = path => {
  let route = Routes.getRoute(path);
  switch route {
  | Home => <View_home />
  | Companies => <View_companies />
  | Company(id) => <View_company id />
  | NotFound => <div> (Utils.textEl("Page not found!")) </div>
  };
};

let getInitialPage = () =>
  getPageFromPath(ReasonReact.Router.dangerouslyGetInitialUrl().path);

let init = pageChanged => {
  let watchId =
    ReasonReact.Router.watchUrl(url => {
      let page = getPageFromPath(url.path);
      pageChanged(page);
    });
  watchId;
};

let destroy = ReasonReact.Router.unwatchUrl;