#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

class KeyboardController
{
public:
  KeyboardController();

  static void keyDown(unsigned char key, int x, int y);
  static void keyUp(unsigned char key, int x, int y);

  bool isKeyPressed(unsigned char key) const;

private:
  static bool keyStates[256]; // Array estático para armazenar estados das teclas
};

#endif // KEYBOARDCONTROLLER_H
