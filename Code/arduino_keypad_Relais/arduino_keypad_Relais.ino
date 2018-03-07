#include <Keypad.h>   // library Keypad

#define Buzzer 9    
#define LedBlue 11
#define LedRed 12
#define Relay 13

const byte ROWS = 4; 
const byte COLS = 3; 

char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
  };
byte rowPins[ROWS] = {7,6,5,4 };
byte colPins[COLS] = { 3,2,1 };

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //declaration keypad 
char pressed;
String password="1234";

int post=0,err=0 ;

void setup() {
  Serial.begin(9600);
  pinMode(LedBlue , OUTPUT);  
  pinMode(LedRed ,  OUTPUT); 
  pinMode(Relay ,   OUTPUT);
  pinMode(Buzzer ,   OUTPUT);
  delay(1000);
  Serial.print("System acces control \n");
  digitalWrite(LedRed, LOW);
}

void loop() {
  pressed=keypad.getKey();
  delay(100);
  
  if(pressed)             // IF THE KEY IS PRESSED
    { 
      Serial.print(pressed) ;
      digitalWrite(Buzzer,HIGH) ;
      delay(50) ;
      digitalWrite(Buzzer ,LOW) ; 
      if(pressed == '*') { 
           post = 0 ;
           err=0; 
           Serial.println("init position"); 
           digitalWrite(LedBlue,LOW);
           digitalWrite(Relay,LOW) ; 
           digitalWrite(LedRed,LOW) ; 
        }
      
     else if(pressed == password[post])
      {
          Serial.print("position:");
          Serial.println(post);
          post++;   
      }
     else if (pressed != password[post] ) {
          //pswdstate=false;
          post ++;
          err++ ;
          Serial.print("err++:");
          Serial.println(err);
      }

      if( post == 4 && err==0 ){
              post = 0;
              err=0 ;
              Serial.println("password accepted and relais actived");
              digitalWrite(LedBlue,HIGH); 
              digitalWrite(Relay,HIGH) ;
              
            }    
        if( post == 4 && err!=0 ){
              Serial.println("error password  and buzzer actived");
              digitalWrite(LedRed,HIGH); 
              digitalWrite(Buzzer,HIGH) ;
              
            }        
    } 
 }

 



