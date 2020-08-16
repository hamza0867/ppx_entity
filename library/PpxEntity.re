open Ppxlib;

let expand = (~ctxt, structure) => {
  let loc = Expansion_context.Extension.extension_point_loc(ctxt);
  let new_structure =
    structure
    |> List.fold_right(~init=[], ~f=(item, acc: structure) => {
         switch (item.pstr_desc) {
         | Pstr_type(rec_flag, type_declarations) =>
           let new_item = {
             pstr_loc: item.pstr_loc,
             pstr_desc:
               Pstr_type(
                 rec_flag,
                 type_declarations
                 |> List.map(~f=type_declaration =>
                      switch (type_declaration.ptype_name.txt) {
                      | "t" =>
                        type_declaration.ptype_kind
                        |> (
                          fun
                          | Ptype_record(label_declarations) =>
                            label_declarations
                            |> List.iter(~f=label_declaration => {
                                 Stdio.Out_channel.print_endline(
                                   string_of_core_type(
                                     label_declaration.pld_type,
                                   ),
                                 )
                               })
                          | _ => ()
                        );

                        {
                          ...type_declaration,
                          ptype_name: {
                            ...type_declaration.ptype_name,
                            txt: "main",
                          },
                        };
                      | _ => type_declaration
                      }
                    ),
               ),
           };
           [new_item, ...acc];
         | _ => [item, ...acc]
         }
       });

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
