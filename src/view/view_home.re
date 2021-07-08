open Utils;

[@react.component]("Home");

let make = () => {
   
   
    <div>
      <h1 className="margin-bottom-xl"> (textEl("Home")) </h1>
      <p> (textEl("This is REASONML CRUD example.")) </p>
      <p>
        (
          textEl(
            "Purpose of this project was to study REASONML and find a lean way how to implement common CRUD functionality using simple Company-entity."
          )
        )
      </p>
    </div>
};