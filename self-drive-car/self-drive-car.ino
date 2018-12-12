const int MotorLeftDirection2A = 2;
const int MotorLeftDirection1A = 4;
const int MotorLeftSpeed = 6;

const int MotorRightDirection4A = 12;
const int MotorRightDirection3A = 7;
const int MotorRightSpeed = 9;

const int triggerPin = 10;
const int echoPin = 11;
const int ultrasonicSource = 8;

long duration;
int distance;
unsigned long trackTime;

void setup() {
    pinMode(MotorLeftDirection1A, OUTPUT);
    pinMode(MotorLeftDirection2A, OUTPUT);
    pinMode(MotorLeftSpeed, OUTPUT);

    pinMode(MotorRightDirection4A, OUTPUT);
    pinMode(MotorRightDirection3A, OUTPUT);
    pinMode(MotorRightSpeed, OUTPUT);

    pinMode(triggerPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(ultrasonicSource, OUTPUT);
    Serial.begin(9600); // Starts the serial communication

    duration = 0;
    distance = 0;
    trackTime = 0;
}

void runForward() {
    digitalWrite(MotorLeftDirection1A, HIGH);
    digitalWrite(MotorLeftDirection2A, LOW);
    analogWrite(MotorLeftSpeed, 148);

    digitalWrite(MotorRightDirection4A, HIGH);
    digitalWrite(MotorRightDirection3A, LOW);
    analogWrite(MotorRightSpeed, 125);
}

void runBackward() {
    digitalWrite(MotorLeftDirection1A, LOW);
    digitalWrite(MotorLeftDirection2A, HIGH);
    analogWrite(MotorLeftSpeed, 148);

    digitalWrite(MotorRightDirection4A, LOW);
    digitalWrite(MotorRightDirection3A, HIGH);
    analogWrite(MotorRightSpeed, 125);
}

void turnRight() {
    digitalWrite(MotorLeftDirection1A, HIGH);
    digitalWrite(MotorLeftDirection2A, LOW);
    analogWrite(MotorLeftSpeed, 148);

    digitalWrite(MotorRightDirection4A, LOW);
    digitalWrite(MotorRightDirection3A, HIGH);
    analogWrite(MotorRightSpeed, 125);
}

void loop() {
    trackTime = millis();
    digitalWrite(ultrasonicSource, HIGH);
    runForward();

    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    if (distance < 4 && trackTime >= 500) {
        // change the direction to backward.
        runBackward();
        delay(300);
        // only turn the left wheel forward to turn right.
        turnRight();
        delay(330);
        // turn all the wheel forward.
        runForward();
    }

}
