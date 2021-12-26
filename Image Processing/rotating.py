import cv2

image = cv2.imread("D:/Github Repo/GitHub\OpenCvConcept/water.png", 1)

(row, col) = image.shape[:2]

# getRotationMatrix2D creates a matrix needed for transformation.
M = cv2.getRotationMatrix2D((col/2, row/2),45 , 1)
res= cv2.warpAffine(image, M, (col,row))

cv2.imshow("Rotating ", res)
cv2.waitKey(0)
