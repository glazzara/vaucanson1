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

    static inline unsigned semiring_elt(const g_t& g, const vertex_t& from, const vertex_t& to)
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
      for (vertices_iterator i = vertices_begin(g);
	   i != vertices_end(g);
	   ++i)
	d[vertice(i)] = max;
      d[s] = 0;
    }

    template<typename Graph>
    static void relax(d_t& d, pi_t& pi, const Graph& g, const vertex_t& u, const vertex_t& v)
    {

      unsigned dv = d[v];
      unsigned du = d[u];
      unsigned wuv = semiring_elt(g, u, v);
      unsigned sum = du + wuv;

      d("-- relaxing from u = " << u << " to v = " << v);
      d("d[u] = " << d[u] << ", d[v] = " << d[v] << ", w(u,v) = " << wuv);
      
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
      d("** d[u] = " << d[u] << ", d[v] = " << d[v]);
    }

    static unsigned rec_back_find(const Env::converters_map_t& m, 
			 const pi_t& pi, 
			 const vertex_t& from, 
			 const vertex_t& level,
			 const vertex_t& back)
    {
      unsigned r = 0;
      if (from != level) {
	  r = rec_back_find(m, pi, from, pi.find(level)->second, level);
	}
      d("converting from " << level << " to " << back);
      Env::converters_map_t::const_iterator c = m.find(std::make_pair(level, back));
      assert(c != m.end());
      return r + c->second.first;
    }	  

    static inline unsigned back_find(const g_t& g, const pi_t& pi, 
				     const vertex_t& from, 
				     const vertex_t& to)
    {
      const Env::converters_map_t& m = g.converters();
      d("-- attempting to reach " << to);
      return rec_back_find(m, pi, from, pi.find(to)->second, to);
    }


    template<typename Graph>
    unsigned dijkstra(const Graph& g, const vertex_t& s, const vertex_t& to)
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
	      d("- studying state " << *i << " which has value " << d[*i]);
	      if (d[*i] < min)
		{
		  d("lower than minimum " << min);
		  u = &(*i);
		  min = d[*i];
		}
	      d("lower state is " << (u ? u->name() : "none"));
	    }
	  if (!u)
	    u = &(*Q.begin());
          d("end of search, lower state is " << u->name() \
	    << " with value " << d[*u]);
	  vertex_t _u = *u;
	  Q.erase(_u);
	  
	  for (vertices_iterator v = vertices_begin(g);
	       v != vertices_end(g);
	       ++v)
	    if (edge_exists(g, _u, vertice(v)))
	      relax(d, pi, g, _u, vertice(v));
	}
      if (pi.find(to) == pi.end())
	return max;
      return back_find(g, pi, s, to);
    }

    unsigned Env::do_find_cost(Symbol from, Symbol to) const
    {
      return dijkstra(*this, from, to);
    }

  }
}


	  
      

