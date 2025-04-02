
import requests
import time

while True:
    #print("Start")
    post_response = requests.post("http://192.168.13.1:8009/berlindes/?skill=TOTAL")
    #print(".")
    time.sleep(2)
    post_response = requests.post("http://192.168.13.2:8009/berlindes/?skill=TOTAL")
    #print(".")
    post_response = requests.post("http://192.168.13.3:8009/berlindes/?skill=GRAB")
    #print(".")
    post_response = requests.post("http://192.168.13.2:8009/berlindes/?skill=MOVET2G2")
    #print(".")
    post_response = requests.post("http://192.168.13.3:8009/berlindes/?skill=RELEASE")
    #print(".")
    post_response = requests.post("http://192.168.13.2:8009/berlindes/?skill=MOVET2G3")
    #print("End")