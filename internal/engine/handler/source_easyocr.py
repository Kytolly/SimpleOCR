import easyocr 
from input.input import *
from output.output import *
from output.outputJson import *
from utils.time_str import *
from pdf2image import convert_from_path
import requests
import tempfile
import shutil
from urllib.parse import urlparse
import os

class Handler_easyocr():
    def __init__(self):
        self.OCR_reader = easyocr.Reader(
            lang_list=['ch_sim', 'en'], 
            gpu=False, 
            download_enabled=True,
            model_storage_directory= 'model'
        )
    
    def handle(self, i: Input):
        out = Output(
                oId=now_time_string(i.hash_name()),
                statusOK=False,
                msgCode=ERROR_OUTPUT_EMPTY,
                records=[]
            )
        paths = self.getImagePaths(i)
        if len(paths) == 0:
            return out
        results = []
        for p in paths:
            result = self.OCR_reader.readtext(p, detail=1)
            for r in result:
                results.append(r)
        out.fit(results)
        return out
            
    def getImagePaths(self, i: Input):
        cache_path = st.img_dir_local
        input_path = i.path
        if not os.path.exists(cache_path):
            os.makedirs(cache_path)
        paths = []

        if urlparse(input_path).scheme in ('http', 'https'):
            input_path = self.download(input_path)

        if input_path.lower().endswith(('.png')):
            output_path = os.path.join(cache_path, f"{i.hash_name()}.png")
            shutil.copyfile(input_path, output_path)
            paths.append(output_path)
        elif input_path.lower().endswith('.pdf'):
            images = convert_from_path(input_path)
            for idx, image in enumerate(images):
                image_path = os.path.join(cache_path, f"{i.hash_name()}_page_{idx+1}.png")
                image.save(image_path, 'PNG')
                paths.append(image_path)
        else:
            pass

        if urlparse(input_path).scheme in ('http', 'https'):
            os.remove(input_path)
        
        return paths

    def download(self, input_path):
        response = requests.get(input_path, stream=True)
        with tempfile.NamedTemporaryFile(delete=False) as temp_file:
            temp_path = temp_file.name
            response.raw.decode_content = True
            shutil.copyfileobj(response.raw, temp_file)
        return temp_path
