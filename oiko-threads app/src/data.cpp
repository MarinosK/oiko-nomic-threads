
#include "data.h"

// ================================ Entry ================================

bool Entry::getNextDigit(unsigned& rhs) {
  if (boost::logic::indeterminate(doneReadingBothMembers)) {
    rhs = date;
    doneReadingBothMembers = false;
    return true;
  } else if (!doneReadingBothMembers) {
    rhs = amount;
    doneReadingBothMembers = true;
    return false;
  } else // if (doneReadingBothMembers)
    helper::myThrow<std::logic_error>
      ("Entry: both members have been already read");
}

// ========================= overload operator>> =========================

std::istream& operator>> (std::istream &is, Entry &rhs) {
  char delim;
  std::string str;
  std::getline(is, str);
  std::istringstream sstream {str};
  unsigned date{}, amount{};
  sstream >> date >> delim >> amount;
  rhs.setDate(date);
  rhs.setAmount(amount);
  return is;
}

// ============================= Constructors ============================
Data::Data(const std::string& filename) :
  dataFile {filename},
  entries {},
  iterator {},
  currentEntry {} {
    if (!dataFile)
      helper::myThrow<std::runtime_error>
	("failed to open "+filename+" data file");
    Entry e{};
    while (dataFile >> e) entries.emplace_back(e);
    dataFile.close();
    iterator = entries.begin();
    currentEntry = nextEntry();
  }

// ============================= nextEntry ============================== 
Entry Data::nextEntry() {
  if (iterator == entries.end()) iterator = entries.begin();
  return *(iterator++);
}

// ============================== nextDigit ==============================

unsigned Data::nextDigit() {
  helper::log("retrieving next data entry");
  unsigned digit{};
  if (!currentEntry.getNextDigit(digit)) currentEntry = nextEntry();
  std::ostringstream message{};
  message << digit << " " << "has been retrieved";
  helper::log(message.str());
  return digit;
}

