// timer.hh: this file is part of the CBS project.
//
// CBS, a C++ benchmarking suite.
//
// Copyright (C) 2007, 2009 The CBS Authors.
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

#ifndef BENCH_TIMER_HH
# define BENCH_TIMER_HH

/**
 *  \file src/timer.hh
 *  \brief Timing nested tasks.
 *
 *  NOTE: This file was originally part of Vaucanson.
 *        The documentation below may be incomplete.
 *
 *  The purpose of the class Timer provided here is to measure the
 *  time user-defined tasks use in the execution of a program.
 *
 *  Each task is identified by a unique name (std::string), or
 *  alternatively, once task has been declared, by an id number.
 *  Special characters in task names must be escaped for the XML export
 *  to work properly.
 *
 *  The program source code must be equipped with calls to methods of
 *  the Timer instance.
 *
 *  For the timing to be accurate, a task should take 1ms of execution
 *  time or more (preferably over 10ms).
 *
 *  Once all the relevant timing data are gathered, the Timer object
 *  builds a graph of the results (using the boost graph library),
 *  which can be printed to a stream or exported in DOT format.
 *  Alternatively, export of the complete results in XML format for
 *  further analysis will be made available.
 *
 *
 *
 *  How to use this timer in Vaucauson (taf-kit):
 *
 *      A global timer is declared in taf-kit/src/common.hh.
 *      See misc/global_timer.hh for a list of commands on the global
 *      timer (using macro definitions).
 *
 *      Refer to the description of the class's methods below.
 *
 *      The global timer is automatically started and stopped in
 *      taf-kit/tests/vcsn* programs.  Only the source code of
 *      automata manipulation algorithm has to be equipped with
 *      declaration an execution of tasks (using TIMER_SCOPED(Task)
 *      alone or TIMER_PUSH(Task) and TIMER_POP() together).
 *
 *      To obtain a detailed report of the results on std::cerr, use
 *      the command-line option --report-time (results are not printed
 *      otherwise). This option takes an optional int argument as the
 *      verbose degree of the report (from 1 to 3, default 2)
 *
 *      To export the graph of the timing results in DOT format on
 *      std::cerr, use the command-line option --export-time-dot.
 *      This option takes an optional int argument as the
 *      verbose degree of the graph (from 0 to 3, default 2)
 *
 *      To dump the timer in XML format on std::cerr, use the
 *      command-line option --export-time-xml.
 *
 *      To benchmark several executions of the same set of tasks, use
 *      the command-line option --bench=X where X is the number of
 *      iterations.  A summary of the results is printed on std::cerr.
 *
 *
 *  How to use this timer outside Vaucanson:
 *
 *      - Create an instance of Timer.
 *
 *      - Before the beginning of the sequence of tasks (which can be
 *        nested), insert a call to Timer.start ().
 *        This will initialize the timer, discarding any previous
 *        data.  The special task _program_ will be initialized here.
 *        This task computes the total time of the program: Do not
 *        use it elsewhere.
 *
 *      - Declare and execute tasks.  The data gathering process is
 *        based on a stack (comparable to a system call stack): use
 *        push () and pop () methods accordingly.
 *
 *        There are two ways to refer to a given task:
 *
 *              - Its unique name can be passed to every function
 *                requiring it (as in Timer.push ("MyTask")).  This
 *                leads to a map lookup which can be costly with
 *                a large number of tasks.
 *
 *              - It can be declared using Timer.task ("MyTask"). This
 *                method returns the task's id (creating the task in
 *                the process if it doesn't exist).  This id is an int
 *                and can be used in place of the task's full name.  It
 *                removes the map lookup, thus decreasing the
 *                influence of the timer's data gathering on the
 *                program.
 *
 *        There are two ways to time a task:
 *
 *              - Calls can be explicitely made to Timer.push (Task)
 *                and Timer.pop ().  Tasks may be nested, recursive,
 *                and may form cycles e.g. A -> B -> A.
 *                Only the task started last can be stopped.
 *                Timer.pop (Task) fails if the Task is not the task
 *                on top of the timer's internal stack.
 *
 *              - A class ScopedTimer (Timer, Task) is provided.
 *                It simply calls Timer.push (Task) upon creation
 *                and Timer.pop () upon destruction. Instanciate it in
 *                a scope, i.e. at the beginning of a function.
 *
 *      - After the part of the program to be timed, insert a call to
 *        Timer.stop ().  This computes the data into a graph.  The
 *        timer can't be resumed.
 *
 *      * Once stopped, standard arithmetic operators (+, +=, /, /=)
 *        can be used on timers, e.g. to calculate the mean of several
 *        iterations of the same program.  The structure of timers
 *        added to each other must be strictly identical (same
 *        function calls).
 *        A Timer.join () method might appear in the future.
 *
 *      - Print the results using Timer.print (Stream,
 *        VerboseDegree).  VerboseDegree represents the amount of
 *        information printed.  Available VerboseDegree values are:
 *          timer::VERBOSE_NONE
 *          timer::VERBOSE_MINIMAL
 *          timer::VERBOSE_NORMAL (Default)
 *          timer::VERBOSE_MAXIMAL
 *
 *      * In this report, task names can be truncated to fit the
 *        layout.  See the description of the report's fields below.
 *
 *      - Export the results in DOT format using Timer.export(Stream,
 *        VerboseDegree, ChargeColorRatio).  VerboseDegree is the same
 *        as above.  ChargeColorRatio controls the adjustement of the
 *        graph node colors to the task's self charge.  The node color
 *        ranges from cyan to red.  Increasing ChargeColorRatio
 *        makes nodes attain red for lower charges.  This is for fine
 *        tuning, as the color is internally adjusted to the number of
 *        tasks.  Default value for ChargeColorRatio is 1.0.
 *
 *      - Subsequent calls to Timer.start () would initialize the
 *        timer, thus allowing the same timer to time different sets
 *        of tasks in a row (results are discarded upon calling
 *        Timer.start ()).
 *
 *
 *
 *  Note on performance:
 *
 *  The data gathering process is generally non-obtrusive
 *  (timing one task by its id takes about 1 extra microsecond).
 *  However, for a large number of small tasks, using only full name
 *  lookup may impact the results.
 *
 *
 *  Documentation for the standard report:
 *
 *  The report obtained using Timer.print () is 80 columns wide.
 *  Task names are truncated to fit.  Times are reported in the most
 *  accurate unit (among hours, minutes, seconds, and milliseconds),
 *  except in the task list where the same unit is shared between all
 *  tasks' total and self times.
 *
 *  Task list:
 *    - charge: Percentage of the total program time the task has
 *      taken by itself.
 *    - total: Total time spent in the task and its children.  If the
 *      task is part of a cycle (total time is irrelevant), the cycle
 *      id is printed there.
 *    - self: Time spent in the task itself.
 *    - calls: Total number of calls to the task, including recursive
 *      calls
 *    - self avg.: Average time spent in the task itself per call.
 *    - total avg.: Average time a call to the task takes to return.
 *      If the task is part of a cycle (total time is irrelevant), the cycle
 *      id is printed there.
 *
 *  Call graph (VERBOSE_NORMAL or higer):
 *
 *  Cycles:
 *    - charge: percentage of the program time spent in the cycle/task.
 *    - total: total time spent in the cycle and the external tasks it
 *      called.
 *    - self: time spend in the cycle/task itself.
 *    - calls:e/i: (e) Calls to the cycle/task from outside the cycle.
 *                 (i) Calls to the cycle/task from inside the cycle.
 *    - int avg.: (cycle) Average time spent in a member per internal
 *                        call.
 *                (task) Average time spent in the task itself per call.
 *    - self avg.: Average time spent in the cycle itself per call
 *      from outside.
 *    - total avg.: (cycle) Average time a call to the cycle from outside
 *                          takes to return.
 *                  (task) Task name is printed here.
 *
 *  Tasks:
 *    This section lists each task, as well as its incoming and
 *    outgoing calls.  Incoming calls are listed above the task (D:
 *    <-), while outgoing calls are listed below (D: ->).
 *
 *    - Incoming calls:
 *        - name: Name of the caller.
 *        - charge: Percentage of the called task's charge caused by the
 *          call.
 *        - self: Part of the called task's self time caused by the call.
 *        - calls: Number of calls from this caller.
 *        - self avg.: Average time spend in the called task per call
 *          from this caller.
 *
 *    - Task:
 *      See Task list.
 *
 *    - Outgoing calls:
 *        - name: Name of the called task.
 *        - charge: Percentage of the called task's charge caused by
 *          the call.
 *        - self: Part of the called task's self time caused by the call.
 *        - calls: Number of calls to this task.
 *        - self avg.: Average time spend in the called task per call.
 *
 *    Note: Recursive calls are listed both in incoming and outgoing
 *    calls.
 *
 *
 *  Detailed tasks (VERBOSE_MAXIMAL):
 *
 *    Each task is listed here with its gathered data.
 *
 *    Self time refers to the time spent in the task itself.
 *    Total time refers to the time spent in the task and its
 *    children.
 *
 *    All times are in clock ticks.
 *
 *    User time is the time spent in user code.
 *    System time is the time spent in system calls.
 *    Cpu time is the total time the cpu spent in the program.  It is
 *    the value used in the previous parts of the report.
 *    Wall time is the real time spent in the task, i.e. the time
 *    observed by the user on a wall clock.
 */

// STL
# include <stack>
# include <map>
# include <list>
# include <string>
# include <iosfwd>
# include <cassert>

// Boost
# include <boost/graph/adjacency_list.hpp>
# include <boost/graph/strong_components.hpp>
# include <boost/graph/graphviz.hpp>

// Internal
# include <cbs/bench/internal/timer_gathering.hh>
# include <cbs/bench/internal/timer_graph.hh>

namespace timer
{
  /// Provide a way to time nested tasks and export their call graph.
  class Timer;

  /// Allow the timing of a task within a scope.
  class ScopedTimer
  {
  public:
    /// Start timing a new task upon creation.
    /// \param timer    the timer within which the task is executed.
    /// \param i        the id of the task in the timer (must be declared).
    ScopedTimer (Timer& timer, const unsigned int i);

    /// Start timing a new task upon creation.
    /// \param timer    the timer within which the task is executed.
    /// \param name     the name of the task in the timer (does not
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

    /// Gather system information (clock ticks per second) upon creation.
    Timer ();
    /// Copy a timer.  It is not recommended to copy a running timer.
    /// \param rhs      the timer to be duplicated.
    Timer (const Timer& rhs);

    ~Timer ();

    /// Make this timer a copy of the timer.  It is not recommended to
    /// duplicate a running timer.
    /// \param rhs      the timer to be duplicated.
    const Timer& operator= (const Timer& rhs);

    /// Return the id associated to the unique task name provided if
    /// the association exists.  Otherwise, create the association and
    /// return its id.
    /// The timer has to be running.
    /// \param name     the task name.
    unsigned int task (const std::string& name);

    /// Return the name of the current task.
    /// The timer has to be running.
    std::string current_task () const;

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
    std::ostream& print (std::ostream& o,
                         timer::verbose_degree vd = timer::VERBOSE_NORMAL)
      const;

    /// Export the task graph in dot format. The timer must have been stopped.
    /// \param o the output stream.
    /// \param vd determines the amount of information in the output
    /// graph.
    /// \param ccr adjusts how much the task self charge affects the
    /// node color
    std::ostream& export_dot (std::ostream&         o,
                              timer::verbose_degree vd = timer::VERBOSE_NORMAL,
                              double                ccr = 1) const;

    /// Dump the task graph in XML format for post-processing.
    /// All the information gathered is printed and include a large
    /// amount of redundancy.
    /// The Timer must be stopped.
    std::ostream& dump (std::ostream& o) const;

    /// Start a sub-timer for a task using an unique string identifier
    /// (the task doesn't have to be declared beforehand).
    /// The timer must be running.
    void push (const std::string& name);

    /// Start a sub-timer for a task using its id number (which must
    /// be declared beforehand).
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

    /// Return the measured cpu time, in ms.
    /// Includes cpu time for the current process and its children
    /// (started and terminated while the timer was running).
    /// The time is recorded after the timer has been stopped.
    long time () const;

    /// Return the measured user time, in ms.
    /// The time is recorded after the timer has been stopped.
    long time_user () const;

    /// Return the measured system time, in ms.
    /// The time is recorded after the timer has been stopped.
    long time_system () const;

    /// Return the measured user time in terminated children processes, in ms.
    /// The time is recorded after the timer has been stopped.
    long time_children_user () const;

    /// Return the measured system time in terminated children processes, in ms.
    /// The time is recorded after the timer has been stopped.
    long time_children_system () const;

    /// Return the measured wall clock (observed) time, in ms.
    /// The time is recorded after the timer has been stopped.
    long time_wall () const;

    /// Return the total number of measures made.
    /// Recorded after the timer has been stopped.
    unsigned total_calls () const;

    /// \brief Comparison between two Timers.
    /// This operator enables the use of std::min and std::max.
    /// It checks only the \a total cpu time, so it's a strict weak ordering.
    bool operator< (const Timer& rhs) const;

    /// \brief Accumulate another timer.
    /// The two timers _must_ have the _exact same structure_ (ie: tasks
    /// defined and executed in the same order) and _must not_ be
    /// running.
    /// Alternatively, this timer can be empty (just initialized or cleared)
    /// Call counts are accumulated as well as measured times.
    /// Average values are updated.
    Timer& operator+= (const Timer& rhs);

    /// \brief Sum two timers
    /// The two timers _must_ have the _exact same structure_ (ie: tasks
    /// defined and executed in the same order) and _must not_ be
    /// running.
    /// Call counts are accumulated as well as measured times.
    /// Average values are updated.
    Timer operator+ (const Timer& rhs);

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
    /*------------------------------.
    | Timer: Internal structures.   |
    `------------------------------*/

    // Graph output writers
    friend class timer::GraphWriter;
    friend class timer::VertexWriter;
    friend class timer::EdgeWriter;

    // Add task vertices and call edges to the graph
    void build_output_graph ();
    // Build connected component array
    void build_connected_components ();

    // Compute task & call times in graph
    void compute_output_graph ();
    // Compute component times in graph
    void compute_connected_components ();

    void print_output_graph (std::ostream& o,
                             timer::verbose_degree vd = timer::VERBOSE_NORMAL)
      const;

    timer::call_stack           calls_;
    timer::task_vector          tasks_;
    timer::task_names_map       names_;
    timer::TimeStamp            time_;
    timer::TimeStamp            last_time_;

    timer::output_graph         graph_;
    timer::component_id_vector  comp_id_;
    timer::component_vector     comp_;
    unsigned int                comp_count_;
    unsigned int                task_count_;
    unsigned int                total_calls_;

    bool                        is_running_;

    bool                        cleared_;

  };
} // namespace timer

# include <cbs/bench/timer.hxx>

#endif // !BENCH_TIMER_HH
