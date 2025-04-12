/*
  Can measure voltage from 0 to 20V
  r1 -> 20K
  r2 -> 
*/

#include <LiquidCrystal.h>
#include <stdio.h>

LiquidCrystal lcd(6, 7, 5, 4, 3, 2);
unsigned char gchr='x',gchr1='x';
 char rcv,count;
 //char pastnumber[11]="";
 


int sti=0;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

float voltage1=0,current1=0;
float voltage2=0,current2=0;

int current11=0,current22=0;

int rtr1=0;


int relay1       = 8;
int relay2       = 9;

int sts1=0,sts2=0;


void okcheck()
{
  unsigned char rcr;
  do{
      rcr = Serial.read();
    }while(rcr != 'K');
}


void setup() 
{
  // initialize serial:
  Serial.begin(9600);serialEvent();


 pinMode(relay1, OUTPUT); pinMode(relay2, OUTPUT);

digitalWrite(relay1, LOW);digitalWrite(relay2, LOW);
 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Solar Charger");
  lcd.setCursor(0,1);
  lcd.print("Using Arduino");
    delay(2500);
  
  //wifiinit();
  
  lcd.clear();
  
    lcd.setCursor(0, 0);   //column,row
    lcd.print("V:");        //2,0
  //  lcd.setCursor(0, 1);   //column,row
    //lcd.print("C:");        //8,0
    
    
}

void loop() 
{
   voltage1 = analogRead(A0);
   voltage1 = (voltage1 * (5.0/1023.0));
   voltage1 = (voltage1 * 5.54); 
   lcd.setCursor(3,0);
   //convertl(voltage);
   lcd.print(voltage1);lcd.write("   ");   
   //lcd.setCursor(8, 0);   //column,row
    //lcd.print("SC:");        //8,0
     
       delay(200);
}
 

void serialEvent() 
{
  while (Serial.available()) 
        {
         char inChar = (char)Serial.read();
           //sti++;
           //inputString += inChar;
          if(inChar == '*')
            {sti=1;
              inputString += inChar;
             //  stringComplete = true;
             // gchr = inputString[sti-1] 
            }
          if(sti == 1)
            {
                inputString += inChar;
            }
          if(inChar == '#')
            {sti=0;
              gchr = inputString[2];
              stringComplete = true;      
            }        
        }
}


/*
  Read input serial
 */
int readSerial(char result[]) 
{
  int i = 0;
  while (1) 
  {
    while (Serial.available() > 0) 
    {
      char inChar = Serial.read();
      if (inChar == '\n') 
         {
          result[i] = '\0';
          Serial.flush();
          return 0;
         }
      if (inChar != '\r') 
         {
          result[i] = inChar;
          i++;
         }
    }
  }
}






void converts(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   Serial.write(a);
   Serial.write(c);
   Serial.write(e); 
   Serial.write(g);
   Serial.write(h);
}

void convertl(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
  // lcd.write(a);
  // lcd.write(c);
   lcd.write(e); 
   lcd.write(g);
   lcd.write(h);
}
void convertl1(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
  // lcd.write(a);
  // lcd.write(c);
  // lcd.write(e); 
   lcd.write(g);
   lcd.write(h);
}



/*
   sensorValue = analogRead(analogInPin);
   sensorValue = (sensorValue/9.31);
   lcd.setCursor(1,1); //rc
   lcd.print(sensorValue);
   Serial.print(sensorValue);
 */
