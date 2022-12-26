#define TRIG_PIN 23 // ultrasonic pin
#define ECHO_PIN 22 // ultrasonic pin
#define MoP1 34 // moister sensor linked to relay at pin 17
#define MoP2 35 // moister sensor linked to relay at pin 16
#define MoP3 36 // moister sensor linked to relay at pin 27
#define MoP4 39 // moister sensor linked to relay at pin 26
#define ReP1 17 // relay controlled by moister sensor at pin 34
#define ReP2 16 // relay controlled by moister sensor at pin 35
#define ReP3 27 // relay controlled by moister sensor at pin 36
#define ReP4 26 // relay controlled by moister sensor at pin 39
#define THRESHOLD1 1000 // moister sensor calibration value to trigger the relay for watring used with pins 34 + 36 (((needs calibration)))
#define THRESHOLD2 1000 // moister sensor calibration value to trigger the relay for watring used with pins 35 + 39 (((needs calibration)))

//these are parameters used to get the needed outputs
float duration_us, distance_cm, i, saved, r, y, perc;
//initil setup
void setup() {
  Serial.begin (9600);
  pinMode(TRIG_PIN, OUTPUT); //ultrasonic
  pinMode(ECHO_PIN, INPUT); //ultrasonic
  pinMode(ReP1, OUTPUT); // relay module
  pinMode(ReP2, OUTPUT); // relay module
  pinMode(ReP3, OUTPUT); // relay module
  pinMode(ReP4, OUTPUT); // relay module
  i=0;  // used to get the amount of water used

  
}

void loop() {
  // put your main code here, to run repeatedly:
  int Moi1 = analogRead(MoP1); // read the analog value from moister sensor 1
  int Moi2 = analogRead(MoP2); // read the analog value from moister sensor 1
  int Moi3 = analogRead(MoP3); // read the analog value from moister sensor 1
  int Moi4 = analogRead(MoP4); // read the analog value from moister sensor 1
  
  
  
  if (Moi1 < THRESHOLD1) { // loop to trigger the watering porcess uses the threshold
    digitalWrite(ReP1, HIGH); // start relay
    delay(1000); // delay next line by 1 sec (((needs calibration)))
    digitalWrite(ReP1, LOW); // stop relay
    i=i+1; // calculate water used
  } else {
    digitalWrite(ReP1, LOW); // keep the relay off because no watring needed
  }  
  // same process in all loops as the one before
  if (Moi2 < THRESHOLD2) {
    digitalWrite(ReP2, HIGH);
    delay(1000);
    digitalWrite(ReP2, LOW);
    i=i+1;
  } else {
    digitalWrite(ReP2, LOW);
  }

  if (Moi3 < THRESHOLD1) {
    digitalWrite(ReP3, HIGH);
    delay(1000);
    digitalWrite(ReP3, LOW);
    i=i+1;
  } else {
    digitalWrite(ReP3, LOW);
  }

  if (Moi4 < THRESHOLD2) {
    digitalWrite(ReP4, HIGH);
    delay(1000);
    digitalWrite(ReP4, LOW);
    i=i+1;    
  } else {
    digitalWrite(ReP4, LOW);
  }
  // trigger the ultrasonic to get measrements
  digitalWrite(TRIG_PIN, HIGH); 
  delayMicroseconds(1000);
  digitalWrite(TRIG_PIN, LOW); 
  
 
  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;
  saved = i * 5; // the should display the amount of water used (((needs calibration)))
  y= -(distance_cm - 30) * 35 * 50 ; // calculate the distance to help in getting the water level percentage
  r= (y/43750) * 100 ;  // get water level percantage
  //perc = y/1000;
  Serial.println(Moi1); // all serial.print are lines to display collected data
  Serial.println(Moi2);
  Serial.println(Moi3);
  Serial.println(Moi4);  
// this is a loop to tell us if the water level is overflowing or empty or display current water percentage  
  if (distance_cm >= 30 ) {
    Serial.print("\nEmpty");
       
  } else if (distance_cm <= 5 ){
    Serial.print("\nOverflow");
  } else {
    Serial.print("\n");
    Serial.print(perc);
    Serial.print("liter");
    Serial.print("\n");
    Serial.print(r);  
    Serial.print("%");
  }// print the value to Serial Monitor
  
  delay(30000);
}
