from imutils.video import VideoStream
from imutils.video import fps
import argparse
import imutils
import time
import cv2
import sys

# construct argument parser and parse arguments

argument_paser = argparse.ArgumentParser()

# --tracker specifies OpenCV tracker (csrt, kcf, boosting, mil, tld, medianflow, mosse)
argument_paser.add_argument("-t", "--tracker", type=str, default="kcf", help="OpenCV object tracker type")
args = vars(argument_paser.parse_args())

# Using OpenCV 4.6.0
OPENCV_OBJECT_TRACKER = {
    "csrt": cv2.TrackerCSRT_create(),
    "kcf": cv2.TrackerKCF_create(),
    "boosting": cv2.TrackerBoosting_create(),
    "mil": cv2.TrackerMIL_create(),
    "tld": cv2.TrackerTLD_create(),
    "medianflow": cv2.TrackerMedianFlow_create(),
    "goturn": cv2.TrackerGOTURN_create(),
    "mosse": cv2.TrackerMOSSE_create(),
}

tracker = OPENCV_OBJECT_TRACKER[args["tracker"]]()


# Read video
video = cv2.VideoCapture("resources/helicam.mp4")

# Exit if video is not opened.
if not video.isOpened(): 
    print("Failed to open video")
    sys.exit()
    
ok, frame = video.read()
if not ok:
    print("Cannot read video file")
    sys.exit()
    
bbox = cv2.selectROI(frame, False)