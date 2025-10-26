# Mecanum_wheel_Smart_Car_Prototype

This project presents the design and development of a smart Mecanum wheel vehicle capable of both manual and autonomous operation. The system is built around the STM32F103C8T6 (Blue Pill) microcontroller and integrates various sensors and modules for motion control, obstacle detection, and wireless communication. 

---

## 🔧 Features
The operational logic of the system begins with the initialization of the system once the vehicle is powered on. The user is first prompted to select between two operating modes: Manual or Auto. In Manual Mode, control is handed over to the user via a smartphone application connected through the HC-05 Bluetooth module. User can move the car in any direction (forward, backward, left, right, diagonal, rotation and so on). The system operates in the same mode until the user give the command to change to the Auto mode. Once the user set the mode to Auto mode, it starts to move forward automatically following the black path. The system moves toward the front if the black lines from either side is not detected. The obstacle and path checking sequence runs automatically until the user returns to the Manual mode setting. Through manual and auto mode the system can operates efficiently in different situations even in the confined spaces. 

- **Auto Mode:**  
  - Detects obstacles using ultrasonic sensor (HC-SR04) mounted on a servo motor  
  - Stops vehicle when an obstacle is detected and resumes when clear  
- **Manual Mode:**  
  - Bluetooth (HC-05) control via Android smartphone app  
- **Line Following:** IR sensors for path detection and correction  
- **OLED Display:** 0.96" display shows system state and obstacle distance  
- **Custom PCB:** Designed in EasyEDA and tested via Proteus simulation  
- **Omnidirectional Motion:** Achieved using four Mecanum wheels with TT motors

---

## ⚙️ Main Hardware Components
| Component | Description |
|-----------|-------------|
| STM32F103C8T6 | Main microcontroller |
| TB6612FNG | Motor driver for 4 wheels |
| HC-05 | Bluetooth communication module |
| HC-SR04 | Ultrasonic sensor for obstacle detection |
| SG90 | Servo motor to rotate ultrasonic sensor |
| IR Sensors | Line following and path detection |
| OLED 0.96" | I2C display for real-time feedback |
| TT Motors + Mecanum Wheels | Omnidirectional motion |
| Battery Pack (12V) | Power Supply |

--

## 🧠 Software Tools
- STM32CubeMX  
- Keil uVision IDE  
- Proteus Simulation  
- EasyEDA PCB Design
- MIT App Inventor to design the Remote Controller App for Android Phone


---

## 📷 Project Gallery

### 🧩 PCB Layout
PCB: 
---
<img width="559" height="515" alt="PCB" src="https://github.com/user-attachments/assets/0de47a53-034d-4c41-9db8-296fdd7e6c8f" />

Schematic Diagram: 
---
<img width="1129" height="825" alt="Schematic_diagram" src="https://github.com/user-attachments/assets/0ccbd641-ea4b-4eee-a879-552815c8c8c0" />

----

Mecanum Wheel:
---
![Mecanum Wheel](https://github.com/user-attachments/assets/7d4fb3e1-245e-43b6-bf06-74529b457bdd)




### 🤖 Mecanum Car Prototype:
---
![c5ea2884be367eb5b4597f2aade0d464](https://github.com/user-attachments/assets/1056bb14-16df-4906-9e96-57838724fa49)
![409906d4871d7f1de4ec9df567fd132c](https://github.com/user-attachments/assets/0830146a-b980-43ea-bf06-be675710ee53)
![329ff36093e51433b83004fee03ab6aa](https://github.com/user-attachments/assets/4cf6f07f-d5c6-4d02-8de9-455d3251cbcb)


---
## 🔧 Hardware Components
STM32F103C8T6:
---
<img width="899" height="603" alt="STM32 CHIP" src="https://github.com/user-attachments/assets/474a5379-07d9-41f3-8890-69216421ad90" />



Motor Driver:
---
![Motor_driver](https://github.com/user-attachments/assets/31d41081-e271-4a97-902e-01f59b9ecfdb)

IR Sensor:
---
<img width="793" height="328" alt="IR_sensor" src="https://github.com/user-attachments/assets/32eb8d18-85f0-431c-b65d-5a265c535284" />

Ultrasonic Sensor:
---
![Ultrasonic_sensor](https://github.com/user-attachments/assets/a47121ae-117b-4f58-b63c-70204b9b6e97)


Bluetooth Module:
---
![HC_05 bluetooth module](https://github.com/user-attachments/assets/09cbc151-23bc-4ec0-9702-4c3d954c56f1)


### 🎥 Video Demonstration
---


https://github.com/user-attachments/assets/93c06f23-17a9-4f16-9394-6318988b5f13



https://github.com/user-attachments/assets/e1e55ff7-4ffa-4e40-a549-7270eccaefb4








---
