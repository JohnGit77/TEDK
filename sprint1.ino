#include <Keypad.h>
#include <LiquidCrystal.h>

// LCD setup
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

// Keypad setup
const byte ROWS = 4; 
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '5', '9', 'C'},
  {'2', '6', '0', '-'},
  {'3', '7', '+', '*'},
  {'4', '8', '=', '/'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Variables for calculation
String input = "";
String result = "";

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Calculator Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    if (key == 'C') {
      input = "";
      result = "";
      lcd.clear();
    } else if (key == '=') {
      result = calculate(input);
      lcd.setCursor(0, 1);
      lcd.print("= ");
      lcd.print(result);
    } else {
      input += key;
      lcd.setCursor(0, 0);
      lcd.print(input);
    }
  }
}

String calculate(String expr) {
  int index = expr.indexOf('+');
  if (index < 0) index = expr.indexOf('-');
  if (index < 0) index = expr.indexOf('*');
  if (index < 0) index = expr.indexOf('/');
  
  if (index > 0) {
    int num1 = expr.substring(0, index).toInt();
    int num2 = expr.substring(index + 1).toInt();
    char op = expr[index];
    
    switch (op) {
      case '+': return String(num1 + num2);
      case '-': return String(num1 - num2);
      case '*': return String(num1 * num2);
      case '/': return num2 != 0 ? String((float)num1 / num2) : "Err";
    }
  }
  
  return "Err";
}
