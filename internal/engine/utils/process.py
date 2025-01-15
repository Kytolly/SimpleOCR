import cv2
import setting as st
import numpy as np

def getRatio(image):
    # 获得缩放比例
    ratio = image.shape[0] / st.stdHeight
    return ratio

def resize(image, widge=0, height=0, inter=cv2.INTER_AREA):
    # 将输入的图像按照高度为height，或者宽度为widge进行缩放
    dim = None
    (h, w) = image.shape[:2]
    if widge == 0 and height == 0:
        return image
    if widge == 0:
        r = height/float(h)
        dim = (int(w*r), height)
    else:
        r = widge/float(w)
        dim = (widge, int(h*r))
    resized = cv2.resize(image, dim, interpolation=inter)
    return resized

def findContours(image):
    # 轮廓检测
    cnts = cv2.findContours(image.copy(), cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)[0]
    cnts = sorted(cnts, key = cv2.contourArea, reverse=True)[:10]
    screenCnt = []
    for c in cnts:
        # 计算近似轮廓
        peri = cv2.arcLength(c, True)
        approx = cv2.approxPolyDP(c, 0.02 * peri, True)
        # 如果近似轮廓有4个顶点，那么它就是一个可能的字符
        if len(approx) == 4:
            screenCnt.append(approx)
            break
    return screenCnt

def order_points(pts):
    # 坐标对应：左上，右上，右下，左下
    rect = np.zeros((4, 2), dtype = "float32")
    s = pts.sum(axis = 1)
    rect[0] = pts[np.argmin(s)]
    rect[2] = pts[np.argmax(s)]
    diff = np.diff(pts, axis = 1)
    rect[1] = pts[np.argmin(diff)]
    rect[3] = pts[np.argmax(diff)]
    return rect

def four_point_transform(image, pts):
    # 透视变换
    rect = order_points(pts)
    (tl, tr, br, bl) = rect
    widthA = np.sqrt(((br[0] - bl[0]) ** 2) + ((br[1] - bl[1]) ** 2))
    widthB = np.sqrt(((tr[0] - tl[0]) ** 2) + ((tr[1] - tl[1]) ** 2))
    maxWidth = max(int(widthA), int(widthB))
    heightA = np.sqrt(((tr[0] - br[0]) ** 2) + ((tr[1] - br[1]) ** 2))
    heightB = np.sqrt(((tl[0] - bl[0]) ** 2) + ((tl[1] - bl[1]) ** 2))
    maxHeight = max(int(heightA), int(heightB))
    dst = np.array([
        [0, 0],
        [maxWidth - 1, 0],
        [maxWidth - 1, maxHeight - 1],
        [0, maxHeight - 1]], dtype = "float32")

    M = cv2.getPerspectiveTransform(rect, dst)
    warped = cv2.warpPerspective(image, M, (maxWidth, maxHeight))

    return warped 
