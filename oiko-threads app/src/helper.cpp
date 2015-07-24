
#include "helper.h"


unsigned settings::width {WIDTH};
unsigned settings::height {HEIGHT};
unsigned settings::speed {SPEED};

// ================== static helper functions ==================
/// static helper function: appends a relative path to an absolute one
static const std::string appendPath(std::string path, const std::string& relativePath) {
  path.append("/");
  path.append(relativePath);
  return path;
}

/// static helper function: gets absolute path
static const std::string getAbsolutePath() {
  boost::filesystem::path full_path {boost::filesystem::current_path()};
  return full_path.string();
}

/// static helper function: fills vector with the paths of the original motifs
static std::vector<const std::string>
getVectorWithPathsToOriginalMottifs() {
  std::vector<const std::string> result;
  for (int i=0; i<10; ++i) {
    std::ostringstream path{};
    path << "/data/" << i << ".png";
    result.emplace_back(appendPath(getAbsolutePath(), path.str()));
  }
  return result;
}

// ========================== runtime constants ==========================

#ifndef EMULATION_MODE
const std::string settings::hardwarePath {helper::trackHardware()};
#else
const std::string settings::hardwarePath {};
#endif

const std::string settings::dataFile = appendPath(getAbsolutePath(),"data/PSGR.csv");  // the filename to use

const std::vector<const std::string> settings::pathsToOriginalMottifs {
  getVectorWithPathsToOriginalMottifs() };

// ========================== helper functions ==========================

void helper::setWidthAndHeightAndSpeed(int argc, char** argv) {
  try {
    if (argc > 1) {
      settings::width = boost::lexical_cast<unsigned>(argv[1]);
      std::ostringstream message {};
      message << "width set to: " << settings::width << std::endl;
      helper::log(message.str());
    } else
      helper::log("no valid argument provided, using default width");
    if (argc > 2) {
      settings::height  = boost::lexical_cast<unsigned>(argv[2]);
      std::ostringstream message {};
      message << "height set to: " << settings::height << std::endl;
      helper::log(message.str());
    } else
      helper::log("no valid argument provided, using default height");
    if (argc > 3) {
      settings::speed = boost::lexical_cast<unsigned>(argv[3]);
      std::ostringstream message {};
      message << "speed set to: " << settings::speed << std::endl;
      helper::log(message.str());
    } else
      helper::log("no valid argument provided, using default speed");
  }  catch(...) {
    helper::log("no valid argument(s) provided, using default value(s)");
  }
}

#ifndef EMULATION_MODE
// I need to refactor this at some point in proper C++11 style
std::string helper::trackHardware() {
  helper::log("detecting hardware over serial..");
  std::string path {};
  FILE *pipe = popen("ls /dev/tty.usbmodem*", "r");
  if (!pipe) {
    helper::log("failed to open temporary file: press <enter> to retry");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    helper::trackHardware(); // recursive call
  } else {
    char buffer[128];
    while(!feof(pipe)) {
      if (fgets(buffer, 128, pipe) !=NULL) {
	path += buffer; 
      } 
    }   
    if (path == "") {
      helper::log("no harware found:\n\tconnect the machine to a usb port and press <enter> to retry");
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
      helper::trackHardware(); // recursive call
    } else {
      pclose(pipe);
      path = path.substr(0,path.length()-1); // remove gap from the end
      std::ostringstream message {};
      message << "hardware detected on serial port: "<< path << std::endl;
      helper::log(message.str());
    }
  }
  return path;
}
#endif

#ifdef DUAL_MODE
void helper::sendOsc(const std::string& message) {
  UdpTransmitSocket transmitSocket {
    IpEndpointName(settings::oscPath, settings::oscPort) };
  char buffer[1024]; 
  memset(&buffer[0], 0, sizeof(buffer)); // initiallize to 0
  osc::OutboundPacketStream osc_stream {buffer, 1024};
  osc_stream.Clear();
  osc_stream << osc::BeginMessage( "/oiko-threads" ) 
	     << message.c_str() // send message
	     << osc::EndMessage;
  transmitSocket.Send(osc_stream.Data(), osc_stream.Size());
}
#endif

void helper::testShow(cv::Mat mat) {
  cv::namedWindow("test");
  cv::imshow("test", mat); 
  cv::waitKey(0);  // wait for key  
}
