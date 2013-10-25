/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#include "sendOsc.h"

void osc_communication::sendOsc(const std::string& message) {
  
  UdpTransmitSocket transmitSocket(IpEndpointName(settings::oscPath.c_str(), settings::oscPort));
  
  char buffer[1024]; 
  memset(&buffer[0], 0, sizeof(buffer)); // initiallize to 0
  osc::OutboundPacketStream p( buffer, 1024 );

  p.Clear();
  p << osc::BeginMessage( "/oiko-threads" ) 
    << message.c_str() // send message
    << osc::EndMessage;
  
  transmitSocket.Send(p.Data(), p.Size());
}
