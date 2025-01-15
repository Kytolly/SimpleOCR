import json 
from setting.message import *
import setting as st

class Record():
    def __init__(self, rId, result:str, confidence: float):
        self.rId = rId
        self.result = result
        self.confidence = confidence
    
    def __dict__(self):
        return {
            "rId": self.rId,
            "result": self.result,
            "confidence": self.confidence
        }
    @staticmethod
    def from_dict(r):
        return Record(
            rId=r['rId'],
            result=r['result'],
            confidence=r['confidence']
        )
    
class Output():
    def __init__(self, oId, statusOK, msgCode, records):
        self.oId = oId
        self.statusOK = statusOK
        self.msgCode = msgCode
        self.records = records
        
    def fit(self, records):
        if records == None:
            return 
        self.records = []
        for i in range(len(records)): 
            now = Record(rId=i, result=records[i][1], confidence=records[i][2])
            self.records.append(now)
            
        if len(records) == 0:
            self.msgCode = ERROR_OUTPUT_EMPTY
        else:
            self.statusOK = True
            self.msgCode = SUCCESS
            
    def __dict__(self):
        return {
            'oId': self.oId,
            "statusOK": self.statusOK,
            'msgCode': self.msgCode,
            'records': [r.__dict__() for r in self.records]
        }
    
    def _json(self):
        return json.dumps(self.__dict__())
    
    def serialize(self):
        return self._json().encode(st.coding)
    
    @staticmethod
    def deserialize(data:bytes):
        sdata = data.decode(st.coding)
        dic = json.loads(sdata)
        return Output(
            oId=dic['oId'],
            statusOK=dic['statusOK'],
            msgCode=dic['msgCode'],
            records=[Record.from_dict(r) for r in dic['records']]
        )