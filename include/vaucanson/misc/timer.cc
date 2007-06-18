// timer.hh: this file is part of the Vaucanson project.
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

# include <sys/times.h>
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
  {
    ticks_per_sec_ = sysconf(_SC_CLK_TCK);

    comp_count_    = 0;
    task_count_    = 1;

    is_running_    = false;
    cleared_       = true;
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
    ticks_per_sec_ = (rhs.ticks_per_sec_);
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

    return (*this);
  }

  INLINE_TIMER_CC
  Timer::~Timer ()
  {
  }

  INLINE_TIMER_CC
  void
  Timer::clear ()
  {
    while (!calls_.empty ())
      calls_.pop();

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

    tasks_.resize(1);

    names_["_program_"] = 0;
    tasks_[0].name_     = "_Program_";
    tasks_[0].id_       = 0;

    time_.set_to_now();
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

	time_.set_to_lap();

	task_count_ = tasks_.size();

	build_output_graph();
	build_connected_components();

	compute_output_graph();
	compute_connected_components();

	tasks_.clear();
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

    StackedCall _call (0);

    task_names_map::iterator iter;

    iter = names_.find(name);
    if (iter == names_.end())
      {
	i = tasks_.size();
	tasks_.resize(i + 1);

	names_[name]    = i;
	tasks_[i].name_ = name;
	tasks_[i].id_   = i;
      }
    else
      {
	i = iter->second;
      }

    _call.called_ = i;
    calls_.push(_call);
  }

  INLINE_TIMER_CC
  unsigned int
  Timer::task(const std::string& name)
  {
    task_names_map::iterator iter;

    iter = names_.find(name);
    if (iter == names_.end())
      {
	unsigned int i;

	i = tasks_.size();
	tasks_.resize(i + 1);

	names_[name]    = i;
	tasks_[i].name_ = name;
	tasks_[i].id_   = i;
	return (i);
      }
    else
      {
	return (iter->second);
      }
  }

  INLINE_TIMER_CC
  void
  Timer::push (const unsigned int i)
  {
    StackedCall _call (0);

    if (i >= tasks_.size())
      {
	std::cerr << "Timer.push: Task id does not exist" << std::endl;
	precondition (false);
	return;
      }

    _call.called_ = i;
    calls_.push(_call);
  }

  INLINE_TIMER_CC
  void
  Timer::pop (const std::string& task_name)
  {
    if (!(calls_.empty ()) &&
	tasks_[(calls_.top().called_)].name_ == task_name)
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
	calls_.top().called_ == i)
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
    Task* task;

    if (!calls_.empty())
      {
	StackedCall call = (calls_.top());
	calls_.pop();

	call.total_.set_to_lap();
	if (!calls_.empty())
	  {
	    calls_.top().children_ += call.total_;
	    task = &(tasks_[calls_.top().called_]);
	  }
	else
	  task = &(tasks_[0]);

	(task->call(call.called_)).add (call);
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
  bool
  Timer::operator< (const Timer& rhs) const
  {
    precondition (!(is_running_ || rhs.is_running_));

    return (graph_[0].total_cpu < rhs.graph_[0].total_cpu);
  }

  INLINE_TIMER_CC
  Timer&
  Timer::operator+= (const Timer& rhs)
  {
    output_graph::vertex_iterator   vx;
    output_graph::vertex_descriptor vd;
    output_graph::edge_iterator     ei;
    output_graph::edge_descriptor   ed;

    vertex_range vxrange;
    edge_range   erange;

    output_graph::vertex_iterator   vx_;
    output_graph::vertex_descriptor vd_;
    output_graph::edge_iterator     ei_;
    output_graph::edge_descriptor   ed_;

    vertex_range vxrange_;
    edge_range   erange_;

    if (this->cleared_)
      {
	*this = rhs;
	return (*this);
      }

    clock_t	total_cpu;

    total_cpu = graph_[0].total_cpu + rhs.graph_[0].total_cpu;

    for (vxrange = vertices(graph_), vx = vxrange.first,
	   vxrange_ = vertices(rhs.graph_), vx_ = vxrange_.first;
	 vx != vxrange.second && vx_ != vxrange_.second; ++vx, ++vx_)
      {
	vd  = *vx;
	vd_ = *vx_;

	graph_[vd].total_wall   += rhs.graph_[vd_].total_wall;
	graph_[vd].total_user   += rhs.graph_[vd_].total_user;
	graph_[vd].total_system += rhs.graph_[vd_].total_system;
	graph_[vd].total_cpu    += rhs.graph_[vd_].total_cpu;

	graph_[vd].self_wall    += rhs.graph_[vd_].self_wall;
	graph_[vd].self_user    += rhs.graph_[vd_].self_user;
	graph_[vd].self_system  += rhs.graph_[vd_].self_system;
	graph_[vd].self_cpu     += rhs.graph_[vd_].self_cpu;

	graph_[vd].compute_average(total_cpu);
      }

    for (erange = edges(graph_), ei = erange.first,
	   erange_ =  edges(rhs.graph_), ei_ = erange_.first;
	 ei != erange.second && ei_ != erange_.second; ++ei, ++ei_)
      {
	ed  = *ei;
	ed_ = *ei_;

	graph_[ed].total_wall   += rhs.graph_[ed_].total_wall;
	graph_[ed].total_user   += rhs.graph_[ed_].total_user;
	graph_[ed].total_system += rhs.graph_[ed_].total_system;
	graph_[ed].total_cpu    += rhs.graph_[ed_].total_cpu;

	graph_[ed].self_wall    += rhs.graph_[ed_].self_wall;
	graph_[ed].self_user    += rhs.graph_[ed_].self_user;
	graph_[ed].self_system  += rhs.graph_[ed_].self_system;
	graph_[ed].self_cpu     += rhs.graph_[ed_].self_cpu;

	graph_[ed].compute_average(total_cpu);
      }
    
    return (*this);
  }

  INLINE_TIMER_CC
  Timer
  Timer::operator/ (unsigned rhs) const
  {
    Timer res;

    res = *this;
    res /= rhs;

    return (res);
  }

  INLINE_TIMER_CC
  Timer&
  Timer::operator/= (unsigned rhs)
  {
    output_graph::vertex_iterator   vx;
    output_graph::vertex_descriptor vd;
    output_graph::edge_iterator     ei;
    output_graph::edge_descriptor   ed;

    vertex_range vxrange;
    edge_range   erange;

    clock_t	 total_cpu;

    total_cpu = graph_[0].total_cpu / rhs;

    for (vxrange =  vertices(graph_), vx = vxrange.first;
	 vx != vxrange.second; ++vx)
      {
	vd = *vx;

	graph_[vd].total_wall   /= rhs;
	graph_[vd].total_user   /= rhs;
	graph_[vd].total_system /= rhs;
	graph_[vd].total_cpu    /= rhs;

	graph_[vd].self_wall    /= rhs;
	graph_[vd].self_user    /= rhs;
	graph_[vd].self_system  /= rhs;
	graph_[vd].self_cpu     /= rhs;

	graph_[vd].compute_average(total_cpu);
      }

    for (erange = edges(graph_), ei = erange.first;
	 ei != erange.second; ++ei)
      {
	ed = *ei;

	graph_[ed].total_wall   /= rhs;
	graph_[ed].total_user   /= rhs;
	graph_[ed].total_system /= rhs;
	graph_[ed].total_cpu    /= rhs;

	graph_[ed].self_wall    /= rhs;
	graph_[ed].self_user    /= rhs;
	graph_[ed].self_system  /= rhs;
	graph_[ed].self_cpu     /= rhs;

	graph_[ed].compute_average(total_cpu);
      }
    
    return (*this);
  }

  /*----------------------.
  | Timer.                |
  | Result computation.   |
  `----------------------*/

  INLINE_TIMER_CC
  void
  Timer::build_connected_components()
  {
    comp_id_.resize(num_vertices(graph_));
    comp_count_ = strong_components(graph_, &comp_id_[0]);
  }


  INLINE_TIMER_CC
  void
  Timer::compute_output_graph ()
  {
    Task*	task;
    Call*	call;

    output_graph::vertex_iterator   vx;
    output_graph::vertex_iterator   vx2;
    output_graph::vertex_descriptor vd;
    output_graph::out_edge_iterator oe;
    output_graph::edge_descriptor   ed;

    vertex_range   vxrange;
    out_edge_range oerange;

    for (vxrange =  vertices(graph_), vx = vxrange.first;
	 vx != vxrange.second; ++vx)
      {
	task = &(tasks_[graph_[*vx].id]);
	for (oerange = out_edges(*vx, graph_), oe = oerange.first;
	     oe != oerange.second; ++oe)
	  {
	    ed   = *oe;
	    call = &(task->call(graph_[ed].to));

	    graph_[ed].add_times(call->total_, call->self_,
				 time_, call->count_);

	    vx2 = (target(ed, graph_));
	    vd  = *vx2;

	    if (comp_id_[graph_[ed].to] == comp_id_[graph_[ed].from])
	      {
		graph_[vd].add_int_time(call->self_, call->count_);

		if (graph_[ed].to == graph_[ed].from)
		  {
		    graph_[vd].recursive_count += call->count_;
		    graph_[vd].int_count -= call->count_;
		  }
	      }
	    else
	      graph_[vd].add_times(call->total_, call->self_,
				    time_, call->count_);
	  }
      }

    graph_[0].add_times(time_, time_, time_, 1);

    for (vxrange =  vertices(graph_), vx = vxrange.first;
	 vx != vxrange.second; ++vx)
      {
	graph_[*vx].compute_average(time_.sys_ + time_.user_);
      }

  }


  INLINE_TIMER_CC
  void
  Timer::compute_connected_components()
  {
    comp_.resize(comp_count_);

    for (unsigned int i = 0; i < num_vertices(graph_); ++i)
      {
	output_graph::in_edge_iterator  ie;
	output_graph::out_edge_iterator oe;
	in_edge_range                   ierange;
	out_edge_range                  oerange;


	comp_[comp_id_[i]].add_member(graph_[boost::vertex(i, graph_)]);

	for (ierange = in_edges(boost::vertex(i, graph_), graph_),
	       ie = ierange.first;
	     ie != ierange.second; ++ie)
	  {
	    if (comp_id_[graph_[*ie].from] == comp_id_[i])
	      comp_[comp_id_[i]].add_call_internal(graph_[*ie]);
	    else
	      comp_[comp_id_[i]].add_call_inc(graph_[*ie]);
	  }

	for (oerange = out_edges(boost::vertex(i, graph_), graph_),
	       oe = oerange.first;
	     oe != oerange.second; ++oe)
	  {
	    if (comp_id_[graph_[*oe].to] != comp_id_[i])
	      comp_[comp_id_[i]].add_call_out(graph_[*oe]);
	  }

	comp_[comp_id_[i]].compute_average(graph_[0].total_cpu);
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
    Task*	task;
    Call*	call;

    output_graph::vertex_iterator	vx;
    output_graph::edge_descriptor	ed;

    vertex_range vxrange;

    for (task_vector::iterator task_ = tasks_.begin();
	 task_ != tasks_.end(); ++task_)
      {
	task = &(*task_);
	vx   = add_vertex(graph_);

	graph_[*vx].name = task->name_;
	graph_[*vx].id   = task->id_;
      }

    for (task_vector::iterator task_ = tasks_.begin();
	 task_ != tasks_.end(); ++task_)
      {
	task = &(*task_);
	for (call_map::iterator call_ = task->calls_.begin();
	     call_ != task->calls_.end(); ++call_)
	  {
	    call = &(call_->second);
	    ed   = (add_edge(vertex((*task_).id_, graph_),
			     vertex(call_->first, graph_),
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
  std::ostream&
  Timer::print (std::ostream&  o,
		verbose_degree vd) const
  {
    print_output_graph(o, vd);

    return (o);
  }

  INLINE_TIMER_CC
  std::ostream&
  Timer::export_dot (std::ostream&  o,
		     verbose_degree vd,
		     double         ccr) const
  {
    write_graphviz(o, graph_,
		   VertexWriter(*this, vd, ccr),
		   EdgeWriter(*this, vd, ccr),
		   GraphWriter(*this, vd, ccr));
    return (o);
  }


  INLINE_TIMER_CC
  void
  Timer::print_output_graph(std::ostream&  o,
			    verbose_degree vd) const
  {
    output_graph::vertex_iterator   vx;
    output_graph::in_edge_iterator  ie;
    output_graph::out_edge_iterator oe;

    vertex_range   vxrange;
    in_edge_range  ierange;
    out_edge_range oerange;

    std::list<GraphTask> gtlist;

    o << "[Task list:]" << std::endl << std::endl
      << "Charge  id:        <name>          total\
    self    calls   self avg. total avg."
      << std::endl;
    for (vxrange =  vertices(graph_), vx = vxrange.first;
	 vx != vxrange.second; ++vx)
      {
	gtlist.push_front(graph_[*vx]);
      }

    gtlist.sort();

    for (std::list<GraphTask>::iterator li = gtlist.begin();
	 li != gtlist.end(); ++li)
      {
	o << " " << std::setw(4) << std::setprecision(3)
	  << li->self_charge << "% "
	  << std::setw(3) <<  li->id << ":"
	  << std::setw(18) << li->name << "   ";

	if (comp_[comp_id_[li->id]].member_count > 1)
	  o << " (C:" << std::setw(3) << comp_id_[li->id] << ")";
	else
	  o << std::setprecision(3) << std::setw(7)
	    << double(li->total_cpu) / ticks_per_sec_ << "s";

	o << std::setprecision(3) << std::setw(7)
	  << double(li->self_cpu) / ticks_per_sec_ << "s";

	o << std::setprecision(3) << std::setw(9)
	  << li->count + li->recursive_count + li->int_count << " ";

	o << std::setprecision(5) << std::setw(9)
	  << double(int(li->self_average * 1000)) / ticks_per_sec_ << "ms";

	if (comp_[comp_id_[li->id]].member_count > 1)
	  o << "    (C:" << std::setw(3) << comp_id_[li->id] << ")";
	else
	  o << std::setprecision(5) << std::setw(9)
	    << double(int(li->total_average * 1000)) / ticks_per_sec_
	    << "ms";

	o << std::endl;

      }

    if (vd < VERBOSE_NORMAL)
      return;

    o << "__________________________________\
______________________________________________" << std::endl << std::endl;

    o << "[Call graph:]" << std::endl << std::endl << std::endl;

    o << "Cycles:" << std::endl
      << "<cycle>  charge    total     self  calls:e/i    int avg.\
   self avg.  total avg." << std::endl;


    for (unsigned int c = 0; c < comp_count_; ++c)
      {
	if (comp_[c].member_count > 1)
	  {
	    o << "..................................\
.............................................." << std::endl;

	    o << "(C:" << std::setw(3) << comp_[c].id << ")"
	      << "  " << std::setw(5) << std::setprecision(3)
	      << comp_[c].self_charge << "%"
	      << std::setprecision(3) << std::setw(8)
	      << double(comp_[c].total_cpu) / ticks_per_sec_ << "s";

	    o << std::setprecision(3) << std::setw(8)
	      << double(comp_[c].self_cpu) / ticks_per_sec_ << "s";

	    o << std::setw(5) << comp_[c].calls << "/";
	    o << std::setw(5) << comp_[c].int_calls << "";

	    o << std::setprecision(4) << std::setw(10)
	      << double(int(comp_[c].int_average * 1000))
	      / ticks_per_sec_ << "ms";

	    o << std::setprecision(4) << std::setw(10)
	      << double(int(comp_[c].self_average * 1000))
	      / ticks_per_sec_ << "ms";

	    o << std::setprecision(4) << std::setw(10)
	      << double(int(comp_[c].total_average * 1000))
	      / ticks_per_sec_ << "ms";

	    o << std::endl << std::endl;

	    for (std::list<int>::const_iterator li = comp_[c].members.begin();
		 li != comp_[c].members.end(); ++li)
	      {
		const GraphTask& task = (graph_[vertex(*li, graph_)]);
		o << std::setw(6) << task.id << ":  "
		  << std::setw(5) << std::setprecision(3)
		  << task.self_charge * 100 / comp_[c].self_charge << "%";

		o << "         ";

		o << std::setprecision(3) << std::setw(8)
		  << double(task.self_cpu) / ticks_per_sec_ << "s";

		o << std::setw(5) << task.count << "/";
		o << std::setw(5)
		  << task.int_count + task.recursive_count << "";

		o << std::setprecision(4) << std::setw(10)
		  << double(int(task.self_average * 1000))
		  / ticks_per_sec_ << "ms";

		o << std::setw(24) << task.name;

		o << std::endl;
	      }
	  }
      }

    o << "__________________________________\
______________________________________________" << std::endl
      << std::endl << std::endl;
 
    o << "Tasks:" << std::endl
      << "D  id:        <name>   charge    total    self calls(rec.)\
  self avg. total avg." << std::endl;

    for (vxrange =  vertices(graph_), vx = vxrange.first;
	 vx != vxrange.second; ++vx)
      {
	o << "..................................\
.............................................." << std::endl;

	o << "[" << graph_[*vx].id << "] " << graph_[*vx].name
	  << std::endl << std::endl;
	
	for (ierange = in_edges(*vx, graph_), ie = ierange.first;
	     ie != ierange.second; ++ie)
	  {
	    const GraphTask& task = (graph_[source(*ie, graph_)]);
	    const GraphCall& call = graph_[*ie];

	    o << "<-" << std::setw(3)
	      << task.id << ":";

	    o << std::setw(16) << task.name;

	    o << std::setprecision(3) << std::setw(6)
	      << call.self_charge * 100 / graph_[*vx].self_charge << "% ";

	    o << "        ";

	    o << std::setprecision(3) << std::setw(7)
	      << double(call.self_cpu) / ticks_per_sec_ << "s";

	    o << std::setw(6)
	      << call.count << "      ";

	    o << std::setprecision(5) << std::setw(9)
	      << double(int(call.self_average * 1000))
	      / ticks_per_sec_ << "ms";

	    o << std::endl;
	  }
	o << std::endl;

	const GraphTask& task = (graph_[*vx]);

	o << "  " << std::setw(3)
	  << task.id << ":";

	o << std::setw(16) << task.name;

	o << std::setprecision(3) << std::setw(6)
	  << task.self_charge << "% ";

	if (comp_[comp_id_[task.id]].member_count > 1)
	  o << " (C:" << std::setw(3)
	    << comp_id_[task.id] << ")";
	else
	  o << std::setprecision(3) << std::setw(7)
	    << double(task.total_cpu) / ticks_per_sec_ << "s";

	o << std::setprecision(3) << std::setw(7)
	  << double(task.self_cpu) / ticks_per_sec_ << "s";

	o << std::setw(6)
	  << task.count + task.int_count << "("
	  << std::setw(4)
	  << task.recursive_count << ")";

	o << std::setprecision(5) << std::setw(9)
	  << double(int(task.self_average * 1000))
	  / ticks_per_sec_ << "ms";

	if (comp_[comp_id_[task.id]].member_count > 1)
	  o << "    (C:" << std::setw(3)
	    << comp_id_[task.id] << ")";
	else
	  o << std::setprecision(5) << std::setw(9)
	    << double(int(task.total_average * 1000))
	    / ticks_per_sec_
	    << "ms";

	o << std::endl << std::endl;


	for (oerange =  out_edges(*vx, graph_), oe = oerange.first;
	     oe != oerange.second; ++oe)
	  {
	    const GraphTask& task = (graph_[target(*oe, graph_)]);
	    const GraphCall& call = graph_[*oe];

	    o << "->" << std::setw(3)
	      << task.id << ":";

	    o << std::setw(16) << task.name;

	    o << std::setprecision(3) << std::setw(6)
	      << call.self_charge * 100 / task.self_charge << "% ";

	    o << "        ";

	    o << std::setprecision(3) << std::setw(7)
	      << double(call.self_cpu) / ticks_per_sec_ << "s";

	    o << std::setw(6)
	      << call.count << "      ";

	    o << std::setprecision(5) << std::setw(9)
	      << double(int(call.self_average * 1000))
	      / ticks_per_sec_ << "ms";

	    o << std::endl;
	  }
      }
    if (vd < VERBOSE_MAXIMAL)
      return;

    o << "__________________________________\
______________________________________________" << std::endl;

    o << std::endl;

    o << "[Detailed tasks:]" << std::endl << std::endl;

    for (vxrange =  vertices(graph_), vx = vxrange.first;
	 vx != vxrange.second; ++vx)
      {
	o << "..................................\
.............................................." << std::endl;

	const GraphTask& task = (graph_[*vx]);

	o << "[" << task.id << "] " << task.name
	  << std::endl << std::endl;

	o << "Calls from exterior:    " << std::setw(10) << task.count
	  << std::endl;
	o << "Calls from within cycle:" << std::setw(10) << task.int_count
	  << std::endl;
	o << "Recursive calls:        " << std::setw(10)
	  << task.recursive_count << std::endl;

	o << std::endl;

	o << "Clock ticks per second: " << std::setw(10) << ticks_per_sec_
	  << std::endl << std::endl;

	o << "Self wall time:         " << std::setw(10) << task.self_wall
	  << std::endl;
	o << "Self cpu time:          " << std::setw(10) << task.self_cpu
	  << std::endl;
	o << "Self user time:         " << std::setw(10) << task.self_user
	  << std::endl;
	o << "Self system time:       " << std::setw(10) << task.self_system
	  << std::endl;
	o << "Self average cpu time:  " << std::setw(10)
	  << task.self_average << std::endl;
	o << "Self charge:            " << std::setw(10)
	  << task.self_charge << "%" << std::endl;


	o << std::endl;

	o << "Total wall time:        " << std::setw(10) << task.total_wall
	  << std::endl;
	o << "Total cpu time:         " << std::setw(10) << task.total_cpu
	  << std::endl;
	o << "Total user time:        " << std::setw(10) << task.total_user
	  << std::endl;
	o << "Total system timer:     " << std::setw(10) << task.total_system
	  << std::endl;
	o << "Total average cpu time: " << std::setw(10)
	  << task.total_average << std::endl;
	o << "Total charge:           " << std::setw(10)
	  << task.total_charge << "%" << std::endl;

      }
  }

  /*-----------------------.
  | Timer:                 |
  | Graph export writers.  |
  `-----------------------*/

  /*------------------------.
  | Timer::GraphWriter.     |
  `------------------------*/

  INLINE_TIMER_CC
  Timer::GraphWriter::GraphWriter (const Timer&         timer,
				   const verbose_degree vd,
				   double               ccr)
    : g_              (timer.graph_),
      c_              (timer.comp_),
      c_id_           (timer.comp_id_),
      chrg_col_ratio_ (ccr),
      tps_	      (timer.ticks_per_sec_)
  {
    vd_ = vd;
  }

  INLINE_TIMER_CC
  void
  Timer::GraphWriter::operator()
    (std::ostream& out) const
  {
    out << std::endl
	<< "node[fontname=\"courier new\"];" << std::endl
	<< "node[fontsize=14];" << std::endl
	<< "node[shape=box];" << std::endl
	<< "node[style=filled];" << std::endl
	<< "edge[fontname=\"courier new\"];" << std::endl
	<< "edge[fontsize=10];" << std::endl
	<< "graph[fontname=\"courier new\"];" << std::endl;

    for (unsigned int i = 0; i < c_.size(); i++)
      {
	if (c_[i].member_count > 1)
	  {
	    out << "subgraph cluster" << i
		<< "{" << std::endl;
	    switch (vd_)
	      {
	      case VERBOSE_NONE:
		break;

	      case VERBOSE_MINIMAL:
		out << "caption" << i << "[label=\""
		    << "(C:" << std::setw(3) << i << ")"
		    << "\\lIncoming calls: " << std::setw(7) << c_[i].calls
		    << "\\lInternal calls: " << std::setw(7) << c_[i].int_calls
		    << "\\lOutgoing calls: " << std::setw(7) << c_[i].out_calls
		    << "\\lSelf time:      " << std::setw(7)
		    << double(c_[i].self_cpu) / tps_
		    << "s\\l\""
		    << ",style=solid,shape=box]";
		break;

	      case VERBOSE_NORMAL:
		out << "caption" << i << "[label=\""
		    << "(C:" << std::setw(3) << i << ")"
		    << "\\l"
		    << "\\lIncoming calls: " << std::setw(7) << c_[i].calls
		    << "\\lInternal calls: " << std::setw(7) << c_[i].int_calls
		    << "\\lOutgoing calls: " << std::setw(7) << c_[i].out_calls
		    << "\\l"
		    << "\\lSelf time:      " << std::setw(7)
		    << double(c_[i].self_cpu) / tps_
		    << "s"
		    << "\\lSelf average:   " << std::setprecision(5)
		    << std::setw(7)
		    << double(int(c_[i].self_average * 1000)) / tps_ << "ms"
		    << "\\lSelf charge:    " << std::setprecision(3)
		    << std::setw(7)
		    << c_[i].self_charge << "%"
		    << "\\l"
		    << "\\lTotal time:     " << std::setw(7)
		    << double(c_[i].total_cpu) / tps_
		    << "s"
		    << "\\lTotal charge:   " << std::setprecision(3)
		    << std::setw(7)
		    << c_[i].total_charge << "%\\l\""
		    << ",style=solid,shape=box]";
		break;

	      default:
		out << "caption" << i << "[label=\""
		    << "(C:" << std::setw(3) << i << ")"
		    << "\\l"
		    << "\\lIncoming calls:  " << std::setw(7)
		    << c_[i].calls
		    << "\\lInternal calls:  " << std::setw(7)
		    << c_[i].int_calls
		    << "\\lOutgoing calls:  " << std::setw(7)
		    << c_[i].out_calls
		    << "\\l"
		    << "\\lSelf time:       " << std::setw(7)
		    << double(c_[i].self_cpu) / tps_
		    << "s"
		    << "\\lSelf user time:  " << std::setw(7)
		    << c_[i].self_user << "ct"
		    << "\\lSelf syst. time: "<< std::setw(7)
		    << c_[i].self_system << "ct"
		    << "\\lSelf average:    " << std::setprecision(5)
		    << std::setw(7)
		    << double(int(c_[i].self_average * 1000)) / tps_ << "ms"
		    << "\\lSelf charge:     " << std::setprecision(3)
		    << std::setw(7)
		    << c_[i].self_charge << "%"
		    << "\\l"
		    << "\\lTotal time:      " << std::setw(7)
		    << double(c_[i].total_cpu) / tps_
		    << "s"
		    << "\\lTotal average:   " << std::setprecision(5)
		    << std::setw(7)
		    << double(int(c_[i].total_average * 1000)) / tps_ << "ms"
		    << "\\lTotal charge:    " << std::setprecision(3)
		    << std::setw(7)
		    << c_[i].total_charge << "%"
		    << "\\l"
		    << "\\lInternal average:" << std::setprecision(5)
		    << std::setw(7)
		    << double(int(c_[i].int_average * 1000)) / tps_
		    << "ms\\l\""
		    << ",style=solid,shape=box]";
	      }
	    out << std::endl
		<< "style=filled" << std::endl
		<< "fillcolor=\""
		<< std::max
	      (0.35 - c_[i].self_charge * chrg_col_ratio_ * c_.size() / 700,
	       0.)
		<< ","
		<< std::min
	      (0.1 + c_[i].self_charge * chrg_col_ratio_ * c_.size() / 700,
	       0.4)
		<< ","
	      	<< "0.99" << "\";" << std::endl;

	    for (std::list<int>::const_iterator li = c_[i].members.begin();
		 li != c_[i].members.end(); li++)
	      out << *li << ";" << std::endl;
	    out << "}" << std::endl << std::endl;
	  }
      }
  }

  /*-------------------------.
  | Timer::VertexWriter.     |
  `-------------------------*/

  INLINE_TIMER_CC
  Timer::VertexWriter::VertexWriter (const Timer&         timer,
				     const verbose_degree vd,
				     double               ccr)
    : g_                (timer.graph_),
      c_                (timer.comp_),
      c_id_             (timer.comp_id_),
      chrg_col_ratio_   (ccr),
      tps_	        (timer.ticks_per_sec_)
  {
    vd_ = vd;
  }

  INLINE_TIMER_CC
  void
  Timer::VertexWriter::operator()
    (std::ostream& out,
     const output_graph::vertex_descriptor& v) const
  {
    out << "[label=\"" << g_[v].name;
    switch (vd_)
      {
      case VERBOSE_NONE:
	break;

      case VERBOSE_MINIMAL:
	out << "\\lCalls:     " << std::setw(7)
	    << g_[v].count + g_[v].recursive_count + g_[v].int_count
	    << "\\lSelf time: " << std::setw(7)
	    << double(g_[v].self_cpu) / tps_ << "s";
	  break;

      case VERBOSE_NORMAL:
	out << "\\l"
	    << "\\lCalls:        " << std::setw(7)
	    << g_[v].count + g_[v].recursive_count + g_[v].int_count
	    << "\\l"
	    << "\\lSelf time:    " << std::setw(7)
	    << double(g_[v].self_cpu) / tps_ << "s"
	    << "\\lSelf average: " << std::setprecision(5) << std::setw(7)
	    << double(int(g_[v].self_average * 1000)) / tps_ << "ms"
	    << "\\lSelf charge:  " << std::setprecision(3)
	    << std::setw(7) << g_[v].self_charge << "%";
	  if (c_[c_id_[g_[v].id]].member_count <= 1)
	    {
	      out << "\\l"
		  << "\\lTotal time:   " << std::setw(7)
		  << double(g_[v].total_cpu) / tps_ << "s"
		  << "\\lTotal charge: " << std::setprecision(3)
		  << std::setw(7) << g_[v].total_charge << "%";
	    }
	  break;


      default:
	out << "\\l"
	    << "\\lCalls:           " << std::setw(7)
	    << g_[v].count + g_[v].recursive_count + g_[v].int_count
	    << "\\l"
	    << "\\lSelf time:       " << std::setw(7)
	    << double(g_[v].self_cpu) / tps_ << "s"
	    << "\\lSelf user time:  " << std::setw(7)
	    << g_[v].self_user << "ct"
	    << "\\lSelf system time:" << std::setw(7)
	    << g_[v].self_system << "ct"
	    << "\\lSelf average:    " << std::setprecision(5) << std::setw(7)
	    << double(int(g_[v].self_average * 1000)) / tps_ << "ms"
	    << "\\lSelf charge:     " << std::setprecision(3)
	    << std::setw(7) << g_[v].self_charge << "%";
	  if (c_[c_id_[g_[v].id]].member_count <= 1)
	    {
	      out << "\\l"
		  << "\\lTotal time:      " << std::setw(7)
		  << double(g_[v].total_cpu) / tps_ << "s"
		  << "\\lTotal average:   " << std::setprecision(5)
		  << std::setw(7)
		  << double(int(g_[v].total_average * 1000)) / tps_ << "ms"
		  << "\\lTotal charge:    " << std::setprecision(3)
		  << std::setw(7) << g_[v].total_charge << "%";
	    }
      }
    out << "\\l\""
	<< ", fillcolor=\""
	<< std::max
      (0.35 - g_[v].self_charge * chrg_col_ratio_ * c_.size() / 700, 0.)
	<< ","
	<< std::min
      (0.1 + g_[v].self_charge * chrg_col_ratio_ * c_.size() / 700, 0.4)
	<< ","
	<< "0.99"<< "\"]";
  }

  /*-----------------------.
  | Timer::EdgeWriter.     |
  `-----------------------*/

  INLINE_TIMER_CC
  Timer::EdgeWriter::EdgeWriter (const Timer&         timer,
				 const verbose_degree vd,
				 double               ccr)
    : g_              (timer.graph_),
      c_id_	      (timer.comp_id_),
      chrg_col_ratio_ (ccr),
      tps_	      (timer.ticks_per_sec_)
  {
    vd_ = vd;
  }

  INLINE_TIMER_CC
  void
  Timer::EdgeWriter::operator()
    (std::ostream& out,
     const output_graph::edge_descriptor& e) const
  {
    switch (vd_)
      {
      case VERBOSE_NONE:
	break;

      case VERBOSE_MINIMAL:
	out << "[label=\""
	    << g_[e].count
	    << "\"]";
	break;

      case VERBOSE_NORMAL:
	out << "[label=\""
	    << "Calls: " << std::setw(7) << g_[e].count;
	if (c_id_[g_[e].to] != c_id_[g_[e].from])
	  {
	    out << "\\lT.avg: " << std::setprecision(5) << std::setw(7)
		<< double(int(g_[e].total_average * 1000)) / tps_ << "ms";
	  }
	out << "\\l\"]";
	break;

      default:
	out << "[label=\""
	    << "Calls: " << std::setw(7) << g_[e].count
	    << "\\lS.avg: " << std::setprecision(5) << std::setw(7)
	    << double(int(g_[e].self_average * 1000)) / tps_ << "ms";
	  if (c_id_[g_[e].to] != c_id_[g_[e].from])
	    {
	      out << "\\lT.avg: " << std::setprecision(5) << std::setw(7)
		  << double(int(g_[e].total_average * 1000)) / tps_ << "ms";
	    }
	  out << "\\l\"]";
      }
  }


  /*-------------------.
  | Timer::TimeStamp.  |
  `-------------------*/

  INLINE_TIMER_CC
  Timer::TimeStamp::TimeStamp ()
  {
  }

  INLINE_TIMER_CC
  void
  Timer::TimeStamp::clear ()
  {
    wall_ = 0;
    user_ = 0;
    sys_  = 0;
  }


  INLINE_TIMER_CC
  std::ostream&
  Timer::TimeStamp::print (std::ostream& o) const
  {
    return (o << "(" << wall_ << "," << user_ << "," << sys_ << ")");
  }

  INLINE_TIMER_CC
  void
  Timer::TimeStamp::set_to_now ()
  {
    tms tms;

    wall_ = times (&tms);
    user_ = tms.tms_utime;
    sys_  = tms.tms_stime;
  }

  INLINE_TIMER_CC
  void
  Timer::TimeStamp::set_to_lap ()
  {
    clock_t wall;
    tms     tms;

    wall  = times (&tms);

    wall_ = wall - wall_;
    user_ = tms.tms_utime - user_;
    sys_  = tms.tms_stime - sys_;
  }

  INLINE_TIMER_CC
  Timer::TimeStamp&
  Timer::TimeStamp::operator += (const TimeStamp& rhs)
  {
    wall_ += rhs.wall_;
    user_ += rhs.user_;
    sys_  += rhs.sys_;

    return (*this);
  }

  INLINE_TIMER_CC  
  Timer::TimeStamp&
  Timer::TimeStamp::operator -= (const TimeStamp& rhs)
  {
    wall_ -= rhs.wall_;
    user_ -= rhs.user_;
    sys_  -= rhs.sys_;

    return (*this);
  }

  INLINE_TIMER_CC
  double
  Timer::TimeStamp::operator/ (unsigned int n) const
  {
    return (10 * (user_ + sys_) / (n == 0 ? 1.0 : n));
  }


  INLINE_TIMER_CC
  bool
  Timer::TimeStamp::operator < (const TimeStamp& rhs) const
  {
    return (user_ + sys_ < rhs.user_ + rhs.sys_);
  }

  /*--------------.
  | Timer::Task.  |
  `--------------*/

  INLINE_TIMER_CC
  Timer::Task::Task ()
  {
  }

  INLINE_TIMER_CC
  Timer::Task::Task (const std::string& name,
		     const unsigned int id)
    : name_ (name)
  {
    id_ = id;
  }

  INLINE_TIMER_CC
  Timer::Task::Task (const Task& task)
  {
    id_    = task.id_;
    name_  = task.name_;
    calls_ = task.calls_;
  }

  INLINE_TIMER_CC
  Timer::Task::~Task ()
  {
  }

  INLINE_TIMER_CC
  Timer::Call&
  Timer::Task::call(unsigned int called)
  {
    return (calls_[called]);
  }

  /*--------------.
  | Timer::Call.  |
  `--------------*/

  INLINE_TIMER_CC  
  Timer::Call::Call (unsigned int called)
  {
    count_  = 0;
    called_ = called;

    self_.clear();
    total_.clear();
  }

  INLINE_TIMER_CC
  Timer::Call&
  Timer::Call::operator += (const Call& call)
  {
    total_ += call.total_;
    self_  += call.self_;

    count_ += call.count_;

    return (*this);
  }

  INLINE_TIMER_CC
  void
  Timer::Call::add(const StackedCall&	call)
  {
    total_ += call.total_;

    self_  -= call.children_;
    self_  += call.total_;

    count_++;
  }

  /*---------------------.
  | Timer::StackedCall.  |
  `---------------------*/

  INLINE_TIMER_CC
  Timer::StackedCall::StackedCall ()
  {
    total_.set_to_now();
    children_.clear();
  }

  INLINE_TIMER_CC
  Timer::StackedCall::StackedCall (unsigned int called)
  {
    called_ = called;
    total_.set_to_now();
    children_.clear();
  }

  /*-------------------.
  | Timer::GraphCall.  |
  `-------------------*/

  INLINE_TIMER_CC
  Timer::GraphCall::GraphCall ()
  {
    count         = 0;

    to            = 0;
    from          = 0;

    total_wall    = 0;
    total_user    = 0;
    total_system  = 0;
    total_cpu     = 0;
    total_average = 0;
    total_charge  = 0;

    self_wall     = 0;
    self_user     = 0;
    self_system   = 0;
    self_cpu      = 0;
    self_average  = 0;
    self_charge   = 0;
  }

  INLINE_TIMER_CC
  void
  Timer::GraphCall::add_times(TimeStamp&	total,
			      TimeStamp&	self,
			      TimeStamp&	program,
			      unsigned int	cnt)
  {
    count           += cnt;

    total_wall      += total.wall_;
    total_user      += total.user_;
    total_system    += total.sys_;
    total_cpu       += total.sys_ + total.user_;
    total_average   = total_cpu / double(count);
    total_charge    = total_cpu * 100 / double(program.sys_ + program.user_);

    self_wall       += self.wall_;
    self_user       += self.user_;
    self_system     += self.sys_;
    self_cpu        += self.sys_ + self.user_;
    self_average    = self_cpu / double(count);
    self_charge     = self_cpu * 100 / double(program.sys_ + program.user_);
  }

  INLINE_TIMER_CC
  void
  Timer::GraphCall::add_self_time(TimeStamp&		self,
				 unsigned int		cnt)
  {
    count         += cnt;

    self_wall     += self.wall_;
    self_user     += self.user_;
    self_system   += self.sys_;
    self_cpu      += self.sys_ + self.user_;
  }

  INLINE_TIMER_CC
  void
  Timer::GraphCall::add_total_time(TimeStamp&		total,
				   unsigned int		cnt)
  {
    count         += cnt;

    total_wall    += total.wall_;
    total_user    += total.user_;
    total_system  += total.sys_;
    total_cpu     += total.sys_ + total.user_;
  }

  INLINE_TIMER_CC
  void
  Timer::GraphCall::compute_average(clock_t		program_cpu)
  {
    total_average = total_cpu / double(count);
    total_charge  = total_cpu * 100 / double(program_cpu);
    self_average  = self_cpu / double(count);
    self_charge   = self_cpu * 100 / double(program_cpu);
  }

  /*-------------------.
  | Timer::GraphTask.  |
  `-------------------*/


  INLINE_TIMER_CC
  Timer::GraphTask::GraphTask ()
  {
    count           = 0;
    recursive_count = 0;
    int_count       = 0;

    total_wall      = 0;
    total_user      = 0;
    total_system    = 0;
    total_cpu       = 0;
    total_average   = 0;
    total_charge    = 0;

    self_wall       = 0;
    self_user       = 0;
    self_system     = 0;
    self_cpu        = 0;
    self_average    = 0;
    self_charge     = 0;
  }

  INLINE_TIMER_CC
  bool
  Timer::GraphTask::operator < (const GraphTask& task) const
  {
    return (self_cpu > task.self_cpu);
  }

  INLINE_TIMER_CC
  void
  Timer::GraphTask::add_times(TimeStamp&	total,
			      TimeStamp&	self,
			      TimeStamp&	program,
			      unsigned int	cnt)
  {
    count          += cnt;

    total_wall     += total.wall_;
    total_user     += total.user_;
    total_system   += total.sys_;
    total_cpu      += total.sys_ + total.user_;
    total_average  = total_cpu / double(count);
    total_charge   = total_cpu * 100 / double(program.sys_ + program.user_);

    self_wall      += self.wall_;
    self_user      += self.user_;
    self_system    += self.sys_;
    self_cpu       += self.sys_ + self.user_;
    self_average   = self_cpu / double(count);
    self_charge    = self_cpu * 100 / double(program.sys_ + program.user_);
  }

  INLINE_TIMER_CC
  void
  Timer::GraphTask::add_int_time(TimeStamp&		self,
				 unsigned int		cnt)
  {
    int_count    += cnt;
    
    self_wall    += self.wall_;
    self_user    += self.user_;
    self_system  += self.sys_;
    self_cpu     += self.sys_ + self.user_;
  }

  INLINE_TIMER_CC
  void
  Timer::GraphTask::compute_average(clock_t		program_cpu)
  {
    total_average = total_cpu / double(count + int_count + recursive_count);
    total_charge  = total_cpu * 100 / double(program_cpu);
    self_average  = self_cpu / double(count + int_count + recursive_count);
    self_charge   = self_cpu * 100 / double(program_cpu);
  }

  /*------------------------.
  | Timer::GraphComponent.  |
  `------------------------*/

  INLINE_TIMER_CC
  Timer::GraphComponent::GraphComponent ()
  {
    member_count   = 0;

    id             = 0;

    calls          = 0;
    int_calls      = 0;
    out_calls      = 0;

    total_wall     = 0;
    total_user     = 0;
    total_system   = 0;
    total_cpu      = 0;
    total_average  = 0;
    total_charge   = 0;

    self_wall      = 0;
    self_user      = 0;
    self_system    = 0;
    self_cpu       = 0;
    self_average   = 0;
    self_charge    = 0;
  }

  INLINE_TIMER_CC
  void
  Timer::GraphComponent::add_member(GraphTask&	task)
  {
    member_count++;
    members.push_back(task.id);

    self_cpu    += task.self_cpu;
    self_user   += task.self_user;
    self_system += task.self_system;
    self_wall   += task.self_wall;
  }

  INLINE_TIMER_CC
  void
  Timer::GraphComponent::add_call_inc(GraphCall&	call)
  {
    total_cpu    += call.total_cpu;
    total_user   += call.total_user;
    total_system += call.total_system;
    total_wall   += call.total_wall;

    calls += call.count;

    calls_in.push_back(&call);
  }

  INLINE_TIMER_CC
  void
  Timer::GraphComponent::add_call_out(GraphCall&	call)
  {
    out_calls += call.count;

    calls_out.push_back(&call);
  }

  INLINE_TIMER_CC
  void
  Timer::GraphComponent::add_call_internal(GraphCall&	call)
  {
    int_calls += call.count;
  }

  INLINE_TIMER_CC
  void
  Timer::GraphComponent::compute_average(clock_t program_cpu)
  {
    self_charge   = self_cpu * 100 / double(program_cpu); 
    self_average  = self_cpu / double(calls);

    total_charge  = total_cpu * 100 / double(program_cpu); 
    total_average = total_cpu / double(calls);

    int_average   = self_cpu / double (int_calls);
  }

  /*--------------.
  | ScopedTimer.  |
  `--------------*/

  INLINE_TIMER_CC
  ScopedTimer::ScopedTimer (Timer&             timer,
			    const unsigned int i)
  {
    timer_ = &timer;
    timer.push(i);
  }

  INLINE_TIMER_CC
  ScopedTimer::ScopedTimer (Timer&             timer,
			    const std::string& name)
  {
    timer_ = &timer;
    timer.push(name);
  }

  INLINE_TIMER_CC
  ScopedTimer::~ScopedTimer ()
  {
    timer_->pop();
  }


  /*--------------------------.
  | Free standing functions.  |
  `--------------------------*/

  /// Dump \a t on \a o.
  INLINE_TIMER_CC
  std::ostream&
  operator<< (std::ostream& o, const Timer& t)
  {
    return t.print (o, Timer::VERBOSE_NONE);
  }


} // namespace misc

NAMESPACE_VCSN_END

# undef INLINE_TIMER_CC


#endif //!VCSN_MISC_TIMER_CC
