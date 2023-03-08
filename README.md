# MH-Z14A, MH-Z19B CO2 ... Module

ESP32/Arduino implementation for MH-Z CO2 sensors such as **MH-Z14A**, **MH-Z19B** and **MH-Z19C** (as I didn't find all info in one place).

MH-Z14A  
<https://www.eleparts.co.kr/goods/view?no=3186568>  

**This modified fork repository has been tested with ESP32 (NodeMCU-32S) and MH-Z14A.**  

[한글 README](https://github.com/nyk-yeon/MH-Z-CO2-Sensors/blob/master/README_kr.md)  

## Implementation  

See example.

> PPMuart: 602, PPMpwm: 595

### Implementation details

```text
C ppm = 5000 * (T_high - 2 ms) / (T_high + T_low - 4ms)
```

The implementation is mostly based on  <https://forum.arduino.cc/index.php?topic=525459.msg3587557#msg3587557>  

## Usage

When using the PWM function, the RANGE must be the same as the MHZ sensor  

By default the PWM range value is set to 5000 and there is no need to change anything in the class constructor (if the Cppm value is in the expected range 400-1000), otherwise you may want to test it with 2000 range value :  

### Software Serial  

Detaching the Software Serial Library  

Refer to the repository below for the ESP32 Software Serial library.  
<https://github.com/plerup/espsoftwareserial>  

```c++
#include <MHZ.h>
#include <SoftwareSerial.h>

// Pin PWM
#define CO2_IN 18

// pin for uart (SoftwareSerial)
#define RX_Pin 22 // Connect sensor Tx
#define TX_Pin 23 // Connect sensor Rx

SoftwareSerial SWSerial;

MHZ co2(SWSerial, MHZ14A);                      // Serial only
MHZ co2(SWSerial, CO2_IN, MHZ14A);              // here the range value is set to 5000 by default (RANGE_5K)
MHZ co2(SWSerial, CO2_IN, MHZ14A, RANGE_5K);    // here the range value is set 5K or 10k

void setup() {
    // USE SW serial
    SWSerial.begin(9600, SWSERIAL_8N1, RX_Pin, TX_Pin);

    // Change sensor range settings (2k, 5k, 10k)
    co2.setRange(RANGE_5K);

    // pwm pin set
    pinMode(CO2_IN, INPUT); 
}

```

### Hardware Serial  

No software serial library required.  

Hardware Serial:  
ESP32: UART2 - Pin Rx: 16 / Tx: 17  

```c++
#include <MHZ.h>

// Pin PWM
#define CO2_IN 18

MHZ co2(Serial2, MHZ14A);                       // Serial only
MHZ co2(Serial2, CO2_IN, MHZ14A);               // here the range value is set to 5000 by default (RANGE_5K)
MHZ co2(Serial2, CO2_IN, MHZ14A, RANGE_10K);    // here the range value is set 5K or 10k

void setup() {
    // Use HW serial - UART2
    Serial2.begin(9600);  // ESP32 uart2 - Pin Rx: 16 / Tx: 17  

    // Change sensor range settings (2k, 5k, 10k)
    co2.setRange(RANGE_5K);

    // pwm pin set
    pinMode(CO2_IN, INPUT); 
}
```  

## Resources:  

Datasheet (MH-Z14A):
<https://www.winsen-sensor.com/d/files/mh-z14a-co2-manual-v1_4.pdf>

Datasheet (MH-Z19B):
<http://www.winsen-sensor.com/d/files/infrared-gas-sensor/mh-z19b-co2-ver1_0.pdf>

Datasheet (MH-Z19C):
<https://pdf1.alldatasheet.com/datasheet-pdf/view/1303687/WINSEN/MH-Z19C.html>

More info about the sensor:
<https://revspace.nl/MHZ19>

## Further reading:  

- http://ihormelnyk.com/Page/mh-z19_co2_meter

(russuian, but google translate does a good job)
- https://geektimes.ru/post/285572/
- https://geektimes.ru/post/278178/

