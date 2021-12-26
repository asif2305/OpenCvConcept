import cv2
import numpy

"""
Grayscaling is the process of converting an image from other color spaces e.g. RGB, CMYK, HSV, etc. 
to shades of gray. It varies between complete black and complete white.
"""
image = cv2.imread("D:/Github Repo/GitHub\OpenCvConcept/water.png", 1)
#cv2.imshow("original",image)

# Obtain the dimensions of the image array
# using the shape method
(row,col) = image.shape[0:2]

# Take the average of pixel values of the BGR Channels
# to convert the colored image to grayscale image

for i in range(row):
    for j in range(col): # Find the average of th BRG pixel values
        image[i,j] = sum(image[i,j]) * 0.33

cv2.imshow('Grayscale Image ', image)
cv2.waitKey(0)



print(row)
print(image)




# Window shown waits for any key pressing event
cv2.destroyAllWindows()