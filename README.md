OIKO-NOMIC THREADS
An installation for algorithmically controlled knitting machine and open data 
(c) 2013 Marinos Koutsomichalis, Maria Varela, Afroditi Psara

Software and Hardware development for Oiko-nomic threads was realized by Marinos Koutsomichalis, Afroditi Psarra and Maria Varela.  Related code, texts and images are distributed under the Attribution-NonCommercial-ShareAlike 3.0 Unported Creative Commons Licence (details here: http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US). 

> THIS MATERIAL IS DISTRIBUTED AS IS WITH NO GUARANTEE OF FUNCTIONALITY OR RELEVANCE TO THIRD PARTY PROJECTS - THE DEVELOPERS ARE THUS NOT TO BE HELD RESPONSIBLE FOR PERSONAL INJURIES, HARDWARE, FINANCIAL, OR ANY OTHER LOSSES AND IN GENERAL FOR ANY MISFORTUNATE EVENT CAUSED BY THE DESCRIBED SOFTWARE/HARDWARE OR IN THE PROCESS OF ATTEMPTING TO IMPLEMENT IT. IF YOU DON'T AGREE WITH THE AFOREMENTIONED YOUR ARE NOT ALLOWED TO USE THE MATERIAL PROVIDED HEREIN

Contact: 
marinos [at] agxivatein.com
stereochic [at] gmail.com
m.mivon [at] gmail.com

> IMPORTANT: IN ITS CURRENT STATE SOFTWARE/HARDWARE IS UNDER HEAVY DEVELOPMENT AND NOT FUNCTIONAL 

DESCRIPTION:
Hardware and software related with OIKO-NOMIC THREADS installation art project.  The oiko-threads command-line app retrieves data from a file, encodes them with respect to a complex algorithm and a database of ethnological motiffs and controls algorithmically a hacked knitting machine (Brother 950i model).  The Brother 950i knitting machine was heavily hacked: 'brain' of the machine was completely removed (along with many other elecronics parts) and substituted by an Arduino DUE running custom firmware that communicates with the oiko-threads app, informs the latter of the K-carriage's position and encodes image data sent by it into electronic/mechanical operations that will eventually knit patterns into a piece of fabrik. Details follow>


OIKO_THREADS APP:

General Information:
* designed and implemented by Marinos Koutsomichalis in C++ using STL, Boost and openCV headers and libraries.
* the application is tested and reported to work in Mac Os X 10.8 operating system
* in theory the application can be ported to other operating systems
To Compile/Use: 
* openCV, Boost and g++ should be installed and configured
* edit makefile to make sure that all the flags are set according to your specific configuration
* edit Settings.h to include the paths of the motiffs and the dataset, as well as the rest settings 
* use make and a binary will be created in the application folder
* remember to put all the required files into the data folder
* the dataset should be a csv file (named PSGR.csv if Settings.h is left untouched) containing lists of dates and ammounts (formated as YYYYMMDD, AMMOUNT) with no blank or text lines
* the raw patterns to be used should be in .png format

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
* designed and implemented by Afroditi Psarra in Wiring.
Usage/etc:
* [.. to be edited ..]


HARDWARE:
General Information:
* designed and implemented by Maria Varela, Afroditi Psarra and Marinos Koutsomichalis
* of invaluable help has been PCB designs and instructions ditributed by the Knitic Project (https://github.com/mcanet/knitic) (with thanks)
Instructions/Implementation
* [..to be edited ]


ACKNOWELEDGEMENTS:
Daphne Dragona, Tina Panti, Daphne Vitali,Thanos Eleftherakos, the Knitic Project.
