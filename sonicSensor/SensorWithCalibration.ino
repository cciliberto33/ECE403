int trigPin = 2;
int trigSensorPin = 52;
int trigReadPin = A0;
int echoPin = 48;
int startProcessPin = 2;
int edgeCount = 0;
int prevEdgeCount = 0;
int counter = 0;
double starttime = 0;
double stoptime = 0;
double duration = 0;
double distance = 0;
double adjdist = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin,INPUT);
  pinMode(trigSensorPin,OUTPUT);
  pinMode(startProcessPin,INPUT);
  attachInterrupt(digitalPinToInterrupt(trigPin),riseCount,RISING);
}

void loop() {
  while (counter < 101){
  startProcess();
  delay(10);
  counter++ ;
  }
}

void lowpass_filter(double old, double &filtered, double alpha){
  filtered = (1-alpha)*old + alpha*filtered;
}

void riseCount(){
  edgeCount++;
}

double filtered_d;

void startProcess(){
  // things to fix:: add a timeout to waiting for a return signal....
  delay(2);
  digitalWrite(trigSensorPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigSensorPin,LOW);
  while(digitalRead(echoPin) == LOW){
    
  }
  starttime = micros();
  while(digitalRead(echoPin)== HIGH){
    
  }
  stoptime = micros();
  duration = stoptime - starttime;
  distance = duration / 148;
  lowpass_filter(distance, filtered_d, 0.01);
  adjdist = percenterroradjust(distance);
  Serial.println(adjdist);
}

double percenterroradjust(double D){
  double percenterror = -0.11*D + 5.8; //This is the percent error calculation based on the line of best fit calculated in MATLAB.
  double newdistance = D*(1.0/(1.0+(percenterror/100)));
  return newdistance;
}
