module A = [%reweb.entity
  type t = {
    a: int,
    b: string,
  };
  type other = {c: option(string)}
];
