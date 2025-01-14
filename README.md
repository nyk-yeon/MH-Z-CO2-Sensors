[**한글 README 페이지로 이동하기**](https://github.com/nyk-yeon/MH-Z-CO2-Sensors#mh-z14a-mh-z19b-co2--%EB%AA%A8%EB%93%88)  

# MH-Z14A, MH-Z19B CO2 ... Module

ESP32/Arduino implementation for MH-Z CO2 sensors such as **MH-Z14A**, **MH-Z19B** and **MH-Z19C** (as I didn't find all info in one place).

## Information about this fork repository  

**This modified fork repository has been tested with ESP32 (ESP32 DevKit) and MH-Z14A.**  

Fixed ESP32 and [MH-Z14A](https://www.eleparts.co.kr/goods/view?no=3186568) hardware serial compatibility, separated [ESP32](https://www.eleparts.co.kr/EPXRVLBX) software serial library  
Remove isReady, etc.  

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

---  
---  

# MH-Z14A, MH-Z19B CO2 ... 모듈  

ESP32/Arduino에서 **MH-Z14A**, **MH-Z19B** and **MH-Z19C** 센서 구동을 위한 라이브러리 입니다.  

**이 수정된 포크 저장소는 ESP32(ESP32 DevKit) 및 MH-Z14A로 테스트되었습니다.**  

MH-Z14A  
<https://www.eleparts.co.kr/goods/view?no=3186568>  

ESP32 DevKit v1 - ESP32 개발보드  
<https://www.eleparts.co.kr/EPXRVLBX>  

## Implementation  

출력  

> PPMuart: 602, PPMpwm: 595

### Implementation details

```text
C ppm = 5000 * (T_high - 2 ms) / (T_high + T_low - 4ms)
```

The implementation is mostly based on  <https://forum.arduino.cc/index.php?topic=525459.msg3587557#msg3587557>  

## 사용법  

PWM 기능을 사용할 때, 생성자의 RANGE 값은 MH-Z 센서의 내부 설정 값과 동일해야 합니다.  

기본적으로 PWM 범위 값은 5000 으로 설정되어 있으며 클래스 생성자에서 변경할 필요가 없습니다  
5000 이외의 설정을 사용하는 경우 범위를 변경해야 합니다.  

UART 기능은 Hardware Serial과 Software Serial을 선택해 사용 가능합니다.  

### Software Serial  

Software Serial 라이브러리 분리됨, 별도 설치 필요  

ESP32용 Software Serial 라이브러리는 아래 리포지토리를 추가하세요(아두이노 IDE 라이브러리 관리자에 있음).  
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
MHZ co2(SWSerial, CO2_IN, MHZ14A);              // 기본 Range 설정 (RANGE_5K)
MHZ co2(SWSerial, CO2_IN, MHZ14A, RANGE_5K);    // 센서 범위 설정이 다른 경우 수동 입력 is set 5K or 10k

void setup() {
    // USE SW serial
    SWSerial.begin(9600, SWSERIAL_8N1, RX_Pin, TX_Pin);

    // 센서 범위 설정 변경 (2k, 5k, 10k)
    co2.setRange(RANGE_5K);

    // pwm 핀 설정
    pinMode(CO2_IN, INPUT); 
}
```

### Hardware Serial  

Software serial 라이브러리가 필요하지 않습니다.  

Hardware Serial:  
ESP32: UART2 - Pin Rx: 16 / Tx: 17  

```c++  
#include <MHZ.h>

// Pin PWM
#define CO2_IN 18

MHZ co2(SWSerial, MHZ14A);                      // Serial only
MHZ co2(SWSerial, CO2_IN, MHZ14A);              // 기본 Range 설정 (RANGE_5K)
MHZ co2(SWSerial, CO2_IN, MHZ14A, RANGE_5K);    // 센서 범위 설정이 다른 경우 수동 입력 5K or 10k

void setup() {
    // HW serial 사용 - UART2
    Serial2.begin(9600);  // ESP32 uart2 - Pin Rx: 16 / Tx: 17  

    // 센서 범위 설정 변경 (2k, 5k, 10k)
    co2.setRange(RANGE_5K);

    // pwm 핀 설정
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

## Further reading:  

ESP32와 CO2 센서로 이산화탄소 농도 측정기 만들기  
https://blog.naver.com/elepartsblog/223046208897  
