import cv2
import matplotlib.pyplot as plt
import numpy as np

img = cv2.imread('road.jpg');
img = cv2.resize(img, (500, 500))
hsv_color = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

lower_range = np.array([10, 10, 160])
upper_range = np.array([100, 50, 200])

mask = cv2.inRange(hsv_color, lower_range, upper_range)
result = cv2.bitwise_and(img, img, mask=mask)
result = cv2.cvtColor(result, cv2.COLOR_HSV2BGR)
# res = np.copy(result)
# print(res.shape)
# res2 = np.zeros(res.shape[0:2], dtype='uint8')
# print(res2.dtype)
# print(result.dtype)
# res2 = np.hstack(res2)
# print(res2.shape)
# res3 = cv2.bitwise_or(result, result, mask=res2)
# cv2.imshow('mask', hsv_color)
# cv2.imshow('image', result)
plt.imshow(result)
# plt.imshow(img)
plt.show()
cv2.waitKey(0)
