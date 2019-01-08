int orderResponse = 1;

void GameHamsa()
{  
  if (roundActivity == false && gameActivity == true)
  {
    NextQestion();
  } 
  else
  {
    OrderResponseH();

    //if (readButtons(8) == true && millis() - lastPress > debounce)
    //if ((readButtons(9) == true && millis() - lastPress > debounce) || (readButtons(10) == true && millis() - lastPress > debounce))
    {
      //if (activeCommand == 0 || roundActivity == false)
      if (activeCommand == 0)
        {
          NextQestion();
        }
        else
        {
          StartGameHamsa(0);
        }

      //lastPress = millis();
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

void NextQestion()
{
  if (gameRound == 0) gameRound = 1;
  if (gameQuestion < maxQuestionsCountHamsa)
    NewQuestionH();
   else
    NewRoundH();
}

void NewRoundH()
{
  gameRound++;
  gameQuestion = 0;
  NewQuestionH();
}

void NewQuestionH()
{
  roundActivity = true;
  errorResponseActivity = false;
  activeCommand = countCommand;
  orderResponse = 1;
  gameQuestion++;
  p1.activity = 0;
  p2.activity = 0;
  p3.activity = 0;
  p4.activity = 0;
  PrintGame();
}

void OrderResponseH()
{
  //while(1)
  {
    if (roundActivity == true) 
    {
      if(digitalRead(2) == HIGH)
      {
        OrderResponseSetH(1);
      }
        
      if(digitalRead(3) == HIGH)
      {
        OrderResponseSetH(2);
      }

      if (countCommand >= 3)
        if(digitalRead(4) == HIGH)
        {
          OrderResponseSetH(3);
        }
          
      if (countCommand == 4)
        if(digitalRead(5) == HIGH)
        {
          OrderResponseSetH(4);
        }
          
    }
  }
}

void OrderResponseSetH(int command)
{
  switch(command)
  {
      case 1:{
        if (p1.activity == 0)
        {
          p1.activity = orderResponse + 3;
          orderResponse++;
          PrintGame();
        }       
      break;
      }
      case 2:{
        if (p2.activity == 0)
        {
          p2.activity = orderResponse + 3;
          orderResponse++;
          PrintGame();
        }
      break;
      }
      case 3:{
        if (p3.activity == 0)
        {
          p3.activity = orderResponse + 3;
          orderResponse++;
          PrintGame();
        }
      break;
      }
      case 4:{
        if (p4.activity == 0)
        {
          p4.activity = orderResponse + 3;
          orderResponse++;
          PrintGame();
        }
      break;
      }
  }
}

void CommandScoreSet(int command)
{
  //while(1)
  {
  switch(command){
      case 1:{
        if (p1.activity == 4)
        {
          if (readButtons(10) == true && millis() - lastPress > debounce)
          {
            p1.score += scoreIncrementH * gameQuestion;
            roundActivity = false;
            PrintStatus(3);
            lastPress = millis();
            //NewRound();
            return;
          }
          if (readButtons(9) == true && millis() - lastPress > debounce)
          {
            p1.activity = 3;
            p1.score -= scoreDecrementH * gameQuestion;
            activeCommand--;
            orderResponse--;
            errorResponseActivity = true;
            if (p2.activity > 3) p2.activity--;
            if (p3.activity > 3) p3.activity--;
            if (p4.activity > 3) p4.activity--;
            lastPress = millis();
            PrintStatus(4);
            return;
          }
        }
        break;
      }
      case 2:{
        if (p2.activity == 4)
        {
          if (readButtons(10) == true && millis() - lastPress > debounce)
          {
            p2.score += scoreIncrementH * gameQuestion;
            roundActivity = false;
            PrintStatus(3);
            lastPress = millis();
            //NewRound();
            return;
          }
          if (readButtons(9) == true && millis() - lastPress > debounce)
          {
            p2.activity = 3;
            p2.score -= scoreIncrementH * gameQuestion;
            activeCommand--;
            orderResponse--;
            errorResponseActivity = true;
            if (p1.activity > 3) p1.activity--;
            if (p3.activity > 3) p3.activity--;
            if (p4.activity > 3) p4.activity--;
            PrintStatus(4);
            lastPress = millis();
            return;
          }
        }
        break;
      }
      case 3:{
        if (p3.activity == 4)
        {
          if (readButtons(10) == true && millis() - lastPress > debounce)
          {
            p3.score += scoreIncrementH * gameQuestion;
            roundActivity = false;
            PrintStatus(3);
            lastPress = millis();
            //NewRound();
            return;
          }
          if (readButtons(9) == true && millis() - lastPress > debounce)
          {
            p3.activity = 3;
            p3.score -= scoreIncrementH * gameQuestion;
            activeCommand--;
            orderResponse--;
            errorResponseActivity = true;
            if (p1.activity > 3) p1.activity--;
            if (p2.activity > 3) p2.activity--;
            if (p4.activity > 3) p4.activity--;
            PrintStatus(4);
            lastPress = millis();
            return;
          }
        }
        break;
      }
      case 4:{
      if (p4.activity == 4)
        {
          if (readButtons(10) == true && millis() - lastPress > debounce)
          {
            p4.score += scoreIncrementH * gameQuestion;
            roundActivity = false;
            PrintStatus(3);
            lastPress = millis();
            //NewRound();
            return;
          }
          if (readButtons(9) == true && millis() - lastPress > debounce)
          {
            p4.activity = 3;
            p4.score -= scoreIncrementH * gameQuestion;
            activeCommand--;
            orderResponse--;
            errorResponseActivity = true;
            if (p1.activity > 3) p1.activity--;
            if (p2.activity > 3) p2.activity--;
            if (p3.activity > 3) p3.activity--;
            PrintStatus(4);
            lastPress = millis();
            return;
          }
        }
        break;
      }
    }
  }
}



void StartGameHamsa(int sec)
{
  unsigned long prev_ms = 0;
  int s = sec;
  timerActivity = true;
  //while (1)
  {
    if(p1.activity == 4)
    {
      //p1.activity = 1;
      //timerActivity = false;
      PrintGame();
      CommandScoreSet(1);
    }
    if(p2.activity == 4)
      {
      //p2.activity = 1;
      //timerActivity = false;
      PrintGame();
      CommandScoreSet(2);
    }
    if (countCommand >= 3)
      if(p3.activity == 4)
      {
        //p3.activity = 1;
        //timerActivity = false;
        PrintGame();
        CommandScoreSet(3);
      }
    if (countCommand == 4)
      if(p4.activity == 4)
      {
        //p4.activity = 1;
        //timerActivity = false;
        PrintGame();
        CommandScoreSet(4);
      }
    PrintGame();
    //timerActivity = false;
  }
  //PrintGame();
}
