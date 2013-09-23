/*
  part of Oikonomic Threads project
  coded by Marinos Koutsomichalis (c) 2013, Heraklion
*/

// global settings

#pragma once

#include <iostream>
#include <string>
#include <libproc.h>
#include <mach-o/dyld.h>

#include "mar_utils.h"

const std::string getAbsolutePath();
const std::string appendPath(std::string, const std::string&);

namespace settings {
  // global settings 
  extern const unsigned int width;
  extern const unsigned int speed;
  extern const std::string filename;  // the filename to use
  // selected patterns
extern const std::string pattern0;
  extern const std::string pattern1;
  extern const std::string pattern2;
  extern const std::string pattern3;
  extern const std::string pattern4;
  extern const std::string pattern5;
  extern const std::string pattern6;
  extern const std::string pattern7;
  extern const std::string pattern8;
  extern const std::string pattern9;
}
