#include <EEPROM.h>
#include <SoftwareSerial.h>
int flag=0,D[4]={3,3,3,3};
int Hs1[4]={30,30,30,30},He1[4]={30,30,30,30},Ms1[4]={70,70,70,70},Me1[4]={70,70,70,70};
int relay1=9,relay2=12,relay3=11,relay4=10;// Relays which can be used to turn on AC, TV etc.
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#define testing 0 // for time
#define testing1 0 // for status of device
#define testing2 0 // hs ms he me
#define testing3 0 // for serial
#define testing4 0  // for tr
tmElements_t tm;
SoftwareSerial Serial_bluetooth(8,7);

void setup() 
{Serial.begin(9600);
Serial_bluetooth.begin(9600);
pinMode(relay1,OUTPUT);
pinMode(relay2,OUTPUT);
pinMode(relay3,OUTPUT);
pinMode(relay4,OUTPUT);
eeprom_read();
}


int number_convert(int tens, int ones)
{
  int no;
  no=tens*10+ones;
  return(no);
}

void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

void eeprom_read(){   
  int eeprom_location1=1,eeprom_location2=11,eeprom_location3=21,eeprom_location4=31;
  for(int i=0;i<=3;i++)
  {
    {
      Hs1[i]=EEPROM.read(eeprom_location1);
      Ms1[i]=EEPROM.read(eeprom_location2);
      He1[i]=EEPROM.read(eeprom_location3);
      Me1[i]=EEPROM.read(eeprom_location4);
      eeprom_location1=eeprom_location1+2;
      eeprom_location2=eeprom_location2+2;
      eeprom_location3=eeprom_location3+2;
      eeprom_location4=eeprom_location4+2;
    }
  }
}
void eeprom_write(){ 

  int eeprom_location1=1,eeprom_location2=11,eeprom_location3=21,eeprom_location4=31;
  for(int i=0;i<=3;i++)
  {
    {
      EEPROM.write(eeprom_location1,Hs1[i]);
      EEPROM.write(eeprom_location2,Ms1[i]);
      EEPROM.write(eeprom_location3,He1[i]);
      EEPROM.write(eeprom_location4,Me1[i]);
      eeprom_location1=eeprom_location1+2;
      eeprom_location2=eeprom_location2+2;
      eeprom_location3=eeprom_location3+2;
      eeprom_location4=eeprom_location4+2;
    }
  }
}
int time_range(int Hs,int He, int Ms, int Me)
{
  
  if(testing2==1)
{
  delay(1000);
  Serial.print(" hs device:  ");
  Serial.print(Hs);
   Serial.print(" ms device:  ");
  Serial.print(Ms);
   Serial.print(" he device:  ");
  Serial.print(He);
   Serial.print(" me device:  ");
  Serial.println(Me);
}
int     H,M,S;
int range=0;
    if (RTC.read(tm)) 
    {
H=tm.Hour;
M=tm.Minute;
S=tm.Second;
if(testing==1)
{
print2digits(H);
Serial.print(":");
print2digits(M);
Serial.print(":");
print2digits(S);
Serial.println(":");
delay(300);
}
    } 

if(Hs!=He)
{
if(H==Hs){if(M>=Ms){range=1;}else {range=0;}}
else if(H==He){if(M<=Me){range=1;}else {range=0;}}
else if(Hs<H&&H<He){range=1;}
}
else if(Hs==He){if(H==Hs){if(M>=Ms && M<=Me){range=1;}else {range=0;}}}
else{range=0;}
//Serial.println(" range: ");
//Serial.println(range);
return(range);
}

void serial_check()
{

  int s[20]={},count=0,s_temp=0;
  while(Serial_bluetooth.available())
  {
    while(!Serial_bluetooth.available()){}
    flag=1;
    s_temp=Serial_bluetooth.read();

    if(s_temp!='x'){s[count]=s_temp;}
     if(testing3==1)
{
    Serial.write(s[count]);
}
    count++;
    delay(2)  ;  
  }
  
  if(flag==1)
  {
    if(s[0]=='#')
    {
      
      if(s[1]=='T')
      {
        if(s[2]=='A')
        { 
          D[0]=2;
      Hs1[0]=number_convert(s[4]-48,s[5]-48);
      Ms1[0]=number_convert(s[7]-48,s[8]-48);
      He1[0]=number_convert(s[11]-48,s[12]-48);
      Me1[0]=number_convert(s[14]-48,s[15]-48) ;       
        }
        else if(s[2]=='B')
        {
          D[1]=2; 
      Hs1[1]=number_convert(s[4]-48,s[5]-48);
      Ms1[1]=number_convert(s[7]-48,s[8]-48);
      He1[1]=number_convert(s[11]-48,s[12]-48);
      Me1[1]=number_convert(s[14]-48,s[15]-48) ;  
        }
        else if(s[2]=='C')
        {
          D[2]=2;
      Hs1[2]=number_convert(s[4]-48,s[5]-48);
      Ms1[2]=number_convert(s[7]-48,s[8]-48);
      He1[2]=number_convert(s[11]-48,s[12]-48);
      Me1[2]=number_convert(s[14]-48,s[15]-48) ;
          }
        else if(s[2]=='D')
        {
          D[3]=2;
      Hs1[3]=number_convert(s[4]-48,s[5]-48);
      Ms1[3]=number_convert(s[7]-48,s[8]-48);
      He1[3]=number_convert(s[11]-48,s[12]-48);
      Me1[3]=number_convert(s[14]-48,s[15]-48) ;
        }
        eeprom_write();
      }
    }
//    else if(s[0]=='x')
//    {
//
//    }

    else
    {
      
      if(s[0]=='A'){D[0]=0;}
      else if(s[0]=='a'){D[0]=1;}
      else if(s[0]=='B'){D[1]=0;}
      else if(s[0]=='b'){D[1]=1;}
      else if(s[0]=='C'){D[2]=0;}
      else if(s[0]=='c'){D[2]=1;}
      else if(s[0]=='d'){D[3]=1;}
      else if(s[0]=='D'){D[3]=0;}
    }
  flag=0;
if(testing1==1)
{  
  Serial.print(" A device:  ");
  Serial.print(D[0]);
   Serial.print(" B device:  ");
  Serial.print(D[1]);
   Serial.print(" C device:  ");
  Serial.print(D[2]);
   Serial.print(" D device:  ");
  Serial.println(D[3]);
delay(300);
}

  }
}


void relay()
{
int time_flag[4]={0,0,0,0};  

if(D[0]==1){digitalWrite(relay1,1);}else if(D[0]==0) {digitalWrite(relay1,0);}
if(D[1]==1){digitalWrite(relay2,1);}else if(D[1]==0){digitalWrite(relay2,0);}
if(D[2]==1){digitalWrite(relay3,1);}else if(D[2]==0){digitalWrite(relay3,0);}
if(D[3]==1){digitalWrite(relay4,1);}else if(D[3]==0){digitalWrite(relay4,0);}
time_flag[0]=time_range(Hs1[0],He1[0],Ms1[0],Me1[0]);
time_flag[1]=time_range(Hs1[1],He1[1],Ms1[1],Me1[1]);
time_flag[2]=time_range(Hs1[2],He1[2],Ms1[2],Me1[2]);
time_flag[3]=time_range(Hs1[3],He1[3],Ms1[3],Me1[3]);
if(testing4==1)
{
Serial.print("tr 1:");
Serial.print(time_flag[0]);
Serial.print(" tr 2:");
Serial.print(time_flag[1]);
Serial.print(" tr 3:");
Serial.print(time_flag[2]);
Serial.print(" tr 4:");
Serial.println(time_flag[3]);
delay(300);
}
if(D[0]==2){digitalWrite(relay1,time_flag[0]);}
if(D[1]==2){digitalWrite(relay2,time_flag[1]);}
if(D[2]==2){digitalWrite(relay3,time_flag[2]);}
if(D[3]==2){digitalWrite(relay4,time_flag[3]);}

}

void loop() 
{
//  Serial.println("112");
serial_check();
relay();  
}
