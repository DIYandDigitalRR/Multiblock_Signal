int Sensor1 = A0; //Sensor 1 is setup on pin A0
int Sensor2 = A1; //Sensor 2 is setup on pin A1
int Green1 = 13; // Green Signal 1 is digital pin 2
int Yellow1 = 3;// Yellow Signal 1 is digital pin 3
int Red1 = 4;// Red Signal 1 is digital pin 4
int Green2 = 5;// Green Signal 2 is digital pin 5
int Yellow2 = 6;// Yellow Signal 1 is digital pin 6
int Red2 = 7;//Red Signal 2 is digital pin 7
int blockASend=8;// The transmit pin for the previous block in the sequence
int blockBSend=9;// The transmit pin for the next block in the sequence
int blockARec=10;// The recieve pin for the previous block in the sequence
int blockBRec=11;// The recieve pin for the next block in the sequence
int clearcount;

void setup() {
  Serial.begin(9600);

  //Establish all of our pins at inputs or outputs

  pinMode(Sensor1, INPUT);
  pinMode(Sensor2, INPUT);
  pinMode(Green1, OUTPUT);
  pinMode(Yellow1, OUTPUT);
  pinMode(Red1, OUTPUT);
  pinMode(Green2, OUTPUT);
  pinMode(Yellow2, OUTPUT);
  pinMode(Red2, OUTPUT);
  pinMode(blockASend, OUTPUT);
  pinMode(blockBSend, OUTPUT);
  pinMode(blockARec, INPUT);
  pinMode(blockBRec, INPUT);
  
}

enum SIGNALSTATES
{
  ST_GG,
  ST_GY,
  ST_YG,
  ST_YY,
  ST_RR1,
  ST_RR2,
  ST_RR3,
  ST_YY1,
}; //Sets up different signal states for the entire program

SIGNALSTATES signalState = ST_GG; //Sets default state to Green and Green

void loop(){
  int valA1 = analogRead(Sensor1);
  int valA2 = analogRead(Sensor2);
  int valA3 = digitalRead(blockARec);
  int valA4 = digitalRead(blockBRec);
  // Sets up the values of the different signals we will be reading
  Serial.println(valA1);
  Serial.println(valA2);
  Serial.println(valA3);
  Serial.println(valA4);
  // Sets up the different values to be read on the serial monitor in the Arduino IDE
  delay(200);

  switch(signalState)
  {
    case ST_GG:
    signalgg(valA1, valA2, valA3, valA4);
    break;
    case ST_GY:
    signalgy(valA1, valA2, valA3, valA4);
    break;
    case ST_YG:
    signalyg(valA1, valA2, valA3, valA4);
    break;
    case ST_YY:
    signalyy(valA1, valA2, valA3, valA4);
    break;
    case ST_RR1:
    signalrr1(valA1, valA2, valA3, valA4);
    break;
    case ST_RR2:
    signalrr2(valA1, valA2, valA3, valA4);
    break;
    case ST_RR3:
    signalrr3(valA1, valA2, valA3, valA4);
    break;
    case ST_YY1:
    signalyy1(valA1, valA2, valA3, valA4);
    break;
    //this sets up our different loops within the main loop for our different signal states
  }
}

void signalgg(int valA1, int valA2, int valA3, int valA4){
  digitalWrite(Green1, LOW); //Sets Green1 to ON
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Green2, LOW); //Sets Green2 to ON
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(blockASend, LOW); //this will not transmit a signal to Block A
  digitalWrite(blockBSend, LOW); //this will not transmit a signal to Block B
  delay(200);
  clearcount=0;

  if ((valA1 > 500) && (valA2 >500) && (valA3==0) && (valA4==1)){
    signalState = ST_GY;//block not occupied but Block B is
  }
   if ((valA1 > 500) && (valA2 >500) && (valA3==1) && (valA4==0)){
    signalState = ST_YG;//block not occupied but Block A is
  }
   if ((valA1 > 500) && (valA2 >500) && (valA3==1) && (valA4==1)){
    signalState = ST_YY;//block not occupied but Block B and Block A are
  }
   if ((valA1 < 500) && (valA2 >500)){
    signalState = ST_RR1;// block is occupied entered from Sensor1
   }
    if ((valA1 > 500) && (valA2 <500)){
    signalState = ST_RR2;// block is occupied entered from Sensor2
   }
}

void signalgy(int valA1, int valA2, int valA3, int valA4){
  digitalWrite(Green1, LOW); //Sets Green1 to ON
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Red1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, LOW);//Sets Yellow2 to ON
  digitalWrite(Red2, HIGH);
  digitalWrite(blockASend, LOW); //this will not transmit a signal to Block A
  digitalWrite(blockBSend, LOW); //this will not transmit a signal to Block B
  delay(200);

  if ((valA1 > 500) && (valA2 >500) && (valA3==0) && (valA4==0)){
    signalState = ST_GG;//block not occupied No adjacent blocks occupied
  }
   if ((valA1 > 500) && (valA2 >500) && (valA3==1) && (valA4==0)){
    signalState = ST_YG;//block not occupied but Block A is
  }
   if ((valA1 > 500) && (valA2 >500) && (valA3==1) && (valA4==1)){
    signalState = ST_YY;//block not occupied but Block B and Block A are
  }
   if ((valA1 < 500) && (valA2 >500)){
    signalState = ST_RR1;// block is occupied entered from Sensor1
   }
    if ((valA1 > 500) && (valA2 <500)){
    signalState = ST_RR2;// block is occupied entered from Sensor2
   }
}

void signalyg(int valA1, int valA2, int valA3, int valA4){
  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, LOW);//Sets Yellow1 to ON
  digitalWrite(Red1, HIGH);
  digitalWrite(Green2, LOW);//Sets Green2 to ON
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red2, HIGH);
  digitalWrite(blockASend, LOW); //this will not transmit a signal to Block A
  digitalWrite(blockBSend, LOW); //this will not transmit a signal to Block B
  delay(200);

  if ((valA1 > 500) && (valA2 >500) && (valA3==0) && (valA4==0)){
    signalState = ST_GG;//block not occupied No adjacent blocks occupied
  }
   if ((valA1 > 500) && (valA2 >500) && (valA3==0) && (valA4==1)){
    signalState = ST_GY;//block not occupied but Block B is
  }
   if ((valA1 > 500) && (valA2 >500) && (valA3==1) && (valA4==1)){
    signalState = ST_YY;//block not occupied but Block B and Block A are
  }
   if ((valA1 < 500) && (valA2 >500)){
    signalState = ST_RR1;// block is occupied entered from Sensor1
   }
    if ((valA1 > 500) && (valA2 <500)){
    signalState = ST_RR2;// block is occupied entered from Sensor2
   }
}

void signalyy(int valA1, int valA2, int valA3, int valA4){
  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, LOW);//Sets Yellow1 to ON
  digitalWrite(Red1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, LOW);//Sets Yellow2 to ON
  digitalWrite(Red2, HIGH);
  digitalWrite(blockASend, LOW); //this will not transmit a signal to Block A
  digitalWrite(blockBSend, LOW); //this will not transmit a signal to Block B
  delay(200);

  if ((valA1 > 500) && (valA2 >500) && (valA3==0) && (valA4==0)){
    signalState = ST_GG;//block not occupied No adjacent blocks occupied
  }
   if ((valA1 > 500) && (valA2 >500) && (valA3==0) && (valA4==0)){
    signalState = ST_GY;//block not occupied but Block B is
  }
   if ((valA1 > 500) && (valA2 >500) && (valA3==1) && (valA4==0)){
    signalState = ST_YG;//block not occupied but Block B and Block A are
  }
   if ((valA1 < 500) && (valA2 >500)){
    signalState = ST_RR1;// block is occupied entered from Sensor1
   }
    if ((valA1 > 500) && (valA2 <500)){
    signalState = ST_RR2;// block is occupied entered from Sensor2
   }
}

void signalrr1(int valA1, int valA2, int valA3, int valA4){
  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Red1, LOW);//Sets Red1 to ON
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red2, LOW);//Sets Red2 to ON
  digitalWrite(blockASend, HIGH); //this will transmit a signal to Block A
  digitalWrite(blockBSend, HIGH); //this will transmit a signal to Block B
  delay(200);

  if ((valA1>500) && (valA2<500)){
    signalState = ST_RR3; //switched to transition Red signal state
  }
}

void signalrr2(int valA1, int valA2, int valA3, int valA4){
  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Red1, LOW);//Sets Red1 to ON
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red2, LOW);//Sets Red2 to ON
  digitalWrite(blockASend, HIGH); //this will transmit a signal to Block A
  digitalWrite(blockBSend, 1023); //this will transmit a signal to Block B
  delay(200);

  if ((valA1<500) && (valA2>HIGH)){
    signalState = ST_RR3; //switched to transition Red signal state
  }
}

void signalrr3(int valA1, int valA2, int valA3, int valA4){
  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, HIGH);
  digitalWrite(Red1, LOW);//Sets Red1 to ON
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, HIGH);
  digitalWrite(Red2, LOW);//Sets Red2 to ON
  digitalWrite(blockASend, HIGH); //this will transmit a signal to Block A
  digitalWrite(blockBSend, HIGH); //this will transmit a signal to Block B
  delay(200);

  if ((valA1>500) && (valA2>500)){
    signalState = ST_YY1;
  }
}

void signalyy1(int valA1, int valA2, int valA3, int valA4){
  digitalWrite(Green1, HIGH);
  digitalWrite(Yellow1, LOW);
  digitalWrite(Red1, HIGH);
  digitalWrite(Green2, HIGH);
  digitalWrite(Yellow2, LOW);
  digitalWrite(Red2, HIGH);
  digitalWrite(blockASend, HIGH); //this will transmit a signal to Block A
  digitalWrite(blockBSend, HIGH); //this will transmit a signal to Block B
  delay(1000);

    if ((valA1>500) && (valA2>500) && (clearcount<5)){
    clearcount++;
    }
    else if((valA1<500) || (valA2<500) && clearcount<5){ clearcount=0;
    }
    else if((valA1>500) && (valA2>500) && (clearcount>4)){
   signalState = ST_GG;
    }
  
}
