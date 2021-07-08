open Utils;

requireCSS("./index.css");
// %raw{|import "@blueprintjs/core/dist/blueprint.css"|}
registerServiceWorker();

// ReactDOM.renderToElementWithId(<App />, "root");
switch (ReactDOM.querySelector("#root")) {
| Some(root) => ReactDOM.render(<App />, root)
| None => Js.log("Coudn't find #root element to mount the React app.")
};
