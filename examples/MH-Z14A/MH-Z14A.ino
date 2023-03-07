// #include <SoftwareSerial.h>
#include <MHZ.h>

// pin for pwm reading
#define CO2_IN 10

// pin for uart reading (SoftwareSerial)
#define MH_Z14_RX D4  // D7
#define MH_Z14_TX D0  // D6

//MHZ co2(MH_Z19_RX, MH_Z19_TX, CO2_IN, MHZ14A);
//MHZ co2(Serial2, CO2_IN, MHZ14A);
MHZ co2(Serial2, MHZ14A);

void setup() {
  Serial.begin(9600);
  
  // use HW serial
  Serial2.begin(9600);  // ESP32 uart2 - Pin Rx: 16 / Tx: 17  

  // pinMode(CO2_IN, INPUT); // use pwm
  delay(100);
  Serial.println("MHZ 14A");

  // enable debug to get addition information
  // co2.setDebug(true);

  if (co2.isPreHeating()) {
    Serial.print("Preheating");
    while (co2.isPreHeating()) {
      Serial.print(".");
      delay(5000);
    }
    Serial.println();
  }
}

void loop() {
  Serial.print("\n----- Time from start: ");
  Serial.print(millis() / 1000);
  Serial.println(" s");

  int ppm_uart = co2.readCO2UART();
  Serial.print("PPMuart: ");

  if (ppm_uart > 0) {
    Serial.print(ppm_uart);
  } else {
    Serial.print("n/a");
  }

  /* use pwm
  int ppm_pwm = co2.readCO2PWM();
  Serial.print(", PPMpwm: ");
  Serial.print(ppm_pwm);
  */

  Serial.println("\n------------------------------");
  delay(5000);
}
