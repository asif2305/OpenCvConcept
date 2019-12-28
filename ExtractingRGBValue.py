import numpy as np
import WorkingWithImage as WithImage

# Extracting RGB values
# Here we have randomly chosen a pixel
# by passing in 100, 100 for height and width

(B, G, R) = WithImage.image[100, 100]
# Displaying the pixel values
print("R ={} ,G = {} ,B ={}".format(R, G, B))

# We can also pass the channel to extract
# the value for a specific channel
B = WithImage.image[100, 100, 1]  # third parameter 0 for R,1 for G and 2 for B
print("B = {}".format(B))

# Region of interest
# at first I will find the region which I want to take
# image = WithImage.cv2.resize(WithImage.image, (1200, 1450))
##print(image)
region = WithImage.image[864:1060, 1134:1266]
# print(region)
# set the croping image

WithImage.image[500:696, 600:732] = region
# WithImage.cv2.imshow('POI', WithImage.image)


# Displaying text
# copying the original image
output = WithImage.image.copy()
# Adding the text using putText() function
text = WithImage.cv2.putText(output, 'OpenCv Demo Test by Ahmed', (500, 500), WithImage.cv2.FONT_HERSHEY_SIMPLEX, 4,
                             (255, 0, 0), 2)
# WithImage.cv2.imshow('POI', output)
# putText takes in 7 arguments –

# Image
# Text to be displayed
# Bottom-left corner co-ordinates, from where the text should start
# Font
# Font size
# Color (BGR format)
# Line width
# Draw geometric shapes on images using Python OpenCV
img = np.zeros([512, 512, 3], np.uint8)
img = WithImage.cv2.line(img, (0, 0), (255, 255), (147, 96, 44), 10)
img = WithImage.cv2.arrowedLine(img, (0, 255), (255, 255), (255, 0, 0), 10)
img = WithImage.cv2.rectangle(img, (384, 0), (50, 128), (0, 0, 255), 10)
img = WithImage.cv2.circle(img, (447, 63), 63, (0, 255, 0), -1)
font = WithImage.cv2.FONT_HERSHEY_SIMPLEX
img = WithImage.cv2.putText(img, 'Geometric Shape', (10, 400), font, 1, (0, 255, 255), 1, WithImage.cv2.LINE_AA)
WithImage.cv2.imshow('Geometric line', img)
WithImage.cv2.waitKey(0)
