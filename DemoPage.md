# Point Matching with Feature Grouping, v 0.2.4 #
Fixed a small bug where it crashes at the end if there is no connected component to be found.

./FeatureBasedTracker --nodebug\_gui --visualize\_per\_step test2.visualize.avi test2\_short.avi test2.avi.homography.mat output.txt

# Point Matching with Feature Grouping, v 0.2.3 #
This version clean the output even more. Different components have different colors. Speed is improved.

http://www.youtube.com/watch?v=21yFZKX9mW4

Ran with the following flags
--min\_distance\_moved\_required 10 test2.avi test2.avi.homography.mat test2.avi.output

# Point Matching with Feature Grouping, v 0.2.2 #
This version fixes the problem of remaining tracks when all edges are removed. Stationary tracks are now removed. Outputs are cleaner. The parameters in this video is not tuned so when tracks are activated, it is over extended.

There are also some parameters in the feature detector that can be better tuned.

http://www.youtube.com/watch?v=sZQ44xcA2iQ

# Point Matching with Feature Grouping, v 0.2.1 #
This version fixes the problem of the previous version for over connection of tracks.

http://www.youtube.com/watch?v=l6ZEh6oYLRg

The remaining problems are:
# Tune parameters so stationary blob get severed.
# When an object leaves the scene, its tracks are left behind.

# Point Matching with Feature Grouping, v 0.2 #
The demo application is still the same executable name but the functionality has been improved. Now you can run

> ./FeatureBasedTracking --help

to get all the possible options.

Here is what a run of the application with debug gui will give:

> ./FeatureBasedTracking --debug\_gui --min\_frames\_tracked 5 --maximum\_distance\_activated 700 --segmentation\_threshold 200 /home/dchu/Dropbox/GSoC/Data/test2\_short.avi /home/dchu/Dropbox/GSoC/Data/test2.avi.homography.mat TrackAvi2Output.txt

![http://lh3.ggpht.com/_A6BW9X8vOFE/TA8McETX9sI/AAAAAAAAO0A/Tbo7AP8aejw/s800/FeatureGrouperBetter.png](http://lh3.ggpht.com/_A6BW9X8vOFE/TA8McETX9sI/AAAAAAAAO0A/Tbo7AP8aejw/s800/FeatureGrouperBetter.png)

In this screenshot, you can see several missing functionalities in the implementation

# Tracks are activated even if they haven't moved => trees and poles are activated where they should not
# Tracks that stay at the same place for a long time don't get removed.

# Point Matching with KLT Tracker, v 0.1 #

KLT Tracker works with optical flow. It detects points similar to corners. The matching is non-robust although the specific alternate implementation in OpenCV (which is wrapped) has improvements due to the inclusion of pyramidal decomposition.

This demo main file is FeatureBasedTracking.cxx . Under Visual Studio, this should be under the project FeatureBasedTracking. Simply run this executable with:

```
  Working directory: src_dir/Data
  Arguments: test1.avi test1.avi.homography.txt
```

You should see something like this:

![http://lh3.ggpht.com/_A6BW9X8vOFE/S_dcCVI-0zI/AAAAAAAAOzM/G71jxahKy0E/s400/Screen%20shot%202010-05-21%20at%2011.09.03%20PM.png](http://lh3.ggpht.com/_A6BW9X8vOFE/S_dcCVI-0zI/AAAAAAAAOzM/G71jxahKy0E/s400/Screen%20shot%202010-05-21%20at%2011.09.03%20PM.png)

Hitting Spacebar to advance.
Hitting Esc to quit the application