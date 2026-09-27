#define BUTTON_PIN 4
#define BOARD_LED_PIN 13
#define PWM_LED_PIN 10

// 每次改变亮度的步长
const int brightness_step = 2;

// 保存按钮上一次的状态
bool last_button_state = HIGH;

// 板载 LED 当前状态
bool led_on = false;

// 是否处于呼吸灯模式
bool breathing = true;

// PWM LED 当前亮度
int brightness = 0;

// true = 亮度增加
// false = 亮度减少
bool direction = true;


void setup()
{
    // ========================
    // 初始化板载 LED
    // ========================
    pinMode(BOARD_LED_PIN, OUTPUT);
    digitalWrite(BOARD_LED_PIN, LOW);

    // ========================
    // 初始化按钮
    // ========================
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // ========================
    // 初始化 PWM LED
    // ========================
    pinMode(PWM_LED_PIN, OUTPUT);
    analogWrite(PWM_LED_PIN, 0);
}


void loop()
{
    // 读取按钮当前状态
    bool current_button_state = digitalRead(BUTTON_PIN);


    // ========================
    // 检测按钮按下
    // ========================

    // INPUT_PULLUP：
    //
    // 没按按钮 = HIGH
    // 按下按钮 = LOW
    //
    // 所以：
    // HIGH → LOW
    // 就说明刚刚按下按钮
    if (last_button_state && !current_button_state)
    {
        // 切换板载 LED 状态
        led_on = !led_on;

        digitalWrite(BOARD_LED_PIN, led_on);


        // 切换呼吸灯模式
        breathing = !breathing;
    }


    // ========================
    // 呼吸灯控制
    // ========================

    if (breathing)
    {
        // 亮度增加
        if (direction)
        {
            brightness += brightness_step;

            // 达到最大值
            if (brightness >= 255)
            {
                brightness = 255;

                // 接下来开始变暗
                direction = false;
            }
        }

        // 亮度减少
        else
        {
            brightness -= brightness_step;

            // 达到最小值
            if (brightness <= 0)
            {
                brightness = 0;

                // 接下来开始变亮
                direction = true;
            }
        }
    }
    else
    {
        // 不在呼吸模式时关闭 PWM LED
        brightness = 0;
    }


    // 输出 PWM
    analogWrite(PWM_LED_PIN, brightness);


    // 保存当前按钮状态
    // 下一轮 loop() 用于比较
    last_button_state = current_button_state;


    // 简单延时
    delay(10);
}
