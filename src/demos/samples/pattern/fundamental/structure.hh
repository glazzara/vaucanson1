
#ifndef   STRUCTURE_HH_
# define   STRUCTURE_HH_

template<typename Self>
struct Structure
{
  typedef Self		self_t;
  
  /*! Check if a given element is compatible with the structural element. */
  template<typename T>
  bool  contains(const Element<Self, T>& elt) const;
  
  /*! If S <> Self, contains allways returns false. */
  template<typename S, typename T>
  bool  contains(const Element<S, T>& other) const;


  /*! Return the instance viewed as its exact type. */
  self_t&        self();

  /*! Return the instance viewed as its exact type (const). */
  const self_t&  self() const;
  
protected:
  /*! Default constructor is protected since Structure is an
    abstract class. */
  Structure();

  /*! Copy constructor is protected because Structure is an abstract class. 
   */
  Structure(const Structure& other);
};

#include "structure.hxx"

#endif /* !STRUCTURE_HH_ */
