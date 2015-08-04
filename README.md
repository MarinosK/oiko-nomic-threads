OIKO-NOMIC THREADS
An installation for algorithmically controlled knitting machine and open data 
(c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psarra

Software and Hardware development for Oiko-nomic threads was realized by Marinos Koutsomichalis, Afroditi Psarra and Maria Varela.  Related code, texts and images are distributed under the Attribution-NonCommercial-ShareAlike 3.0 Unported Creative Commons Licence (details here: http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US). 

> THIS MATERIAL IS DISTRIBUTED AS IS WITH NO GUARANTEE OF FUNCTIONALITY OR RELEVANCE TO THIRD PARTY PROJECTS - THE DEVELOPERS ARE THUS NOT TO BE HELD RESPONSIBLE FOR PERSONAL INJURIES, HARDWARE, FINANCIAL, OR ANY OTHER LOSSES AND IN GENERAL FOR ANY MISFORTUNATE EVENT CAUSED BY THE DESCRIBED SOFTWARE/HARDWARE OR IN THE PROCESS OF ATTEMPTING TO IMPLEMENT IT. IF YOU DON'T AGREE WITH THE AFOREMENTIONED YOUR ARE NOT ALLOWED TO USE THE MATERIAL PROVIDED HEREIN

Contact: 
marinos [at] agxivatein.com
stereochic [at] gmail.com
m.mivon [at] gmail.com

DESCRIPTION:
Software related with OIKO-NOMIC THREADS installation art project.  The oiko-threads command-line app retrieves data from a file, encodes them with respect to algorithmic instructions and a database of traditional motiffs and controls algorithmically a hacked knitting machine (Brother 950i model).  The Brother 950i knitting machine was heavily hacked: 'brain' of the machine was completely removed (along with many other elecronics parts) and substituted by an Arduino DUE running custom firmware that communicates with the oiko-threads app, informs the latter of the K-carriage's position and encodes image data sent by it into electronic/mechanical operations that will eventually knit patterns into a piece of fabrik. Details follow>

dumpOsc app:
Just a dump osc receiver app in C++; used for testing purposes and in DUAL_MODE. 


OIKO_THREADS APP:

General Information:
* designed and implemented by Marinos Koutsomichalis in C++14 using STL, Boost and openCV.
* the application is tested and reported to work in Mac Os X 10.8 operating system with clang
* in its current form the application is not cross platform.

To Compile:
Given that xcode, xcode-tools, cmake, doxygen, openCV, Boost and clang is installed, try:

cd oiko-threads app
mkdir build
cd build
cmake <OPTIONS> ..
make

this will create an Install folder with the executable, the data assets, some tests and the auto-generated documentation. Options are as follows:

    * -DCMAKE_BUILD_TYPE=Debug or =Release -> to switch between debug/release builds,default it Release
    * -DEMULATION_MODE=ON -> for a video only version (no machine interaction)
    * -DDUAL_MODE=ON -> also sends stdout via OSC (dumpOsc listens to this stream); for use when the host computer does no support dual screen mode.
    * -DTEST_MODE=OFF -> do not compile/run the tests
    * -DBUILD_DOCUMENTATION=OFF -> do not generate documentation

more, there are a number of important constants that can be defined in compile time

    * -DWIDTH            -> projection width
    * -DHEIGHT           -> projection height
	* -DOSC_PATH         -> OSC IP address
	* -DBAUD_RATE        -> default baud rate 
	* -DGUI_WINDOW_NAME  -> used internally
	* -DOSC_PORT         -> OSC port
	* -DSPEED            -> animation speed (emulation_mode), wait time (nromal mode)
	
To Use:
Given that everything is properly connected and that the firmaware is loaded to the machine, just run the oiko-threads app. Custom width, height and speed can be set as arguments to the executable.

---- Algorith Description and Flow Diagram ----

Data Retreival: 
* an instance of Data class retreives entries from the file when asked by the Pattern encoding algorithm

Pattern Encoding:
1 ask the next entry (could be date or amount, doesn't actually matter)
2 encode it to the corresponding patterns
3 distribute (based on meta-data or stochastic process) these patterns to fill an area with the desired WIDTH in pixels -> every patterns will be given an area so that the total width will be WIDTH but the individual widths will not be equal
4 normalize originals to much distributed size based on width (normalize in this context would be to scale the original images to match the given length [as calculated in step 3] - height is to be proportionally scaled according to the patterns original perspective)
5 store normallized images to std::vector<cv::Mat> patterns
6 calculate a line of pixels (totaling WIDTH) and store it to cv::Mat output / read the pixel values from the normalized patterns and erase lines one by one when read
7 when some pattern is done and there are no more lines left to read from, repeat steps 1-4
8 these new cv::Mats should be merged with the remaing cv::Mats (from step 7) and the result should be a new vector of cv::Mats (stored in cv::Mat patterns again) -> Merge should be a bitwise OR operation on binary pixel values (to be implemented somehow)
9 Repeat steps 6 and 7

ARDUINO FIRMWARE:

General Information:
* designed and implemented by Marinos Koutsomichalis and Afroditi Psarra.
* the code will update the position of the solenoids according to messages received from over Serial from the oiko-threads app and will respond when succesfully done so. 
* due to certain technical restrictions only a certain range of needles is used in the machine, namely 16-175.

HARDWARE:
General Information:
* designed and implemented by Maria Varela, Afroditi Psarra and Marinos Koutsomichalis
* of invaluable help has been PCB designs and instructions ditributed by the Knitic Project (https://github.com/mcanet/knitic) (with thanks)


