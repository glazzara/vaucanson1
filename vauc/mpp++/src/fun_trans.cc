#include "transformer/fun_transformer.hh"
# include "parse/libparse.hh"
#include "transformer/funs.hh"
#include <fstream>


using namespace spec;


int main(int argc, char* argv[])
{
  if (argc < 2)
    {
      std::cerr << "must give the fun spec to use as argument" << std::endl;
      return 1;
    }


  std::cerr << "reading file " << argv[1] << std::endl;
  spec::FunSpec *fs =
    fun_parse(std::string(argv[1])+".fun");
  if (fs == 0)
    {
      std::cerr << "error loading file" << std::endl;
      return 2;
    }

  std::string outfname = lower(norm(std::string(argv[1])))+".fxx";
  std::cerr << "output to file " << outfname << std::endl;

  std::ofstream of(outfname.c_str());

  fun_transformer(of, *fs);
}
