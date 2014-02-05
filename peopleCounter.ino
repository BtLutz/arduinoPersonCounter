const int pingPin = 7;
const int trigPin = 12;
const int echoPin = 13;

int lastPing;
int lastEcho;
int personCounter;

boolean pingTrigger;
boolean echoTrigger;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
}

void loop()
{
  int pingCentimeters = findDistance();
  int delta = abs(lastPing - pingCentimeters);
  
  if(pingCentimeters < 100 && delta > 50 && delta < 100 ) {
    personCounter++;
    Serial.print("New Person: ");
    Serial.print(personCounter);
    Serial.print(" Distance: ");
    Serial.print(pingCentimeters);
    Serial.print(" Last Distance: ");
    Serial.print(lastPing);
    Serial.print(" distance btn: ");
    Serial.print(abs(lastPing - pingCentimeters));
    Serial.print("\n");
    delay(950);
  }
  lastPing = pingCentimeters;
  delay(30);
}
  
long findDistance()
{
  long pingDuration, pingInches, pingCentimeters;
  long echoDuration, echoInches, echoCentimeters;
  
  //Check duration for pingPin
  
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  pingDuration = pulseIn(pingPin, HIGH);
  
  pingCentimeters = microsecondsToCentimeters(pingDuration);
  
  return pingCentimeters;
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
