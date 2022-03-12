
#include <SPI.h>                //http://arduino.cc/en/Reference/SPI
#include <Thermocouple.h>       //http://github.com/JChristensen/Thermocouple
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // Library for I2C LCD
#include "Wire.h"

#include "I2CKeyPad.h"
const uint8_t KEYPAD_ADDRESS = 0x38;
I2CKeyPad keyPad(KEYPAD_ADDRESS);
char keymap[19] = "147*2580369#ABCDNF";  // N = NoKey, F = Fail
int32_t sum = 0;
int32_t val = 0;
int setting =0;
String TYPE= "BACON & SMOKIES ";
int OTemp = 107;   // default smoker temp Celcius
int MTemp = 54;   //  default Meat temp  Celcius
float CTime = 3; // hrs 
float Time = 0;
float NTime = 0;
float tmp0=0;
int Number =0;

//MAX6675 SPI pin definitions
#define csTC1  D8                //chip select for MAX6675 #1
#define csTC2 D4                 //chip select for MAX6675 #2
int SSRPin = D0;
LiquidCrystal_I2C lcd(0x27, 16, 2); 
//Additionally, connect the MAX6675s as follows:
//MISO  Arduino pin 12   //D7       //master in slave out
//SCK   Arduino pin 13  //D5        //serial clock  

Thermocouple tc1 = Thermocouple(csTC1);    //instantiate the thermocouple objects
Thermocouple tc2 = Thermocouple(csTC2);

void setup() {
    Serial.begin(115200);       //initialize Serial
    lcd.init();
    lcd.backlight();
    lcd.begin(16, 2);
    lcd.clear();  
    lcd.setCursor(0,0); 
    lcd.print("   THE SMOKER   ") ;
    lcd.setCursor(0,1); 
    lcd.print("  BY KRYWENKO  ") ;
    Wire.begin();
    Wire.setClock(400000);
    pinMode(SSRPin, OUTPUT);
  if (keyPad.begin() == false){
    Serial.println("\nERROR: cannot communicate to keypad.\nPlease reboot.\n");
    while (1);
  }

  keyPad.loadKeyMap(keymap); 
  analogWrite(SSRPin, 0);      
 delay(3000);
}

void loop() {
     int HRS;
     float MIN;
      
     HRS = CTime;
     MIN = (CTime - HRS)*60 ;    
      lcd.setCursor(0,1);
      lcd.print(TYPE);
      delay(2000);
      lcd.setCursor(0,1);
      lcd.print("OVEN TEMP ");lcd.print(OTemp); lcd.print("\337C "); //lcd.write(B11011111);
      delay(2000);
      lcd.setCursor(0,1);
      lcd.print("MEAT TEMP ");lcd.print(MTemp); lcd.print("\337C "); //lcd.write(B11011111);
      delay(2000);
      lcd.setCursor(0,1);
      lcd.print("COOKTIME ");lcd.print(HRS); lcd.print("h"); ;lcd.print(MIN, 0); lcd.print("m   ");//lcd.write(B11011111);
       ///works
       delay(2000); 
      lcd.clear();
      lcd.setCursor(0,0);
      //lcd.autoscroll();
      lcd.print("MEAT SELECTION "); 
      delay(1000);
      lcd.setCursor(0,1);
      lcd.print("A BEEF         ");
      delay(2000);
      lcd.setCursor(0,1);
      lcd.print("B PORK         ");
      delay(2000);
      lcd.setCursor(0,1);
      lcd.print("C POULTRY       ");
      delay(2000);
      lcd.setCursor(0,1);
      lcd.print("D FISH          ");
            delay(2000);
      lcd.setCursor(0,1);
      lcd.print("* MANUALLY SET  ");
      delay(2000);
      lcd.setCursor(0,1);
      lcd.print("# START SMOKER  ");
      delay(2000);
      lcd.setCursor(0,0);
      lcd.print("                        SELECT NOW      ");
     
      
        for (int positionCounter = 0; positionCounter < 24; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(200);
  }
  lcd.clear();
  lcd.print("SELECT NOW ");
  delay(1000);

if (keyPad.isPressed())
  {
    char ch = keyPad.getChar();
    switch (ch)
    {
      case 'A' :
        setting=1;
        Serial.print(ch);
          while (setting == 1) {
         Beef();
           }
        break;
      case 'B':
        setting=1;
        Serial.print(ch);
          while (setting == 1) {
         Pork();
          }
        break;
      case 'C' :
        setting=1;
        Serial.print(ch);
          while (setting == 1) {
         Poultry();
          }
        break;
       case 'D' :
        setting=1;
        Serial.print(ch);
          while (setting == 1) {
         Fish();
           }
        break;
      case '*':
        setting=1;
        Serial.print(ch);
          while (setting == 1) {
         Matrix();
          }
        break;
      case '#' :
        setting=1;
        Serial.print(ch);
          while (setting == 1) {
         Smoke();
          }
        break;
    }
  }
  

 delay(300);   
}

void Beef(){
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("BEEF-SELLECT ");
   lcd.setCursor(0,1);
   lcd.print("1 BRISKET       ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("2 CHUCK         ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("3 BACK RIB      ");
   delay(2000);  
   lcd.setCursor(0,1);
   lcd.print("4 SHORT RIB     ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("5 COUNTRY RIB   ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("6 FATTIES/LOAFs ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("7 STEAKS        ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("8 PRIME ROAST   ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("9 TRI TIP       ");
   delay(2000); 
     
  if (keyPad.isPressed())
  {
    char ch = keyPad.getChar();
    switch (ch)
    {
      case '1' :
              TYPE = "   BRISKET " ;
              OTemp = 107;
              MTemp = 78;
              CTime  = 16;
               while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("BRISKET-TEMP");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED-DARK   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D DARK       ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     MTemp = 63;
                      BrisketT();
                     break;
                  case 'B' :
                     MTemp = 71;
                     BrisketT();
                     break;
                 case 'C' :
                    MTemp = 85;
                    BrisketT();
                     break; 
                  case 'D' :
                     MTemp = 93;
                     BrisketT();
                   break;
                                         
                  case '*':
                     BrisketT();
                    break;

                 }
                }
               }
        break;
        
      case '2' :
              TYPE = "   CHUCK " ;
              OTemp = 107;
              MTemp = 78;
              CTime  = 9;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("CHUCK-SMOKE ");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED-DARK   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D DARK       ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     MTemp = 63;
                      CHUCKT();
                     break;
                  case 'B' :
                     MTemp = 71;
                     CHUCKT();
                     break;
                 case 'C' :
                    MTemp = 85;
                    CHUCKT();
                     break; 
                  case 'D' :
                     MTemp = 93;
                     CHUCKT();
                   break;
                                         
                  case '*':
                     CHUCKT();
                    break;

                 }
                }
               }


        break;
        
      case '3' :
       
        TYPE = "BACK RIB " ;
              OTemp = 107;
              MTemp = 78;
              CTime  = 4.5;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("BACK RIB TEMP");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED-DARK   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D DARK       ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     MTemp = 63;
                      BRT();
                     break;
                  case 'B' :
                     MTemp = 71;
                     BRT();
                     break;
                 case 'C' :
                    MTemp = 85;
                    BRT();
                     break; 
                  case 'D' :
                     MTemp = 93;
                     BRT();
                   break;
                                         
                  case '*':
                     BRT();
                    break;

                 }
                }
               }



        break;
        
      case '4' :
        //lcd.print(ch);lcd.print(" SHORT RIB");
        TYPE = "SHORT RIB " ;
              OTemp = 107;
              MTemp = 78;
              CTime  = 3.5;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("SHORT RIB TEMP");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED-DARK   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D DARK       ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     MTemp = 63;
                      SRT();
                     break;
                  case 'B' :
                     MTemp = 71;
                     BRT();
                     break;
                 case 'C' :
                    MTemp = 85;
                    BRT();
                     break; 
                  case 'D' :
                     MTemp = 93;
                     BRT();
                   break;
                                         
                  case '*':
                     BRT();
                    break;

                 }
                }
               }

        
        break;
        
      case '5' :
        //lcd.print(ch);lcd.print(" COUNTRY RIB");
              TYPE = "COUNTRY RIB " ;
              OTemp = 107;
              MTemp = 76;
              CTime  = 3.5;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("SHORT RIB TEMP");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED-DARK   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D DARK       ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     MTemp = 63;
                      CRT();
                     break;
                  case 'B' :
                     MTemp = 69;
                     CRT();
                     break;
                 case 'C' :
                    MTemp = 82;
                    CRT();
                     break; 
                  case 'D' :
                     MTemp = 88;
                     CRT();
                   break;
                                         
                  case '*':
                     CRT();
                    break;

                 }
                }
               }

        

        break;
        
      case '6' :
      
         TYPE = "FATTIES/LOAFs " ;
              OTemp = 107;
              MTemp = 71;
              CTime  = 3;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("FATTIES/LOAFs");
              lcd.setCursor(0,1);
              lcd.print("A MEATLOAF    ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B FATTIES  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C BURGERS   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D BACON WRAP  ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime = 3;
                     setting=0; 
                     break;
                  case 'B' :
                     CTime = 3;
                     setting=0;
                     break;
                 case 'C' :
                    CTime = 1;
                   setting=0;
                     break; 
                  case 'D' :
                     CTime = 3;
                     setting=0;
                   break;
                                         
                  case '*':
                     setting=0;
                    break;

                 }
                }
               }

        
        

        break;
        
      case '7' :
        
              TYPE = "STEAKS " ;
              OTemp = 107;
              MTemp = 63;
              CTime  = 1;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("STEAK SMOKE  ");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MEDIUM    ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D MED- STRONG  ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-STRONG");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     MTemp = 54;
                      STRT();
                     break;
                  case 'B' :
                     MTemp = 55;
                     STRT();
                     break;
                 case 'C' :
                    MTemp = 57;
                    STRT();
                     break; 
                  case 'D' :
                     MTemp = 59;
                     STRT();
                   break;
                                         
                  case '*':
                     STRT();
                    break;

                 }
                }
               }

        
        
        break;
        
      case '8' :
        
              TYPE = "PRIME ROAST " ;
              OTemp = 107;
              MTemp = 71;
              CTime  = 4.5;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("PRIME ROAST TEMP");
              lcd.setCursor(0,1);
              lcd.print("A RARE      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-RARE  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MEDIUM    ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D MED- WELL  ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-WELL");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     MTemp = 52;
                      PRT();
                     break;
                  case 'B' :
                     MTemp = 57;
                     PRT();
                     break;
                 case 'C' :
                    MTemp = 62;
                    PRT();
                     break; 
                  case 'D' :
                     MTemp = 67;
                     PRT();
                   break;
                                         
                  case '*':
                     PRT();
                    break;

                 }
                }
               }

        
        break;
        
      case '9' :
        lcd.print(ch);lcd.print(" TRI TIP");
        
              TYPE = "TRI TIP " ;
              OTemp = 107;
              MTemp = 71;
              CTime  = 2;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("TRI TIP TEMP");
              lcd.setCursor(0,1);
              lcd.print("A RARE      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-RARE  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MEDIUM    ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D MED- WELL  ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-WELL");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     MTemp = 52;
                      
                     break;
                  case 'B' :
                     MTemp = 57;
                     
                     break;
                 case 'C' :
                    MTemp = 62;
                    
                     break; 
                  case 'D' :
                     MTemp = 67;
                     
                   break;
                                         
                  case '*':
                     PRT();
                    break;

                 }
                }
               }

        
        
        break;
          
        case '*':
        Serial.print("11 ");
        lcd.setCursor(0,0);
        lcd.print("SAVING   ");
        setting =0;
        
        Serial.println(ch);
        delay(1000);
        break;   
    }
  }
  
}

void Poultry(){
  lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("POULTRY-SELLECT");
   lcd.setCursor(0,1);
   lcd.print("1 WHOLE CHICKEN ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("2 CHICKEN PARTS ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("3 WHOLE TURKEY  ");
   delay(2000);  
   lcd.setCursor(0,1);
   lcd.print("4 TURKEY PARTS  ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("5 QUAIL/PHEASANT");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("6 CORNISH HEN  ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("7 DUCK");
   delay(2000);

     
  if (keyPad.isPressed())
  {
    char ch = keyPad.getChar();
    switch (ch)
    {
      case '1' :
              TYPE = "WHOLE CHICKEN " ;
              OTemp = 121;
              MTemp = 74;
              CTime  = 3.5;
               while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("WHOLE CHICKEN");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED-DARK   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D DARK       ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime = 3;
                     setting =0;
                     break;
                  case 'B' :
                     CTime = 3.25;
                     setting =0;
                     break;
                 case 'C' :
                    CTime = 3.75;
                    setting =0;
                     break; 
                  case 'D' :
                     CTime = 4;
                     setting =0;
                   break;
                                         
                  case '*':
                     setting =0;
                    break;

                 }
                }
               }
        break;
        
      case '2' :
              TYPE = "CHICKEN PARTS" ;
              OTemp = 121;
              MTemp = 77;
              CTime  = 2;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("CHICKEN PARTS ");
              lcd.setCursor(0,1);
              lcd.print("A 1/4 CHICKEN ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B 1/2 CHICKEN ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C THIGHS    ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D WINGS     ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MISC");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime = 2;
                      setting =0;
                     break;
                  case 'B' :
                     CTime = 2;
                     setting =0;
                     break;
                 case 'C' :
                    CTime = 2;
                    setting =0;
                     break; 
                  case 'D' :
                     CTime = 2;
                     setting =0;
                   break;
                                         
                  case '*':
                     setting =0;
                    break;

                 }
                }
               }


        break;
        
      case '3' :
       
        TYPE = "WHOLE TURKEY" ;
              OTemp = 116;
              MTemp = 74;
              CTime  = 6;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("WHOLE TURKEY");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED-DARK   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D DARK       ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime = 5;
                      setting =0;
                     break;
                  case 'B' :
                     CTime = 5.5;
                     setting =0;
                     break;
                 case 'C' :
                    CTime = 6.6;
                    setting =0;
                     break; 
                  case 'D' :
                     CTime = 7;
                     setting =0;
                   break;
                                         
                  case '*':
                     setting =0;
                    break;

                 }
                }
               }



        break;
        
      case '4' :
        //lcd.print(ch);lcd.print(" SHORT RIB");
        TYPE = "TURKEY PARTS" ;
              OTemp = 116;
              MTemp = 74;
              CTime  = 4;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("TURKEY PARTS");
              lcd.setCursor(0,1);
              lcd.print("A LARGE BREASTS");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B SMALL BREAST ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C LARGE LEGS ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D SMALL LEGS ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime = 4;
                     setting =0;
                     break;
                  case 'B' :
                     CTime = 3;
                     setting =0;
                     break;
                 case 'C' :
                    CTime = 3;
                    setting =0;
                     break; 
                  case 'D' :
                     CTime = 4;
                     setting =0;
                   break;
                                         
                  case '*':
                     setting =0;
                    break;

                 }
                }
               }

        
        break;
        
      case '5' :
        //lcd.print(ch);lcd.print(" COUNTRY RIB");
              TYPE = "QUAIL/PHEASANT" ;
              OTemp = 107;
              MTemp = 74;
              CTime  = 1;
              setting =0;
        break;
        
      case '6' :
        
         TYPE = "CORNISH HEN" ;
              OTemp = 116;
              MTemp = 74;
              CTime  = 2;
              setting =0;
        break;
        
      case '7' :
        
              TYPE = "DUCK" ;
              OTemp = 121;
              MTemp = 74;
              CTime  = 5;
                
        break;
                 
        case '*':
        Serial.print("11 ");
        lcd.setCursor(0,0);
        lcd.print("SAVING   ");
        setting =0;
        
        Serial.println(ch);
        delay(1000);
        break;   
    }
  }
  
}
void Fish(){

 lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("FISH-SELLECT ");
   lcd.setCursor(0,1);
   lcd.print("1 SALMON       ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("2 TILPIA         ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("3 TROUT      ");
   delay(2000);  
   lcd.setCursor(0,1);
   lcd.print("4 LOBSTER     ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("5 OYSTER   ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("6 SCALLOPS ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("7 SHRIMP   ");
   delay(2000);
   
     
  if (keyPad.isPressed())
  {
    char ch = keyPad.getChar();
    switch (ch)
    {
      case '1' :
              TYPE = "SALMON " ;
              OTemp = 104;
              MTemp = 63;
              CTime  = 1;
             setting =0;
        break;
        
      case '2' :
              TYPE = "TILAPIA " ;
              OTemp = 104;
              MTemp = 63;
              CTime  = 1;
              setting =0;
        break;
        
      case '3' :
       
        TYPE = "TROUT " ;
              OTemp = 107;
              MTemp = 63;
              CTime  = 1;
              setting =0;

        break;
        
      case '4' :
        
        TYPE = "LOBSTER " ;
              OTemp = 107;
              MTemp = 63;
              CTime  = 0.75;
              setting =0;
        break;
        
      case '5' :
       
              TYPE = "OYSTER " ;
              OTemp = 107;
              MTemp = 63;
              CTime  = 0.5;
              setting =0;

        break;
        
      case '6' :
      
         TYPE = "SCALLOPS " ;
              OTemp = 107;
              MTemp = 63;
              CTime  = 0.75;
              setting =0;

        break;
        
      case '7' :
        
              TYPE = "SHRIMP " ;
              OTemp = 107;
              MTemp = 63;
              CTime  = 0.5;
              setting =0;
        break;
               
        case '*':
        Serial.print("11 ");
        lcd.setCursor(0,0);
        lcd.print("SAVING   ");
        setting =0;
        
        Serial.println(ch);
        delay(1000);
        break;   
    }
  }
   
}
void Pork(){
  lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("PORK-SELLECT ");
   lcd.setCursor(0,1);
   lcd.print("1 BUTT       ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("2 BABYBACK RIBS");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("3 SPARE RIB    ");
   delay(2000);  
   lcd.setCursor(0,1);
   lcd.print("4 LOINS        ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("5 TENDERLOINS  ");
   delay(2000);
   lcd.setCursor(0,1);
   lcd.print("6 PORKBELLY    ");
   delay(2000);
   
     
  if (keyPad.isPressed())
  {
    char ch = keyPad.getChar();
    switch (ch)
    {
      case '1' :
              TYPE = "   BUTT    " ;
              OTemp = 107;
              MTemp = 78;
              CTime  = 13;
               while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("BUTT-TEMP");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED-DARK   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D DARK       ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     MTemp = 63;
                      BUTTT();
                     break;
                  case 'B' :
                     MTemp = 71;
                     BUTTT();
                     break;
                 case 'C' :
                    MTemp = 85;
                    BUTTT();
                     break; 
                  case 'D' :
                     MTemp = 93;
                     BUTTT();
                   break;
                                         
                  case '*':
                     BUTTT();
                    break;

                 }
                }
               }
        break;
        
      case '2' :
              TYPE = "BABYBACK RIBS" ;
              OTemp = 107;
              MTemp = 78;
              CTime  = 5;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("BABYBACK SMOKE");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED-DARK   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D DARK       ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     MTemp = 63;
                      setting=0;
                     break;
                  case 'B' :
                     MTemp = 71;
                     setting=0;
                     break;
                 case 'C' :
                    MTemp = 85;
                    setting=0;
                     break; 
                  case 'D' :
                     MTemp = 93;
                     setting=0;
                   break;
                                         
                  case '*':
                     setting=0;
                    break;

                 }
                }
               }


        break;
        
      case '3' :
       
        TYPE = "SPARE RIB " ;
              OTemp = 107;
              MTemp = 78;
              CTime  = 6;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("SPARE RIB TEMP");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED-DARK   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D DARK       ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     MTemp = 63;
                     setting=0;
                     break;
                  case 'B' :
                     MTemp = 71;
                     setting=0;
                     break;
                 case 'C' :
                    MTemp = 85;
                    setting=0;
                     break; 
                  case 'D' :
                     MTemp = 93;
                     setting=0;
                   break;
                                         
                  case '*':
                     setting=0;
                    break;

                 }
                }
               }



        break;
        
      case '4' :
        //lcd.print(ch);lcd.print(" SHORT RIB");
        TYPE = "LOIN     " ;
              OTemp = 107;
              MTemp = 70;
              CTime  = 4;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("LOIN SMOKE   ");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED-DARK   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D DARK       ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime = 3;
                     setting=0;
                     break;
                  case 'B' :
                     CTime = 3.5;
                     setting=0;
                     break;
                 case 'C' :
                    CTime = 4.5;
                    setting=0;
                     break; 
                  case 'D' :
                     CTime = 5;
                     setting=0;
                   break;
                                         
                  case '*':
                     setting=0;
                    break;

                 }
                }
               }

        
        break;
        
      case '5' :
        //lcd.print(ch);lcd.print(" COUNTRY RIB");
              TYPE = "TENDERLOIN " ;
              OTemp = 107;
              MTemp = 70;
              CTime  = 2;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("TENDERLOIN SMOKE");
              lcd.setCursor(0,1);
              lcd.print("A LIGHT      ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED-LIGHT  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED-DARK   ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D DARK       ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-MED");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime = 1;
                      setting=0;
                     break;
                  case 'B' :
                     CTime = 1.5;
                     setting=0;
                     break;
                 case 'C' :
                    CTime = 2.5;
                    setting=0;
                     break; 
                  case 'D' :
                     CTime = 3;
                     setting=0;
                   break;
                                         
                  case '*':
                     setting=0;
                    break;

                 }
                }
               }

        

        break;
        
      case '6' :
       
         TYPE = "PORKBELLIES " ;
              OTemp = 107;
              MTemp = 71;
              CTime  = 6;
      while (setting == 1) {
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("PORKBELLIES");
              lcd.setCursor(0,1);
              lcd.print("A SOFT ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MED SOFT ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C MED CRISPY");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D CRISPY   ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* LIGHT CRISP");
              delay(2000);
              
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     MTemp = 63;
                     setting=0; 
                     break;
                  case 'B' :
                     MTemp = 71;
                     setting=0;
                     break;
                 case 'C' :
                    MTemp = 85;
                   setting=0;
                     break; 
                  case 'D' :
                     MTemp = 93;
                     setting=0;
                   break;
                                         
                  case '*':
                     setting=0;
                    break;

                 }
                }
               }
   
        break;
          
        case '*':
        Serial.print("11 ");
        lcd.setCursor(0,0);
        lcd.print("SAVING   ");
        setting =0;
        
        Serial.println(ch);
        delay(1000);
        break;   
    }
  }
  
}
void Smoke(){
      PreHeat();
      while (setting ==1 ){
      int HRS;
     float MIN;
    delay(300); 
    lcd.clear();                     // The following 17 lines set up the LCD display to indicate the Set & Actual temperatures
    lcd.setCursor(0, 0);
     NTime = CTime - (Time/120);
     HRS = NTime;
     MIN = (NTime - HRS)*60 ;
     
    
    lcd.print("OVEN ");
  
    Serial.print("tc1: ");
    displayTemp(tc1.readC()); //read the 1st TC and print the temperature
    if ( OTemp > tc1.readC()) { Serial.println("ON"); analogWrite(SSRPin, 100); } else {Serial.println("Off"); analogWrite(SSRPin, 0);}
    lcd.print(HRS);lcd.print("h");lcd.print(MIN, 0);
  lcd.print("m");
  Serial.print(NTime);
    Serial.print("tc2: ");
    lcd.setCursor(0, 1);
    lcd.print("MEAT ");
    displayTemp(tc2.readC());  //read the 2nd TC and print the temperature
    if ( MTemp > tc2.readC()) { Serial.println("ON"); } else { Serial.println("Off"); analogWrite(SSRPin, 0); } 
    if ( NTime == 0 ) { STOP();}
    static uint32_t oldtime=millis();

    if ( (millis()-oldtime) > 30000) {
       oldtime = millis();
       Time++;
    lcd.clear();                     // The following 17 lines set up the LCD display to indicate the Set & Actual temperatures
    lcd.setCursor(0, 0);   
    lcd.print(TYPE );
    lcd.setCursor(0, 1);
    lcd.print("OVEN SET @ "); lcd.print(OTemp );lcd.print("\337C ");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("MEAT SET @ "); lcd.print(MTemp );lcd.print("\337C ");
    delay(2000);
    lcd.setCursor(0, 1);
    lcd.print("TIME SET @ "); lcd.print(CTime, 1 );lcd.print("HRS ");
    delay(2000);
    }
    Serial.println();



        if (keyPad.isPressed()){
    int key = keyPad.getLastKey();
    Serial.println(key);
    if ( key == 16){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("STOPPING  ");
      setting =0;
      delay(1000);
    }}
    delay(1000);
}
}

void Matrix(){
 Serial.println("Setting");
  lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("MANUAL       ");
              lcd.setCursor(0,1);
              lcd.print("A OVEN TEMP  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B MEAT TEMP  ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C TIME       ");
              delay(2000); 
              //lcd.setCursor(0,1);
              //lcd.print("D NA   ");
             // delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* ENTER      ");
              delay(2000);
if (keyPad.isPressed())
  {
    char ch = keyPad.getChar();
    Serial.println (ch);
    switch (ch)
    {
      case 'A' :
         lcd.setCursor(0,1);lcd.print("OVEN TEMP        ");
   lcd.setCursor(0,1); lcd.print(tmp0);   Number = 1;
      while ( Number ==1){
        NUMBER();
      }
       OTemp=tmp0;
        break;
      case 'B':
      lcd.setCursor(0,1);lcd.print("MEAT TEMP        ");
      Number = 1;
      while ( Number ==1){
        NUMBER();
      }
       MTemp=tmp0;
        break;
      case 'C' :
      lcd.setCursor(0,1);lcd.print("COOK TIME - MIN  ");
      Number = 1;
      while ( Number ==1){
        NUMBER();
      }
       CTime=tmp0/60;
        break;

        case '*' :
        TYPE = " MANUAL    " ;
        setting = 0;
        break;
    }
  }
}
void displayTemp(float fTemp) {
    if (fTemp < 0.0) {
        Serial.println("Open thermocouple circuit");
    }
    else {
        Serial.println(fTemp, 0);
        //Serial.println("\260F");    //octal 260 = degree symbol
        
        lcd.print(fTemp, 0);lcd.print("\337C "); 

    }
}
void BrisketT(){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("BRISKET-TIME ");
              

               while (setting == 1) {
              lcd.setCursor(0,1);
              lcd.print("A 12 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B 14 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C 18 HRS     ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D 20 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-16");
              delay(2000);
                
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime= 12;
                     setting = 0;
                     break;
                  case 'B' :
                     CTime= 14;
                     setting = 0;
                     break;
                 case 'C' :
                     CTime= 18;
                     setting = 0;
                     break; 
                  case 'D' :
                     CTime= 20;
                     setting = 0;
                   break;
                                         
                  case '*':
                     CTime= 16;
                   
                    lcd.print("SAVING   ");
                    setting =0;
        
                   Serial.println(ch1);
                   delay(1000);
                    break;

                 }
                }
               }

  
}

void CHUCKT(){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("CHUCK-TIME ");
              

               while (setting == 1) {
              lcd.setCursor(0,1);
              lcd.print("A 8 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B 8.5 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C 9.5 HRS     ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D 10 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-9");
              delay(2000);
                
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime= 8;
                     setting = 0;
                     break;
                  case 'B' :
                     CTime= 8.5;
                     setting = 0;
                     break;
                 case 'C' :
                     CTime= 9.5;
                     setting = 0;
                     break; 
                  case 'D' :
                     CTime= 10;
                     setting = 0;
                   break;
                                         
                  case '*':
                     CTime= 9;
                   
                    lcd.print("SAVING   ");
                    setting =0;
        
                   Serial.println(ch1);
                   delay(1000);
                    break;

                 }
                }
               }

  
}
void BRT(){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("BACK RIB-TIME ");
              

               while (setting == 1) {
              lcd.setCursor(0,1);
              lcd.print("A 4 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B 4.25 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C 4.75 HRS     ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D 5 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-4.5");
              delay(2000);
                
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime= 4;
                     setting = 0;
                     break;
                  case 'B' :
                     CTime= 4.25;
                     setting = 0;
                     break;
                 case 'C' :
                     CTime= 4.75;
                     setting = 0;
                     break; 
                  case 'D' :
                     CTime= 5;
                     setting = 0;
                   break;
                                         
                  case '*':
                     CTime= 4.5;
                   
                    lcd.print("SAVING   ");
                    setting =0;
        
                   Serial.println(ch1);
                   delay(1000);
                    break;

                 }
                }
               }

  
}

void SRT(){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("SHORT RIB-TIME");
              

               while (setting == 1) {
              lcd.setCursor(0,1);
              lcd.print("A 3 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B 3.25 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C 3.75 hrs     ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D 4 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT- 3.5");
              delay(2000);
                
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime= 3;
                     setting = 0;
                     break;
                  case 'B' :
                     CTime= 3.25;
                     setting = 0;
                     break;
                 case 'C' :
                     CTime= 3.75;
                     setting = 0;
                     break; 
                  case 'D' :
                     CTime= 4;
                     setting = 0;
                   break;
                                         
                  case '*':
                     CTime= 3.5;
                   
                    lcd.print("SAVING   ");
                    setting =0;
        
                   Serial.println(ch1);
                   delay(1000);
                    break;

                 }
                }
               }

  
}

void CRT(){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("COUNTRY RIB-T");
              

               while (setting == 1) {
              lcd.setCursor(0,1);
              lcd.print("A 3 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B 3.25 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C 3.75 HRS     ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D 4 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-3.5");
              delay(2000);
                
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime= 3;
                     setting = 0;
                     break;
                  case 'B' :
                     CTime= 3.25;
                     setting = 0;
                     break;
                 case 'C' :
                     CTime= 3.75;
                     setting = 0;
                     break; 
                  case 'D' :
                     CTime= 4;
                     setting = 0;
                   break;
                                         
                  case '*':
                     CTime= 3.5;
                   
                    lcd.print("SAVING   ");
                    setting =0;
        
                   Serial.println(ch1);
                   delay(1000);
                    break;

                 }
                }
               }

  
}

void STRT(){

              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("STEAK-TIME");

               while (setting == 1) {
              lcd.setCursor(0,1);
              lcd.print("A 45 MINUTES   ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B 48 MINUTES   ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C 52 MINUTES  ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D 55 MINUTES ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-60");
              delay(2000);
                
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime= .75;
                     setting = 0;
                     break;
                  case 'B' :
                     CTime= .8;
                     setting = 0;
                     break;
                 case 'C' :
                     CTime= .88;
                     setting = 0;
                     break; 
                  case 'D' :
                     CTime= .92;
                     setting = 0;
                   break;
                                         
                  case '*':
                     CTime= 1;
                   
                    lcd.print("SAVING   ");
                    setting =0;
        
                   Serial.println(ch1);
                   delay(1000);
                    break;

                 }
                }
               }

  
}

void PRT(){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("PRIME ROAST-TIME");
              

               while (setting == 1) {
              lcd.setCursor(0,1);
              lcd.print("A 4 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B 4.25 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C 4.75 HRS     ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D 5 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-4.5");
              delay(2000);
                
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime= 4;
                     setting = 0;
                     break;
                  case 'B' :
                     CTime= 4.25;
                     setting = 0;
                     break;
                 case 'C' :
                     CTime= 4.75;
                     setting = 0;
                     break; 
                  case 'D' :
                     CTime= 5;
                     setting = 0;
                   break;
                                         
                  case '*':
                     CTime= 4.5;
                   
                    lcd.print("SAVING   ");
                    setting =0;
        
                   Serial.println(ch1);
                   delay(1000);
                    break;

                 }
                }
               }
}

void BUTTT(){
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("BUTT-TIME ");
              

               while (setting == 1) {
              lcd.setCursor(0,1);
              lcd.print("A 12 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("B 12.5 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);
              lcd.print("C 13.5 HRS     ");
              delay(2000); 
              lcd.setCursor(0,1);
              lcd.print("D 14 HRS     ");
              delay(2000);
              lcd.setCursor(0,1);              
              lcd.print("* DEFAULT-13");
              delay(2000);
                
                if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case 'A' :
                     CTime= 12;
                     setting = 0;
                     break;
                  case 'B' :
                     CTime= 12.5;
                     setting = 0;
                     break;
                 case 'C' :
                     CTime= 13.5;
                     setting = 0;
                     break; 
                  case 'D' :
                     CTime= 14;
                     setting = 0;
                   break;
                                         
                  case '*':
                     CTime= 13;
                   
                    lcd.print("SAVING   ");
                    setting =0;
        
                   Serial.println(ch1);
                   delay(1000);
                    break;

                 }
                }
               } 
}

void STOP(){
  while (setting = 1){
    lcd.clear();
    lcd.print("FINISHED ");
    analogWrite(SSRPin, 0);
    delay(500);
  }
}
void PreHeat(){
  
int preheat = 1;
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("PREHEAT TO ");lcd.print(OTemp); lcd.print("\337C");
  delay(5000);
  while ( preheat ==1){
    float TEMP = tc1.readC();
  lcd.setCursor(0,1); lcd.print(TEMP); lcd.print("\337C    "); 
  if ( OTemp > TEMP) { Serial.println("ON");analogWrite(SSRPin, 100); } else { analogWrite(SSRPin, 0); Serial.println("READY FOR USE");lcd.clear(); lcd.setCursor(0,0); lcd.print("  READY FOR USE ");}
  delay(300);
  if (keyPad.isPressed()){
                 char ch1 = keyPad.getChar();
              switch (ch1){
                  case '#' :
                     preheat = 0;
                     break;
              }
  }
  }
}

void NUMBER(){
  
  if (keyPad.isPressed())
  {
    char ch = keyPad.getChar();
    switch (ch)
    {
      case '0'...'9' :
tmp0 = ch- '0';
   lcd.setCursor(0,1);lcd.print("               ");
   lcd.setCursor(0,1); lcd.print(tmp0 ,0);
//int NUM =1;
while (Number ==1) {
   delay(500);
   if (tmp0 > 2000){ tmp0 = 0; }
   lcd.setCursor(0,1);lcd.print("               ");
   lcd.setCursor(0,1); lcd.print(tmp0, 0);
   Serial.println(tmp0);
  if (keyPad.isPressed())
  {
    char ch = keyPad.getChar();
    switch (ch)
    {
      case '0'...'9' :
      Serial.println(tmp0);
        tmp0 = (tmp0*10) + (ch - '0');
        Serial.print(ch);Serial.print(" "); Serial.println(tmp0);
        
        break;
      case '*':
 Number=0;
        break;

    }
  }

}
        break;
      case '*':
      Number == 0;
        break;

    }
  }

}
