# Week of Aug 16 #
  * Final evaluation form completed
  * Fix wrong assumptions in the test code, all tests pass now.
  * Update the wiki page for blob track demo
  * SaunierSayed executable changed to FeatureBasedTracking
  * Fix a couple of warnings and update the Tutorial page
  * The FeatureBasedTracking executable should not crash at the end anymore.
# Week of Aug 8 #
  * Wrote a new wiki page for README instructions, compilation and running of different executables.
  * BlobMatcher interface updated. The match function only asks for query and not target since the target blob might be stored in a different object (e.g. an object from BlobTracker).
  * The example now shows better debug visualization on what happens as matches occurred.
  * Fix a bug with blobs not being matched correctly due to iterator not reset.
  * Test code for blob matching module added.
# Week of Aug 1 #
  * Finally found the code that performs blob matching via position and a simple trajectory constraints. Implementing it as separate classes under the new blob track module.
  * Stumble upon an interesting design problem. How does one design a Tracker interface without relying on templates? Without template, how would one store arbitrary in the tracker?
  * Now creating a new executable called BlobTrackPedestrian. Only performs blob detection and counting for now but the outputs provide some ability to see what is going on with the new blob track module.
# Week of July 25 #
  * Plow through more of blobtrack code. It was written in the old OpenCV 1.0 style.
  * Introduce a new class called cv::BlobDetector that implements the connected component blob detector method that was used in the blobtrack sample. The blob track sample has another one which uses clustering. Need to figure out how to merge with this clustering stuff (probably when I visit blob matcher)
  * HighGUI of OpenCV SVN doesn't seem to be able to read these videos. Will stop testing on Win7 x64 until HighGUI works on this platform as well.
  * Found that BGL which comes with Boost 1.4.2 will not work under Win7 x64. It complains about tie() in adjacency\_list.hpp. Using 1.4.3 will work again.
  * Fixed the memory problem when trying to visualize the tracker as it progress.
# Week of July 18 #
  * Code is now compilable with OpenCV-SVN. Ready for future integration into OpenCV.
  * I realize that a couple of classes which I have is the same as those provided by OpenCV. So I switch over to the ones already available in OpenCV e.g. GoodFeaturesToTrackDetector.
  * In contact with Vadim regarding interface decision for the FeatureMatcher class. Since the feature2d module has already been put into OpenCV-SVN, I would rather not do something that will be removed when the next version of OpenCV comes around.
  * Going through the BlobTrack module inside of OpenCV2. Came up with a conceptual diagram of the different parts on BlobTrack module and how they relate to the feature-based tracking framework. https://docs.google.com/drawings/edit?id=1My6RCEsYmXCnXXKOUpE0Yr2G9xDBRUafY3dehNRm044&hl=en
# Week of July 11 #
  * Implemented a DFS visitor that check if a vertex (track) in the graph is activated before performing component grouping. Results show correct component grouping for each frame but the component id is not uniform temporally. What I need is a persistent storage for the component\_id property of a track.
  * Speed is much slower now (about 10 times slower) due to the way I built the graph. It starts out with too many edges. Considering pruning this. UPDATE: Only nearby tracks are connected when a new track is added to the graph, this speeds up the code a bit.
  * Removed storage of previous points and updating of average position.
  * Added the storage of component id. Component ID is iteratively update as processing is done. Visualization now shows different colors for different tracks according to the component id (and available color palletes.
  * Update flag parsing to be more useful when running concurrently multiple instances of SaunierSayed program.
  * Completed midterm evaluation

# Week of July 4 #
  * Happy Independence Day
  * Instead of checking whether a track variance in the previous N frames is > min\_distance\_moved\_required. Now checking that all N frames have displacements > min\_distance\_moved\_required. This very quickly removes stationary points but at the same time, stalling vehicle will instantly get dropped.
  * Refactor the UpdatePoints() method into separate smaller methods to make it clean.
# Week of June 27 #
  * Found a bug which is fixed when setting --min\_distance\_moved\_required 0
# Week of June 20 #
  * Fix a bug in which edges are not removed when vertices are already removed
  * Fix naming scheme of id for new tracks. New track id are now incrementally numbered. This fix the problem in which points that do not have enough variance are not removed.
  * Visualization now has real world coordinate next to each track. Things are more crowded in certain parts of the video.
  * All tests are now passed.
  * More parameters of feature grouper is exposed to command line flags
  * (REGRESSION) Running with --debug\_gui flag is now very slow (possibly due to intensive window drawings). For now, it is recommended to run with --nodebug\_gui flag.
# Week of June 13 #
  * Attended CVPR 2010
  * Implementation of systematic method for removing static points are done.
  * Points that are not tracked after a while will also be removed
  * (BUG) There seems to exists edges even when the target points have already been removed
# Week of June 6 #
  * Finishing implementation of SaunierSayed
    * Give decent results with tracked objects persist despite being occluded by foreground objects.
    * Video of first 20 seconds of test2.avi video uploaded to YouTube.
    * Implementing a systematic method for removing static points (those that are left after the vehicle has left the scene, those that are left when the vehicle underwent obstacles).
# Week of June 1 #
  * Finishing implementation of SaunierSayed
    * Homography matrices still give weird (x,y) locations of tracked points on the world plane
    * Resulting output does not give any connected components (probably due to incorrect world point coordinates
    * Obtained parameter values from Dr. Saunier. Trying them now but still no luck.
  * SaunierSayed executable now uses Google GFlags to parse algorithm parameters
# Week of May 24 #
  * Decided to go with Boost Graph Library
    * Writing Unit Tests on simple graph code to understand how to use Boost Graph (test\_boost\_graph.cpp)
    * On going progress to refactor implementation of SauinierSayed Feature Grouping to make use of Boost Graph entirely instead of of mash-ups of std::map<int, ...>
  * Fiddling with BGL
    * Finally decide to use listS for vertex and vecS for edges
    * Can find Connected Components
    * Can add vertices, edges are added if tracked for a while, edges are severed if condition no longer meets
    * Ready to plug into algorithm implementation for final step

# Week of May 17 #
  * Clean up and merge
    * Merge the latest proposal from PluggableDescriptors wiki page on WillowGarage into the code
    * Update BlobFeature and EMDMatcher so that the whole project can compile. Problem remains since these features are region-based and do not fully fit into the current interface.
    * Remove unnecessary stuff that is non-related to this project
    * Put together the boiler plate for implementation of Sauinier and Sayed
  * ShiTomasi feature detector implemented
    * KLT Tracker implements the DescriptorMatchGeneric
    * Add a search method to descriptor match generic for cases when we want to search for a descriptor in input image (instead of matching them to certain descriptors)
    * Visualize the matches using a WindowPair
  * Added DemoPage
    * Several tests implemented showing the ability to add new points into tracks
    * Switch to using test2.avi and ground-truth homography matrix
    * Implemented half of Saunier Sayed algorithm
    * At half-way in implementing the graph structure for tracks connection using Boost Graph Library

# Week of April 26 #
  * Clean up + auto build setup
    * Set up Hudson with Hg support, CMake support + automatic running of GTest and tallying the report. So far all tests pass.
    * Removed some unnecessary stuff
  * I got accepted for Google Summer of Code 2010 to work on Feature-based tracking with OpenCV.
    * Created this project on Google Code hosting
    * Committed the first batch of code
    * Read OpenCV Coding Style Guide
    * Corresponding with Dr. Saunier on certain aspects of the project (how to report changes, ...)