#ifndef __BLOB_DETECTOR_
#define __BLOB_DETECTOR_

#include "common.hpp"
#include "Blob.h"
#include <vector>

namespace cv{
    /** forward declarations to save on compile time*/
    class Mat;


    class BlobDetector{
    public:
        BlobDetector();
        //BlobDetector(); // fully parameterized specification
        virtual std::vector<Blob> operator()(const Mat & input_foreground_mask_image, int close_holes = 1) const;
    private:
        DISALLOW_COPY_AND_ASSIGN(BlobDetector);
    };


    class BlobMatcher {
    public:
        /** \brief interface for matching a set of query blobs (i.e. blobs detected in the current frames) against
          a set of target blobs (i.e. blobs detected in the previous frames).

          Subclass this class in order to implement your own blob matcher. Try not to store any information in your blob
          matcher implementation. If you are interested in implementing a more sophisticated blob matching technique (e.g.
          Kalman-filter technique, trajectory-modelling technique), you should implement their logic inside of a subclass
          of BlobTracker or perhaps as a general tracker.
        */
        virtual void match(const Mat & query_image, const std::vector<Blob> & query_blobs,
                           const Mat & target_image, const std::vector<Blob> & target_blobs,
                           std::vector<int> & matches) = 0;
    };


    class BlobTrajectoryTracker {
    public:
        BlobTrajectoryTracker();
        void addBlobs(const std::vector<Blob> & new_blobs);
        void updateBlobs(const std::vector<Blob> & new_blobs, const std::vector<int> & ids_to_update);
        bool isTrajectoryConsistent(const Blob & query_blobs, int target_track_id) const;
        void nextTimeInstance();
    private:
        std::vector<std::vector<Blob> > blobs_over_time_;
        int current_time_;
    };


    class BlobWithTrajectoryMatcher : public BlobMatcher {
    public:
        BlobWithTrajectoryMatcher(BlobTrajectoryTracker * trajectory_tracker);
        virtual void match(const Mat & query_image, const std::vector<Blob> & query_blobs,
                           const Mat & target_image, const std::vector<Blob> & target_blobs,
                           std::vector<int> & matches);
    private:
        DISALLOW_COPY_AND_ASSIGN(BlobWithTrajectoryMatcher);

        bool isClose(const Blob & query, const Blob & target) const;

        BlobTrajectoryTracker * trajectory_tracker_;
    };
}

#endif
