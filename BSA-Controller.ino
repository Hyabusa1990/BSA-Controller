// ********************************************************************* 
// Includes
// ********************************************************************* 
#include <LiquidCrystal.h>
#include <Event.h>
#include <Timer.h>
#include <Keypad.h>

// ********************************************************************* 
// Initial Keypad
// ********************************************************************* 
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {28, 30, 32, 34}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {22, 24, 26}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// ********************************************************************* 
// Initial Display
// ********************************************************************* 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define LCD_COL  16
#define LCD_ROW  4

// ********************************************************************* 
// Variablen
// ********************************************************************* 
String strDisplay[LCD_ROW];
bool change_strDisplay = false;
Timer tim_initial;      //Timer für initial Bildschirm
Timer tim_counter;      //Timer für zähler
Timer tim_update;       //Timer für Schnittstellen update
Timer tim_ampel;        //Timer für Ampel update

bool initial = false;

bool startup = false;
bool input_vorlauf = false;
bool input_schuss = false;
bool show_ampel = false;

bool abcd = false;
int vorlaufzeit = 10;
int schusszeit = 120;

bool ab = true;
bool state_Red = true;
bool state_Yellow = false;
bool state_Green = false;
bool state_Horn = false;
bool count_clock = false;
bool vorlauf = true;
int clock_time = 120;
int clock_displ = 120;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd.begin(LCD_COL, LCD_ROW);
  lcd.display();
  display_initialScreen();
  tim_initial.every(10000, display_Startup, 1);
  tim_counter.every(1000, count_time);
  tim_ampel.every(10, cont_ampel);
}

void loop() {
  cont_startup();
  cont_schuss();
  cont_vorlauf();
  print_Display();
  tim_initial.update();
  tim_counter.update();
  tim_ampel.update();
}


