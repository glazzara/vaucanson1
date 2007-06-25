// timer_internal_graph.hh: this file is part of the Vaucanson project.
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

#ifndef VCSN_MISC_TIMER_INTERNAL_GRAPH_HH
# define VCSN_MISC_TIMER_INTERNAL_GRAPH_HH

/**
 ** \file misc/timer_internal_graph.hh
 ** This file contains classes used by Timer in timer.hh to build and
 ** export a graph of the task timing results.
 ** Classes declared here are not meant to be used on their own.
 ** See timer.hh for information on how to use the Timer class to time
 ** nested tasks.
 */

# include <list>
# include <string>
# include <iosfwd>
# include <boost/graph/adjacency_list.hpp>
# include <boost/graph/strong_components.hpp>
# include <boost/graph/graphviz.hpp>

# ifdef VAUCANSON
#  define NAMESPACE_VCSN_BEGIN namespace vcsn {
#  define NAMESPACE_VCSN_END   } // namespace vcsn
# else
#  define NAMESPACE_VCSN_BEGIN
#  define NAMESPACE_VCSN_END
#  include <cassert>
#  define precondition(C) assert(C)
# endif


NAMESPACE_VCSN_BEGIN

namespace misc
{
  class Timer;

  namespace timer
  {
    class TimeStamp;

    /// Enumerate the different verbose degrees for dot format graph export.
    typedef enum verbose_degree { VERBOSE_NONE, VERBOSE_MINIMAL,
                                  VERBOSE_NORMAL, VERBOSE_MAXIMAL };

    // Return the corresponding verbose_degree.
    verbose_degree get_verbose_degree (int i);

    // Graph output writers
    class GraphWriter;
    class VertexWriter;
    class EdgeWriter;

    // Extensive time representation
    // (compare TimeStamp in timer_internal_gathering.hh)
    struct TimeStats
    {
      clock_t   wall;
      clock_t   user;
      clock_t   system;
      clock_t   cpu;
      double    average;
      double    charge;

      TimeStats ();

      friend class misc::Timer;

    private:
      // Dump time in XML
      void dump (std::ostream& o,
                 const std::string& name) const;
    };

    // Data analysis structures
    struct GraphCall
    {
      // clear on init
      GraphCall ();

      void add_times (TimeStamp&                total,
                      TimeStamp&                self,
                      TimeStamp&                program,
                      unsigned int              cnt);

      void add_self_time (TimeStamp&            self,
                          unsigned int          cnt);

      void add_total_time (TimeStamp&           total,
                           unsigned int         cnt);

      void compute_average (clock_t             program_cpu);


      unsigned int      count;
      unsigned int      from;
      unsigned int      to;

      TimeStats         total;
      TimeStats         self;
    };

    struct GraphTask
    {
      // clear on init
      GraphTask ();

      void add_times (TimeStamp&                total,
                      TimeStamp&                self,
                      TimeStamp&                program,
                      unsigned int              cnt);

      void add_int_time (TimeStamp&             self,
                         unsigned int           cnt);

      void compute_average (clock_t             program_cpu);


      // Ordering using CPU time.
      bool operator< (const GraphTask& task) const;

      unsigned int      id;
      std::string       name;

      unsigned int      count;
      unsigned int      recursive_count;
      unsigned int      int_count;

      TimeStats         total;
      TimeStats         self;
    };

    struct GraphComponent
    {
      // clear on init
      GraphComponent ();

      void add_member (GraphTask&               task);

      void add_call_inc (GraphCall&             call);

      void add_call_out (GraphCall&             call);

      void add_call_internal (GraphCall&        call);

      void compute_average (clock_t             program_cpu);

      unsigned int      member_count;
      std::list<int>    members;

      std::list<GraphCall*> calls_in;
      std::list<GraphCall*> calls_out;

      unsigned int      out_calls;
      unsigned int      int_calls;
      unsigned int      calls;

      unsigned int      id;

      TimeStats         total;
      TimeStats         self;

      double            int_average;
    };

    typedef boost::adjacency_list<boost::vecS, boost::vecS,
                                  boost::bidirectionalS,
                                  GraphTask,
                                  GraphCall> output_graph;

    typedef std::pair<output_graph::vertex_iterator,
                      output_graph::vertex_iterator> vertex_range;
    typedef std::pair<output_graph::edge_iterator,
                      output_graph::edge_iterator> edge_range;
    typedef std::pair<output_graph::in_edge_iterator,
                      output_graph::in_edge_iterator> in_edge_range;
    typedef std::pair<output_graph::out_edge_iterator,
                      output_graph::out_edge_iterator> out_edge_range;
    typedef std::pair<output_graph::edge_iterator,
                      output_graph::edge_iterator> edge_range;

    typedef std::vector<int> component_id_vector;
    typedef std::vector<GraphComponent> component_vector;

    class VertexWriter
    {
    public:
      VertexWriter (const Timer&         timer,
                    const verbose_degree vd,
                    double               ccr);

      void operator() (std::ostream& out,
                       const output_graph::vertex_descriptor& v) const;
    private:
      const output_graph&        g_;
      const component_vector&    c_;
      const component_id_vector& c_id_;
      verbose_degree             vd_;
      double                     chrg_col_ratio_;
      clock_t                    tps_;
    };

    class EdgeWriter
    {
    public:
      EdgeWriter (const Timer&         timer,
                  const verbose_degree vd,
                  double               ccr);

      void operator() (std::ostream& out,
                       const output_graph::edge_descriptor& e) const;
    private:
      const output_graph&        g_;
      const component_id_vector& c_id_;
      verbose_degree             vd_;
      double                     chrg_col_ratio_;
      clock_t                    tps_;
    };

    class GraphWriter
    {
    public:
      GraphWriter (const Timer&         timer,
                   const verbose_degree vd,
                   double               ccr);

      void operator() (std::ostream& out) const;
    private:
      const output_graph&        g_;
      const component_vector&    c_;
      const component_id_vector& c_id_; 
      verbose_degree             vd_;
      double                     chrg_col_ratio_;
      clock_t                    tps_;
    };
  } // namespace timer
} // namespace misc

NAMESPACE_VCSN_END

// Include full definition of all classes.
# ifdef VAUCANSON
#  include <vaucanson/misc/timer.hh>
#  include <vaucanson/misc/timer_internal_graph.hh>
#  include <vaucanson/misc/timer_internal_gathering.hh>
# else
#  include "timer.hh"
#  include "timer_internal_graph.hh"
#  include "timer_internal_gathering.hh"
# endif

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  ifdef VAUCANSON
#   include <vaucanson/misc/timer_internal_graph.hxx>
#  else
#   include "timer_internal_graph.hxx"
#  endif
# endif // !VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_MISC_TIMER_INTERNAL_GRAPH_HH
