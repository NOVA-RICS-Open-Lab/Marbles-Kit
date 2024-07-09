*************
Esp32 NUMBER 1

Responsible for:

T1 - Feeder for G1 / User
G1 - Station 1

Settings:

IP: http://192.168.250.180:8009/berlindes/
HTTP POST with param "skill" with the wanted skill.

Available skills:

"RESET"
"GRAB" 
"RELEASE"
"FEEDT1"
"FEEDG1"

"TOTAL" //main skill

Example Post: http://192.168.250.180:8009/berlindes/?skill=TOTAL

*************
Esp32 NUMBER 2

Responsible for:

T2 - Feeder for G3 / G2

G2 - Station 2

Settings:

IP: http://192.168.250.181:8009/berlindes/
HTTP POST with param "skill" with the wanted skill.

Available skills:

"RESET"

"GRAB"      
"RELEASE"   
"MOVEG2G1"  
"MOVEG2T2"  
"MOVET2G2"  
"MOVET2G3"  

"TOTAL" //main skill

Example Post: http://192.168.250.181:8009/berlindes/?skill=TOTAL

*************
Esp32 NUMBER 3

Responsible for:

G3 - Station 3

Settings:

IP: http://192.168.250.182:8009/berlindes/
HTTP POST with param "skill" with the wanted skill.

Available skills:

"RESET"
"GRAB"
"RELEASE"

Example Post: http://192.168.250.182:8009/berlindes/?skill=GRAB
