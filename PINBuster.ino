// 2019/03/06 Jokin Astobiza
// Victsing trail camera password cracker

// Solder some wires to these buttons on the trail camera (left), and link them to the Arduino (right):
// Ground           Ground
// Ok                8
// Right             9
// Left             10
// Up               11
const byte simuOk    =  8;
const byte simuRight =  9;
const byte simuLeft  = 10;
const byte simuUp    = 11;
const byte simuDown  = 12; // finally NOT used

const byte passLength = 4; // Password length
const String alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Possible values for each digit
const byte sizeOfAlphabet = alphabet.length();
// Combinations: alphabet ^ passLength. For example 36 ^ 4 = 1,679.616 possible combinations!
// At over 3 seconds (errorDelay) per try: 58 days 07:40:48

String initString = "";
byte positions[passLength]; // just in case inicial code is not "0000", get each digit's position in alphabet

// Trial&error quick&dirty fixes...
const int pressDuration = 100;  // (ms) How long to push a button for
const int keyDelay      = 150;  // (ms) How long to wait after pushing a button
const int errorDelay    = 3000; // (ms) How long to wait for error to clear up

void setup() {
  // NEVER SET ANY OF THE PINS TO HIGH IN THIS PROGRAM, IT'LL SEND 5V TO A 3,3V BOARD! ARDUINO WILL *FRY* TRAIL CAMERA
  digitalWrite(simuUp,    LOW);
  digitalWrite(simuDown,  LOW);
  digitalWrite(simuLeft,  LOW);
  digitalWrite(simuRight, LOW);
  digitalWrite(simuOk,    LOW);

  pinMode(LED_BUILTIN, OUTPUT); // initialize digital pin LED_BUILTIN as an output (pin 13 is wired to internal LED)

  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps

  // Use ONLY one of the following options: A)Start from 0, or B)Set an initial combination
  // A) "0" x passLength
  //for (byte count=0; count<passLength; count++) initString = initString + String("0"); // Default would be something like: "000", "0000", "00000"
  // B) Set custom combination
  initString = "0ZZW"; // set a custom one (helpfull for debugging)

  Serial.println(alphabet + " Size: " + String(sizeOfAlphabet) + " Initial code: " + String(initString));

  for (byte cont=0; cont<passLength; cont++)
    positions[cont] = alphabet.indexOf(initString[cont]);

  Serial.println("Setting each digit in its position:");
  for (byte digit=0; digit<passLength; digit++) { // loop through all the digits
    Serial.print("Digit " + String(digit+1) + "/" + passLength + " to " + String(initString[digit]) + " (" + alphabet.indexOf(initString[digit]) + " positions)...");
    for (byte skipper=0; skipper<positions[digit]; skipper++) // Setting each character as desired
      pressButton(simuUp);
    Serial.println(" Done");
    pressButton(simuRight); // Skip to next digit
  }
}

void loop() {
  byte loopLimit[passLength];
  for (byte count=0; count<passLength; count++) { // loop through all the digits
    loopLimit[count] = sizeOfAlphabet-positions[count];
  }
  
  Serial.println("Main program running!");
  for (byte loop0=0; loop0<loopLimit[0]; loop0++) { // First character
    pressButton(simuRight); // Skip to next digit
    for (byte loop1=0; loop1<loopLimit[1]; loop1++) { // Second character
      pressButton(simuRight); // Skip to next digit
      for (byte loop2=0; loop2<loopLimit[2]; loop2++) { // Third character
        pressButton(simuRight); // Skip to next digit
        for (byte loop3=0; loop3<loopLimit[3]; loop3++) { // Fourth character
          pressButton(simuOk); // Try the combination
          digitalWrite(LED_BUILTIN, HIGH); // turn the LED on
          delay(errorDelay); // Wait for error to clear up
          pressButton(simuUp); // skip to next character in our alphabet
          digitalWrite(LED_BUILTIN, LOW); // turn the LED off
        }
        pressButton(simuLeft);
        pressButton(simuUp);
        loopLimit[3] = sizeOfAlphabet-1;
      }
      pressButton(simuLeft);
      pressButton(simuUp);
      loopLimit[2] = sizeOfAlphabet-1;
    }
    pressButton(simuLeft);
    pressButton(simuUp);
    loopLimit[1] = sizeOfAlphabet-1;
  }
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on 

  Serial.print("Program finished, stopping!");
  exit(0);  //STOP!
}

void pressButton(byte myBbutton) { // simulate button press by going low and then opened again
  pinMode(myBbutton, OUTPUT);     // Push the button. Pull the signal low to activate the power button
  delay(pressDuration);           // Wait a moment while pushing the button (ms)
  pinMode(myBbutton, INPUT);      // Release the power button.
  delay(keyDelay);                // Delay a moment to unknowledge button press
}

// this function is finally not really used...
void blinkLED(int delayMS) {
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on
  delay(delayMS);                  // wait for delayMS
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off
}
