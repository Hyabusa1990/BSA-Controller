void count_time() {
  if (count_clock && clock_time >= 0) {
    clock_time--;
    cont_ampel();
  }
  if(runTime){
    change_strDisplay = true;
  }
}


