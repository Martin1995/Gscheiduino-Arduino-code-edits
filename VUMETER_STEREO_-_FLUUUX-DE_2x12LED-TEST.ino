//source: http://fluuux.de/2012/09/arduino-vu-meter-audiolightshow-vu-meter/
//Audiokabel mit 3 Adern, weiß=A0, rot=A1, Kupfer=GNR
//5 LEDs für den linken Kanal an den digitalen Pins 4 - 8
//5 LEDs für den rechten Kanal an den digitalen Pins 9 - 13
 
int ledCountLeft  = 12;    // Anzahl der Leds für den linken Audio-Eingang
int ledCountRight = 12;    // Anzahl der Leds für den rechten Audio-Eingang
 
int ledsLeftChannel[12]  = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };      // Pins der LEDs für linken Audio-Eingang
int ledsRightChannel[12] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };  // Pins der LEDs für rechten Audio-Eingang

int Switch_PIN = A3;

int leftChannelPin  = A0;   // Analoger Pin für Linken Audio-Eingang
int rightChannelPin = A1;   // Analoger Pin für Rechten Audio-Eingang

int Divider = 43
 
int i;
 
void setup()

{  
  pinMode(leftChannelPin, INPUT);
  pinMode(rightChannelPin, INPUT);

  pinMode(Switch_PIN, OUTPUT);
 
  for (i = 0; i < ledCountLeft; i++)
    pinMode(ledsLeftChannel[i], OUTPUT);
 
  for (i = 0; i < ledCountRight; i++)
    pinMode(ledsRightChannel[i], OUTPUT);
 
  Serial.begin(9600);
}
 
void loop()
{
  int left      = analogRead(leftChannelPin);
  int right     = analogRead(rightChannelPin);
 
  Serial.println("LEFT: " + String(left) + " RIGHT: " + String(right));
 
  left  = left  / Divider;
  right = right / Divider;
 
  if (left == 0) {                                    // Wenn Lautstärke = 0 dann alle LEDs des linken Eingangs ausschalten
    for(i = 0; i < ledCountLeft; i++)
      digitalWrite(ledsLeftChannel[i], LOW);
      digitalWrite(Switch_PIN, LOW);
  }
  else
  {
    for (i = 0; i < left; i++)                       // LEDs einschalten, je höher die Lautstärke, desto mehr LEDs werden eingeschaltet
     digitalWrite(ledsLeftChannel[i], HIGH);
     digitalWrite(Switch_PIN, LOW);
 
    for(i = i; i < ledCountLeft; i++)                // LEDs ausschalten, je niedriger die Lautstärke, desto mehr LEDs werden ausgeschaltet
      digitalWrite(ledsLeftChannel[i], LOW);
      digitalWrite(Switch_PIN, LOW);
  }

delay(10);
 
  if (right == 0) {                                   // Wenn Lautstärke = 0 dann alle LEDs des rechten Eingangs ausschalten
    for(i = 0; i < ledCountRight; i++)
      digitalWrite(ledsRightChannel[i], HIGH);
      digitalWrite(Switch_PIN, HIGH);
  }
  else
  {
    for (i = 0; i < right; i++)                       // LEDs einschalten, je höher die Lautstärke, desto mehr LEDs werden eingeschaltet
     digitalWrite(ledsRightChannel[i], LOW);
     digitalWrite(Switch_PIN, HIGH);
 
    for(i = i; i < ledCountRight; i++)               // LEDs ausschalten, je niedriger die Lautstärke, desto mehr LEDs werden ausgeschaltet
      digitalWrite(ledsRightChannel[i], HIGH);
      digitalWrite(Switch_PIN, HIGH);
  }
}
