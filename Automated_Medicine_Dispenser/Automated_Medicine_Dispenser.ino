#include <Wire.h>
#include <RTClib.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Servo.h>
#include "RTClib.h"
const char* dayOfWeek[] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY",
"Thursday", "FRIDAY", "SATURDAY"};
RTC_DS3231 rtc;
int Day, Month, Min, Sec, Hour;
int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;
int b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
LiquidCrystal_I2C lcd(0x27, 20, 4);
int currentOption = 1;
int previousOption = 1;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
{'1', '2', '3', 'A'},
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};
Servo servo1, servo2, servo3, servo4, servo5;
bool servoA1Enabled = false;
bool servoA2Enabled = false;
bool servoA3Enabled = false;
bool servoA4Enabled = false;
bool servoA5Enabled = false;
bool servoB1Enabled = false;
bool servoB2Enabled = false;
bool servoB3Enabled = false;
bool servoB4Enabled = false;
bool servoB5Enabled = false;
bool servoC1Enabled = false;
bool servoC2Enabled = false;
bool servoC3Enabled = false;
bool servoC4Enabled = false;
bool servoC5Enabled = false;
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
int moralarmHour = 0, moralarmMinute = 0;
int afteralarmHour = 0, afteralarmMinute = 0;
int nightalarmHour = 0, nightalarmMinute = 0;
bool moralarmEnabled = false;
bool afteralarmEnabled = false;
bool nightalarmEnabled = false;
void setup() {
Serial.begin(9600);
lcd.init();
lcd.backlight();
servo1.attach(14);
servo2.attach(15);
servo3.attach(16);
servo4.attach(17);
servo5.attach(18);
pinMode(12,INPUT);
if (! rtc.begin()) {
Serial.println("Couldn't find RTC");
Serial.flush();
while (1) delay(10);
}
if (rtc.lostPower()) {
Serial.println("RTC lost power, let's set the time!");
rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}
pinMode(13, OUTPUT);
}
void displaytime() {
DateTime now = rtc.now();
lcd.setCursor(0, 0);
lcd.print(" Digital Clock");
lcd.setCursor(0, 1);
lcd.print("Date : ");
Day =now.day();
if(Day <= 9)
{
lcd.print('0');
lcd.print(now.day(), DEC);
}
else
{
lcd.print(now.day(), DEC);
}
lcd.print('/');
Month = now.month();
if(Month <= 9)
{
lcd.print('0');
lcd.print(now.month(), DEC);
}
else
{
lcd.print(now.month(), DEC);
}
lcd.print('/');
lcd.print(now.year(), DEC);
lcd.print(" ");
lcd.setCursor(0, 2);
lcd.print("Time : ");
Hour = now.hour();
if( Hour <= 9)
{
lcd.print('0');
lcd.print(now.hour(), DEC);
}
else{
lcd.print(now.hour(), DEC);
}
lcd.print(':');
Min = now.minute();
if(Min <= 9)
{
lcd.print('0');
lcd.print(now.minute(), DEC);
}
else
{
lcd.print(now.minute(), DEC);
}
lcd.print(':');
Sec = now.second();
if ( Sec <= 9)
{
lcd.print("0");
lcd.print(now.second(), DEC);
}
else
{
lcd.print(now.second(), DEC);
}
lcd.print(" ");
lcd.setCursor(0, 3);
lcd.print("Day : ");
lcd.print(dayOfWeek[now.dayOfTheWeek()]);
delay(1000);
}
void morningAlarm() {
lcd.clear();
while(1){
char key = keypad.getKey();
if (key == '1') {
moralarmHour++;
if (moralarmHour > 23) {
moralarmHour = 0;
}
}
if (key == '2') {
moralarmMinute++;
if (moralarmMinute > 59) {
moralarmMinute = 0;
}
}
if (key == '3') {
moralarmEnabled = !moralarmEnabled;
}
if(key == '4') {
servoA1Enabled = !servoA1Enabled;
}
if(key == '5') {
servoA2Enabled =!servoA2Enabled;
}
if(key == '6') {
servoA3Enabled =!servoA3Enabled;
}
if(key == '8') {
servoA4Enabled =!servoA4Enabled;
}
if(key == '9') {
servoA5Enabled =!servoA5Enabled;
}
DateTime now = rtc.now();
lcd.setCursor(0, 0);
lcd.print("Set Alarm: ");
lcd.print(moralarmHour);
lcd.print(":");
if (moralarmMinute < 10) {
lcd.print("0");
}
lcd.print(moralarmMinute);
lcd.print(" ");
lcd.print(moralarmEnabled ? "ON " : "OFF");
lcd.setCursor(0,1);
lcd.print("S1 = ");
lcd.print(servoA1Enabled ? "ON " : "OFF");
lcd.print(" S2 = ");
lcd.print(servoA2Enabled ? "ON " : "OFF");
lcd.setCursor(0,2);
lcd.print("S3 = ");
lcd.print(servoA3Enabled ? "ON " : "OFF");
lcd.print(" S4 = ");
lcd.print(servoA4Enabled ? "ON " : "OFF");
lcd.setCursor(0,3);
lcd.print("S5 = ");
lcd.print(servoA5Enabled ? "ON " : "OFF");
if(key == '#')
{
return currentOption;
}
}
delay(100);
}
void afternoonAlarm(){
lcd.clear();
while(1){
char key = keypad.getKey();
if (key == '1') {
afteralarmHour++;
if (afteralarmHour > 23) {
afteralarmHour = 0;
}
}
if (key == '2') {
afteralarmMinute++;
if (afteralarmMinute > 59) {
afteralarmMinute = 0;
}
}
if (key == '3') {
afteralarmEnabled = !afteralarmEnabled;
}
if(key == '4') {
servoB1Enabled = !servoB1Enabled;
}
if(key == '5') {
servoB2Enabled =!servoB2Enabled;
}
if(key == '6') {
servoB3Enabled =!servoB3Enabled;
}
if(key == '8') {
servoB4Enabled =!servoB4Enabled;
}
if(key == '9') {
servoB5Enabled =!servoB5Enabled;
}
DateTime now = rtc.now();
lcd.setCursor(0, 0);
lcd.print("Set Alarm: ");
lcd.print(afteralarmHour);
lcd.print(":");
if (afteralarmMinute < 10) {
lcd.print("0");
}
lcd.print(afteralarmMinute);
lcd.print(" ");
lcd.print(afteralarmEnabled ? "ON " : "OFF");
lcd.setCursor(0,1);
lcd.print("S1 = ");
lcd.print(servoB1Enabled ? "ON " : "OFF");
lcd.print(" S2 = ");
lcd.print(servoB2Enabled ? "ON " : "OFF");
lcd.setCursor(0,2);
lcd.print("S3 = ");
lcd.print(servoB3Enabled ? "ON " : "OFF");
lcd.print(" S4 = ");
lcd.print(servoB4Enabled ? "ON " : "OFF");
lcd.setCursor(0,3);
lcd.print("S5 = ");
lcd.print(servoB5Enabled ? "ON " : "OFF");
if(key == '0')
{
return currentOption;
}
}
delay(100);
}
void nightAlarm(){
lcd.clear();
while(1){
char key = keypad.getKey();
if (key == '1') {
nightalarmHour++;
if (nightalarmHour > 23) {
nightalarmHour = 0;
}
}
if (key == '2') {
nightalarmMinute++;
if (nightalarmMinute > 59) {
nightalarmMinute = 0;
}
}
if (key == '3') {
nightalarmEnabled = !nightalarmEnabled;
}
if(key == '4') {
servoC1Enabled = !servoC1Enabled;
}
if(key == '5') {
servoC2Enabled =!servoC2Enabled;
}
if(key == '6') {
servoC3Enabled =!servoC3Enabled;
}
if(key == '8') {
servoC4Enabled =!servoC4Enabled;
}
if(key == '9') {
servoC5Enabled =!servoC5Enabled;
}
DateTime now = rtc.now();
lcd.setCursor(0, 0);
lcd.print("Set Alarm: ");
lcd.print(nightalarmHour);
lcd.print(":");
if (nightalarmMinute < 10) {
lcd.print("0");
}
lcd.print(nightalarmMinute);
lcd.print(" ");
lcd.print(nightalarmEnabled ? "ON " : "OFF");
lcd.setCursor(0,1);
lcd.print("S1 = ");
lcd.print(servoC1Enabled ? "ON " : "OFF");
lcd.print(" S2 = ");
lcd.print(servoC2Enabled ? "ON " : "OFF");
lcd.setCursor(0,2);
lcd.print("S3 = ");
lcd.print(servoC3Enabled ? "ON " : "OFF");
lcd.print(" S4 = ");
lcd.print(servoC4Enabled ? "ON " : "OFF");
lcd.setCursor(0,3);
lcd.print("S5 = ");
lcd.print(servoC5Enabled ? "ON " : "OFF");
if(key == '*')
{
return currentOption;
}
}
delay(100);
}
void loop() {
DateTime now = rtc.now();
int buttonState = digitalRead(12);
if (buttonState == 0) {
currentOption++;
if (currentOption > 2) {
currentOption = 1;
}
while (digitalRead(12) == 0) {
}
}
switch (currentOption) {
case 1:
lcd.clear();
displaytime();
break;
case 2:
lcd.setCursor(0, 0);
lcd.print(" Menu ");
lcd.setCursor(0, 1);
lcd.print("'#' - Morning Pill ");
lcd.setCursor(0, 2);
lcd.print("'0' - Afternoon Pill");
lcd.setCursor(0, 3);
lcd.print("'*' - Night Pill");
break;
}
char key = keypad.getKey();
if (key == '#') {
morningAlarm();
}
else if(key == '0') {
afternoonAlarm();
}
else if(key == '*') {
nightAlarm();
}
if (now.hour() == moralarmHour && now.minute() == moralarmMinute && moralarmEnabled) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print(" Alarming!!");
lcd.setCursor(0, 1);
lcd.print(" Take a Medicines");
lcd.setCursor(0, 2);
lcd.print(" Get Well Soon ");
digitalWrite(13, HIGH);
delay(1000);
digitalWrite(13, LOW);
delay(1000);
if (servoA1Enabled && a1==0) {
for(int i=0;i<=90;i++) {
servo1.write(i);
delay(10);
}
for(int i=90;i>=0;i--) {
servo1.write(i);
delay(10);
}
a1=1;
}
if (servoA2Enabled && a2==0) {
for(int i=0;i<90;i++) {
servo2.write(i);
delay(10);
}
for(int i=90;i>0;i--) {
servo2.write(i);
delay(10);
}
a2=1;
}
if (servoA3Enabled && a3==0) {
for(int i=0;i<90;i++) {
servo3.write(i);
delay(10);
}
for(int i=90;i>0;i--) {
servo3.write(i);
delay(10);
}
a3=1;
}
if (servoA4Enabled && a4==0) {
for(int i=0;i<90;i++) {
servo4.write(i);
delay(10);
}
for(int i=90;i>0;i--) {
servo4.write(i);
delay(10);
}
a4=1;
}
if (servoA5Enabled && a5==0) {
for(int i=0;i<90;i++) {
servo5.write(i);
delay(10);
}
for(int i=90;i>0;i--) {
servo5.write(i);
delay(10);
}
a5=1;
}
}
else if (now.hour() == afteralarmHour && now.minute() == afteralarmMinute &&
afteralarmEnabled) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print(" Alarming!!");
lcd.setCursor(0, 1);
lcd.print(" Take a Medicines");
lcd.setCursor(0, 2);
lcd.print(" Get Well Soon ");
digitalWrite(13, HIGH);
delay(1000);
digitalWrite(13, LOW);
delay(1000);
if (servoB1Enabled && b1==0) {
for(int i=0;i<=90;i++) {
servo1.write(i);
delay(10);
}
for(int i=90;i>=0;i--) {
servo1.write(i);
delay(10);
}
b1=1;
}
if (servoB2Enabled && b2==0) {
for(int i=0;i<90;i++) {
servo2.write(i);
delay(10);
}
for(int i=90;i>0;i--) {
servo2.write(i);
delay(10);
}
b2=1;
}
if (servoB3Enabled && b3==0) {
for(int i=0;i<90;i++) {
servo3.write(i);
delay(10);
}
for(int i=90;i>0;i--) {
servo3.write(i);
delay(10);
}
b3=1;
}
if (servoB4Enabled && b4==0) {
for(int i=0;i<90;i++) {
servo4.write(i);
delay(10);
}
for(int i=90;i>0;i--) {
servo4.write(i);
delay(10);
}
b4=1;
}
if (servoB5Enabled && b5==0) {
for(int i=0;i<90;i++) {
servo5.write(i);
delay(10);
}
for(int i=90;i>0;i--) {
servo5.write(i);
delay(10);
}
b5=1;
}
}
else if (now.hour() == nightalarmHour && now.minute() == nightalarmMinute &&
nightalarmEnabled) {
lcd.clear();
lcd.setCursor(0, 0);
lcd.print(" Alarming!!");
lcd.setCursor(0, 1);
lcd.print(" Take a Medicines");
lcd.setCursor(0, 2);
lcd.print(" Get Well Soon ");
digitalWrite(13, HIGH);
delay(1000);
digitalWrite(13, LOW);
delay(1000);
if (servoC1Enabled && c1==0) {
for(int i=0;i<=90;i++) {
servo1.write(i);
delay(10);
}
for(int i=90;i>=0;i--) {
servo1.write(i);
delay(10);
}
c1=1;
}
if (servoC2Enabled && c2==0) {
for(int i=0;i<90;i++) {
servo2.write(i);
delay(10);
}
for(int i=90;i>0;i--) {
servo2.write(i);
delay(10);
}
c2=1;
}
if (servoC3Enabled && c3==0) {
for(int i=0;i<90;i++) {
servo3.write(i);
delay(10);
}
for(int i=90;i>0;i--) {
servo3.write(i);
delay(10);
}
c3=1;
}
if (servoC4Enabled && c4==0) {
for(int i=0;i<90;i++) {
servo4.write(i);
delay(10);
}
for(int i=90;i>0;i--) {
servo4.write(i);
delay(10);
}
c4=1;
}
if (servoC5Enabled && c5==0) {
for(int i=0;i<90;i++) {
servo5.write(i);
delay(10);
}
for(int i=90;i>0;i--) {
servo5.write(i);
delay(10);
}
c5=1;
}
}
else if(now.minute() > moralarmMinute && now.hour() > moralarmHour)
{
a1 = 0;
a2 = 0;
a3 = 0;
a4 = 0;
a5 = 0;
}
else if(now.minute() > afteralarmMinute && now.hour() >afteralarmHour)
{
b1 = 0;
b2 = 0;
b3 = 0;
b4 = 0;
b5 = 0;
}
else if(now.minute() > nightalarmMinute && now.hour() > nightalarmHour )
{
c1 = 0;
c2 = 0;
c3 = 0;
c4 = 0;
c5 = 0;
}
delay(100);
}
