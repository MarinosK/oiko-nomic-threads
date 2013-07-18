
/*
part of Oikonomic Threads project
coded by Marinos Koutsomichalis (c) 2013, Heraklion
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



struct Entry {
  unsigned int date;
  unsigned int amount;
};

class Data {
 public:
  void setUp();
  Entry nextEntry();
 private:
  long pointer;		// the position of the next piece of data
  unsigned long end;	// end of the file
};
