#include <Wire.h>
#include "Adafruit_Trellis.h"
#include <LiquidCrystal_I2C.h>;
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MOMENTARY 0
#define LATCHING 1
// set the mode here
#define MODE MOMENTARY

Adafruit_Trellis matrix1 = Adafruit_Trellis();
Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix1, &matrix0);

// set to however many you're working with here, up to 8
#define NUMTRELLIS 2
#define numKeys (NUMTRELLIS * 16)
#define INTPIN A2

int buttonPushCounter = 0;

// MIDI BASE
int chanBase = 0x94;
int noteBase = 0x01;
int noteSend = 0;
int chanSend = 0;

//MIDI DATA IN
byte incomingByte;
byte note;
byte velocity;
int statusLed = 13;   // select the pin for the LED
int action = 2; //0 =note off ; 1=note on ; 2= nada
long previousMillis = 0;
long interval = 25;

void setup() {

  lcd.init();
  lcd.backlight();
  //mySerial.begin(9600); // set up serial port for 9600 baud
  delay(500); // wait for display to boot up
  Serial.begin(31250);
  //Serial.begin(38400);

  lcd.print("FM Belfast");
  lcd.setCursor(0, 1);
  lcd.print("illumidi v3");

  // INT pin requires a pullup
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);

  // begin() with the addresses of each panel in order
  // I find it easiest if the addresses are in order
  //trellis.begin(0x70);  // only one
  trellis.begin(0x71, 0x72);  // or four!

  // light up all the LEDs in order
  for (uint8_t i = 0; i < numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();
    delay(5);
  }
  // then turn them off
  for (uint8_t i = 0; i < numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();
    delay(5);
  }
}



void loop() {

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // wait for as status-byte, channel 1, note on or off
    if (incomingByte == 144) { // note on message starting starting
      action = 1;
      //digitalWrite(statusLed,HIGH);
      //     DmxSimple.write(1, 255);
    } else if (incomingByte == 128) { // note off message starting
      action = 0;
      //digitalWrite(statusLed,LOW);
      //     DmxSimple.write(1, 0);
    } else if (incomingByte == 208) { // aftertouch message starting
      //not implemented yet
    } else if (incomingByte == 160) { // polypressure message starting
      //not implemented yet
    } else if ( (action == 0) && (note == 0) ) { // if we received a "note off", we wait for which note (databyte)
      note = incomingByte;
      playNote(note, 0);
      note = 0;
      velocity = 0;
      action = 2;
    } else if ( (action == 1) && (note == 0) ) { // if we received a "note on", we wait for the note (databyte)
      note = incomingByte;
    } else if ( (action == 1) && (note != 0) ) { // ...and then the velocity
      velocity = incomingByte;
      playNote(note, velocity);
      note = 0;
      velocity = 0;
      action = 0;
    } else {
      //nada
    }
  }



  unsigned long currentMillis = millis();

  // delay(30); // 30ms delay is required, dont remove me!
  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    if (MODE == MOMENTARY) {
      // If a button was just pressed or released...
      if (trellis.readSwitches()) {
        // go through every button


        if (trellis.justPressed(0)) {
          noteOn(chanSend, noteSend + 0, 0x45);
          trellis.setLED(0);
        }
        if (trellis.justReleased(0)) {
          noteOn(chanSend, noteSend + 0, 0x00);
          trellis.clrLED(0);
        }
        if (trellis.justPressed(1)) {
          noteOn(chanSend, noteSend + 1, 0x45);
          trellis.setLED(1);
        }
        if (trellis.justReleased(1)) {
          noteOn(chanSend, noteSend + 1, 0x00);
          trellis.clrLED(1);
        }
        if (trellis.justPressed(2)) {
          noteOn(chanSend, noteSend + 2, 0x45);
          trellis.setLED(2);
        }
        if (trellis.justReleased(2)) {
          noteOn(chanSend, noteSend + 2, 0x00);
          trellis.clrLED(2);
        }
        if (trellis.justPressed(3)) {
          noteOn(chanSend, noteSend + 3, 0x45);
          trellis.setLED(3);
        }
        if (trellis.justReleased(3)) {
          noteOn(chanSend, noteSend + 3, 0x00);
          trellis.clrLED(3);
        }



        if (trellis.justPressed(16)) {
          noteOn(chanSend, noteSend + 4, 0x45);
          trellis.setLED(16);
        }
        if (trellis.justReleased(16)) {
          noteOn(chanSend, noteSend + 4, 0x00);
          trellis.clrLED(16);
        }
        if (trellis.justPressed(17)) {
          noteOn(chanSend, noteSend + 5, 0x45);
          trellis.setLED(17);
        }
        if (trellis.justReleased(17)) {
          noteOn(chanSend, noteSend + 5, 0x00);
          trellis.clrLED(17);
        }
        if (trellis.justPressed(18)) {
          noteOn(chanSend, noteSend + 6, 0x45);
          trellis.setLED(18);
        }
        if (trellis.justReleased(18)) {
          noteOn(chanSend, noteSend + 6, 0x00);
          trellis.clrLED(18);
        }
        if (trellis.justPressed(19)) {
          noteOn(chanSend, noteSend + 7, 0x45);
          trellis.setLED(19);
        }
        if (trellis.justReleased(19)) {
          noteOn(chanSend, noteSend + 7, 0x00);
          trellis.clrLED(19);
        }



        if (trellis.justPressed(4)) {
          noteOn(chanSend, noteSend + 8, 0x45);
          trellis.setLED(4);
        }
        if (trellis.justReleased(4)) {
          noteOn(chanSend, noteSend + 8, 0x00);
          trellis.clrLED(4);
        }
        if (trellis.justPressed(5)) {
          noteOn(chanSend, noteSend + 9, 0x45);
          trellis.setLED(5);
        }
        if (trellis.justReleased(5)) {
          noteOn(chanSend, noteSend + 9, 0x00);
          trellis.clrLED(5);
        }
        if (trellis.justPressed(6)) {
          noteOn(chanSend, noteSend + 10, 0x45);
          trellis.setLED(6);
        }
        if (trellis.justReleased(6)) {
          noteOn(chanSend, noteSend + 10, 0x00);
          trellis.clrLED(6);
        }
        if (trellis.justPressed(7)) {
          noteOn(chanSend, noteSend + 11, 0x45);
          trellis.setLED(7);
        }
        if (trellis.justReleased(7)) {
          noteOn(chanSend, noteSend + 11, 0x00);
          trellis.clrLED(7);
        }
        if (trellis.justPressed(20)) {
          noteOn(chanSend, noteSend + 12, 0x45);
          trellis.setLED(20);
        }
        if (trellis.justReleased(20)) {
          noteOn(chanSend, noteSend + 12, 0x00);
          trellis.clrLED(20);
        }
        if (trellis.justPressed(21)) {
          noteOn(chanSend, noteSend + 13, 0x45);
          trellis.setLED(21);
        }
        if (trellis.justReleased(21)) {
          noteOn(chanSend, noteSend + 13, 0x00);
          trellis.clrLED(21);
        }
        if (trellis.justPressed(22)) {
          noteOn(chanSend, noteSend + 14, 0x45);
          trellis.setLED(22);
        }
        if (trellis.justReleased(22)) {
          noteOn(chanSend, noteSend + 14, 0x00);
          trellis.clrLED(22);
        }
        if (trellis.justPressed(23)) {
          noteOn(chanSend, noteSend + 15, 0x45);
          trellis.setLED(23);
        }
        if (trellis.justReleased(23)) {
          noteOn(chanSend, noteSend + 15, 0x00);
          trellis.clrLED(23);
        }

        //DRUM PADS
        if (trellis.justPressed(12)) {
          noteOn(0x93, 0x01, 0x45);
          trellis.setLED(12);
        }
        if (trellis.justReleased(12)) {
          noteOn(0x93, 0x01, 0x00);
          trellis.clrLED(12);
        }

        if (trellis.justPressed(13)) {
          noteOn(0x93, 0x02, 0x45);
          trellis.setLED(13);
        }
        if (trellis.justReleased(13)) {
          noteOn(0x93, 0x02, 0x00);
          trellis.clrLED(13);
        }

        if (trellis.justPressed(14)) {
          noteOn(0x93, 0x03, 0x45);
          trellis.setLED(14);
        }
        if (trellis.justReleased(14)) {
          noteOn(0x93, 0x03, 0x00);
          trellis.clrLED(14);
        }
        if (trellis.justPressed(15)) {
          noteOn(0x93, 0x04, 0x45);
          trellis.setLED(14);
        }
        if (trellis.justReleased(15)) {
          noteOn(0x93, 0x04, 0x00);
          trellis.clrLED(14);
        }
        if (trellis.justPressed(30)) {
          buttonPushCounter--;
          trellis.setLED(30);
        }
        if (trellis.justReleased(30)) {
          trellis.clrLED(30);
        }
        if (trellis.justPressed(31)) {
          buttonPushCounter++;
          trellis.setLED(31);
        }
        if (trellis.justReleased(31)) {
          trellis.clrLED(31);
        }




        lcd.setCursor(0, 0);
        lcd.clear();
        // lcd.print(254);
        // lcd.print(128);
        int songNum = 33;
        if (buttonPushCounter > songNum) {
          buttonPushCounter = 0;
        }
        if (buttonPushCounter < 0) {
          buttonPushCounter = songNum;
        }
        lcd.setCursor(0, 0);

        if (buttonPushCounter == 0) {
          lcd.print("FM BELFAST");
          lcd.setCursor(0, 1);
          lcd.print("illumidi v3");
        }
        if (buttonPushCounter == 1) {
          lcd.print("01-Lotus");
          chanSend = 0x99; // MIDI CH 10
          noteSend = 0x00;
        }
        if (buttonPushCounter == 2) {
          lcd.print("02-Par Avion");
          chanSend = 0x99;
          noteSend = 0x10;
        }
        if (buttonPushCounter == 3) {
          lcd.print("03-Tropical");
          chanSend = 0x99;
          noteSend = 0x20;
        }
        if (buttonPushCounter == 4) {
          lcd.print("04-I Can Feel Love");
          chanSend = 0x99;
          noteSend = 0x30;
        }
        if (buttonPushCounter == 5) {
          lcd.print("05-Nicole");
          chanSend = 0x99;
          noteSend = 0x40;
        }
        if (buttonPushCounter == 6) {
          lcd.print("06-Frequency");
          chanSend = 0x99;
          noteSend = 0x50;
        }
        if (buttonPushCounter == 7) {
          lcd.print("07-Underwear");
          chanSend = 0x99;
          noteSend = 0x60;
        }
        if (buttonPushCounter == 8) {
          lcd.print("08-Back and Spine");
          chanSend = 0x99;
          noteSend = 0x70;
        }
        if (buttonPushCounter == 9) {
          lcd.print("09-Synthia");
          chanSend = 0x9A;  // MIDI CH 11
          noteSend = 0x00;
        }
        if (buttonPushCounter == 10) {
          lcd.print("10-Vertigo");
          chanSend = 0x9A;
          noteSend = 0x10;
        }
        if (buttonPushCounter == 11) {
          lcd.print("11-No offense");
          chanSend = 0x9A;
          noteSend = 0x20;
        }
        if (buttonPushCounter == 12) {
          lcd.print("12-American");
          chanSend = 0x9A;
          noteSend = 0x30;
        }
        if (buttonPushCounter == 13) {
          lcd.print("13-Everything");
          chanSend = 0x9A;
          noteSend = 0x40;
        }
        if (buttonPushCounter == 14) {
          lcd.print("14-Sleep");
          chanSend = 0x9A;
          noteSend = 0x50;
        }
        if (buttonPushCounter == 15) {
          lcd.print("15-New Year");
          chanSend = 0x9A;
          noteSend = 0x60;
        }
        if (buttonPushCounter == 16) {
          lcd.print("16-In Line");
          chanSend = 0x9A;
          noteSend = 0x70;
        }
        if (buttonPushCounter == 17) {
          lcd.print("14-Stripes");
          chanSend = 0x9B;   // MIDI CH 11
          noteSend = 0x00;
        }
        if (buttonPushCounter == 18) {
          lcd.print("18-Believe");
          chanSend = 0x9B;
          noteSend = 0x10;
        }
        if (buttonPushCounter == 19) {
          lcd.print("19-DeLorean");
          chanSend = 0x9B;
          noteSend = 0x20;
        }
        if (buttonPushCounter == 20) {
          lcd.print("20-The End");
          chanSend = 0x9B;
          noteSend = 0x30;
        }
        if (buttonPushCounter == 21) {
          lcd.print("21-Brighter Days");
          chanSend = 0x9B;
          noteSend = 0x40;
        }
        if (buttonPushCounter == 22) {
          lcd.print("22-We Are Faster Than You");
          chanSend = 0x9B;
          noteSend = 0x50;
        }
        if (buttonPushCounter == 23) {
          lcd.print("23-Gold");
          chanSend = 0x9B;
          noteSend = 0x60;
        }
        if (buttonPushCounter == 24) {
          lcd.print("24-Ariel");
          chanSend = 0x9B;
          noteSend = 0x70;
        }
        if (buttonPushCounter == 25) {
          lcd.print("25-Holiday");
          chanSend = 0x9C;    // MIDI CH 12
          noteSend = 0x00;
        }
        if (buttonPushCounter == 26) {
          lcd.print("26-2 Planets");
          chanSend = 0x9C;
          noteSend = 0x10;
        }
        if (buttonPushCounter == 27) {
          lcd.print("27-Pinapple Rainbow");
          chanSend = 0x9C;
          noteSend = 0x20;
        }
        if (buttonPushCounter == 28) {
          lcd.print("28-Mondays");
          chanSend = 0x9C;
          noteSend = 0x30;
        }
        if (buttonPushCounter == 29) {
          lcd.print("29-President");
          chanSend = 0x9C;
          noteSend = 0x40;
        }
        if (buttonPushCounter == 30) {
          lcd.print("30-Lone Star State");
          chanSend = 0x9C;
          noteSend = 0x50;
        }
        if (buttonPushCounter == 31) {
          lcd.print("31-VHS");
          chanSend = 0x9C;
          noteSend = 0x60;
        }
        if (buttonPushCounter == 32) {
          lcd.print("32-We Fall");
          chanSend = 0x9C;
          noteSend = 0x70;
        }
        if (buttonPushCounter == 33) {
          lcd.print("33-Ghostbusters");
          chanSend = 0x9D;
          noteSend = 0x00;
        }
        trellis.writeDisplay();
      }
    }
  }
}

void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void playNote(byte note, byte velocity) {
  int value = LOW;
  if (velocity > 10) {
    value = HIGH;
  } else {
    value = LOW;
  }

  //since we don't want to "play" all notes we wait for a note between 36 & 44
  if (note == 36) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(0);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(0);
      trellis.writeDisplay();
    }
  }
  if (note == 37) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(1);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(1);
      trellis.writeDisplay();
    }
  }
  if (note == 38) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(2);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(2);
      trellis.writeDisplay();
    }
  }
  if (note == 39) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(3);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(3);
      trellis.writeDisplay();
    }
  }
  if (note == 40) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(16);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(16);
      trellis.writeDisplay();
    }
  }
  if (note == 41) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(17);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(17);
      trellis.writeDisplay();
    }

  }
  if (note == 42) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(18);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(18);
      trellis.writeDisplay();
    }

  }
  if (note == 43) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(19);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(19);
      trellis.writeDisplay();
    }

  }
  if (note == 44) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(4);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(4);
      trellis.writeDisplay();
    }

  }
  if (note == 45) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(5);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(5);
      trellis.writeDisplay();
    }

  }
  if (note == 46) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(6);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(6);
      trellis.writeDisplay();
    }

  }
  if (note == 47) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(7);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(7);
      trellis.writeDisplay();
    }

  }
  if (note == 48) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(20);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(20);
      trellis.writeDisplay();
    }

  }
  if (note == 49) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(21);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(21);
      trellis.writeDisplay();
    }

  }
  if (note == 50) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(22);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(22);
      trellis.writeDisplay();
    }

  }
  if (note == 51) {
    //byte myPin=note-34; // to get a pinnumber between 2 and 9
    if (value == HIGH) {
      trellis.setLED(23);
      trellis.writeDisplay();
    } else {
      trellis.clrLED(23);
      trellis.writeDisplay();
    }

  }


}
