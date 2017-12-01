//https://playground.arduino.cc/ArduinoNotebookTraduccion/Appendix3
//http://www.circuitstoday.com/pwm-generation-and-control-using-arduino                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             //ATtiny85 RGB color fading Mood Light && fan fading!!

const int redPin = 2; 
const int grnPin = 0; 
const int bluPin = 1;
const int potenciometro = A2; //CAMBIE 3 DIGITAL POR 3 ANALOG, PROBAR SI ANDA SINO DEJARLO COMO DIGITAL.
const int pwmPin = 3;
//const int resetpin = RESET;
//int vel1,vel2,vel3,velocidadfinal;

// variables del potenciometro:
int velocidad = 0;         // the sensor value
int velocidadMin = 0;        // minimum sensor value
int velocidadMax = 1023;           // maximum sensor value

int t1 = 0;   // declarams variable tiempo 1
int t2 = 0;   // declarams variable tiempo 2

//variables para promediar la lectura, para una lectura mas precisa del valor del potenciometro.
const int numReadings = 5;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average


void setup()
{
  pinMode(redPin, OUTPUT);    
  pinMode(grnPin, OUTPUT);    
  pinMode(bluPin, OUTPUT);
  pinMode(potenciometro, INPUT);
  pinMode(pwmPin, OUTPUT);

  while (millis() < 5000) { //Calibramos el potenciometro y su lectura.
    t2 = analogRead(potenciometro);

    // record the maximum sensor value
    if (t2 > velocidadMax) {
      velocidadMax = t2;
    }

    // record the minimum sensor value
    if (t2 < velocidadMin) {
      velocidadMin = t2;
    }
     
}
for (int thisReading = 0; thisReading < numReadings; thisReading++) {
  readings[thisReading] = 0;
}
}

void loop() {

    PwmCooler();  
    if (velocidad > 100 && velocidad < 200) //cambiar aca para el pote de 10
  {
    redtoyellow();
    yellowtogreen();
    greentocyan();
    cyantoblue();
    bluetomagenta();
    magentatored();
  }
  else if (velocidad <= 100)
  {
    digitalWrite(redPin, LOW);
    digitalWrite(grnPin, LOW);
    digitalWrite(bluPin, HIGH);
  }
  else if (velocidad >= 200)
  {
    digitalWrite(grnPin, LOW);
    digitalWrite(bluPin, LOW);
    digitalWrite(redPin, HIGH);
  }
}
  
void PwmCooler(){
  // subtract the last reading:
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = analogRead(potenciometro);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }
  // calculamos el promedio
  average = total / numReadings;
    // read the sensor:
  t2= average;
  t1= 1023-t2;         // subtracts t2 from 1000 ans saves the result in t1
  //esta resta es por que es una lectura digital del pote(va de 0-1023).
    // apply the calibration to the sensor reading
  
 //velocidad = map(t2, velocidadMin, velocidadMax, 0, 255); //No ESTOY USANDO ESTO
    // in case the sensor value is outside the range seen during calibration
 //velocidad= constrain(velocidad, 0, 255); //TAMPOCO ESTOY USANDO ESTO, YA QUE 
  //LA SALIDA ES DIGITAL Y USO SOLO T1 Y T2.
//analogWrite(pwmPin, velocidad); NO SIRVE POR EL PIN SELECCIONADO, NO POSEE PWM. PASAMOS A PWM DIGITAL
  
  digitalWrite(pwmPin, HIGH); // sets pin 12 HIGH
  delayMicroseconds(t2);   // waits for t1 uS (high time)
  digitalWrite(pwmPin, LOW);  // sets pin 12 LOW
  delayMicroseconds(t1);   // waits for t2 uS (low time)  
  //cambie t1 por t2 en el high and low, probar! 19.32:21/10/17 
}

void redtoyellow()
{
  digitalWrite(redPin, HIGH);
  digitalWrite(bluPin, LOW);

  // fade up green
  for(byte i=1; i<100; i++) {
    byte on  = i;
    byte off = 100-on;
    for( byte a=0; a<100; a++ ) {
      digitalWrite(grnPin, HIGH);
      delayMicroseconds(on);
      digitalWrite(grnPin, LOW);
      delayMicroseconds(off);
    }
  }
}



void yellowtogreen()
{
  digitalWrite(grnPin, HIGH);
  digitalWrite(bluPin, LOW);

  // fade down red
  for(byte i=1; i<100; i++) {
    byte on  = 100-i;
    byte off = i;
    for( byte a=0; a<100; a++ ) {
      digitalWrite(redPin, HIGH);
      delayMicroseconds(on);
      digitalWrite(redPin, LOW);
      delayMicroseconds(off);
    }
  }
}


void greentocyan()
{
  digitalWrite(grnPin, HIGH);
  digitalWrite(redPin, LOW);

  // fade up blue
  for(byte i=1; i<100; i++) {
    byte on  = i;
    byte off = 100-on;
    for( byte a=0; a<100; a++ ) {
      digitalWrite(bluPin, HIGH);
      delayMicroseconds(on);
      digitalWrite(bluPin, LOW);
      delayMicroseconds(off);
    }
  }
}



void cyantoblue()
{
  digitalWrite(bluPin, HIGH);
  digitalWrite(redPin, LOW);

  // fade down green
  for(byte i=1; i<100; i++) {
    byte on  = 100-i;
    byte off = i;
    for( byte a=0; a<100; a++ ) {
      digitalWrite(grnPin, HIGH);
      delayMicroseconds(on);
      digitalWrite(grnPin, LOW);
      delayMicroseconds(off);
    }
  }
}


void bluetomagenta()
{
  digitalWrite(bluPin, HIGH);
  digitalWrite(grnPin, LOW);

  // fade up red
  for(byte i=1; i<100; i++) {
    byte on  = i;
    byte off = 100-on;
    for( byte a=0; a<100; a++ ) {
      digitalWrite(redPin, HIGH);
      delayMicroseconds(on);
      digitalWrite(redPin, LOW);
      delayMicroseconds(off);
    }
  }
}



void magentatored()
{
  digitalWrite(redPin, HIGH);
  digitalWrite(grnPin, LOW);

  // fade down blue
  for(byte i=1; i<100; i++) {
    byte on  = 100-i;
    byte off = i;
    for( byte a=0; a<100; a++ ) {
      digitalWrite(bluPin, HIGH);
      delayMicroseconds(on);
      digitalWrite(bluPin, LOW);
      delayMicroseconds(off);
    }
  }
}

