# Hardware Design

## Table of Contents
* [Part Selection](#Part-Selection)
* [Development](#Development)
* [Roadbumps](#Roadbumps)
* [Conclusion / Future Design Changes](#Conclusion--Future-Design-cChanges)

## Part Selection

### Op-Amp



### ADC
The chosen ADC was [PCM1802DB](https://www.digikey.com/en/products/filter/data-acquisition/adcs-dacs-special-purpose/768?s=N4IgTCBcDaIIwA4AMYAiAhEBdAvkA)

This was chosen due to the following characteristics:

* Multiple internal filters such as anti-aliasing and high pass filters
* Stereo input (for future board development)
* 96kHz sample rate at max (44.1kHz is standard) to allow for higher fidelity 
* Supports I2S transactions and contains multiple control pins for different internal configurations


### MCU
The chosen MCU was [STM32F44RE](https://www.digikey.com/en/products/detail/stmicroelectronics/NUCLEO-F446RE/5347712?gclsrc=aw.ds&&utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Low%20ROAS%20Categories&utm_term=&utm_content=&utm_id=go_cmp-20243063506_adg-_ad-__dev-c_ext-_prd-5347712_sig-CjwKCAjwzMi_BhACEiwAX4YZUPHpk-zHzDov2nI4mvNVZQl9ZMhKRm_qsVS7q0sjmrhjJ651UxK07RoCICAQAvD_BwE&gad_source=1&gbraid=0AAAAADrbLlhzVWufnPiJhrASsS6sFmpfE&gclid=CjwKCAjwzMi_BhACEiwAX4YZUPHpk-zHzDov2nI4mvNVZQl9ZMhKRm_qsVS7q0sjmrhjJ651UxK07RoCICAQAvD_BwE&gclsrc=aw.ds)

This was chosen due to the following characteristics:

* Exists on a readily availible development board 
* High clock speed and FPU support
* Supports all different I2S formats that the ADC/DAC can use
* Used in industry and very user friendly

### DAC

### Power Distribution
The current network contains the following:
* Li-Po 7.4V 26000mAh battery 
* BMS for balancing voltages and charging
* Buck converter 7.4V --> 3.3
* Charge pump for dual +- 5V supply

#### Charging Circuit 


#### Where does the power go?

# Development 
# Roadbumps
# Conclusion / Future Design Changes
