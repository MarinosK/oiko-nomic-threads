
#include "data.h"

// ============================= Constructor ============================== 
Data::Data() :
  // init list
  pointer(0)
{
  // nothing here
}

// ============================= setUp ============================== 
void Data::setUp() {
  // open file
  std::ifstream myfile (FILENAME, std::ios::in | std::ios::ate);
  if (myfile.is_open()) {
    // calculate end of file
    end = myfile.tellg();
    myfile.close();
  }
}

// ============================= nextEntry ============================== 
Entry Data::nextEntry() {;
  std::string rawDate; 
  std::string rawAmount;
  Entry entry;
  std::ifstream myfile (FILENAME, std::ios::in);      // open file 
  if (myfile.is_open()) {
    myfile.seekg (pointer, std::ios::beg);	    // set pointer to next entry
    char next;
    // read date
    while(myfile.get(next)) {
      if (next != ',')  {  
	rawDate += next;
      } else {
	break;  
      }              
    }
    entry.date = std::atoi(rawDate.c_str());
    // read amount
    while(myfile.get(next)) {
      if (next != '\n')  {  
	rawAmount += next;
      } else {
	// update pointer
	pointer =  myfile.tellg();
	if (pointer >= end) pointer = 0;
	break;  
      }              
    }
    entry.amount = std::atoi(rawAmount.c_str());    
    myfile.close();		        // close file
  } else {
    std::cout << "Error: could not read entry from file - file not open" << std::endl;
  }
  // return data
  return entry;
}
