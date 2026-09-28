// ******** ARD.C.1.5 Arduino IDE版本 ******** //


// =========================
// 1. 引脚定义
// =========================

// 按钮
#define BUTTON_PIN 4

// Arduino板载LED
#define BOARD_LED_PIN 13

// 呼吸灯PWM引脚
#define PWM_LED_PIN 10

// 电机A方向控制
#define MOTOR_A_IN1 7
#define MOTOR_A_IN2 8

// 电机B方向控制
// A0、A1在这里当普通数字GPIO使用
#define MOTOR_B_IN1 A0
#define MOTOR_B_IN2 A1

// 两个电机的PWM调速
#define MOTOR_PWM_A 5
#define MOTOR_PWM_B 6


// =========================
// 2. 全局变量
// =========================

// 电机状态
// 0 = 前进
// 1 = 后退
// 2 = 停止
int motor_state_step = 0;


// 按钮上一次状态
bool last_button_state = HIGH;


// 呼吸灯参数
int brightness = 0;
bool brightness_direction = true;

const int brightness_step = 2;


// =========================
// 3. setup()
// 上电以后只运行一次
// =========================

void setup()
{
    // ---------- 板载LED ----------
    pinMode(BOARD_LED_PIN, OUTPUT);
    digitalWrite(BOARD_LED_PIN, LOW);


    // ---------- 按钮 ----------
    pinMode(BUTTON_PIN, INPUT_PULLUP);


    // ---------- 呼吸灯 ----------
    pinMode(PWM_LED_PIN, OUTPUT);
    analogWrite(PWM_LED_PIN, 0);


    // ---------- 电机A方向 ----------
    pinMode(MOTOR_A_IN1, OUTPUT);
    pinMode(MOTOR_A_IN2, OUTPUT);


    // ---------- 电机B方向 ----------
    pinMode(MOTOR_B_IN1, OUTPUT);
    pinMode(MOTOR_B_IN2, OUTPUT);


    // ---------- 电机PWM ----------
    pinMode(MOTOR_PWM_A, OUTPUT);
    pinMode(MOTOR_PWM_B, OUTPUT);

    // 初始电机停止
    analogWrite(MOTOR_PWM_A, 0);
    analogWrite(MOTOR_PWM_B, 0);
}


// =========================
// 4. loop()
// 程序一直重复运行
// =========================

void loop()
{
    // =========================
    // 检查按钮
    // =========================

    if (check_button_pressed())
    {
        /*
          每按一次按钮：

          0 -> 1
          1 -> 2
          2 -> 0

          所以状态不断循环：
          前进 -> 后退 -> 停止 -> 前进...
        */

        motor_state_step =
            (motor_state_step + 1) % 3;
    }


    // =========================
    // 状态0：前进
    // =========================

    if (motor_state_step == 0)
    {
        // 电机A正转
        digitalWrite(MOTOR_A_IN1, HIGH);
        digitalWrite(MOTOR_A_IN2, LOW);

        // 电机B正转
        // 因为左右两个电机安装方向相反
        // 所以B的电平正好与A相反
        digitalWrite(MOTOR_B_IN1, LOW);
        digitalWrite(MOTOR_B_IN2, HIGH);


        // PWM = 125
        // 约为 125 / 255 ≈ 49%
        analogWrite(MOTOR_PWM_A, 125);
        analogWrite(MOTOR_PWM_B, 125);


        // 呼吸灯开启
        update_breathing_led(true);

        // 板载LED常亮
        digitalWrite(BOARD_LED_PIN, HIGH);
    }


    // =========================
    // 状态1：后退
    // =========================

    else if (motor_state_step == 1)
    {
        // 电机A反转
        digitalWrite(MOTOR_A_IN1, LOW);
        digitalWrite(MOTOR_A_IN2, HIGH);

        // 电机B反转
        digitalWrite(MOTOR_B_IN1, HIGH);
        digitalWrite(MOTOR_B_IN2, LOW);


        // 约50%速度
        analogWrite(MOTOR_PWM_A, 125);
        analogWrite(MOTOR_PWM_B, 125);


        // 呼吸灯开启
        update_breathing_led(true);

        // 板载LED关闭
        digitalWrite(BOARD_LED_PIN, LOW);
    }


    // =========================
    // 状态2：停止
    // =========================

    else
    {
        /*
          TB6612：
          IN1 = HIGH
          IN2 = HIGH

          属于刹车状态
        */

        digitalWrite(MOTOR_A_IN1, HIGH);
        digitalWrite(MOTOR_A_IN2, HIGH);

        digitalWrite(MOTOR_B_IN1, HIGH);
        digitalWrite(MOTOR_B_IN2, HIGH);


        // PWM关闭
        analogWrite(MOTOR_PWM_A, 0);
        analogWrite(MOTOR_PWM_B, 0);


        // 呼吸灯关闭
        update_breathing_led(false);

        // 板载LED关闭
        digitalWrite(BOARD_LED_PIN, LOW);
    }


    delay(10);
}


// =========================
// 5. 按钮检测函数
// =========================

bool check_button_pressed()
{
    // 读取按钮
    bool current_button_state =
        digitalRead(BUTTON_PIN);


    bool pressed = false;


    /*
      INPUT_PULLUP模式：

      没按：
      HIGH

      按下：
      LOW

      所以：

      HIGH -> LOW

      就代表刚刚按下
    */

    if (last_button_state == HIGH &&
        current_button_state == LOW)
    {
        pressed = true;
    }


    // 保存当前状态
    last_button_state =
        current_button_state;


    return pressed;
}


// =========================
// 6. 呼吸灯函数
// =========================

void update_breathing_led(bool breathing)
{
    // 如果不需要呼吸灯
    if (!breathing)
    {
        brightness = 0;

        analogWrite(PWM_LED_PIN, 0);

        return;
    }


    // =========================
    // 从暗变亮
    // =========================

    if (brightness_direction)
    {
        brightness += brightness_step;

        if (brightness >= 255)
        {
            brightness = 255;

            // 到顶以后开始变暗
            brightness_direction = false;
        }
    }


    // =========================
    // 从亮变暗
    // =========================

    else
    {
        brightness -= brightness_step;

        if (brightness <= 0)
        {
            brightness = 0;

            // 到底以后重新变亮
            brightness_direction = true;
        }
    }


    // 真正输出PWM
    analogWrite(PWM_LED_PIN, brightness);
}