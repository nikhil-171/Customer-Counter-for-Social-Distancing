/*The project was created in light of the Coronavirus pandemic.
I created a Arudino device that would be able to monitor and regulate the number of customer in indoor environments.
When placed at an entrance it will count the number of people entering and will indicate through leds when maximum capacity is reached.
*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int trigPin = 8;
const int echoPin = 9;
int duration, distance;
int customer = 0 ;

void setup() {
 lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
 digitalWrite(trigPin, LOW);          //initalizing ultrasonic signal
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  distance = distance/30.48;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(500);

  if (distance<2){                 //utilizing a counter to monitor the number of people entering
  customer= customer+1;
  lcd.clear();
  lcd.print("Customers: ");
  lcd.println(customer);
  
  }
  if  (customer<=10){
    digitalWrite(7, HIGH);        //activating a green led when number of people are below max capacity
    digitalWrite(6, LOW);
  }
  if (customer>10){
    digitalWrite(7, LOW);         //activating a red led when number of people are above max capacity
    digitalWrite(6, HIGH);
  }
  
}
