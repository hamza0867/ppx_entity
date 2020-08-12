open Ppxlib;

let expand = (~ctxt, structure) => {
  let loc = Expansion_context.Extension.extension_point_loc(ctxt);
  let item =
    switch (structure) {
    | [hd, ..._] => hd
    | [] => Location.raise_errorf(~loc, "This module is empty")
    };
  Ast_builder.Default.pmod_structure(loc, [item]);
};

let my_extension =
  Extension.V3.declare(
    "reweb.entity",
    Extension.Context.module_expr,
    Ast_pattern.(pstr(__)),
    expand,
  );

let rule = Ppxlib.Context_free.Rule.extension(my_extension);

let () = Driver.register_transformation(~rules=[rule], "reweb.entity");
