from imutils.video import VideoStream
from imutils.video import fps
import argparse
import imutils
import time
import cv2
import sys

from matplotlib.pyplot import box

# construct argument parser and parse arguments

# argument_paser = argparse.ArgumentParser()

# --tracker specifies OpenCV tracker (csrt, kcf, boosting, mil, tld, medianflow, mosse)
# argument_paser.add_argument("-t", "--tracker", type=str, default="kcf", help="OpenCV object tracker type")
# args = vars(argument_paser.parse_args())

# Using OpenCV 4.6.0
OPENCV_OBJECT_TRACKER = {
    "csrt": cv2.TrackerCSRT_create(),
    "kcf": cv2.TrackerKCF_create(),
    "boosting": cv2.legacy.TrackerBoosting_create(),
    "mil": cv2.TrackerMIL_create(),
    "tld": cv2.legacy.TrackerTLD_create(),
    "medianflow": cv2.legacy.TrackerMedianFlow_create(),
    #"goturn": cv2.TrackerGOTURN_create(),
    "mosse": cv2.legacy.TrackerMOSSE_create(),
}

tracker = cv2.TrackerKCF_create()


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
    
bounding_box = cv2.selectROI(frame, False)

# Initialize the tracker with the first frame and bounding box
ok = tracker.init(frame, bounding_box)

while True:
    ok, frame = video.read()
    if not ok:
        break
    # Start the timer
    timer = cv2.getTickCount()
    
    # Update tracker
    ok, bounding_box = tracker.update(frame)
    
    # FPS
    fps = cv2.getTickFrequency() / (cv2.getTickCount() - timer);

    # Draw bounding box
    if ok:
        # Tracking succes
        p1 = (int(bounding_box[0]), int(bounding_box[1]))
        p2 = (int(bounding_box[0] + bounding_box[2]), int(bounding_box[1] + bounding_box[3]))
        cv2.rectangle(frame, p1, p2, (255,0,0), 2, 1)
    else :
        # Tracking Failure
        cv2.putText(frame, "Tracking failure", (100,80), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (50,170,50),2);
        
        # Display tracker on frame
        cv2.putText(frame, "kcf", (100,20), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (50,170,50),2);
        
        # Display FPS on frame
        cv2.putText(frame, "FPS: " + str(int(fps)), (100,50), cv2.FONT_HERSHEY_SIMPLEX, 0.75, (50,170,50),2);
        
        # Display result
        cv2.imshow("Tracking", frame)
        
        k = cv2.waitKey(1) & 0xff
        if k == 27 : break
        
        