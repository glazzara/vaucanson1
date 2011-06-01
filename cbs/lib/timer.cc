// timer.cc: this file is part of the CBS project.
//
// CBS, a C++ benchmarking suite.
//
// Copyright (C) 2007, 2008, 2009, 2011 The CBS authors.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// The complete GNU General Public Licence Notice can be found as the
// `COPYING' file in the root directory.
//
// The CBS Authors consists of people listed in the `AUTHORS' file.
//

/**
 ** \file lib/timer.cc
 ** \brief Implementation for include/cbs/bench/timer.hh.
 */

// STL
#include <iostream>
#include <iomanip>

// Unix
#include <unistd.h>

// Internal
#include <cbs/bench/timer.hh>


#define INLINE_TIMER_CC

#define MAIN_TASK_NAME "_program"

namespace timer
{

  /*------------------.
  | Timer.            |
  | General methods.  |
  `------------------*/

  INLINE_TIMER_CC
  Timer::Timer ()
    : comp_count_    (0),
      task_count_    (1),
      total_calls_   (0),
      is_running_    (false),
      cleared_       (true)
  {
  }

  INLINE_TIMER_CC
  Timer::Timer       (const Timer& rhs)
    : calls_         (rhs.calls_),
      tasks_         (rhs.tasks_),
      names_         (rhs.names_),
      time_          (rhs.time_),
      graph_         (rhs.graph_),
      comp_id_       (rhs.comp_id_),
      comp_          (rhs.comp_),
      comp_count_    (rhs.comp_count_),
      task_count_    (rhs.task_count_),
      total_calls_   (rhs.total_calls_),
      is_running_    (rhs.is_running_),
      cleared_       (rhs.cleared_),
      last_time_     (rhs.last_time_)
  {
  }

  INLINE_TIMER_CC
  const Timer& Timer::operator= (const Timer& rhs)
  {
    if (this == &rhs)
      return *this;

    names_         = rhs.names_;
    time_          = rhs.time_;
    graph_         = rhs.graph_;
    calls_         = rhs.calls_;
    comp_id_       = rhs.comp_id_;
    comp_          = rhs.comp_;
    comp_count_    = rhs.comp_count_;
    task_count_    = rhs.task_count_;
    total_calls_   = rhs.total_calls_;
    tasks_         = rhs.tasks_;
    is_running_    = rhs.is_running_;
    cleared_       = rhs.cleared_;
    last_time_     = rhs.last_time_;

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
    last_time_.clear();

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

    total_calls_ = 0;

    tasks_.resize (1);

    names_[MAIN_TASK_NAME] = 0;
    tasks_[0].name_     = MAIN_TASK_NAME;
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

	last_time_ = time_;

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
  std::string
  Timer::current_task () const
  {
    if (!(calls_.empty ()))
    {
      return tasks_[calls_.top ().called_].name_;
    }
    return MAIN_TASK_NAME;
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
        assert (false);
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
        assert (false);
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
        assert (false);
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
        std::cerr << "Timer.pop: Call stack empty" << std::endl;
        assert (false);
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

    timer::TimeVal total_cpu =
      graph_[0].total.cpu + rhs.graph_[0].total.cpu;

    for (vxrange = vertices (graph_), vx = vxrange.first,
           vxrange2 = vertices (rhs.graph_), vx2 = vxrange2.first;
         vx != vxrange.second && vx2 != vxrange2.second; ++vx, ++vx2)
      {
        vd  = *vx;
        vd2 = *vx2;

        graph_[vd].total.user    += rhs.graph_[vd2].total.user;
        graph_[vd].total.system  += rhs.graph_[vd2].total.system;
        graph_[vd].total.cuser   += rhs.graph_[vd2].total.cuser;
        graph_[vd].total.csystem += rhs.graph_[vd2].total.csystem;
        graph_[vd].total.cpu     += rhs.graph_[vd2].total.cpu;

        graph_[vd].self.user     += rhs.graph_[vd2].self.user;
        graph_[vd].self.system   += rhs.graph_[vd2].self.system;
        graph_[vd].self.cuser    += rhs.graph_[vd2].self.cuser;
        graph_[vd].self.csystem  += rhs.graph_[vd2].self.csystem;
        graph_[vd].self.cpu      += rhs.graph_[vd2].self.cpu;

        graph_[vd].count            += rhs.graph_[vd2].count;
        graph_[vd].recursive_count  += rhs.graph_[vd2].recursive_count;
        graph_[vd].int_count        += rhs.graph_[vd2].int_count;

        graph_[vd].compute_average (total_cpu);
      }

    for (erange = edges (graph_), ei = erange.first,
           erange2 =  edges (rhs.graph_), ei2 = erange2.first;
         ei != erange.second && ei2 != erange2.second; ++ei, ++ei2)
      {
        ed  = *ei;
        ed2 = *ei2;

        graph_[ed].total.user    += rhs.graph_[ed2].total.user;
        graph_[ed].total.system  += rhs.graph_[ed2].total.system;
        graph_[ed].total.cuser   += rhs.graph_[ed2].total.cuser;
        graph_[ed].total.csystem += rhs.graph_[ed2].total.csystem;
        graph_[ed].total.cpu     += rhs.graph_[ed2].total.cpu;

        graph_[ed].self.user     += rhs.graph_[ed2].self.user;
        graph_[ed].self.system   += rhs.graph_[ed2].self.system;
        graph_[ed].self.cuser    += rhs.graph_[ed2].self.cuser;
        graph_[ed].self.csystem  += rhs.graph_[ed2].self.csystem;
        graph_[ed].self.cpu      += rhs.graph_[ed2].self.cpu;

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

    timer::TimeVal total_cpu = graph_[0].total.cpu / rhs;

    for (vxrange = vertices (graph_), vx = vxrange.first;
         vx != vxrange.second; ++vx)
      {
        vd = *vx;

        graph_[vd].total.user    /= rhs;
        graph_[vd].total.system  /= rhs;
        graph_[vd].total.cuser   /= rhs;
        graph_[vd].total.csystem /= rhs;
        graph_[vd].total.cpu     /= rhs;

        graph_[vd].self.user     /= rhs;
        graph_[vd].self.system   /= rhs;
        graph_[vd].self.cuser    /= rhs;
        graph_[vd].self.csystem  /= rhs;
        graph_[vd].self.cpu      /= rhs;

        graph_[vd].count                /= rhs;
        graph_[vd].recursive_count      /= rhs;
        graph_[vd].int_count            /= rhs;

        graph_[vd].compute_average (total_cpu);
      }

    for (erange = edges (graph_), ei = erange.first;
         ei != erange.second; ++ei)
      {
        ed = *ei;

        graph_[ed].total.user    /= rhs;
        graph_[ed].total.system  /= rhs;
        graph_[ed].total.cuser   /= rhs;
        graph_[ed].total.csystem /= rhs;
        graph_[ed].total.cpu     /= rhs;

        graph_[ed].self.user     /= rhs;
        graph_[ed].self.system   /= rhs;
        graph_[ed].self.cuser    /= rhs;
        graph_[ed].self.csystem  /= rhs;
        graph_[ed].self.cpu      /= rhs;

        graph_[ed].count         /= rhs;

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
    timer::Task*        task = 0;
    timer::Call*        call = 0;

    timer::output_graph::vertex_iterator   vx;
    timer::output_graph::vertex_descriptor vd;
    timer::output_graph::out_edge_iterator oe;
    timer::output_graph::edge_descriptor   ed;

    timer::vertex_range   vxrange;
    timer::out_edge_range oerange;

    total_calls_ = 1;

    for (vxrange = vertices (graph_), vx = vxrange.first;
         vx != vxrange.second; ++vx)
      {
        task = & (tasks_[graph_[*vx].id]);
        for (oerange = out_edges (*vx, graph_), oe = oerange.first;
             oe != oerange.second; ++oe)
          {
            ed   = *oe;
            call = & (task->call (graph_[ed].to));

	    total_calls_ += call->count_;

            graph_[ed].add_times (call->total_, call->self_,
                                  time_, call->count_);

            vd  = target (ed, graph_);

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
    timer::Task*        task = 0;
    timer::Call*        call = 0;

    timer::output_graph::vertex_descriptor      vd;
    timer::output_graph::edge_descriptor        ed;

    timer::vertex_range vxrange;

    for (timer::task_vector::iterator task_ = tasks_.begin();
         task_ != tasks_.end (); ++task_)
      {
        task = & (*task_);
        vd   = add_vertex (graph_);

        graph_[vd].name = task->name_;
        graph_[vd].id   = task->id_;
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
  std::ostream&
  Timer::dump (std::ostream&         o) const
  {
    timer::output_graph::vertex_iterator   vx;
    timer::output_graph::edge_iterator     ed;

    timer::vertex_range   vxrange;
    timer::edge_range     edrange;


    o << "<timer>\n"

      << "  ";
    graph_[0].total.dump (o, "total");
    o << '\n'

      << "  <taskList>\n";

    for (vxrange =  vertices (graph_), vx = vxrange.first;
         vx != vxrange.second; ++vx)
      {
        const timer::GraphTask& task = (graph_[*vx]);

        o << "    <task\n"
          << "      id=\""             << task.id              << "\"\n"
          << "      name=\""           << task.name            << "\"\n"
          << "      calls=\""          << task.count           << "\"\n"
          << "      recursiveCalls=\"" << task.recursive_count << "\"\n"
          << "      cycleCalls=\""     << task.int_count       << "\"\n"
          << "      component=\""      << comp_id_[task.id]    << "\"\n"
          << "    >\n";

        o << "      ";
        task.total.dump (o, "total");

        o << "\n      ";
        task.self.dump (o, "self");

        o << "\n    </task>\n";
      }

    o << "  </taskList>" << std::endl;


    o << "  <callList>\n";

    for (edrange = edges (graph_), ed = edrange.first;
         ed != edrange.second; ++ed)
      {
        const timer::GraphCall& call   = graph_[*ed];

        o << "    <call\n"
          << "      source=\""   << call.from  << "\"\n"
          << "      target=\""   << call.to    << "\"\n"
          << "      count=\""    << call.count << "\"\n"
          << "    >\n";

        o << "      ";
        call.total.dump (o, "total");

        o << "\n      ";
        call.self.dump (o, "self");

        o << "\n    </call>\n";
      }

    o << "  </callList>" << std::endl;

    o << "  <componentlist>\n";

    for (unsigned int c = 0; c < comp_count_; ++c)
      {
        o << "    <component id=\""      << c                     << "\"\n"
          << "      memberCount=\""      << comp_[c].member_count << "\"\n"
          << "      inboundCalls=\""     << comp_[c].calls        << "\"\n"
          << "      outgoingCalls=\""    << comp_[c].out_calls    << "\"\n"
          << "      internalCalls=\""    << comp_[c].int_calls    << "\"\n"
          << "      internalAverage=\""  << comp_[c].int_average  << "\"\n"
          << "    >\n";

        o << "      ";
        comp_[c].total.dump (o, "total");

        o << "\n      ";
        comp_[c].self.dump (o, "self");
        o << '\n';

        for (std::list<int>::const_iterator li = comp_[c].members.begin ();
             li != comp_[c].members.end (); ++li)
          {
            o << "      <member id=\"" << *li << "\" />\n";
          }

        o << "    </component>\n";

      }

    o << "  </componentList>\n";

    o << "</timer>" << std::endl;

    return o;
  }

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

    timer::time_unit time_unit =
      (graph_[0].self.cpu.ms () < 200 * int (task_count_)
       && graph_[0].self.cpu.ms () < 10000)
      ? timer::TIME_MS :
      (graph_[0].self.cpu.s () < 120 * int (task_count_)
       && graph_[0].self.cpu.s () < 10000)
      ? timer::TIME_S :
      (graph_[0].self.cpu.m () < 120 * int (task_count_)
       && graph_[0].self.cpu.m () < 10000)
      ? timer::TIME_M :
      timer::TIME_H;

    o << "[Task list:]\n\n"
      << "Charge  id:        <name>        total"
      "     self     calls   self avg. total avg.\n";

    for (vxrange = vertices (graph_), vx = vxrange.first;
         vx != vxrange.second; ++vx)
      {
        gtlist.push_front (graph_[*vx]);
      }

    gtlist.sort ();

    for (std::list<timer::GraphTask>::iterator li = gtlist.begin ();
         li != gtlist.end (); ++li)
      {
        o << std::setiosflags (std::ios::fixed)
          << std::setw (5) << std::setprecision (1)
          << li->self.charge << "% "
          << std::setw (3) <<  li->id << ':'
          << std::setw (18) << li->name.substr (0, 18) << ' ';

        if (comp_[comp_id_[li->id]].member_count > 1)
          o << " (C:" << std::setw (3) << comp_id_[li->id] << ") ";
        else
          {
            o << std::setprecision (2) << std::setw (7);
            li->total.cpu.print (o, time_unit);
          }

        o << std::setprecision (2) << std::setw (7);
        li->self.cpu.print (o, time_unit);

        o << std::resetiosflags (std::ios::fixed);

        o << std::setprecision (7) << std::setw (9)
          << li->count + li->recursive_count + li->int_count << ' ';

        o << std::setiosflags (std::ios::fixed);

        o << std::setprecision (2) << std::setw (9);
        li->self.average.print (o);

        if (comp_[comp_id_[li->id]].member_count > 1)
          o << "    (C:" << std::setw (3) << comp_id_[li->id] << ')';
        else
          {
            o << std::setprecision (2) << std::setw (9);
            li->total.average.print (o);
          }

        o << std::resetiosflags (std::ios::fixed);

        o << '\n';

      }

    o << std::endl;

    if (vd < timer::VERBOSE_NORMAL)
      return;

    o << "__________________________________"
         "______________________________________________\n\n";

    o << "[Call graph:]\n\n\n";

    o << "Cycles:\n"
      << "<cycle>  charge   total     self   calls:e/i    int avg."
         "   self avg.  total avg.\n";


    for (unsigned int c = 0; c < comp_count_; ++c)
      {
        if (comp_[c].member_count > 1)
          {
            o << ".................................."
                 "..............................................\n";

            o << "(C:" << std::setw (3) << comp_[c].id << ')';

            o << std::setiosflags (std::ios::fixed);

            o << "  " << std::setw (5) << std::setprecision (1)
              << comp_[c].self.charge << '%';

            o << std::setprecision (2) << std::setw (7);
            comp_[c].total.cpu.print (o);

            o << std::setprecision (2) << std::setw (7);
            comp_[c].self.cpu.print (o);

            o << std::resetiosflags (std::ios::fixed);

            o << std::setw (5) << comp_[c].calls << '/';
            o << std::setw (5) << comp_[c].int_calls;

            o << std::setiosflags (std::ios::fixed);

            o << std::setprecision (2) << std::setw (10);
            comp_[c].int_average.print (o);

            o << std::setprecision (2) << std::setw (10);
            comp_[c].self.average.print (o);

            o << std::setprecision (2) << std::setw (10);
            comp_[c].total.average.print (o);

            o << std::resetiosflags (std::ios::fixed);

            o << std::endl << std::endl;

            for (std::list<int>::const_iterator li = comp_[c].members.begin ();
                 li != comp_[c].members.end (); ++li)
              {
                const timer::GraphTask& task = (graph_[vertex (*li, graph_)]);
                o << std::setw (6) << task.id << ":  ";

                o << std::setiosflags (std::ios::fixed);

                o << std::setw (5) << std::setprecision (1)
                  << task.self.charge * 100 / comp_[c].self.charge << '%';

                o << "         ";

                o << std::setprecision (2) << std::setw (7);
                task.self.cpu.print (o);

                o << std::resetiosflags (std::ios::fixed);

                o << std::setw (5) << task.count << '/';
                o << std::setw (5)
                  << task.int_count + task.recursive_count;

                o << std::setiosflags (std::ios::fixed);

                o << std::setprecision (2) << std::setw (10);
                task.self.average.print (o);

                o << std::resetiosflags (std::ios::fixed);

                o << std::setw (24) << task.name.substr(0, 24);

                o << std::endl;
              }
          }
      }

    o << std::endl;

    o << "__________________________________"
         "______________________________________________\n\n\n";

    o << "Tasks:\n"
      << "D  id:        <name>   charge   total    self        calls"
         "  self avg. total avg.\n";

    for (vxrange =  vertices (graph_), vx = vxrange.first;
         vx != vxrange.second; ++vx)
      {
        o << ".................................."
             "..............................................\n";

        o << '[' << graph_[*vx].id << "] " << graph_[*vx].name
          << std::endl << std::endl;

        for (ierange = in_edges (*vx, graph_), ie = ierange.first;
             ie != ierange.second; ++ie)
          {
            const timer::GraphTask& task = (graph_[source (*ie, graph_)]);
            const timer::GraphCall& call = graph_[*ie];

            o << "<-" << std::setw (3)
              << task.id << ':';

            o << std::setw (16) << task.name.substr (0, 16);

            o << std::setiosflags (std::ios::fixed);

            o << std::setprecision (1) << std::setw (6)
              << (graph_[*vx].self.charge == 0 ? 100 :
                  call.self.charge * 100 / graph_[*vx].self.charge)
              << "% ";

            o << "        ";

            o << std::setprecision (2) << std::setw (6);
            call.self.cpu.print (o);

            o << std::setw (12)
              << call.count;

            o << std::setprecision (2) << std::setw (9);
            call.self.average.print (o);

            o << std::resetiosflags (std::ios::fixed);

            o << std::endl;
          }
        o << std::endl;

        const timer::GraphTask& task = (graph_[*vx]);

        o << "  " << std::setw (3)
          << task.id << ':';

        o << std::setw (16) << task.name.substr (0, 16);

        o << std::setiosflags (std::ios::fixed);

        o << std::setprecision (1) << std::setw (6)
          << task.self.charge << "% ";

        if (comp_[comp_id_[task.id]].member_count > 1)
          o << "(C:" << std::setw (3)
            << comp_id_[task.id] << ") ";
        else
          {
            o << std::setprecision (2) << std::setw (6);
            task.total.cpu.print (o);
          }

        o << std::setprecision (2) << std::setw (6);
        task.self.cpu.print (o);

        o << std::resetiosflags (std::ios::fixed);

        o << std::setw (12)
          << task.count + task.int_count + task.recursive_count;

        o << std::setiosflags (std::ios::fixed);

        o << std::setprecision (2) << std::setw (9);
        task.self.average.print (o);

        if (comp_[comp_id_[task.id]].member_count > 1)
          o << "   (C:" << std::setw (3)
            << comp_id_[task.id] << ") ";
        else
          {
            o << std::setprecision (2) << std::setw (9);
            task.total.average.print (o);
          }

        o << std::resetiosflags (std::ios::fixed);

        o << std::endl << std::endl;


        for (oerange = out_edges (*vx, graph_), oe = oerange.first;
             oe != oerange.second; ++oe)
          {
            const timer::GraphTask& task = (graph_[target (*oe, graph_)]);
            const timer::GraphCall& call = graph_[*oe];

            o << "->" << std::setw (3)
              << task.id << ':';

            o << std::setw (16) << task.name.substr (0, 16);

            o << std::setiosflags (std::ios::fixed);

            o << std::setprecision (1) << std::setw (6)
              << (task.self.charge == 0 ? 100 :
                  call.self.charge * 100 / task.self.charge)
              << "% ";

            o << "        ";

            o << std::setprecision (2) << std::setw (6);
            call.self.cpu.print (o);

            o << std::resetiosflags (std::ios::fixed);

            o << std::setw (12)
              << call.count;

            o << std::setiosflags (std::ios::fixed);

            o << std::setprecision (2) << std::setw (9);
            call.self.average.print (o);

            o << std::resetiosflags (std::ios::fixed);

            o << std::endl;
          }
      }

    o << std::endl;

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

        o << '[' << task.id << "] " << task.name
          << "\n\n";

        o << "Calls from exterior:        " << std::setw (10) << task.count
          << '\n';
        o << "Calls from within cycle:    " << std::setw (10) << task.int_count
          << '\n';
        o << "Recursive calls:            " << std::setw (10)
          << task.recursive_count << '\n';

        o << '\n';

        o << std::setiosflags (std::ios::fixed);

        o << "Self cpu time:              " << std::setw (10)
	  << std::setprecision (2) << task.self.cpu
          << '\n';
        o << "Self user time:             " << std::setw (10)
	  << std::setprecision (2) << task.self.user
          << '\n';
        o << "Self system time:           " << std::setw (10)
	  << std::setprecision (2) << task.self.system
          << '\n';
        o << "Self children user time:    " << std::setw (10)
	  << std::setprecision (2) << task.self.cuser
          << '\n';
        o << "Self children system time:  " << std::setw (10)
	  << std::setprecision (2) << task.self.csystem
          << '\n';
        o << "Self wall time:             " << std::setw (10)
	  << std::setprecision (2) << task.self.wall
          << '\n';

        o << "Self average cpu time:      " << std::setw (10)
	  << std::setprecision (2)
          << task.self.average << '\n';
        o << "Self charge:                " << std::setw (10)
	  << std::setprecision (1)
          << task.self.charge << "%\n";

        o << '\n';
        o << "Total cpu time:             " << std::setw (10)
	  << std::setprecision (2) << task.total.cpu
          << '\n';
        o << "Total user time:            " << std::setw (10)
	  << std::setprecision (2) << task.total.user
          << '\n';
        o << "Total system time:          " << std::setw (10)
	  << std::setprecision (2) << task.total.system
          << '\n';
        o << "Total children user time:   " << std::setw (10)
	  << std::setprecision (2) << task.total.cuser
          << '\n';
        o << "Total children system time: " << std::setw (10)
	  << std::setprecision (2) << task.total.csystem
          << '\n';
        o << "Total wall time:            " << std::setw (10)
	  << std::setprecision (2) << task.total.wall
          << '\n';

        o << "Total average cpu time:     " << std::setw (10)
	  << std::setprecision (2)
          << task.total.average << '\n';
        o << "Total charge:               " << std::setw (10)
	  << std::setprecision (1)
          << task.total.charge << "%\n";

	o << std::resetiosflags (std::ios::fixed);
      }
    o << std::endl;
  }
} // namespace timer


#undef INLINE_TIMER_CC
