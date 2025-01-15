from utils.process import *
import setting as st
from filter.gray import *
from filter.edge import *

def filterTransform(edged, resized):
    # 透视变换的过滤器
    screenCnt = findContours(edged) 
    ratio = getRatio(resized)
    warped = four_point_transform(resized, screenCnt[0].reshape(4,2)*ratio)
    return warped

def process_normal(image):
    resized = resize(image, height=st.stdHeight)
    gray = filterGray(resized)
    return gray

def process_fourPoints(image):
    resized = resize(image, height=st.stdHeight)
    edged = filterEdgeDetection(resized)
    warped = filterTransform(edged, resized)
    gray = filterGray(warped)
    return gray