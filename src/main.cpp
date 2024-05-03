
#include <Arduino.h>

#define TOUCH_READ 0x0
#define TOUCH_INTERRUPT 0x1
#define PIN_INTERRUPT 0x2

#define TOUCH_HANDLE_MODE TOUCH_INTERRUPT

#define TOUCH_PIN T0
// 阈值，touch value低于则发生中断
#define THRESHOLD 40

#define LED_PIN 2

static bool eventOccured = false;

void TouchEvent()
{
	Serial.printf("Touch Event.\r\n");
	eventOccured = true;
}

void PinEvent()
{
	eventOccured = true;
}

void setup()
{
	// put your setup code here, to run once:
	Serial.begin(115200);
	pinMode(LED_PIN, OUTPUT);

#if TOUCH_HANDLE_MODE == TOUCH_INTERRUPT
	touchAttachInterrupt(TOUCH_PIN, TouchEvent, THRESHOLD);
#elif TOUCH_HANDLE_MODE == PIN_INTERRUPT
	// 引脚接GND触发
	pinMode(TOUCH_PIN, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(TOUCH_PIN), PinEvent, FALLING);
#endif
}

void loop()
{
	digitalWrite(LED_PIN, LOW);
#if TOUCH_HANDLE_MODE == TOUCH_READ
	Serial.printf("touch value: %d\r\n", touchRead(TOUCH_PIN));
#endif
	// 防止中断阻塞崩溃
	if (eventOccured)
	{
		eventOccured = false;
		digitalWrite(LED_PIN, HIGH);
	}
	delay(200);
}