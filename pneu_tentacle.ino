int t1 = 0;   // declares variable t1
int t2 = 0;   // declares variable t2

int A_on = A1;
int A_pump = 12;
int A_valve = 11;


void setup() {
  Serial.begin(9600);
  pinMode(A_on, INPUT);
  pinMode(A_pump, OUTPUT);
  pinMode(A_valve, OUTPUT);
  t2= 1; //50; //100; //500;                     // duty cycle on (lower = faster deflate)
  t1= 1000-t2;                 // duty cycke off
}

void loop() {

  // BASIC PUMP ON AND OFF  
  //  if(digitalRead(A_on) == HIGH){ 
  //    digitalWrite(A_pump, HIGH); 
  //    Serial.println("high");
  //    }
  //  else{
  //   digitalWrite(A_pump, LOW); 
  //   }
  
  
  // BASIC PUMP + VALVE INFLATE AND DEFLATE
  //while(digitalRead(A_on) == HIGH){   // when button pressed...
  //    digitalWrite(A_valve,LOW);      // normally open valve = open, (PNP transistor)
  //    digitalWrite(A_pump, HIGH);     // switch pump on
  //    Serial.println("inflate");
  //    }
  //
  // // when button released...
  //Serial.println("deflate");
  //digitalWrite(A_valve, HIGH);  // normally open valve = closed, (PNP transistor)
  //digitalWrite(A_pump, LOW);    // switch pump off

  
  // PUMP + VALVE INFLATE AND DEFLATE, PWM
  
  while(digitalRead(A_on) == HIGH){   // when button pressed...
      digitalWrite(A_valve,HIGH);      // normally open valve = closed, (PNP transistor)
      digitalWrite(A_pump, HIGH);     // switch pump on
      Serial.println("inflate");
      }

  // when button released...
  Serial.println("deflate");
  //digitalWrite(A_valve, HIGH);  // normally open valve = open, (PNP transistor)
  digitalWrite(A_pump, LOW);    // switch pump off
  while(digitalRead(A_on) == LOW){   // when button pressed...
      valve_pwm();
      }
}



void valve_pwm(){
  digitalWrite(A_valve, LOW); // open release valve 
  delayMicroseconds(t1);       // waits for t1 uS 
  digitalWrite(A_valve, HIGH);  // close release valve
  delayMicroseconds(t2);       // waits for t2 uS 
}
