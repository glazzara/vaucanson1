// bencher.hxx: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
// Copyright (C) 2007 The Vaucanson Group.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//

#ifndef   	BENCHER_HXX_
# define   	BENCHER_HXX_
# include <vaucanson/misc/bencher.hh>

NAMESPACE_VCSN_BEGIN

namespace misc
{

  void
  Bencher::push (const Timer t)
  {
    if (this->timers_.empty ())
      this->timers_.push_back (t);
    else
    {
      // FIXME : Assert timers are compatible
      this->timers_.push_back (t);
    }
  }

  void
  Bencher::print (std::ostream& o)
  {
    std::vector< Timer >::const_iterator i;
    for (i = this->timers_.begin (); i != this->timers_.end (); ++i)
    {
      o << "------------------------" << std::endl;
      o << (*i);
    }
    o<< std::endl << "-------------------------" << std::endl;
    o << "        SUMMARY" << std::endl;
    o << "-------------------------" << std::endl;
    o << "ARITHMETIC MEANS" << std::endl
      << std::endl;
    o << this->arith_means_;
    o << "-------------------------" << std::endl;
    o << "MIN" << std::endl
      << std::endl;
    o << this->min_;
    o << "-------------------------" << std::endl;
    o << "MAX" << std::endl
      << std::endl;
    o << this->max_;
  }

  void
  Bencher::plot (std::ostream& o)
  {
    std::vector< Timer >::const_iterator i;
    for (i = this->timers_.begin (); i != this->timers_.end (); ++i)
    {
      o << (float) i->total.elapsed.wall / i->clocks_per_sec
	<< std::endl;
    }
  }

  void
  Bencher::arithmetical_means_set ()
  {
    std::vector< Timer >::const_iterator i;
    Timer::task_map_type::const_iterator j;
    unsigned int n1 = this->timers_.size ();

    // Summarize total times by classic mean
    for (i = this->timers_.begin ();
	 i != this->timers_.end ();
	 ++i)
    {
      this->arith_means_.total = this->arith_means_.total + i->total;

      // Summarize sub-timers
      for (j = i->tasksmap.begin ();
	   j != i->tasksmap.end ();
	   ++j)
      {
	// First time task is seen
	if (not this->arith_means_.tasksmap[j->first])
	{
	  this->arith_means_.tasksmap[j->first] =
	    new Timer::TimeVar (*j->second);
	  *(this->arith_means_.tasksmap[j->first]) /= n1;
	}
	else
	{
	  Timer::TimeVar* t_ptr =
	    new Timer::TimeVar (*j->second);
	  *(this->arith_means_.tasksmap[j->first]) += (*t_ptr) / n1;
	}
      }
    }

    this->arith_means_.total /= n1;
  }

  void
  Bencher::min_max_set ()
  {
    bool first = true;
    std::vector< Timer >::const_iterator i;
    Timer::task_map_type::const_iterator j;

    // Summarize total times by classic mean
    for (i = this->timers_.begin ();
	 i != this->timers_.end ();
	 ++i)
    {
      if (first)
      {
	this->min_.total = i->total;
	this->max_.total = i->total;
      }
      else
      {
	this->min_.total = this->min_.total.min (i->total);
	this->max_.total = this->max_.total.max (i->total);
      }

      // Summarize sub-timers
      for (j = i->tasksmap.begin ();
	   j != i->tasksmap.end ();
	   ++j)
      {
	if (first)
	{
	  this->min_.tasksmap[j->first] =
	    new Timer::TimeVar (*j->second);

	  this->max_.tasksmap[j->first] =
	    new Timer::TimeVar (*j->second);
	}
	else
	{
	  Timer::TimeVar* t_ptr =
	    new Timer::TimeVar (*j->second);
	  *(this->min_.tasksmap[j->first]) =
	    this->min_.tasksmap[j->first]->min((*t_ptr));

	  t_ptr = new Timer::TimeVar (*j->second);
	  *(this->max_.tasksmap[j->first]) =
	    this->max_.tasksmap[j->first]->max((*t_ptr));
	}
      }
      first = false;
    }
  }

  void
  Bencher::finalize ()
  {
    //Fixme
    // Recuperation des elements pour l'affichage
    if (this->timers_.begin () != this->timers_.end ())
    {
      this->arith_means_.tab_to_disp = this->timers_.begin()->tab_to_disp;
      this->arith_means_.task_ordered = this->timers_.begin()->task_ordered;

      this->min_.tab_to_disp = this->timers_.begin()->tab_to_disp;
      this->min_.task_ordered = this->timers_.begin()->task_ordered;

      this->max_.tab_to_disp = this->timers_.begin()->tab_to_disp;
      this->max_.task_ordered = this->timers_.begin()->task_ordered;
    }

    this->arithmetical_means_set ();
    this->min_max_set ();
  }
}

NAMESPACE_VCSN_END

#endif /* !BENCHER_HXX_ */
