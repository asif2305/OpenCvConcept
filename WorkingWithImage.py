# Reading an image
# link:https://www.geeksforgeeks.org/introduction-to-opencv/
#Importing the OpenCv library

import cv2

# Reading an image using imread() function
image=cv2.imread('road.jpg')

#Extracting the height and width of an image
h, w=image.shape[:2]
# Displaying the height and width
print('Height = {}, Width = {}'.format(h,w))
print(image.shape)
#Draw a rectangle line

# Start coordinate point
# represent the top left corner of rectangle
start_point=(200,200)
#Ending point
#Represent the bottom right corner of rectangle
end_point=(1300,1000)
# Blue color in BGR
color=(255,0,0)
# Line thickness of 2 px
thickness=5
# Using cv2.rectangle() method
# Draw a rectangle line blue line borders of thickness of 2 px
image=cv2.rectangle(image,start_point,end_point,color,thickness)
cv2.imshow('Road',image)
cv2.waitKey(0)



