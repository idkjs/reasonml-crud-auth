type jsUnsafe;

external toJsUnsafe: 'a => jsUnsafe = "%identity";

let unwrapValue =
  fun
  | `String(s) => toJsUnsafe(s)
  | `Bool(b) => toJsUnsafe(b)
  | `Float(f) => toJsUnsafe(f)
  | `Date(d) => toJsUnsafe(d)
  | `Callback(c) => toJsUnsafe(c)
  | `Element(e) => toJsUnsafe(e)
  | `Object(o) => toJsUnsafe(o)
  | `Enum(_) => assert(false);

module Intent = {
  type t =
    | NONE
    | PRIMARY
    | SUCCESS
    | WARNING
    | DANGER;
  let toInt = x =>
    switch (x) {
    | NONE => (-1)
    | PRIMARY => 0
    | SUCCESS => 1
    | WARNING => 2
    | DANGER => 3
    };
  let fromOpt = o =>
    switch (o) {
    | Some(intent) => Js.Undefined.return(toInt(intent))
    | None => Js.Undefined.empty
    };
};

let optionMap = (fn, option) =>
  switch (option) {
  | Some(value) => Some(fn(value))
  | None => None
  };

module NavbarAlign = {
  type t =
    | Left
    | Right;
  let toString =
    fun
    | Left => "left"
    | Right => "right";
};

module ButtonType = {
  type t =
    | Button
    | Submit;
  let toString =
    fun
    | Button => "button"
    | Submit => "submit";
};

module Navbar = {
  [@bs.module "@blueprintjs/core"] [@react.component]
  external make:
    (~className: option(string)=?, ~children: React.element) => React.element =
    "Navbar";
};

module NavbarGroup = {
  [@bs.module "@blueprintjs/core"] [@react.component]
  external make:
    (
      ~className: option(string)=?,
      ~align: option(NavbarAlign.t)=?,
      ~children: React.element
    ) =>
    React.element =
    "NavbarGroup";
};
module NavbarHeading = {
  [@bs.module "@blueprintjs/core"] [@react.component]
  external make:
    (~className: option(string)=?, ~children: React.element) => React.element =
    "NavbarHeading";
};

module Button = {
  [@bs.module "@blueprintjs/core"] [@react.component]
  external make:
    (
      ~active: option(bool)=?,
      ~className: option(string)=?,
      ~disabled: option(bool)=?,
      ~elementRef: option(Dom.element)=?,
      ~iconName: option(string)=?,
      ~intent: option(Intent.t)=?,
      ~loading: option(bool)=?,
      ~onClick: option(React.callback(ReactEvent.Mouse.t, 'a))=?,
      ~rightIconName: option(string)=?,
      ~text: option(string)=?,
      ~buttonType: option(ButtonType.t)=?,
      ~children: option(React.element)=?
    ) =>
    React.element =
    "Button";
  // let make =
  //     (
  //       ~active: option(bool)=?,
  //       ~className: option(string)=?,
  //       ~disabled: option(bool)=?,
  //       ~elementRef: option(Dom.element)=?,
  //       ~iconName: option(string)=?,
  //       ~intent: option(Intent.t)=?,
  //       ~loading: option(bool)=?,
  //       ~onClick: option(React.callback.t(ReactEvent.Mouse.t))=?,
  //       ~rightIconName: option(string)=?,
  //       ~text: option(string)=?,
  //       ~buttonType: option(ButtonType.t)=?,
  //       children
  //     ) =>
  //   React.wrapJsForReason(
  //     ~reactClass,
  //     ~props={
  //       "active": Js.Nullable.fromOption(optionMap( , active)),
  //       "className": Js.Nullable.fromOption(className),
  //       "disabled": Js.Nullable.fromOption(optionMap( , disabled)),
  //       "elementRef": Js.Nullable.fromOption(elementRef),
  //       "iconName": Js.Nullable.fromOption(iconName),
  //       "intent": Js.Nullable.fromOption(optionMap(Intent.toInt, intent)),
  //       "loading": Js.Nullable.fromOption(optionMap( , loading)),
  //       "onClick": Js.Nullable.fromOption(onClick),
  //       "rightIconName": Js.Nullable.fromOption(rightIconName),
  //       "text": Js.Nullable.fromOption(text),
  //       "type": Js.Nullable.fromOption(optionMap(ButtonType.toString, buttonType))
  //     },
  //     children
  //   );
};

module NavbarDivider = {
  [@bs.module "@blueprintjs/core"] [@react.component]
  external make: (~className: option(string)=?) => React.element =
    "NavbarDivider";
};

module Tabs = {
  type onChangeEvent = {
    newTab: string,
    oldTab: string,
    event: ReactEvent.Mouse.t,
  };
  [@bs.module "@blueprintjs/core"] [@react.component]
  external make:
    (
      ~animate: option(bool)=?,
      ~className: option(string)=?,
      ~id: string,
      ~onChange: option((string, string, ReactEvent.Mouse.t) => unit)=?,
      ~children: React.element
    ) =>
    React.element =
    "Tabs2";
};

module Tab = {
  [@bs.module "@blueprintjs/core"] [@react.component]
  external make:
    (
      ~className: option(string)=?,
      ~id: string,
      ~title: option(string)=?,
      ~panel: option(React.element)=?,
      ~children: React.element
    ) =>
    React.element =
    "Tab2";
};

module Dialog = {
  [@bs.module "@blueprintjs/core"] [@react.component]
  external make:
    (
      ~isOpen: bool,
      ~autoFocus: option(bool)=?,
      ~backdropClassName: option(string)=?,
      ~backdropProps: option(Js.t({..}))=?,
      ~canEscapeKeyClose: option(bool)=?,
      ~canOutsideClickClose: option(bool)=?,
      ~className: option(string)=?,
      ~enforceFocus: option(bool)=?,
      ~hasBackdrop: option(bool)=?,
      ~iconName: option(string)=?,
      ~inline: option(bool)=?,
      ~isCloseButtonShown: option(bool)=?,
      ~_lazy: option(bool)=?,
      ~onClose: option('a => unit)=?,
      ~style: option(ReactDOM.style)=?,
      ~title: option(React.element)=?, /* TODO: can be also string */
      ~transitionDuration: option(int)=?,
      ~transitionName: option(string)=?,
      ~children: React.element
    ) =>
    React.element =
    "Dialog";
};

module Label = {
  [@bs.module "@blueprintjs/core"] [@react.component]
  external make:
    (
      ~text: string,
      ~className: option(string)=?,
      ~disabled: option(bool)=?,
      ~helperText: option(React.element)=?,
      ~required: option(bool)=?,
      ~children: React.element
    ) =>
    React.element =
    "Label";
};

module FormGroup = {
  [@bs.module "@blueprintjs/core"] [@react.component]
  external make:
    (
      ~className: option(string)=?,
      ~disabled: option(bool)=?,
      ~helperText: option(React.element)=?,
      ~inline: option(bool)=?,
      ~intent: option(Intent.t)=?,
      ~label: option(React.element)=?,
      ~labelFor: option(string)=?,
      ~requiredLabel: option([ | `Bool(bool) | `Element(React.element)])=?,
      ~required: option(bool)=?,
      ~children: React.element
    ) =>
    React.element =
    "FormGroup";
};

module InputGroup = {
  [@bs.module "@blueprintjs/core"] [@react.component]
  external make:
    (
      ~id: string=?,
      ~className: string=?,
      ~defaultValue: string=?,
      ~disabled: bool=?,
      ~inputRef: React.element=?,
      ~intent: Intent.t=?,
      ~leftIconName: string=?,
      ~onChange: React.callback('input, 'output)=?,
      ~placeholder: string=?,
      ~rightElement: React.element=?,
      ~_type: string=?,
      ~value: string=?
    ) =>
    React.element =
    "InputGroup";
};
module Spinner = {
  [@bs.module "@blueprintjs/core"] [@react.component]
  external make:
    (
      ~className: option(string)=?,
      ~intent: option(Intent.t)=?,
      ~value: option(int)=?
    ) =>
    React.element =
    "Spinner";
};

module Position = {
  type t =
    | TOP_LEFT
    | TOP
    | TOP_RIGHT
    | RIGHT_TOP
    | RIGHT
    | RIGHT_BOTTOM
    | BOTTOM_RIGHT
    | BOTTOM
    | BOTTOM_LEFT
    | LEFT_BOTTOM
    | LEFT
    | LEFT_TOP;
  let toInt = x =>
    switch (x) {
    | TOP_LEFT => 0
    | TOP => 1
    | TOP_RIGHT => 2
    | RIGHT_TOP => 3
    | RIGHT => 4
    | RIGHT_BOTTOM => 5
    | BOTTOM_RIGHT => 6
    | BOTTOM => 7
    | BOTTOM_LEFT => 8
    | LEFT_BOTTOM => 9
    | LEFT => 10
    | LEFT_TOP => 11
    };
  let fromOpt = o =>
    switch (o) {
    | Some(position) => Js.Undefined.return(toInt(position))
    | None => Js.Undefined.empty
    };
  [@bs.module "@blueprintjs/core"]
  external isPositionHorizontal: t => bool = "isPositionHorizontal";
  [@bs.module "@blueprintjs/core"]
  external isPositionVertical: t => bool = "isPositionVertical";
};

module ActionProps = {
  type t = {
    // .
    /** Visual intent color to apply to element. */
    intent: option(Intent.t),
    /** Whether this action is non-interactive. */
    disabled: option(bool),
    /** Name of the icon (the part after `pt-icon-`) to add to the button. */
    iconName: option(string), /* TODO - define IconName type */
    /** Click event handler. */
    onClick: option(unit => unit),
    /** Action text. */
    text: option(string),
    /** Link URL. */
    href: option(string),
    /** Link target attribute. Use `"_blank"` to open in a new window. */
    target: option(string),
  };
};

module ToastPropsOld = {
  type t = {
    // .
    /**
     * Action rendered as a minimal `AnchorButton`. The toast is dismissed automatically when the
     * user clicks the action button. Note that the `intent` prop is ignored (the action button
     * cannot have its own intent color that might conflict with the toast's intent). Omit this
     * prop to omit the action button.
     */
    action: Js.Nullable.t(ActionProps.t),
    /** Name of the icon (the part after `pt-icon-`) to appear before the message. */
    iconName: Js.Nullable.t(string), /* TODO - define IconName type */
    /** Visual intent color to apply to element. */
    intent: Js.Nullable.t(int),
    /** Message to display in the body of the toast. */
    message: React.element,
    /**
       * Callback invoked when the toast is dismissed, either by the user or by the timeout.
       * The value of the argument indicates whether the toast was closed because the timeout expired.
       */
    onDismiss: Js.Nullable.t(bool),
    /**
       * Milliseconds to wait before automatically dismissing toast.
       * Providing a value less than or equal to 0 will disable the timeout (this is discouraged).
       * @default 5000
       */
    timeout: Js.Nullable.t(int),
  };

  let create =
      (
        ~message: React.element,
        ~action: option(ActionProps.t)=?,
        ~intent: option(Intent.t)=?,
        ~iconName: option(string)=?,
        ~onDismiss: option(bool)=?,
        ~timeout: option(int)=?,
        (),
      ) => {
    {
      "iconName": Js.Nullable.fromOption(iconName),
      "intent": Js.Nullable.fromOption(optionMap(Intent.toInt, intent)),
      "message": message,
      /* todo next ones need correct conversion */
      "action": Js.Nullable.fromOption(action),
      "onDismiss": Js.Nullable.fromOption(onDismiss),
      "timeout": Js.Nullable.fromOption(timeout),
    };
  };
};
module ToastProps = {
  type t;
  // type props;
  [@bs.obj]
  external create:
    (
      ~message: React.element,
      ~action: option(ActionProps.t)=?,
      ~intent: option(Intent.t)=?,
      ~iconName: option(string)=?,
      ~onDismiss: option(bool)=?,
      ~timeout: option(int)=?,
      unit
    ) =>
    t;
};

module IToaster = {
  type t;
  /** Show a new toast to the user. Returns the unique key of the new toast. */
  [@bs.send]
  external show: (t, ToastProps.t) => string = "show";

  /**
   * Updates the toast with the given key to use the new props.
   * Updating a key that does not exist is effectively a no-op.
   */
  [@bs.send]
  external update: (t, string, ToastProps.t) => unit = "update";

  /** Dismiss the given toast instantly. */
  [@bs.send]
  external dismiss: (t, string) => unit = "dismiss";

  /** Dismiss all toasts instantly. */
  [@bs.send]
  external clear: t => unit = "clear";

  /** Returns the props for all current toasts. */;
  /* TODO - ToastOptions are almost same as ToastProps
    * [@bs.send] external getToasts : (t) => Js.Array.t(ToastOptions.t) = "getToasts";
   */
};

module ToasterProps = {
  // type t = {
  //   autoFocus: Js.Nullable.t(bool),
  //   canEscapeKeyClear: Js.Nullable.t(bool),
  //   className: Js.Nullable.t(string),
  //   inline: Js.Nullable.t(bool),
  //   position: Js.Nullable.t(int),
  // };
  type t;
  // type props;
  [@bs.obj]
  external create:
    (
      ~autoFocus: option(bool)=?,
      ~canEscapeKeyClear: option(bool)=?,
      ~className: option(string)=?,
      ~inline: option(bool)=?,
      ~position: option(Position.t)=?,
      unit
    ) =>
    t;
  // type t;
  // [@bs.module] external make: props => t = "pg-listen";
  // [@bs.obj]
  //   let create =
  //       (
  //         ~autoFocus: option(bool)=?,
  //         ~canEscapeKeyClear: option(bool)=?,
  //         ~className: option(string)=?,
  //         ~inline: option(bool)=?,
  //         ~position: option(Position.t)=?,
  //         (),
  //       ) = t;
  // let create =
  //     (
  //       ~autoFocus: option(bool)=?,
  //       ~canEscapeKeyClear: option(bool)=?,
  //       ~className: option(string)=?,
  //       ~inline: option(bool)=?,
  //       ~position: option(Position.t)=?,
  //       (),
  //     ) => {
  //   {
  //     "autoFocus": Js.Nullable.fromOption(autoFocus),
  //     "canEscapeKeyClear": Js.Nullable.fromOption(canEscapeKeyClear),
  //     "className": Js.Nullable.fromOption(className),
  //     "inline": Js.Nullable.fromOption(inline),
  //     "position":
  //       Js.Nullable.fromOption(optionMap(Position.toInt, position)),
  //   };
  // };
};

module Toaster = {
  [@bs.module "@blueprintjs/core"]
  external create: ToasterProps.t => IToaster.t = "Toaster";

  [@bs.module "@blueprintjs/core"] [@react.component]
  external make:
    (
      ~autoFocus: option(bool)=?,
      ~canEscapeKeyClear: option(bool)=?,
      ~className: option(string)=?,
      ~inline: option(bool)=?,
      ~position: option(Position.t)=?,
      ~children: React.element
    ) =>
    React.element =
    "Toaster";
};
