#define BUTTON_PIN 4
#define BOARD_LED_PIN 13

bool lastButtonState = HIGH;  // 上一次按键状态
bool ledOn = LOW;             // 当前 LED 状态

void setup()
{
    // D4：按键输入，并开启内部上拉电阻
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // D13：控制板载 LED
    pinMode(BOARD_LED_PIN, OUTPUT);

    // 一开始让 LED 熄灭
    digitalWrite(BOARD_LED_PIN, LOW);
}

void loop()
{
    // 读取现在的按键状态
    bool currentButtonState = digitalRead(BUTTON_PIN);

    // 如果上一次是 HIGH，现在变成 LOW
    // 说明按钮刚刚被按下
    if (lastButtonState == HIGH && currentButtonState == LOW)
    {
        // 把 LED 状态反过来
        ledOn = !ledOn;

        // 根据 ledOn 控制板载 LED
        digitalWrite(BOARD_LED_PIN, ledOn);
    }

    // 把这一次的状态保存下来
    // 下一轮 loop 时它就成为“上一次状态”
    lastButtonState = currentButtonState;

    delay(10);
}