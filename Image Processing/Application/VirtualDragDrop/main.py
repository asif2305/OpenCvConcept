import cv2
from cvzone.HandTrackingModule import HandDetector
import cvzone
import numpy as np
cap = cv2.VideoCapture(0)
"""
0. CV_CAP_PROP_POS_MSEC Current position of the video file in milliseconds.
1. CV_CAP_PROP_POS_FRAMES 0-based index of the frame to be decoded/captured next.
2. CV_CAP_PROP_POS_AVI_RATIO Relative position of the video file
3. CV_CAP_PROP_FRAME_WIDTH Width of the frames in the video stream.
4. CV_CAP_PROP_FRAME_HEIGHT Height of the frames in the video stream.
5. CV_CAP_PROP_FPS Frame rate.
6. CV_CAP_PROP_FOURCC 4-character code of codec.
7. CV_CAP_PROP_FRAME_COUNT Number of frames in the video file.
8. CV_CAP_PROP_FORMAT Format of the Mat objects returned by retrieve() .
9. CV_CAP_PROP_MODE Backend-specific value indicating the current capture mode.
10. CV_CAP_PROP_BRIGHTNESS Brightness of the image (only for cameras).
11. CV_CAP_PROP_CONTRAST Contrast of the image (only for cameras).
12. CV_CAP_PROP_SATURATION Saturation of the image (only for cameras).
13. CV_CAP_PROP_HUE Hue of the image (only for cameras).
14. CV_CAP_PROP_GAIN Gain of the image (only for cameras).
15. CV_CAP_PROP_EXPOSURE Exposure (only for cameras).
16. CV_CAP_PROP_CONVERT_RGB Boolean flags indicating whether images should be converted to RGB.
17. CV_CAP_PROP_WHITE_BALANCE Currently unsupported
18. CV_CAP_PROP_RECTIFICATION Rectification flag for stereo cameras (note: only supported by DC1394 v 2.x backend currently)
"""

cap.set(3, 1280)  # width
cap.set(4, 720)  # height
detector = HandDetector(detectionCon=0.8)  # default 0.5
colorRect = (255, 0, 255)

cx, cy, w, h = 100, 100, 200, 200  # center point and width and height+



class DragRect():
    def __init__(self, posCenter, size=[200,200]):
        self.posCenter= posCenter
        self.size= size

    def update(self,cursor):
        cx, cy = self.posCenter
        w, h = self.size
        # if the finger index top is in the rectangle region
        if cx - w // 2 < cursor[0] < cx + w // 2 and cy - h // 2 < cursor[
            1] < cy + h // 2:  # first check is x and second check is y
            self.posCenter = cursor

recList =[]
for x in range(5):
    recList.append(DragRect([x* 250 +150 , 150]))

while True:
    success, img = cap.read()
    img = cv2.flip(img, 1)  # 1- horizontal 0- vertical flip
    img = detector.findHands(img)
    lmList, _ = detector.findPosition(img)

    if lmList:
        # find the distance of the finger
        l,_,_ = detector.findDistance(8,12 ,img, draw= False)
        print(l)
        if l<50:
            cursor = lmList[8]  # index finger tip landmark
            print(cursor)
            # call the update here
            for rect in recList:
                rect.update(cursor)



    # draw solid
    """
       for rect in recList:
        cx, cy = rect.posCenter
        w, h = rect.size

        cv2.rectangle(img, (cx - w // 2, cy - h // 2), (cx + w // 2, cy + h // 2), colorRect, cv2.FILLED)
        cvzone.cornerRect(img, (cx - w // 2, cy - h // 2, w, h),20, rt = 0)

    """
    # draw transperency

    imgNew = np.zeros_like(img, np.uint8)
    for rect in recList:
        cx, cy = rect.posCenter
        w, h = rect.size

        cv2.rectangle(imgNew, (cx - w // 2, cy - h // 2), (cx + w // 2, cy + h // 2), colorRect, cv2.FILLED)
        cvzone.cornerRect(imgNew, (cx - w // 2, cy - h // 2, w, h), 20, rt=0)
    out = img.copy()
    alpha = 0.5
    mask = imgNew.astype(bool)
    print(mask.shape)
    out[mask] = cv2.addWeighted(img, alpha, imgNew, 1-alpha,0)[mask]

    cv2.imshow("Image", out)
    cv2.waitKey(1)
