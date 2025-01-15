import time
import zmq
import setting as st 
from filter.gray import *
from filter.edge import *
from filter.transform import * 
from handler.source_easyocr import *
from input.input import *

class Server():
    def __init__(self):
        self.context = zmq.Context()
        self.socket = self.context.socket(zmq.REP)
        self.socket.bind(st.serverHost + st.tcpPort)
        
    def run(self):
        while True:
            input_data = self.socket.recv()
            input_obj = Input.deserialize(input_data)
            
            output_obj = Handler_easyocr().handle(input_obj)

            output_data = output_obj.serialize()
            self.socket.send(output_data)