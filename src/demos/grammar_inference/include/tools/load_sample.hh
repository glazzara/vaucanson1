// load_sample.hh

#ifndef   LOAD_SAMPLE_HH_
# define   LOAD_SAMPLE_HH_

#include <set>


template <typename W>
std::set<W>
load_sample(SELECTOR(W), const char* name_file);

#include <tools/load_sample.hxx>

#endif /* !LOAD_SAMPLE_HH_ */
