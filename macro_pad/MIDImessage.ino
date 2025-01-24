/*
  The MIDI message consists of three bytes, first setting the status
  of the message, and the following bytes denoting the action, which
  note number, velocity, pressure etc. The data bytes are different
  depending on the type of the message set by the status byte.

  Refer to the following chart for which bytes do what:

  https://www.midi.org/specifications-old/item/table-2-expanded-messages-list-status-bytes
*/

void MIDImessage(byte status, byte data1, byte data2) {
  Serial.write(status);
  Serial.write(data1);
  Serial.write(data2);
}
int checkModeButton() {
  buttonState = digitalRead(ModeButton);
  if (buttonState !=
      lastButtonState) {      // compare the buttonState to its previous state
    if (buttonState == LOW) { // if the state has changed, increment the counter
      // if the current state is LOW then the button cycled:
      modePushCounter++;
    }
    delay(50); // Delay a little bit to avoid bouncing
  }
  lastButtonState = buttonState; // save the current state as the last state,
                                 // for next time through the loop
  if (modePushCounter >
      1) { // reset counter after 4 presses (remember we start counting at 0)
           // change this number to add more modes
    modePushCounter = 0;
  }
  return modePushCounter;
}
