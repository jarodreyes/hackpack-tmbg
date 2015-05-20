#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>

#include "RGB.h"

bool first_load;

// Analog input for right & left turn button
int rightPin = A0;   
int leftPin = A1;

// Variables to store right & left input value in
int rightValue = 0;  
int leftValue = 0;

#define PIN 1

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);


void setup() {
  // Open serial port for loggin information  
  Serial.begin(9600);
  matrix.begin();
  matrix.setBrightness(50);
  matrix.setTextColor( matrix.Color(white.r, white.g, white.b) );
  matrix.setTextWrap(false);
}

void loop() {
  // Read right & left values from buttons 
  rightValue = analogRead(rightPin);
  leftValue = analogRead(leftPin);
  drawBand();
  scrollText("They Might Be Giants");
  delay(1000);

}

// Blinking bike light, blinks color sent on line above
void drawBand() {
  matrix.fillScreen(matrix.Color(0, 0, 0));
  drawT(blue);
  delay(1500);
  matrix.fillScreen(matrix.Color(0, 0, 0));
  drawM(green);
  delay(1500);
  matrix.fillScreen(matrix.Color(0, 0, 0));
  drawB(red);
  delay(1500);
  matrix.fillScreen(matrix.Color(0, 0, 0));
  drawG(yellow);
  delay(1500);
}

// Fade pixel (x, y) from startColor to endColor
void fadePixel(int x, int y, RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++) 
  {  
     matrix.drawPixel(x, y, matrix.Color(startColor.r, startColor.g, startColor.b));
     matrix.show();
     delay(wait);
  }
}

// Crossfade entire screen from startColor to endColor
void crossFade(RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++)
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;
     
     matrix.fillScreen(matrix.Color(newR, newG, newB));
     matrix.show();
     delay(wait);
  }
}



void drawT(RGB color) {
  // This 8x8 array represents the LED matrix pixels. 
  // A value of 1 means we’ll fade the pixel to white
  int letter[8][8] = {  
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {0, 0, 0, 1, 1, 0, 0, 0},
   {0, 0, 0, 1, 1, 0, 0, 0},
   {0, 0, 0, 1, 1, 0, 0, 0},
   {0, 0, 0, 1, 1, 0, 0, 0},
   {0, 0, 0, 1, 1, 0, 0, 0}
  };
   
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(letter[row][column] == 1) {
       fadePixel(column, row, color, color, 0, 0);
     }
   }
  }
}

void drawM(RGB color) {
  // This 8x8 array represents the LED matrix pixels. 
  // A value of 1 means we’ll fade the pixel to white
  int letter[8][8] = {  
   {1, 1, 1, 0, 0, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 0, 1, 1, 0, 1, 1},
   {1, 1, 0, 1, 1, 0, 1, 1},
   {1, 1, 0, 0, 0, 0, 1, 1},
   {1, 1, 0, 0, 0, 0, 1, 1},
   {1, 1, 0, 0, 0, 0, 1, 1}
  };
   
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(letter[row][column] == 1) {
       fadePixel(column, row, color, color, 0, 0);
     }
   }
  }
}

void drawB(RGB color) {
  // This 8x8 array represents the LED matrix pixels. 
  // A value of 1 means we’ll fade the pixel to white
  int letter[8][8] = {  
   {1, 1, 1, 1, 1, 1, 0, 0},
   {1, 1, 1, 1, 1, 1, 1, 0},
   {1, 1, 1, 0, 0, 1, 1, 0},
   {1, 1, 1, 0, 0, 1, 0, 0},
   {1, 1, 1, 1, 1, 1, 0, 0},
   {1, 1, 1, 0, 0, 1, 1, 0},
   {1, 1, 1, 1, 1, 1, 1, 0},
   {1, 1, 1, 1, 1, 1, 0, 0}
  };
   
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(letter[row][column] == 1) {
       fadePixel(column, row, color, color, 0, 0);
     }
   }
  }
}

void drawG(RGB color) {
  // This 8x8 array represents the LED matrix pixels. 
  // A value of 1 means we’ll fade the pixel to white
  int letter[8][8] = {  
   {1, 1, 1, 1, 1, 1, 1, 0},
   {1, 1, 1, 1, 1, 1, 1, 0},
   {1, 1, 0, 0, 0, 0, 0, 0},
   {1, 1, 0, 0, 1, 1, 1, 1},
   {1, 1, 0, 0, 1, 1, 1, 1},
   {1, 1, 0, 0, 0, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1}
  };
   
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(letter[row][column] == 1) {
       fadePixel(column, row, color, color, 0, 0);
     }
   }
  }
}

void scrollText(String textToDisplay) {
  int x = matrix.width();
  int pixelsInText = textToDisplay.length() * 7;
  
  matrix.setCursor(x, 0);
  matrix.print(textToDisplay);
  matrix.show();
  
  while(x > (matrix.width() - pixelsInText)) {
    matrix.fillScreen(matrix.Color(0, 0, 0));
    matrix.setCursor(--x, 0);
    matrix.print(textToDisplay);
    matrix.show();
    delay(150);
  }
}
