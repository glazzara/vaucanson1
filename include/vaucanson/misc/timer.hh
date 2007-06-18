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

#ifndef VCSN_MISC_TIMER_HH
# define VCSN_MISC_TIMER_HH

/**
 ** \file misc/timer.hh
 ** \brief Timer: Timing nested tasks.
 */

# include <stack>
# include <map>
# include <list>
# include <string>
# include <iosfwd>
# include <boost/graph/adjacency_list.hpp>
# include <boost/graph/strong_components.hpp>
# include <boost/graph/graphviz.hpp>

# define VAUCANSON 1

# if defined VAUCANSON
#  define NAMESPACE_VCSN_BEGIN namespace vcsn {
#  define NAMESPACE_VCSN_END   } // namespace vcsn
#  include <vaucanson/misc/contract.hh>
# else
#  define NAMESPACE_VCSN_BEGIN
#  define NAMESPACE_VCSN_END
#  include <cassert>
#  define precondition(C) assert(C)
# endif


NAMESPACE_VCSN_BEGIN

namespace misc
{
  /// Provide a way to time nested tasks and export their call graph.
  class Timer;

  /// Allow the timing of a task within a scope.
  class ScopedTimer
  {
  public:
    /// Start timing a new task upon creation.
    /// \param timer	the timer within which the task is executed.
    /// \param i	the id of the task in the timer (must be declared).
    ScopedTimer (Timer& timer, const unsigned int i);

    /// Start timing a new task upon creation.
    /// \param timer	the timer within which the task is executed.
    /// \param name	the name of the task in the timer (does not
    /// have to be declared yet).
    ScopedTimer (Timer& timer, const std::string& name);
  
    /// Upon destruction, stop the task on top of the timer's stack.
    /// It is _not_ guaranteed this task is the one started upon creation.
    ~ScopedTimer ();
  private:
    Timer* timer_;
  };

  class Timer
  {
  public:
    /// Enumerate the different verbose degrees for dot format graph export.
    typedef enum verbose_degree { VERBOSE_NONE, VERBOSE_MINIMAL,
				  VERBOSE_NORMAL, VERBOSE_MAXIMAL };

    /// Gather system information (clock ticks per second) upon creation.
    Timer ();
    /// Copy a timer.  It is not recommended to copy a running timer.
    /// \param rhs	the timer to be duplicated.
    Timer (const Timer& rhs);

    ~Timer ();

    /// Make this timer a copy of the timer.  It is not recommended to
    /// duplicate a running timer.
    /// \param rhs	the timer to be duplicated.
    const Timer& operator= (const Timer& rhs);

    /// Return the id associated to the unique task name provided if
    /// the association exists.  Otherwise, create the association and
    /// return its id.
    /// The timer has to be running.
    /// \param name	the task name.
    unsigned int task (const std::string& name);

    /// Clear any data in the timer (task names associations and
    /// results) and start the data gathering process (the timer is
    /// now running).
    void start ();

    /// Stop the data gathering process and compute results into a
    /// graph that can be exported in dot format (the timer is stopped).
    void stop ();

    /// Clear any data in the timer (task names associations and
    /// results).
    void clear ();

    /// Write a summary of the results. The timer must have been stopped.
    /// \param o the output stream.
    /// \param vd determines the amount of information printed
    std::ostream& print (std::ostream&  o,
			 verbose_degree vd = VERBOSE_NORMAL) const;

    /// Export the task graph in dot format. The timer must have been stopped.
    /// \param o the output stream.
    /// \param vd determines the amount of information in the output
    /// graph.
    /// \param ccr adjusts how much the task self charge affects the
    /// node color
    std::ostream& export_dot (std::ostream&  o,
			      verbose_degree vd = VERBOSE_NORMAL,
			      double         ccr = 1) const;

    /// Start a sub-timer for a task using an unique string identifier
    /// (the task doesn't have to be declared beforehand).
    /// The timer must be running.
    void push (const std::string& name);

    // Start a sub-timer for a task using its id number (which must
    // be declared beforehand).
    /// The timer must be running.
    void push (const unsigned int i);

    /// Stop the named task.
    /// The timer must be running.
    void pop (const std::string& task_name);

    /// \see pop (), pop (const std::string name)
    /// The timer must be running.
    void pop (const unsigned int i);

    /// Stop the current task's timer (the last task pushed).
    /// The timer must be running.
    void pop ();

    /// \brief Comparison between two Timers.
    /// This operator enables the use of std::min and std::max.
    /// It checks only the \a total cpu time, so it's a strict weak ordering.
    bool operator< (const Timer& rhs) const;

    /// \brief Accumulate another timer.
    /// The two timers _must_ have the _exact same structure_ (ie: tasks
    /// defined and executed in the same order) and _must not_ be
    /// running.
    /// Alternatively, this timer can be empty (just initialized or cleared)
    /// Only the measured times are stacked (not call counts).
    /// Average values are updated.
    Timer& operator+= (const Timer& rhs);

    /// \brief Divide in place.
    /// Typically used to compute the mean of several timers.
    /// The timer _must not_ be running.
    /// Average values are updated.
    Timer& operator/= (unsigned rhs);

    /// \brief Divide.
    /// Typically used to compute the mean of several timers.
    /// The timer _must not_ be running.
    /// Average values are updated.
    Timer operator/ (unsigned rhs) const;

  private:
    // Internal Time representation
    class TimeStamp;


    // Data collection classes
    class Task;
    class Call;
    class StackedCall;

    // Graph output writers
    friend class GraphWriter;
    friend class VertexWriter;
    friend class EdgeWriter;

    // Data analysis structures
    struct GraphCall
    {
      // clear on init
      GraphCall();

      void add_times(TimeStamp&		total,
		     TimeStamp&		self,
		     TimeStamp&		program,
		     unsigned int	cnt);

      void add_self_time(TimeStamp&		self,
			 unsigned int		cnt);

      void add_total_time(TimeStamp&		total,
			  unsigned int		cnt);

      void compute_average(clock_t		program_cpu);


      unsigned int	count;
      unsigned int	from;
      unsigned int	to;

      clock_t	total_wall;
      clock_t	total_user;
      clock_t	total_system;
      clock_t	total_cpu;
      double	total_average;
      double	total_charge;

      clock_t	self_wall;
      clock_t	self_user;
      clock_t	self_system;
      clock_t	self_cpu;
      double	self_average;
      double	self_charge;
    };

    struct GraphTask
    {
      // clear on init
      GraphTask();

      void add_times(TimeStamp&		total,
		     TimeStamp&		self,
		     TimeStamp&		program,
		     unsigned int	cnt);

      void add_int_time(TimeStamp&		self,
			 unsigned int		cnt);

      /*      void add_total_time(TimeStamp&		total,
	      unsigned int		cnt);*/

      void compute_average(clock_t		program_cpu);


      // Ordering using CPU time.
      bool operator < (const GraphTask& task) const;

      unsigned int	id;
      std::string	name;

      unsigned int	count;
      unsigned int	recursive_count;
      unsigned int	int_count;

      clock_t	total_wall;
      clock_t	total_user;
      clock_t	total_system;
      clock_t	total_cpu;
      double	total_average;
      double	total_charge;

      clock_t	self_wall;
      clock_t	self_user;
      clock_t	self_system;
      clock_t	self_cpu;
      double	self_average;
      double	self_charge;
    };

    struct GraphComponent
    {
      // clear on init
      GraphComponent ();

      void add_member(GraphTask&	task);

      void add_call_inc(GraphCall&	call);

      void add_call_out(GraphCall&	call);

      void add_call_internal(GraphCall&	call);

      void compute_average(clock_t	program_cpu);

      unsigned int	member_count;
      std::list<int>	members;

      std::list<GraphCall*> calls_in;
      std::list<GraphCall*> calls_out;

      unsigned int	out_calls;
      unsigned int	int_calls;
      unsigned int	calls;

      unsigned int	id;

      clock_t	total_wall;
      clock_t	total_user;
      clock_t	total_system;
      clock_t	total_cpu;
      double	total_average;
      double	total_charge;

      clock_t	self_wall;
      clock_t	self_user;
      clock_t	self_system;
      clock_t	self_cpu;
      double	self_average;
      double	self_charge;

      double	int_average;
    };



    typedef std::map<const std::string, int> task_names_map;
    typedef std::vector<Task> task_vector;
    typedef std::map<int, Call> call_map;
    typedef std::stack<StackedCall> call_stack;

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

    typedef std::vector<int> component_id_vector;
    typedef std::vector<GraphComponent> component_vector;


    class VertexWriter {
    public:
      VertexWriter (const Timer& timer,
		    const	 verbose_degree vd,
		    double       ccr);

      void operator()(std::ostream& out,
		      const output_graph::vertex_descriptor& v) const;
    private:
      const output_graph&	 g_;
      const component_vector&    c_;
      const component_id_vector& c_id_;
      verbose_degree             vd_;
      double                     chrg_col_ratio_;
      clock_t			 tps_;
    };

    class EdgeWriter {
    public:
      EdgeWriter (const Timer&         timer,
		  const verbose_degree vd,
		  double               ccr);

      void operator()(std::ostream& out,
		      const output_graph::edge_descriptor& e) const;
    private:
      verbose_degree             vd_;
      const output_graph&        g_;
      const component_id_vector& c_id_;
      double                     chrg_col_ratio_;
      clock_t		         tps_;
    };

    class GraphWriter {
    public:
      GraphWriter (const Timer&         timer,
		   const verbose_degree vd,
		   double               ccr);

      void operator()(std::ostream& out) const;
    private:
      verbose_degree             vd_;
      const output_graph&        g_;
      const component_vector&    c_;
      const component_id_vector& c_id_;
      double                     chrg_col_ratio_;
      clock_t			 tps_;
    };

    class TimeStamp
    {
      friend class Timer;

      TimeStamp ();

      // Set to the current time
      void set_to_now ();

      // Set to the difference between the current time and the time
      // previously set.time_.set_to_lap();
      void set_to_lap ();

      // Set internal values to 0;
      void clear ();

      std::ostream& print (std::ostream& o) const;

      TimeStamp& operator += (const TimeStamp& rhs);
      TimeStamp& operator -= (const TimeStamp& rhs);

      // Returns the divison of the total CPU time by n
      double operator/ (unsigned int n) const;

      // Ordering using CPU time.
      bool operator < (const TimeStamp& rhs) const;

    private:
      clock_t	wall_;
      clock_t	user_;
      clock_t	sys_;
    };

    // Data collection classes
    class Task
    {
    public:
      friend class Timer;

      Task ();

      Task (const Task& task);

      // Create a new task.
      Task (const std::string&	name,
	    const unsigned int	id);

      // Free call list upon destruction.
      ~Task ();

      // Add the call if it doesn't exist.  Return the call to the
      // called task.
      Call& call (unsigned int called);

    private:
      std::string	name_;
      unsigned int	id_;
      call_map		calls_;
    };

    class Call
    {
    public:
      friend class Timer;
      friend class Task;

      // Initialize upon creation.
      Call (unsigned int called = 0);

      // Sum up the call stats;
      Call& operator += (const Call& call);

    private:
      // Adds the calculated time of a task instance to the associated
      // call on Timer::pop()
      void add(const StackedCall&	call);


      // Total time of the called task and its children.
      TimeStamp total_;

      // Time of the called task itself only.
      TimeStamp self_;

      // Number of calls with the same calling and called tasks.
      unsigned int count_;

      unsigned int called_;
    };

    class StackedCall
    {
    public:
      friend class Timer;
      friend class Task;
      friend class Call;

      StackedCall (unsigned int called = 0);
      StackedCall ();

    private:
      TimeStamp    total_;
      TimeStamp    children_;

      unsigned int called_;
    };

    clock_t		ticks_per_sec_;

    call_stack		calls_;
    task_vector		tasks_;
    task_names_map	names_;
    TimeStamp		time_;

    // Add task vertices and call edges to the graph
    void build_output_graph ();
    // Build connected component array
    void build_connected_components();

    // Compute task & call times in graph
    void compute_output_graph ();
    // Compute component times in graph
    void compute_connected_components ();

    void print_output_graph (std::ostream& o,
			     verbose_degree vd = VERBOSE_NORMAL) const;

    output_graph	graph_;
    component_id_vector comp_id_;
    component_vector	comp_;
    unsigned int	comp_count_;
    unsigned int	task_count_;

    bool		is_running_;

    bool		cleared_;
  };
} // namespace misc

NAMESPACE_VCSN_END

# if !defined VCSN_USE_INTERFACE_ONLY || defined VCSN_USE_LIB
#  /*include <vaucanson/misc/timer.hxx>*/
#  if defined VAUCANSON
#   include <vaucanson/misc/timer.cc>
#  endif
# endif // !VCSN_USE_INTERFACE_ONLY

#endif // !VCSN_MISC_TIMER_HH
