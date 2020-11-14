/*********************************************************************
  Light Control
  
  Beleuchtungssteuerung für Modellschiff. Über Signale werden Lichtsituationen aus einzelnen LEDs angesteuert und aufgerufen.
  
  Light control for rc model boat. 
  
  CC-BY SA 2020 Kai Laborenz
*********************************************************************/

int timer = 1000;           // The higher the number, the slower the timing.

int navLights[6] = {0,0,0,0,0,0};
int posLights[2] = {0,0};
int topLights[2] = {0,0};
int backLights[2] = {0,0};
int searchLight = 0;
int radar = 0;

const int offLights[6] = {0,0,0,0,0,0};
const int onLights[6] = {1,1,1,1,1,1};
const int diveLights[6] = {1,0,1,0,1,0};

const int smallOffLights[2] = {0,0};
const int smallOnLights[2] = {1,1};



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
      memcpy (posLights, smallOnLights, sizeof posLights);
      memcpy (topLights, smallOnLights, sizeof topLights);
      memcpy (backLights, smallOnLights, sizeof backLights);
      searchLight = 0;
    break;

    // anchor  
    case 'a':
    Serial.println("Anchor");
    Serial.println(" ");
      memcpy (navLights, offLights, sizeof navLights);
      memcpy (posLights, smallOffLights, sizeof posLights);
      memcpy (topLights, smallOnLights, sizeof topLights);
      memcpy (backLights, smallOffLights, sizeof backLights);
      searchLight = 0;
    break;

    // diver operations  
    case 'd':
    Serial.println("Diving");
    Serial.println(" ");
      memcpy (navLights, diveLights, sizeof navLights);
      memcpy (posLights, smallOnLights, sizeof posLights);
      memcpy (topLights, smallOnLights, sizeof topLights);
      memcpy (backLights, smallOnLights, sizeof backLights);
      searchLight = 1;
    break;

    // test (all lights on)
    case 't':
    Serial.println("Testing");
    Serial.println(" ");
      memcpy (navLights, onLights, sizeof navLights);
      memcpy (posLights, smallOnLights, sizeof posLights);
      memcpy (topLights, smallOnLights, sizeof topLights);
      memcpy (backLights, smallOnLights, sizeof backLights);
      searchLight = 1;
    break;

     // off  
    case 'o':
    Serial.println("Off");
    Serial.println(" ");
      memcpy (navLights, offLights, sizeof navLights);
      memcpy (posLights, smallOffLights, sizeof posLights);
      memcpy (topLights, smallOffLights, sizeof topLights);
      memcpy (backLights, smallOffLights, sizeof backLights);
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
