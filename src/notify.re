open Blueprintjs;

let toasterProps = ToasterProps.create(~position=Some(Position.BOTTOM), ());

let toaster = Toaster.create(toasterProps);

let showError = text => {
  let props =
    ToastProps.create(
      ~message=React.string(text),
      ~iconName=Some("warning-sign"),
      ~intent=Some(Intent.DANGER),
      (),
    );
  IToaster.show(toaster, props);
};
