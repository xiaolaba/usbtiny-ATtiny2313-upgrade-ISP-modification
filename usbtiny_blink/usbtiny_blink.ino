/*
blink port D and port B of Attiny2313
usbtiny has two LED used for power indication and busy, PD5 and PB0

https://dicks.home.xs4all.nl/avr/usbtiny/
https://cdn-learn.adafruit.com/assets/assets/000/010/326/original/usbtinyisp2sch.png
modified JUN-04-2011 by xiaolaba


*/


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  
  DDRD = B11111110; // sets D1-D7 as outputs, D0 as input
  DDRD = DDRD | B11111100; // D2 – D7 outputs, D0 = TX, D1 = RX
  DDRB = B00111111; //PORTB maps to D8 to D13, two high bits (6 & 7) map to the crystal pins, no use
}


#define dly 4000 //delay time, unit ms

void blink_port_500ms(){
  PORTD = B11111111;
  PORTB = B00111111;
  delay(dly); // wait for 0.5 second;
  PORTD = 0x0;
  PORTB = 0x0;
  delay(dly); // wait for 0.5 second;
}

void loop() {
  blink_port_500ms();
}
