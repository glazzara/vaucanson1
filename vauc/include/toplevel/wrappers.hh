// wrappers.hh: this file is part of the Vaucanson project.
// 
// Vaucanson, a generic library for finite state machines.
// 
// Copyright (C) 2005 The Vaucanson Group.

// 
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// The complete GNU General Public Licence Notice can be found as the
// `NOTICE' file in the root directory.
// 
// The Vaucanson Group consists of people listed in the `AUTHORS' file.
//
#ifndef VCSN_VAUC_INCLUDE_TOPLEVEL_WRAPPERS_HH
# define VCSN_VAUC_INCLUDE_TOPLEVEL_WRAPPERS_HH


// customize as needed. But beware, changing this file often means recompiling the
// whole thing.

#define SYNTAX_ERROR "Syntax error"

#define FUNCTION_IF		"_if"
#define FUNCTION_IFELSE		"_if"
#define FUNCTION_SET		"_set"
#define FUNCTION_ASSIGN		"_assign"
#define FUNCTION_CLONE		"_clone"
#define FUNCTION_TRY		"_try"
#define FUNCTION_FOR		"_for"
#define FUNCTION_WHILE		"_while"
#define FUNCTION_FOREACH	"_foreach"

#define FUNCTION_NEG		"_op_neg"
#define FUNCTION_NOT		"_op_not"
#define FUNCTION_EVAL		"_eval"
#define FUNCTION_AND		"_op_and"
#define FUNCTION_REASSIGN	"_in_assign"
#define FUNCTION_CONS		"_cons"
#define FUNCTION_APPEND		"_append"
#define FUNCTION_OR		"_op_or"
#define FUNCTION_ADD		"_op_add"
#define FUNCTION_MUL		"_op_mul"
#define FUNCTION_IN_ADD		"_op_in_add"
#define FUNCTION_IN_MUL		"_op_in_mul"
#define FUNCTION_IN_STAR	"_op_in_star"
#define FUNCTION_STAR		"_op_star"
#define FUNCTION_LT		"_op_lt"
#define FUNCTION_EQ		"_op_eq"
#define FUNCTION_PAIR		"_couple"
#define FUNCTION_TYPEOF		"_typeof"
#define FUNCTION_KILL		"_kill"
#define FUNCTION_IMPORT		"_import"
#define FUNCTION_EXPORT		"_export"
#define FUNCTION_THROW		"_throw"
#define FUNCTION_FETCH		"_fetch"
#define FUNCTION_LAMBDA		"_lambda"
#define FUNCTION_SEQ		"_seqeval"
#define FUNCTION_SUB		"_subeval"
#define FUNCTION_INC		"_op_inc"
#define FUNCTION_IOIN		"_op_in"
#define FUNCTION_IOOUT		"_op_out"
#define FUNCTION_TYPES		"_types"
#define FUNCTION_CLEAR		"_clear"
#define FUNCTION_FUNMERGE	"_funmerge"
#define FUNCTION_LAST		"_ans"
#define FUNCTION_PRINTERS	"_op_out"
#define FUNCTION_LIST    	"_current"

#endif // ! VCSN_VAUC_INCLUDE_TOPLEVEL_WRAPPERS_HH
