#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3f, 20, 4);

struct player{
  int score = 0;
  int activity = 0;
};

#define debounce 400 
unsigned long lastPress;

bool menuActivity = true;
bool countCommandsActivity = false;
bool gameActivity = false;

bool timerActivity = false;
bool falseStartActivity = false;
bool errorResponseActivity = false;
bool roundActivity = false;

int selectedGame = 1;

int countCommand = 2;
int activeCommand = 0;
int gameRound = 0;
int gameQuestion = 0;

int roundTimeFirst = 60;
int roundTimeFalseStart = 40;
int roundTimeSecond = 20;

int roundTimeSG = 15;

int maxRoundCountHamsa = 5;
int maxQuestionsCountHamsa = 5;

int scoreIncrementBR = 20;
int scoreDecrementBR = 10;

int scoreIncrementH = 100;
int scoreDecrementH = 100;

int scoreIncrementSG = 1;
int scoreDecrementSG = 1;

player p1;
player p2;
player p3;
player p4;

void setup()
{
  Serial.begin(115200);
  lcd.begin();
  pinMode (2, INPUT);
  pinMode (3, INPUT);
  pinMode (4, INPUT);
  pinMode (5, INPUT);
  pinMode (6, INPUT);
  pinMode (7, INPUT);
  pinMode (8, INPUT);
  pinMode (9, INPUT);
  pinMode (10, INPUT);
  pinMode (13, OUTPUT);
}

int readButtons (int key)
{
  if (digitalRead(key) == HIGH)
    return true;
  if (digitalRead(key) == LOW)
    return false;
}

void PrintMenu()
{ 
  lcd.setCursor (8, 0);
  lcd.print ("MENU");
  lcd.setCursor (1, 1);
  lcd.print ("Brain-ring");
  lcd.setCursor (1, 2);
  lcd.print ("Hamsa");
  lcd.setCursor (1, 3);
  lcd.print ("Svoya igra");
  
  lcd.setCursor (0, selectedGame);
  lcd.print (">");

  SelectMenu();
}

void SelectMenu()
{
  lcd.setCursor (0, 1);
  lcd.print (" ");
  lcd.setCursor (0, 2);
  lcd.print (" ");
  lcd.setCursor (0, 3);
  lcd.print (" ");
  
  lcd.setCursor (0, selectedGame);
  lcd.print (">");
    
  if (readButtons(6) == true && millis() - lastPress > debounce) 
  {
    if (selectedGame > 1)
      selectedGame--;
  
    lastPress = millis();
  } 
  
  if (readButtons(7) == true && millis() - lastPress > debounce) 
  {
    if (selectedGame < 3)
      selectedGame++;
    lastPress = millis();
  }

  if (readButtons(8) == true && millis() - lastPress > debounce) 
  {
    menuActivity = false;
    ClearLCD();
    countCommandsActivity = true;
    lastPress = millis();
  }
}

int CountCommands()
{
  lcd.setCursor (2, 1);
  lcd.print ("Count commands:");
  
  lcd.setCursor (17, 1);
  lcd.print (countCommand);
  
  if (readButtons(6) == true && millis() - lastPress > debounce) 
  {
    if (countCommand > 2)
      countCommand--;
    lastPress = millis();
  } 
  
  if (readButtons(7) == true && millis() - lastPress > debounce) 
  {
    if (countCommand < 4)
      countCommand++;
    lastPress = millis();
  }

  if (readButtons(8) == true && millis() - lastPress > debounce) 
  {
    countCommandsActivity = false;
    ClearLCD();
    NewGame();
    gameActivity = true;
    
    lastPress = millis();
  }
}

void NewGame()
{
timerActivity = false;
falseStartActivity = false;
errorResponseActivity = false;
roundActivity = false;

activeCommand = 0;
gameRound = 0;
gameQuestion = 0;

p1.activity = 0;
p2.activity = 0;
p3.activity = 0;
p4.activity = 0;

p1.score = 0;
p2.score = 0;
p3.score = 0;
p4.score = 0;
}

String ScoreToString(int num)
{
  String S = "";

  if (num < 0 && num > -10)
    S = "   " + String(num);
  else if (num <= -10 && num > -100) 
    S =  "  " + String(num);
  else if (num <= -100 && num > -1000)
    S = " " + String(num);
  else if (num <= -1000 && num > -10000)
    S = String(num);
    
  if (num < 10 && num >= 0)
    S = "    " + String(num);
  else if (num >= 10 && num < 100) 
    S =  "   " + String(num);
  else if (num >= 100 && num < 1000)
    S = "  " + String(num);
  else if (num >= 1000 && num < 10000)
    S = " " + String(num);

    return S;
}

String ToString(int num)
{
  String S = "";
    
  if (num < 10 && num >= 0)
    S = "  " + String(num);
  else if (num >= 10 && num < 100) 
    S =  " " + String(num);
  else if (num >= 100 && num < 1000)
    S = String(num);

    return S;
}

void ClearLCD()
{
  for (int i = 0; i < 20; i++)
    for(int j = 0; j < 4; j++)
    {
      lcd.setCursor (i, j);
      lcd.print (" ");
    }
}

void PrintStatus(int gameSt)
{
  String gameStatus[] = {"NR ", "FS", "R", "A", "W", "CD"};
  
  lcd.setCursor (1, 3);
  lcd.print (gameStatus[gameSt]);
}

void PrintTimer(int sec)
{
  lcd.setCursor (2, 1);
  lcd.print (ToString(sec));
}

void PrintGame()
{
  String act[] = {" ", ">", "F", "X", "1", "2", "3", "4"};
    
  lcd.setCursor (0, 0);
  lcd.print ("R:");
  lcd.print (ToString(gameRound));
  if (gameQuestion > 0)
  {
    lcd.print (".");
    lcd.print (gameQuestion);
  }

  lcd.setCursor (0, 1);
  lcd.print ("T:");

  lcd.setCursor (0, 2);
  lcd.print ("A: ");
  lcd.print (activeCommand);
  
  lcd.setCursor (10, 0);
  lcd.print (act[p1.activity]);
  lcd.print ("K1:");
  lcd.print (ScoreToString(p1.score));

  lcd.setCursor (10, 1);
  lcd.print (act[p2.activity]);
  lcd.print ("K2:");
  lcd.print (ScoreToString(p2.score));

  if (countCommand >= 3)
  {
    lcd.setCursor (10, 2);
    lcd.print (act[p3.activity]);
    lcd.print ("K3:");
    lcd.print (ScoreToString(p3.score));
  }
  
  if (countCommand == 4)
  {
    lcd.setCursor (10, 3);
    lcd.print (act[p4.activity]);
    lcd.print ("K4:");
    lcd.print (ScoreToString(p4.score));
  }
}

void loop() 
{
  if (menuActivity == true)
    PrintMenu();
    
  if (countCommandsActivity == true)
    CountCommands();
    
  if (gameActivity == true)
    switch(selectedGame)
      {
         case 1:{
          GameBrainRing(); 
         }       
         break;
         case 2:{
          GameHamsa(); 
         }       
         break;
         case 3:{
          GameSGame(); 
         }       
         break;
      } 
}
