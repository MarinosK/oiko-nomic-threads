/*! \stitch-test
 * Coded by Marinos Koutsomichalis for the Oikonomic Threads project ((c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra). Oiko-nomic Threads is an installation for algorithmically controlled knitting machine and open data. For more info see the project's page <a href="http://marinoskoutsomichalis.com/oikonomic-threads/">here</a>.
 */

// debuging tool

#include <iostream>
#include "controller.h"

/// launces OikoThreadsApp on its own thread, controls input (if q-enter the application quits), and catches exceptions
int main( int argc, char** argv) {
  try {
    std::cout << "starting test" << std::endl;
    Controller arduino{};

    while (true) {
      std::cout << "enter stitch pattern: " << std::endl;
      char buffer[161];
      std::cin.getline(buffer,161);
      std::string data{buffer};
      if (arduino.sendMsg(data)) { // if conection open, proceed
	arduino.waitForMsg();
      } else helper::log("communication with the machine interrupted");
    }
    return 0;
  }
  catch (...) {
    std::cerr << "uknown exception" << std::endl;
    return 1;
  }
}

