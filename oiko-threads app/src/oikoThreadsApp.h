#ifndef OIKOTHREADSAPP_H
#define OIKOTHREADSAPP_H

#include <opencv2/opencv.hpp>
#include "decoration.h"
#include "helper.h"
#include "visualizer.h"

#ifndef EMULATION_MODE
#include "controller.h"
#endif

/// application aggregate comprised of all the required data structures
class OikoThreadsApp {
private:
  Visualizer visualizer;
#ifndef EMULATION_MODE
  Controller arduino;
  short counter;
#endif
  Decoration decoration;
public:
  /// construct an object on given dimensions
  OikoThreadsApp(unsigned int width, unsigned int height);
  /// construct an object using default dimensions (found in settings)
  OikoThreadsApp() : OikoThreadsApp(settings::width, settings::height) {};
  /// default destructor 
  ~OikoThreadsApp() =default;
  OikoThreadsApp(const OikoThreadsApp&) =delete;
  OikoThreadsApp(OikoThreadsApp&&) =delete;
  OikoThreadsApp& operator=(const OikoThreadsApp&) =delete;
  OikoThreadsApp& operator=(OikoThreadsApp&&) =delete;
  /// the main program loop
  void loop();
};

#endif
