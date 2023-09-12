/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#include <Arduino.h>
#include <stdint.h>
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Minesweeper.h"
#include <Ticker.h>
#include "device.h"
#include <Firebase_ESP_Client.h>
#include "memory.h"

// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Define Firebase Data object
FirebaseAuth auth;
FirebaseConfig config;

Ticker timerTicker;

/*variables*/
const int rowBorder = 18 * ROW;
const int columnBorder = 18 * COLUMN;
int buttonRead = NONE, lastButtonState = NONE;
int rectX = zeroX, rectY = zeroY;
int posX = 0, posY = 0;
bool counting = false, firebaseConnected = false, yes = true;
unsigned long int startTime = 0;
unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
unsigned long debounceDelay = 100;  // the debounce time; increase if the output flickers
long batas_bawah = 0;
float battery = 0;
float charged = 0;
float lastBattery = 0;
int lastSecond = 0;

/*declare functions*/
int taskButton();
int waiting_input();
void gameLoop(game g);
void draw7Number(int n, unsigned int xLoc, unsigned int yLoc, char cS, unsigned int fC, unsigned int bC, char nD);
void updateTimer();
void endMenu(bool winning);
void createScore(int score);
void helpMenu();
void connectFirebase();
void checkBattery();
void printTFT(int x, int y, int color, int size);
void charging();
void playSound(int melody[][5]);
void click_sound();

void setup()
{
  delay(3000);
  Serial.begin(115200);
  Serial.println("ILI9341 Test!");

  tft.begin();
  tft.setRotation(3);

  tft.fillScreen(ILI9341_BLACK);
  tft.drawRGBBitmap(100, 60, egra_bmp, 120, 120);
  
  pinMode(BUZZER, OUTPUT);
  playSound(logo_sound);
  delay(3000);
  tft.fillScreen(ILI9341_BLACK);
  // read diagnostics (optional but can help debug problems)
  uint8_t xu = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x");
  Serial.println(xu, HEX);
  xu = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x");
  Serial.println(xu, HEX);
  xu = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x");
  Serial.println(xu, HEX);
  xu = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x");
  Serial.println(xu, HEX);
  xu = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x");
  Serial.println(xu, HEX);
  Serial.println(F("Done!"));

  timerTicker.attach_ms(1000, updateTimer);
  randomSeed(analogRead(A1));
  tft.fillScreen(ILI9341_BLACK);
  helpMenu();

}

void loop()
{
  // digitalWrite(BUZZER, LOW);
  tft.drawRGBBitmap(0, 0, board_bmp, 320, 240); // draw background
  tft.drawRGBBitmap(17, 149, martinSwag_bmp, 70, 74);
  tft.drawRGBBitmap(233, 240 / 2 - 34, goodLuck_bmp, 70, 69);

  rectX = zeroX;
  rectY = zeroY; // cursor kotak selector
  posX = 0;
  posY = 0;

  startTime = millis();
  counting = true;
  game newGame(COLUMN, ROW);
  gameLoop(newGame);
  counting = false;
  endMenu(win);
}

int waiting_input()
{
  // Serial.println("waiting input...");
  int button = analogRead(BUTTON_READ_PIN) / 100;

  while (button < 2)
  {
    button = analogRead(BUTTON_READ_PIN) / 100;
  }

  delay(150);
  if (button < 7 && button >= 3)
  {
    // Serial.println("Button DOWN rhs clicked");
    while (button < 7 && button >= 3)
      button = analogRead(BUTTON_READ_PIN) / 100;
    click_sound();
    return DOWN_R;
  }
  else if (button < 13 && button >= 7)
  {
    // Serial.println("Button RIGHT rhs clicked");
    while (button < 13 && button >= 7)
      button = analogRead(BUTTON_READ_PIN) / 100;
    return RIGHT_R;
  }
  else if (button < 18 && button >= 13)
  {
    // Serial.println("Button LEFT rhs clicked");
    while (button < 18 && button >= 13)
      button = analogRead(BUTTON_READ_PIN) / 100;
    return LEFT_R;
  }
  else if (button < 23 && button >= 18)
  {
    // Serial.println("Button UP rhs clicked");
    while (button < 23 && button >= 18)
      button = analogRead(BUTTON_READ_PIN) / 100;
    return UP_R;
  }

  else if (button < 28 && button >= 23)
  {
    // Serial.println("Button DOWN clicked");
    while (button < 28 && button >= 23)
      button = analogRead(BUTTON_READ_PIN) / 100;
    return DOWN;
  }
  else if (button < 34 && button >= 28)
  {
    // Serial.println("Button RIGHT clicked");
    while (button < 34 && button >= 28)
      button = analogRead(BUTTON_READ_PIN) / 100;
    return RIGHT;
  }
  else if (button < 38 && button >= 34)
  {
    // Serial.println("Button LEFT clicked");
    while (button < 38 && button >= 34)
      button = analogRead(BUTTON_READ_PIN) / 100;
    return LEFT;
  }
  else if (button < 41 && button >= 38)
  {
    // Serial.println("Button UP clicked");
    while (button < 41 && button >= 38)
      button = analogRead(BUTTON_READ_PIN) / 100;
    return UP;
  }
  else
    return NONE;
}

int taskButton()
{
  for (;;)
  {
    buttonRead = waiting_input();
    // digitalWrite(BUZZER, LOW);

    tft.drawRect(rectX, rectY, boxSize + 1, boxSize + 1, ILI9341_DARKGREY);

    if (buttonRead == NONE)
    {
    }
    else if (buttonRead == UP)
    {
      rectY = zeroY + (rowBorder + ((rectY - zeroY - boxSize) % rowBorder)) % rowBorder;
      posY = (ROW + ((posY - 1) % ROW)) % ROW;
      Serial.printf("button UP clicked");
    }
    else if (buttonRead == LEFT)
    {
      rectX = zeroX + (columnBorder + ((rectX - zeroX - boxSize) % columnBorder)) % columnBorder;
      posX = (COLUMN + ((posX - 1) % COLUMN)) % COLUMN;
      Serial.printf("button LEFT clicked");
    }
    else if (buttonRead == RIGHT)
    {
      rectX = zeroX + (columnBorder + ((rectX - zeroX + boxSize) % columnBorder)) % columnBorder;
      posX = (COLUMN + ((posX + 1) % COLUMN)) % COLUMN;
      Serial.printf("button RIGHT clicked");
    }
    else if (buttonRead == DOWN)
    {
      rectY = zeroY + (rowBorder + ((rectY - zeroY + boxSize) % rowBorder)) % rowBorder;
      posY = (ROW + ((posY + 1) % ROW)) % ROW;
      Serial.printf("button DOWN clicked");
    }
    else
    {
      return buttonRead;
    }

    tft.drawRect(rectX, rectY, boxSize + 1, boxSize + 1, ILI9341_BLUE);

    // Serial.printf("pos coordinate: %d, %d\n\n", posX, posY);
  }
}

void gameLoop(game g)
{
  int act = 0;
  while (!g.go)
  {
    g.drawBoard();
    tft.drawRect(rectX, rectY, boxSize + 1, boxSize + 1, ILI9341_BLUE);
    act = taskButton();
    tft.drawRect(rectX, rectY, boxSize + 1, boxSize + 1, ILI9341_BLUE);
    // Serial.printf("action: %d, %d, %d\n", posX, posY, act);
    if (act == UP_R) // button E
      g.makeMove(posX, posY, "F");
    else if (act == LEFT_R) // button G
      helpMenu();
    else if (act == RIGHT_R) // button R
      g.makeMove(posX, posY, "?");
    else if (act == DOWN_R) // button A
      g.makeMove(posX, posY, "O");
  }
}

void draw7Number(int n, unsigned int xLoc, unsigned int yLoc, char cS, unsigned int fC, unsigned int bC, char nD)
{
  unsigned int num = abs(n), i, s, t, w, col, h, a, b, si = 0, j = 1, d = 0, S1 = cS, S2 = 5 * cS, S3 = 2 * cS, S4 = 7 * cS, x1 = (S3 / 2) + 1, x2 = (2 * S1) + S2 + 1, y1 = yLoc + x1, y3 = yLoc + (2 * S1) + S4 + 1;
  unsigned int seg[7][3] = {{(S3 / 2) + 1, yLoc, 1}, {x2, y1, 0}, {x2, y3 + x1, 0}, {x1, (2 * y3) - yLoc, 1}, {0, y3 + x1, 0}, {0, y1, 0}, {x1, y3, 1}};
  unsigned char nums[12] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67, 0x00, 0x40}, c = (c = abs(cS)) > 10 ? 10 : (c < 1) ? 1
                                                                                                                                           : c,
                cnt = (cnt = abs(nD)) > 10 ? 10 : (cnt < 1) ? 1
                                                            : cnt;
  for (xLoc += cnt * (d = (2 * S1) + S2 + (2 * S3) + 2); cnt > 0; cnt--)
  {
    for (i = (num > 9) ? num % 10 : ((!cnt) && (n < 0)) ? 11
                                : ((nD < 0) && (!num))  ? 10
                                                        : num,
        xLoc -= d, num /= 10, j = 0;
         j < 7; ++j)
    {
      col = (nums[i] & (1 << j)) ? fC : bC;
      s = (2 * S1) / S3;
      if (seg[j][2])
        for (w = S2, t = seg[j][1] + S3, h = seg[j][1] + (S3 / 2), a = xLoc + seg[j][0] + S1, b = seg[j][1]; b < h; b++, a -= s, w += (2 * s))
          tft.drawFastHLine(a, b, w, col);
      else
        for (w = S4, t = xLoc + seg[j][0] + S3, h = xLoc + seg[j][0] + S3 / 2, b = xLoc + seg[j][0], a = seg[j][1] + S1; b < h; b++, a -= s, w += (2 * s))
          tft.drawFastVLine(b, a, w, col);
      for (; b < t; b++, a += s, w -= (2 * s))
        seg[j][2] ? tft.drawFastHLine(a, b, w, col) : tft.drawFastVLine(b, a, w, col);
    }
  }
}

void updateTimer()
{
  if (counting)
  {
    int time = (millis() - startTime) / 1000.0;
    if (time > 999)
      time = 999;
    draw7Number(time, 257, 21, 1, ILI9341_RED, ILI9341_BLACK, 3);
  }
  checkBattery();
}

void endMenu(bool winning)
{
  int score = millis() - startTime;
  float displayScore = score;

  if (winning)
  {
    tft.drawRGBBitmap(145, 19, win_bmp, 30, 30);
    playSound(mcD_sound);

    tft.fillRect(320 / 2 - 64, 240 / 2 - 48, 128, 96, ILI9341_WHITE);
    tft.drawRect(320 / 2 - 64, 240 / 2 - 48, 128, 96, ILI9341_BLACK);

    printTFT(320 / 2 - 46, 240 / 2 - 36, ILI9341_BLACK, 1);
    tft.print("Congratulations!");

    printTFT(320 / 2 - 49, 240 / 2 - 24, ILI9341_BLACK, 1);
    tft.print("You won the game!");

    printTFT(320 / 2 - 38, 240 / 2 - 12, ILI9341_BLACK, 1);
    tft.print("YOUR SCORE IS");

    printTFT(320 / 2 - 14, 240 / 2, ILI9341_BLACK, 1);
    tft.printf("%.3f", displayScore / 1000.0);

    printTFT(320 / 2 - 38, 240 / 2 + 12, ILI9341_BLACK, 1);
    tft.print("UPLOAD SCORE?");

    printTFT(320 / 2 - 32, 240 / 2 + 28, ILI9341_BLACK, 1);
    tft.print("Yes");
    tft.drawRect(320 / 2 - 40, 240 / 2 + 24, 32, 16, ILI9341_BLACK);

    printTFT(320 / 2 + 19, 240 / 2 + 28, ILI9341_BLACK, 1);
    tft.print("No");
    tft.drawRect(320 / 2 + 8, 240 / 2 + 24, 32, 16, ILI9341_BLACK);

    int select = waiting_input();
    while (select != DOWN_R)
    {
      if (select == LEFT || select == RIGHT)
        yes = !yes;

      if (!yes)
      {
        tft.drawRect(320 / 2 - 40, 240 / 2 + 24, 32, 16, ILI9341_BLACK);
        tft.drawRect(320 / 2 + 8, 240 / 2 + 24, 32, 16, ILI9341_BLUE);
      }
      else
      {
        tft.drawRect(320 / 2 + 8, 240 / 2 + 24, 32, 16, ILI9341_BLACK);
        tft.drawRect(320 / 2 - 40, 240 / 2 + 24, 32, 16, ILI9341_BLUE);
      }

      select = waiting_input();
    }

    if (yes)
    {
      if (!firebaseConnected)
      {
        connectFirebase();
      }

      if (firebaseConnected)
      {
        tft.fillScreen(ILI9341_BLACK);
        tft.drawRGBBitmap(4, 240 / 2 - 43, martin_bmp, 100, 87);
        tft.drawRGBBitmap(216, 240 / 2 - 45, doraemon_bmp, 100, 97);
        tft.fillRect(320 / 2 - 64, 240 / 2 - 30, 128, 78, ILI9341_WHITE);
        tft.drawRect(320 / 2 - 64, 240 / 2 - 30, 128, 78, ILI9341_BLACK);

        printTFT(320 / 2 - 48, 240 / 2 - 6, ILI9341_BLACK, 1);
        tft.print("UPLOADING SCORE..");

        createScore(score);

        tft.fillRect(320 / 2 - 64, 240 / 2 - 30, 128, 78, ILI9341_WHITE);
        tft.drawRect(320 / 2 - 64, 240 / 2 - 30, 128, 78, ILI9341_BLACK);

        printTFT(320 / 2 - 48, 240 / 2 - 6, ILI9341_BLACK, 1);
        tft.print("UPLOADING SCORE..");

        printTFT(320 / 2 - 16, 240 / 2 + 10, ILI9341_BLACK, 1);
        tft.print("DONE !");

        printTFT(320 / 2 - 8, 240 / 2 + 28, ILI9341_BLACK, 1);
        tft.print("OK");
        tft.drawRect(320 / 2 - 16, 240 / 2 + 24, 32, 16, ILI9341_BLUE);

        int waitInput = waiting_input();
      }
    }
  }
  else
  {
    playSound(dead_sound);

    tft.drawRGBBitmap(145, 19, dead_bmp, 30, 30); // draw dead smiley

    tft.fillRect(320 / 2 - 64, 240 / 2 - 50, 128, 100, ILI9341_WHITE);
    tft.drawRect(320 / 2 - 64, 240 / 2 - 50, 128, 100, ILI9341_BLACK);

    printTFT(320 / 2 - 48, 240 / 2 - 48, ILI9341_BLACK, 1);
    tft.print("B O O O M M M M !");
    tft.drawRGBBitmap(320 / 2 - 48, 240 / 2 - 40, gameOver_bmp, 97, 50);

    printTFT(320 / 2 - 32, 240 / 2 + 12, ILI9341_BLACK, 1);
    tft.print("PLAY AGAIN?");

    printTFT(320 / 2 - 8, 240 / 2 + 28, ILI9341_BLACK, 1);
    tft.print("YES");
    tft.drawRect(320 / 2 - 16, 240 / 2 + 24, 32, 16, ILI9341_BLUE);

    int waitInput = waiting_input();
  }
}

void createScore(int score)
{
  FirebaseData fbdo;
  FirebaseJson content;

  String documentPath = "scores/Username";

  content.set("fields/isNew/booleanValue", true);
  content.set("fields/isRenamed/booleanValue", false);
  content.set("fields/score/arrayValue/values/[0]/integerValue", score);
  Serial.print("Creating document... ");

  bool success = false;
  while (!success)
  {
    if (Firebase.Firestore.createDocument(&fbdo, FIREBASE_PROJECT_ID, "", documentPath.c_str(), content.raw()))
      Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
    else
    {
      Serial.println(fbdo.errorReason());
      if (Firebase.Firestore.patchDocument(&fbdo, FIREBASE_PROJECT_ID, "" /* databaseId can be (default) or empty */, documentPath.c_str(), content.raw(), "isNew,isRenamed,score" /* updateMask */))
      {
        Serial.printf("ok\n%s\n\n", fbdo.payload().c_str());
        success = true;
      }
      else
      {
        Serial.println(fbdo.errorReason());
        // tft.fillScreen(ILI9341_BLACK);
        // tft.setTextColor(ILI9341_WHITE);
        // tft.setTextSize(3);
        // tft.setCursor(35, 90);
        // tft.println("Error! Reconnection..");
        // connectFirebase();
      }
    }
  }
}

void helpMenu()
{
  checkBattery();

  if (charged > 2900 && charged < 3200)
  {
    tft.fillRect(320 / 2 - 100, 240 / 2 - 65, 200, 130, ILI9341_WHITE);
    tft.drawRect(320 / 2 - 100, 240 / 2 - 65, 200, 130, ILI9341_BLACK);
  }
  else
  {
    tft.fillRect(320 / 2 - 100, 240 / 2 - 65, 200, 105, ILI9341_WHITE);
    tft.drawRect(320 / 2 - 100, 240 / 2 - 65, 200, 105, ILI9341_BLACK);
  }
  printTFT(320 / 2 - 28, 240 / 2 - 48, ILI9341_BLACK, 1);
  tft.print("HELP MENU");

  printTFT(320 / 2 - 95, 240 / 2 - 36, ILI9341_BLACK, 1);
  tft.print("Click button A to open");

  printTFT(320 / 2 - 95, 240 / 2 - 24, ILI9341_BLACK, 1);
  tft.print("Click button E to flag");

  printTFT(320 / 2 - 95, 240 / 2 - 12, ILI9341_BLACK, 1);
  tft.print("Click button R to mark unknown");

  printTFT(320 / 2 - 95, 240 / 2, ILI9341_BLACK, 1);
  tft.print("Click button G to open help menu");

  if (charged > 2900 && charged < 3200)
  {
    printTFT(320 / 2 - 95, 240 / 2 - 60, ILI9341_BLACK, 1);
    tft.printf("Charging.....");
    printTFT(320 / 2 - 47, 240 / 2 + 12, ILI9341_BLACK, 1);
    // tft.fillRect(320 / 2 - 50, 240 / 2 + 12, 94,8, ILI9341_BLACK);
    tft.print("You are charging");
    printTFT(320 / 2 - 95, 240 / 2 + 24, ILI9341_BLACK, 1);
    tft.print("Do you want go to charging mode?");

    printTFT(320 / 2 - 50, 240 / 2 + 45, ILI9341_BLACK, 1);
    tft.print("YES");
    tft.drawRect(320 / 2 - 58, 240 / 2 + 40, 32, 16, ILI9341_BLACK);

    printTFT(320 / 2 + 33, 240 / 2 + 45, ILI9341_BLACK, 1);
    tft.print("NO");
    tft.drawRect(320 / 2 + 22, 240 / 2 + 40, 32, 16, ILI9341_BLACK);

    int select = waiting_input();
    while (select != DOWN_R)
    {
      if (select == LEFT || select == RIGHT)
        yes = !yes;

      if (yes)
      {
        tft.drawRect(320 / 2 - 58, 240 / 2 + 40, 32, 16, ILI9341_BLACK);
        tft.drawRect(320 / 2 + 22, 240 / 2 + 40, 32, 16, ILI9341_BLUE);
      }
      else
      {
        tft.drawRect(320 / 2 + 22, 240 / 2 + 40, 32, 16, ILI9341_BLACK);
        tft.drawRect(320 / 2 - 58, 240 / 2 + 40, 32, 16, ILI9341_BLUE);
      }

      select = waiting_input();
    }

    if (!yes)
    {
      lastSecond = millis() - startTime;
      counting = false;
      do
      {
        tft.fillScreen(ILI9341_BLACK);
        tft.drawRGBBitmap(5, 5, backLogo_bmp, 20, 21);
        tft.drawRGBBitmap(160 - 38, 120 - 52, batteryChargeLogo_bmp, 76, 60);
        printTFT(160 - 96, 120 + 28, ILI9341_WHITE, 3);
        tft.printf("Charging...");

        int waitInput = waiting_input();
        tft.fillRect(320 / 2 - 100, 240 / 2 - 35, 200, 70, ILI9341_WHITE);
        tft.drawRect(320 / 2 - 100, 240 / 2 - 35, 200, 70, ILI9341_BLACK);
        printTFT(320 / 2 - 90, 240 / 2 - 25, ILI9341_BLACK, 1);
        tft.print("Do you want back to game mode?");

        printTFT(320 / 2 - 50, 240 / 2 + 16, ILI9341_BLACK, 1);
        tft.print("YES");
        tft.drawRect(320 / 2 - 58, 240 / 2 + 12, 32, 16, ILI9341_BLACK);

        printTFT(320 / 2 + 30, 240 / 2 + 16, ILI9341_BLACK, 1);
        tft.print("NO");
        tft.drawRect(320 / 2 + 22, 240 / 2 + 12, 32, 16, ILI9341_BLACK);

        int select = waiting_input();
        while (select != DOWN_R)
        {
          if (select == LEFT || select == RIGHT)
            yes = !yes;

          if (yes)
          {
            tft.drawRect(320 / 2 - 58, 240 / 2 + 12, 32, 16, ILI9341_BLACK);
            tft.drawRect(320 / 2 + 22, 240 / 2 + 12, 32, 16, ILI9341_BLUE);
          }
          else
          {
            tft.drawRect(320 / 2 + 22, 240 / 2 + 12, 32, 16, ILI9341_BLACK);
            tft.drawRect(320 / 2 - 58, 240 / 2 + 12, 32, 16, ILI9341_BLUE);
          }

          select = waiting_input();
        }
      } while (yes);

      counting = true;
      startTime = millis() - lastSecond;
    }
  }
  else
  {
    printTFT(320 / 2 - 95, 240 / 2 - 60, ILI9341_BLACK, 1);
    tft.printf("Battery = %.0f%%", battery);
    printTFT(320 / 2 - 8, 240 / 2 + 20, ILI9341_BLACK, 1);
    tft.print("OK");
    tft.drawRect(320 / 2 - 16, 240 / 2 + 16, 32, 16, ILI9341_BLUE);
    int waitInput = waiting_input();
  }

  // int waitInput = waiting_input();
  digitalWrite(BUZZER, LOW);
  tft.drawRGBBitmap(0, 0, board_bmp, 320, 240); // draw background
  tft.drawRGBBitmap(17, 149, martinSwag_bmp, 70, 74);
  tft.drawRGBBitmap(233, 240 / 2 - 34, goodLuck_bmp, 70, 69);
}

void connectFirebase()
{
  firebaseConnected = true;
  /* Connect to Wi-Fi */
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  tft.fillScreen(ILI9341_BLACK);

  printTFT(160 - 124, 50, ILI9341_WHITE, 2);
  tft.println("Connecting to Wifi...");

  unsigned long startConnecting = millis();
  while (WiFi.status() != WL_CONNECTED)
  {

    tft.drawRGBBitmap(160 - 48, 90, wiFILogo_bmp, 97, 80);
    delay(500);
    tft.drawRGBBitmap(160 - 48, 90, wiFILogo1_bmp, 97, 80);
    delay(500);
    tft.drawRGBBitmap(160 - 48, 90, wiFILogo2_bmp, 97, 80);
    delay(500);
    tft.drawRGBBitmap(160 - 48, 90, wiFILogo3_bmp, 97, 80);
    delay(500);
    tft.drawRGBBitmap(160 - 48, 90, wiFILogo4_bmp, 97, 80);
    delay(500);
    delay(500);
    Serial.print(".");

    if (millis() - startConnecting > 10000)
    {
      tft.fillScreen(ILI9341_BLACK);
      printTFT(160 - 106, 25, ILI9341_WHITE, 2);
      tft.println("Failed connecting.");
      printTFT(160 - 55, 50, ILI9341_WHITE, 2);
      tft.println("No WiFi ");
      tft.drawRGBBitmap(160 + 30, 47, sleepLogo_bmp, 20, 20);
      tft.drawRGBBitmap(160 - 48, 90, noWiFILogo_bmp, 97, 80);

      printTFT(320 / 2 - 32, 190, ILI9341_WHITE, 1);
      tft.print("Reconnect?");

      printTFT(320 / 2 - 32, 206, ILI9341_WHITE, 1);
      tft.print("Yes");
      tft.drawRect(320 / 2 - 40, 202, 32, 16, ILI9341_WHITE);

      printTFT(320 / 2 + 19, 206, ILI9341_WHITE, 1);
      tft.print("No");
      tft.drawRect(320 / 2 + 8, 202, 32, 16, ILI9341_WHITE);

      int select = waiting_input();
      while (select != DOWN_R)
      {
        if (select == LEFT || select == RIGHT)
          yes = !yes;

        if (yes)
        {
          tft.drawRect(320 / 2 - 40, 202, 32, 16, ILI9341_WHITE);
          tft.drawRect(320 / 2 + 8, 202, 32, 16, ILI9341_BLUE);
        }
        else
        {
          tft.drawRect(320 / 2 + 8, 202, 32, 16, ILI9341_WHITE);
          tft.drawRect(320 / 2 - 40, 202, 32, 16, ILI9341_BLUE);
        }

        select = waiting_input();
      }

      if (!yes)
      {
        tft.fillScreen(ILI9341_BLACK);
        printTFT(160 - 124, 60, ILI9341_WHITE, 2);
        tft.println("Connecting to Wifi...");
        Serial.println("yes reconnect to wifi");
        startConnecting = millis();
        continue;
      }
      else
      {
        firebaseConnected = false;
        break;
      }
    }
  }

  if (firebaseConnected)
  {

    Serial.println("");
    tft.fillScreen(ILI9341_BLACK);
    printTFT(160 - 81, 25, ILI9341_WHITE, 2);
    tft.println("WiFi connected");
    tft.drawRGBBitmap(160 - 48, 90, connectedWiFILogo_bmp, 97, 80);
    tft.drawRGBBitmap(4, 240 / 2 - 43, martin_bmp, 100, 87);
    tft.drawRGBBitmap(216, 240 / 2 - 45, doraemon_bmp, 100, 97);

    Serial.println("WiFi connected.");
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

    /* Assign the api key (required) */
    config.api_key = API_KEY;

    /* Assign the user sign in credentials */
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    /* Assign the callback function for the long running token generation task */
    config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    // tft.fillScreen(ILI9341_BLACK);
    // tft.setTextColor(ILI9341_WHITE);
    // tft.setTextSize(3);
    // tft.setCursor(60, 90);
    // tft.println("Firebase\n    connected");
  }

  delay(500);
}

void checkBattery()
{
  battery = ((analogRead(pinBATTERY) - 2365) / 395.0) * 100.0;
  charged = (analogRead(pinBATTERY));
  // Serial.print("%f", charged);
  if (battery > 100)
    battery = 100;
  if (battery < 0)
    battery = 0;

  if (counting)
  {
    if (charged >= 2800)
    {
      if (lastBattery <= 2800)
      {
        playSound(plug_sound);
      }
      tft.drawRGBBitmap(284, 4, batteryCharge_bmp, 19, 10);
    }
    else if (battery < 25)
    {
      if (lastBattery >= 2800)
        playSound(unplug_sound);
      tft.drawRGBBitmap(284, 4, battery25_bmp, 19, 10);
    }
    else

        if (battery >= 25 && battery < 50)
    {
      if (lastBattery >= 2800)
        playSound(unplug_sound);
      tft.drawRGBBitmap(284, 4, battery50_bmp, 19, 10);
    }
    else

        if (battery >= 50 && battery < 75)
    {
      if (lastBattery >= 2800)
        playSound(unplug_sound);
      tft.drawRGBBitmap(284, 4, battery75_bmp, 19, 10);
    }
    else
    {
      if (lastBattery >= 2800)
        playSound(unplug_sound);
      tft.drawRGBBitmap(284, 4, battery100_bmp, 19, 10);
    };
  }

  // tft.drawRGBBitmap(280, 4, battery50_bmp, 14, 7);
  // tft.fillRect(280, 20, 25, 7, ILI9341_WHITE);
  // printTFT(280, 20, ILI9341_BLACK, 1);
  // tft.printf("%.0f%%", charged);
  // battery = battery + 5;
  lastBattery = charged;
}

void charging()
{
  tft.fillScreen(ILI9341_BLACK);
};

void printTFT(int x, int y, int color, int size)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(size);
}

void playSound(int melody[][5])
{

  int size = sizeof(melody[0]) / sizeof(int);
  for (int i = 0; i < size; i++)
  {
    tone(BUZZER, melody[0][i], melody[1][i]);
    noTone(BUZZER);
    delay(melody[2][i]);
  }
}

void click_sound()
{
  tone(BUZZER, 1000, 35);
  noTone(BUZZER);
}

// TODO
// ticker utk time (done)
// jumlah sisa unmarked mine (done)
// UI win (done)
// UI booom! pake smiley dead (done)
// fix error kepotong (done)
// bunyi teken teken buzzer (done)
// berhentiin timer (done)
// send score ke firebase (done)
// menu help di awal (done)
// penggunaan button kanan & bawah (done)
// read button analog utk esp32 seed (done)
// benerin noise (done)
// benerin flickering (done)
// reconnecting (done)
// bikin logo awal x1.5 (done)

// flutter gaboleh masukkin nama username (rael)
// jumlah flag benerin (epa)
// sound effect (epa)
// rapiin code
// rapiin layout tulisan" display (done)
// benerin ok setelah done
// benerin abis charging
