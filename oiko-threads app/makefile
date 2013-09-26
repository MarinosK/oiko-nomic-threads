# this makefile is for mac with gcc and opecv installed with macports

CC = /opt/local/bin/g++-mp-4.8

# dynamic linking
# CFLAGS = -I/opt/local/include -I/usr/local/include -L/opt/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -std=c++11

# static linking
CFLAGS = -I/opt/local/include -I/usr/local/include /Users/marinos/projects/ongoing/oiko-nomic-threads/oiko-threads\ app/static_libs/libopencv_core.a /Users/marinos/projects/ongoing/oiko-nomic-threads/oiko-threads\ app/static_libs/libopencv_highgui.a /Users/marinos/projects/ongoing/oiko-nomic-threads/oiko-threads\ app/static_libs/libopencv_imgproc.a  /Users/marinos/projects/ongoing/oiko-nomic-threads/oiko-threads\ app/static_libs/liblibjpeg.a  /Users/marinos/projects/ongoing/oiko-nomic-threads/oiko-threads\ app/static_libs/liblibpng.a  /Users/marinos/projects/ongoing/oiko-nomic-threads/oiko-threads\ app/static_libs/libzlib.a /Users/marinos/projects/ongoing/oiko-nomic-threads/oiko-threads\ app/static_libs/liblibtiff.a /Users/marinos/projects/ongoing/oiko-nomic-threads/oiko-threads\ app/static_libs/liblibjasper.a /Users/marinos/projects/ongoing/oiko-nomic-threads/oiko-threads\ app/static_libs/libIlmImf.a -F/System/Library/PrivateFrameworks -framework Cocoa -framework QTKit -framework QuartzCore -framework AppKit -framework OpenCL -std=c++11

# deprecated building configurations
# CFLAGS = -I/opt/local/include -I/usr/local/include -L/opt/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -std=c++11 -Bstatic
# CFLAGS = -I/opt/local/include -I/usr/local/include -L./static_libs -Wl,-Bstatic -lopencv_core -lopencv_highgui -lopencv_imgproc -Wl, -Bdynamic -lcrt0 -Wl,--as-needed -std=c++11 

DEPS = src/data.h src/pattern.h src/visualizer.h src/settings.h src/controller.h src/arduino-serial-lib.h
OBJ = src/oiko-threads.cpp src/data.cpp src/pattern.cpp src/visualizer.cpp src/settings.cpp src/controller.cpp src/arduino-serial-lib.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o application/oiko-threads $< $(CFLAGS)

oiko-threads: $(OBJ)
	$(CC) -o application/oiko-threads $^ $(CFLAGS)

clean:
	rm -rf *o
