//Program menggerakkan servo dengan sensor jarak ultrasonik ditampilkan pada LCD I2C

#include <Adafruit_LiquidCrystal.h>		//library LCD I2C
#include <Servo.h>						//library servo

Adafruit_LiquidCrystal LCD(0);			//inisialisasi LCD dengan nama LCD
Servo Myservo;							//inisialisasi servo dengan nama Myservo

//inisialisai PIN Ultrasonik(menginisialisasi PIN mana Yang dipakai)
const int TRG_PIN = 3;		// PIN 3 TRIGER
const int ECH_PIN = 2;		// PIN 2 ECHO

//deklarasi (deklarai output dari Ultrasonik)
int distance;
long duration;
int pos = 0;

void setup()
{
  Serial.begin(9600);		//Komunikasi serial, agar tampil diserial monitor
  pinMode(TRG_PIN, OUTPUT); //inisialisasi TRG_PIN sebagai output dari Ultrasonik
  pinMode(ECH_PIN, INPUT);	//inisialisasi ECH_PIN sebagai Input dari Ulrasonik
  Myservo.attach(4);		//kaki signal servo PIN 4
  Myservo.write(90);		//Menggerakkan servo motor ke posisi tengah (90 derajat)
  delay(100);				//memberi waktu servo untuk mencapai posisi awal
  
  LCD.begin(16, 2);			//memulai komunikasi dengan LCD
  LCD.setCursor(2, 1);		//mengatur posisi text
  LCD.print("Jarak = ");	//menampilkan "Jarak =" di LCD
}  

void loop()
{
  LCD.setBacklight(1);			//mengaktifkan cahaya LCD
  
  //mengirim pulsa ultrasonik
  digitalWrite(TRG_PIN, LOW); 
  delay(5);
  digitalWrite(TRG_PIN, HIGH);
  delay(10);
  digitalWrite(TRG_PIN, LOW);
  duration = pulseIn(ECH_PIN, HIGH);// Membaca waktu yang dibutuhkan untuk echo pulsa kembali
  distance = (duration/2)*0.034;	//konversi hasil pengukuran ultrasonik dengan persamaan (duration/2)*0.034 
  
  Serial.print("Jarak = ");	//menampilkan kata (jarak =)diserial monitor
  Serial.print(distance);   //mencetak jarak hasil ukur ultrasonik
  Serial.println(" cm");	//mencetak satuan (cm) hasil deteksi jarak 
 
  // Menggerakkan servo motor berdasarkan jarak
  if (distance >= 50 && distance <= 150);
  {
    int servoPosition = map(distance, 50, 150, 0, 180);    
    Myservo.write(servoPosition);
    delay(10);
  }
  
  //menampilkan pengukuran jarak pada LCD
  LCD.setCursor(10, 1);					//mengatur posisi text baris ke2
  LCD.print(String(distance) + "cm" );	//Menampilkan hasil pengukuran jarak pada LCD
  delay(50);							//Menunda sejenak sebelum membaca sensor ultrasonik lagi
}