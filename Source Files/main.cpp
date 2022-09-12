#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

#include "Blob.h"

const cv::Scalar SCALAR_BLACK = cv::Scalar(0.0, 0.0, 0.0);
const cv::Scalar SCALAR_WHITE = cv::Scalar(255.0, 255.0, 255.0);
const cv::Scalar SCALAR_BLUE = cv::Scalar(255.0, 0.0, 0.0);
const cv::Scalar SCALAR_GREEN = cv::Scalar(0.0, 200.0, 0.0);
const cv::Scalar SCALAR_RED = cv::Scalar)0.0, 0.0, 255.0);

int main(void) {

    cv:VideoCapture capturedVideo;
    cv::Mat imageFrame1
    cv::Mat imageFrame2

    capturedVideo.open(""); // Enter video file 

    if (!capVideo.isOpened()) {

        std::cout << "\nError reading video file" << std::endl << std::endl;
        return 0;
    }

}