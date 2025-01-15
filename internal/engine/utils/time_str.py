import datetime
import time

def now_time_string(hash_name: int):
    timestamp = time.time()
    date_time = datetime.datetime.fromtimestamp(timestamp)
    return date_time.strftime('%Y-%m-%d-%H-%M-%S-') + str(hash_name)