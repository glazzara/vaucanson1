// timer_internal_graph.cc: this file is part of the Vaucanson project.
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
 ** \file misc/timer_internal_graph.cc
 ** Implementation of classes declared in
 ** misc/timer_internal_graph.hh.
 ** These classes are used in Timer (misc/timer.hh) to build a graph
 ** of the results and export it in DOT language.
 */

#ifndef VCSN_MISC_TIMER_INTERNAL_GRAPH_CC
# define VCSN_MISC_TIMER_INTERNAL_GRAPH_CC

# include <iostream>
# include <iomanip>

# ifdef VAUCANSON
#  include <vaucanson/misc/timer_internal_graph.hh>
# else
#  include "timer_internal_graph.hh"
# endif


/// This file is also used in Tiger Compiler, where it is compiled in
/// a C library, so INLINE_TIMER_CC should be defined to empty in that
/// case.
# ifdef VAUCANSON
#  define INLINE_TIMER_CC inline
# else
#  define INLINE_TIMER_CC
# endif

NAMESPACE_VCSN_BEGIN

namespace misc
{
  namespace timer
  {
    /*-----------------------.
    | Standalone functions:  |
    `-----------------------*/

    INLINE_TIMER_CC
    verbose_degree get_verbose_degree (int i)
    {
      switch (i)
        {
        case 0:
          return VERBOSE_NONE;
        case 1:
          return VERBOSE_MINIMAL;
        case 2:
          return VERBOSE_NORMAL;
        case 3:
          return VERBOSE_MAXIMAL;
        default:
          return VERBOSE_NORMAL;
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
    GraphWriter::GraphWriter (const Timer&         timer,
                              const verbose_degree vd,
                              double               ccr)
      : g_              (timer.graph_),
        c_              (timer.comp_),
        c_id_           (timer.comp_id_),
        vd_             (vd),
        chrg_col_ratio_ (ccr),
        tps_            (timer.ticks_per_sec_)
    {
    }

    INLINE_TIMER_CC
    void
    GraphWriter::operator() (std::ostream& out) const
    {
      out << std::endl
          << "node[fontname=\"courier new\"];\n"
          << "node[fontsize=14];\n"
          << "node[shape=box];\n"
          << "node[style=filled];\n"
          << "edge[fontname=\"courier new\"];\n"
          << "edge[fontsize=10];\n"
          << "graph[fontname=\"courier new\"];";

      for (unsigned int i = 0; i < c_.size(); i++)
        {
          if (c_[i].member_count > 1)
            {
              out << "subgraph cluster" << i
                  << "{\n";
              switch (vd_)
                {
                case VERBOSE_NONE:
                  break;

                case VERBOSE_MINIMAL:
                  out << "caption" << i << "[label=\""
                      << "(C:" << std::setw (3) << i << ')'
                      << "\\lIncoming calls: " << std::setw (7)
                      << c_[i].calls
                      << "\\lInternal calls: " << std::setw (7)
                      << c_[i].int_calls
                      << "\\lOutgoing calls: " << std::setw (7)
                      << c_[i].out_calls
                      << "\\lSelf time:      " << std::setw (7)
                      << double (c_[i].self.cpu) / tps_
                      << "s\\l\""
                      << ",style=solid,shape=box]";
                  break;

                case VERBOSE_NORMAL:
                  out << "caption" << i << "[label=\""
                      << "(C:" << std::setw (3) << i << ')'
                      << "\\l"
                      << "\\lIncoming calls: " << std::setw (7)
                      << c_[i].calls
                      << "\\lInternal calls: " << std::setw (7)
                      << c_[i].int_calls
                      << "\\lOutgoing calls: " << std::setw (7)
                      << c_[i].out_calls
                      << "\\l"
                      << "\\lSelf time:      " << std::setw (7)
                      << double (c_[i].self.cpu) / tps_
                      << 's'
                      << "\\lSelf average:   " << std::setprecision (5)
                      << std::setw (7)
                      << double (int (c_[i].self.average * 1000)) / tps_
                      << "ms"
                      << "\\lSelf charge:    " << std::setprecision (3)
                      << std::setw (7)
                      << c_[i].self.charge << '%'
                      << "\\l"
                      << "\\lTotal time:     " << std::setw (7)
                      << double (c_[i].total.cpu) / tps_
                      << 's'
                      << "\\lTotal charge:   " << std::setprecision (3)
                      << std::setw (7)
                      << c_[i].total.charge << "%\\l\""
                      << ",style=solid,shape=box]";
                  break;

                default:
                  out << "caption" << i << "[label=\""
                      << "(C:" << std::setw (3) << i << ')'
                      << "\\l"
                      << "\\lIncoming calls:  " << std::setw (7)
                      << c_[i].calls
                      << "\\lInternal calls:  " << std::setw (7)
                      << c_[i].int_calls
                      << "\\lOutgoing calls:  " << std::setw (7)
                      << c_[i].out_calls
                      << "\\l"
                      << "\\lSelf time:       " << std::setw (7)
                      << double (c_[i].self.cpu) / tps_
                      << 's'
                      << "\\lSelf user time:  " << std::setw (7)
                      << c_[i].self.user << "ct"
                      << "\\lSelf syst. time: "<< std::setw (7)
                      << c_[i].self.system << "ct"
                      << "\\lSelf average:    " << std::setprecision (5)
                      << std::setw (7)
                      << double (int (c_[i].self.average * 1000)) / tps_
                      << "ms"
                      << "\\lSelf charge:     " << std::setprecision (3)
                      << std::setw (7)
                      << c_[i].self.charge << '%'
                      << "\\l"
                      << "\\lTotal time:      " << std::setw (7)
                      << double (c_[i].total.cpu) / tps_
                      << 's'
                      << "\\lTotal average:   " << std::setprecision (5)
                      << std::setw (7)
                      << double (int (c_[i].total.average * 1000)) / tps_
                      << "ms"
                      << "\\lTotal charge:    " << std::setprecision (3)
                      << std::setw (7)
                      << c_[i].total.charge << '%'
                      << "\\l"
                      << "\\lInternal average:" << std::setprecision (5)
                      << std::setw (7)
                      << double (int (c_[i].int_average * 1000)) / tps_
                      << "ms\\l\""
                      << ",style=solid,shape=box]";
                }
              out << std::endl
                  << "style=filled\n"
                  << "fillcolor=\""
                  << std::max
                (0.35 - c_[i].self.charge * chrg_col_ratio_ * c_.size () / 700,
                 0.)
                  << ','
                  << std::min
                (0.1 + c_[i].self.charge * chrg_col_ratio_ * c_.size () / 700,
                 0.4)
                  << ','
                  << "0.99" << "\";" << std::endl;

              for (std::list<int>::const_iterator li = c_[i].members.begin();
                   li != c_[i].members.end(); li++)
                out << *li << ";\n";
              out << "}\n" << std::endl;
            }
        }
    }

    /*-------------------------.
    | Timer::VertexWriter.     |
    `-------------------------*/

    INLINE_TIMER_CC
    VertexWriter::VertexWriter (const Timer&         timer,
                                const verbose_degree vd,
                                double               ccr)
      : g_                (timer.graph_),
        c_                (timer.comp_),
        c_id_             (timer.comp_id_),
        vd_               (vd),
        chrg_col_ratio_   (ccr),
        tps_              (timer.ticks_per_sec_)
    {
    }

    INLINE_TIMER_CC
    void
    VertexWriter::operator()
      (std::ostream&                          out,
       const output_graph::vertex_descriptor& v) const
    {
      out << "[label=\"" << g_[v].name;
      switch (vd_)
        {
        case VERBOSE_NONE:
          break;

        case VERBOSE_MINIMAL:
          out << "\\lCalls:     " << std::setw (7)
              << g_[v].count + g_[v].recursive_count + g_[v].int_count
              << "\\lSelf time: " << std::setw (7)
              << double (g_[v].self.cpu) / tps_ << 's';
          break;

        case VERBOSE_NORMAL:
          out << "\\l"
              << "\\lCalls:        " << std::setw (7)
              << g_[v].count + g_[v].recursive_count + g_[v].int_count
              << "\\l"
              << "\\lSelf time:    " << std::setw (7)
              << double (g_[v].self.cpu) / tps_ << 's'
              << "\\lSelf average: " << std::setprecision (5) << std::setw (7)
              << double (int (g_[v].self.average * 1000)) / tps_ << "ms"
              << "\\lSelf charge:  " << std::setprecision (3)
              << std::setw (7) << g_[v].self.charge << '%';
          if (c_[c_id_[g_[v].id]].member_count <= 1)
            {
              out << "\\l"
                  << "\\lTotal time:   " << std::setw (7)
                  << double (g_[v].total.cpu) / tps_ << 's'
                  << "\\lTotal charge: " << std::setprecision (3)
                  << std::setw (7) << g_[v].total.charge << '%';
            }
          break;


        default:
          out << "\\l"
              << "\\lCalls:           " << std::setw (7)
              << g_[v].count + g_[v].recursive_count + g_[v].int_count
              << "\\l"
              << "\\lSelf time:       " << std::setw (7)
              << double (g_[v].self.cpu) / tps_ << 's'
              << "\\lSelf user time:  " << std::setw (7)
              << g_[v].self.user << "ct"
              << "\\lSelf system time:" << std::setw (7)
              << g_[v].self.system << "ct"
              << "\\lSelf average:    " << std::setprecision (5)
              << std::setw (7)
              << double (int (g_[v].self.average * 1000)) / tps_ << "ms"
              << "\\lSelf charge:     " << std::setprecision (3)
              << std::setw (7) << g_[v].self.charge << '%';
          if (c_[c_id_[g_[v].id]].member_count <= 1)
            {
              out << "\\l"
                  << "\\lTotal time:      " << std::setw (7)
                  << double (g_[v].total.cpu) / tps_ << 's'
                  << "\\lTotal average:   " << std::setprecision (5)
                  << std::setw (7)
                  << double (int (g_[v].total.average * 1000)) / tps_ << "ms"
                  << "\\lTotal charge:    " << std::setprecision (3)
                  << std::setw (7) << g_[v].total.charge << '%';
            }
        }
      out << "\\l\""
          << ", fillcolor=\""
          << std::max
        (0.35 - g_[v].self.charge * chrg_col_ratio_ * c_.size () / 700, 0.)
          << ','
          << std::min
        (0.1 + g_[v].self.charge * chrg_col_ratio_ * c_.size () / 700, 0.4)
          << ','
          << "0.99"<< "\"]";
    }

    /*-----------------------.
    | Timer::EdgeWriter.     |
    `-----------------------*/

    INLINE_TIMER_CC
    EdgeWriter::EdgeWriter (const Timer&         timer,
                            const verbose_degree vd,
                            double               ccr)
      : g_              (timer.graph_),
        c_id_           (timer.comp_id_),
        vd_             (vd),
        chrg_col_ratio_ (ccr),
        tps_            (timer.ticks_per_sec_)
    {
    }

    INLINE_TIMER_CC
    void
    EdgeWriter::operator()
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
              << "Calls: " << std::setw (7) << g_[e].count;
          if (c_id_[g_[e].to] != c_id_[g_[e].from])
            {
              out << "\\lT.avg: " << std::setprecision (5) << std::setw (7)
                  << double (int (g_[e].total.average * 1000)) / tps_ << "ms";
            }
          out << "\\l\"]";
          break;

        default:
          out << "[label=\""
              << "Calls: " << std::setw (7) << g_[e].count
              << "\\lS.avg: " << std::setprecision (5) << std::setw (7)
              << double (int (g_[e].self.average * 1000)) / tps_ << "ms";
          if (c_id_[g_[e].to] != c_id_[g_[e].from])
            {
              out << "\\lT.avg: " << std::setprecision (5) << std::setw (7)
                  << double (int (g_[e].total.average * 1000)) / tps_ << "ms";
            }
          out << "\\l\"]";
        }
    }

    /*-------------------.
    | Timer::TimeStats.  |
    `-------------------*/

    INLINE_TIMER_CC
    TimeStats::TimeStats ()
      : wall    (0),
        user    (0),
        system  (0),
        cpu     (0),
        average (0),
        charge  (0)
    {
    }

    // " in task names would produce unwanted results.
    INLINE_TIMER_CC
    void
    TimeStats::dump (std::ostream&      o,
                     const std::string& name) const
    {
      o << "<time name=\"" << name
        << "\" wall=\"" << wall
        << "\" user=\"" << user
        << "\" system=\"" << system
        << "\" cpu=\"" << cpu
        << "\" average=\"" << average
        << "\" charge=\"" << charge
        << "\" />";
    }


    /*-------------------.
    | Timer::GraphCall.  |
    `-------------------*/

    INLINE_TIMER_CC
    GraphCall::GraphCall ()
      : count         (0),
        from          (0),
        to            (0)
    {
    }

    INLINE_TIMER_CC
    void
    GraphCall::add_times (TimeStamp&    total,
                          TimeStamp&    self,
                          TimeStamp&    program,
                          unsigned int  cnt)
    {
      count           += cnt;

      this->total.wall      += total.wall_;
      this->total.user      += total.user_;
      this->total.system    += total.sys_;
      this->total.cpu       += total.sys_ + total.user_;
      this->total.average   = this->total.cpu / double (count);
      this->total.charge    = this->total.cpu * 100 /
	double (program.sys_ + program.user_);
      this->self.wall       += self.wall_;
      this->self.user       += self.user_;
      this->self.system     += self.sys_;
      this->self.cpu        += self.sys_ + self.user_;
      this->self.average    = this->self.cpu / double (count);
      this->self.charge     = this->self.cpu * 100 /
	double (program.sys_ + program.user_);
    }

    INLINE_TIMER_CC
    void
    GraphCall::add_self_time (TimeStamp&                self,
                              unsigned int              cnt)
    {
      count         += cnt;

      this->self.wall     += self.wall_;
      this->self.user     += self.user_;
      this->self.system   += self.sys_;
      this->self.cpu      += self.sys_ + self.user_;
    }

    INLINE_TIMER_CC
    void
    GraphCall::add_total_time (TimeStamp&               total,
                               unsigned int             cnt)
    {
      count         += cnt;

      this->total.wall    += total.wall_;
      this->total.user    += total.user_;
      this->total.system  += total.sys_;
      this->total.cpu     += total.sys_ + total.user_;
    }

    INLINE_TIMER_CC
    void
    GraphCall::compute_average (clock_t         program_cpu)
    {
      total.average = total.cpu / double (count);
      total.charge  =
	(program_cpu == 0 ? 0 : total.cpu * 100 / double (program_cpu));
      self.average  = self.cpu / double (count);
      self.charge   =
	(program_cpu == 0 ? 0 : self.cpu * 100 / double (program_cpu));
    }

    /*-------------------.
    | Timer::GraphTask.  |
    `-------------------*/


    INLINE_TIMER_CC
    GraphTask::GraphTask ()
      : count           (0),
        recursive_count (0),
        int_count       (0)
    {
    }

    INLINE_TIMER_CC
    void
    GraphTask::add_times (TimeStamp&    total,
                          TimeStamp&    self,
                          TimeStamp&    program,
                          unsigned int  cnt)
    {
      count          += cnt;

      this->total.wall     += total.wall_;
      this->total.user     += total.user_;
      this->total.system   += total.sys_;
      this->total.cpu      += total.sys_ + total.user_;
      this->total.average  = this->total.cpu / double (count);
      this->total.charge   =
	(program.sys_ + program.user_ == 0 ? 0 : this->total.cpu * 100 /
	 double (program.sys_ + program.user_));

      this->self.wall      += self.wall_;
      this->self.user      += self.user_;
      this->self.system    += self.sys_;
      this->self.cpu       += self.sys_ + self.user_;
      this->self.average   = this->self.cpu / double (count);
      this->self.charge    =
	(program.sys_ + program.user_ == 0 ? 0 :this->self.cpu * 100 /
	 double (program.sys_ + program.user_));
    }

    INLINE_TIMER_CC
    void
    GraphTask::add_int_time (TimeStamp&         self,
                             unsigned int       cnt)
    {
      int_count    += cnt;
    
      this->self.wall    += self.wall_;
      this->self.user    += self.user_;
      this->self.system  += self.sys_;
      this->self.cpu     += self.sys_ + self.user_;
    }

    INLINE_TIMER_CC
    void
    GraphTask::compute_average (clock_t         program_cpu)
    {
      total.average = total.cpu / double (count + int_count + recursive_count);
      total.charge  =
	(program_cpu == 0 ? 0 : total.cpu * 100 / double (program_cpu));
      self.average  = self.cpu / double (count + int_count + recursive_count);
      self.charge   =
	(program_cpu == 0 ? 0 : self.cpu * 100 / double (program_cpu));
    }

    /*------------------------.
    | Timer::GraphComponent.  |
    `------------------------*/

    INLINE_TIMER_CC
    GraphComponent::GraphComponent ()
      : member_count   (0),
        out_calls      (0),
        int_calls      (0),
        calls          (0),
        id             (0)
    {
    }

    INLINE_TIMER_CC
    void
    GraphComponent::add_member (GraphTask&      task)
    {
      ++member_count;
      members.push_back (task.id);

      self.cpu    += task.self.cpu;
      self.user   += task.self.user;
      self.system += task.self.system;
      self.wall   += task.self.wall;
    }

    INLINE_TIMER_CC
    void
    GraphComponent::add_call_inc (GraphCall&    call)
    {
      total.cpu    += call.total.cpu;
      total.user   += call.total.user;
      total.system += call.total.system;
      total.wall   += call.total.wall;

      calls += call.count;

      calls_in.push_back (&call);
    }

    INLINE_TIMER_CC
    void
    GraphComponent::compute_average (clock_t program_cpu)
    {
      self.charge   =
	(program_cpu == 0 ? 0 : self.cpu * 100 / double (program_cpu)); 
      self.average  = self.cpu / double (calls);

      total.charge  =
	(program_cpu == 0 ? 0 : total.cpu * 100 / double (program_cpu)); 
      total.average = total.cpu / double (calls);

      int_average   = self.cpu / double (int_calls);
    }
  } // namespace timer
} // namespace misc

NAMESPACE_VCSN_END

# undef INLINE_TIMER_CC


#endif //!VCSN_MISC_TIMER_INTERNAL_GRAPH_CC
