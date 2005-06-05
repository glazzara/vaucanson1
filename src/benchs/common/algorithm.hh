#ifndef ALGORITHM_HH
# define ALGORITHM_HH

template <typename St, typename auto_t>
void fsm_dump(St& out, const auto_t& a)
{
  AUTOMATON_TYPES(auto_t);

  typename auto_t::initial_iterator initial = a.initial().begin();
  std::set<hedge_t> succ;

  a.deltac(succ, *initial, delta_kind::edges());
  for_all_const_(std::set<hedge_t>, e, succ)
    out << *initial << "\t" << a.aim_of(*e) << "\t"
	<< a.series_of(*e) << "\t 0"
	<< std::endl;
  for_each_state(s, a)
    if (!a.is_initial(*s))
    {
      succ.clear();
      a.deltac(succ, *s, delta_kind::edges());
      for_all_const_(std::set<hedge_t>, e, succ)
	out << *s << "\t" << a.aim_of(*e) << "\t"
	    << a.series_of(*e) << "\t 0"
	    << std::endl;
    }
  for_each_final_state(f, a)
    out << *f << "\t 0" << std::endl;
}
#endif
