#ifndef IO_HH
# define IO_HH

# include <vaucanson/automata/concept/handlers.hh>
# include <iostream>
# include <string>

namespace vcsn
{

  namespace io
  {

    /*-------.
    | Output |
    `-------*/

    template<typename Auto, typename EdgeConverter, typename Format>
    struct automaton_saver_
    {
      typedef Auto automaton_t;
      typedef EdgeConverter edge_converter_t;
      typedef Format format_t;

      automaton_saver_(const Auto&, const EdgeConverter&, const Format&);

      automaton_t& automaton();
      const automaton_t& automaton() const;

    protected:
      const automaton_t& a_;
      edge_converter_t conv_;
      format_t format_;

      template<typename A, typename E, typename F>
      friend std::ostream& operator<<(std::ostream&, const automaton_saver_<A, E, F>&);
    };


    template<typename Auto, typename EdgeConverter, typename Format>
    std::ostream& operator<<(std::ostream&, const automaton_saver_<Auto, EdgeConverter, Format>&);

    struct string_out
    {
      template<typename A, typename T>
      std::string operator()(const A&, const T&) const;
    };

  }

  template<typename Auto, typename EdgeConverter, typename Format>
  io::automaton_saver_<Auto, EdgeConverter, Format> automaton_saver(const Auto&,
								    const EdgeConverter& e = EdgeConverter(),
								    const Format& f = Format());
    

  namespace io 
  {
    /*------.
    | Input |
    `------*/

    template<typename Auto, typename EdgeConverter, typename Format>
    struct automaton_loader_
    {
      typedef Auto automaton_t;
      typedef EdgeConverter edge_converter_t;
      typedef Format format_t;

      automaton_loader_(automaton_t& a,
			const edge_converter_t& conv,
			const format_t& format,
			bool merge_states);

      automaton_t& automaton();
      const automaton_t& automaton() const;

      hstate_t add_state(unsigned);
      void set_initial(unsigned, const std::string&);
      void set_initial(unsigned);
      void set_final(unsigned, const std::string&);
      void set_final(unsigned);
      void add_edge(unsigned, unsigned, const std::string&);
      void add_spontaneous(unsigned, unsigned);

    protected:
      automaton_t& a_;
      edge_converter_t conv_;
      format_t format_;
      unsigned scount_;
      std::map<unsigned, hstate_t> smap_;
      bool merge_states_;

      template<typename A, typename E, typename F>
      friend std::istream& operator>>(std::istream&, automaton_loader_<A, E, F>&);
    };

    template<typename Auto, typename EdgeConverter, typename Format>
    std::istream& operator>>(std::istream&, automaton_loader_<Auto, EdgeConverter, Format>&);


  }
  
  
  template<typename Auto, typename EdgeConverter, typename Format>
  io::automaton_loader_<Auto, EdgeConverter, Format> automaton_loader(Auto& a, 
								      const EdgeConverter& e = EdgeConverter(),
								      const Format& f = Format());
  


  

}

# include <vaucanson/tools/io.hxx>

#endif
