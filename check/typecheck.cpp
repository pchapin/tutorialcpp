
// The following OCaml program is due to Mairson (1990). It is well
// typed but it takes a long time to typecheck. The OCaml type inference
// algorithms requires expontential time in the worst case.
//
// let f0 = fun x -> (x, x) in
//   let f1 = fun y -> f0 (f0, y) in
//     let f2 = fun y -> f1 (f1, y) in
//       let f3 = fun y -> f2 (f2, y) in
//         let f4 = fun y -> f3 (f3, y) in
//           let f5 = fun y -> f4 (f4, y) in
//             f5 (fun z -> z)
//
// The following C++ program is an attempt to duplicate this with C++'s
// template type deduction process. The goal here is to learn something.
//

#include <utility>

template<class Type>
std::pair<Type, Type>
  f0(const Type &x)
{
  return std::make_pair(x, x);
}

template<class Type>
std::pair< std::pair< std::pair<Type, Type> (*)(const Type &), Type>,
           std::pair< std::pair<Type, Type> (*)(const Type &), Type> > 
  f1(const Type &y)
{
  return f0(std::make_pair(f0, y));
}

template<class Type>
Type identity(const Type &z)
{
  return z;
}

int main()
{
  f1(identity);
  return 0;
}

// Hmmm.
