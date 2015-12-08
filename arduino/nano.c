/*
NANO CODE
*/

#include <Wire.h>

byte temp_top_set = 0; // top pad set point
byte thermistor_top = 0; // thermistor at top

byte temp_bottom_set = 0;  // bottom set point
byte thermistor_bottom = 0; // thermistor at bottom

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register events
  Wire.onReceive(receiveCallback);
  
}

void loop() {
  delay(100);
  thermistor_top ^= 1 << 0;
  thermistor_bottom = ~ thermistor_top; //test
  
  /*Turning this on later...
  int tempRead = analogRead(tempPin);
    float tempVolt = float(tempRead) / 310; //3.1 Volts per division
    float tempF = ((100 * tempVolt) - 50)*1.8+32; // From TMP36 Datasheet, then C -> F conversion
    
    */
  
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  uint8_t tbuffer[2];
  tbuffer[0] = thermistor_top;
  tbuffer[1] = thermistor_bottom;
  Wire.write(tbuffer, 2);
  // as expected by master
}


void receiveCallback(int num_bytes_rec)
{
  if(num_bytes_rec == 2)
  {
    temp_top_set = Wire.read(); //temperature set point of the top sensor in celcius
    temp_bottom_set = Wire.read(); //temperature set point of the bottom pad in celcius
  }
  else
  {
    Serial.print("Malformed packet with size of: ");
    Serial.println(num_bytes_rec);
  }
}
