/*! \mainpage Oikonomic Threads App
 * Coded by Marinos Koutsomichalis for the Oikonomic Threads project ((c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra). Oiko-nomic Threads is an installation for algorithmically controlled knitting machine and open data. For more info see the project's page <a href="http://marinoskoutsomichalis.com/oikonomic-threads/">here</a>.
 */

#include <iostream>
#include <atomic>
#include <thread>
#include "helper.h"
#include "oikoThreadsApp.h"

/// launces OikoThreadsApp on its own thread, controls input (if q-enter the application quits), and catches exceptions
int main( int argc, char** argv) {
  try {
    helper::log(settings::preample); 
    helper::setWidthAndHeightAndSpeed(argc, argv); 
    
    // threadA -> quit on q
    std::atomic<bool> run {true};
    std::thread thread{[&](){ while(1) {
	  char input = std::cin.get();
	  if (input == 'q') run = false; 
	}}};
    thread.detach(); // detach Threads
 
    // threadB -> main program loop
    OikoThreadsApp program{};
    while (run) program.loop();

    // to export stills if needed
    // for (int i=0; i<5; i++) visualizer->exportStill(pattern, 768);  
    
    return 0;
  }
  catch (const std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 2;
  }
  catch (...) {
    std::cerr << "uknown exception" << std::endl;
    return 3;
  }
}
