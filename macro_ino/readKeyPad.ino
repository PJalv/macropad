void sendCommand(String command) {
  String totalCommand = "[exec]: #";
  totalCommand += command;
  totalCommand += "@\n\r";
  Serial.print(totalCommand);
}
void readKeyPad() {
  char key = kpd.getKey();

  checkModeButton();

  switch (modePushCounter) { // switch between keyboard configurations:
  case 0:                    //  Application Alpha or MODE 0
          //  ========================================================================

    digitalWrite(Mode1, HIGH);
    digitalWrite(Mode2, LOW); // indicate what mode is loaded
    if (key) {
      // Serial.println(key);
      switch (key) {
      case '1':
        Keyboard.press(
            KEY_LEFT_CTRL); // this presses CTRL + F11 (MUTES MAIN OUTPUT)
        Keyboard.press(204);
        delay(50);
        Keyboard.releaseAll();
        break; // don't forget the break statement!
      case '2':
        Keyboard.press(KEY_RIGHT_ALT);
        Keyboard.press(KEY_RIGHT_SHIFT);
        Keyboard.print("2");
        delay(50);
        Keyboard.releaseAll(); // go back playback
        break;

      case '3':
        Keyboard.press(KEY_RIGHT_ALT);
        Keyboard.press(KEY_RIGHT_SHIFT); // next on playback
        Keyboard.print("4");
        delay(50);
        Keyboard.releaseAll();
        break;
      case '4':
        Keyboard.press(
            KEY_LEFT_CTRL); // this presses CTRL + F12 MUTES BROWSER OUTPUT
        Keyboard.press(205);
        delay(50);
        Keyboard.releaseAll();
        break;
      case '5':
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press('q'); // SHOULD MUTE DISCORD
        delay(50);
        Keyboard.releaseAll();
        break;
      case '6':
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('c');
        delay(50);
        Keyboard.releaseAll();
        break;

      case '7':
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('l');
        delay(50);
        Keyboard.releaseAll();
        break;

      case '8':
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('v');
        delay(50);
        Keyboard.releaseAll();
        break;
      }
    }

    break;
  case 1: //  Arduino shortcuts or MODE 1
          //  ========================================================================

    digitalWrite(Mode1, LOW);
    digitalWrite(Mode2, HIGH);
    if (key) {
      // Serial.println(key);
      switch (key) {
      case '1': // Space Bar
        Serial.print("[Toggle]: ");
        Serial.print("1\n\r");
        break;
      case '2':
        sendCommand(
            "pactl set-default-sink $(pactl list sinks short | grep -v $(pactl "
            "get-default-sink) | grep -oP 'alsa_output[^\\s]+' | head -n 1)");
        break;
      case '3':
        sendCommand("notify-send Testing notifications");
        break;
      case '4':
        Serial.print("[Toggle]: ");
        Serial.print("2\n\r");
        break;
      case '5':
        sendCommand("pactl set-sink-mute $(pactl get-default-sink) toggle");
        break;
      case '6':
        sendCommand("playerctl --player=spotify,vlc previous");
        break;
      case '7':
        sendCommand("playerctl --player=spotify,vlc play-pause");
        break;
      case '8': // Find
        sendCommand("playerctl --player=spotify,vlc next");
        break;
      }
      delay(50);
      Keyboard.releaseAll(); // this releases the buttons
    }
    break;
  }
}
