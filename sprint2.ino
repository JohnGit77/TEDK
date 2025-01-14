#include <Keypad.h>
#include <LiquidCrystal.h>

class Display {
private:
    LiquidCrystal& lcd;
public:
    Display(LiquidCrystal& lcdDisplay) : lcd(lcdDisplay) {}

    void clearDisplay() {
        lcd.clear();
    }

    void showMessage(const String& message) {
        lcd.setCursor(0, 0);
        lcd.print(message);
    }

    void showResult(const String& result) {
        lcd.setCursor(0, 1);
        lcd.print(result);
    }

    void showInput(const String& input) {
        lcd.setCursor(0, 0);
        lcd.print(input);
    }
};

class Calculator {
private:
    String input;
    String result;
    Display& display;

public:
    Calculator(Display& displayObj) : display(displayObj) {}

    void processKey(char key) {
        if (key == 'C') {
            clearAll();
        } else if (key == '=') {
            result = calculate(input);
            display.showResult("= " + result);
        } else {
            input += key;
            display.showInput(input);
        }
    }

    void clearAll() {
        input = "";
        result = "";
        display.showMessage("Cleared");
        delay(1000);  // Optional delay to show "Cleared" message for a brief moment
        display.clearDisplay();
    }

    String calculate(const String& expr) {
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
};

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

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

Display display(lcd);
Calculator calculator(display);

void setup() {
    lcd.begin(16, 2);
    display.showMessage("Calculator Ready");
    delay(2000);
    display.clearDisplay();
}

void loop() {
    char key = keypad.getKey();
    if (key) {
        calculator.processKey(key);
    }
}

