// fundamental/slots.hh
//
// VCSN_HEADER
#ifndef FUNDAMENTAL_SLOTS_HH
# define FUNDAMENTAL_SLOTS_HH

# include <vaucanson/misc/selectors.hh>
# include <vaucanson/fundamental/predefs.hh>

namespace vcsn {

  /*-----------------------------------.
  | Base class for SetSlot class below |
  `-----------------------------------*/

  template<typename S, bool dynamic /* default: false */>
  struct SetSlotAttribute
  {
    SetSlotAttribute();
    SetSlotAttribute(const SetSlotAttribute& other);
    SetSlotAttribute(const S& other);
    
    const S&	get() const;
    S&		get();

    void	assign(const SetSlotAttribute& other);
    void	attach(const S& other);
    bool	bound() const;

  };

  // Specialization when structural element is dynamic

  template<typename S>
  struct SetSlotAttribute<S, true>
  {
    SetSlotAttribute();
    SetSlotAttribute(const SetSlotAttribute& other);
    SetSlotAttribute(const S& other);

    const S&	get() const;
    S&		get();

    void	assign(const SetSlotAttribute& other);
    void	attach(const S& s);
    bool	bound() const;
    
  protected:
    const S*	s_;
  };


  /*------------------------------------.
  | Set attribute for the Element class |
  `------------------------------------*/

  template<typename S>
  struct SetSlot : SetSlotAttribute<S, MetaSet<S>::dynamic_set>
  {
    SetSlot();
    SetSlot(const SetSlot& other);
    SetSlot(const S& other);
  };

  /*-------------------------------------.
  | Base class for ValueSlot class below |
  `-------------------------------------*/

  template<typename T, bool dynamic>
  struct ValueSlotAttribute
  {
    ValueSlotAttribute();
    ValueSlotAttribute(const T& data);
    ValueSlotAttribute(const ValueSlotAttribute& other);

    const T&	get() const;
    T&		get();

    void	assign(const ValueSlotAttribute& other);
  };

  // specialization for dynamic structural element

  template<typename T>
  struct ValueSlotAttribute<T, true>
  {
    ValueSlotAttribute();
    ValueSlotAttribute(const T& data);
    ValueSlotAttribute(const ValueSlotAttribute& other);

    T&		get();
    const T&	get() const;

    void	assign(const ValueSlotAttribute& other);

  protected:
    T data_;
  };

  /*--------------------------------------.
  | Value attribute for the Element class |
  `--------------------------------------*/

  template<typename S, typename T>
  struct ValueSlot : 
    ValueSlotAttribute<T, MetaElement<S, T>::dynamic_values>
  {
    ValueSlot();
    ValueSlot(const ValueSlot& other);
    ValueSlot(const T& other);

    operator const T& () const;
  };

}

/*----------------------------.
| comparison between SetSlots |
`----------------------------*/
template<typename S>
static inline
bool operator==(const vcsn::SetSlotAttribute<S, true>& a,
		const vcsn::SetSlotAttribute<S, true>& b);

template<typename S>
static inline
bool operator==(const vcsn::SetSlotAttribute<S, false>& a,
		const vcsn::SetSlotAttribute<S, false>& b);

template<typename S>
static inline
bool operator!=(const vcsn::SetSlotAttribute<S, true>& a,
		const vcsn::SetSlotAttribute<S, true>& b);

template<typename S>
static inline
bool operator!=(const vcsn::SetSlotAttribute<S, false>& a,
		const vcsn::SetSlotAttribute<S, false>& b);


/*---------------------------------------.
| internal comparison between ValueSlots |
`---------------------------------------*/
namespace vcsn
{
  namespace internal
  {

    enum comp_kind { eq, neq, lt, gt, le, ge };
    
    template<typename S1, typename S2,
	     typename T1, typename T2, 
	     comp_kind e, bool dynamic /* default false */,
	     bool default_ret>
    struct op
    {
      static bool do_comp(const T1& v1, const T2& v2)
      { 
	return default_ret; 
      }
    };

#define TRIV_OP(Name, Rel)				\
    template<typename S, typename T, bool b>		\
    struct op<S, S, T, T, Name, true, b>		\
    {							\
      static bool do_comp(const T& v1, const T& v2)	\
      { return Rel; }					\
    };

    TRIV_OP(eq, v1 == v2);
    TRIV_OP(neq, !(v1 == v2));
    TRIV_OP(lt, v1 < v2);
    TRIV_OP(gt, v2 < v1);
    TRIV_OP(le, !(v2 < v1));
    TRIV_OP(ge, !(v1 < v2));

#undef TRIV_OP
#define INTER_OP(Name, Op, Rel1, Rel2)				\
    template<typename S, typename T, typename U, bool b>	\
    struct op<S, S, T, U, Name, true, b>			\
    {								\
      static bool do_comp(const T& v1, const U& v2)		\
      { return Op(SELECT(S), Rel1, Rel2); }			\
    };
    
    INTER_OP(eq, op_eq, v1, v2)
    INTER_OP(neq, !op_eq, v1, v2)
    INTER_OP(lt, op_lt, v1, v2)
    INTER_OP(gt, op_lt, v2, v1)
    INTER_OP(ge, !op_lt, v1, v2)
    INTER_OP(le, !op_lt, v2, v1)
#undef INTER_OP

    struct toto {};

#define FOREIGN_OP(Name, Op, X1, X2, Rel1, Rel2)			\
    template<typename S1, typename S2, typename T, typename U, bool b>	\
    struct op<S1, S2, T, U, Name, true, b>				\
    {									\
      static bool do_comp(const T& v1, const U& v2)			\
      { return Op(SELECT(X1), SELECT(X2), Rel1, Rel2); }		\
    }

    FOREIGN_OP(eq, op_eq, S1, S2, v1, v2);
    FOREIGN_OP(neq, !op_eq, S1, S2, v1, v2);
    FOREIGN_OP(lt, op_lt, S1, S2, v1, v2);
    FOREIGN_OP(gt, op_lt, S2, S1, v2, v1);
    FOREIGN_OP(ge, !op_lt, S1, S2, v1, v2);
    FOREIGN_OP(le, !op_lt, S2, S1, v2, v1);

#undef FOREIGN_OP

  } // internal

} // vcsn

namespace vcsn {

#define CALL_OP(Op, Name, Deflt)				\
template<typename S1, typename T1, typename S2, typename T2>	\
static inline							\
bool operator Op(const vcsn::ValueSlot<S1, T1>& v1,	\
		 const vcsn::ValueSlot<S2, T2>& v2)	\
{ return v1.get() == v2.get(); }                         \

CALL_OP(==, vcsn::internal::eq, true);
CALL_OP(!=, vcsn::internal::neq, false);
CALL_OP(<, vcsn::internal::lt, false);
CALL_OP(>, vcsn::internal::gt, false);
CALL_OP(<=, vcsn::internal::le, true);
CALL_OP(>=, vcsn::internal::ge, true);

#undef CALL_OP

} // vcsn

# include <vaucanson/fundamental/slots.hxx>

#endif // FUNDAMENTAL_SLOTS_HH
