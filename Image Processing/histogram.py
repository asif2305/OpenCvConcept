import numpy as np
import cv2 as cv
from matplotlib import  pyplot as plt

#img= np.zeros((200,200), np.uint8) # height and width
#(row,col) = img[0: 2]
#cv.rectangle(img,(0,100),(200,200),(255),-1)
#cv.rectangle(img,(0,50),(100,100),(127),-1)
img= cv.imread("D:/Github Repo/GitHub/OpenCvConcept/lena.jpg",0) # grayscale mode =0
#sb,g,r = cv.split(img)
# calculate histogram
"""
Image masking is a process of graphics software like
 Photoshop to hide some portions of an image and to reveal some portions.
"""
"""
calcHist : ist parameter :img
        2nd parameter : image mode
        3rd parameter : bin -> max value
        4th parameter: range 
"""
hist = cv.calcHist([img],[0] , None, [256],[0,256] )
plt.plot(hist)
#cv.imshow("img", img)
#cv.imshow("b", b)
#cv.imshow("g", g)
#cv.imshow("r", r)
# ravel us used to order the array in the single line
#plt.hist(b.ravel(), 256, [0,256])
#plt.hist(g.ravel(), 256, [0,256])
#plt.hist(r.ravel(), 256, [0,256])
plt.show()


cv.waitKey(0)
cv.destroyAllWindows()