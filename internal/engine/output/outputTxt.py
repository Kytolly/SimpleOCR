from output.output import *

class OutputTxt(Output):
    def __init__(self, output: Output, dirName, fileName):
        super().__init__(
            oId=output.oId, 
            statusOK=output.statusOK, 
            msgCode=output.msgCode, 
            records=output.records
        )
        self.dirName = dirName
        self.fileName = f'{fileName}.txt'
        self.outputPath = self.dirName + '/' + self.fileName

    def print(self):
        with open(self.outputPath, 'w', encoding='utf-8') as f:
            for record in self.records:
                print(record.result, file=f)
        f.close()