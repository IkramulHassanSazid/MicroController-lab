// C++ code
//Transmitter arduino
const int redPin = 9;
const int greenPin = 6;
const int buttonPin = 8;

char receivedChar;
unsigned long prevTime1 =0;
unsigned long currentTime;
int Led1_state = LOW; //Green LED Stete
int Led2_state =HIGH; 	//Red LED Stete
void setup()
{
    
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  digitalWrite(greenPin, Led1_state); // car green light on
  digitalWrite(redPin, Led2_state);
  
}

void loop()
{	
  
  	
   if (Serial.available() > 0) {
    char receivedChar = Serial.read();

    // Handle received characters from the first Arduino
    currentTime = millis();
     
     if (receivedChar == 'r') { 
       digitalWrite(greenPin, HIGH);
    	digitalWrite(redPin, LOW);
      if(currentTime - prevTime1 >= 5000){ 
    	    	      	
    	digitalWrite(greenPin, LOW);
    	digitalWrite(redPin, HIGH);
    	prevTime1 = currentTime;
      //Serial.write('r'); // Acknowledge to the first Arduino that it's safe to proceed
    }
           	prevTime1 = currentTime;

  }
     else{
   		digitalWrite(greenPin, LOW);
    	digitalWrite(redPin, HIGH);
   }
   }
  
	int buttonState=digitalRead(buttonPin);
    currentTime = millis();
  	if (buttonState == LOW){
  	Serial.write('1');
     }else{
    Serial.write('0');
      }
}
