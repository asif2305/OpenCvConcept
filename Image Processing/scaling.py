import cv2
# Scaling operation increases/reduces size of an image.
# Get number of pixel horizontally and vertically.
image = cv2.imread("D:/Github Repo/GitHub\OpenCvConcept/water.png", 1)
(height, width) = image.shape[:2]
"""
specify the size of image along with interpolation methods
cv2.INTRA_AREA is used for shrinking, whereas cv2.INTER_CUBIC is used for zooming
"""
res= cv2.resize(image, (int(width/2), int(height /2)), interpolation= cv2.INTER_CUBIC)
cv2.imshow("Scaling", res)
cv2.waitKey(0)
