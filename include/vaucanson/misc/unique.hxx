#ifndef UTILITY_UNIQUE_HXX
# define UTILITY_UNIQUE_HXX

#include <vaucanson/misc/unique.hh>


namespace utility
{

  namespace unique
  {
    template<typename T>
    unsigned hash<T>::operator()(const T&) const
    { return 0; }

    template<typename T, unsigned hash_size>
    const T& hashmap<T, hash_size>::get_or_insert(const T& v)
    {
      unsigned key = hash<T>()(v) % hash_size;
      
      for (typename std::list<T>::const_iterator i = vec_[key].begin();
	   i != vec_[key].end();
	   ++i)
	if (*i == v)
	  return *i;
      vec_[key].push_front(v);
      return vec_[key].front();
    } 

    template<typename T, unsigned hash_size>
    hashmap<T, hash_size>::~hashmap()
    {}

    unique_map::ti_slot::ti_slot(const std::type_info& _id)
      : id(_id) {}
    bool unique_map::ti_slot::operator==(const unique_map::ti_slot& other) const
    { return id == other.id; }
    bool unique_map::ti_slot::operator<(const unique_map::ti_slot& other) const
    { return id.before(other.id); }


    template<typename T>
    const T& get(const T& v)
    {
      static const unsigned hash_size = 256;

      unique_map::map_t& m = unique_map::instance();
      
      unique_map::map_t::iterator i = m.find(typeid(T));
      if (i == m.end())
	{
	  hashmap<T, hash_size> *h = 
	    static_cast<hashmap<T, hash_size>* >(m[typeid(T)] = new hashmap<T, hash_size>);
	  return h->get_or_insert(v);
	}
      return static_cast<hashmap<T, hash_size>*>(i->second)->get_or_insert(v);
    }
  }
}



#endif
