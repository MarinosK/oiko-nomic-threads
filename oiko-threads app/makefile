# this makefile is for mac with gcc and opecv installed with macports

CC = /opt/local/bin/g++-mp-4.8
CFLAGS = -I/opt/local/include -I/usr/local/include -L/opt/local/lib -L/usr/local/lib -lopencv_core -lopencv_imgproc -lopencv_calib3d -lopencv_video -lopencv_features2d -lopencv_ml -lopencv_highgui -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lserial -std=c++11 -static
DEPS = src/data.h src/pattern.h src/visualizer.h src/settings.h src/controller.h src/arduino-serial-lib.h
OBJ = src/oiko-threads.cpp src/data.cpp src/pattern.cpp src/visualizer.cpp src/settings.cpp src/controller.cpp src/arduino-serial-lib.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o application/oiko-threads $< $(CFLAGS)

oiko-threads: $(OBJ)
	$(CC) -o application/oiko-threads $^ $(CFLAGS)

clean:
	rm -rf *o
