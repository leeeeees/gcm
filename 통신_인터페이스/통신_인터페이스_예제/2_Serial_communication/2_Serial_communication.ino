int led1 = LOW;
int led2 = LOW;
int led3 = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {
  if(Serial.available()) {
    char received = Serial.read();
    if(received == '1') {
      led1 = !led1;
      digitalWrite(4, led1);
      Serial.print("LED 1 = ");
      Serial.println(led1);
    } else if(received == '2') {
      led2 = !led2;
      digitalWrite(5, led2);
      Serial.print("LED 2 = ");
      Serial.println(led2);
    } else if(received == '3') {
      led3 = !led3;
      digitalWrite(6, led3);
      Serial.print("LED 3 = ");
      Serial.println(led3);
    }
  }
}

