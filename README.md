# 🎮NRF24L01 Controller and Receiver

My project is an NRF24L01 Controller and Receiver. The idea is to use NRF communication to control any car or any RC device, in a way that allows it to be connected to any device, not dedicated to a single car, drone, or RC plane.

---

# 🚀Usage of the Project

Instead of buying an RC controller and receiver, you can DIY your own. It is more customizable, and you can control the number of channels and features according to your needs. With this controller, you are able to control an RC car, RC plane, RC boat, and any other RC device. The best thing is that it is upgradable: you can upgrade the joysticks to higher-quality ones for more precision, the NRF module to a better one with more range, and even the battery and other components. This flexibility is why it is better than the commercial one.

---

# ✨Features
* 📶Long range
* ⚡Low lantency
* 🌍Open-Source
* 🛠️Easy to make

---

# 🔩Components

* Arduino pro mini
* ADXL345
* Joystics
* Mosfet
* 5V voltage regulator
* NRF Module
* 0.96" I2C OLED display
* 120 * 180mm perforated plate
* 40-PIN 2.0mm Single Female Breakable Power Strip
* 40-PIN 2.0mm Single Male Breakable Power Strip
* Wires

---

# 💻Software requirements

**Arduino IDE**
* <SPI.h> library
* <RF24.h> library
* <Wire.h> library
* <Adafruit_GFX.h> library
* <Adafruit_SSD1306.h> library
* <Adafruit_ADXL345_U.h> library

---

# 🖼️Here are some images for my project 

![3d29e406-d13c-45fb-8668-cd6f811e18a5](https://github.com/user-attachments/assets/127c8d96-838e-4969-aee2-5514184b4756)
![1a8ff81d-e89b-45f4-ad1f-db64161f107a](https://github.com/user-attachments/assets/6f838bae-033d-49a1-a552-ee14f66daa33)
<img width="1920" height="1080" alt="2" src="https://github.com/user-attachments/assets/06c7bb70-d57b-4061-9974-b8a618aaac1d" />
<img width="1920" height="1080" alt="1" src="https://github.com/user-attachments/assets/148ab8ad-6251-45c7-9b05-eac477faec40" />

---

# ⚙️Setup 
The setup of the project is easy. As the Pro Mini does not have a USB port, you should use an FTDI232 to upload the code. However, before uploading the code, you should change
const byte addr[6] = "00001";
which is the address of your NRF channel. Change it to whatever you want, but most importantly, make sure it is the same in both the transmitter and receiver code.

![5a2cf62c-e1f3-419b-b7a8-c6350b661b8c](https://github.com/user-attachments/assets/636c1b14-01f2-424f-b50a-9240fcda7a80)
<img width="803" height="157" alt="{BC20082C-80BD-474D-A4F6-BE51961F4A0B}" src="https://github.com/user-attachments/assets/46f1773c-68ec-4416-b3e5-0849f95a4773" />
<img width="692" height="121" alt="{1098038B-6B9A-4797-80FC-0F39AC50E7C9}" src="https://github.com/user-attachments/assets/827a86f3-f11a-4680-968e-0563f3a9035c" />

---

# 🛠️Configuration

To use the controller, you are able to modify it as it pleases you. You have two joystick values and ADXL345 values, and you can match them with whatever you want in the receiver code in order to control devices like servo motors, LEDs, simple motors, or any output that pleases you. You can use pins 4, 5, 6, 7, 8, and 9 in the receiver and match them with conditions of the joystick and ADXL345 of the transmitter.


<img width="1077" height="788" alt="{020A14A6-894D-46D8-BB32-A1696C7E0EE9}" src="https://github.com/user-attachments/assets/a52c9f07-80b4-4d79-8299-2df39e40704a" />


