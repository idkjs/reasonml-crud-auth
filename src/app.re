open Utils;

requireCSS("./app.css");

let logo = requireAssetURI("./logo.svg");

type state = {mainContent: React.element};

type action =
  | MainContentChanged(React.element);

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (_, action) =>
        switch (action) {
        | MainContentChanged(el) => {mainContent: el}
        },
      {mainContent: Router.getInitialPage()},
    );

  React.useEffect1(
    () => {
      let watcherID = Router.init(el => dispatch(MainContentChanged(el)));
      Some(() => Router.destroy(watcherID));
    },
    [|dispatch|],
  );
  <div className="app">
    <Blueprintjs.Navbar className="pt-dark">
      <Blueprintjs.NavbarGroup align=Blueprintjs.NavbarAlign.Left>
        <Link route=Routes.Home className="test">
          <img src=logo className="app-logo" alt="logo" />
        </Link>
        <Link
          route=Routes.Home className="pt-navbar-heading pt-button pt-minimal">
          {textEl("REASONML CRUD EXAMPLE")}
        </Link>
      </Blueprintjs.NavbarGroup>
      <Blueprintjs.NavbarGroup align=Blueprintjs.NavbarAlign.Right>
        <Link
          route=Routes.Companies
          className="pt-button pt-minimal pt-icon-people">
          {textEl("Companies")}
        </Link>
        <Blueprintjs.NavbarDivider />
        <Blueprintjs.Button className="pt-minimal" iconName="cog" />
      </Blueprintjs.NavbarGroup>
    </Blueprintjs.Navbar>
    <div className="app-content"> {state.mainContent} </div>
  </div>;
};
