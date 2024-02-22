import argparse
import os
from dotenv import load_dotenv


load_dotenv()
service = str(os.getenv("SERVICE_NAME"))
port = int(os.getenv("PORT"))
topic_name = str(os.getenv("TOPIC_NAME"))
message = str(os.getenv("MESSAGE"))
loop = int(os.getenv("LOOP"))


def tester_unique_service(service, port, topic_name, message):
    #todo
    count = 0
    mean = 0
    
    print("TODO")
    while count < loop:
        measure = measuring_processing_time(service)
        mean = mean + measure
        count = count + 1
    output = "mean/loop... json? string? print? csv?"
    return output


def measuring_processing_time():
    measure = 0
    
    return measure

def send_msg():
    return ""