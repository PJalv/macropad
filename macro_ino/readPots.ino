void readPots() {

  int diff = 4; // difference amount

  // READ POTENTIOMETERS //

  checkModeButton();

  potVal1 = analogRead(pot1);

  // CALCULATE DIFFERENCE BETWEEN NEW VALUE AND LAST RECORDED VALUE //

  int potVal1diff = potVal1 - lastPotVal1;

  // SEND MIDI MESSAGE //

  if (abs(potVal1diff) >
      diff) // execute only if new and old values differ enough
  {
    switch (modePushCounter) {
    case 0:
      MIDImessage(
          179, 0,
          map(potVal1, -2, 1021, 0, 127)); // map sensor range to MIDI range
      break;
    case 1:
      int percentage =
          map(potVal1, -2, 1021, 0, 100); // map sensor range to MIDI range
      Serial.print("[Volume]: ");
      Serial.print(percentage);
      Serial.print("\n\r");
      break;
    } // switch between keyboard configurations:
    lastPotVal1 = potVal1; // reset old value with new reading
  }

  delay(2); // small delay further stabilizes sensor readings
}
