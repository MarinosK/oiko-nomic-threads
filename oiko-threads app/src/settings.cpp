/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#include "settings.h"

const unsigned int settings::width = 1680; // it Helps if it is an integer multiple of the next one
const unsigned int settings::knitWidth = 160;

#ifndef demo_mode 
const unsigned int settings::speed = 1;
#endif
#ifdef demo_mode 
const unsigned int settings::speed = 100;
#endif

#ifndef dual_mode 
const std::string settings::oscPath = "192.168.1.2";
const int settings::oscPort = 7000;
#endif
#ifdef dual_mode 
const std::string settings::oscPath = "192.168.1.2";
const int settings::oscPort = 7000;
#endif

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

const std::string settings::absolutePath = getAbsolutePath();

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
const std::string settings::knitPattern0 = appendPath(absolutePath, "/data/knit0.png");
const std::string settings::knitPattern1 = appendPath(absolutePath, "/data/knit1.png");
const std::string settings::knitPattern2 = appendPath(absolutePath, "/data/knit2.png");
const std::string settings::knitPattern3 = appendPath(absolutePath, "/data/knit3.png");
const std::string settings::knitPattern4 = appendPath(absolutePath, "/data/knit4.png");
const std::string settings::knitPattern5 = appendPath(absolutePath, "/data/knit5.png");
const std::string settings::knitPattern6 = appendPath(absolutePath, "/data/knit6.png");
const std::string settings::knitPattern7 = appendPath(absolutePath, "/data/knit7.png");
const std::string settings::knitPattern8 = appendPath(absolutePath, "/data/knit8.png");
const std::string settings::knitPattern9 = appendPath(absolutePath, "/data/knit9.png");
