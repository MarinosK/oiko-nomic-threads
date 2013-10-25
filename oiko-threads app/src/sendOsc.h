/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#ifndef _SENDOSC_H
#define _SENDOSC_H 1

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include <string>

#include "settings.h"

namespace osc_communication { 
  void sendOsc(const std::string&);
}

#endif /* _SENDOSC_H */

