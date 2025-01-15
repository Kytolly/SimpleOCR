from input.input import *

if __name__ == "__main__":
    path = 'D:/Proj/MultiMedia/OcrRecognition/imagel.png'
    statusOK = True
    input = Input(path=path, statusOK=statusOK)
    print(input._json())
    print(input.serialize())