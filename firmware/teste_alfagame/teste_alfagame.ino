#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

// DEFINIÇÕES
#define BLACK   0xFFFF// OK
#define CINZA   0x6A5ACD // OK
#define YELLOW  0x001F// OK
#define WHITE   0x0000 // OK
#define RED     0x901FFF // OK
#define BLUE    0xFFE0 // OK
#define ROXO    0x1740 // OK
#define AZULCEU 0x3fa104  // OK
#define GREEN   0xf8ff1f // ok
#define BRONZE  0xFE8C
#define OURO    0x7EFE

#define bta                               22 // 3 gpio conector, fio preto
#define btb                               27 // 3 gpio conector 2, 
#define btc                               16
#define btd                               17
#define bat                               0

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

int flagnota=0;
int nota=0;
int resposta=0;

void tela_pergunta(const char* frase1, const char* frase2, const char* frase3, const char* frase4, const char* frase5, int resp_correta);
void tela_nota(int retornonota);

void setup() 
{
    Serial.begin(115200);
    Serial.println("TESTE");
    pinMode(bta,INPUT_PULLUP); 
    pinMode(btb,INPUT_PULLUP); 
    pinMode(btc,INPUT_PULLUP); 
    pinMode(btd,INPUT_PULLUP); 
    tft.init();
    tft.setRotation(1);
}

void loop() 
{
    tela_pergunta("JUNTE AS VOGAIS: 1", "A + I =","A- AI","B- IA","C- AE",1);
    delay(2000);
    Serial.println("TESTE");

}

void tela_pergunta(const char* frase1, const char* frase2, const char* frase3, const char* frase4, const char* frase5, int resp_correta)
{
    tft.fillScreen(AZULCEU);
    tft.fillRect(1, 200, 320, 40, GREEN);
    tft.fillRect(10, 5, 305, 80, WHITE); 
    tft.fillRect(30, 95, 260, 40, WHITE); 
    tft.fillRect(30, 145, 260, 40, WHITE); 
    tft.fillRect(30, 195, 260, 40, WHITE); 
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.setCursor(20, 20);
    tft.println(frase1);
    tft.setCursor(20, 50);
    tft.println(frase2);
    tft.setCursor(40, 110);
    tft.println(frase3);               
    tft.setCursor(40, 160);            
    tft.println(frase4);          
    tft.setCursor(40, 210);
    tft.println(frase5);

    while (flagnota == 0)
    {
        if (digitalRead(bta) == 0) //A
        {
            resposta = 1;
            flagnota = 1;
            delay(500);
        }
        if (digitalRead(btb) == 0)//B
        {
            resposta = 2;
            flagnota = 1;
            delay(500);
        }
        if (digitalRead(btc) == 0)//C
        {
            resposta = 3;
            flagnota = 1;
            delay(500);
        }
        delay(10);
    }

    if (resp_correta == resposta)
    {
        tela_nota(1); // acertou
        nota = nota + 1;
    }
    else
    {
        tela_nota(0);
        nota = nota;
    }
    flagnota=0;
}

void tela_nota(int retornonota)
{
  tft.fillScreen(CINZA);
  ////////////////////////////////////////////////////////////////////////BETO
  tft.fillRect(50, 40, 110, 180, AZULCEU); 
  tft.fillCircle(75, 110, 10, RED); // BOCHECHA ESQUERDA
  tft.fillCircle(135, 110, 10, RED); // BOCHECHA ESQUERDA
  tft.drawCircle(105, 110, 13, BLACK); // BOCA DO BETO
  tft.fillRect(90, 85, 30, 30, AZULCEU); 
  tft.fillRoundRect(98, 90, 15, 25, 10, WHITE); //NARIZ BETO
  tft.fillCircle(85, 80, 12, WHITE); // OLHO ESQUERDA
  tft.fillCircle(85, 80, 3, BLACK); // OLHO ESQUERDA
  tft.fillCircle(125, 80, 12, WHITE); // OLHO DIREITO
  tft.fillCircle(125, 80, 3, BLACK); // OLHO DIREITO
  tft.fillRect(180, 40, 100, 100, WHITE);

  if (retornonota == 1)
  {
      tft.setCursor(210, 70);
      tft.setTextColor(GREEN);
      tft.setTextSize(6);
      tft.println("V");           // Texto original
      tft.setCursor(211, 70);     // Desloca 1px para a direita
      tft.println("V");           // Texto sobreposto
      tft.setCursor(212, 70);     // Desloca 1px para a direita
      tft.println("V");           // Texto sobreposto
      tft.setCursor(210, 71);     // Desloca 1px para a direita
      tft.println("V");           // Texto sobreposto
      tft.setCursor(210, 72);     // Desloca 1px para a direita
      tft.println("v");           // Texto sobreposto
  }
  else
  {
      tft.setCursor(210, 70);
      tft.setTextColor(RED);
      tft.setTextSize(6);
      tft.println("X");           // Texto original
      tft.setCursor(211, 70);     // Desloca 1px para a direita
      tft.println("X");           // Texto sobreposto
      tft.setCursor(212, 70);     // Desloca 1px para a direita
      tft.println("X");           // Texto sobreposto
      tft.setCursor(210, 71);     // Desloca 1px para a direita
      tft.println("X");           // Texto sobreposto
      tft.setCursor(210, 72);     // Desloca 1px para a direita
      tft.println("X");           // Texto sobreposto
  }
}
