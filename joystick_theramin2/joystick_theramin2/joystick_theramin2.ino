#define ypin A1
#define xpin A0


long xval;
long yval;
long xmsg = 0;
long ymsg = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:


  xval = analogRead(xpin);
  yval = analogRead(ypin);
  //  Serial.print(xval);
  //  Serial.print(" ");
  //  Serial.println(yval);


  xmsg = map(xval, 0, 1023, 100, 255);
  ymsg = map(yval, 0, 1023, 0, 99);

  if (xmsg >= 100 && xmsg < 255) {
    Serial.write(xmsg);
  }
  if (ymsg >= 0 && ymsg < 100) {
    Serial.write(ymsg);
  }
  delay(5);


}
