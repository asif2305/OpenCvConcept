import cv2
class OpenCVMaskRcnn():

    """ OpenCVMaskRcnn takes four parameter for the initialization object"""
    def __init__(self, model,weights,labelFile):
        self.model = model
        self.weights= weights
        self.net= cv2.dnn.readNetFromTensorflow(self.weights, self.model)
        self.labelFile = labelFile

    """ feed the input towards the network """
    def feed_network(self,image):
        # detect object
        blob = cv2.dnn.blobFromImage(image)
        self.net.setInput(blob)
        boxes, masks = self.net.forward(["detection_out_final", "detection_masks"])
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
        img_height = image.shape[0]
        img_width = image.shape[1]
        for i in range(detectionCount):
            box = boxes[0, 0, i]
            class_id = box[1]
            # print(class_id)
            score = box[2]
            if score < 0.5:
                continue
            # Get the box Coordinates
            x = int(box[3] * img_width)
            y = int(box[4] * img_height)
            x2 = int(box[5] * img_width)
            y2 = int(box[6] * img_height)
            # find the Region of interest
            roi = image[y: y2, x: x2]

            label = "{} : {:.4f}".format(self.read_label()[int(class_id)] , score)
            cv2.putText(image, label, (x, y - 20), cv2.FONT_HERSHEY_COMPLEX, 0.5, (0, 0, 255), 1)
            roi_height, roi_width, _ = roi.shape
            cv2.rectangle(image, (x, y), (x2, y2), (255, 0, 0), 3)

        return image


if __name__ == "__main__":

    model =  "dnn/mask_rcnn_inception_v2_coco_2018_01_28.pbtxt"
    weights = "dnn/frozen_inference_graph_coco.pb"
    #model = "dnn/export/pipeline.pbtxt"
    #weights = "dnn/export/saved_model/saved_model.pb"
    labelFile ='label.txt'
    openCVMask = OpenCVMaskRcnn(model, weights,labelFile)
    # vedio image load
    cap = cv2.VideoCapture(0)
    # cap.set(cv2.CAP_PROP_FPS,50)
    while True:
        success, image = cap.read()
        boxes, masks = openCVMask.feed_network(image)
        # for box in boxes:
        img = openCVMask.detectionImage(image, boxes.shape[2], boxes)
        cv2.imshow("img", image)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cv2.waitKey(0)
    cap.release()
    cv2.destroyAllWindows()

