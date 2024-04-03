#include <Adafruit_LiquidCrystal.h>

int led=13;
int led2=10;
int led3=9;
int button=7;
int button2=6;
int buzzer=8;
int ldr=A0;
int lm=A1;
int pwmpin=A2;

int buttonState = 0;
int buttonState2 = 0;

Adafruit_LiquidCrystal lcd_1(0);

void setup() {
lcd_1.begin(16,2);
lcd_1.print("LD     L1:  L2: ");
lcd_1.setCursor(0,1);
lcd_1.print("TP:       PT:   ");
  
pinMode(led,OUTPUT);
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(button,INPUT_PULLUP);
pinMode(button2,INPUT_PULLUP);
Serial.begin(9600);
}

int leitura_botao() {
buttonState = digitalRead(button);
return buttonState;
}

int leitura_botao2() {
buttonState2 = digitalRead(button2);
return buttonState2;
}

void controlebuzzer(float ldrvalor) {
if (ldrvalor>500)
tone(buzzer, 264);
else
noTone (buzzer); 
} 

int escala(int pwmvalor) {
int pwm;
pwm = map(pwmvalor, 0, 1023, 0, 255);
return pwm;
}

void decisao_led() {
  if (buttonState==LOW){
  lcd_1.setCursor(10,0);
  lcd_1.print("L");
  }
  else {
  lcd_1.setCursor(10,0);
  lcd_1.print("D");
  }
}

void decisao_led2() {
if (buttonState2==LOW){
  lcd_1.setCursor(15,0);
  lcd_1.print("L");
  }
  else {
  lcd_1.setCursor(15,0);
  lcd_1.print("D");
  }
}

void exibe_pwm(int poten) {
  if (poten < 100){
lcd_1.setCursor(13,1);
lcd_1.print(poten);
 lcd_1.setCursor(15,1);
lcd_1.print(" ");
  }
  else if (poten < 10)
    {
lcd_1.setCursor(14,1);
lcd_1.print(poten);
 lcd_1.setCursor(15,1);
lcd_1.print("  ");
  }
  else
     {
lcd_1.setCursor(13,1);
lcd_1.print(poten);
 }
}

void exibe_ldr(int ldr) {
lcd_1.setCursor(2,0);
lcd_1.print(ldr);
  if (ldr < 1000){
 lcd_1.setCursor(5,0);
lcd_1.print("  ");
  }
 
}

void exibe_temp(float temper) {
lcd_1.setCursor(3,1);
lcd_1.print(temper);
  if (temper < 10){
 lcd_1.setCursor(7,1);
lcd_1.print("  ");
  }
  else if (temper < 100)
    {
 lcd_1.setCursor(8,1);
lcd_1.print("  ");
  }
}

void controled() {
if(buttonState==LOW)
digitalWrite(led,HIGH);
else
digitalWrite(led,LOW);
}

void controled2() {
if(buttonState2==LOW)
digitalWrite(led2,HIGH);
else
digitalWrite(led2,LOW);
}

void controled3(int pot){
analogWrite(led3,pot);
}

int leitura_ldr(){
  int ldrvalor;
  ldrvalor = analogRead(ldr); 
  Serial.println(ldrvalor);
  return ldrvalor;
}

float leitura_temp() {
float temperatura = (float(analogRead(lm))*5.0/(1023))/0.01;
return temperatura;
}

int leitura_pwm(){
  int pwmvalor;
  pwmvalor = analogRead(pwmpin);
  Serial.println(pwmvalor);
  return pwmvalor;
}

void loop(){

float tempvalor;
int valor;
int pwm;
int pwmap;
int ldrvalor;
int esc;
  
leitura_botao();
controled();
decisao_led();

leitura_botao2();
controled2();
decisao_led2();
  
ldrvalor=leitura_ldr();
controlebuzzer(ldrvalor);
exibe_ldr(ldrvalor);

pwm=leitura_pwm();
pwmap=escala(pwm);    

controled3(pwmap);
exibe_pwm(pwmap);

tempvalor=leitura_temp();
exibe_temp(tempvalor);
}