/* Data.h */

/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

// this class takes care of accessing data from a csv file containing amounts and dates only
// the file has to be preprocessed to only contain 'date,amount' entries per line (no blank or text files allowed)
// date and amount should be integers or floats
// date should be in this format: YYYYMMDD
// no sanity check ! so make sure file is formated according to the above

#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include "settings.h"
#include "mar_utils.h"

struct Entry {
  unsigned int date;
  unsigned int amount;
};

class Data {
 private:
  // data
  long pointer;		// the position of the next piece of data
  unsigned long end;	// end of the file
  // functions
  explicit Data();      // private constructor
  void setUp();
  Entry nextEntry();
 public:
  friend class Pattern; // members of Pattern may access this class
  Data(const Data&) =delete;
  Data& operator=(const Data&) =delete;
  ~Data() =default;
};
