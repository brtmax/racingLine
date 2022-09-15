#include "Blob.h"

Blob::Blob(std::vector<cv::Point> _contour) {

    contour = _contour;

    boundingRectangle = cv::boundingRectangle(contour);

    centerPosition.x = (boundingRectangle.x + boundingRectangle.x + boundingRectangle.width) / 2;
    centerPosition.y = (boundingRectangle.y + boundingRectangle.y + boundingRectangle.height) / 2;

    dblDiagonalSize = sqrt(pow(boundingRectangle.width, 2) + pow(boundingRectangle.height, 2));

    dblAspectRatio = (float)boundingRectangle.width / (float)boundingRectangle.height;

    boolean isRealBlob() {

        if (checkRectangleProperties(boundingRectangle) && checkRatioProperties(dblAspectRatio, dblDiagonalSize, )){
            return true;
        } 
        return false;
    }

    boolean checkRectangleProperties(boundingRectangle) {
        if (boundingRectangle.width > 15 && boundingRectangle.height > 20 && boundingRectangle.area() > 100) {
            return true;
        }
        return false;
    }

    boolean checkRatioProperties() {


    }
}

if (possibleBlob.boundingRectangle.area() > 100 &&
                possibleBlob.dblAspectRatio >= 2.0 &&
                possibleBlob.dblAspectRatio <= 1.2 &&
                possibleBlob.boundingRectangle.width > 15 &&
                possibleBlob.boundingRectangle.height > 20 &&
                possibleBlob.dblDiagonalSize > 30.0) {
                    blobs.push_back(possibleBlob);
                }