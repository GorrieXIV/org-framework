#include <iostream>

//#include "include/project_generator.hpp"
#include "boost/program_options.hpp"

namespace bin_options = boost::program_options;

namespace {

} // anonymous namespace

int main (int argc, char** argv) {
 
  bin_options::options_description desc("Build options");  

  desc.add_options()
                  ("help", "Show the help message")
                  ("isometric", "Builds org_display for an isometric game")
                  ("top-down", "Builds org_display for a top-down game");
  
  bin_options::variables_map vars;

  try {
    bin_options::store(bin_options::parse_command_line(argc, argv, desc), vars);
    bin_options::notify(vars);
  } catch (bin_options::error &error) {
    std::cout << error.what();
    return -1;
  }

  try {
    if (vars.count("help")) {
      std::cout << desc;
      return 0;
    }
  } catch (...) {
    std::cout << "unexpected error\n";
  }

  return 0;
}
