/*
  Coded by Marinos Koutsomichalis for the Oikonomic Threads projects.
  Oikonomic Threads (c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra. 
  Installation for algorithmically controlled knitting machine and open data
*/

#include <iostream>
#include <cstring>
#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"


#define PORT 7000

class ExamplePacketListener : public osc::OscPacketListener {
protected:
  virtual void ProcessMessage( const osc::ReceivedMessage& m, 
			       const IpEndpointName& remoteEndpoint ) {
    (void) remoteEndpoint; // suppress unused parameter warning
    try {
      osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
      const char *a;
      args >> a >> osc::EndMessage; 
      std::cout << a << std::endl;      
    }
    catch( osc::Exception& e ){
      // do nothing
    }
  }
};

int main(int argc, char* argv[]) {
  (void) argc; // suppress unused parameter warnings
  (void) argv; // suppress unused parameter warnings
  ExamplePacketListener listener;
  UdpListeningReceiveSocket s
    (IpEndpointName( IpEndpointName::ANY_ADDRESS, PORT),
     &listener );
  s.RunUntilSigInt();
  return 0;
}

