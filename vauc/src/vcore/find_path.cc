#include <map>
#include <set>
#include <vcore/env.hh>
#include <vcore/exception.hh>
#include <limits>
#include <set>

namespace vcsn
{
  namespace vauc
  {

// #ifndef DEBUG
// #define DEBUG 1
// #endif

#ifdef DEBUG
#define d(x) do { std::cerr << x << std::endl; } while(0)
#else
#define d(x)
#endif

    typedef std::pair<unsigned, Callable> mat_value_t;

    class Composition : public FunctionImpl
    {
    public:
      virtual const sig_t& signature() const
      {
	return _inside.signature();
      }
      virtual std::string return_type(const sig_t& sig) const
      {
	return "";
      }
      virtual const std::string& description() const
      {
	return _description;
      }

      virtual const std::string& origin() const
      {
	return _origin;
      }
      virtual ~Composition() {}

      Composition(Callable in, Callable out)
	: _inside(in), _outside(out),
	  _origin("<composition for conversions>")
      {
// 	_description = '(' + out.description() 
// 	  + ") o (" + in.description() + ')';
      }

      virtual Object call(Env& context,
			  const std::vector<Object>& args) const
      {
	std::vector<Object> inter_args;
	inter_args.push_back(_inside.call(context, args));
	if (inter_args[0].cpp_type().name() != 
	    *_outside.signature().begin())
	  RAISE("converting", \
		std::string("converter from ") \
		+ inter_args[0].cpp_type().name() \
		+ " to " + *_outside.signature().end() \
		+ " is not honest");
	return _outside.call(context, inter_args);
      }

    protected:
      Callable _inside;
      Callable _outside;
      std::string _origin;
      std::string _description;
    };

    static Callable compose_callables(Callable in, Callable out)
    {
      return Callable(new Composition(in, out));
    }

    typedef Symbol vertex_t;
    typedef std::map<vertex_t, unsigned> d_t;
    typedef std::map<vertex_t, vertex_t> pi_t;
    static const unsigned max = std::numeric_limits<unsigned>::max();
    typedef Env g_t;
    typedef Env::type_map_t::const_iterator vertices_iterator;
    
    static inline vertices_iterator vertices_begin(const g_t& g)
    {
      return g.type_map().begin();
    }
    static inline vertices_iterator vertices_end(const g_t& g)
    {
      return g.type_map().end();
    }
    static inline const vertex_t& vertice(const vertices_iterator& i)
    {
      return i->first;
    }

    static inline unsigned weight(const g_t& g, const vertex_t& from, const vertex_t& to)
    {
      const Env::converters_map_t& c = g.converters();
      Env::converters_map_t::const_iterator i = c.find(std::make_pair(from, to));
      if (i != c.end())
	return i->second.first;
      return max;
    }
     
    static inline bool edge_exists(const g_t& g, const vertex_t& from, const vertex_t& to)
    {
      const Env::converters_map_t& c = g.converters();
      Env::converters_map_t::const_iterator i = c.find(std::make_pair(from, to));
      return (i != c.end());
    }
 
    template<typename Graph>
    static void initialize_single_source(d_t& d, pi_t& pi, const vertex_t& s, const Graph& g)
    {
//       for (vertices_iterator i = vertices_begin(g);
// 	   i != vertices_end(g);
// 	   ++i)
// 	d[vertice(i)] = max;
      d[s] = 0;
    }

    template<typename Graph>
    static void relax(d_t& d, pi_t& pi, const Graph& g, const vertex_t& u, const vertex_t& v)
    {

      unsigned dv, du;

      {
	d_t::const_iterator di = d.find(v);
	if (di == d.end())
	  dv = max;
	else
	  dv = di->second;
      }

      {
	d_t::const_iterator di = d.find(u);
	if (di == d.end())
	  du = max;
	else
	  du = di->second;
      }

      unsigned wuv = weight(g, u, v);
      unsigned sum = du + wuv;

      d("-- relaxing from u = " << u << " to v = " << v);
      d("d[u] = " << du << ", d[v] = " << dv << ", w(u,v) = " << wuv);
      
      if (sum < du || sum < wuv)
	sum = max;

      d("d[u] + w(u,v) = " << sum);

      if (dv > sum)
	{
	  d("d[v] > d[u] + w(u,v)");
	  d[v] = sum;
	  pi.erase(v);
	  pi.insert(pi_t::value_type(v, u));
	  d("pi[v] = " << pi.find(v)->second);
	}
      d("** d[u] = " << du << ", d[v] = " << dv);
    }

    static mat_value_t rec_back_find(const Env::converters_map_t& m, 
			 const pi_t& pi, 
			 const vertex_t& from, 
			 const vertex_t& level,
			 const vertex_t& back)
    {
      Env::converters_map_t::const_iterator c = m.find(std::make_pair(level, back));
      d("found converter from from " << level << " to " << back);
      mat_value_t r;
      r.first = c->second.first; r.second = c->second.second;

      if (from != level) {
	  mat_value_t rec_r = rec_back_find(m, pi, from, pi.find(level)->second, level);
	  r.first += rec_r.first;
	  r.second = compose_callables(rec_r.second, r.second);
      }
      return r;
    }	  

    static inline mat_value_t back_find(const g_t& g, 
					const pi_t& pi, 
					const vertex_t& from, 
					const vertex_t& to)
    {
      const Env::converters_map_t& m = g.converters();
      d("-- attempting to reach " << to);
      return rec_back_find(m, pi, from, pi.find(to)->second, to);
    }


    template<typename Graph>
    static mat_value_t dijkstra(const Graph& g, const vertex_t& s, const vertex_t& to)
    {
      d_t d;
      pi_t pi;

      std::set<vertex_t> Q;
      for (vertices_iterator i = vertices_begin(g);
	   i != vertices_end(g);
	   ++i)
	Q.insert(vertice(i));

      d("-- dijkstra init --");
      d("there are " << Q.size() << " types.");

      initialize_single_source(d, pi, s, g);
      while (Q.size() != 0)
	{
	  d(">> entering loop, #Q = " << Q.size());
	  unsigned min = max;
	  const vertex_t *u = 0;
	  d("-- looking for minimum state");
	  for (std::set<vertex_t>::const_iterator i = Q.begin();
	       i != Q.end();
	       ++i)
	    {
	      unsigned di;
	      {
		d_t::const_iterator dit = d.find(*i);
		if (dit == d.end())
		  continue;
		di = dit->second;
	      }
	      d("- studying state " << *i << " which has value " << di);
	      if (di < min)
		{
		  d("lower than minimum " << min);
		  u = &(*i);
		  min = di;
		}
	      d("lower state is " << (u ? u->name() : "none"));
	    }
	  if (!u)
	    u = &(*Q.begin());
	  vertex_t _u = *u;
	  Q.erase(_u);
	  
	  for (vertices_iterator v = vertices_begin(g);
	       v != vertices_end(g);
	       ++v)
	    if (edge_exists(g, _u, vertice(v)))
	      relax(d, pi, g, _u, vertice(v));
	}
      if (pi.find(to) == pi.end())
	return mat_value_t(max, Callable());
      return back_find(g, pi, s, to);
    }

    mat_value_t Env::find_path(Symbol from, Symbol to) const
    {
      return dijkstra(*this, from, to);
    }

  }
}


	  
      

