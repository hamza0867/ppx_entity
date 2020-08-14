open Ppxlib;

let expand = (~ctxt, structure) => {
  let loc = Expansion_context.Extension.extension_point_loc(ctxt);
  let new_structure =
    structure
    |> List.map((item: Ppxlib_ast__.Import.Parsetree.structure_item) =>
         switch (item.pstr_desc) {
         | Pstr_type(rec_flag, type_declarations) => {
             pstr_loc: item.pstr_loc,
             pstr_desc:
               Pstr_type(
                 rec_flag,
                 type_declarations
                 |> List.map(type_declaration =>
                      switch (type_declaration.ptype_name.txt) {
                      | "t" =>
                        print_string("Found main type");
                        type_declaration;
                      | _ => type_declaration
                      }
                    ),
               ),
           }
         | _ => item
         }
       );
  Ast_builder.Default.pmod_structure(loc, new_structure);
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
