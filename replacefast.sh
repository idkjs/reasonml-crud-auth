#!/bin/sh
# cd ..
files=$(find src -name "*.re" && find src -name "*.rei")
echo $files
for file in $files
do
echo $PWD/$file

# fastreplacestring $file "ReasonReact.NoUpdate" "NoUpdate"
fastreplacestring $file "ReasonReact.Update" " "
fastreplacestring $file "ReasonReact.NoUpdate" "state"
fastreplacestring $file "ReasonReact.UpdateWithSideEffects" "UpdateWithSideEffects"
# fastreplacestring $file "ReactEventRe.Synthetic" "ReactEvent.Synthetic"
# fastreplacestring $file "ReactEventRe" "ReactEvent"
fastreplacestring $file "Js.Null_undefined.to_opt" "Js.Nullable.toOption"
fastreplacestring $file "Js.Nullable.to_opt" "Js.Nullable.toOption"
fastreplacestring $file "Js.Nullable.from_opt" "Js.Nullable.fromOption"
fastreplacestring $file "Js.Null_undefined.to_opt" "Js.Nullable.toOption"
fastreplacestring $file "Js.Boolean.to_js_boolean" " "
fastreplacestring $file "ReactEventRe." "ReactEvent."

fastreplacestring $file "ReasonReact.Router" "RescriptReactRouter"
fastreplacestring $file "nullElement" "null"
fastreplacestring $file "stringToElement" "string"
# fastreplacestring $file "ReasonReact.string" "React.string"
fastreplacestring $file "arrayToElement" "array"
# fastreplacestring $file "ReasonReact.array" "React.array"
fastreplacestring $file "reactElement" "element"
fastreplacestring $file "Js.boolean" "bool"
fastreplacestring $file "Js.false_" "false"
fastreplacestring $file "Js.true_" "true"
fastreplacestring $file "self.state" "state"
fastreplacestring $file "let component = ReasonReact.reducerComponent" "[@react.component]"
fastreplacestring $file "let component = ReasonReact.statelessComponent" "[@react.component]"
fastreplacestring $file "_children" "()"
fastreplacestring $file "render: _self =>" " "
fastreplacestring $file "...component," " "
fastreplacestring $file "ReasonReact." "React."
fastreplacestring $file " children)" " ~children)"
fastreplacestring $file "external reactClass : React.reactClass" "[@react.component] external make :() => React.element"

done
