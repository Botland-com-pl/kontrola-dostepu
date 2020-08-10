#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Stworzenie instancji dla modułu
 
void setup() 
{
  SPI.begin();      // Włączamy komunikacje przez SPI
  mfrc522.PCD_Init();   // Inicjujemy moduł RC522
  pinMode(8, OUTPUT); //Ustawiamy 8 pin cyfrowy jako pin wyjściowy - przekaźnik
  pinMode(7, OUTPUT); //Ustawiamy 7 pin cyfrowy jako pin wyjściowy - pin diody RGB odpowiedzialny za kolor czerwony
  pinMode(6, OUTPUT); //Ustawiamy 6 pin cyfrowy jako pin wyjściowy - pin diody RGB odpowiedzialny za kolor zielony
}
void loop() 
{
  digitalWrite(7, HIGH); //Podajemy napięcie na pin 7, powoduje to zaświecenie się diody na czerwono
  // Moduł sprawdza czy pojawia się nowa karta
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Moduł sprawdza czy można odczytać ID karty
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Wyświetlenie ID na Serial Monitorze
  Serial.print("ID tagu :");
  String content= ""; // Stworzenie zmiennej typu string, będzie służyć do przechowania ID
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase(); //Przekształcenie wyniku na duże litery
  if (content.substring(1) == "PIERWSZE ID") // !!!TUTAJ WPISZ ID PIERWSZEGO TAGA!!!
  {
    digitalWrite(8,HIGH); //Włączamy przekaźnik
    digitalWrite(7, LOW); //Podajemy na pin 7 stan niski, dioda przestaje świecić się na czerwono
    digitalWrite(6, HIGH); //Podajemy napięcie na pin 6, powoduje to zaświecenie się diody na zielono
    delay(10000); //Zamek jest odbezpieczony na 10 sekund
    digitalWrite(8,LOW); //Wyłączamy przekaźnik
    digitalWrite(6, LOW); //Podajemy na pin 6 stan niski, dioda przestaje świecić się na zielono
    digitalWrite(7, HIGH); //Podajemy napięcie na pin 7, dioda zaświeca się na czerwono
  }
else if (content.substring(1) == "DRUGIE ID") // !!!TUTAJ WPISZ ID DRUGIEGO TAGA!!!
  {
    digitalWrite(8,HIGH); //Włączamy przekaźnik
    digitalWrite(7, LOW); //Podajemy na pin 7 stan niski, dioda przestaje świecić się na czerwono
    digitalWrite(6, HIGH); //Podajemy napięcie na pin 6, powoduje to zaświecenie się diody na zielono
    delay(10000); //Zamek jest odbezpieczony na 10 sekund
    digitalWrite(8,LOW); //Wyłączamy przekaźnik
    digitalWrite(6, LOW); //Podajemy na pin 6 stan niski, dioda przestaje świecić się na zielono
    digitalWrite(7, HIGH); //Podajemy napięcie na pin 7, dioda zaświeca się na czerwono
  }
 else   {
    for (byte i = 0; i < 10; i++) //Pętla 10 razy przechodzi przez mruganie diodą, odczyt karty zablokowany na 5 sekund
  {
     digitalWrite(7, LOW);
     delay(250);
     digitalWrite(7,HIGH);
     delay(250);
  }
  }
} 
