// letter_automaton.modules
//
//

name LetterAutomaton

type CharAlphabet      is Alphabet        with Letter = char
type LetterAutomaton   is LetterAutomaton with Alphabet = CharAlphabet
type LAEdge	       is Edge
type LAState           is State


//  Interpr.             Fonction interne.
fun add_state        is  AddState with 
			              Automaton = LetterAutomaton, 
			              State     = LAState 



// ...