
import cv2
"""
Parameters:
src: It is the source image.
top: It is the border width in number of pixels in top direction.
bottom: It is the border width in number of pixels in bottom direction.
left: It is the border width in number of pixels in left direction.
right: It is the border width in number of pixels in right direction.
borderType: It depicts what kind of border to be added. It is defined by flags like cv2.BORDER_CONSTANT, cv2.BORDER_REFLECT, etc dest: It is the destination image
value: It is an optional parameter which depicts color of border if border type is cv2.BORDER_CONSTANT.

Return Value: It returns an image. 
"""
image = cv2.imread("D:/Github Repo/GitHub\OpenCvConcept/water.png",1)

# Window name in which image is displayed
window_name = 'Image'
# Using cv2.copyMakeBorder() method
image=cv2.copyMakeBorder(image,100,100,100,100, cv2.BORDER_CONSTANT ,None, value=0)

cv2.imshow(window_name, image)

cv2.waitKey(0)