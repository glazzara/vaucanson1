#include "unwind_init.hh"
#include <lazy/exp.hh>
#include <lazy/eval_visitor.hh>
#include <vcore/exception.hh>
#include <kern/exnprint.hh>

#define NAMED(Name) \
        Constant<VisitorBase>(Symbol(Name))
#define INDIRECT(Name) \
    new Constant<VisitorBase> \
            (LazyExp(new NAMED(Name)))


namespace vcsn
{
  namespace vauc
  {
    using namespace vcsn::vauc::lazy;

    void unwind_init(Env& _env, const std::string& _initstr)
    {
      // what follows is the compiled version of:
      // {
      //   st = std//isstream[input];
      //   e = `0;
      //   st >> e;
      //   ? e;
      // }
      // which is, expanded:
      // :call(_subeval, 
      //       :list(:abstr(
      //          :call(_seqeval,
      //                :list(
      //       :abstr(:call(_assign, 
      //                     :list(:abstr("st"), 
      //                           std//isstream,
      //                           input))),
      //       :abstr(:call(_assign,
      //                    :list(:abstr("e"), :abstr("a")))),
      //       :call(_op_in, st, e),
      //       :call(_eval, e)
      //                     )
      //                )
      //             )      )
      //        )

      static Exp<VisitorBase>* _make_input_call = 
	NEW_VAUC_CALL1("std//isstream", \
		  new Constant<VisitorBase>(_initstr));

      static Exp<VisitorBase>* _assign_input_call =
	NEW_VAUC_CALL2("_assign", 
			  INDIRECT("st"),
			  _make_input_call);

      static Exp<VisitorBase>* _create_exp =
	NEW_VAUC_CALL2("_assign",
		  INDIRECT("e"),
		  INDIRECT("any"));

      static Exp<VisitorBase>* _read_exp =
	NEW_VAUC_CALL2("_op_in",
		  new NAMED("st"),
		  new NAMED("e"));
      
      static Exp<VisitorBase>* _seq_exp = 
	NEW_VAUC_CALL1("_seqeval",
		  (new List<VisitorBase>)
		  ->attach_back(new Constant<VisitorBase>(LazyExp(_assign_input_call)))
		  ->attach_back(new Constant<VisitorBase>(LazyExp(_create_exp)))
		  ->attach_back(new Constant<VisitorBase>(LazyExp(_read_exp)))
		  ->attach_back(INDIRECT("e")));

      static Exp<VisitorBase>* _sub_exp =
	NEW_VAUC_CALL1("_subeval",
		  new Constant<VisitorBase>(LazyExp(_seq_exp)));
      
      static LazyExp _init_call =
	LazyExp(NEW_VAUC_CALL1("_eval", _sub_exp));

      try
	{
	  EvalVisitor v(_env);
	  _init_call.exp().accept(v);
	}
      catch(EXCEPTION(x))
	{
	  std::cerr << "warning: _init gave an exception:" << x <<  std::endl;
	}
    }
  }
}
