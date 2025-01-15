import setting as st
import json
import cv2

class Input():
    def __init__(self, path=st.img_dir_local, statusOK=False):
        self.path = path
        self.statusOK = statusOK
        
    def __dict__(self):
        return {
            'path':self.path,
            "statusOK": self.statusOK,
        }
    
    def _json(self):
        return json.dumps(self.__dict__())
    
    def serialize(self):
        return self._json().encode(st.coding)
    
    @staticmethod
    def deserialize(data:bytes):
        sdata = data.decode(st.coding)
        dic = json.loads(sdata)
        return Input(
            path=dic['path'],
            statusOK=dic['statusOK'],  
        )
    
    def hash_name(self):
        return hash(self._json())
    
if __name__ == "__main__":
    path = 'D:/Proj/MultiMedia/0crRecognition/imagel.png'
    statusOK = True
    input = Input(path=path, statusOK=statusOK)
    print(input._json())
    print(input.serialize())