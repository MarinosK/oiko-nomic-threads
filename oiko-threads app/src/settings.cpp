/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#include "settings.h"

#ifndef demo_mode 
const unsigned int settings::width = 160;
#endif
#ifdef demo_mode 
const unsigned int settings::width = 1680;
#endif
const unsigned int settings::speed = 10;

const std::string getAbsolutePath() {
  char buf [PATH_MAX];
  uint32_t bufsize = PATH_MAX;
  if(!_NSGetExecutablePath(buf, &bufsize)) puts(buf);
  std::string path(buf);
  // strip executables filename
  const std::string executable("/oiko-threads");
  path = path.substr(0, path.size() - executable.size());
  // return path
  return path;
}

const std::string appendPath(std::string path, const std::string& relativePath) {
  path.append(relativePath);
  return path;
}

static const std::string absolutePath = getAbsolutePath();

const std::string settings::filename = appendPath(absolutePath,"/data/PSGR.csv");  // the filename to use
// selected patterns
const std::string settings::pattern0 = appendPath(absolutePath, "/data/0.png");
const std::string settings::pattern1 = appendPath(absolutePath, "/data/1.png");
const std::string settings::pattern2 = appendPath(absolutePath, "/data/2.png");
const std::string settings::pattern3 = appendPath(absolutePath, "/data/3.png");
const std::string settings::pattern4 = appendPath(absolutePath, "/data/4.png");
const std::string settings::pattern5 = appendPath(absolutePath, "/data/5.png");
const std::string settings::pattern6 = appendPath(absolutePath, "/data/6.png");
const std::string settings::pattern7 = appendPath(absolutePath, "/data/7.png");
const std::string settings::pattern8 = appendPath(absolutePath, "/data/8.png");
const std::string settings::pattern9 = appendPath(absolutePath, "/data/9.png");
