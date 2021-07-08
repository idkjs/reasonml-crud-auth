exception CannotCreateLinkToNotFound;

[@react.component]
let make = (~route: Routes.t, ~className=?, ~children: React.element) => {
  let isModifiedEvent = (event: ReactEvent.Mouse.t) =>
    ReactEvent.Mouse.metaKey(event)
    || ReactEvent.Mouse.altKey(event)
    || ReactEvent.Mouse.ctrlKey(event)
    || ReactEvent.Mouse.shiftKey(event);
  let isLinkEvent = (event: ReactEvent.Mouse.t) =>
    ReactEvent.Mouse.button(event) == 0  /* ignore everything but left clicks */
    && !isModifiedEvent(event); /* ignore clicks with modifier keys */

  let url =
    switch (route) {
    | Home => Routes.Home.url()
    | Companies => Routes.Companies.url()
    | Company(id) => Routes.Company.url(id)
    | NotFound => raise(CannotCreateLinkToNotFound)
    };
  let handleClick = (event: ReactEvent.Mouse.t) =>
    if (isLinkEvent(event)) {
      ReactEvent.Mouse.preventDefault(event);
      RescriptReactRouter.push(url);
    };
  let props =
    ReactDOM.domProps(
      ~className=Utils.optStringOrEmpty(className),
      ~onClick=handleClick,
      ~href=url,
      (),
    );

  React.createElementVariadic(
    ReactDOM.stringToComponent("a"),
    props->Obj.magic,
    [|children|],
  );
};
