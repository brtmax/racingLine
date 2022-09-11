#ifndef MY_BLOB
#define MY_BLOB

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/impgproc/imgproc.hpp>

class Blob {

    //member variables
    public:
    std::vector<cv::Point> contour;
    cv::Rect boundingRectangle;
    cv::Point centerPosition;

    double dblDiagonalSize;
    double dblAspectRatio;

    // function prototypes
    Blob(std::vector<cv::Point> _contour);
};

#endif