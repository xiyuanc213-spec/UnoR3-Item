//******** ARD.C.1.1 ********//

#include <Arduino.h>

void init_led()
{
    // 初始化 GPIO 13 引脚为输出模式
    pinMode(13, OUTPUT);              // 初始化 GPIO 13 引脚
    
    digitalWrite(13, LOW);            // 将 GPIO 13 引脚设置为低电平（LED 关闭）
    return;
}

// int main()
// {
//     // 初始化整块板子
//     init();

//     /*
//     - 函数调用：通过调用函数来执行特定的任务，这里我们定义了一个函数来初始化 GPIO 13 引脚。
//     */
//     init_led();

//     /*
//     - while 循环：无限循环，程序将一直在此运行。若想退出循环并向下运行，需要break；。
//     */
//     while (true)
//     {
//         digitalWrite(13, HIGH); // 将 GPIO 13 引脚设置为高电平（LED 点亮）
//         delay(1000);            // 亮灯持续 1000 毫秒（1 秒）
//         digitalWrite(13, LOW);  // 将 GPIO 13 引脚设置为低电平（LED 关闭）
//         delay(1000);            // 灭灯持续 1000 毫秒（1 秒)
//     }
// }

// //******** ARD.C.1.2 ********//

/*
宏定义：使用 #define 定义一个常量或宏，以便在代码中使用更具描述性的名称来代替具体的值。
*/
#define BUTTON_PIN 4
#define BOARD_LED_PIN 13

void init_button()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);      // 初始化 BUTTON_PIN 引脚 启用 BUTTON_PIN 引脚的上拉电阻

    return;
}

// int main()
// {
//     // 初始化整块板子
//     init();

//     // 初始化 BOARD_LED_PIN 引脚为输出模式
//     init_led();

//     // 初始化 BUTTON_PIN 引脚为输入模式，并启用上拉电阻
//     init_button();

//     /*
//     变量：在程序中用于存储数据的容器，这里使用 bool 类型的变量 last_button_state 来记录上一次按钮的状态。
//     */
//     /*
//     flag 标志位： 用于记录系统的某项状态
//     */
//     bool last_button_state = true; // 记录上一次按钮的状态，初始为未按下（高电平）

//     while (true)
//     {

//         /*
//         作用域：
//         在 while 循环内定义的变量 current_button_state 只在循环体内有效，每次循环都会重新定义和赋值。
//         而 last_button_state 定义在循环外部，因此它的值在整个程序运行期间都保持不变，直到被更新为当前按钮状态。
//         */
//         bool current_button_state = digitalRead(BUTTON_PIN); // 读取当前按钮状态

//         //

//         /*
//         if() 条件语句：根据括号内的条件判断是否执行大括号内的代码块，经常包含&&（逻辑与）或||（逻辑或）等逻辑运算符来组合多个条件。
//         */

//         if (last_button_state && !current_button_state)
//         {
//             // 检测到按钮从未按下变为按下的状态变化（下降沿）

//             /*
//             static 变量：在函数内定义的 static 变量在程序周期内只初始化一次、不被销毁。但作用域仍然限制。
//             */
//             static bool led_on = false;      // 记录 LED 当前状态
//             led_on = !led_on;                // 切换 LED 状态
//             digitalWrite(BOARD_LED_PIN, led_on); // 根据 led_on 的值设置 BOARD_LED_PIN 引脚
//         }

//         last_button_state = current_button_state; // 将当前按钮状态保存为上一次状态，以便下一次循环比较
//         delay(10);                             // 延迟
//     }
// }

//******** ARD.C.1.3 ********//

#define PWM_LED_PIN 10   // pin11 与 MsTimer2 共用 Timer2 冲突，改到 pin10(OC1B/Timer1)

void init_pwm_led()
{
    // 初始化 PWM 功能
    pinMode(PWM_LED_PIN, OUTPUT);                        // 初始化 PWM_LED_PIN 引脚
    // Arduino analogWrite 使用内置 PWM
    // PWM_LED_PIN=10 使用 Timer1/OC1B，与 Servo(pin9/OC1A) 共用 Timer1
    // Timer1 默认配置：prescaler=64, phase-correct PWM, TOP=255
    // Phase-correct PWM：计数器 0→255→0 为一个周期，共 512 tick
    // PWM 频率 = 16MHz / 64 / 512 ≈ 488Hz
    
    analogWrite(PWM_LED_PIN, 0);                          // 初始占空比为 0（LED 关闭）
}

/*
const变量：在函数内定义的 const 变量在程序周期内值不可修改，且只初始化一次。适用于常量值的定义。
全局变量：在函数外部定义的变量，在整个程序中都可以访问和修改。
*/
const int brightness_step = 2; // 亮度变化步长（8位 PWM 0~255）

// int main()
// {
//     // 初始化整块板子
//     init();

//     // 初始化 BOARD_LED_PIN 引脚为输出模式
//     init_led();

//     // 初始化 BUTTON_PIN 引脚为输入模式，并启用上拉电阻
//     init_button();

//     // 初始化 PWM LED
//     /*
//     PWM：通过 analogWrite 输出 PWM 信号控制 LED 亮度。
//     */
//     init_pwm_led();

//     bool last_button_state = true; // 记录上一次按钮的状态，初始为未按下（高电平）

//     while (true)
//     {
//         static bool breathing = true; // 新增：记录当前呼吸状态
//         static int brightness = 0;    // 记录当前亮度
//         static bool direction = true; // 记录亮度变化方向

//         bool current_button_state = digitalRead(BUTTON_PIN); // 读取当前按钮状态

//         if (last_button_state && !current_button_state)
//         {
//             // 检测到按钮从未按下变为按下的状态变化（下降沿）

//             static bool led_on = false;      // 记录 LED 当前状态
//             led_on = !led_on;                // 切换 LED 状态
//             digitalWrite(BOARD_LED_PIN, led_on); // 根据 led_on 的值设置 BOARD_LED_PIN 引脚

//             breathing = !breathing; // 新增：切换呼吸模式状态
//         }

//         /*
//         if-else 条件语句：根据括号内的条件判断执行不同的代码块。
//         */
//         if (breathing)
//         {
//             if (direction)
//             {
//                 brightness += brightness_step; // 增加亮度
//                 /*
//                 边界条件控制：当亮度值达到上限（255）时停止增加并翻转方向，实现亮度从暗到亮再到暗的循环变化。
//                 */
//                 if (brightness >= 255)
//                 { // 达到最大亮度
//                     brightness = 255;
//                     direction = false; // 切换为减少亮度
//                 }
//             }
//             else
//             {
//                 brightness -= brightness_step; // 减少亮度
//                 /*
//                 边界条件控制：当亮度值达到下限（0）时停止减少并翻转方向，形成完整的呼吸周期。
//                 */
//                if (brightness <= 0)
//                 { // 达到最小亮度
//                     brightness = 0;
//                     direction = true; // 切换为增加亮度
//                 }
//             }
//         }
//         else
//         {
//             brightness = 0; // 关闭 LED
//         }

//         analogWrite(PWM_LED_PIN, brightness); // 设置 PWM 占空比以调整 LED 亮度（Arduino 范围 0-255）

//         last_button_state = current_button_state; // 将当前按钮状态保存为上一次状态，以便下一次循环比较
//         delay(10);                             // 延迟
//     }
// }

//******** ARD.C.1.4 ********//
/*
函数返回值：
函数可以返回一个值，表示函数执行的结果或状态。
check_button_pressed 函数用于检测按钮是否被按下，并返回一个布尔值表示按钮状态。
*/
bool check_button_pressed()
{
    static bool last_button_state = true;             // 记录上一次按钮的状态，初始为未按下（高电平）
    bool current_button_state = digitalRead(BUTTON_PIN); // 读取当前按钮状态

    if (last_button_state && !current_button_state)
    {
        last_button_state = current_button_state; // 更新 last_button_state
        return true;                              // 检测到按钮按下，返回 true
    }

    last_button_state = current_button_state; // 更新 last_button_state
    return false;                             // 没有检测到按钮按下，返回 false
}

/*
函数传入参数：
函数可以接受参数，这些参数在函数内部使用来执行特定的操作。
update_breathing_led 函数接受一个布尔参数 breathing，表示当前是否处于呼吸模式，根据该参数来更新 LED 的状态。
*/
int update_breathing_led(bool breathing)
{
    if (!breathing)
    {
        analogWrite(PWM_LED_PIN, 0); // 关闭 LED
        return -1;
    }
    else
    {
        static int brightness = 0;    // 记录当前亮度
        static bool direction = true; // 记录亮度变化方向

        if (direction)
        {
            brightness += brightness_step; // 增加亮度
            if (brightness >= 255)
            { // 达到最大亮度
                brightness = 255;
                direction = false; // 切换为减少亮度
            }
        }
        else
        {
            brightness -= brightness_step; // 减少亮度
            if (brightness <= 0)
            { // 达到最小亮度
                brightness = 0;
                direction = true; // 切换为增加亮度
            }
        }
        analogWrite(PWM_LED_PIN, brightness); // 设置 PWM 占空比以调整 LED 亮度（Arduino 范围 0-255）
        return brightness; // 返回当前亮度值
    }
}

int main()
{
    // 初始化整块板子
    init();

    // 初始化串口通信，设置波特率为 115200
    Serial.begin(115200);

    // 初始化 BOARD_LED_PIN 引脚为输出模式
    init_led();

    // 初始化 BUTTON_PIN 引脚为输入模式，并启用上拉电阻
    init_button();

    // 初始化 PWM LED
    init_pwm_led();

    bool breathing = true; // 记录当前呼吸状态

    while (true)
    {

        if (check_button_pressed())
        {
            static bool led_on = false;      // 记录 LED 当前状态
            led_on = !led_on;                // 切换 LED 状态
            digitalWrite(BOARD_LED_PIN, led_on); // 根据 led_on 的值设置 BOARD_LED_PIN 引脚

            breathing = !breathing; // 切换呼吸模式状态
        }

        int now_brightness = update_breathing_led(breathing); // 更新呼吸灯状态

        /*
        printf() 函数：用于将信息输出到串口进行调试和分析，这里我们可以输出当前的亮度值来观察呼吸灯的变化。
        */
        Serial.print("Brightness: "); Serial.println(now_brightness); // 打印当前亮度值到串口进行调试

        delay(10); // 延迟
    }
}