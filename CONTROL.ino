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
          startup = false;
          show_ampel = true;
          clock_time = vorlaufzeit;
          display_Ampel();
          count_clock = true;
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
      if (vorlaufzeit == 0) {
        vorlaufzeit = 10;
      }
      input_vorlauf = false;
      startup = true;
      display_Startup();
    }
  }
}

void cont_ampel() {
  if (count_clock && clock_time >= 0) {
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
    if (show_ampel) {
      display_Ampel();
    }
  }
  else if (count_clock) {
    if (vorlauf) {
      clock_time = schusszeit;
      vorlauf = false;
    }
    if (clock_time <= 0) {
      state_Red = true;
      state_Yellow = false;
      state_Green = false;
    }
  }
}
