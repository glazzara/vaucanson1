#ifndef UTILITY_UNIQUE_HXX
# define UTILITY_UNIQUE_HXX

#include <vaucanson/misc/unique.hh>


namespace utility
{

  namespace unique
  {
    unique_map::ti_slot::ti_slot(const std::type_info& _id)
      : id(_id) {}
    bool unique_map::ti_slot::operator==(const unique_map::ti_slot& other) const
    { return id == other.id; }
    bool unique_map::ti_slot::operator<(const unique_map::ti_slot& other) const
    { return id.before(other.id); }

    template<typename T>
    uniquelist<T>::~uniquelist() {}

    unifiable::unifiable() : unique_(false) {}
    unifiable::unifiable(const unifiable& ) : unique_(false) {} 

    template<typename T>
    const T& get(const T& v)
    {
      if (static_cast<const unifiable&>(v).unique_)
	return v;

      unique_map::map_t& m = unique_map::instance();
      
      unique_map::map_t::iterator i = m.find(typeid(T));
      if (i == m.end())
	{
	  uniquelist<T> *l = 
	    static_cast<uniquelist<T>* >(m[typeid(T)] = new uniquelist<T>);
	  l->push_front(v);
	  static_cast<unifiable&>(l->front()).unique_ = true;
	  return l->front();
	}
      uniquelist<T> *l =
	static_cast<uniquelist<T>*>(i->second);
      typename uniquelist<T>::const_iterator j;
      if ((j = std::find(l->begin(), l->end(), v)) == l->end())
	{
	  l->push_front(v);
	  static_cast<unifiable&>(l->front()).unique_ = true;
	  return l->front();
	}
      return *j;
    }

    template<typename T>
    const T* get(const T* v)
    { return & get(*v); }

  }
}



#endif
