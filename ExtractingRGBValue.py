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
#image = WithImage.cv2.resize(WithImage.image, (1200, 1450))
#print(image)
region = WithImage.image[864:1060, 1134:1266]
print(region)
# set the croping image

WithImage.image[500:696, 600:732] = region
WithImage.cv2.imshow('POI', WithImage.image)
WithImage.cv2.waitKey(0)
