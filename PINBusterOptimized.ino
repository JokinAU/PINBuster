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

const byte passLength = 4; // Password length
const String alphabet = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Possible values for each digit
// Combinations: alphabet ^ passLength. For example 36 ^ 4 = 1,679.616 possible combinations!
// At over 3 seconds (errorDelay) per try: 58 days 07:40:48

// Trial&error quick&dirty fixes...
const int pressDuration = 100;  // (ms) How long to push a button for
const int keyDelay      = 150;  // (ms) How long to wait after pushing a button
const int errorDelay    = 3000; // (ms) How long to wait for error to clear up

void setup() {
  // NEVER SET ANY OF THE PINS TO HIGH IN THIS PROGRAM, IT'LL SEND 5V TO A 3,3V BOARD! ARDUINO WILL *FRY* TRAIL CAMERA
  digitalWrite(simuOk,    LOW);
  digitalWrite(simuRight, LOW);
  digitalWrite(simuLeft,  LOW);
  digitalWrite(simuUp,    LOW);

  runDigit(passLength);
}

void loop() {
  exit(0);  //STOP! There is no loop in this program, just a single launch
}

// AUXILIARY CUSTOM FUNCTIONS:

// A recursive function that runs each digit until the last, where it checks for each combination
void runDigit(byte deepness) {
  // If we are NOT in the first loop (because the cursor already starts at this position) skip to the next digit
  if (deepness<passLength) pressButton(simuRight);
  
  for (byte count=0; count<alphabet.length(); count++)
    if (deepness>1) runDigit(deepness-1);
    else { // If we are at the lowest level, check each combination
      pressButton(simuOk); // Try the combination
      delay(errorDelay);   // Wait for error to clear up
      pressButton(simuUp); // skip to next character in our alphabet
    }
  pressButton(simuLeft);   // Go to the previous digit
  pressButton(simuUp);     // And increase it
}

// Simulate button press by going low and then opened again
void pressButton(byte myButton) {
  pinMode(myButton, OUTPUT); // Push the button. Pull the signal low to activate the power button
  delay(pressDuration);       // Wait a moment while pushing the button (ms)
  pinMode(myButton, INPUT);  // Release the power button.
  delay(keyDelay);            // Delay a moment to unknowledge button press
}
