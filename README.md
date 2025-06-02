<div  align="center"> 

# Marbles Kit
[![License: MIT](https://img.shields.io/badge/License-MIT-red.svg)](https://opensource.org/licenses/MIT)

<sup>1</sup> **NOVA School of Science and Technology, Center of Technology and Systems (UNINOVA-CTS)**,
and Associated Lab of Intelligent Systems (LASI), NOVA University
Lisbon, 2829-516 Lisbon, Portugal

This work proposes the development of a control system for an industrial marble transportation machine using 
</div>

## <div align="center">Get Started</div>
Follow these steps to set up your ESP:

1. **Controller PCB**
   - You can find a detailed description on how to assemble your own controller pcb [here](https://github.com/NOVA-RICS-Open-Lab/open-modular-controller).

2. **Dependencies**
   - Python
     In order to run python the requests module is needed:
    ```bibtex
    $ python -m pip install requests
    ```
   - Arduino
     In order to implement http services you will need 2 Librarys:
        - WiFi.h
        - WebServer.h
     All these librarys come insisde the [ESP's board package from expressif](https://github.com/espressif/arduino-esp32)
   - Pins and Ports
   ```bibtex
   #define ATUADOR_1 23
   #define ATUADOR_2 22
   #define ATUADOR_3 21
   #define ATUADOR_4 19
   #define ATUADOR_5 18
   #define ATUADOR_6 5
   #define ATUADOR_7 17
   ```
   There are the specified ports used for the actuators, who need to be setup as Outputs.
   - WiFi configuration
  
      The SSID and Password for the wifi network also need to be specified along with his static IP. ESP code lack this elements

3. **Gather Components**
   - The test was conducted using an ESP32 DEVKIT V1.

4. **Service Identification**
   - Each controller board is able to support 7 actuators and 7 sensors, having this in mind, define how many controllers you will need and what services you want them to provide.
   - Once you have identified the services, you can code their handlers using as example the code snipet below.

    ```bibtex
        server.on("/HEADER/", HTTP_MESSAGE_TYPE, HANDLER_FUNCTION);
    ```
   
      More on this can be found on any ESP32 code provided.


5. **Test Services**
   - Test your Services using a browser or any other application. (We recomend Postman)

If everything goes well, congratulations! You have implemented a functional services based industrial system.

### Implementation Description
For our case in particular, we used 3 Controllers that provide the services described below.

## Esp32 NUMBER 1

**Responsible for:**

T1 - Feeder for G1 / User
G1 - Station 1

**Settings:**

IP: http://192.168.13.1:8009/berlindes/

**Available skills:**

"RESET" "GRAB" "RELEASE" "FEEDT1" "FEEDG1"

"TOTAL" //main skill

**How to use:**

HTTP POST with param "skill" with the wanted skill. 

**Example Post:** 
```bibtex
http://192.168.13.1:8009/berlindes/?skill=TOTAL
```

*************
## Esp32 NUMBER 2

**Responsible for:**

T2 - Feeder for G3 / G2

G2 - Station 2

**Settings:**

IP: http://192.168.13.2:8009/berlindes/

**Available skills:**

"RESET" "GRAB" "RELEASE" "MOVEG2G1" "MOVEG2T2" "MOVET2G2" "MOVET2G3"  

"TOTAL" //main skill

**How to use:**

HTTP POST with param "skill" with the wanted skill. 

**Example Post:**
```bibtex
http://192.168.13.2:8009/berlindes/?skill=TOTAL
```

*************
## Esp32 NUMBER 3

**Responsible for:**

G3 - Station 3

**Settings:**

IP: http://192.168.13.3:8009/berlindes/

**Available skills:**

"RESET"
"GRAB"
"RELEASE"

**How to use:**

HTTP POST with param "skill" with the wanted skill. 

**Example Post:** 
```bibtex
http://192.168.13.3:8009/berlindes/?skill=GRAB
```

### Project Structure
For you to better understand this repository organization here is a quick overview of its structure and where to find what you might be looking for:
```
Marbles-Kit
├── imgs                # images from this project
└── src                 # evaluation code
    ├── esp1                # developed code
    ├── esp3                # developed code
    └── esp4                # developed code
```
## <div align="center">Contribution Guidelines</div>
NOVA RICS Open Lab open source, and we welcome contributions from the community! See the [Contribution](CONTRIBUTING.md) guide for more information on the development workflow and the internals of the wandb library. For project related bugs and feature requests, visit [GitHub Issues](https://github.com/NOVA-RICS-Open-Lab/open-modular-controller/issues) or contact novaricsopenlab@gmail.com

## <div align="center">License</div>
This repository is released under the MIT License. Please see the [LICENSE](LICENSE) file for more details.

## <div align="center">Contacts</div>
For any questions regarding this or any other project please contact us at novaricsopenlab@gmail.com or enroll in our [Discussion Forum](https://github.com/NOVA-RICS-Open-Lab/open-modular-controller/discussions) for sharing your ideas and sharing projects.
