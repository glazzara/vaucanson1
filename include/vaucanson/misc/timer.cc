// timer.cc: this file is part of the Vaucanson project.
//
// Vaucanson, a generic library for finite state machines.
//
// Copyright (C) 2006, 2007 The Vaucanson Group.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//

/**
 ** \file misc/timer.cc
 ** \brief Implementation for misc/timer.hh.
 */

#ifndef VCSN_MISC_TIMER_CC
# define VCSN_MISC_TIMER_CC

# include <iostream>
# include <iomanip>

# include <unistd.h>

# if defined VAUCANSON
#  include <vaucanson/misc/timer.hh>
# else
#  include "timer.hh"
# endif



/// This file is also used in Tiger Compiler, where it is compiled in
/// a C library, so INLINE_TIMER_CC should be defined to empty in that
/// case.
# if defined VAUCANSON
#  define INLINE_TIMER_CC inline
# else
#  define INLINE_TIMER_CC
# endif

NAMESPACE_VCSN_BEGIN

namespace misc
{

  /*------------------.
  | Timer.            |
  | General methods.  |
  `------------------*/

  INLINE_TIMER_CC
  Timer::Timer ()
    : ticks_per_sec_  (sysconf (_SC_CLK_TCK)),
      comp_count_     (0),
      task_count_     (1),
      is_running_     (false),
      cleared_        (true)
  {
  }

  INLINE_TIMER_CC
  Timer::Timer       (const Timer& rhs)
    : ticks_per_sec_ (rhs.ticks_per_sec_),
      calls_         (rhs.calls_),
      tasks_         (rhs.tasks_),
      names_         (rhs.names_),
      time_          (rhs.time_),
      graph_         (rhs.graph_),
      comp_id_       (rhs.comp_id_),
      comp_          (rhs.comp_),
      comp_count_    (rhs.comp_count_),
      task_count_    (rhs.task_count_),
      is_running_    (rhs.is_running_),
      cleared_       (rhs.cleared_)
  {
  }

  INLINE_TIMER_CC
  const Timer& Timer::operator= (const Timer& rhs)
  {
    if (this == &rhs)
      return *this;

    ticks_per_sec_ = rhs.ticks_per_sec_;
    names_         = rhs.names_;
    time_          = rhs.time_;
    graph_         = rhs.graph_;
    calls_         = rhs.calls_;
    comp_id_       = rhs.comp_id_;
    comp_          = rhs.comp_;
    comp_count_    = rhs.comp_count_;
    task_count_    = rhs.task_count_;
    tasks_         = rhs.tasks_;
    is_running_    = rhs.is_running_;
    cleared_       = rhs.cleared_;

    return *this;
  }

  INLINE_TIMER_CC
  void
  Timer::clear ()
  {
    while (!calls_.empty ())
      calls_.pop ();

    tasks_.clear ();
    names_.clear ();
    time_.clear ();

    graph_.clear ();
    comp_id_.clear ();
    comp_.clear ();

    comp_count_ = 0;
    task_count_ = 1;
    is_running_ = false;
    cleared_    = true;
  }

  INLINE_TIMER_CC
  void
  Timer::start ()
  {
    clear ();
    cleared_ = false;

    tasks_.resize (1);

    names_["_program_"] = 0;
    tasks_[0].name_     = "_Program_";
    tasks_[0].id_       = 0;

    time_.set_to_now ();
    is_running_ = true;
  }

  INLINE_TIMER_CC
  void
  Timer::stop ()
  {
    if (is_running_)
      {
	while (!calls_.empty ())
	  pop();

	time_.set_to_lap ();

	task_count_ = tasks_.size ();

	build_output_graph ();
	build_connected_components ();

	compute_output_graph ();
	compute_connected_components ();

	tasks_.clear ();
	names_.clear ();
	time_.clear ();
      }

    is_running_ = false;
  }

  /*------------------------.
  | Timer.                  |
  | Call stack management.  |
  `------------------------*/

  INLINE_TIMER_CC
  void
  Timer::push (const std::string& name)
  {
    unsigned int i;

    timer::StackedCall _call (0);

    timer::task_names_map::iterator iter = names_.find (name);

    if (iter == names_.end ())
      {
	i = tasks_.size ();
	tasks_.resize (i + 1);

	names_[name]    = i;
	tasks_[i].name_ = name;
	tasks_[i].id_   = i;
      }
    else
      {
	i = iter->second;
      }

    _call.called_ = i;
    calls_.push (_call);
  }

  INLINE_TIMER_CC
  unsigned int
  Timer::task (const std::string& name)
  {
    timer::task_names_map::iterator iter = names_.find (name);

    if (iter == names_.end ())
      {
	unsigned int i;

	i = tasks_.size ();
	tasks_.resize (i + 1);

	names_[name]    = i;
	tasks_[i].name_ = name;
	tasks_[i].id_   = i;
	return i;
      }
    else
      {
	return iter->second;
      }
  }

  INLINE_TIMER_CC
  void
  Timer::push (const unsigned int i)
  {
    timer::StackedCall _call (0);

    if (i >= tasks_.size ())
      {
	std::cerr << "Timer.push: Task id does not exist" << std::endl;
	precondition (false);
	return;
      }

    _call.called_ = i;
    calls_.push (_call);
  }

  INLINE_TIMER_CC
  void
  Timer::pop (const std::string& task_name)
  {
    if (!(calls_.empty ()) &&
	tasks_[(calls_.top ().called_)].name_ == task_name)
      {
	std::cerr << "Timer.pop: Task on top has wrong name" << std::endl;
	precondition (false);
	return;
      }
    pop ();
  }

  INLINE_TIMER_CC
  void
  Timer::pop (const unsigned int i)
  {
    if (!(calls_.empty ()) &&
	calls_.top ().called_ == i)
      {
	std::cerr << "Timer.pop: Task on top has wrong id" << std::endl;
	precondition (false);
	return;
      }
    pop();
  }

  INLINE_TIMER_CC
  void
  Timer::pop ()
  {
    timer::Task* task = 0;

    if (!calls_.empty ())
      {
	timer::StackedCall call = (calls_.top ());
	calls_.pop ();

	call.total_.set_to_lap ();
	if (!calls_.empty ())
	  {
	    calls_.top ().children_ += call.total_;
	    task = & (tasks_[calls_.top ().called_]);
	  }
	else
	  task = & (tasks_[0]);

	(task->call (call.called_)).add (call);
      }
    else
      {
	std::cout << "Timer.pop: Call stack empty" << std::endl;
	precondition (false);
      }
  }

  /*--------------.
  | Timer.        |
  | Arithmetics.  |
  `--------------*/

  INLINE_TIMER_CC
  Timer
  Timer::operator+ (const Timer& rhs)
  {
    Timer res = *this;

    res += rhs;

    return (res);
  }

  INLINE_TIMER_CC
  Timer&
  Timer::operator+= (const Timer& rhs)
  {
    timer::output_graph::vertex_iterator   vx;
    timer::output_graph::vertex_descriptor vd;
    timer::output_graph::edge_iterator     ei;
    timer::output_graph::edge_descriptor   ed;

    timer::vertex_range vxrange;
    timer::edge_range   erange;

    timer::output_graph::vertex_iterator   vx2;
    timer::output_graph::vertex_descriptor vd2;
    timer::output_graph::edge_iterator     ei2;
    timer::output_graph::edge_descriptor   ed2;

    timer::vertex_range vxrange2;
    timer::edge_range   erange2;

    if (this->cleared_)
      {
	*this = rhs;
	return *this;
      }

    clock_t	total_cpu = graph_[0].total.cpu + rhs.graph_[0].total.cpu;

    for (vxrange = vertices (graph_), vx = vxrange.first,
	   vxrange2 = vertices (rhs.graph_), vx2 = vxrange2.first;
	 vx != vxrange.second && vx2 != vxrange2.second; ++vx, ++vx2)
      {
	vd  = *vx;
	vd2 = *vx2;

	graph_[vd].total.wall   += rhs.graph_[vd2].total.wall;
	graph_[vd].total.user   += rhs.graph_[vd2].total.user;
	graph_[vd].total.system += rhs.graph_[vd2].total.system;
	graph_[vd].total.cpu    += rhs.graph_[vd2].total.cpu;

	graph_[vd].self.wall    += rhs.graph_[vd2].self.wall;
	graph_[vd].self.user    += rhs.graph_[vd2].self.user;
	graph_[vd].self.system  += rhs.graph_[vd2].self.system;
	graph_[vd].self.cpu     += rhs.graph_[vd2].self.cpu;

	graph_[vd].compute_average (total_cpu);
      }

    for (erange = edges (graph_), ei = erange.first,
	   erange2 =  edges (rhs.graph_), ei2 = erange2.first;
	 ei != erange.second && ei2 != erange2.second; ++ei, ++ei2)
      {
	ed  = *ei;
	ed2 = *ei2;

	graph_[ed].total.wall   += rhs.graph_[ed2].total.wall;
	graph_[ed].total.user   += rhs.graph_[ed2].total.user;
	graph_[ed].total.system += rhs.graph_[ed2].total.system;
	graph_[ed].total.cpu    += rhs.graph_[ed2].total.cpu;

	graph_[ed].self.wall    += rhs.graph_[ed2].self.wall;
	graph_[ed].self.user    += rhs.graph_[ed2].self.user;
	graph_[ed].self.system  += rhs.graph_[ed2].self.system;
	graph_[ed].self.cpu     += rhs.graph_[ed2].self.cpu;

	graph_[ed].compute_average (total_cpu);
      }
    
    return *this;
  }

  INLINE_TIMER_CC
  Timer
  Timer::operator/ (unsigned rhs) const
  {
    Timer res;

    res = *this;
    res /= rhs;

    return res;
  }

  INLINE_TIMER_CC
  Timer&
  Timer::operator/= (unsigned rhs)
  {
    timer::output_graph::vertex_iterator   vx;
    timer::output_graph::vertex_descriptor vd;
    timer::output_graph::edge_iterator     ei;
    timer::output_graph::edge_descriptor   ed;

    timer::vertex_range vxrange;
    timer::edge_range   erange;

    clock_t	 total_cpu = graph_[0].total.cpu / rhs;

    for (vxrange = vertices (graph_), vx = vxrange.first;
	 vx != vxrange.second; ++vx)
      {
	vd = *vx;

	graph_[vd].total.wall   /= rhs;
	graph_[vd].total.user   /= rhs;
	graph_[vd].total.system /= rhs;
	graph_[vd].total.cpu    /= rhs;

	graph_[vd].self.wall    /= rhs;
	graph_[vd].self.user    /= rhs;
	graph_[vd].self.system  /= rhs;
	graph_[vd].self.cpu     /= rhs;

	graph_[vd].compute_average (total_cpu);
      }

    for (erange = edges (graph_), ei = erange.first;
	 ei != erange.second; ++ei)
      {
	ed = *ei;

	graph_[ed].total.wall   /= rhs;
	graph_[ed].total.user   /= rhs;
	graph_[ed].total.system /= rhs;
	graph_[ed].total.cpu    /= rhs;

	graph_[ed].self.wall    /= rhs;
	graph_[ed].self.user    /= rhs;
	graph_[ed].self.system  /= rhs;
	graph_[ed].self.cpu     /= rhs;

	graph_[ed].compute_average (total_cpu);
      }
    
    return *this;
  }

  /*----------------------.
  | Timer.                |
  | Result computation.   |
  `----------------------*/

  INLINE_TIMER_CC
  void
  Timer::compute_output_graph ()
  {
    timer::Task*	task = 0;
    timer::Call*	call = 0;

    timer::output_graph::vertex_iterator   vx;
    timer::output_graph::vertex_iterator   vx2;
    timer::output_graph::vertex_descriptor vd;
    timer::output_graph::out_edge_iterator oe;
    timer::output_graph::edge_descriptor   ed;

    timer::vertex_range   vxrange;
    timer::out_edge_range oerange;

    for (vxrange = vertices (graph_), vx = vxrange.first;
	 vx != vxrange.second; ++vx)
      {
	task = & (tasks_[graph_[*vx].id]);
	for (oerange = out_edges (*vx, graph_), oe = oerange.first;
	     oe != oerange.second; ++oe)
	  {
	    ed   = *oe;
	    call = & (task->call (graph_[ed].to));

	    graph_[ed].add_times (call->total_, call->self_,
				  time_, call->count_);

	    vx2 = (target (ed, graph_));
	    vd  = *vx2;

	    if (comp_id_[graph_[ed].to] == comp_id_[graph_[ed].from])
	      {
		graph_[vd].add_int_time (call->self_, call->count_);

		if (graph_[ed].to == graph_[ed].from)
		  {
		    graph_[vd].recursive_count += call->count_;
		    graph_[vd].int_count -= call->count_;
		  }
	      }
	    else
	      graph_[vd].add_times (call->total_, call->self_,
				    time_, call->count_);
	  }
      }

    graph_[0].add_times (time_, time_, time_, 1);

    for (vxrange = vertices (graph_), vx = vxrange.first;
	 vx != vxrange.second; ++vx)
      {
	graph_[*vx].compute_average (time_.sys_ + time_.user_);
      }

  }


  INLINE_TIMER_CC
  void
  Timer::compute_connected_components ()
  {
    comp_.resize (comp_count_);

    for (unsigned int i = 0; i < num_vertices (graph_); ++i)
      {
	timer::output_graph::in_edge_iterator  ie;
	timer::output_graph::out_edge_iterator oe;
	timer::in_edge_range                   ierange;
	timer::out_edge_range                  oerange;

	comp_[comp_id_[i]].add_member (graph_[boost::vertex (i, graph_)]);

	for (ierange = in_edges (boost::vertex (i, graph_), graph_),
	       ie = ierange.first;
	     ie != ierange.second; ++ie)
	  {
	    if (comp_id_[graph_[*ie].from] == comp_id_[i])
	      comp_[comp_id_[i]].add_call_internal (graph_[*ie]);
	    else
	      comp_[comp_id_[i]].add_call_inc (graph_[*ie]);
	  }

	for (oerange = out_edges(boost::vertex (i, graph_), graph_),
	       oe = oerange.first;
	     oe != oerange.second; ++oe)
	  {
	    if (comp_id_[graph_[*oe].to] != comp_id_[i])
	      comp_[comp_id_[i]].add_call_out (graph_[*oe]);
	  }

	comp_[comp_id_[i]].compute_average (graph_[0].total.cpu);
      }

    for (unsigned int i = 0; i < comp_count_; ++i)
      {
	comp_[i].id = i;
      }
  }


  INLINE_TIMER_CC
  void
  Timer::build_output_graph ()
  {
    timer::Task*	task = 0;
    timer::Call*	call = 0;

    timer::output_graph::vertex_iterator	vx;
    timer::output_graph::edge_descriptor	ed;

    timer::vertex_range vxrange;

    for (timer::task_vector::iterator task_ = tasks_.begin();
	 task_ != tasks_.end (); ++task_)
      {
	task = & (*task_);
	vx   = add_vertex (graph_);

	graph_[*vx].name = task->name_;
	graph_[*vx].id   = task->id_;
      }

    for (timer::task_vector::iterator task_ = tasks_.begin ();
	 task_ != tasks_.end (); ++task_)
      {
	task = & (*task_);
	for (timer::call_map::iterator call_ = task->calls_.begin ();
	     call_ != task->calls_.end (); ++call_)
	  {
	    call = & (call_->second);
	    ed   = (add_edge (vertex ((*task_).id_, graph_),
			      vertex (call_->first, graph_),
			      graph_)).first;

	    graph_[ed].to   = call_->first;
	    graph_[ed].from = (*task_).id_;
	  }
      }

  }

  /*-----------.
  | Timer.     |
  | Printing.  |
  `-----------*/

  INLINE_TIMER_CC
  void
  Timer::print_output_graph (std::ostream&         o,
			     timer::verbose_degree vd) const
  {
    timer::output_graph::vertex_iterator   vx;
    timer::output_graph::in_edge_iterator  ie;
    timer::output_graph::out_edge_iterator oe;

    timer::vertex_range   vxrange;
    timer::in_edge_range  ierange;
    timer::out_edge_range oerange;

    std::list<timer::GraphTask> gtlist;

    o << "[Task list:]\n\n"
      << "Charge  id:        <name>          total"
      "    self    calls   self avg. total avg.\n";

    for (vxrange =  vertices (graph_), vx = vxrange.first;
	 vx != vxrange.second; ++vx)
      {
	gtlist.push_front (graph_[*vx]);
      }

    gtlist.sort ();

    for (std::list<timer::GraphTask>::iterator li = gtlist.begin ();
	 li != gtlist.end (); ++li)
      {
	o << " " << std::setw (4) << std::setprecision (3)
	  << li->self.charge << "% "
	  << std::setw(3) <<  li->id << ":"
	  << std::setw(18) << li->name << "   ";

	if (comp_[comp_id_[li->id]].member_count > 1)
	  o << " (C:" << std::setw (3) << comp_id_[li->id] << ")";
	else
	  o << std::setprecision (3) << std::setw (7)
	    << double (li->total.cpu) / ticks_per_sec_ << "s";

	o << std::setprecision (3) << std::setw (7)
	  << double (li->self.cpu) / ticks_per_sec_ << "s";

	o << std::setprecision (3) << std::setw (9)
	  << li->count + li->recursive_count + li->int_count << " ";

	o << std::setprecision (5) << std::setw (9)
	  << double (int (li->self.average * 1000)) / ticks_per_sec_ << "ms";

	if (comp_[comp_id_[li->id]].member_count > 1)
	  o << "    (C:" << std::setw (3) << comp_id_[li->id] << ")";
	else
	  o << std::setprecision (5) << std::setw (9)
	    << double (int (li->total.average * 1000)) / ticks_per_sec_
	    << "ms";

	o << "\n";

      }

    if (vd < timer::VERBOSE_NORMAL)
      return;

    o << "__________________________________"
         "______________________________________________\n\n";

    o << "[Call graph:]\n\n\n";

    o << "Cycles:\n"
      << "<cycle>  charge    total     self  calls:e/i    int avg."
         "   self avg.  total avg.\n";


    for (unsigned int c = 0; c < comp_count_; ++c)
      {
	if (comp_[c].member_count > 1)
	  {
	    o << ".................................."
                 "..............................................\n";

	    o << "(C:" << std::setw (3) << comp_[c].id << ")"
	      << "  " << std::setw (5) << std::setprecision (3)
	      << comp_[c].self.charge << "%"
	      << std::setprecision (3) << std::setw (8)
	      << double (comp_[c].total.cpu) / ticks_per_sec_ << "s";

	    o << std::setprecision (3) << std::setw (8)
	      << double (comp_[c].self.cpu) / ticks_per_sec_ << "s";

	    o << std::setw (5) << comp_[c].calls << "/";
	    o << std::setw (5) << comp_[c].int_calls << "";

	    o << std::setprecision (4) << std::setw (10)
	      << double (int (comp_[c].int_average * 1000))
	      / ticks_per_sec_ << "ms";

	    o << std::setprecision (4) << std::setw (10)
	      << double (int (comp_[c].self.average * 1000))
	      / ticks_per_sec_ << "ms";

	    o << std::setprecision (4) << std::setw (10)
	      << double (int (comp_[c].total.average * 1000))
	      / ticks_per_sec_ << "ms";

	    o << std::endl << std::endl;

	    for (std::list<int>::const_iterator li = comp_[c].members.begin ();
		 li != comp_[c].members.end (); ++li)
	      {
		const timer::GraphTask& task = (graph_[vertex (*li, graph_)]);
		o << std::setw (6) << task.id << ":  "
		  << std::setw (5) << std::setprecision (3)
		  << task.self.charge * 100 / comp_[c].self.charge << "%";

		o << "         ";

		o << std::setprecision (3) << std::setw (8)
		  << double (task.self.cpu) / ticks_per_sec_ << "s";

		o << std::setw (5) << task.count << "/";
		o << std::setw (5)
		  << task.int_count + task.recursive_count << "";

		o << std::setprecision (4) << std::setw (10)
		  << double (int (task.self.average * 1000))
		  / ticks_per_sec_ << "ms";

		o << std::setw (24) << task.name;

		o << std::endl;
	      }
	  }
      }

    o << "__________________________________"
         "______________________________________________\n\n\n";
 
    o << "Tasks:\n"
      << "D  id:        <name>   charge    total    self calls(rec.)"
         "  self avg. total avg.\n";

    for (vxrange =  vertices (graph_), vx = vxrange.first;
	 vx != vxrange.second; ++vx)
      {
	o << ".................................."
             "..............................................\n";

	o << "[" << graph_[*vx].id << "] " << graph_[*vx].name
	  << std::endl << std::endl;
	
	for (ierange = in_edges (*vx, graph_), ie = ierange.first;
	     ie != ierange.second; ++ie)
	  {
	    const timer::GraphTask& task = (graph_[source (*ie, graph_)]);
	    const timer::GraphCall& call = graph_[*ie];

	    o << "<-" << std::setw (3)
	      << task.id << ":";

	    o << std::setw (16) << task.name;

	    o << std::setprecision (3) << std::setw (6)
	      << call.self.charge * 100 / graph_[*vx].self.charge << "% ";

	    o << "        ";

	    o << std::setprecision (3) << std::setw (7)
	      << double (call.self.cpu) / ticks_per_sec_ << "s";

	    o << std::setw (6)
	      << call.count << "      ";

	    o << std::setprecision (5) << std::setw (9)
	      << double (int (call.self.average * 1000))
	      / ticks_per_sec_ << "ms";

	    o << std::endl;
	  }
	o << std::endl;

	const timer::GraphTask& task = (graph_[*vx]);

	o << "  " << std::setw (3)
	  << task.id << ":";

	o << std::setw (16) << task.name;

	o << std::setprecision (3) << std::setw (6)
	  << task.self.charge << "% ";

	if (comp_[comp_id_[task.id]].member_count > 1)
	  o << " (C:" << std::setw (3)
	    << comp_id_[task.id] << ")";
	else
	  o << std::setprecision (3) << std::setw (7)
	    << double (task.total.cpu) / ticks_per_sec_ << "s";

	o << std::setprecision (3) << std::setw (7)
	  << double (task.self.cpu) / ticks_per_sec_ << "s";

	o << std::setw (6)
	  << task.count + task.int_count << "("
	  << std::setw (4)
	  << task.recursive_count << ")";

	o << std::setprecision (5) << std::setw (9)
	  << double (int (task.self.average * 1000))
	  / ticks_per_sec_ << "ms";

	if (comp_[comp_id_[task.id]].member_count > 1)
	  o << "    (C:" << std::setw (3)
	    << comp_id_[task.id] << ")";
	else
	  o << std::setprecision (5) << std::setw (9)
	    << double (int (task.total.average * 1000))
	    / ticks_per_sec_
	    << "ms";

	o << std::endl << std::endl;


	for (oerange = out_edges (*vx, graph_), oe = oerange.first;
	     oe != oerange.second; ++oe)
	  {
	    const timer::GraphTask& task = (graph_[target (*oe, graph_)]);
	    const timer::GraphCall& call = graph_[*oe];

	    o << "->" << std::setw (3)
	      << task.id << ":";

	    o << std::setw (16) << task.name;

	    o << std::setprecision (3) << std::setw (6)
	      << call.self.charge * 100 / task.self.charge << "% ";

	    o << "        ";

	    o << std::setprecision (3) << std::setw (7)
	      << double (call.self.cpu) / ticks_per_sec_ << "s";

	    o << std::setw (6)
	      << call.count << "      ";

	    o << std::setprecision (5) << std::setw (9)
	      << double (int (call.self.average * 1000))
	      / ticks_per_sec_ << "ms";

	    o << std::endl;
	  }
      }
    if (vd < timer::VERBOSE_MAXIMAL)
      return;

    o << "__________________________________"
         "______________________________________________\n\n";

    o << "[Detailed tasks:]\n\n";

    for (vxrange =  vertices (graph_), vx = vxrange.first;
	 vx != vxrange.second; ++vx)
      {
	o << ".................................."
             "..............................................\n";

	const timer::GraphTask& task = (graph_[*vx]);

	o << "[" << task.id << "] " << task.name
	  << "\n\n";

	o << "Calls from exterior:    " << std::setw (10) << task.count
	  << "\n";
	o << "Calls from within cycle:" << std::setw (10) << task.int_count
	  << "\n";
	o << "Recursive calls:        " << std::setw (10)
	  << task.recursive_count << "\n";

	o << "\n";

	o << "Clock ticks per second: " << std::setw (10) << ticks_per_sec_
	  << "\n\n";

	o << "Self wall time:         " << std::setw (10) << task.self.wall
	  << "\n";
	o << "Self cpu time:          " << std::setw (10) << task.self.cpu
	  << "\n";
	o << "Self user time:         " << std::setw (10) << task.self.user
	  << "\n";
	o << "Self system time:       " << std::setw (10) << task.self.system
	  << "\n";
	o << "Self average cpu time:  " << std::setw (10)
	  << task.self.average << "\n";
	o << "Self charge:            " << std::setw (10)
	  << task.self.charge << "%\n";

	o << "\n";

	o << "Total wall time:        " << std::setw (10) << task.total.wall
	  << "\n";
	o << "Total cpu time:         " << std::setw (10) << task.total.cpu
	  << "\n";
	o << "Total user time:        " << std::setw (10) << task.total.user
	  << "\n";
	o << "Total system timer:     " << std::setw (10) << task.total.system
	  << "\n";
	o << "Total average cpu time: " << std::setw (10)
	  << task.total.average << "\n";
	o << "Total charge:           " << std::setw (10)
	  << task.total.charge << "%\n";
      }
  }
} // namespace misc

NAMESPACE_VCSN_END

# undef INLINE_TIMER_CC


#endif //!VCSN_MISC_TIMER_CC
