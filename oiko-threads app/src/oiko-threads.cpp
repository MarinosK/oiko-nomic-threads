/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
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

// using an aggreagate class to implement RAII
class OikoThreadsAggregate {
private:
  Pattern *pattern;
  Visualizer *visualizer;
  Controller *arduino;
  bool portOpen;
  cv::Mat nextLine;
public:
  OikoThreadsAggregate() : 
    pattern(new Pattern),
    visualizer(new Visualizer(1680, 1020)),
    arduino(new Controller),
    portOpen(false),
    nextLine()
  {
  }
  explicit OikoThreadsAggregate(int width, int height) : 
    pattern(new Pattern),
    visualizer(new Visualizer(width,height)),
    arduino(new Controller),
    portOpen(false),
    nextLine() {
  }
  ~OikoThreadsAggregate() {
    delete pattern;
    delete visualizer;
    delete arduino;
  }
  OikoThreadsAggregate(const OikoThreadsAggregate&) =delete;
  OikoThreadsAggregate& operator=(const OikoThreadsAggregate&) =delete;
  void setUp() {
    pattern->setUp();
    portOpen = arduino->setUp();
  }
  void loop() {
    if (portOpen) { // if there is a connection
      nextLine = pattern->nextLine(); // retrieve nextLine
      arduino->sendMsg(nextLine); // setUp solenoids
      arduino->waitForMsg(); // wait for responce
      visualizer->animate(nextLine); // animate next line
      #ifndef demo_mode
      cv::waitKey(1); // wait  a second
      #endif
      #ifdef demo_mode
      cv::waitKey(10); // wait  20 seconds
      #endif
      
    } else {
      std::cout << "Communication with the machine interrupted !" << std::endl;   
    }
  }
};


int main( int argc, char** argv ) {

  // preample credits
  std::cout << "\n*****\nOiko-nomic Threads \ninstallation for algorithmically controlled knitting machine and open data \n(c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psara\n*****\n" << std::endl;

  std::cout << "press q (and <return>) to quit.\n" << std::endl;
  std::cout << "starting..\n" << std::endl;

  std::atomic<bool> run(true); // flag to quit when q is pressed

  // lauch a new thread to upate run
  std::thread thread([&](){
      while(1) {
	char input = std::cin.get();
	if (input == 'q')  { run = false; }
      }
    });
  thread.detach(); // detach thread

  // lauch program
  OikoThreadsAggregate program;
  program.setUp();
  while (run) {
    program.loop();
  }

  // for stills
  // for (int i=0; i<10; i++) visualizer->still(pattern, 200);  
  // visualizer->clean();

  // export stills
  // for (int i=0; i<5; i++) visualizer->exportStill(pattern, 768);  

  return 0;
}
