// limits.hh
//
// $Id$
// VCSN_HEADER
#ifndef INTERNAL_LIMITS_HH
# define INTERNAL_LIMITS_HH

namespace std {

  template <class _Tp>
  struct numeric_limits
  {
    static const bool is_specialized = false;
    
    static _Tp min() throw() { return static_cast<_Tp>(0); }
    static _Tp max() throw() { return static_cast<_Tp>(0); }

    static const int digits = 0;
    static const int digits10 = 0;
    static const bool is_signed = false;
    static const bool is_integer = false;
    static const bool is_exact = false;
    static const int radix = 0;

    static _Tp epsilon() throw() { return static_cast<_Tp>(0); }
    static _Tp round_error() throw() { return static_cast<_Tp>(0); }

    static const int min_exponent = 0;
    static const int min_exponent10 = 0;
    static const int max_exponent = 0;
    static const int max_exponent10 = 0;

    static const bool has_infinity = false;
    static const bool has_quiet_NaN = false;
    static const bool has_signaling_NaN = false;
    static const bool has_denorm_loss = false;

    static _Tp infinity() throw()  { return static_cast<_Tp>(0); }
    static _Tp quiet_NaN() throw() { return static_cast<_Tp>(0); }
    static _Tp signaling_NaN() throw() { return static_cast<_Tp>(0); }
    static _Tp denorm_min() throw() { return static_cast<_Tp>(0); }

    static const bool is_iec559 = false;
    static const bool is_bounded = false;
    static const bool is_modulo = false;

    static const bool traps = false;
    static const bool tinyness_before = false;
  };

template<>
    struct numeric_limits<bool>
    {
      static const bool is_specialized = true;

      static bool min() throw()
      { return false; }

      static bool max() throw()
      { return true; }

      static const int digits10 = 1;
      static const bool is_signed = false;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;
      static bool epsilon() throw()
      { return false; }
      static bool round_error() throw()
      { return false; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const bool has_denorm_loss = false;

      static bool infinity() throw()
      { return false; }
      static bool quiet_NaN() throw()
      { return false; }
      static bool signaling_NaN() throw()
      { return false; }
      static bool denorm_min() throw()
      { return false; }

      static const bool is_iec559 = true;
      static const bool is_bounded = true;
      static const bool is_modulo = true;

      // It is not clear what it means for a boolean type to trap.
      // This is a DR on the LWG issue list.  Here, I use integer
      // promotion semantics.
      static const bool tinyness_before = false;
    };

  
  template<>
    struct numeric_limits<int>
    {
      static const bool is_specialized = true;

      static int min() throw()
      { return INT_MIN; }
      static int max() throw()
      { return INT_MAX; }

      static const bool is_signed = true;
      static const bool is_integer = true;
      static const bool is_exact = true;
      static const int radix = 2;
      static int epsilon() throw()
      { return 0; }
      static int round_error() throw()
      { return 0; }

      static const int min_exponent = 0;
      static const int min_exponent10 = 0;
      static const int max_exponent = 0;
      static const int max_exponent10 = 0;

      static const bool has_infinity = false;
      static const bool has_quiet_NaN = false;
      static const bool has_signaling_NaN = false;
      static const bool has_denorm_loss = false;

      static int infinity() throw()
      { return static_cast<int>(0); }
      static int quiet_NaN() throw()
      { return static_cast<int>(0); }
      static int signaling_NaN() throw()
      { return static_cast<int>(0); }
      static int denorm_min() throw()
      { return static_cast<int>(0); }

      static const bool is_iec559 = true;
      static const bool is_bounded = true;
      static const bool is_modulo = false;

      static const bool tinyness_before = false;
    };

} // std

#endif // INTERNAL_LIMITS_HH
