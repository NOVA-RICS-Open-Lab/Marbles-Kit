
import requests
import time
print("Start\n")
post_response = requests.post("http://192.168.250.180:8009/berlindes/?skill=TOTAL")
print(".")
time.sleep(2)
post_response = requests.post("http://192.168.250.181:8009/berlindes/?skill=TOTAL")
print(".")
post_response = requests.post("http://192.168.250.182:8009/berlindes/?skill=GRAB")
print(".")
post_response = requests.post("http://192.168.250.181:8009/berlindes/?skill=MOVET2G2")
print(".")
post_response = requests.post("http://192.168.250.182:8009/berlindes/?skill=RELEASE")
print(".")
post_response = requests.post("http://192.168.250.181:8009/berlindes/?skill=MOVET2G3")
print("\nEnd")