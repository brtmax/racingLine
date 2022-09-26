from imutils.video import VideoStream
from imutils.video import fps
import argparse
import imutils
import time
import cv2

# construct argument parser and parse arguments

argument_paser = argparse.ArgumentParser()

argument_paser.add_argument("-v", "--video", type=str, help="path to input video file")
argument_paser.add_argument("-t", "--tracker", type=str, default="kcf", help="OpenCV object tracker type")
args = vars(argument_paser.parse_args())

