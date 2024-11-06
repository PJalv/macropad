/*
  The values of the two encoders are stored in an array. This
  allows the values to be remembered when changing inbetween
  encoders using the rotary switch. The rotary switch sets
  the cVal value which determines which position in the array
  the value is stored at, and retrieved from.

  While the rotary encoders can turn essentially forever their
  values are constrained to match MIDI note values (0-127).
*/

void readEncoder1() {

  int newPos1 = myEnc1.read();
  int newPos2 = myEnc2.read();

  if (newPos1 > position1) { // increases encoder #1
    position1 = newPos1;
    encVals[cVal]--;
    encVals[cVal] = constrain(encVals[cVal], 0, 127);

    MIDImessage(177, 0, encVals[cVal]);
  }

  if (newPos1 < position1) { // decreases encoder #1
    position1 = newPos1;
    encVals[cVal]++;
    encVals[cVal] = constrain(encVals[cVal], 0, 127);

    MIDImessage(177, 0, encVals[cVal]);
  }

  if (newPos2 > position2) { // increases encoder #2
    position2 = newPos2;
    encVals[cVal + 1]--;
    encVals[cVal + 1] = constrain(encVals[cVal + 1], 0, 127);

    MIDImessage(178, 0, encVals[cVal + 1]);
  }

  if (newPos2 < position2) { // decreases encoder #2
    position2 = newPos2;
    encVals[cVal + 1]++;
    encVals[cVal + 1] = constrain(encVals[cVal + 1], 0, 127);

    MIDImessage(178, 0, encVals[cVal + 1]);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////

void readEncoder2() {

  int newPos1 = myEnc1.read();
  int newPos2 = myEnc2.read();

  if (newPos1 > position1) { // increases encoder #1
    position1 = newPos1;
    encVals2[cVal2]--;
    encVals2[cVal2] = constrain(encVals2[cVal2], 0, 100);
    Serial.print("[Decrease]: ");
    Serial.print("1\n\r");
  }

  if (newPos1 < position1) { // decreases encoder #1
    position1 = newPos1;
    encVals2[cVal2]++;
    encVals2[cVal2] = constrain(encVals2[cVal2], 0, 100);
    Serial.print("[Increase]: ");
    Serial.print("1\n\r");
  }

  if (newPos2 > position2) { // increases encoder #2
    position2 = newPos2;
    encVals2[cVal2 + 1]--;
    encVals2[cVal2 + 1] = constrain(encVals2[cVal2 + 1], 0, 100);
    Serial.print("[Decrease]: ");
    Serial.print("2\n\r");
  }

  if (newPos2 < position2) { // decreases encoder #2
    position2 = newPos2;
    encVals2[cVal2 + 1]++;
    encVals2[cVal2 + 1] = constrain(encVals2[cVal2 + 1], 0, 100);
    Serial.print("[Increase]: ");
    Serial.print("2\n\r");
  }
}
