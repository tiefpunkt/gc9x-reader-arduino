/*


*/

const byte command[] = {0x77, 0x33, 0xC0, 0x41};
uint32_t voltage, current, power, usage, cum_usage;
uint16_t temperature;
#include <SoftwareSerial.h>

SoftwareSerial gc9x(8, 9); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("DC Meter Reader");

  // set the data rate for the SoftwareSerial port
  gc9x.begin(19200);
}

uint8_t readWhenAvailable() {
  while (gc9x.available() == 0) {
    delay(10);
  }
  return gc9x.read();
}

void gatherData() {
  uint8_t a,b,c,d;
  gc9x.write(command,4);
  // Header
  readWhenAvailable();
  readWhenAvailable();
  readWhenAvailable();
  readWhenAvailable();
  // address
  readWhenAvailable();
  // voltage
  a = readWhenAvailable();
  b = readWhenAvailable();
  c = readWhenAvailable();
  d = readWhenAvailable();
  voltage = (long)a << 24 |  (long)b << 16 |  (long)c << 8 | d;
  // current
  a = readWhenAvailable();
  b = readWhenAvailable();
  c = readWhenAvailable();
  d = readWhenAvailable();
  current = (long)a << 24 |  (long)b << 16 |  (long)c << 8 | d;
  // power
  a = readWhenAvailable();
  b = readWhenAvailable();
  c = readWhenAvailable();
  d = readWhenAvailable();
  power = (long)a << 24 |  (long)b << 16 |  (long)c << 8 | d;
  // usage
  a = readWhenAvailable();
  b = readWhenAvailable();
  c = readWhenAvailable();
  d = readWhenAvailable();
  usage = (long)a << 24 |  (long)b << 16 |  (long)c << 8 | d;
  // loadtime
  readWhenAvailable();
  readWhenAvailable();
  readWhenAvailable();
  readWhenAvailable();
  // capacity
  readWhenAvailable();
  readWhenAvailable();
  readWhenAvailable();
  readWhenAvailable();
  // cummulative usage
  a = readWhenAvailable();
  b = readWhenAvailable();
  c = readWhenAvailable();
  d = readWhenAvailable();
  cum_usage = (long)a << 24 |  (long)b << 16 |  (long)c << 8 | d;
  // cum. capacity
  readWhenAvailable();
  readWhenAvailable();
  readWhenAvailable();
  readWhenAvailable();
  // cum. loadtime
  readWhenAvailable();
  readWhenAvailable();
  readWhenAvailable();
  readWhenAvailable();
  // temperature
  c = readWhenAvailable();
  d = readWhenAvailable();
  temperature = (c << 8) + d;
  // switch
  readWhenAvailable();
}

void loop() { // run over and over
  gatherData();
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" mV");
  Serial.print("Current: ");
  Serial.print(current);
  Serial.println(" mA");
  Serial.print("Power: ");
  Serial.print(power);
  Serial.println(" mW");
  Serial.print("Usage: ");
  Serial.print(usage);
  Serial.println(" mWH");
  Serial.print("Cumulative Usage: ");
  Serial.print(cum_usage);
  Serial.println(" mWH");
  Serial.print("Temperature: ");
  Serial.print(temperature/10.0);
  Serial.println(" °C");

  Serial.println("-----------------------------");

  delay(10000);

}
