from imutils.video import VideoStream
from imutils.video import fps
import argparse
import imutils
import time
import cv2
import sys

from matplotlib.pyplot import box

tracker_types = ['BOOSTING', 'MIL', 'KCF', 'TLD', 'MEDIANFLOW', 'GOTURN', 'MOSSE', 'CSRT']
tracker_type = tracker_types[2]


if tracker_type == 'BOOSTING':
    tracker = cv2.legacy.TrackerBoosting_create()
if tracker_type == 'MIL':
    tracker = cv2.TrackerMIL_create() 
if tracker_type == 'KCF':
    tracker = cv2.TrackerKCF_create() 
if tracker_type == 'TLD':
    tracker = cv2.legacy.TrackerTLD_create() 
if tracker_type == 'MEDIANFLOW':
    tracker = cv2.legacy.TrackerMedianFlow_create() 
# if tracker_type == 'GOTURN':
#    tracker = cv2.TrackerGOTURN_create()
if tracker_type == 'MOSSE':
    tracker = cv2.legacy.TrackerMOSSE_create()
if tracker_type == "CSRT":
    tracker = cv2.TrackerCSRT_create()
tracker = cv2.TrackerKCF_create()


# Read first frame
video = cv2.VideoCapture("resources/street.mp4")
ret, frame = video.read()

frame_height, frame_width = frame.shape[:2]
# Resize video for better view
frame = cv2.resize(frame, [frame_width//2, frame_height//2])
# Initialize video writer to save the results
output = cv2.VideoWriter(f'{tracker_type}.avi', cv2.VideoWriter_fourcc(*'XVID'), 60.0, (frame_width//2, frame_height//2), True)

if not ret:
    print('Cannot read the video')
    
bounding_box = cv2.selectROI(frame, False)

# Initialize the tracker with the first frame and bounding box
ret = tracker.init(frame, bounding_box)

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
        
        