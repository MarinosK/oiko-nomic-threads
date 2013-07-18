# this makefile is for mac with gcc and opecv installed with macports

CC = g++
CFLAGS = -I/opt/local/include -L/opt/local/lib -lopencv_core -lopencv_imgproc -lopencv_calib3d -lopencv_video -lopencv_features2d -lopencv_ml -lopencv_highgui -lopencv_objdetect -lopencv_contrib -lopencv_legacy
DEPS = src/data.h src/pattern.h src/visualizer.h
OBJ = src/oiko-threads.cpp src/data.cpp src/pattern.cpp src/visualizer.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o application/oiko-threads $< $(CFLAGS)

oiko-threads: $(OBJ)
	$(CC) -o application/oiko-threads $^ $(CFLAGS)

clean:
	rm -rf *o
