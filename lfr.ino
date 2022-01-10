#define IR_SENSOR_RIGHT 11
#define IR_SENSOR_LEFT 12
#define MOTOR_SPEED 180

// Right motor
int enable_right_motor = 6;
int right_motor_pin_1 = 7;
int right_motor_pin_2 = 8;

// Left motor
int enable_left_motor = 5;
int left_motor_pin_1 = 9;
int left_motor_pin_2 = 10;

void setup() {
    TCCR0B = TCCR0B & B11111000 | B00000010;

    // put your setup code here, to run once:
    pinMode(enable_right_motor, OUTPUT);
    pinMode(right_motor_pin_1, OUTPUT);
    pinMode(right_motor_pin_2, OUTPUT);

    pinMode(enable_left_motor, OUTPUT);
    pinMode(left_motor_pin_1, OUTPUT);
    pinMode(left_motor_pin_2, OUTPUT);

    pinMode(IR_SENSOR_RIGHT, INPUT);
    pinMode(IR_SENSOR_LEFT, INPUT);
    rotateMotor(0, 0);
}

void loop() {
    int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
    int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);

    // If none of the sensors detects black line, then go straight
    if (rightIRSensorValue == LOW && leftIRSensorValue == LOW) {
        rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
    }
    // If right sensor detects black line, then turn right
    else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW) {
        rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
    }
    // If left sensor detects black line, then turn left
    else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH) {
        rotateMotor(MOTOR_SPEED, -MOTOR_SPEED);
    }
    // If both the sensors detect black line, then stop
    else {
        rotateMotor(0, 0);
    }
}

void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {

    if (rightMotorSpeed < 0) {
        digitalWrite(right_motor_pin_1, LOW);
        digitalWrite(right_motor_pin_2, HIGH);
    } else if (rightMotorSpeed > 0) {
        digitalWrite(right_motor_pin_1, HIGH);
        digitalWrite(right_motor_pin_2, LOW);
    } else {
        digitalWrite(right_motor_pin_1, LOW);
        digitalWrite(right_motor_pin_2, LOW);
    }

    if (leftMotorSpeed < 0) {
        digitalWrite(left_motor_pin_1, LOW);
        digitalWrite(left_motor_pin_2, HIGH);
    } else if (leftMotorSpeed > 0) {
        digitalWrite(left_motor_pin_1, HIGH);
        digitalWrite(left_motor_pin_2, LOW);
    } else {
        digitalWrite(left_motor_pin_1, LOW);
        digitalWrite(left_motor_pin_2, LOW);
    }
    analogWrite(enable_right_motor, abs(rightMotorSpeed));
    analogWrite(enable_left_motor, abs(leftMotorSpeed));
}
