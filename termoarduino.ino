
///////librerias//////////////////////////////
#include <CapacitiveSensor.h>
#include <OneWire.h>
#include <DallasTemperature.h>
 
//////display pines///////////////////////////////////
int shiftClock = 5;  //module pin label SCLK
int latchClock = 6;  //module pin label RCLK
int displayOut = 7;  //module pin label DIO

///////////display variables//////////////////////////////////////
const byte numDigits = 4;
byte testDigits[numDigits] = {0};
byte* displayLocation = testDigits;
int showText = 6;
int charCount = -1150;

///////termometer variables///////////////////////////
OneWire ourWire(8); //pin lectura temperatura
DallasTemperature sensors(&ourWire); 
float t = 0;
float termometro = 0;
float temperatura = 80.00;
int flagTer = 0;  
int flagSelect = 0; 
int flagPlay = 0;  
int flagStop = 0;
long subir = 0;
long bajar = 0;
long go = 0;

//////////////////////pines botones///////////////////////////////
CapacitiveSensor menos = CapacitiveSensor(12,11);        
CapacitiveSensor ok = CapacitiveSensor(12,10);        
CapacitiveSensor mas = CapacitiveSensor(12,9);       

///////////////////////////////////////////////////////
void setup (){
 Serial.begin(9600);  
 sensors.begin(); //Se inician los sensores
 pinMode(shiftClock, OUTPUT);
 pinMode(latchClock, OUTPUT);
 pinMode(displayOut, OUTPUT);
 pinMode(2,OUTPUT);//relay
 pinMode(4,OUTPUT);//relay
 pinMode(3,OUTPUT);//speak
 digitalWrite(2,HIGH);
 digitalWrite(4,HIGH);
 digitalWrite(3,LOW);

////////////////timer code/////////////////////////////////////////

  // Timer 2 - gives us the display segment refresh interval
  TCCR2A = 0;  // reset Timer 2
  TCCR2B = 0;
  TCCR2A = bit (WGM21) ;   // configure as CTC mode
  // 16 MHz clock (62.5 nS per tick) - prescaled by 256
  // counter increments every 16 µS.
  // There are 8 segments and 4 digits to scan every 1/60th of a second
  // so we count 32 of them at 60Hz, giving a display refresh interval of 512 µS.
  #define scanRateHz 60  // tested, maximum that works is 88 using Wire library and Serial
  #define displayScanCount 1000000L / numDigits / 8 / scanRateHz / 16
  OCR2A  = displayScanCount;            // count up to 32 @ 60Hz
  // Timer 2 - interrupt on match (ie. every segment refresh interval)
  TIMSK2 = bit (OCIE2A);   // enable Timer2 Interrupt
  TCNT2 = 0;  // counter to zero
  // Reset prescalers
  GTCCR = bit (PSRASY);        // reset prescaler now
  // start Timer 2
  TCCR2B =  bit (CS21) | bit (CS22) ;  // prescaler of 256
  
} // end of setup()

void loop(){
 unsigned long currentMillis = millis();
 long start = millis();
    
///////////////////////////////////////////////////////////////
  if(flagSelect == 0){ 
    Serial.println ("temperatura"); 
    Serial.println (temperatura);
    subir = mas.capacitiveSensor(30);
    bajar = menos.capacitiveSensor(30);
    if((subir>250)&&(bajar>250)){ 
      flagTer = 1;
      flagStop = 1;
      digitalWrite(3,HIGH);
      delay(100);
      digitalWrite(3,LOW); 
    }
    subir = mas.capacitiveSensor(30);
    if(subir>250){ 
      temperatura = temperatura+1;  
      digitalWrite(3,HIGH);
      delay(100);
      digitalWrite(3,LOW); 
    }
    bajar = menos.capacitiveSensor(30);
    if(bajar>250){
      temperatura = temperatura-1;
      digitalWrite(3,HIGH);
      delay(100);
      digitalWrite(3,LOW); 
    }
    go = ok.capacitiveSensor(60);
    if(go>350){ 
      Serial.println ("gooo"); 
      flagSelect = 1; 
      digitalWrite(3,HIGH);
      delay(100);
      digitalWrite(3,LOW); 
    }
    t = temperatura;
  }

/////////////////////////////////////////////////////////////////////  
  if((flagTer==0)&&(flagSelect==1)){ 
    Serial.println ("************** entroo ter 0 select 1");
    sensors.requestTemperatures(); //Prepara el sensor para la lectura    
    termometro = (float) sensors.getTempCByIndex(0);
    go = ok.capacitiveSensor(60);
    if(temperatura > termometro){         
      Serial.println ("termometro");
      Serial.println (termometro);
      t = termometro;
      digitalWrite(2,LOW); 
      digitalWrite(4,LOW);
    }
    if(((termometro+3) > temperatura)||(go>250)){
      flagTer = 1;
      flagStop = 1;
      digitalWrite(2,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(3,HIGH);
      //go = ok.capacitiveSensor(30);
      finishSpeak();
    }
  }
    
/////////////////////////////////////////////////////////////////////
  if(flagStop==1){ 
    Serial.println ("************** entro stop");  
    sensors.requestTemperatures(); //lectura termometro
    termometro = sensors.getTempCByIndex(0);
    Serial.println ("termometro");
    Serial.println (termometro);
    t = termometro;
    go = ok.capacitiveSensor(60); 
    if(go > 350){ 
      t = 80;
      termometro = 0;
      temperatura = 80.00;
      flagTer = 0;   
      flagSelect = 0; 
      flagPlay = 0;  
      flagStop = 0;
      go = 0;
      digitalWrite(3,HIGH);
      delay(100);
      digitalWrite(3,LOW); 
    }
  }
  LED4_Print (t);
} // end of loop()

///////////////////////////////////////////////////////////
void finishSpeak(){
 delay(100);
 digitalWrite(3,LOW);
 delay(100);
 digitalWrite(3,HIGH);
 delay(100);
 digitalWrite(3,LOW);
 delay(100);
 digitalWrite(3,HIGH);
 delay(100);
 digitalWrite(3,LOW);
}

///////////////////////////////////////////////////////////
void LED4_Print (float num){
 int  val = (int) (num*100);
 byte LED2[4];
 for(int i = 3; i >= 0; i--){
   LED2[i] = val % 10;  // digits to print
   val /= 10;
 }
 LED2[1] |= 0x80;//print float point
 displayLocation = LED2;
 delay(300);
}

///////////////////////////////////////////////////////////////////
ISR (TIMER2_COMPA_vect){
 const byte NUM_PLUS_SYMBOL_FONT[] = {
   0b00111111, // 0
   0b00000110, // 1
   0b01011011, // 2
   0b01001111, // 3
   0b01100110, // 4
   0b01101101, // 5
   0b01111101, // 6
   0b00000111, // 7
   0b01111111, // 8
   0b01101111, // 9
   0b01110111, // A
   0b01111100, // b
   0b00111001, // C
   0b01011110, // d
   0b01111001, // E
   0b01110001, // F
   0b00111101, // (71)  G
   0b01110110, // (72) H
   0b00011110, // (74) J
   0b00111000, // (76) L
   0b01110011, // (80) P
   0b00111110, // (85) U
   0b00000000, // (32)  <space>
   0b01000000, // (45) -
   0b10000000  //  .   float point
  };
  static byte digit = 0;
  static byte segment = 0x80;
  byte tempDigit = displayLocation[digit];
  shiftOut(displayOut, shiftClock, MSBFIRST,  // send segment data
    ~(segment & ((NUM_PLUS_SYMBOL_FONT[tempDigit & 0x7f]) | (tempDigit & 0x80))) );   
  shiftOut(displayOut, shiftClock, MSBFIRST, 8 >> digit);  // send digit select data
  // data is now in the display shift register, so latch to LEDs
  digitalWrite(latchClock, LOW);
  digitalWrite(latchClock, HIGH);
  // increment variables to select the next segment and possibly the next digit:
  segment = segment >> 1;
  if (segment == 0){
    segment = 0x80;
    digit++;
    if (digit >= numDigits)
      digit = 0;
  }
  
}




