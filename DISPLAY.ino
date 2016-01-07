void print_Display() {
  if (change_strDisplay) {
    lcd.clear();
    for (int i = 0; i < LCD_ROW; i++) {
      lcd.setCursor(0, i);
      lcd.print(strDisplay[i]);
      Serial.println(strDisplay[i]);
    }
    change_strDisplay = false;
  }
}

void display_initialScreen() {
  if (LCD_ROW >= 4) {
    strDisplay[0] = "";
    int center = (LCD_COL - 14) / 2;
    for (int i = 0; i < center; i++) {
      strDisplay[1] += " ";
    }
    strDisplay[1] += "BSA-Controller";
    strDisplay[2] = "";
    center = (LCD_COL - 16) / 2;
    for (int i = 0; i < center; i++) {
      strDisplay[3] += " ";
    }
    strDisplay[3] += "ampel.gras-it.de";
  }
  else if (LCD_ROW >= 2) {
    int center = (LCD_COL - 14) / 2;
    for (int i = 0; i < center; i++) {
      strDisplay[0] += " ";
    }
    strDisplay[0] += "BSA-Controller";

    center = (LCD_COL - 16) / 2;
    for (int i = 0; i < center; i++) {
      strDisplay[1] += " ";
    }
    strDisplay[1] += "ampel.gras-it.de";
  }
  else {
    int center = (LCD_COL - 14) / 2;
    for (int i = 0; i < center; i++) {
      strDisplay[0] += " ";
    }
    strDisplay[0] += "BSA-Controller";
  }
  change_strDisplay = true;
}

void display_Startup() {
  initial = true;
  strDisplay[0] = "1|Vorlaufzeit ";
  int center = LCD_COL - (14 + String(vorlaufzeit).length());
  for (int i = 0; i < center; i++) {
    strDisplay[0] += " ";
  }
  strDisplay[0] += String(vorlaufzeit);

  strDisplay[1] = "2|Schusszeit ";
  center = LCD_COL - (13 + String(schusszeit).length());
  for (int i = 0; i < center; i++) {
    strDisplay[1] += " ";
  }
  strDisplay[1] += String(schusszeit);

  strDisplay[2] = "3|A/B ";
  if (abcd) {
    center = LCD_COL - 8;
    for (int i = 0; i < center; i++) {
      strDisplay[2] += " ";
    }
    strDisplay[2] += "AN";
  }
  else {
    center = LCD_COL - 9;
    for (int i = 0; i < center; i++) {
      strDisplay[2] += " ";
    }
    strDisplay[2] += "AUS";
  }
  strDisplay[3] = "Weiter mit #: ";
  startup = true;
  change_strDisplay = true;
}

void display_ZeitSetting() {
  if (input_schuss) {
    strDisplay[0] = "Schusszeit:";
    strDisplay[1] = String(schusszeit) + " Sekunden";
  }
  else if (input_vorlauf) {
    strDisplay[0] = "Vorlaufzeit:";
    strDisplay[1] = String(vorlaufzeit) + " Sekunden";
  }
  strDisplay[2] = "";
  strDisplay[3] = "Bestaetigen: #";
  change_strDisplay = true;
}

void display_Ampel() {
  int line1 = 0;
  strDisplay[0] = "";
  if (abcd) {
    line1 = 3;
    if (ab) {
      strDisplay[0] = "A/B";
    }
    else {
      strDisplay[0] = "C/D";
    }
  }

  if (state_Red) {
    for (int i = 0; i < (LCD_COL - (3 + line1)); i++) {
      strDisplay[0] += " ";
    }
    strDisplay[0] += "ROT";
  }
  else if (state_Yellow) {
    for (int i = 0; i < (LCD_COL - (4 + line1)); i++) {
      strDisplay[0] += " ";
    }
    strDisplay[0] += "GELB";
  }
  else if (state_Green) {
    for (int i = 0; i < (LCD_COL - (5 + line1)); i++) {
      strDisplay[0] += " ";
    }
    strDisplay[0] += "Gruen";
  }
  strDisplay[1] = "";
  int center = (LCD_COL - String(clock_time).length()) / 2;
  for (int i = 0; i < center; i++) {
    strDisplay[1] += " ";
  }
  strDisplay[1] += String(clock_displ);

  int line3 = String(vorlaufzeit).length();
  strDisplay[2] = String(vorlaufzeit);
  for (int i = 0; i < (LCD_COL - (String(schusszeit).length() + line3)); i++) {
    strDisplay[2] += " ";
  }
  strDisplay[2] += String(schusszeit);

  strDisplay[3] = "Menue mit #";
}

