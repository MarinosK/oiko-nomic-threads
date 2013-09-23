
#include "settings.h"

const unsigned int settings::width = 160;
const unsigned int settings::speed = 10;
const char* const settings::filename = "data/PSGR.csv";  // the filename to use
// selected patterns
const char* const settings::pattern0 = "data/0.png";
const char* const settings::pattern1 = "data/1.png";
const char* const settings::pattern2 = "data/2.png";
const char* const settings::pattern3 = "data/3.png";
const char* const settings::pattern4 = "data/4.png";
const char* const settings::pattern5 = "data/5.png";
const char* const settings::pattern6 = "data/6.png";
const char* const settings::pattern7 = "data/7.png";
const char* const settings::pattern8 = "data/8.png";
const char* const settings::pattern9 = "data/9.png";

// void setupSettings() {
//   int ret;
//   pid_t pid; 
//   char pathbuf[PROC_PIDPATHINFO_MAXSIZE];
  
//   pid = getpid();
//   ret = proc_pidpath (pid, pathbuf, sizeof(pathbuf));
//   if ( ret <= 0 ) {
//     std::cout << "Failed to determing current path correctly - will now terminate" << std::endl;
//     exit();
//   } else {
//     std::cout << "Current path detected succesfully!" << std::endl;
//     std::string path(pathbuf); 
//   }
// }
