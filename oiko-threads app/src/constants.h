// some useful macros (so that I can easily change those constants with compiler flags)

#ifndef PREAMPLE
#define PREAMPLE  "\n*****\nOiko-nomic Threads \ninstallation for algorithmically controlled knitting machine and open data \n(c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra\n*****\n\npress q (and <return>) to quit.\nstarting..\n"
#endif
#ifndef WIDTH
#define WIDTH 1050
#endif
#ifndef HEIGHT
#define HEIGHT 600
#endif
#ifndef OSC_PATH
#define OSC_PATH "192.168.1.2"
#endif
#ifndef BAUD_RATE
#define BAUD_RATE 115200
#endif
#ifndef GUI_WINDOW_NAME
#define GUI_WINDOW_NAME "Oiko-nomic Threads: Knitting emulation"
#endif
#ifndef KNIT_WIDTH
#define KNIT_WIDTH 160
#endif
#ifndef OSC_PORT
#define OSC_PORT 7000
#endif
#ifndef SPEED           // nested ifs start here 
#ifdef  EMULATION_MODE 
#define SPEED 2000
#else
#define SPEED 1
#endif
#endif                  // to here
