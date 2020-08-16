open Ppxlib;

let expand = (~ctxt, structure) => {
  let loc = Expansion_context.Extension.extension_point_loc(ctxt);

  let new_structure =
    structure
    |> List.fold_right(~init=[], ~f=(item, acc) => {
         switch (item.pstr_desc) {
         | Pstr_type(rec_flag, declarations) =>
           let main_type_opt =
             declarations
             |> List.find(~f=declaration =>
                  switch (declaration.ptype_name.txt) {
                  | "t" => true
                  | _ => false
                  }
                );
           switch (main_type_opt) {
           | None => [item, ...acc]
           | Some(type_declaration) =>
             let new_type = {
               ...type_declaration,
               ptype_kind:
                 switch (type_declaration.ptype_kind) {
                 | Ptype_record(label_declarations) =>
                   Ptype_record(
                     label_declarations
                     |> List.map(~f=label_declaration =>
                          {
                            ...label_declaration,
                            pld_type: label_declaration.pld_type,
                          }
                        ),
                   )
                 | _ =>
                   Location.raise_errorf(
                     ~loc=type_declaration.ptype_loc,
                     "The main type of an entity should be a record",
                   )
                 },
             };
             let new_item = [%stri
               module Partial = {
                 %i
                 {
                   pstr_loc: Location.none,
                   pstr_desc: Pstr_type(rec_flag, [new_type]),
                 };
               }
             ];
             [item, new_item, ...acc];
           };
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
