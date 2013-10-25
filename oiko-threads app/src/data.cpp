/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#include "data.h"

// ============================= Constructor ============================== 
Data::Data() :
  // init list
  pointer(0),
  end(0)
{
  // nothing here
}

// ============================= setUp ============================== 
void Data::setUp() {
  // open file
  std::ifstream myfile (settings::filename, std::ios::in | std::ios::ate);
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
  std::ifstream myfile (settings::filename, std::ios::in);      // open file 
  std::cout << "Attempting to retrieve next data enrtry." << std::endl;
#ifdef dual_mode
  osc_communication::sendOsc("Attempting to retrieve next data enrtry.");
#endif
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
    entry.date = std::stoi(rawDate.c_str());
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
    entry.amount = std::stoi(rawAmount.c_str());    
    myfile.close();		        // close file
  } else {
    std::cout << "Error: could not read entry from file - file not open" << std::endl;
  }
  std::cout << "Data entry retrieved successfully.\nDate: " << entry.date << "\nAmount: " << entry.amount << std::endl;
#ifdef dual_mode
  osc_communication::sendOsc("Data entry retrieved successfully.");
  std::string str = "Date: ";
  std::string date = static_cast< std::ostringstream* > ( &(std::ostringstream() << entry.date ) )->str();
  osc_communication::sendOsc(str.append(date));
  str = "Amount: ";
  std::string amount = static_cast< std::ostringstream* > ( &(std::ostringstream() << entry.date ) )->str();
  osc_communication::sendOsc(str.append(amount));
#endif
  // return data
  return entry;
}
