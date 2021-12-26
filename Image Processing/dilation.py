import cv2
import numpy as np
"""
https://www.youtube.com/watch?v=d1we_yqUASg&ab_channel=TheVertex
Fills in holes
Smoothes object boundaries
Adds an extra outer ring of pixel onto object boundary, ie, object becomes slightly larger
"""

img = cv2.imread("D:/Github Repo/GitHub\OpenCvConcept/water.png", 1)
# Taking a matrix of size 5 as the kernel
kernel = np.ones((5, 5), np.uint8)

# The first parameter is the original image,
# kernel is the matrix with which image is
# convolved and third parameter is the number
# of iterations, which will determine how much
# you want to erode/dilate a given image.
img_erosion = cv2.erode(img, kernel, iterations=1)
img_dilation = cv2.dilate(img, kernel, iterations=1)

cv2.imshow('Input', img)
cv2.imshow('Erosion', img_erosion)
cv2.imshow('Dilation', img_dilation)

cv2.waitKey(0)