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
  
  if(first_load == 0) {
    crossFade(off, red, 50, 5);
    delay(1000);
    drawLogo();c
    delay(1000);
    first_load = 1;
  } 

  if (rightValue > 0) {
    drawRight(10);
  }
  
  if (leftValue > 0) {
    drawLeft(10);
  }
  
  if (first_load == 1) {
    blinkMatrix(white);
  }
  
}

// Blinking bike light, blinks color sent on line above
void blinkMatrix(RGB color) {
  matrix.fillScreen(matrix.Color(color.r, color.g, color.b));
  matrix.show();
  delay(500);
  matrix.fillScreen(matrix.Color(0, 0, 0));
  matrix.show();
  delay(250);
}

// Fade pixel (x, y) from startColor to endColor
void fadePixel(int x, int y, RGB startColor, RGB endColor, int steps, int wait) {
  for(int i = 0; i <= steps; i++) 
  {
     int newR = startColor.r + (endColor.r - startColor.r) * i / steps;
     int newG = startColor.g + (endColor.g - startColor.g) * i / steps;
     int newB = startColor.b + (endColor.b - startColor.b) * i / steps;
     
     matrix.drawPixel(x, y, matrix.Color(newR, newG, newB));
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

void drawLogo() {
  // This 8x8 array represents the LED matrix pixels. 
  // A value of 1 means we’ll fade the pixel to white
  int logo[8][8] = {  
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 0, 0, 0, 0, 0, 0, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 1, 1, 0, 0, 1, 1, 0},
   {0, 0, 0, 0, 0, 0, 0, 0}
  };
   
  for(int row = 0; row < 8; row++) {
    for(int column = 0; column < 8; column++) {
     if(logo[row][column] == 1) {
       fadePixel(column, row, red, white, 120, 0);
     }
   }
  }
}

void drawRight(int time) {
  int arr_right[8][8] = {  
   {0, 0, 0, 0, 1, 0, 0, 0},
   {0, 0, 0, 0, 1, 1, 0, 0},
   {0, 0, 0, 0, 1, 1, 1, 0},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {0, 0, 0, 0, 1, 1, 1, 0},
   {0, 0, 0, 0, 1, 1, 0, 0},
   {0, 0, 0, 0, 1, 0, 0, 0}
  };
  
  // Loop the drawing x seconds - defined by int time
  for (int secs = 0; secs < time; secs++) {
    for(int row = 0; row < 8; row++) {
      for(int column = 0; column < 8; column++) {
         if(arr_right[row][column] == 1) {
           fadePixel(column, row, red, white, 0, 0);
         }
       }
    }
    delay(1000);
    matrix.fillScreen(matrix.Color(0, 0, 0));
    
  }
}

void drawLeft(int time) {
  int arr_left[8][8] = {  
   {0, 0, 0, 1, 0, 0, 0, 0},
   {0, 0, 1, 1, 0, 0, 0, 0},
   {0, 1, 1, 1, 0, 0, 0, 0},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {1, 1, 1, 1, 1, 1, 1, 1},
   {0, 1, 1, 1, 0, 0, 0, 0},
   {0, 0, 1, 1, 0, 0, 0, 0},
   {0, 0, 0, 1, 0, 0, 0, 0}
  };
   
  for (int secs = 0; secs < time; secs++) {
    for(int row = 0; row < 8; row++) {
      for(int column = 0; column < 8; column++) {
         if(arr_left[row][column] == 1) {
           fadePixel(column, row, red, white, 0, 0);
         }
       }
    }
    delay(1000);
    matrix.fillScreen(matrix.Color(0, 0, 0));
  }
}