#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>

#include "misc.h"
#include "opencv_io_extra.h"
#include "daisy_feature.h"

using std::string;
using std::vector;
using std::ofstream;
using namespace cv;

/** \brief Given a matrix, output into outstream into space-separated format for MATLAB/Python
    \param[in] descriptors descriptor matrix where each row is one instance
    \param[in] ofs output file stream

*/
void MatRowToTXTRow(const Mat & descriptors, ofstream * ofs){
    for (int i=0; i<descriptors.rows; i++){
        const float * ptr = descriptors.ptr<float>(i);
        for (int j=0; j<descriptors.cols; j++){
            *ofs << *ptr << " ";
            ptr++;
        }

        *ofs << std::endl;
    }
}

/** \file ExtractDAISYToTXT.cxx Get the DAISY descriptors into a text file for use in other programs

  The output format is ASCII of a Nx200 matrix where N = image.width * image.height
*/
int main(int argc, char ** argv){
    if (argc<4){
        printf("Usage: %s [options] image.png query_points.txt output_file.txt \n",argv[0]);
        
        std::cout << "You gave:\n";
        for (int i=0; i<argc; i++){
            std::cout << argv[i] << std::endl;
        }
        exit(-1);
    }

    const string image_filename(argv[1]);
    const string query_points_filename(argv[2]);

    ofstream ofs(argv[3]);

    if (!ofs.is_open()){
        std::cerr << "Cannot open file " << argv[4] << std::endl;
        exit(-1);
    }

    Mat gray_im = imread(image_filename, 0);
    Mat query_points = loadtxt(query_points_filename);
    Mat descriptors;

    DaisyDescriptorExtractor daisy_extractor;
    daisy_extractor.compute(gray_im, query_points, descriptors);

    MatRowToTXTRow(descriptors, &ofs);

    // Done
    ofs.close();
    std::cout << "Done extracting DAISY" << std::endl;
    return 0;
}