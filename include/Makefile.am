# Makefile.am
#
# $Id$

nobase_nodist_include_HEADERS = vaucanson/config/pconf.hh

nobase_include_HEADERS = \
vaucanson/fundamental/slots.hh\
vaucanson/fundamental/op_traits.hh\
vaucanson/fundamental/fundamental.hh\
vaucanson/fundamental/element_ops.hh\
vaucanson/fundamental/element.hh\
vaucanson/fundamental/element_base.hh\
vaucanson/fundamental/predefs.hh\
vaucanson/fundamental/meta_set.hh\
vaucanson/fundamental/meta_element.hh\
vaucanson/fundamental/structure.hh\
vaucanson/fundamental/default_ops.hh\
vaucanson/misc/static.hh\
vaucanson/misc/selectors.hh\
vaucanson/misc/container_ops.hh\
vaucanson/misc/numerical_constraints.hh\
vaucanson/misc/misc_constraints.hh\
vaucanson/misc/constraints.hh\
vaucanson/misc/converter.hh\
vaucanson/misc/functors.hh\
vaucanson/misc/ref.hh\
vaucanson/misc/type_constraints.hh\
vaucanson/misc/dot_dump.hh\
vaucanson/misc/random.hh\
vaucanson/misc/limits.hh\
vaucanson/internal/traits.hh\
vaucanson/algebra/concrete/alphabets/set_alphabet.hh\
vaucanson/algebra/concrete/alphabets/alphabets.hh\
vaucanson/algebra/concrete/semiring/numerical_semiring.hh\
vaucanson/algebra/concrete/semiring/tropical_semiring.hh\
vaucanson/algebra/concrete/free_monoid/words.hh\
vaucanson/algebra/concrete/free_monoid/str_words.hh\
vaucanson/algebra/concrete/series/krat_conversion.hh\
vaucanson/algebra/concrete/series/krat.hh\
vaucanson/algebra/concrete/series/polynoms.hh\
vaucanson/algebra/concrete/series/series.hh\
vaucanson/algebra/concrete/series/rat/depth_visitor.hh\
vaucanson/algebra/concrete/series/rat/dump_visitor.hh\
vaucanson/algebra/concrete/series/rat/exp.hh\
vaucanson/algebra/concrete/series/rat/nodes.hh\
vaucanson/algebra/concrete/series/rat/random_visitor.hh\
vaucanson/algebra/concrete/series/transpose.hh\
vaucanson/algebra/concrete/series/generalized.hh\
vaucanson/algebra/concept/concepts.hh\
vaucanson/algebra/concept/alphabets_base.hh\
vaucanson/algebra/concept/semigroup_base.hh\
vaucanson/algebra/concept/monoid_base.hh\
vaucanson/algebra/concept/semiring_base.hh\
vaucanson/algebra/concept/numerical_semiring.hh\
vaucanson/algebra/concept/tropical_semiring.hh\
vaucanson/algebra/concept/freemonoid_base.hh\
vaucanson/algebra/concept/series_base.hh\
vaucanson/automata/concrete/manylinks_states.hh\
vaucanson/automata/concrete/manylinks_impl.hh\
vaucanson/automata/concrete/manylinks_edges.hh\
vaucanson/automata/concrete/manylinks_carriers.hh\
vaucanson/automata/concrete/manylinks.hh\
vaucanson/automata/concrete/generalized.hh\
vaucanson/automata/concept/transpose_impl.hh\
vaucanson/automata/concept/translate.hh\
vaucanson/automata/concept/tags.hh\
vaucanson/automata/concept/relabel_impl.hh\
vaucanson/automata/concept/history.hh\
vaucanson/automata/concept/handlers.hh\
vaucanson/automata/concept/copy.hh\
vaucanson/automata/concept/concepts.hh\
vaucanson/automata/concept/automaton_impl.hh\
vaucanson/automata/concept/automata_base.hh\
vaucanson/automata/concept/automata.hh\
vaucanson/automata/concept/kinds.hh\
vaucanson/automata/concept/generalized.hh\
vaucanson/algorithms/extract.hh\
vaucanson/algorithms/reachable.hh\
vaucanson/algorithms/determinize.hh\
vaucanson/algorithms/transpose.hh\
vaucanson/algorithms/union.hh\
vaucanson/algorithms/normalized.hh\
vaucanson/algorithms/compute.hh\
vaucanson/algorithms/product.hh\
vaucanson/algorithms/closure.hh\
vaucanson/algorithms/moore.hh\
vaucanson/algorithms/hopcroft.hh\
vaucanson/algorithms/elimination.hh\
vaucanson/algorithms/glushkov.hh\
vaucanson/algorithms/standard.hh\
vaucanson/algorithms/thompson.hh\
vaucanson/algorithms/realtime.hh\
vaucanson/algorithms/complete.hh\
vaucanson/algorithms/complementary.hh\
vaucanson/algorithms/trim.hh\
vaucanson/tools/usual.hh\
vaucanson/tools/gen_random.hh\
vaucanson/config/system.hh\
vaucanson/config/rel_ops_work_around_g++2.hh\
vaucanson/fundamental/slots.hxx\
vaucanson/fundamental/element.hxx\
vaucanson/fundamental/element_base.hxx\
vaucanson/fundamental/meta_element.hxx\
vaucanson/fundamental/structure.hxx\
vaucanson/fundamental/default_ops.hxx\
vaucanson/misc/static.hxx\
vaucanson/misc/container_ops.hxx\
vaucanson/misc/converter.hxx\
vaucanson/misc/ref.hxx\
vaucanson/misc/functors.hxx\
vaucanson/misc/random.hxx\
vaucanson/algebra/concrete/alphabets/set_alphabet.hxx\
vaucanson/algebra/concrete/semiring/numerical_semiring.hxx\
vaucanson/algebra/concrete/semiring/tropical_semiring.hxx\
vaucanson/algebra/concrete/free_monoid/words.hxx\
vaucanson/algebra/concrete/free_monoid/str_words.hxx\
vaucanson/algebra/concrete/series/krat_conversion.hxx\
vaucanson/algebra/concrete/series/krat.hxx\
vaucanson/algebra/concrete/series/polynoms.hxx\
vaucanson/algebra/concrete/series/series.hxx\
vaucanson/algebra/concrete/series/rat/exp.hxx\
vaucanson/algebra/concrete/series/rat/nodes.hxx\
vaucanson/algebra/concrete/series/rat/dump_visitor.hxx\
vaucanson/algebra/concrete/series/rat/depth_visitor.hxx\
vaucanson/algebra/concrete/series/rat/random_visitor.hxx\
vaucanson/algebra/concrete/series/generalized.hxx\
vaucanson/algebra/concrete/series/transpose.hxx\
vaucanson/algebra/concept/concepts.hxx\
vaucanson/algebra/concept/alphabets_base.hxx\
vaucanson/algebra/concept/semigroup_base.hxx\
vaucanson/algebra/concept/monoid_base.hxx\
vaucanson/algebra/concept/semiring_base.hxx\
vaucanson/algebra/concept/freemonoid_base.hxx\
vaucanson/algebra/concept/series_base.hxx\
vaucanson/automata/concrete/generalized.hxx\
vaucanson/automata/concept/transpose_impl.hxx\
vaucanson/automata/concept/translate.hxx\
vaucanson/automata/concept/tags.hxx\
vaucanson/automata/concept/relabel_impl.hxx\
vaucanson/automata/concept/history.hxx\
vaucanson/automata/concept/handlers.hxx\
vaucanson/automata/concept/copy.hxx\
vaucanson/automata/concept/concepts.hxx\
vaucanson/automata/concept/automaton_impl.hxx\
vaucanson/automata/concept/automata_base.hxx\
vaucanson/automata/concept/automata.hxx\
vaucanson/automata/concept/kinds.hxx\
vaucanson/automata/concept/generalized.hxx\
vaucanson/algorithms/extract.hxx\
vaucanson/algorithms/reachable.hxx\
vaucanson/algorithms/determinize.hxx\
vaucanson/algorithms/transpose.hxx\
vaucanson/algorithms/union.hxx\
vaucanson/algorithms/normalized.hxx\
vaucanson/algorithms/compute.hxx\
vaucanson/algorithms/product.hxx\
vaucanson/algorithms/closure.hxx\
vaucanson/algorithms/moore.hxx\
vaucanson/algorithms/hopcroft.hxx\
vaucanson/algorithms/elimination.hxx\
vaucanson/algorithms/glushkov.hxx\
vaucanson/algorithms/standard.hxx\
vaucanson/algorithms/thompson.hxx\
vaucanson/algorithms/realtime.hxx\
vaucanson/algorithms/trim.hxx\
vaucanson/algorithms/complete.hxx\
vaucanson/algorithms/complementary.hxx\
vaucanson/tools/gen_random.hxx

EXTRA_DIST = vaucanson/config/extrconf.sh
PERL = perl
SCANDEFS_PL = $(top_srcdir)/tools/scandefs.pl
PCONF_OCCURS = vaucanson/config/system.hh 
$(top_srcdir)/include/vaucanson/config/extrconf.sh: $(SCANDEFS_PL) $(PCONF_OCCURS)
	$(PERL) $(SCANDEFS_PL) $(PCONF_OCCURS) >$@

vaucanson/config/pconf.hh: $(top_srcdir)/include/vaucanson/config/extrconf.sh $(CONFIG_HEADER)
	test -f $(CONFIG_HEADER)
## Ignore the result of config/extrconf.sh.  It might be non 0 if
## grep matched nothing, but that's ok for us.  The sole case
## we bother with is failure caused by an unexisting $(CONFIG_HEADER).
## The test -f above take care of this.
	$(SHELL) $(top_srcdir)/include/vaucanson/config/extrconf.sh $(CONFIG_HEADER) \
	>$(top_srcdir)/include/vaucanson/config/pconf.hh; :

DISTCLEANFILES = vaucanson/config/pconf.hh vaucanson/config/stamp-h1

