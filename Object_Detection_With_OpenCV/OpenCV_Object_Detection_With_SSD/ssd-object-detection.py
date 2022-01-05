import cv2

class OpenCvSSD():
    """ OpenCVMaskRcnn takes four parameter for the initialization object"""
    def __init__(self,model,weights,labelFile):
        self.model = model
        self.weights = weights
        self.net = cv2.dnn.readNetFromCaffe(self.model, self.weights)
        self.labelFile = labelFile
    # Loading model

    """ feed the input towards the network """
    def MobileNetSSD_network(self,image):
        # detect object
        blob = cv2.dnn.blobFromImage(image, 0.007843, (300, 300), (104, 117, 123))
        """
        image= cv2.resize(image,(300,300))
        image = np.expand_dims(image, axis=0)
        image = np.rollaxis(image,3,1)
        """
        self.net.setInput(blob)
        boxes = self.net.forward()
        masks = None
        return boxes, masks

    """ get the class label name """
    def read_label(self):
        # label name
        lines = []
        with open(self.labelFile) as f:
            for line in f:
                lines.append(line.rstrip())
        return lines

    """ bounding box detection and ROI"""
    def detectionImage(self,image, detectionCount, boxes):
        img_height = image.shape[0]  # col
        img_width = image.shape[1]  # row
        for i in range(detectionCount):

            box = boxes[0, 0, i]
            class_id = box[1]
            # print(class_id)
            score = box[2]

            if score < 0.7:
                continue

            # Get box Coordinates
            x = int(box[3] * img_width)
            y = int(box[4] * img_height)
            x2 = int(box[5] * img_width)
            y2 = int(box[6] * img_height)

            roi = image[y: y2, x: x2]
            lines = self.read_label()
            cv2.putText(image, str(lines[int(class_id)]) + ' ' + str(score), (x, y - 20), cv2.FONT_HERSHEY_COMPLEX, 0.5,
                        (0, 0, 255), 1)
            roi_height, roi_width, _ = roi.shape
            cv2.rectangle(image, (x, y), (x2, y2), (255, 0, 0), 3)

        return image


if __name__ == "__main__":

    model ="SSD\MobileNetSSD_deploy.prototxt"
    weights = "SSD\MobileNetSSD_deploy.caffemodel"
    labelFile = 'label.txt'
    openCVSSD =  OpenCvSSD(model, weights,labelFile)
    # vedio image load

    cap = cv2.VideoCapture(0)
    cap.set(cv2.CAP_PROP_FRAME_WIDTH,1920)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1360)
    # cap.set(cv2.CAP_PROP_FPS,50)
    while (cap.isOpened()):
        success, image = cap.read()
        boxes, masks = openCVSSD.MobileNetSSD_network(image)
         # for box in boxes:
        detection_count = boxes.shape[2]
        img =  openCVSSD.detectionImage(image, detection_count, boxes)
        cv2.imshow("img", img)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cv2.waitKey(0)
    cap.release()
    cv2.destroyAllWindows()





