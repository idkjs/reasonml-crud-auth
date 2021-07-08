open Utils;

requireCSS("./index.css");

registerServiceWorker();

ReactDOM.renderToElementWithId(<App />, "root");