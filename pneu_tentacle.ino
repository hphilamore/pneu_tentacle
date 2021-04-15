int t1 = 0;   // declares variable t1
int t2 = 0;   // declares variable t2

int incomingByte = 0; // for incoming serial data
const int BUFFER_SIZE = 3;
char buf[BUFFER_SIZE];

bool val;
int n_bytes;

//int A_on = A1;
//int A_pump = 12;
//int A_valve = 11;

static const uint8_t button_pins[] = {A1,A2,A3};
int valve_pins[] = {11, 9, 7};
int pump_pins[] = {12, 10, 8};
int button_vals[3];

void setup() {
  //Serial.begin(9600);
  Serial.begin(57600);

  // Setup pins for input
  //  pinMode(A_on, INPUT); 
  //  pinMode(A_pump, OUTPUT);
  //  pinMode(A_valve, OUTPUT); 
  for (int i = 0; i < 3; i++) {
    pinMode(button_pins[i], INPUT);
    pinMode(valve_pins[i], OUTPUT);
    pinMode(pump_pins[i], OUTPUT);
  }
  
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
  //  while(digitalRead(A_on) == HIGH){   // when button pressed...
  //      digitalWrite(A_valve,HIGH);      // normally open valve = closed, (PNP transistor)
  //      digitalWrite(A_pump, HIGH);     // switch pump on
  //      Serial.println("inflate");
  //      }
  //
  //  // when button released...
  //  Serial.println("deflate");
  //  //digitalWrite(A_valve, HIGH);  // normally open valve = open, (PNP transistor)
  //  digitalWrite(A_pump, LOW);    // switch pump off
  //  while(digitalRead(A_on) == LOW){   // when button pressed...
  //      valve_pwm();
  //      }


  // MULTIPLE PUMP + VALVE INFLATE AND DEFLATE  
  for (int i = 0; i < 3; i++) {
    button_vals[i] = digitalRead(button_pins[i]);
//    Serial.print(button_vals[0]);
//    Serial.print(button_vals[1]);
//    Serial.println(button_vals[2]);
    digitalWrite(pump_pins[i], bool(button_vals[i]));
    digitalWrite(valve_pins[i], bool(button_vals[i])); 
  }

  
//  // MULTIPLE PUMP + VALVE INFLATE AND DEFLATE, CONTORLLED BY SERIAL
//  if (Serial.available()) {
//        
//    n_bytes = Serial.readBytes(buf, BUFFER_SIZE);
//    //digitalWrite(LED_BUILTIN, bool(buf[1]));   // turn the LED on (HIGH is the voltage level)
//
//    for (int i = 0; i < 3; i++){
//      //digitalWrite(LED_pins[i], bool(buf[i])); 
//      if (buf[i] > 50) { val = HIGH;}
//      else{ val = LOW;}
//      //digitalWrite(LED_pins[i], val);
//      digitalWrite(pump_pins[i], val);
//      digitalWrite(valve_pins[i], val); 
//      }
//    }

  //serial_control();

 }


void serial_control(){

  // MULTIPLE PUMP + VALVE INFLATE AND DEFLATE, CONTORLLED BY SERIAL
  if (Serial.available()) {
        
    n_bytes = Serial.readBytes(buf, BUFFER_SIZE);
    //digitalWrite(LED_BUILTIN, bool(buf[1]));   // turn the LED on (HIGH is the voltage level)

    for (int i = 0; i < 3; i++){
      //digitalWrite(LED_pins[i], bool(buf[i])); 
      if (buf[i] > 50) { val = HIGH;}
      else{ val = LOW;}
      //digitalWrite(LED_pins[i], val);
      digitalWrite(pump_pins[i], val);
      digitalWrite(valve_pins[i], val); 
      }
    }
  
}

void deflate_all(){
  for (int i = 0; i < 3; i++){
      //digitalWrite(LED_pins[i], bool(buf[i])); 
      digitalWrite(pump_pins[i], LOW);
      digitalWrite(valve_pins[i], LOW); 
  }
}


//
//void valve_pwm(){
//  digitalWrite(A_valve, LOW); // open release valve 
//  delayMicroseconds(t1);       // waits for t1 uS 
//  digitalWrite(A_valve, HIGH);  // close release valve
//  delayMicroseconds(t2);       // waits for t2 uS 
//}
