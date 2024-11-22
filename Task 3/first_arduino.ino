const int redPin = 2;
const int greenPin = 7;
const int yellowPin = 4;

int state = 1;           // Initial state (1: Green, 2: Yellow, 3: Red)
char receivedChar;
char flag = 'g';         // Flag to manage transitions
unsigned long prevTime1 = 0; // For timing transitions
unsigned long currentTime;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
}

void loop() {
  currentTime = millis(); // Get current time

  // Handle serial input
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    if (receivedChar == '1' && state != 3) { 
      // Button pressed, prioritize transitioning to yellow
      state = 2;
      flag = 'g';
      prevTime1 = currentTime;
    }
  }

  switch (state) {
    // Case 1: Green light on
    case 1:
      digitalWrite(greenPin, HIGH);
      digitalWrite(yellowPin, LOW);
      digitalWrite(redPin, LOW);
      Serial.write('g'); // Send 'g' for green light

      if (currentTime - prevTime1 >= 5000) { // 5-second duration for green
        state = 2; // Transition to yellow light
        flag = 'g';
        prevTime1 = currentTime;
      }
      break;

    // Case 2: Yellow light on
    case 2:
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, HIGH);
      digitalWrite(redPin, LOW);
      Serial.write('y'); // Send 'y' for yellow light

      if (currentTime - prevTime1 >= 1000) { // 2-second duration for yellow
        if (flag == 'g') {
          state = 3; // Transition to red light
          prevTime1 = currentTime; // Reset the timer for red light duration
        } else if (flag == 'r') {
          state = 1; // Transition back to green light
          prevTime1 = currentTime;
        }
      }
      break;

    // Case 3: Red light on
    case 3:
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(redPin, HIGH);
      Serial.write('r'); // Send 'r' for red light

      if (currentTime - prevTime1 >= 5000) { // 5-second duration for red
        flag = 'r'; // Set flag to red
        state = 2; // Transition back to green
        prevTime1 = currentTime;
      }
      break;
  }
}
