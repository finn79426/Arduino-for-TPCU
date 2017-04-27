/*------------全域變數定義-----------*/

int potpin = 0;//定義類比介面0 連接光敏電阻
int ledpin = 1;//定義數位介面11 輸出PWM 調節LED 亮度
//定義數碼管port
int Apipe = 2;
int Bpipe = 3;
int Cpipe = 4;
int Dpipe = 5;
int Epipe = 6;
int Fpipe = 7;
int Gpipe = 8;
/*int Hpipe = 9;   小數點省略*/


int val;  //定義變數val 給光感電阻用
int list; //定義變數list 給快速關閉數碼管用

//輸出模式(定義LED閃爍頻率)
int pinmode1 = 25;
int pinmode2 = 100;
int pinmode3 = 200;
int nolight = 0;




/*------------數碼管輸出-------------*/

/*******顯示數字1********/
void print1(void) {
  for (list = Apipe; list <= 5; list++)
    digitalWrite(list, LOW);
  //把A、B、C、D燈管熄滅
  digitalWrite(Gpipe, LOW);
  //G管也要熄滅

  digitalWrite(Epipe, HIGH);
  digitalWrite(Fpipe, HIGH);
}

/*******顯示數字2********/
void print2(void) {
  digitalWrite(Apipe, HIGH);
  digitalWrite(Bpipe, HIGH);
  digitalWrite(Gpipe, HIGH);
  digitalWrite(Epipe, HIGH);
  digitalWrite(Dpipe, HIGH);

  digitalWrite(Cpipe, LOW);
  digitalWrite(Fpipe, LOW);
}

/*******顯示數字3********/
void print3(void){
  for(list = Apipe;list <= Dpipe;list++)
  digitalWrite(list, HIGH);//一次亮A~Dpipe
  digitalWrite(Gpipe,HIGH);

  digitalWrite(Fpipe,LOW);
  digitalWrite(Epipe,LOW);
}

void setup() {
  int p;  //區域變數i，給定義輸出針腳使用
  for (p = 1; p <= 8; p++)
    pinMode(p, OUTPUT); //把1~8針腳設定為輸出電流

  Serial.begin(9600);//設置串列傳輸速率為9600
}
void loop() {
  val = analogRead(potpin); //讀取感測器的模擬值並賦值給val

if (val > 50) {
    Serial.println(val);//顯示val 變數數值
  } 


  if (val <= 100 && val >= 50) { //如果光感數值大於等於50，小於等於100
    Serial.println("Rage in 50 ~ 100");
    analogWrite(ledpin, pinmode1); // 打開LED 亮度調整為25             （PWM 輸出最大值255）
    print1(); //數碼管輸出數字1
    delay(10);//延時0.01 秒
  } else if (val <= 150 && val >= 101) { //如果光感數值大於等於101，小於等於150
    Serial.println("Rage in 100 ~ 150");
    analogWrite(ledpin, pinmode2); //打開LED 亮度調整為100
    print2(); //數碼管輸出數字2
    delay(10);
  } else if (val > 150) { //光感數值大於150
Serial.println("Over 150");
    analogWrite(ledpin, pinmode3); //打開LED 亮度調整為200
    print3(); //數碼管輸出數字3
    delay(10);
  } else { //如果以上都不符合
    analogWrite(ledpin, nolight); //LED不亮燈
    delay(10);
    Serial.println("No Light Detected! \t closing the LED...");
  }

}
