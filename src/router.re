let getPageFromPath = path => {
  let route = Routes.getRoute(path);
  switch (route) {
  | Home => <View_home />
  | Companies => <View_companies />
  | Company(id) => <View_company id />
  | NotFound => <div> {Utils.textEl("Page not found!")} </div>
  };
};

let getInitialPage = () =>
  getPageFromPath(RescriptReactRouter.dangerouslyGetInitialUrl().path);

let init = pageChanged => {
  let watchId =
    RescriptReactRouter.watchUrl(url => {
      let page = getPageFromPath(url.path);
      pageChanged(page);
    });
  watchId;
};

let destroy = RescriptReactRouter.unwatchUrl;
