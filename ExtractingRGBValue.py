import WorkingWithImage as WithImage

# Extracting RGB values
# Here we have randomly chosen a pixel
# by passing in 100, 100 for height and width

(B, G, R) = WithImage.image[100, 100]
# Displaying the pixel values
print("R ={} ,G = {} ,B ={}".format(R, G, B))

# We can also pass the channel to extract
# the value for a specific channel
B = WithImage.image[100, 100, 1] # third parameter 0 for R,1 for G and 2 for B
print("B = {}".format(B))
