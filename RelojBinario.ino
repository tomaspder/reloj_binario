#include <Time.h>
#include <TimeLib.h>

int ledPinsSec[] = {2, 3, 4, 5, 6, 7};
int ledPinsMin[] = {8, 9, 10, 11, 12, 13};
int ledPinsHr[] = {15, 16, 17, 18, 19};
int secSize = sizeof(ledPinsSec) / sizeof(int);
int minSize = sizeof(ledPinsMin) / sizeof(int);
int hourSize = sizeof(ledPinsHr) / sizeof(int);


//Horario fijo - se precisa modulo RTC o Shield Ethernet para obtener la hora en tiempo reaal
int seconds = 20;
int minutes = 22;
int hours = 20;

void setup() 
{
  Serial.begin(9600);
  for(int i = 0; i< secSize;i++)
  {
    pinMode(ledPinsSec[i], OUTPUT);
  }
  for(int i = 0; i< minSize;i++)
  {
    pinMode(ledPinsMin[i], OUTPUT);
  }
  for(int i = 0; i< hourSize;i++)
  {
    pinMode(ledPinsHr[i], OUTPUT);
  }
}
void loop() 
{
    seconds++;
    if(seconds > 59)
    {
      seconds = 0;
      minutes++;
      if(minutes > 59)
      {
        minutes = 0;
        hours++;
        if(hours > 23)
        {
          hours = 0;
        }
      }
    }

    Serial.print("Hours: ");
    Serial.print(hours);
    Serial.print("\t");
    Serial.print(hours, BIN);
    Serial.print(" Minutes: ");
    Serial.print(minutes);
    Serial.print("\t");
    Serial.print(minutes, BIN);
    Serial.print(" Seconds: ");
    Serial.print(seconds);
    Serial.print("\t");
    Serial.println(seconds, BIN);
    DisplaySeconds();
    DisplayMinutes();
    DisplayHours();
    delay(1000);

}
void DisplaySeconds()
{     
  for(int i = secSize - 1; i>= 0; i--)
  {
    int currentSecond = bitRead(seconds, i);
    digitalWrite(ledPinsSec[i], currentSecond); 
  }  
}
void DisplayMinutes()
{     
  for(int i = minSize - 1; i>= 0; i--)
  {
    int currentMinute = bitRead(minutes, i);
    digitalWrite(ledPinsMin[i], currentMinute); 
  }  
}
void DisplayHours()
{     
  for(int i = hourSize - 1; i>= 0; i--)
  {
    int currentHour = bitRead(hours, i);
    digitalWrite(ledPinsHr[i], currentHour); 
  }  
}
