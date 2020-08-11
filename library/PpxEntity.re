open Ppxlib;

let expand = (~ctxt, structure: Ppxlib__.Import.structure) => {
  let loc = Expansion_context.Extension.extension_point_loc(ctxt);
  Ast_builder.Default.pmod_structure(loc, structure);
};

let my_extension =
  Extension.V3.declare(
    "reweb_entity",
    Extension.Context.module_expr,
    Ast_pattern.(pstr(__)),
    expand,
  );

let rule = Ppxlib.Context_free.Rule.extension(my_extension);

let () = Driver.register_transformation(~rules=[rule], "reweb_entity");
