#include <TM1637.h>
#include <ChainableLED.h>

#define DISPLATPIN 2
#define CLK 2           //pins definitions for TM1637 in .h    
#define DIO 3
#define NUM_LEDS 5
#define MOPIN_A 5
#define MOPIN_B 6
#define LEDPIN_A 7
#define LEDPIN_B 8
#define fsr_pin_A A0
#define fsr_pin_B A1

int Counter=0;
int8_t ListDisp[4]={0,0,0,0};
int i=0;
boolean TrapA = false;
boolean TrapB = false;
long tmp = 0;
int fsr_value_A = 0;
int fsr_value_B = 0; 

TM1637 tm1637(CLK,DIO);  //set led display clk
ChainableLED leds(LEDPIN_A, LEDPIN_B, NUM_LEDS);//init RGB led

void setup() {
  tm1637.init();
  tm1637.set(BRIGHT_TYPICAL);//BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
  
  leds.init();
  
  pinMode(MOPIN_A, OUTPUT);
  pinMode(MOPIN_B, OUTPUT);
}

void loop() {
  
   fsr_value_A = analogRead(fsr_pin_A); // get value from FSR A
   fsr_value_B = analogRead(fsr_pin_B); // get value from FSR B
   
   leds.setColorRGB(i, 0, 0, 0); 
   
   if(fsr_value_A>800){// 0~1023
     TrapA = true;
     leds.setColorRGB(i, 255, 0, 0);  
     
     digitalWrite(MOPIN_A, HIGH); 
     delay(100); 
     digitalWrite(MOPIN_A, LOW); 
   }
   
   if(fsr_value_B>800){// 0~1023
     TrapB = true;
     leds.setColorRGB(i, 0, 0, 255);  
     
     digitalWrite(MOPIN_B, HIGH); 
     delay(100); 
     digitalWrite(MOPIN_B, LOW); 
   }
   
  if(TrapA && TrapB){
    
    (Counter==9999)?Counter=0:Counter++; //set limit
    
    tmp = Counter;
    
    for(int i=0;i<4;i++){ //get number from counter
      ListDisp[i]=tmp%10;
      tmp=tmp/10;
    }
                
    tm1637.display(3,ListDisp[0]); //set led display
    tm1637.display(2,ListDisp[1]); 
    tm1637.display(1,ListDisp[2]);
    tm1637.display(0,ListDisp[3]);
    
     TrapA = false; //clean flag
     TrapB = false;
  }
  

}
