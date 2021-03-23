#include <SoftwareSerial.h>
SoftwareSerial moduleWifi(3, 2); // TX | RX
 
void setup()
{ 
  Serial.begin(115200);
  moduleWifi.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  configModuleWifi();
}
 
void loop()
{ 
   String cc="";
   cc= readModuleWifi();
   int var = 0;
   var= readGet(cc);
   switch (var) {
    
    case -2:
    turnOffOnError();
    break;
    
    case 1:
    turnLedOn();
    break;

    case 2:
    turnLedOff();
    break;

    default:
    //Serial.println("--");
    break;
   }

}

String readModuleWifi(){
   char cal;
   String cadena = "";
  while (moduleWifi.available() == 0) {
    //nada
  }
  do {
    if (moduleWifi.available() > 0) {
      cadena = "";
      cal = moduleWifi.read(); ;
      while (cal != '\n'){
      cadena += cal ;
      delay(200) ;
      cal = moduleWifi.read();
    }
      Serial.println("---> " + cadena);
      return cadena; 
      
    }
  }  while ((moduleWifi.available() == 0));  
  
 }

  int readGet(String cadena){
    if(cadena.length() > 0){hola esta es la posicion /25
      if (cadena.startsWith("/on",15)){
        //turnLedOn();
        return 1;
        }
      if (cadena.startsWith("/off",15)){
        //turnLedOff();
        return 2;
        }
      if (cadena.startsWith("/off",15) != true || cadena.startsWith("/on",15) != true){
        //turnLedOff();
        return -1;
        }
      }
      return 0;
    }
  
  void turnLedOn(){
     digitalWrite(LED_BUILTIN, HIGH);
     Serial.println("led on -> ok");
     sendData("AT+CIPCLOSE\r\n",2000); 
  }
  
  void turnLedOff(){
    digitalWrite(LED_BUILTIN, LOW); 
    Serial.println("led off -> ok");
    sendData("AT+CIPCLOSE\r\n",2000); 
  }

  void turnOffOnError(){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300); 
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300); 
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(300); 
    digitalWrite(LED_BUILTIN, LOW); 
    Serial.println("a request does not exist");
  }

  void configModuleWifi(){
    sendData("AT+RST\r\n",2000); 
    sendData("AT+CWMODE=3\r\n",1000);
    //sendData("AT+CWJAP=\"DELTA 2020\",\"Delta992020.\"\r\n",6000);
    sendData("AT+CIPMUX=1\r\n",2000);
    sendData("AT+CIPSERVER=1,80\r\n",4000); 
    sendData("AT+CIFSR\r\n",8000);
    Serial.println("--------- END CONFIG -----------");
    }

  void sendData(String comando, const int timeout) {
    long int time = millis();
    moduleWifi.print(comando); 
    while( (time+timeout) > millis())
    {
      while(moduleWifi.available())
      { // Leer los datos disponibles
        char c = moduleWifi.read();
        Serial.print(c);
      }
    } 
    return;
  }

  



  
