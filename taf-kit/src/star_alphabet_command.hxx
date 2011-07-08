
static int
star_alphabet_command(const arguments_t& args)
{
  alphabet_t alpha= get_alphabet(args.alphabet);
	// alphabet_t  alpha;
	//  Create a single state automaton
  automaton_t a = make_automaton(alpha);
  hstate_t q = a.add_state();
	a.set_initial(q);
	a.set_final(q);

	// Add a loop on the single state labeled by every letter of the alphabet
	for(alphabet_iterator i = alpha.begin() ; i != alpha.end(); ++i)
    {
    	a.add_letter_transition(q,q,*i);
    }
  g_res.keep(a);
  return 0;
}

