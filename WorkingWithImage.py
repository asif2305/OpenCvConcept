# Reading an image

#Importing the OpenCv library

import cv2

# Reading an image using imread() function
image=cv2.imread('road.jpg')

#Extracting the height and width of an image
h, w=image.shape[:2]
# Displaying the height and width
print('Height = {}, Width = {}'.format(h,w))