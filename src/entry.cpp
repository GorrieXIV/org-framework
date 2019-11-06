/*******************************************
 * origins vA.0.5 by gxiv                  *
 *                                         *
 * main game loop                          *
 * with inspiration from lazyfoo.net       *
 *******************************************/

#include "platform.hpp"

#include <stdio.h>
#include <cmath>

//#define USING_BOOST

#ifdef USING_BOOST
#include "boost/program_options.hpp"
#endif

#include "GameManager.hpp"
#include "DisplayEngine.hpp"

bool debug_mode = false;

//namespace bin_options = boost::program_options;

/* __ Global DisplayEngine object _________________________ *
 * Every instance of a "TexturedEntity" uses this object to *
 * access the SDL interface.                                */
DisplayEngine displayEngine{};


int main(int argc, char** argv) {
    #ifdef USING_BOOST
    bin_options::options_description desc("program arguments");

    desc.add_options()
                    ("help", "show a list of arguments")
                    ("debug", "enter debugging mode")
                    ("designer", "enter designer mode");

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
      if (vars.count("debug")) {
        debug_mode = true;
      }
    } catch (...) {
      std::cout << "Unexpected exception caught..." << std::endl;
      return 1;
      //TODO: print exception.
    }
    #else
    debug_mode = true;
    #endif

    try {
        GameManager gameManager{};
        std::cout << "- Initializing game manager..." << std::endl;
        gameManager.enterDebugMode();
        gameManager.runGame();
    } catch (...) {
      std::cout << "Unexpected exception caught. Aborting." << std::endl;
    }

    return 0;
}
