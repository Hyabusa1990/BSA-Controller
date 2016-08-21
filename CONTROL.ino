void cont_startup() {
  if (startup) {
    char key = keypad.getKey();
    if (key != NO_KEY) {
      switch (key) {
        case '1':
          input_vorlauf = true;
          startup = false;
          vorlaufzeit = 0;
          display_ZeitSetting();
          break;
        case '2':
          input_schuss = true;
          startup = false;
          schusszeit = 0;
          display_ZeitSetting();
          break;
        case '3':
          abcd = !abcd;
          display_Startup();
          break;
        case '#':
          firstRunFinished = !abcd;
          startup = false;
          show_ampel = true;
          clock_time = vorlaufzeit;
          display_Ampel();
          change_strDisplay = true;
          print_Display();
          break;
        default:
          break;
      }
    }
  }
}

void cont_schuss() {
  if (input_schuss) {
    char key = keypad.getKey();
    if (key != NO_KEY && key != '#' && key != '*') {
      if (String(schusszeit).length() < 3) {
        if (schusszeit == 0) {
          schusszeit = String(key).toInt();
          display_ZeitSetting();
        }
        else {
          schusszeit = String(String(schusszeit) + key).toInt();
          display_ZeitSetting();
        }
      }
    }
    else if ( key != NO_KEY && key == '*') {
      schusszeit = 0;
      display_ZeitSetting();
    }
    else if ( key != NO_KEY && key == '#') {
      if (schusszeit == 0) {
        schusszeit = 120;
      }
      input_schuss = false;
      startup = true;
      display_Startup();
    }
  }
}

void cont_vorlauf() {
  if (input_vorlauf) {
    char key = keypad.getKey();
    if (key != NO_KEY && key != '#' && key != '*') {
      if (String(vorlaufzeit).length() < 2) {
        if (vorlaufzeit == 0) {
          vorlaufzeit = String(key).toInt();
          display_ZeitSetting();
        }
        else {
          vorlaufzeit = String(String(vorlaufzeit) + key).toInt();
          display_ZeitSetting();
        }
      }
    }
    else if ( key != NO_KEY && key == '*') {
      vorlaufzeit = 0;
      display_ZeitSetting();
    }
    else if ( key != NO_KEY && key == '#') {
      input_vorlauf = false;
      startup = true;
      display_Startup();
    }
  }
}

void cont_ampel() {
  if (count_clock && clock_time > 0) {
    if (!vorlauf) {
      clock_displ = clock_time;
      if (clock_time > 30) {
        state_Red = false;
        state_Yellow = false;
        state_Green = true;
      }
      else if (clock_time <= 30 && clock_time > 0) {
        state_Red = false;
        state_Yellow = true;
        state_Green = false;
      }
    }
    else {
      clock_displ = vorlaufzeit - clock_time;
    }
  }
  else if (count_clock) {
    if (vorlauf) {
      clock_time = schusszeit;
      vorlauf = false;
      count_Horn = 1;
    }
    else if (abcd && !firstRunFinished) {
      firstRunFinished = true;
      ab = !ab;
      clock_time = vorlaufzeit;
      vorlauf = true;
      count_Horn = 2;
    }
    else if (runTime) {
      clock_displ = schusszeit;
      count_Horn = 3;
      runTime = false;
    }
  }

  if (clock_time <= 0 || vorlauf) {
    state_Red = true;
    state_Yellow = false;
    state_Green = false;
  }

  if (show_ampel) {
    display_Ampel();
  }
}

void cont_horn() {
  if (count_Horn > 0 || state_Horn) {
    state_Horn = !state_Horn;
    
    if (state_Horn) {
      count_Horn--;
    }
    
    display_Ampel();
    change_strDisplay = true;
  }
}

void cont_serial() {
  String output = "";
  if(state_Red){
    output += "1";
  }
  else{
    output += "0";
  }

  if(state_Yellow){
    output += "1";
  }
  else{
    output += "0";
  }

  if(state_Green){
    output += "1";
  }
  else{
    output += "0";
  }

  if(state_Horn){
    output += "1";
  }
  else{
    output += "0";
  }

  if(abcd){
    if(ab){
      output += "1";
    }
    else{
      output += "2";
    }
  }
  else{
    output += "0";
  }

  output += String(clock_displ);

  Serial1.println(output);
}

//Funktion für die Steuerung der Ampeltaster
void cont_Inputs(){
  char key = keypad.getKey();
  if(key != NO_KEY && !startup){
    //TASTER FUER STOPP
    if(key == '1' && !vorlauf){
      clock_time = 1;
    }
    //TASTER FUER START
    if(key == '3' && !runTime){
      firstRunFinished = !abcd;
      clock_time = vorlaufzeit;
      if(count_clock){
        ab = !ab;
      }
      count_clock = true;
      display_Ampel();
      count_Horn = 2;
      runTime = true;
      vorlauf = true;
      
    }
    //TASTER FUER AB/CD WECHSEL
    if(key == '5'){
      ab = !ab;
    }
    //TASTER FUER MENU
    if (key == '*' && !runTime) {
      //MENU EINBLENDEN
      display_Startup();
      print_Display();
    }
    //TASTER FUER HALT
    if(key == '0'){
      count_clock = !count_clock;
      if(count_clock){
        count_Horn = 1;
      }
      else{
        count_Horn = 5;
        state_Red = true;
        state_Yellow = false;
        state_Green = false;
      }
    }
  }
}

