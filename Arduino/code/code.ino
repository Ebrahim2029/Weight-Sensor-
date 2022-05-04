#include <LiquidCrystal.h>
#include <Keypad.h>
#include "HX711.h"

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

const int LOADCELL_DOUT_PIN = A0;
const int LOADCELL_SCK_PIN = A1;
const byte rows =4;
const byte cols =4;
byte rowpins[rows] = {0,2,3,4};
byte colpins[cols] = {5,6,7};
HX711 scale;
char hexakeys[rows][cols] =
{
   {'1' , '2' ,'3' , 'A'},
   {'4' , '5' ,'6' , 'B'},
   {'7' , '8' ,'9' , 'C'},
   {'*' , '0' ,'#' , 'D'}
  
};
Keypad customKeypad = Keypad(makeKeymap(hexakeys),rowpins,colpins,rows,cols);
int led = A3;
char customKey;
int number ;
int count;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  analogWrite(led, 0);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Serial.println(scale.read_average(20));   
  scale.set_scale(2280.f);
  scale.tare();              


  Serial.println("Readings:");
}

void loop() {
  Enter_number();
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.print(scale.get_units(10), 1);

 float w = scale.get_units() * 5.15584 ;

 
                     if(w < 0 ) { w *= -1 ; }
                    if ( w < 1 )
                    {   
                       lcd.setCursor(0, 0);
                         lcd.print("Put weight .......");
                          lcd.setCursor(0, 1);
                          lcd.print("                ");
                          
  
                    }
                       else 
                   {
                    if((int)w ==number  || (int)w ==(number-1) )  
                    { lcd.setCursor(0, 0);
                        lcd.print("successful      ");
                        lcd.setCursor(0, 1);
                        lcd.print("               ");
                        
                      
                      }
                      else if (number == 1111111)
                      {
                         lcd.setCursor(0, 0);
                        lcd.print("     Weight     ");
                         
                        lcd.setCursor(0, 1);
                        lcd.print((int)w);
                         lcd.print(" g        ");

                      }
                      else{
                        lcd.setCursor(0, 0);
                        lcd.print("Weight :");
                         lcd.print((int)w);
                         lcd.print(" g    ");
                        lcd.setCursor(0, 1);
                        lcd.print("number : ");
                         lcd.print(number);
                         lcd.print(" g");
                         
                      }
   
                    }
                       Serial.print("\t| Weight :\t");
                       Serial.println(w);

  

   scale.power_down();  
  delay(500);
  scale.power_up();

}

void Enter_number()
{
   
  while (number == 0) 

{
  Serial.println("Press # To Enter"); 
  lcd.setCursor(0, 0);
  lcd.print("Press #To Number");
  lcd.setCursor(0, 1);
  lcd.print("Press *To Weight");

  char userinput[4];

customKey = customKeypad.waitForKey();
if(customKey == '*')
{ 
  number = 1111111 ;
}
if(customKey == '#')
{                   lcd.clear();
                    Serial.print(customKey);
                   Serial.print(": >");
                     lcd.setCursor(0, 0);
                     lcd.print(customKey);
                     lcd.print(": >");
                     
                  for ( count = 0; count < 4; count++)
                 {
                       customKey = customKeypad.waitForKey(); 
                       if(customKey =='*') break;
                        userinput[count] =  customKey;
                         Serial.print( customKey );
                          lcd.print(customKey);
                 }
                 for (int count1 = 0; count1 < count; count1++)
                   {         
                      if(count1 == 0 )
                         { number = ( (int) userinput[count1] - 48 ) ;  }
            
                      else
                        {  number =(  (number*10) + ( (int) userinput[count1] - 48 )) ;  }

                   }
  }
  
  

}

}
