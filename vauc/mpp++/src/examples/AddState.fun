// add_state.fun
//
//

{
  // Prelude
}

// Function definition :

name		AddState
parameters	Automaton, State

a:Automaton -> s:State :
{
  s = a.add_state();
}

b:Automaton -> e:String -> s:State :
{
  // some other code
}

// Some other code
{
 // Postlude
}