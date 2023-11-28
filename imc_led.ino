#include <Adafruit_NeoPixel.h>    // include Adafruit NeoPixel library
#include <avr/power.h>            // include Arduino avr library
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// define Pins & max. LED's --------------------------------------------------------------------------------------------
#define LEDPIN         6          // PIN where LED-Band is
#define NUMPIXELS      750        // How many Pixels are used?
#define SPEAKER        46         // Speaker Pin
#define SDPIN          53         // SD-Card-Slot Pin
int relay_4 = 4;                  // Pin for the Relay

// set pixels as variable for the NepPixel libary ----------------------------------------------------------------------
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

// Set Groups (in array) -----------------------------------------------------------------------------------------------
int controll_array[3]     = {0,1,2};
int moon_array[14]        = {3,4,5,6,7,8,9,10,11,12,13,14,15,16};
int tower_array[84]       = {17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100};
int imc_array[97]         = {101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197};
int city_array_1[92]      = {198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,256,257,258,259,260,261,262,263,264,265,266,267,268,269,270,271,272,273,274,275,276,277,278,279,280,281,282,283,284,285,286,287,288,289};
int city_array_2[85]      = {290,291,292,293,294,295,296,297,298,299,300,301,302,303,304,305,306,307,308,309,310,311,312,313,314,315,316,317,318,319,320,321,322,323,324,325,326,327,328,329,330,331,332,333,334,335,336,337,338,339,340,341,342,343,344,345,346,347,348,349,350,351,352,353,354,355,356,357,358,359,360,361,362,363,364,365,366,367,368,369,370,371,372,373,374};
int merkur_array[74]      = {375,376,377,378,379,380,381,382,383,384,385,386,387,388,389,390,391,392,393,394,395,396,397,398,399,400,401,402,403,404,405,406,407,408,409,410,411,412,413,414,415,416,417,418,419,420,421,422,423,424,425,426,427,428,429,430,431,432,433,434,435,436,437,438,439,440,441,442,443,444,445,446,447,448};
int galerie_array_1[81]   = {449,450,451,452,453,454,455,456,457,458,459,460,461,462,463,464,465,466,467,468,469,470,471,472,473,474,475,476,477,478,479,480,481,482,483,484,485,486,487,488,489,490,491,492,493,494,495,496,497,498,499,500,501,502,503,504,505,506,507,508,509,510,511,512,513,523,524,525,526,527,528,529,530,531,532,533,534,535,536,537,538};
int galerie_array_2[35]   = {539,540,541,542,543,544,545,546,547,548,549,550,551,552,553,554,555,556,557,558,559,560,561,562,563,564,565,566,567,568,569,570,571,572,573};
int galerie_logo_array[9] = {514,515,516,517,518,519,520,521,522};
int streets_array_1[95]   = {574,575,576,577,578,579,580,581,582,583,584,585,586,587,588,589,590,591,592,593,594,595,596,597,598,599,600,601,602,603,604,605,606,607,608,609,610,611,612,613,614,615,616,617,618,619,620,621,622,623,624,625,626,627,628,629,630,631,632,633,634,635,636,637,638,639,640,641,642,643,644,645,646,647,648,649,650,651,652,653,654,655,656,657,658,659,660,661,662,663,664,665,666,667,668};
int streets_array_2[13]   = {668,669,670,671,672,673,674,675,676,677,678,679,680};

// initial Setup -------------------------------------------------------------------------------------------------------

void setup() {
  pixels.begin();
  pixels.clear();
  // turn_all_on();
  // pixels.setBrightness(50);
  // pixels.show();

  set_basic_config();
  // pixels.setBrightness(125);
  pixels.show();
  
  Serial.begin(9600);
  //pinMode(relay_4, OUTPUT);
  //digitalWrite(relay_4, HIGH);
  //digitalWrite(relay_4, LOW);

  Serial.println("init done"); 
}

// Shuffle Function for Arrays -----------------------------------------------------------------------------------------
void shuffle(int *arr, size_t n)
{
    if (n > 1) 
    {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}

// Brightness Function -------------------------------------------------------------------------------------------------
void setPixelBrightness(uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint16_t brightness) {
  pixels.setPixelColor(n, (brightness*r/255), (brightness*g/255), (brightness*b/255));
}

// Function to controll the Blacklight ---------------------------------------------------------------------------------
void blackLight() {
  digitalWrite(relay_4, LOW);
  delay(100);
  digitalWrite(relay_4, HIGH);
}

// Function to turn all LED's off --------------------------------------------------------------------------------------
void turn_all_off(){
  for(int i=0;i<600;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
  }
} 

// Function to turn all LED's on ---------------------------------------------------------------------------------------
void turn_all_on() {
  for(int i=0;i<250;i++){
    pixels.setPixelColor(i, pixels.Color(100,0,0));
  }
  for(int i=250;i<500;i++){
    pixels.setPixelColor(i, pixels.Color(0,100,0));
  }
  for(int i=500;i<750;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,100));
  }
}

// Function to set basic config ----------------------------------------------------------------------------------------
void set_basic_config() {
    
  // Control -----------------------------------------------------------------------------------------------------------
  for(int i=0; i<3 ;i++){
    setPixelBrightness(controll_array[i], 190,190,190, 125);
  }
  
  // Moon --------------------------------------------------------------------------------------------------------------
  for(int i=0; i<15 ;i++){
    setPixelBrightness(moon_array[i], 200,200,200, 125);
    // pixels.setPixelColor(moon_array[i], pixels.Color(200,200,200));
  }

  // Tower -------------------------------------------------------------------------------------------------------------
  // Gelb
  for(int i=0; i<18 ;i++) {
    setPixelBrightness(tower_array[i], 200,160,25, 125);
    // pixels.setPixelColor(tower_array[i], pixels.Color(200,160,25));
  }
  
  // Violett
  for(int i=18; i<36 ;i++) {
    setPixelBrightness(tower_array[i], 238,130,238, 125);
    // pixels.setPixelColor(tower_array[i], pixels.Color(238,130,238));
  }
  
  // Orange
  for(int i=36; i<53 ;i++) {
    setPixelBrightness(tower_array[i], 255,165,0, 125);
    // pixels.setPixelColor(tower_array[i], pixels.Color(255,165,0));
  }
   
  // Blau
  for(int i=53; i<70 ;i++) {
    setPixelBrightness(tower_array[i], 127,255,212, 125);
    // pixels.setPixelColor(tower_array[i], pixels.Color(127,255,212));
  }

  // Grün
  for(int i=70; i<85 ;i++) {
    setPixelBrightness(tower_array[i], 50,205,50, 125);
    // pixels.setPixelColor(tower_array[i], pixels.Color(50,205,50));
  }
  
  // IMC ---------------------------------------------------------------------------------------------------------------
  for(int i=0; i<99 ;i++){
    setPixelBrightness(imc_array[i], 200,160,25, 125);
    // pixels.setPixelColor(imc_array[i], pixels.Color(200,160,25));
  } 

  //City --------------------------------------------------------------------------------------------------------------
  for(int i=0; i<93 ;i++){
    setPixelBrightness(city_array_1[i],200,160,25, 125);
    // pixels.setPixelColor(city_array_1[i], pixels.Color(200,160,25));
  } 

  for(int i=0; i<86 ;i++){
    setPixelBrightness(city_array_2[i], 200,160,25, 125);
    // pixels.setPixelColor(city_array_2[i], pixels.Color(200,160,25));
  } 
  
  // Hotel -------------------------------------------------------------------------------------------------------------
  shuffle(merkur_array, 74);
  for(int i=0; i<30 ;i++){
    setPixelBrightness(merkur_array[i], 190,190,190, 100);
    // pixels.setPixelColor(merkur_array[i], pixels.Color(190,190,190));
  } 
  for(int i=30; i<75 ;i++){
    setPixelBrightness(merkur_array[i], 0,0,63, 25);
    // pixels.setPixelColor(merkur_array[i], pixels.Color(0,0,63));
  }

  // Galerie -----------------------------------------------------------------------------------------------------------
  for(int i=0; i<82 ;i++){
    setPixelBrightness(galerie_array_1[i], 200,160,25, 125);
    // pixels.setPixelColor(galerie_array_1[i], pixels.Color(200,160,25));
  }

  for(int i=0; i<10 ;i++){
    setPixelBrightness(galerie_logo_array[i], 255,0,0, 125);
    // pixels.setPixelColor(galerie_logo_array[i], pixels.Color(255,0,0));
  } 

  for(int i=0; i<36 ;i++){
    setPixelBrightness(galerie_array_2[i], 200,160,25, 125);
    // pixels.setPixelColor(galerie_array_2[i], pixels.Color(200,160,25));
  }

  // Streets -----------------------------------------------------------------------------------------------------------
  for(int i=0; i<96 ;i++) {
    setPixelBrightness(streets_array_1[i], 255,120,0, 125);
    // pixels.setPixelColor(streets_array[i], pixels.Color(255,120,0));
  }
  for(int i=0; i<14 ;i++) {
    setPixelBrightness(streets_array_2[i], 255,120,0, 125);
    // pixels.setPixelColor(streets_array[i], pixels.Color(255,120,0));
  }
}

// Function to set basic config ----------------------------------------------------------------------------------------
void setFadeFromTo(uint16_t bright) {
    
  // Control -----------------------------------------------------------------------------------------------------------
  for(int i=0; i<3 ;i++){
    setPixelBrightness(controll_array[i], 190,190,190, 125);
  }
  
  // Moon --------------------------------------------------------------------------------------------------------------
  for(int i=0; i<15 ;i++){
    setPixelBrightness(moon_array[i], 200,200,200, bright);
    // pixels.setPixelColor(moon_array[i], pixels.Color(200,200,200));
  }

  // Tower -------------------------------------------------------------------------------------------------------------
  // Gelb
  for(int i=0; i<18 ;i++) {
    setPixelBrightness(tower_array[i], 200,160,25, bright);
    // pixels.setPixelColor(tower_array[i], pixels.Color(200,160,25));
  }
  
  // Violett
  for(int i=18; i<36 ;i++) {
    setPixelBrightness(tower_array[i], 238,130,238, bright);
    // pixels.setPixelColor(tower_array[i], pixels.Color(238,130,238));
  }
  
  // Orange
  for(int i=36; i<53 ;i++) {
    setPixelBrightness(tower_array[i], 255,165,0, bright);
    // pixels.setPixelColor(tower_array[i], pixels.Color(255,165,0));
  }
   
  // Blau
  for(int i=53; i<70 ;i++) {
    setPixelBrightness(tower_array[i], 127,255,212, bright);
    // pixels.setPixelColor(tower_array[i], pixels.Color(127,255,212));
  }

  // Grün
  for(int i=70; i<85 ;i++) {
    setPixelBrightness(tower_array[i], 50,205,50, bright);
    // pixels.setPixelColor(tower_array[i], pixels.Color(50,205,50));
  }
  
  // IMC ---------------------------------------------------------------------------------------------------------------
  for(int i=0; i<99 ;i++){
    setPixelBrightness(imc_array[i], 200,160,25, bright);
    // pixels.setPixelColor(imc_array[i], pixels.Color(200,160,25));
  } 

  //City --------------------------------------------------------------------------------------------------------------
  for(int i=0; i<93 ;i++){
    setPixelBrightness(city_array_1[i],200,160,25, bright);
    // pixels.setPixelColor(city_array_1[i], pixels.Color(200,160,25));
  } 

  for(int i=0; i<86 ;i++){
    setPixelBrightness(city_array_2[i], 200,160,25, bright);
    // pixels.setPixelColor(city_array_2[i], pixels.Color(200,160,25));
  } 
  
  // Hotel -------------------------------------------------------------------------------------------------------------
  /*
  for(int i=0; i<30 ;i++){
    setPixelBrightness(merkur_array[i], 190,190,190, 100);
    // pixels.setPixelColor(merkur_array[i], pixels.Color(190,190,190));
  } 
  for(int i=30; i<75 ;i++){
    setPixelBrightness(merkur_array[i], 0,0,63, 100);
    // pixels.setPixelColor(merkur_array[i], pixels.Color(0,0,63));
  }
  */
  // Galerie -----------------------------------------------------------------------------------------------------------
  for(int i=0; i<82 ;i++){
    setPixelBrightness(galerie_array_1[i], 200,160,25, bright);
    // pixels.setPixelColor(galerie_array_1[i], pixels.Color(200,160,25));
  }

  for(int i=0; i<10 ;i++){
    setPixelBrightness(galerie_logo_array[i], 255,0,0, bright);
    // pixels.setPixelColor(galerie_logo_array[i], pixels.Color(255,0,0));
  } 

  for(int i=0; i<36 ;i++){
    setPixelBrightness(galerie_array_2[i], 200,160,25, bright);
    // pixels.setPixelColor(galerie_array_2[i], pixels.Color(200,160,25));
  }

  // Streets -----------------------------------------------------------------------------------------------------------
  for(int i=0; i<96 ;i++) {
    setPixelBrightness(streets_array_1[i], 255,120,0, bright);
    // pixels.setPixelColor(streets_array[i], pixels.Color(255,120,0));
  }
  for(int i=0; i<14 ;i++) {
    setPixelBrightness(streets_array_2[i], 255,120,0, bright);
    // pixels.setPixelColor(streets_array[i], pixels.Color(255,120,0));
  }
}

// MAIN LOOP FUNCTION --------------------------------------------------------------------------------------------------
void loop() {
  
  Serial.println("STEP1: START");
  
  for (int i=125; i<226; i++) {
    setFadeFromTo(i);
    pixels.show();
  }

  Serial.println("STEP1: OK!");
  Serial.println("STEP2: START");

  for (int y=0; y<10; y++) {
    
    shuffle(merkur_array, 74);
    for (int x=1; x<2; x++) {
      setPixelBrightness(merkur_array[x], 190,190,190 ,200);
      pixels.show();
    }

    delay(2480);

    for (int i=0; i<1; i++) {
      setPixelBrightness(merkur_array[i], 0,0,63, 50);
      pixels.show();
    }

    delay(2480);
  }

  Serial.println("STEP2: OK!");
  Serial.println("STEP3: START");

  for (int i=225; i>24; i--) {
    setFadeFromTo(i);
    pixels.show();
  }

  Serial.println("STEP3: OK!");
  Serial.println("STEP4: START");

  delay(48000);

  Serial.println("STEP4: OK!");
  Serial.println("STEP5: START");

  for (int i=25; i<126; i++) {
    setFadeFromTo(i);
    pixels.show();
  }

  Serial.println("STEP5: OK!");
}
