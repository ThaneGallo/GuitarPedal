# Abstract 
  A custom reprogrammable guitar pedal using C++ for drivers and digital signal processing to allow for emulation of analog pedals.

#Intro 
  This project was began after my other music related project as it sparked an interest in muscial technologies as well as my interest of embedded system design. The original idea was to create an analog pedal however I would want the most functionality with the least amount of effort for the user this led me to the conclusion that I would need a digital system as I would be theoretically able to reprogram, adjust, and add lots of options for use including but not limited to:

  * Delay 
  * Gain 
  * Distortion 
  * Filters
  * Etc


As this system contains custom hardware and software I decided to split up into other files for ease of reading with the links below:


# Table of Contents
* [Skills Utilized](#Skills-Utilized)
* [System Diagram](#System-Diagram)
* [Hardware Design](#Hardware-Design)
* [Software Design](#Software-Design)
* [Known Issues](#Known-Issues)
* [Conclusion](#Conclusion)
* [Acknowledgements](#Acknowledgements)

# Skills Utilized
Hardware:
* KiCAD
* Amplifier and filter design
* Mixed signal circuit design
* Power system design
* 4-Layer-PCB

Software:
* Digital Signal Processing (DSP)
* C++/C
* FreeRTOS
* I2S
* HAL / Device Drivers

# System Diagram

# Hardware Deisgn

1. **Amplify Analog Audio Signal**:  
   The analog audio signal is first amplified to the desired level of **3 V peak-to-peak (Vp-p)**.

2. **Digitize Signal (ADC)**:  
   The amplified analog signal is converted into a digital format using an **Analog-to-Digital Converter (ADC)** for further processing.

3. **Process Signal (STM32F44RE)**:  
   The digitized signal is processed using the **STM32F44RE microcontroller**, which performs necessary filtering, manipulation, and any other DSP tasks.

4. **Convert Signal to Analog (DAC)**:  
   After processing, the signal is converted back to an analog signal using a **Digital-to-Analog Converter (DAC)**.

5. **Output Signal**:  
   The final analog output is sent through either a **3.5mm headphone jack** or a **1/4" amplifier jack** for listening or further amplification.

More in depth information can be found [here](Documentation/Hardware%Design.md)

---

## Power System Overview

- **Battery**:  
  The system is powered by a **7.4V Li-Po battery**, featuring a **battery management system (BMS)** for safe operation. The system also supports **USB-C recharging**.

- **Voltage Regulation**:  
  - A **buck converter** is used to step down the battery voltage to a stable **3.3V output** for the microcontroller and other low-voltage components.
  - A **charge pump** generates the required **5V** and **-5V outputs** for components that require dual polarity voltage (e.g., certain op-amps or other analog circuits).

Battery life depends on the active filters being used. It can range between **X hours to Y hours**, depending on the power consumption of the system and the complexity of the signal processing.

For more detailed development documentation, refer to the full hardware design specification in the linked document:  
[**Hardware Design Documentation**](/Documentation/Hardware Design.md)

# Software Design
The high level signal flow for software consists as follows.

1. Amplify analog audio signal to desired level (3Vp-p)
2. Digitize Signal (ADC)
3. Process Signal (STM32F44RE)
4. Convert signal to analog (DAC)
5. Output signal through either 3mm headphone jack or 1/4" amp jack

More in depth information can be found [here](Documentation/Software%Design.md)


# Known Issues
* The filter is not perfectly centered around the 1.5 v value with perfect size to fit the whole adc sampling range there is a calibration feature to be added which would give feedback and tell you to adjust the volume potentiometer on the input guitar.

# Conclusion

# Acknowledgements
* 
