# Compilation #

To compile this project, you will need to use CMake. Start CMake, choose opencv-feature-tracker as the source folder and any folder as your build folder. A out-of-source build is recommended.

## Prerequisite ##

You will need
  * GTest http://code.google.com/p/googletest/
  * OpenCV SVN https://code.ros.org/svn/opencv/trunk
  * GFlags http://code.google.com/p/google-gflags/
  * Boost version 1.4.3 or later http://sourceforge.net/projects/boost/files/boost/1.43.0/

Under Ubuntu, you can get gtest and boost with

> sudo apt-get install libboost-dev libgtest-dev

For GFlags, it is best that you download it and perform

> ./configure && make && sudo make install

## CMake compilation flags ##

A screenshot showing the CMake window is found below

![http://lh6.ggpht.com/_A6BW9X8vOFE/TGFGZvGW83I/AAAAAAAAO5Q/p4Jb9aNTzo0/s800/building1.png](http://lh6.ggpht.com/_A6BW9X8vOFE/TGFGZvGW83I/AAAAAAAAO5Q/p4Jb9aNTzo0/s800/building1.png)

There are a couple of flags that you can use, the most important are:
  * COMPILE\_TESTS: You will want to check this in order to run the unit-tests which give you important usage examples. It is a very good way to get to know what each  function/method does and how to use it.
  * OpenCV\_DIR: Path to the **build** directory of OpenCV SVN. Make sure you choose the build directory and not the source directory.

The flag USE\_TBB is currently not in used. The variables for GTest and GFlags will be found automatically by CMake if you have installed these libraries into your system. Otherwise, you can simple set those variables by hand.

# A foreword about passing in arguments #
The executables provided uses GFlags to parse command line arguments. Thus, if there is a boolean option --do-this-for-me, to set this option to false, you pass in --nodo-this-for-me. This is how GFlags handle Boolean flags. More information on GFlags can be found in http://google-gflags.googlecode.com/svn/trunk/doc/gflags.html

# Running the sample programs #
All main programs are found under files with the extension .cxx . Some of them are for special purposes. Most programs have a usage note or a flag parsing component. That means the easiest way to figure out what a specific program do is to run it with no argument or with --help as the only argument.

There are 3 that are very important as they were the main focus of this project during the summer:
  * RunAllTests: Run this program with the working directory set as the source directory and it will tell you what might go wrong. All data used in testing are found inside the test/data folder.
  * FeaturedBasedTracking: This is a sample program that shows the results of the Feature-based tracker. To run it, you simply give it the input video, the homography matrix and the output file. There are many flags that you can configure, a sample set is provided in this DemoPage
  * BlobTrackPedestrian: This program performs the latest code that we have for blob tracking pedestrian. The program is incomplete since it depends on an incomplete blob tracker module. The wiki page for this program is found at BlobTrackDemo.

# Other miscellaneous #
We include a modified version DAISY 1.8.1 that fits into the interface for feature detection/extraction/matching. The modification made was so that DAISY can be compiled along with this project using CMake.