/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#ifndef DATA_H
#define DATA_H

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <boost/logic/tribool.hpp>
#include "helper.h"

/// structure to hold a date/amount pair  
struct Entry {
  /// get the next *unread* element. Return false if all elements have been read.
  bool getNextDigit(unsigned&);
  /// get the date
  inline unsigned getDate() const {return date;}
  /// get the amount
  inline unsigned getAmount() const {return amount;}
  /// set the date
  inline void setDate(unsigned rhs) {date = rhs;}
  /// set the amount
  inline void setAmount(unsigned rhs) {amount = rhs;}
  // constructor
  inline Entry() : date{0}, amount {0},
		   doneReadingBothMembers{boost::logic::indeterminate} {}
  /// constructor with explicit initialization
  inline Entry(unsigned d, unsigned a)
    : date{d}, amount {a},
      doneReadingBothMembers{boost::logic::indeterminate} {}
private:
  unsigned date;
  unsigned amount;
  boost::logic::tribool doneReadingBothMembers; // indeterminate means that ony date has been read
};

/// elements from a csv-formated string are passed to an Entry's date and amount, respectively, line-by-line
std::istream& operator>> (std::istream &is, Entry &rhs);

/// structure to load numerical entries from a csv file; the file is read in the constructor and its contents are stored in memory.
struct Data {
 private:
  std::ifstream dataFile;
  std::vector<Entry> entries;
  std::vector<Entry>::iterator iterator;
  Entry currentEntry;
  Entry nextEntry();
public:
  /// retrieve next numerical value
  unsigned nextDigit();
  /// construct an object and read data from the specified file
  explicit Data(const std::string&);
  /// default destructor
  ~Data()=default;
  /// move constructor
  inline Data(Data&& other) : dataFile {std::move(other.dataFile)} {};
  Data(const Data&) =delete;
  Data& operator=(const Data&) =delete;
  inline Data& operator=(const Data&&) =delete;
};

#endif
