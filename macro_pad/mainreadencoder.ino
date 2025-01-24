 
  void mainreadencoder(){
  
  checkModeButton();
  switch (modePushCounter) { // switch between keyboard configurations:
    case 0:
        readEncoder1();//  Application Alpha or MODE 0 ========================================================================
 break ;
 case 1:    //  Arduino shortcuts or MODE 1 ========================================================================

      readEncoder2();
  break;
}

}
