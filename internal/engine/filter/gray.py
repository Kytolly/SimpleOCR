import cv2

def filterGray(image):
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    return gray