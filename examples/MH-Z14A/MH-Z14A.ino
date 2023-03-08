#include <MHZ.h>

// pin for pwm reading
#define CO2_IN 18

// MHZ co2(Serial2, MHZ14A);                  // Serial only
// MHZ co2(Serial2, CO2_IN, MHZ14A);
MHZ co2(Serial2, CO2_IN, MHZ14A, RANGE_10K);


void setup() {
  Serial.begin(115200);
  
  // Use HW serial - UART2
  Serial2.begin(9600);  // ESP32 uart2 - Pin Rx: 16 / Tx: 17  

  // pwm pin set
  pinMode(CO2_IN, INPUT); 

  // sensor range setting (2k, 5k, 10k)
  // co2.setRange(RANGE_5K);

  delay(100);
  Serial.println("MHZ 14A");

  // Enable debug to get addition information
  // co2.setDebug(true);
 
  // Sensor Preheat time - MHZ14A 3min
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

  // UART
  int ppm_uart = co2.readCO2UART();
  Serial.print("PPMuart: ");

  if (ppm_uart > 0) {
    Serial.print(ppm_uart);
  } else {
    Serial.print("n/a");
  }

  // PWM
  int ppm_pwm = co2.readCO2PWM();
  Serial.print(", PPMpwm: ");
  Serial.print(ppm_pwm);
  

  Serial.println("\n------------------------------");
  delay(5000);
}
