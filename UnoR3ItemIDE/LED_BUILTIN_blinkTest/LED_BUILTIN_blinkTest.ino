void setup() 
{
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  // 13号引脚就是LED_BUILTIN
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  delay(1000);
  Serial.println(1);
  digitalWrite(13, LOW);
  delay(2000);
  Serial.println(2);
}
