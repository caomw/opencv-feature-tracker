/*///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                        Intel License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2000, Intel Corporation, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of Intel Corporation may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Intel Corporation or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//*/
#ifndef __MISC_H_
#define __MISC_H_
#include <vector>
#include <cv.h>
#include <iostream>
using std::cout;
using std::endl;
using std::vector;

/** \brief Create an array of array from a vector of vector

Make sure you free the data with delete_arr_arr.
Notice that T2 needs to be convertible to T

\see delete_arr_arr
*/
template <class T, class T2>
T** vec_vec_to_arr_arr(vector<vector <T2> > input_vector){
    T** result = new T*[input_vector.size()];

    for (int i = 0; i < input_vector.size() ; i++)
    {
        result[i] = new T[input_vector[i].size()];
        for (int j = 0; j < input_vector[i].size() ; j++)
        {
            // Let's do the copying
            result[i][j] = input_vector[i][j];
        }
    }
    return result;
}

/** \brief Deallocate the memory of an array of array
*/
template <class T>
void delete_arr_arr(T** arr, int size){
    for (int i=0; i<size; i++)
        delete [] arr[i];

    delete [] arr;
}

/** \brief Convert one vector of T to another vector T2

  There needs to be T(T2 input) function
*/
template<class T, class T2>
void vector_one_to_another(const vector<T > in, vector<T2> & out){
    out.clear();
    out.resize(in.size());

    for (int i=0; i<in.size(); i++)
        out[i] = in[i];
}

template<>
void vector_one_to_another<cv::Point2f,cv::KeyPoint>(const vector<cv::Point2f> in, vector<cv::KeyPoint> & out);
template<>
void vector_one_to_another<cv::KeyPoint,cv::Point2f>(const vector<cv::KeyPoint> in, vector<cv::Point2f> & out);

/** \brief Convert two corresponding vectors into a map
*/
template<class T, class T2>
std::map<T, T2> vec_vec_to_map(const vector<T> & keys, const vector<T2> & values){
    std::map<T, T2> output;

    int num_elements = keys.size();

    for (int i=0; i<num_elements; i++){
        output[keys[i]] = values[i];
    }

    return output;
}

cv::Mat loadtxt(std::string filename);
bool WriteTXT(const std::string& filename, const cv::Mat& mat);
void LoadGalleryPCAs(std::vector<cv::PCA> * gallery_PCAs, const char * pca_folder, int num_gallery_subjects);
cv::Mat FindInterestPoints(const cv::Mat & gray_im, const char * query_point_filename, int max_num_corners = 10);

/** \brief Print the content of the matrix

  \tparam The type of matrix elements
*/
template<typename T> void print_matrix(const cv::Mat & mat){
    for (int i=0; i<mat.rows; i++){
        const T* mat_ptr = mat.ptr<T>(i);
        std::cout << ">   ";
        for (int j=0; j<mat.cols; j++){
            std::cout << mat_ptr[j] << " ";
        }

        std::cout << std::endl;
    }
}

template<typename T> void print(const std::vector<T> & vec){
    for (int i=0; i<vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

/** Indexing into the container given the indices

  e.g. a = [4,1,2,5,3]
  new_indices = [2,3,4,1,0]

  This method does similar to a[new_indices]. That is it returns:
    [2,5,3,1,4]
*/
template<typename VT>
VT indexing(VT input, const vector<int> & indices){
    VT output(input.size());

    for (int i=0; i<indices.size(); i++){
        output[i] = input[indices[i]];
    }

    return output;
}

// Providing printing support for Vec2f
std::ostream& operator<< (std::ostream& out, const cv::Vec2f & vec );

// Conversion between world and image coordinate
// NOTE: You can pass just use one and manually invert the homography_matrix
void convert_to_world_coordinate(const vector<cv::Point2f> & points_in_image_coordinate,
                                 const cv::Mat & homography_matrix,
                                 vector<cv::Point2f> * points_in_world_coordinate);
void convert_to_image_coordinate(const cv::Point2f & point_in_world_coordinate, const cv::Mat & homography_matrix, cv::Point2f * point_in_image_coordinate);
void convert_to_image_coordinate(const vector<cv::Point2f> & points_in_world_coordinate,
                                 const cv::Mat & homography_matrix,
                                 vector<cv::Point2f> * points_in_image_coordinate);
#endif

