
import cv2
import numpy as np
from matplotlib import pyplot as plt

image = cv2.imread("D:/Github Repo/GitHub\OpenCvConcept/water.png",1)
image= cv2.cvtColor(image, cv2.COLOR_BGR2RGB)

blur = cv2.blur(image,(5,5))
"""
Gaussian Blurring:Gaussian blur is the result of blurring an image by a Gaussian function.
 It is a widely used effect in graphics software, typically to reduce image noise and reduce detail. 
 It is also used as a preprocessing stage before applying our machine learning or deep learning models.
"""
gblur= cv2.GaussianBlur(image, (5,5),0 )
"""
The Median Filter is a non-linear digital filtering technique, often used to remove noise 
from an image or signal. Median filtering is very widely used in digital image processing because, 
under certain conditions, it preserves edges while removing noise. 
It is one of the best algorithms to remove Salt and pepper noise.
"""
median = cv2.medianBlur(image, 5)

"""
A bilateral filter is a non-linear, edge-preserving, and noise-reducing smoothing filter for images. 
It replaces the intensity of each pixel with a weighted average of intensity values from nearby pixels.
 This weight can be based on a Gaussian distribution. Thus, sharp edges are preserved while discarding 
 the weak ones.
"""
# Apply bilateral filter with d = 9,
# sigmaColor = sigmaSpace = 75.
bilateralFilter = cv2.bilateralFilter(image, 9, 75, 75)

titles = ['image', 'blur', 'GaussianBlur', 'median', 'bilateralFilter']
images = [image,  blur, gblur, median, bilateralFilter]

for i in range(5):
    plt.subplot(2, 3, i+1), plt.imshow(images[i], 'gray')
    plt.title(titles[i])
    plt.xticks([]),plt.yticks([])

plt.show()

