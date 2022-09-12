#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>

#include<iostream>

#include "Blob.h"

// I know the code looks horribly right now, I will refactor it soon

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

    if (capturedVideo.get(CV_CAP_PROP_FRAME_COUNT) < 2) {
        std::cout << "\nerror: video file must have at least two frams";
        return 0;
    }

    capturedVideo.read(imageFrame1);
    capturedVideo.read(imageFrame2);

    char keyPressed = 0;

    while(capturedVideo.isOpened() && keyPressed != 27) {

        std::vector<Blob> blobs;

        cv::Mat imageFrame1Copy = imageFrame1.clone();
        cv::Mat imageFrame2Copy = imageFrame2.clone();

        cv::Mat imageDifference;
        cv::Mat imageThreshhold;

        cv::cvtColor(imageFrame1Copy, imageFrame1Copy, CV_BGR2GRAY);
        cv::cvtColor(imageFrame2Copy, imageFrame2Copy, CV_BGR2GRAY);

        cv::GaussianBlur(imageFrame1Copy, imageFrame1Copy, cv::Size(5, 5), 0);
        cv::GaussianBlur(imageFrame2Copy, imageFrame2Copy, cv::Size(5, 5), 0);

        cv::absdiff(imageFrame1Copy, imageFrame2Copy, imageDifference);

        cv::threshold(imageDifference, imageThreshhold, 30, 255.0, CV_THRESH_BINARY);


    }

}