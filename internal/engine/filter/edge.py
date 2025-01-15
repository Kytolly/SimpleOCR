import cv2

def filterEdgeDetection(image):
    # 边缘检测的过滤器
    
    # 转化为灰度图片
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    # 高斯滤波
    gray = cv2.GaussianBlur(gray, (5, 5), 0) 
    # Canny边缘检测
    edged = cv2.Canny(gray, 75, 200) 
    return edged 
