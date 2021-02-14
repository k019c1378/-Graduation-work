//超音波センサのピン
#define trigPin 13
#define echoPin 12

//サーボモーターのピン
#define SERVO_PIN 33
#define PWM_BITWIDTH 16

void setup() {
  //計測用(後述のコメント参照)
  //Serial.begin (9600);

  //センサの初期状態
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //ledcSetup(チャンネル数(0～),周波数(たとえばPWMサイクル20mHzなら50Hzになるという意味(SG90の場合))、分解能は任意(ただし限度はある))
  ledcSetup(0, 50, PWM_BITWIDTH);
  ledcAttachPin(SERVO_PIN, 0); //left_motor


}

//サーボモーターを制御するための関数
int deg2pw(int deg, int bit) {
  double ms = ((double) deg - 90.0) * 0.95 / 90.0 + 1.45;
  return (int) (ms / 20.0 * pow(2, bit));
}

//待機状態から、動作までのプログラムをループしている。
void loop() {

  //距離を計測するのに使用している変数
  float duration, distance;

  //超音波を照射、受信し、距離を計測
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0341;

  //動作確認用にシリアルモニタに物体との距離を表示する(実際の使用では必要ないためコメントアウトしている)
  //Serial.print("Distance = ");
  //Serial.print(distance);
  //Serial.println(" cm");
  //delay(500);

  
  //物体との距離が5cm以内の条件分岐if文の5を任意の距離に変更可能、ただしセンサーの計測範囲内(2cm～４mまで)
  if (distance <= 5) {
    delay(500);
    ledcWrite(0, deg2pw(0, PWM_BITWIDTH));
    delay(800);
    ledcWrite(0, deg2pw(90, PWM_BITWIDTH));
    delay(800);
  } else {
  }
}
