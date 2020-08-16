module A = [%reweb.entity
  type t = {
    a: int,
    b: string,
  };
  type other = {x: bool};
  let a = 5;
  let b = true;
  module X = {
    let b = "new";
  }
];
