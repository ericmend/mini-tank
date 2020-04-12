int val;
int ledpin = 13;
void setup()
{
    Serial.begin(9600);
    pinMode(ledpin, OUTPUT);
}
void loop()
{
    val = Serial.read();
    if (val == 'a')
    {
        digitalWrite(ledpin, HIGH);
        delay(250);
        digitalWrite(ledpin, LOW);
        delay(250);
        Serial.println("keyestudio");
    }
}
