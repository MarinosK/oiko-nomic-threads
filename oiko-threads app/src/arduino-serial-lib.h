// this file has been originally written by Tod E. Kurt, http://todbot.com/blog/ and adapted in C++ by Marinos Koutsomichalis for the purposes of the Oiko-Nomic Threads project - modifications have been minor, therefore all credits should be reserved for Tod E. Kurt


#ifndef __ARDUINO_SERIAL_LIB_H__
#define __ARDUINO_SERIAL_LIB_H__

#include <cstdint>   // Standard types 
#include <cstdio>    // Standard input/output definitions 
#include <unistd.h>   // UNIX standard function definitions 
#include <fcntl.h>    // File control definitions 
#include <cerrno>    // Error number definitions 
#include <termios.h>  // POSIX terminal control definitions 
#include <cstring>   // String function definitions 
#include <sys/ioctl.h>

namespace arduino_lib {
  int serialport_init(const char* serialport, int baud);
  int serialport_close(int fd);
  int serialport_writebyte( int fd, uint8_t b);
  int serialport_write(int fd, const char* str);
  int serialport_read_until(int fd, char* buf, char until, int buf_max,int timeout);
  int serialport_flush(int fd);
}

#endif

