void GameSGame()
{  
  if (roundActivity == false && gameActivity == true)
  {
    NewRoundSG();
  } 
  else
  {
    if (readButtons(8) == true && millis() - lastPress > debounce)
    {
      if (activeCommand == 0 || roundActivity == false)
        {
          NewRoundSG();
        }
        else
        {
          StartGameSGame(roundTimeSG);
        }
      lastPress = millis();
    }
      
  }

  if (gameActivity == true)
  {
    if (readButtons(6) == true && millis() - lastPress > debounce)
    {      
      gameActivity = false;
      roundActivity = false;
      ClearLCD();
      menuActivity = true;

      lastPress = millis();
    }
    
  }
}

void NewRoundSG()
{
  roundActivity = true;
  falseStartActivity = false;
  errorResponseActivity = false;
  activeCommand = countCommand;
  
  p1.activity = 0;
  p2.activity = 0;
  p3.activity = 0;
  p4.activity = 0;
  gameRound++;
  PrintStatus(0);
  PrintGame();
  PrintTimer(roundTimeSG);
  
}

void CommandScoreSetSG(int command)
{
  PrintStatus(2);
  while(1)
  {
  switch(command){
      case 1:{
        if (p1.activity == 1)
        {
          if (readButtons(10) == true)
          {
            p1.score += scoreIncrementSG;
            roundActivity = false;
            PrintStatus(3);
            //NewRound();
            return;
          }
          if (readButtons(9) == true)
          {
            p1.activity = 3;
            p1.score -= scoreDecrementSG;
            activeCommand--;
            errorResponseActivity = true;
            PrintTimer(roundTimeSG);
            PrintStatus(4);
            return;
          }
        }
        break;
      }
      case 2:{
        if (p2.activity == 1)
        {
          if (readButtons(10) == true)
          {
            p2.score += scoreIncrementSG;
            roundActivity = false;
            PrintStatus(3);
            //NewRound();
            return;
          }
          if (readButtons(9) == true)
          {
            p2.activity = 3;
            p2.score -= scoreDecrementSG;
            activeCommand--;
            errorResponseActivity = true;
            PrintTimer(roundTimeSG);
            PrintStatus(4);
            return;
          }
        }
        break;
      }
      case 3:{
        if (p3.activity == 1)
        {
          if (readButtons(10) == true)
          {
            p3.score += scoreIncrementSG;
            roundActivity = false;
            PrintStatus(3);
            //NewRound();
            return;
          }
          if (readButtons(9) == true)
          {
            p3.activity = 3;
            p3.score -= scoreDecrementSG;
            activeCommand--;
            errorResponseActivity = true;
            PrintTimer(roundTimeSG);
            PrintStatus(4);
            return;
          }
        }
        break;
      }
      case 4:{
      if (p4.activity == 1)
        {
          if (readButtons(10) == true)
          {
            p4.score += scoreIncrementSG;
            roundActivity = false;
            PrintStatus(3);
            //NewRound();
            return;
          }
          if (readButtons(9) == true)
          {
            p4.activity = 3;
            p4.score -= scoreDecrementSG;
            activeCommand--;
            errorResponseActivity = true;
            PrintTimer(roundTimeSG);
            PrintStatus(4);
            return;
          }
        }
        break;
      }
    }
  }
}



void StartGameSGame(int sec)
{
  unsigned long prev_ms = 0;
  int s = sec + 1;
  timerActivity = true;
  while (1)
  {
    PrintStatus(5);
    if ((millis() - prev_ms) >=  1000) 
    {
      s--;
      prev_ms = millis();
      //PrintTimer(s);
      if (s == 0) roundActivity = false;
      if (timerActivity == false || s == 0) break;
      PrintTimer(s);
    }
    
    if(digitalRead(2) == HIGH && p1.activity != 2 && p1.activity != 3)
    {
      p1.activity = 1;
      timerActivity = false;
      PrintGame();
      CommandScoreSetSG(1);
    }
    if(digitalRead(3) == HIGH && p2.activity != 2 && p2.activity != 3)
      {
      p2.activity = 1;
      timerActivity = false;
      PrintGame();
      CommandScoreSetSG(2);
    }
    if (countCommand >= 3)
      if(digitalRead(4) == HIGH && p3.activity != 2 && p3.activity != 3)
      {
        p3.activity = 1;
        timerActivity = false;
        PrintGame();
        CommandScoreSetSG(3);
      }
    if (countCommand == 4)
      if(digitalRead(5) == HIGH && p4.activity != 2 && p4.activity != 3)
      {
        p4.activity = 1;
        timerActivity = false;
        PrintGame();
        CommandScoreSetSG(4);
      }
    PrintGame();
    //timerActivity = false;
  }
  //PrintGame();
}
