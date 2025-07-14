<div  align="center"> 

# Marbles Kit
[![License: MIT](https://img.shields.io/badge/License-MIT-red.svg)](https://opensource.org/licenses/MIT)

<sup>1</sup> **NOVA School of Science and Technology, Center of Technology and Systems (UNINOVA-CTS)**,
and Associated Lab of Intelligent Systems (LASI), NOVA University
Lisbon, 2829-516 Lisbon, Portugal

This work proposes the development of a control system for an industrial marble transportation machine using esp32 based [open modular controllers](https://github.com/NOVA-RICS-Open-Lab/open-modular-controller).
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
   
   The test was conducted using an ESP32 DEVKIT V1.

4. **Connect to Kit**

   The modular controller needs to be connected to the industrial marbles kit.
   We numbered the connections in order to have some organization and ease of documentaion.

   <div align="center">

   | ESP | Port | Value | Function |
   | :--- | :--- | :--- | :--- |
   | 1 | 1 | High | T1 Clockwise |
   | 1 | 2 | High | T1 Anticlockwise |
   | 1 | 3 | High | G1 Open |
   | 1 | 3 | Low | G1 Close |
   | 1 | 4 | High | G1 Down |
   | 1 | 4 | Low | G1 Up |
   | 2 | 5 | High | G2 Front |
   | 2 | 5 | Low | G2 Back |
   | 2 | 6 | High | G2 Down |
   | 2 | 6 | Low | G2 Up |
   | 2 | 7 | High | G2 middle on |
   | 2 | 7 | Low | G2 middle off |
   | 2 | 8 | High | T2 Front |
   | 2 | 9 | High | T2 Back |
   | 2 | 10 | High | G2 Grab |
   | 2 | 10 | Low | G2 Release |
   | 3 | 11 | High | G3 Up |
   | 3 | 12 | High | G3 Down |
   | 3 | 13 | High | G3 Open |
   | 3 | 14 | High | G3 Close |
   | 3 | 15 | High | G3 Rotate Clockwise |
   | 3 | 16 | High | G3 Rotate Anticlockwise |

   </div>

5. **Service Identification**
   - Each controller board is able to support 7 actuators and 7 sensors, having this in mind, define how many controllers you will need and what services you want them to provide.
   - Once you have identified the services, you can code their handlers using as example the code snipet below.

    ```bibtex
        server.on("/HEADER/", HTTP_MESSAGE_TYPE, HANDLER_FUNCTION);
    ```
   
      More on this can be found on any ESP32 code provided.

6. **Test Services**
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
├── imgs                            # images from this project
└── src                             # evaluation code
    ├── arduino                           # arduino code for the esp32 
    │   ├── esp1.ino                            # developed code for esp32 1
    │   ├── esp3.ino                            # developed code for esp32 2
    │   └── esp4.ino                            # developed code for esp32 3
    └── python                            # developed python code
        └── AutoBerlindes.py                    # developed orchuestration code
```
## <div align="center">Contribution Guidelines</div>
NOVA RICS Open Lab open source, and we welcome contributions from the community! See the [Contribution](CONTRIBUTING.md) guide for more information on the development workflow and the internals of the wandb library. For project related bugs and feature requests, visit [GitHub Issues](https://github.com/NOVA-RICS-Open-Lab/open-modular-controller/issues) or contact novaricsopenlab@gmail.com

## <div align="center">License</div>
This repository is released under the MIT License. Please see the [LICENSE](LICENSE) file for more details.

## <div align="center">Contacts</div>
For any questions regarding this or any other project please contact us at novaricsopenlab@gmail.com or enroll in our [Discussion Forum](https://github.com/NOVA-RICS-Open-Lab/open-modular-controller/discussions) for sharing your ideas and sharing projects.
