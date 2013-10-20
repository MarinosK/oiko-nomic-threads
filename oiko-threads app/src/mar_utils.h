
// Various C++ Utilities
// by Marinos Koutsomichalis (marinos@agxivatein.com)

/* this header is only meant for privite use - if you ever happen to use it bare in mind that no guarantee of functionlity is given */

#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>

/// ---------  DEBUGGING UTILITIES
// debug print macro
#define DEBUG_PRINT(A) std::cout << #A << ": " << (A) << std::endl;

/// --------- OTHER UTILITIES
// post project info 
#define PROJECT_INFO_PRINT(A) std::cout << (A) << "\nDeveloped by (c) Marinos Koutsomichalis (marinos@agxivatein.com)\nUse at your own risk!" << std::endl;

/// --------- THIRD PARTY
// these are from Require.h header found on Bruce Eckel's Thinking in C++, 2nd Ed book

namespace require {

  inline void require(bool requirement, 
		      const char* msg = "Requirement failed") {
    using namespace std;
    if (!requirement) {
      fprintf(stderr, "%s", msg);
      exit(1);
    }
  }

  inline void requireArgs(int argc, int args, 
			  const char* msg = "Must use %d arguments") {
    using namespace std;
    if (argc != args + 1) {
      fprintf(stderr, msg, args);
      exit(1);
    }
  }

  inline void requireMinArgs(int argc, int minArgs,
			     const char* msg = 
			     "Must use at least %d arguments") {
    using namespace std;
    if(argc < minArgs + 1) {
      fprintf(stderr, msg, minArgs);
      exit(1);
    }
  }
  
  inline void assure(std::ifstream& in, 
		     const char* filename = "") {
    using namespace std;
    if(!in) {
      fprintf(stderr,
	      "Could not open file %s", filename);
      exit(1);
    }
  }

  inline void assure(std::ofstream& in, 
		     const char* filename = "") {
    using namespace std;
    if(!in) {
      fprintf(stderr,
	      "Could not open file %s", filename);
      exit(1);
    }
  }
}
