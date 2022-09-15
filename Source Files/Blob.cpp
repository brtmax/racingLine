#include "Blob.h"

Blob::Blob(std::vector<cv::Point> _contour) {

    contour = _contour;

    boundingRectangle = cv::boundingRect(contour);

    centerPosition.x = (boundingRectangle.x + boundingRectangle.x + boundingRectangle.width) / 2;
    centerPosition.y = (boundingRectangle.y + boundingRectangle.y + boundingRectangle.height) / 2;

    dblDiagonalSize = sqrt(pow(boundingRectangle.width, 2) + pow(boundingRectangle.height, 2));

    dblAspectRatio = (float)boundingRectangle.width / (float)boundingRectangle.height;
}

