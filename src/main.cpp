#include <Arduino.h>

const int sensorIn1 = 9;    // pin where the OUT pin from sensor is connected on ESP
const int sensorIn2 = 8;    // pin where the OUT pin from sensor is connected on ESP
const int voltage_pin = 10; // pin where the OUT pin from sensor is connected on ESP
int mVperAmp = 100;         // this the 5A version of the ACS712 -use 100 for 20A Module and 66 for 30A Module
int Watt = 0;
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;

float getVPP(int sensorPin);

void setup()
{
  Serial.begin(115200);
  Serial.println("ACS712 current sensor");
}

void loop()
{
  // Calculate the current for the first sensor on IO8
  //  Serial.println("");
  //  Voltage = getVPP(sensorIn1);
  //  VRMS = Voltage *0.35355 ;
  //  AmpsRMS = VRMS * 10 ; //0.3 is the error I got for my sensor
  //  AmpsRMS -= 0.11;
  //  AmpsRMS *= 2;
  //  AmpsRMS /= 0.9853;
  //  Serial.print("Amps RMS 1 : ");
  //  Serial.println(AmpsRMS);
  //  Serial.println("");
  //  //------------------------------------------------------------------------------------------------------
  //  //Calculate the current for the second sensor on IO9
  //  Serial.println("");
  //  Voltage = getVPP(sensorIn2);
  //  // Serial.print("Voltage 2 : ");
  //  // Serial.println(Voltage);
  //  // AmpsRMS -= 0.21;
  //  VRMS = Voltage *0.35355 ;
  //  AmpsRMS = VRMS * 10 ; //0.3 is the error I got for my sensor
  //  AmpsRMS -= 0.21;
  //  AmpsRMS *= 2;
  //  AmpsRMS /= 0.9853;
  //  Serial.print("Amps RMS 2 : ");
  //  Serial.println(AmpsRMS);
  //  Serial.println("");
  //  // delay(100);
  Voltage = getVPP(voltage_pin);
  Voltage *= 0.35355;
  Serial.print("Votlage ");
  Serial.println(Voltage);
  Serial.println("");
}

// ***** function calls ******
float getVPP(int sensorPin)
{
  float result;
  int readValue;       // value read from the sensor
  int maxValue = 0;    // store max value here
  int minValue = 4096; // store min value here ESP32 ADC resolution
  uint32_t start_time = millis();
  while ((millis() - start_time) < 1000) // sample for 1 Sec
  {
    readValue = analogRead(sensorPin);
    // see if you have a new maxValue
    if (readValue > maxValue)
    {
      maxValue = readValue;
    }
    if (readValue < minValue)
    {
      minValue = readValue;
    }
  }
  // Subtract min from max
  result = ((maxValue - minValue) * 3.3) / 4096.0; // ESP32 ADC resolution 4096
  return result;
}
// Watt = (AmpsRMS * 240 / 1.2);
// // as the voltage measured at D34 depends on the length of the OUT-to-D34 wire
// // 240 is the main AC power voltage – this parameter changes locally
// Serial.print(Watt);