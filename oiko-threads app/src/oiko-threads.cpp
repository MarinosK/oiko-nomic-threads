/* 
   Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psara
   installation for algorithmically controlled knitting machine and open data 
*/

#include <iostream>
#include <thread>
#include <atomic>

#include "opencv2/opencv.hpp"

#include "pattern.h"
#include "visualizer.h"
#include "settings.h"
#include "controller.h"

#include "mar_utils.h"

int main( int argc, char** argv ) {

  // preample credits
  std::cout << "\n*****\nOiko-nomic Threads \ninstallation for algorithmically controlled knitting machine and open data \n(c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psara\n*****\n" << std::endl;

  std::cout << "press q (and <return>) to quit.\n" << std::endl;

  std::cout << "starting..\n" << std::endl;

  // setup pattern
  Pattern *pattern = new Pattern;
  pattern->setUp();

  // setup visualizer
  Visualizer *visualizer = new Visualizer(settings::width * 8, settings::width * 5);

  // setup Controller
  Controller *arduino = new Controller;
  bool portOpen = arduino->setUp();


  std::atomic<bool> run(true); // flag to quit when q is pressed

  // lauch a new thread to upate run
  std::thread thread([&](){
      while(1) {
	char input = std::cin.get();
	if (input == 'q')  { run = false; }
      }
    });
  thread.detach(); // detach thread

  // start retrieving lines
  while (run) {
  // for (int i = 0; i<10; ++i) {
    if (portOpen) { // if there is a connection
      // start retrieving lines
      cv::Mat nextLine(pattern->nextLine()); // retrieve nextLine
      arduino->sendMsg(nextLine); // setUp solenoids
      arduino->waitForMsg(); // wait for responce
      visualizer->animate(nextLine); // animate next line
      cv::waitKey(1); // wait half a second
    } else {
      std::cout << "Communication with the machine interrupted !" << std::endl;   
    }
  }

  // for stills
  // for (int i=0; i<10; i++) visualizer->still(pattern, 200);  
  // visualizer->clean();
  
  // export stills
  // for (int i=0; i<5; i++) visualizer->exportStill(pattern, 768);  


  // wait key
  // cv::waitKey();

  // free memory
  delete pattern;
  delete visualizer;
  delete arduino;

  return 0;
}
