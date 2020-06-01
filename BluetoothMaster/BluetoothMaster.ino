   
#include <EasyTransfer.h> //https://github.com/madsci1016/Arduino-EasyTransfer

char temperatureChar[10];
char humidityChar[10];

struct WEATHER_DATA_STRUCTURE
{
  float temperature ;
  float humidity ;
};

struct ACKNOWLEDGE
{
  boolean received = false;
};

WEATHER_DATA_STRUCTURE data;
ACKNOWLEDGE acknowledge;
#include <LiquidCrystal.h>
EasyTransfer ETin, ETout; 
LiquidCrystal lcd(12,11,5,4,3,2);
void setup() {
  pinMode(5, OUTPUT);
  Serial.begin(9600);
  ETin.begin(details(data), &Serial);
  ETout.begin(details(acknowledge), &Serial);
  lcd.begin(16,2);
}

void loop() {

  if(ETin.receiveData()){

    String temperatureString = String(data.temperature,1);
    temperatureString.toCharArray(temperatureChar,10);
    Serial.println(temperatureString);
    String humidityString = String(data.humidity,1);
    humidityString.toCharArray(humidityChar,10);
    Serial.println(humidityString);
    acknowledge.received = 1;
    ETout.sendData();
    
    delay(200);
    acknowledge.received = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TEMP:");
    lcd.setCursor(6,0);
    lcd.print(temperatureString);
    
    lcd.setCursor(0,1);
    lcd.print("DEW:");
    lcd.setCursor(5,1);
    lcd.print(humidityString);
  }
}
