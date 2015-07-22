# this makefile is for mac with gcc and opecv installed with macports

CC = clang++
PREFIX = /Users/marinos/projects/ongoing/oiko-threads\ app\ REVISITED/

# dynamic linking (clang)
# CFLAGS = -I/opt/local/include -I/usr/local/include -L/opt/local/lib -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -std=c++11

# static linking (clang)
# CFLAGS = -I/opt/local/include -Isrc -I/usr/local/include $(PREFIX)$/static_libs/libopencv_core.a $(PREFIX)$/static_libs/libopencv_highgui.a $(PREFIX)$/static_libs/libopencv_imgproc.a  $(PREFIX)$/static_libs/liblibjpeg.a  $(PREFIX)$/static_libs/liblibpng.a  $(PREFIX)$/static_libs/libzlib.a $(PREFIX)$/static_libs/liblibtiff.a $(PREFIX)$/static_libs/liblibjasper.a $(PREFIX)$/static_libs/libIlmImf.a -std=c++11

#-F/System/Library/PrivateFrameworks -framework Cocoa -framework QTKit -framework QuartzCore -framework AppKit -framework OpenCL

#  -mmacosx-version-min=10.6

DEPS = src/helper.h src/oikoThreadsApp.h src/data.h  src/sendOsc.h  #src/pattern.h src/segment.h  #src/visualizer.h src/controller.h src/arduino-serial-lib.h 
OBJ = src/oiko-threads.cpp src/helper.cpp src/data.cpp src/oikoThreadsApp.cpp  #src/segment.cpp  src/pattern.cpp #src/visualizer.cpp src/controller.cpp src/arduino-serial-lib.cpp  

DUAL_OBJ = $(OBJ) src/sendOsc.cpp src/ip/posix/UdpSocket.cpp src/ip/posix/NetworkingUtils.cpp src/osc/OscOutboundPacketStream.cpp src/osc/OscTypes.cpp src/ip/IpEndpointName.cpp

TEST_OBJ = src/main_tests.cpp src/tests.cpp src/helper.cpp src/data.cpp src/oikoThreadsApp.cpp  #src/segment.cpp  src/pattern.cpp #src/visualizer.cpp src/controller.cpp src/arduino-serial-lib.cpp  


compile: $(OBJ)
	$(CC) -o application/oiko-threads $^ $(CFLAGS) -O3 

dual: $(DUAL_OBJ)
	$(CC) -o application/oiko-threads $^ $(CFLAGS) -O3 -DDUAL_MODE

emulation: $(OBJ)
	$(CC) -o application/oiko-threads $^ $(CFLAGS) -O3 -DEMULATION

debug:  $(OBJ)
	$(CC) -o debug/oiko-threads $^ $(CFLAGS) -g -DDEBUG

test:   $(TEST_OBJ)
	$(CC) -o debug/tests $^ $(CFLAGS) -lgmock -lgtest -g -DDEBUG -DTEST 

%.o: %.c $(DEPS)
	$(CC) -c -o application/oiko-threads $< $(CFLAGS)

clean:
	rm -rf applications/*o applications/*dSYM applications/oiko-threads debug/*o debug/*dSYM debug/oiko-threads

.PHONY: oiko-nomic dual emulation debug clean
