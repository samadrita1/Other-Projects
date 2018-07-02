const int trig2=7;
const int echo2=8;
const int trig1=9;
const int echo1=10;
const int lightpin=A0;
int ldrval=0;
int LED1=13;
int LED2=12;
int distance1, distance2;
long duration1, duration2;

void setup() {
  pinMode(trig1,OUTPUT);
  pinMode(echo1,INPUT);
  pinMode(trig2,OUTPUT);
  pinMode(echo2,INPUT);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);// put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  //ldrval=analogRead(sensorPin);
  ldrval=650;
  //if(ldrval<700)
 // {
    digitalWrite(trig1,HIGH);
    digitalWrite(trig2,HIGH);
    duration1=pulseIn(echo1,HIGH);
    duration2=pulseIn(echo2,HIGH);
    distance1=duration1/34;
    distance2=duration2/34;
    Serial.print(distance1);
    Serial.print("-----");
    Serial.println(distance2);
    if(distance1<5)
    {
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      delay(1000);
    }
    else
    {
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW);
    }
 // }
  /*
  else
  {
    digitaWrite(trig,LOW);
    digitalWrite(LED1,LOW);
    digitalWrite(LED2,LOW);
    delay(90000);
  }*/
}
