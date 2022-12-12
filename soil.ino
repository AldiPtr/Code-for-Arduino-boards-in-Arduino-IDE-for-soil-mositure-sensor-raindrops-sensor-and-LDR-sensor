//penyiraman tanaman otomatis

const int pinDigital = A0; //inisialisasi pin sensor
const int relay = 6; //inisialisasi pin relay
const int ledGreen = 7; //inisialisasi pin led hijau
const int ledYellow = 8; //inisialisasi pin led 
const int ledRed = 9; //inisialisasi pin led merah
const int ldr = A1; //inisialisasi ldr
const int rain = A2; //inisialisasi sensor hujan
const int buzzer = 5;

void setup() {
  // put your setup code here, to run once:
Serial.begin (9600); //memanggil serial monitor
pinMode(pinDigital, INPUT); //menetapkan pin A0 sebagai input
pinMode(relay, OUTPUT); //menetapkan pin 6 sebagai output
pinMode(ledGreen, OUTPUT); //menetapkan pin 7 sebagai output
pinMode(ledYellow, OUTPUT); //menetapkan pin 8 sebagai output
pinMode(ledRed, OUTPUT); //menetapkan pin 9 sebagai output
pinMode(buzzer, OUTPUT);

}

void loop() {
    // put your main code here, to run repeatedly:
  String minta = "";
  while(Serial.available()>0)
  {
    minta += char(Serial.read());
  }

  minta.trim();

  if(minta == "Ya")
  {
    kirimdata();
  }

  minta = "";
  delay(1000);
}
void kirimdata(){
  // put your main code here, to run repeatedly:
int cahaya = analogRead(ldr); //membaca nilai sensor ldr
int hujan = analogRead(rain); //membaca nilai sensor hujan
int dataAnalog = analogRead (pinDigital); //membaca nilai dari pin sensor
//print hasil ke serial monitor
//Serial.print ("Kelembaban = "); 
//Serial.println (dataAnalog);

//jika nilai A0 kurang dari 500, maka print kata serta nyalakan led hijau dan matikan led kuning, merah dan juga relay
if (dataAnalog < 500){
  //Serial.println(" (Tanah Masih Basah) ");
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledYellow, LOW);
  digitalWrite(ledRed, LOW);
  digitalWrite(relay, LOW);
 }

//tetapi jila nilai A0 kurang dari 900, maka print kata serta nyalakan led kuning dan relay, kemudian matikan led hijau dan merah
else if (dataAnalog < 800){
  //Serial.println(" (Kelembaban Masih Cukup) ");
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledYellow, HIGH);
  digitalWrite(ledRed, LOW);
  digitalWrite(relay, HIGH);
}

//selain dari itu, hanya nyalakan led merah dan relay
else {//Serial.println (" (Taman Perlu Disiram) ");
digitalWrite(ledGreen, LOW);
digitalWrite(ledYellow, LOW);
digitalWrite(ledRed, HIGH);
digitalWrite(relay, HIGH);
}
//nilai sensor hujan
if (hujan <= 500){
  //Serial.println("Cuaca Sedang hujan");
  //Serial.println(hujan);
  digitalWrite(buzzer, HIGH);
  }
else {//Serial.println ("Cuaca Sedang Tidak Hujan");
//Serial.println(hujan);
digitalWrite(buzzer, LOW);
}
//Serial.println("Cahaya Yang Terdeteksi = ");
//Serial.println(cahaya);
//Serial.println();

String datakirim = String(dataAnalog) + "#" + String(hujan) + "#" + String(cahaya);
Serial.println(datakirim);
delay(2000);
}
