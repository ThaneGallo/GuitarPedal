# Analog Design!

## Passive component considerations
After lots of reading through xx(forgot name of book) it was made clear to me the depth that goes into manufacuring and how much variance can actually exist within passive components. 

My specific use case however has a constant temperature, need for a low tolerance for better filter characteristics, low distortion and thermal noise.


## Amplifier Design
Overall the idea for this is a set of small op-amp driven amplifiers that have a band-pass filter characteristic form 20Hz-20kHz which is the audible spectrum. A hardware based filter for PLI will not be included as it would be easier and more efficient to impliment a comb filter digitially to remove harmonics as well as the original 60Hz signal

## Component Selection
### Capacitors
Amongst all of the large variety of choices I have I was drawn to two different types. Since audio frequencies exist around 20Hz-20kHz I would need a beefy capacitor for the low end to attenuate the thermal noise. My choices are as followes

Polypropylene Film 

Polystyrene Film

honestly both extremely solid choices although it seems Polystyrene is a more "premium" choice for this as it generally seems to have better characteristics aside from the cost.

For now I will be using Polypropylene capacitors and after the next iteration will decide if I want to upgrade for crispier quality or not.

### Resistors
As noise is my main concern for this circuit as well as achieveing relatively tight tolerances I will be also have two options similar to the capacitors. One is metal film and the other is thin foil. Metal foil is more expensive than the other and will be skipped for this point in the project.


#### Potentiometer
Single turn pot rotary pots only as multi turns are prone to changing when undesired so for volume tuning.


### Inductors (or lack thereof)
As they pose a risk of noise and coupling with the audio signal they will not be used with the amplifier circuit directly but will be present in the switching regulator for the power sources.


## Power Sources
Since I am using an op amp that has a signal that swings negative I would need a negative and a positive source. This does not have to be super large as the expected value of the signal could have a range of max 3Vpp. I also wish for it to have a single power source that is transformed and modified with converters for easier user access.

My goal as far as noise is concerned will be around 


### TPS6513x
Input: 9v DC Source
Max Draw: 200-500mA (Significantly more than needed)
Switching Frequency: ~1.25MHz
Output: +- 5V with ~5mV ripple
Notes/Other Considerations: As this is going to be fed into a LDO after it is not critical that ripple is minimized at this stage however I will still aim for a low value of around 5mV

This chip also has multiple other features for controlling the chip digitally. As I want to mimimize complexity at this moment I will be skipping the enable pins and will be tying them directly to the Vin so the chip will always be on.

### LDO
Input:+- 5V with ~5mV ripple
Max Draw: 
Output: Clean +-3.3V with x ripple


### Power Supply Schematic 


### Schematic



