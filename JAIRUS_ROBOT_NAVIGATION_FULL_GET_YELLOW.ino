//setting up for pixy cam 
#include <Pixy2.h>
Pixy2 pixy;

//setting up for IR sensors  for counter 
int intersections=0;
int i;
int ledpin =13;
int IR_R=50;
int IR_C=46;
int IR_L=52;

// stting for the u;trasonic sensors 
int trigpin=11,echopin=10;
int long duration,distance;


// Setting up for the motors 
//Rigth motors 1             //motor 2      //left motor 3           // motor 4 
int EN1=7;            int EN2=6;           int EN3=9;        int EN4=8;
int in1=23;            int in3=26;         int in5=30;        int in7=34;
int in2=24;            int in4=28;         int in6=32;        int in8=36;

void setup() {

  
  // setting the baud rate 
  Serial.begin(115200);  
  
  // starting the execution 
  Serial.print("starting...\n");

  
  // setting  up for the pixy cam
  pixy.init();
  pixy.changeProg("line");
  pixy.setServos(300,0);
   pixy.setLamp(1,0);
   
 // setting up for the counter led 
pinMode(ledpin,OUTPUT);

     
     // setting up for the ultrasonic sensor 
pinMode(trigpin,OUTPUT);
pinMode(echopin,INPUT);


  //Rigth motor 1
pinMode(EN1,OUTPUT);
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
//motor 2
pinMode(EN2,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);

//left motors
//MOTOR 3 
pinMode(EN3,OUTPUT);
pinMode(in5,OUTPUT);
pinMode(in6,OUTPUT); 
// motor 4 
pinMode(EN4,OUTPUT);
pinMode(in7,OUTPUT);
pinMode(in8,OUTPUT);
}

void moveforward(int R,int L){
   analogWrite(EN1,R);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
   analogWrite(EN2,R);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

   analogWrite(EN3,L);
  digitalWrite(in5,HIGH);
  digitalWrite(in6,LOW);
   analogWrite(EN4,L);
  digitalWrite(in7,HIGH);
  digitalWrite(in8,LOW);
 
  }
  void movebackwards(int e){
    analogWrite(EN1,e);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
   analogWrite(EN2,e);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);

   analogWrite(EN3,e);
  digitalWrite(in5,LOW);
  digitalWrite(in6,HIGH);
   analogWrite(EN4,e);
  digitalWrite(in7,LOW);
  digitalWrite(in8,HIGH);
  }
  void turnrigth(int R,int L){
  analogWrite(EN1,R);
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
   analogWrite(EN2,R);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);

   analogWrite(EN3,L);
  digitalWrite(in5,LOW);
  digitalWrite(in6,HIGH);
   analogWrite(EN4,L);
  digitalWrite(in7,LOW);
  digitalWrite(in8,HIGH);
}
void turnleft(int e, int s) {
  analogWrite(EN1,e);
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
   analogWrite(EN2,e);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);

   analogWrite(EN3,s);
  digitalWrite(in5,HIGH);
  digitalWrite(in6,LOW);
   analogWrite(EN4,s);
  digitalWrite(in7,HIGH);
  digitalWrite(in8,LOW);
}


void stopp(){
  movebackwards(255);
  delay(100);
  moveforward(255,255);
  delay(25);
  moveforward(0,0);
  for(;;){}
}

void pixy_allign(){
 pixy.line.getMainFeatures();

  if(pixy.line.vectors){
        if(pixy.line.vectors->m_x1 <35 && pixy.line.vectors->m_x0 <35){
         moveforward(255,0);
  }
       else if(pixy.line.vectors->m_x1 > 35 && pixy.line.vectors->m_x0 > 35){
        moveforward(0,255);
  }
       else{
         moveforward(255,255);
    }
  }
  }

  void counter(){
int val1=digitalRead(IR_R);
int val2=digitalRead(IR_C);
int val3=digitalRead(IR_L);


 
  if(val1 ==LOW && val2==LOW && val3==LOW){
    intersections++;
    Serial.println("val high");
    analogWrite(ledpin,100);
     delay(100);
    Serial.println(intersections);  
     analogWrite(ledpin,0);
Serial.print(val1);Serial.print(" ");Serial.print(val2);Serial.print(" ");Serial.println(val3);
     //Serial.println(intersections);
}  
  }

  void ultrasonic(){
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  duration=pulseIn(echopin,HIGH);
  distance= duration*(0.034/2);
  Serial.print("distance=");
  Serial.print(distance);
  Serial.println ("...cm");
  if (distance<=20) {
    stopp();
  }
  else {
pixy_allign();
  }
  }


void turn_left(){
  int found;
  int index = pixy.line.vectors->m_index;
      pixy.line.getMainFeatures();

     found=pixy.line.vectors;
 
     if(found==0){
     // if(index!=index){
     turnleft(175,255);
     }
     if( pixy.line.vectors->m_y1 < pixy.line.vectors->m_y0){
     
     pixy_allign();}
     }

     
 void turn_right(){
     pixy.changeProg("line");
    int found;
    int index = pixy.line.vectors->m_index;
    pixy.line.getMainFeatures();
    found=pixy.line.vectors;
 
    if(found==0){
   // if(index!=index){
   turnrigth(175,255);
    }
    if( pixy.line.vectors->m_y1 < pixy.line.vectors->m_y0){
     
     pixy_allign();}
    }

    // lets get the yellow object 
void getyellow(){
   if (intersections <=2){
       turn_left();
       }
   else if (intersections==5){
       turnrigth(255,255);
       delay(300);
       intersections++;
       }
 else if (intersections==6 ){
    delay(25);
       stopp();
       intersections++;
       }
        else {
     pixy_allign();
     }}
       
    
void loop() {
  // put your main code here, to run repeatedly:
getyellow();
}
