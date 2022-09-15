// Learning project, mostly from the tutorials that come with OpenCV.
// End goal is to detect F1 cars and the lines they are taking around a corner
// and to compare that line to see how much they are off from the ideal racing line
// I know the code looks horribly right now, I will refactor it soon
// And most of the comments are probably unneccesary for most folks, but
// they are for me to understand the code better in the future

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

        cv::imshow("imageThreshhold", imageThreshhold);

        cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
        cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
        cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
        cv::Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));

        cv::dilate(imageThreshhold, imageThreshhold, structuringElement5x5);
        cv::dilate(imageThreshhold, imageThreshhold, structuringElement5x5);
        cv::erode(imageThreshhold, imageThreshhold, structuringElement5x5);

        cv::Mat imageThreshCopy = imageThreshhold.clone();

        std::vector<std::vector<cv::Point>> contours;

        cv::findContours(imageThreshCopy, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        cv::Mat imgContours(imageThreshhold.size(), CV_8UC3, SCALAR_BLACK);

        cv::drawContours(imgContours, contours, -1, SCALAR_WHITE, -1);

        cv::imshow("imgContours", imgContours);

        std::vector<std::vector<cv::Point>> convexHulls(contours.size());

        for (unsigned int i = 0; i < contours.size(); i++) {

            cv::convexHull(contours[i], convexHulls[i])
        }

        for (auto &convexHull : convexHulls) {
            Blob possibleBlob(convexHull);

            // Refactor this later according to Clean Code

            if (possibleBlob.isRealBlob) {
                blobs.push_back(possibleBlob);
            }

            cv::Mat imgConvexHulls(imgTresh.size(), CV_8UC3, SCALAR_BLACK);

            convexHulls.clear();

            for (auto &blob : blobs) {
                convexHulls.push_back(blob.contour);
            }

            cv::drawContours(imgConvexHulls, convexHulls, -1, SCALAR_WHITE, -1);

            cv::imshow("imgConvexHulls", imgConvexHulls);

            imageFrame2Copy = imageFrame2.clone();

            for (auto &blob : blobs) {

                cv::rectangle(imageFrame2Copy, blob.boundingRectangle, SCALAR_RED, 2);
                cv::circle(imageFrame2Copy, blob.centerPosition, 3, SCALAR_GREEN, -1);
            }
        }
    }
};