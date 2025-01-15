from output.output import *

class OutputJson(Output):
    def __init__(self, output, dirName, fileName):
        super().__init__(
            oId=output.oId, 
            statusOK=output.statusOK, 
            msgCode=output.msgCode, 
            records=output.records
        )
        self.dirName = dirName
        self.fileName = f'{fileName}.json'
        self.outputPath = self.dirName + '/' + self.fileName
        
    def print(self):
        with open(self.outputPath, 'w', encoding='utf-8') as f:
            f.write(self._json())