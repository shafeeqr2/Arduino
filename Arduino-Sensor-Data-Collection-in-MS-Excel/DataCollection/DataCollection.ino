//Sensor Data Collection and Graphing

//Temperature Sensor 
float temp;
float valueTemp;
float diffTemp;

//Relative Humidity Sensor
float RH;
float valueRH;
float diffRH;

//Sound Sensor
float sound;
float valueSound;
float diffSound;

//Motion Sensor
float valueMotion;
int motionCounter;
boolean motion;


void setup() {
  
  //Initialize the Serial baud rate to 9600. Initialize analog pins a0 to a3.
  Serial.begin(9600);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  
  //This information is needed by the PLX-DAQ application.
  Serial.println("CLEARDATA");
  
  //This tells the PLX-DAQ application that these are the column titles.
  Serial.println("LABEL,Time,Temperature C, Relative Humidity %, Sound dB, Motion Sensor");
  
  //Each of the sensor values has a specific equation to follow based on their manufacturer.
  //This equation converts sensor data into actual temperature value, relative humidity, sound and moton.
  temp = (analogRead(A0)*0.2222) - 61.111;
  RH = (analogRead(A1)*0.1906) - 40.2;
  sound = 16.801*log(analogRead(A2)) + 9.872;
  
  //Motion is a boolean. can be set to true or false.
  motion = false;

}

void loop() {
  
  //reinitialize motion to false.  
  motion = false;

  //The difference in temperature is recorded. 
  diffTemp = valueTemp - temp;
  diffRH = valueRH - RH;
  diffSound = valueSound - sound;
  
  //Analog value converted into actual temperature.
  valueTemp = (analogRead(A0)*0.22222) - 61.111;
  
  //if the change in temperature is greater than half a degree centigrade, redefine temperature.
  if ((diffTemp >= 0.5) || (diffTemp <= -0.5)) {
    temp = valueTemp;
    
    //Use the sending values function to send data from all the sensors in this one instance.
    SendingValues();
    
    //set diffTemp back to 0.
    diffTemp = 0;
  }
  
  //Analog value converted into actual relative humidity.
  valueRH = (analogRead(A1)*0.1906) - 40.2;

  if ((diffRH >= 0.5) || (diffRH <= -0.5)) {
    RH = valueRH;
    
    //Use the sending values function to send data from all the sensors in this one instance.
    SendingValues();
    
    //set diffRH back to 0.
    diffRH = 0;
  }

  valueSound = 16.801*log(analogRead(A2)) + 9.872;

  if ((diffSound >= 10) || (diffSound <= -10)) {
    sound = valueSound;
    
    //Use the sending values function to send data from all the sensors in this one instance.
    SendingValues();
    
    //set diffSound back to 0.
    diffSound= 0;
  }
  
  
 
  delay(500);
  
  valueMotion = analogRead(A3);
  //if four consecutive readings are out of the range 490 to 610, then motion detected = true.

  if ((valueMotion < 490) || (valueMotion > 610)) {
    motionCounter++;
  }

  if ((valueMotion > 490) && (valueMotion < 610)) {
    motionCounter = 0;
  }

  if (motionCounter >= 5) {
    motion = true;
    
    //Use the sending values function to send data from all the sensors in this one instance.
    SendingValues();
    
    
    motionCounter = 0;
  }
  
  
    
}

//These values are sent through the serial link one line at at time. The PLX-DAQ application takes these values and stores them into a Microsoft Excel spreadsheet.
void SendingValues() {
    Serial.print("DATA,TIME,");
    Serial.print(temp);
    Serial.print(",");
    Serial.print(RH);
    Serial.print(",");
    Serial.print(sound);
    Serial.print(",");
    Serial.println(motion);
}

