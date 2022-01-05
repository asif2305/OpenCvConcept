import numpy as np
import cv2


class YoloDarkNet():
    """ YoloDarkNet takes four parameter for the initialization object"""

    def __init__(self, model, weights, labelFile):
        self.model = model
        self.weights = weights
        self.net = cv2.dnn.readNetFromDarknet(self.model, self.weights)
        self.labelFile = labelFile
        self.wht= 320
        self.confThreshold= 0.5
        self.nmsThreshold = 0.3
        self.net.setPreferableBackend(cv2.dnn.DNN_BACKEND_DEFAULT)
        self.net.setPreferableTarget(cv2.dnn.DNN_TARGET_CPU)

    # function to get the output layer names
    # in the architecture
    def get_output_layers(self,net):
        layer_names = net.getLayerNames()

        output_layers = [layer_names[i - 1] for i in net.getUnconnectedOutLayers()]
        print(output_layers)
        return output_layers

    """ feed the input towards the network """
    def feed_network(self,image):
        # image = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)
        # detect object
        # create input blob
        blob = cv2.dnn.blobFromImage(image, 0.00392, (416, 416), (0, 0, 0), True, crop=False)

        # image dimension instead of blob
        """
        image= cv2.resize(image,(300,300))
        image = np.expand_dims(image, axis=0)
        image = np.rollaxis(image,3,1)
        """

        self.net.setInput(blob)
        boxes = self.net.forward(self.get_output_layers(self.net))
        print(boxes)
        return boxes

    """ get the class label name """
    def labelName(self):
        # label name
        lines = []
        with open(self.labelFile) as f:
            for line in f:
                lines.append(line.rstrip())
        return lines

    """ bounding box detection and ROI"""
    def detectionImage(self,image, boxes):
        classNames = self.labelName()
        img_height = image.shape[0]  # col
        img_width = image.shape[1]  # row

        bboxes = []
        box_confidences = []
        class_id = []
        for output in boxes:
            for det in output:
                scores = det[5:]
                classID = np.argmax(scores)  # return the max value index
                confidence = scores[classID]
                if confidence > self.confThreshold:
                    w, h = int(det[2] * img_width), int(det[3] * img_height)
                    # center x = x + 1/2 * img_width
                    # center y = y + 1/2 * img_height
                    x, y = int((det[0] * img_width) - w / 2), int((det[1] * img_height) - h / 2)

                    bboxes.append([x, y, w, h])
                    class_id.append(classID)
                    box_confidences.append(float(confidence))

        indices = cv2.dnn.NMSBoxes(bboxes, box_confidences, self.confThreshold, self.nmsThreshold)

        if len(indices) > 0:
            for i in indices:
                # i= i[0]
                box = bboxes[i]
                (x, y) = bboxes[i][0], bboxes[i][1]
                (w, h) = bboxes[i][2], bboxes[i][3]
                cv2.rectangle(image, (x, y), (x + w, y + h), (255, 0, 255), 2)
                cv2.putText(image, f'{classNames[class_id[i]].upper()} {int(box_confidences[i] * 100)}%',
                            (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 0, 255), 2)

        return image

# Loading model

if __name__ == "__main__":

    model = 'dnn\yolov4.cfg'
    weights = 'dnn\yolov4.weights'
    labelFile = 'label.txt'
    yoloDarkNet = YoloDarkNet(model, weights, labelFile)

    # vedio image load
    cap = cv2.VideoCapture(0)

    cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1920)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 1360)
    # cap.set(cv2.CAP_PROP_FPS,50)
    while (cap.isOpened()):
        success, image = cap.read()
        boxes= yoloDarkNet.feed_network(image)
        # for box in boxes:
        img = yoloDarkNet.detectionImage(image, boxes)

        cv2.imshow("img", img)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cv2.waitKey(0)
    cap.release()
    cv2.destroyAllWindows()


