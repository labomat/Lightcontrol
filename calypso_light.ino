/*********************************************************************
  Light Control
  
  Beleuchtungssteuerung für Modellschiff. Über Signale werden Lichtsituationen aus einzelnen LEDs angesteuert und aufgerufen.
  
  Light control for rc model boat. 
  
  CC-BY SA 2020 Kai Laborenz
*********************************************************************/

int timer = 1000;           // The higher the number, the slower the timing.

int navLights[6] = {0,0,0,0,0,0};   // Array of 6 navigation (colreg) light on observation bridge port side
int posLights[2] = {0,0};           // position lights on both sides of the main bridge (na)
int topLights[2] = {0,0};           // 2 front facing toplights on observation bridge
int backLights[2] = {0,0};          // 2 front facing toplights on observation bridge (na)

int searchLight = 0;                // front facing search light on observation bridge
int radar = 0;

const int offLights[6] = {0,0,0,0,0,0};   // all lights off
const int onLights[6] = {1,1,1,1,1,1};    // all lights on
const int diveLights[6] = {1,0,1,0,1,0};  // pattern for signal "diver in water": red-white-red


void setup() {
  Serial.begin(9600);
  // use a for loop to initialize each pin as an output:
  for (int thisPin = 2; thisPin < 12; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }
}



void loop() {

 if (Serial.available() > 0) {
    int navstate = Serial.read();  

switch (navstate)
  {
    // cruise  
    case 'c':
    Serial.println("Cruise");
    Serial.println(" ");
      memcpy (navLights, offLights, sizeof navLights);
      memcpy (posLights, onLights, sizeof posLights);
      memcpy (topLights, onLights, sizeof topLights);
      memcpy (backLights, onLights, sizeof backLights);
      searchLight = 0;
    break;

    // anchor  
    case 'a':
    Serial.println("Anchor");
    Serial.println(" ");
      memcpy (navLights, offLights, sizeof navLights);
      memcpy (posLights, offLights, sizeof posLights);
      memcpy (topLights, offLights, sizeof topLights);
      memcpy (backLights, offLights, sizeof backLights);
      searchLight = 0;
    break;

    // diver operations  
    case 'd':
    Serial.println("Diving");
    Serial.println(" ");
      memcpy (navLights, diveLights, sizeof navLights);
      memcpy (posLights, onLights, sizeof posLights);
      //memcpy (topLights, onLights, sizeof topLights);
      memcpy (backLights, onLights, sizeof backLights);
      searchLight = 0;
    break;

    // test (all lights on)
    case 't':
    Serial.println("Testing");
    Serial.println(" ");
      memcpy (navLights, onLights, sizeof navLights);
      memcpy (posLights, onLights, sizeof posLights);
      memcpy (topLights, onLights, sizeof topLights);
      memcpy (backLights, onLights, sizeof backLights);
      searchLight = 1;
    break;

     // off  
    case 'o':
    Serial.println("Off");
    Serial.println(" ");
      memcpy (navLights, offLights, sizeof navLights);
      memcpy (posLights, offLights, sizeof posLights);
      memcpy (topLights, offLights, sizeof topLights);
      memcpy (backLights, offLights, sizeof backLights);
      searchLight = 0;
    break;   

    // deck light
    case 'l':
    Serial.println("Searchlight");
    Serial.println(" ");
    if (searchLight == 0) {
      searchLight = 1;
    }
    else {
      searchLight = 0;
    }
    break;

    // radar
    case 'r':
    Serial.println("Radar");
    Serial.println(" ");
    if (radar == 0) {
      radar = 1;
      analogWrite(11,64);
    }
    else {
      radar = 0;
      analogWrite(11,0);
    }
    break;


    
 }
  
  Serial.println("Navlights");
  for (int thisPin = 2; thisPin < 8; thisPin++) {
    digitalWrite(thisPin,navLights[thisPin-2]);
    Serial.print(thisPin);
    Serial.print(": ");
    Serial.println(navLights[thisPin-2]);
  }

    Serial.println("Toplights");
    for (int thisPin = 8; thisPin < 10; thisPin++) {
    digitalWrite(thisPin,topLights[thisPin-8]);
    Serial.print(thisPin);
    Serial.print(": ");
    Serial.println(topLights[thisPin-8]);
  }
    
    Serial.print("Searchlight: ");
    Serial.println(searchLight);
    digitalWrite(10,searchLight);

 }
}
