#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

// DEFINIÇÕES
//#define BLACK   0x0000
//#define BLUE    0x001F
//#define RED     0xF800
//#define GREEN   0x07E0
//#define YELLOW  0xFFE0
//#define WHITE   0xFFFF
//#define AZULCEU 0x273C
//#define CINZA   0x6A5ACD
//#define BRONZE  0xFF8C00
//#define OURO    0x7FFF00

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
//Sinalizador de autorização do OTA
int estadobta=0;
int estadobtb=0;
int estadobtc=0;
int ano=0;
int nivel=0;
int nota=0;
int flagnota=0;
int resposta=0;
int batValue=0;
float mappedValue =0;
int flagoff=0;
uint32_t  p1=0;
String versao= "V:0.1";

void fundo(void);
void telacarregamento(void);
void dialogo(void);
void telaperg3(void);
void telaperg2(void);
void puloalfa(int nump);
void medalha (int posi);
void alfaebeto(void);
void telanota(int retornonota);
void tela_pergunta(const char* frase1, const char* frase2, const char* frase3, const char* frase4, const char* frase5, int resp_correta);

//Setup
void setup(void)
{
  Serial.begin(115200);
  Serial.println("");
  tft.init();
  tft.setRotation(1);
  fundo();
  telacarregamento();
  pinMode(bta,INPUT_PULLUP); 
  pinMode(btb,INPUT_PULLUP); 
  pinMode(btc,INPUT_PULLUP); 
  pinMode(btd,INPUT_PULLUP); 
  mappedValue = map(analogRead(A0), 0, 4095, 0, 3.3); 
  Serial.print("analogRead: ");
  Serial.println(mappedValue); 
}

void loop(void)
{
      //////////////////////////////////////////////////////////////////////COLOCAR TELA DE CARREGANDO
      tft.fillScreen(AZULCEU);
      tft.drawCircle(70, 170, 50, YELLOW); // ALFA
      tft.fillCircle(70, 170, 50, YELLOW); // ALFA
      tft.fillCircle(55, 150, 12, WHITE); // OLHO ESQUERDA
      tft.fillCircle(55, 150, 3, BLACK); // OLHO ESQUERDA
      tft.fillCircle(86, 150, 12, WHITE); // OLHO DIREITO
      tft.fillCircle(86, 150, 3, BLACK); // OLHO DIREITO
      tft.setCursor(67, 165);
      tft.setTextColor(BLACK);
      tft.setTextSize(2);
      tft.println("U");
      tft.fillRoundRect(34, 175, 24, 10,3, RED);// BOCHECHA ESQUERDA
      tft.fillRoundRect(88, 175, 24, 10,3, RED);// BOCHECHA DIREITA
      tft.setCursor(140, 20);
      tft.setTextColor(BLACK);
      tft.setTextSize(2);
      tft.println("ALFAGAME-02");
      tft.setCursor(140, 60);
      tft.println(versao);
      delay(5000);
      //////////////////////////////////////////////////////////////////////COLOCAR TELA DE CARREGANDO
      dialogo();
      tft.setCursor(150, 30);
      tft.setTextColor(BLACK);
      tft.setTextSize(2);
      tft.println("OI ME CHAMO");
      tft.setCursor(150, 70);
      tft.println("ALFA,");
      tft.setCursor(150, 110);
      tft.println("ME AJUDA");
      tft.setCursor(150, 150);
      tft.println("COM O TEMA?");
      delay(5000);
      dialogo();
      tft.setCursor(150, 30);
      tft.setTextColor(BLACK);
      tft.setTextSize(2);
      tft.println("TENHO QUE");
      tft.setCursor(150, 70);
      tft.println("MOSTRAR PARA");
      tft.setCursor(150, 110);
      tft.println("O PROF. BETO");
      tft.setCursor(150, 150);
      tft.println("TOPA?");
      delay(5000);

      //--------------------------------------------SELECIONE O ANO DAS PERGUNTAS
      telaperg3();
      tft.setCursor(20, 30);
      tft.setTextColor(BLACK);
      tft.setTextSize(2);
      tft.println("SELECIONE O ANO:");
      tft.setCursor(40, 110);
      tft.println("A- PRIMEIRO");
      tft.setCursor(40, 160);
      tft.println("B- SEGUNDO");
      tft.setCursor(40, 210);
      tft.println("C- TERCEIRO");

      while (ano==0)
      {
          if (digitalRead(bta) == 0)
          {
              ano=1;
              Serial.print("Perguntas do ano:");
              Serial.println(ano);
          }
          if (digitalRead(btb) == 0)
          {
              ano=2;
              Serial.print("Perguntas do ano:");
              Serial.println(ano);
          }
          if (digitalRead(btc) == 0)
          {
              ano=3;
              Serial.print("Perguntas do ano:");
              Serial.println(ano);
          }
          delay(10);
      }

      delay(1000);
      //--------------------------------------------SELECIONE O NIVEL DAS PERGUNTAS
      telaperg2();
      tft.setCursor(20, 30);
      tft.setTextColor(BLACK);
      tft.setTextSize(2);
      tft.println("SELECIONE O NIVEL:");
      tft.setCursor(40, 110);
      tft.println("A- FACIL");
      tft.setCursor(40, 160);
      tft.println("B- DIFICIL");

      while (nivel == 0 )
      {
          if (digitalRead(bta) == 0)
          {
              nivel=1;
              Serial.println("Perguntas faceis");
          }
          if (digitalRead(btb) == 0)
          {
              nivel=2;
              Serial.println("Perguntas dificeis");
          }
          delay(10);
      }

      switch (ano)
      {
        case 1:
          if (nivel == 1)//--------------------------------------------PERGUNTAS DO PRIMEIRO ANO FACEIS REVISADAS
          {
              delay(1000);
              p1 = random(3);  // retorna 0, 1 ou 2
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO PRIMEIRO ANO FACEIS 1 REVISADA
              {
                tela_pergunta("JUNTE AS VOGAIS: 1", "A + I =","A- AI","B- IA","C- AE",1);
              }
              else if (p1==1)
              {
                tela_pergunta("JUNTE AS VOGAIS: 2", "I + A =","A- AI","B- IA","C- AE",2);
              }
              else 
              {
                tela_pergunta("JUNTE AS VOGAIS: 3", "E + U =","A- UE","B- EU","C- UA",2);

              }//-------------------------------------------- FIM PERGUNTAS DO PRIMEIRO ANO FACEIS 1 REVISADA

              delay(1000);
              p1 = random(3);  // retorna 0, 1 ou 2
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0) //--------------------------------------------PERGUNTAS DO PRIMEIRO ANO FACEIS 2 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL PALAVRA QUE INICIA");
                  tft.setCursor(20, 50);
                  tft.println("COM A MESMA LETRA: SOL");
                  tft.setCursor(40, 110);
                  tft.println("A- RATO");
                  tft.setCursor(40, 160);
                  tft.println("B- SAPO");
                  tft.setCursor(40, 210);
                  tft.println("C- TOSA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);//errou
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);//acertou
                          delay(1000);  
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);//errou
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else if (p1 == 1)
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL PALAVRA QUE INICIA");
                  tft.setCursor(20, 50);
                  tft.println("COM A MESMA LETRA: RIR");
                  tft.setCursor(40, 110);
                  tft.println("A- RATO");
                  tft.setCursor(40, 160);
                  tft.println("B- SAPO");
                  tft.setCursor(40, 210);
                  tft.println("C- TOSA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);//acertou
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);//errou
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);//errou
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else 
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL PALAVRA QUE INICIA");
                  tft.setCursor(20, 50);
                  tft.println("COM A MESMA LETRA: CASA");
                  tft.setCursor(40, 110);
                  tft.println("A- CAMA");
                  tft.setCursor(40, 160);
                  tft.println("B- MACA");
                  tft.setCursor(40, 210);
                  tft.println("C- BALA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);//acertou
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);//errou
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);//errou
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }//-------------------------------------------- FIM PERGUNTAS DO PRIMEIRO ANO FACEIS 2 REVISADA

              delay(1000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("ARRASOU!");
              tft.setCursor(150, 70);
              tft.println("DEPOIS DE 2,");
              tft.setCursor(150, 110);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 150);
              tft.println("BRONZE!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (3);
              delay(5000);
              p1 = random(3);  // retorna 0, 1 ou 2
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
        
              if (p1==0)//--------------------------------------------PERGUNTAS DO PRIMEIRO ANO FACEIS 3 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("JUNTE AS VOGAIS:");
                  tft.setCursor(20, 50);
                  tft.println("U + I =");
                  tft.setCursor(40, 110);
                  tft.println("A- IAU");
                  tft.setCursor(40, 160);
                  tft.println("B- UO");
                  tft.setCursor(40, 210);
                  tft.println("C- UI");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else if (p1==1)
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("JUNTE AS VOGAIS:");
                  tft.setCursor(20, 50);
                  tft.println("A + U =");
                  tft.setCursor(40, 110);
                  tft.println("A- AU");
                  tft.setCursor(40, 160);
                  tft.println("B- UO");
                  tft.setCursor(40, 210);
                  tft.println("C- IU");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else 
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("JUNTE AS VOGAIS:");
                  tft.setCursor(20, 50);
                  tft.println("A + U =");
                  tft.setCursor(40, 110);
                  tft.println("A- AU");
                  tft.setCursor(40, 160);
                  tft.println("B- UAU");
                  tft.setCursor(40, 210);
                  tft.println("C- AO");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }//-------------------------------------------- FIM PERGUNTAS DO PRIMEIRO ANO FACEIS 3 REVISADA

              delay(1000);
              p1 = random(3);  // retorna 0, 1 ou 2
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
        
              if (p1==0)//--------------------------------------------PERGUNTAS DO PRIMEIRO ANO FACEIS 4 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL PALAVRA QUE INICIA");
                  tft.setCursor(20, 50);
                  tft.println("COM A MESMA LETRA: GATO");
                  tft.setCursor(40, 110);
                  tft.println("A- JOGO");
                  tft.setCursor(40, 160);
                  tft.println("B- HORA");
                  tft.setCursor(40, 210);
                  tft.println("C- GOLA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else if (p1==1)
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL PALAVRA QUE INICIA");
                  tft.setCursor(20, 50);
                  tft.println("COM A MESMA LETRA: JAULA");
                  tft.setCursor(40, 110);
                  tft.println("A- JOGO");
                  tft.setCursor(40, 160);
                  tft.println("B- HORA");
                  tft.setCursor(40, 210);
                  tft.println("C- GOLA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL PALAVRA QUE INICIA");
                  tft.setCursor(20, 50);
                  tft.println("COM A MESMA LETRA: LIVRO");
                  tft.setCursor(40, 110);
                  tft.println("A- VIDRO");
                  tft.setCursor(40, 160);
                  tft.println("B- LAPIS");
                  tft.setCursor(40, 210);
                  tft.println("C- SINO");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }//--------------------------------------------FIM PERGUNTAS DO PRIMEIRO ANO FACEIS 4 REVISADA

              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("EBA!");
              tft.setCursor(150, 70);
              tft.println("DEPOIS DE 4,");
              tft.setCursor(150, 110);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 150);
              tft.println("PRATA!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (2);
              delay(5000);
              p1 = random(3);  // retorna 0, 1 ou 2
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO PRIMEIRO ANO FACEIS 5 REVISA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("JUNTE AS VOGAIS:");
                  tft.setCursor(20, 50);
                  tft.println("O + I =");
                  tft.setCursor(40, 110);
                  tft.println("A- IO");
                  tft.setCursor(40, 160);
                  tft.println("B- IUO");
                  tft.setCursor(40, 210);
                  tft.println("C- OI");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else if (p1==1)
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("JUNTE AS VOGAIS:");
                  tft.setCursor(20, 50);
                  tft.println("A + I =");
                  tft.setCursor(40, 110);
                  tft.println("A- IO");
                  tft.setCursor(40, 160);
                  tft.println("B- AU");
                  tft.setCursor(40, 210);
                  tft.println("C- AI");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("JUNTE AS VOGAIS:");
                  tft.setCursor(20, 50);
                  tft.println("E + I =");
                  tft.setCursor(40, 110);
                  tft.println("A- EIA");
                  tft.setCursor(40, 160);
                  tft.println("B- EI");
                  tft.setCursor(40, 210);
                  tft.println("C- OU");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }//--------------------------------------------FIM PERGUNTAS DO PRIMEIRO ANO FACEIS 5 REVISA

              delay(1000);
              p1 = random(3);  // retorna 0, 1 ou 2
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO PRIMEIRO ANO FACEIS 6 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUANTAS LETRAS TEM A");
                  tft.setCursor(20, 50);
                  tft.println("PALAVRA: LUA");
                  tft.setCursor(40, 110);
                  tft.println("A- 5");
                  tft.setCursor(40, 160);
                  tft.println("B- 3");
                  tft.setCursor(40, 210);
                  tft.println("C- 6");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else if (p1 == 1)
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUANTAS LETRAS TEM A");
                  tft.setCursor(20, 50);
                  tft.println("PALAVRA: BALA");
                  tft.setCursor(40, 110);
                  tft.println("A- 5");
                  tft.setCursor(40, 160);
                  tft.println("B- 3");
                  tft.setCursor(40, 210);
                  tft.println("C- 4");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;               
              }
              else
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUANTAS LETRAS TEM A");
                  tft.setCursor(20, 50);
                  tft.println("PALAVRA: CHUVA");
                  tft.setCursor(40, 110);
                  tft.println("A- 5");
                  tft.setCursor(40, 160);
                  tft.println("B- 3");
                  tft.setCursor(40, 210);
                  tft.println("C- 6");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                          telanota(1);
                          delay(1000);
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                          telanota(0);
                          delay(1000);
                      }
                      delay(10);
                  }
                  flagnota=0;
              }//-------------------------------------------- FIM PERGUNTAS DO PRIMEIRO ANO FACEIS 6 REVISADA

              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("CONSEGUIMOS!");
              tft.setCursor(150, 70);
              tft.println("OBRIGADA POR");
              tft.setCursor(150, 110);
              tft.println("SUA AJUDA.");
              delay(5000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("JUNTOS SOMOS");
              tft.setCursor(150, 70);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 110);
              tft.println("OURO!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (1);
              delay(5000);
          }
          else//--------------------------------------------PERGUNTAS DO PRIMEIRO ANO DIFICEIS
          {
              telaperg2();
              tft.setCursor(20, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)                    //  PERGUNTAS DO PRIMEIRO ANO DIFICEIS 1 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("COMPLETE A ORDEM DAS VOGAIS:"); 
                  tft.setCursor(20, 50);
                  tft.println("A __ I __ __");
                  tft.setCursor(40, 110);
                  tft.println("A- E U O");
                  tft.setCursor(40, 160);
                  tft.println("B- E I O");
                  tft.setCursor(40, 210);
                  tft.println("C- E O U");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else
              {                             //  PERGUNTAS DO PRIMEIRO ANO DIFICEIS 1 REVISADA
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL A VOGAL QUE FALTA?");
                  tft.setCursor(20, 50);
                  tft.println("AN__L");
                  tft.setCursor(40, 110);
                  tft.println("A- U");
                  tft.setCursor(40, 160);
                  tft.println("B- I");
                  tft.setCursor(40, 210);
                  tft.println("C- E");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)                                   //  PERGUNTAS DO PRIMEIRO ANO DIFICEIS 2 REVISADA
              { 
                  telaperg2();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("OVELHA RIMA COM:");
                  tft.setCursor(40, 110);
                  tft.println("A- ABELHA");
                  tft.setCursor(40, 160);
                  tft.println("B- AREIA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else                                        //  PERGUNTAS DO PRIMEIRO ANO DIFICEIS 2 REVISADA
              {
                  telaperg2();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("COMPLETE A ORDEM:");
                  tft.setCursor(20, 50);
                  tft.println("A B C D E F __ __ __");
                  tft.setCursor(40, 110);
                  tft.println("A-  G - H _ I ");
                  tft.setCursor(40, 160);
                  tft.println("B-  J - K - L");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("ARRASOU!");
              tft.setCursor(150, 70);
              tft.println("DEPOIS DE 2,");
              tft.setCursor(150, 110);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 150);
              tft.println("BRONZE!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (3);
              delay(5000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)                                   //  PERGUNTAS DO PRIMEIRO ANO DIFICEIS 3 REVISADA
              { 
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAIS VOGAIS FALTAM:");
                  tft.setCursor(20, 50);
                  tft.println("__ I T __");
                  tft.setCursor(40, 110);
                  tft.println("A-  A - U");
                  tft.setCursor(40, 160);
                  tft.println("B-  O - O");
                  tft.setCursor(40, 210);
                  tft.println("C-  O - U");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else                                         //  PERGUNTAS DO PRIMEIRO ANO DIFICEIS 3 REVISADA
              {
                  telaperg2();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUEM VEM ANTES E DEPOIS:");
                  tft.setCursor(20, 50);
                  tft.println("__ M __");
                  tft.setCursor(40, 110);
                  tft.println("A- L _ N");
                  tft.setCursor(40, 160);
                  tft.println("B- N _ L");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)                                   //  PERGUNTAS DO PRIMEIRO ANO DIFICEIS 4 REVISADA
              { 
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("SOL NAO:");
                  tft.setCursor(20, 50);
                  tft.println("RIMA COM:");
                  tft.setCursor(40, 110);
                  tft.println("A- FAROL");
                  tft.setCursor(40, 160);
                  tft.println("B- NUVEM");
                  tft.setCursor(40, 210);
                  tft.println("C- ANZOL");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else                                         //  PERGUNTAS DO PRIMEIRO ANO DIFICEIS 4 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAIS AS LETRAS FALTANTES:");
                  tft.setCursor(20, 50);
                  tft.println("_ B C D _ F G H _ J");
                  tft.setCursor(40, 110);
                  tft.println("A- VOGAIS");
                  tft.setCursor(40, 160);
                  tft.println("B- CONSOANTES");
                  tft.setCursor(40, 210);
                  tft.println("C- AMBAS");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("EBA!");
              tft.setCursor(150, 70);
              tft.println("DEPOIS DE 4,");
              tft.setCursor(150, 110);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 150);
              tft.println("PRATA!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (2);
              delay(5000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)                                   //  PERGUNTAS DO PRIMEIRO ANO DIFICEIS 5 REVISADA
              { 
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("MARQUE A PALAVRA");
                  tft.setCursor(20, 50);
                  tft.println("COM 3 VOGAIS:");
                  tft.setCursor(40, 110);
                  tft.println("A- QUEIJO");
                  tft.setCursor(40, 160);
                  tft.println("B- PAO");
                  tft.setCursor(40, 210);
                  tft.println("C- BANANA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else                                         //  PERGUNTAS DO PRIMEIRO ANO DIFICEIS 5 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAIS AS CONSOANTES FALTAM:");
                  tft.setCursor(20, 50);
                  tft.println("_ A _ A");
                  tft.setCursor(40, 110);
                  tft.println("A- D-F");
                  tft.setCursor(40, 160);
                  tft.println("B- F-D");
                  tft.setCursor(40, 210);
                  tft.println("C- F-V");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;

                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)                                   //  PERGUNTAS DO PRIMEIRO ANO DIFICEIS 6 REVISADA
              { 
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("RETANGULO RIMA");
                  tft.setCursor(20, 50);
                  tft.println("COM:");
                  tft.setCursor(40, 110);
                  tft.println("A- CIRCULO");
                  tft.setCursor(40, 160);
                  tft.println("B- QUADRADO");
                  tft.setCursor(40, 210);
                  tft.println("C- TRIANGULO");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else                                         //  PERGUNTAS DO PRIMEIRO ANO DIFICEIS 6 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("COMPLETE AS PALAVRAS:");
                  tft.setCursor(20, 50);
                  tft.println("_ELA  _OCA");
                  tft.setCursor(40, 110);
                  tft.println("A- F-V");
                  tft.setCursor(40, 160);
                  tft.println("B- F-F");
                  tft.setCursor(40, 210);
                  tft.println("C- V-F");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("CONSEGUIMOS!");
              tft.setCursor(150, 70);
              tft.println("OBRIGADA POR");
              tft.setCursor(150, 110);
              tft.println("SUA AJUDA.");
              delay(5000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("JUNTOS SOMOS");
              tft.setCursor(150, 70);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 110);
              tft.println("OURO!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (1);
              delay(5000);
          }
          break;

        case 2:
          if (nivel == 1)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO FACEIS
          {
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO FACEIS 1 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL REPRESENTA");
                  tft.setCursor(20, 50);
                  tft.println("A LETRA: G");
                  tft.setCursor(40, 110);
                  tft.println("A- j");
                  tft.setCursor(40, 160);
                  tft.println("B- g");
                  tft.setCursor(40, 210);
                  tft.println("C- i");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0; 
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("COMPLETE AS CONSOANTES:");
                  tft.setCursor(20, 50);
                  tft.println("RIA__0");
                  tft.setCursor(40, 110);
                  tft.println("A- CH");
                  tft.setCursor(40, 160);
                  tft.println("B- LH");
                  tft.setCursor(40, 210);
                  tft.println("C- NH");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO FACEIS 2 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("COMPLETE A PARLENDA:");
                  tft.setCursor(20, 50);
                  tft.println("_ _ FEIJAO COM ARROZ.");
                  tft.setCursor(40, 110);
                  tft.println("A- DOIS-UM");
                  tft.setCursor(40, 160);
                  tft.println("B- UM-QUATRO");
                  tft.setCursor(40, 210);
                  tft.println("C- UM-DOIS");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg2();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUANTAS SILABAS TEM?");
                  tft.setCursor(20, 50);
                  tft.println("COZINHA");
                  tft.setCursor(40, 110);
                  tft.println("A- 3");
                  tft.setCursor(40, 160);
                  tft.println("B- 2");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("ARRASOU!");
              tft.setCursor(150, 70);
              tft.println("DEPOIS DE 2,");
              tft.setCursor(150, 110);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 150);
              tft.println("BRONZE!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (3);
              delay(5000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO FACEIS 3 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("COMPLETE AS CONSOANTES:");
                  tft.setCursor(20, 50);
                  tft.println("LI __ O");
                  tft.setCursor(40, 110);
                  tft.println("A- VR");
                  tft.setCursor(40, 160);
                  tft.println("B- BR");
                  tft.setCursor(40, 210);
                  tft.println("C- CR");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else //REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUANTAS SILABAS TEM:");
                  tft.setCursor(20, 50);
                  tft.println("PARALELEPIPEDO");
                  tft.setCursor(40, 110);
                  tft.println("A- 7");
                  tft.setCursor(40, 160);
                  tft.println("B- 5");
                  tft.setCursor(40, 210);
                  tft.println("C- 4");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO FACEIS 4 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("COMPLETE AS CONSOANTES:");
                  tft.setCursor(20, 50);
                  tft.println("COE__O");
                  tft.setCursor(40, 110);
                  tft.println("A- LH");
                  tft.setCursor(40, 160);
                  tft.println("B- NH");
                  tft.setCursor(40, 210);
                  tft.println("C- CH");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("DESEMBARALHE AS LETRAS:");
                  tft.setCursor(20, 50);
                  tft.println("P I S L A");
                  tft.setCursor(40, 110);
                  tft.println("A- PISCA");
                  tft.setCursor(40, 160);
                  tft.println("B- LAPIS");
                  tft.setCursor(40, 210);
                  tft.println("C- CAPIS");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;

              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("EBA!");
              tft.setCursor(150, 70);
              tft.println("DEPOIS DE 4,");
              tft.setCursor(150, 110);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 150);
              tft.println("PRATA!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (2);
              delay(5000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO FACEIS 5 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("DESEMBARALHE AS LETRAS:");
                  tft.setCursor(20, 50);
                  tft.println("X I A B A C A");
                  tft.setCursor(40, 110);
                  tft.println("A- ABACAXI");
                  tft.setCursor(40, 160);
                  tft.println("B- CAIXA");
                  tft.setCursor(40, 210);
                  tft.println("C- XICARA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("COMPLETE A PARLENDA:");
                  tft.setCursor(20, 50);
                  tft.println("_ _ REPITO OUTRA VEZ");
                  tft.setCursor(40, 110);
                  tft.println("A- CINCO-SEIS");
                  tft.setCursor(40, 160);
                  tft.println("B- CINCO-SETE");
                  tft.setCursor(40, 210);
                  tft.println("C- SEIS-SETE");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO FACEIS 6 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("COMPLETE A PARLENDA:");
                  tft.setCursor(20, 50);
                  tft.println("_ _ FEIJAO NO PRATO");
                  tft.setCursor(40, 110);
                  tft.println("A- TRES-QUATRO");
                  tft.setCursor(40, 160);
                  tft.println("B- DOIS-QUATRO");
                  tft.setCursor(40, 210);
                  tft.println("C- TRES-CINCO");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("MARQUE A PALAVRA IGUAL:");
                  tft.setCursor(20, 50);
                  tft.println("SABADO");
                  tft.setCursor(40, 110);
                  tft.println("A- SEGUNDA-FEIRA");
                  tft.setCursor(40, 160);
                  tft.println("B- DOMINGO");
                  tft.setCursor(40, 210);
                  tft.println("C- SABADO");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("CONSEGUIMOS!");
              tft.setCursor(150, 70);
              tft.println("OBRIGADA POR");
              tft.setCursor(150, 110);
              tft.println("SUA AJUDA.");
              delay(5000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("JUNTOS SOMOS");
              tft.setCursor(150, 70);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 110);
              tft.println("OURO!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (1);
              delay(5000);

          }
          else          //--------------------------------------------PERGUNTAS DO SEGUNDO ANO DIFICEIS
          {
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO DIFICEIS 1 REVISADA
              {
                  telaperg2();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("COMPLETE O ALFABETO:");
                  tft.setCursor(20, 50);
                  tft.println("A b c d e F G H I j k l m");
                  tft.setCursor(40, 110);
                  tft.println("A- n o p q r s t");
                  tft.setCursor(40, 160);
                  tft.println("B- N O P R S T");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("MARQUE A PALAVRA");
                  tft.setCursor(20, 50);
                  tft.println("MONOSSILABA:");
                  tft.setCursor(40, 110);
                  tft.println("A- GLOBO");
                  tft.setCursor(40, 160);
                  tft.println("B- QUEIJO");
                  tft.setCursor(40, 210);
                  tft.println("C- GOL");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO DIFICEIS 2 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("COMPLETE COM AS SILABAS:");
                  tft.setCursor(20, 50);
                  tft.println("_ _ _ _ _ _ DO");
                  tft.setCursor(40, 110);
                  tft.println("A- QUI-DRO");
                  tft.setCursor(40, 160);
                  tft.println("B- QUA-DRA");
                  tft.setCursor(40, 210);
                  tft.println("C- QUO-DRE");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota ;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else //REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL A PALAVRA?");
                  tft.setCursor(20, 50);
                  tft.println("TE SE");
                  tft.setCursor(40, 110);
                  tft.println("A- SETE");
                  tft.setCursor(40, 160);
                  tft.println("B- SETA");
                  tft.setCursor(40, 210);
                  tft.println("C- SATO");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("ARRASOU!");
              tft.setCursor(150, 70);
              tft.println("DEPOIS DE 2,");
              tft.setCursor(150, 110);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 150);
              tft.println("BRONZE!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (3);
              delay(5000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO DIFICEIS 3 
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL A PALAVRA?");
                  tft.setCursor(20, 50);
                  tft.println("JO EST TO");
                  tft.setCursor(40, 110);
                  tft.println("A- ESTOJO");
                  tft.setCursor(40, 160);
                  tft.println("B- REPOLHO");
                  tft.setCursor(40, 210);
                  tft.println("C- JOELHO");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL A PALAVRA?");
                  tft.setCursor(20, 50);
                  tft.println("LA BO");
                  tft.setCursor(40, 110);
                  tft.println("A- CADO");
                  tft.setCursor(40, 160);
                  tft.println("B- BOCA");
                  tft.setCursor(40, 210);
                  tft.println("C- BOLA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota  + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO DIFICEIS 4 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("DESCUBRA A PALAVRA:");
                  tft.setCursor(20, 50);
                  tft.println("RA GI FA");
                  tft.setCursor(40, 110);
                  tft.println("A- GIRAFA");
                  tft.setCursor(40, 160);
                  tft.println("B- FARMACIA");
                  tft.setCursor(40, 210);
                  tft.println("C- FAROFA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("DESCUBRA A PALAVRA:");
                  tft.setCursor(20, 50);
                  tft.println("PA TO SA");
                  tft.setCursor(40, 110);
                  tft.println("A- BABOSA");
                  tft.setCursor(40, 160);
                  tft.println("B- SAPATO");
                  tft.setCursor(40, 210);
                  tft.println("C- PATOSA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("EBA!");
              tft.setCursor(150, 70);
              tft.println("DEPOIS DE 4,");
              tft.setCursor(150, 110);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 150);
              tft.println("PRATA!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (2);
              delay(5000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO DIFICEIS 5 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("COMPLETE A FRASE:");
                  tft.setCursor(20, 50);
                  tft.println("O __ ESTA BRILHANDO.");
                  tft.setCursor(40, 110);
                  tft.println("A- GATO");
                  tft.setCursor(40, 160);
                  tft.println("B- LIVRO");
                  tft.setCursor(40, 210);
                  tft.println("C- SOL");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else //REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("CORRIJA A PALAVRA:");
                  tft.setCursor(20, 50);
                  tft.println("AMIGOOS");
                  tft.setCursor(40, 110);
                  tft.println("A- AMOR");
                  tft.setCursor(40, 160);
                  tft.println("B- AMIGOS");
                  tft.setCursor(40, 210);
                  tft.println("C- AMIZADE");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO DIFICEIS 6 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("SEPARE CORRETAMENTE:");
                  tft.setCursor(20, 50);
                  tft.println("LUA");
                  tft.setCursor(40, 110);
                  tft.println("A- LUA");
                  tft.setCursor(40, 160);
                  tft.println("B- L-U-A");
                  tft.setCursor(40, 210);
                  tft.println("C- LU-A");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL A SILABA FINAL:");
                  tft.setCursor(20, 50);
                  tft.println("MESA");
                  tft.setCursor(40, 110);
                  tft.println("A- ME");
                  tft.setCursor(40, 160);
                  tft.println("B- MI");
                  tft.setCursor(40, 210);
                  tft.println("C- SA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("CONSEGUIMOS!");
              tft.setCursor(150, 70);
              tft.println("OBRIGADA POR");
              tft.setCursor(150, 110);
              tft.println("SUA AJUDA.");
              delay(5000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("JUNTOS SOMOS");
              tft.setCursor(150, 70);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 110);
              tft.println("OURO!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (1);
              delay(5000);
          } 
          break;

        case 3:
          if (nivel == 1)      //--------------------------------------------PERGUNTAS DO TERCEIRO ANO FACEIS
          {
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO TERCEIRO ANO FACEIS 1 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL CONSOANTE FALTA?");
                  tft.setCursor(20, 50);
                  tft.println("TA_ETE  _INGO");
                  tft.setCursor(40, 110);
                  tft.println("A- P-B");
                  tft.setCursor(40, 160);
                  tft.println("B- P-P");
                  tft.setCursor(40, 210);
                  tft.println("C- B-P");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else //--------------------------------------------PERGUNTAS DO TERCEIRO ANO FACEIS OPÇÃO 1 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL PALAVRA");
                  tft.setCursor(20, 50);
                  tft.println("DISSILABA?");
                  tft.setCursor(40, 110);
                  tft.println("A- APONTADOR");
                  tft.setCursor(40, 160);
                  tft.println("B- LIVRO");
                  tft.setCursor(40, 210);
                  tft.println("C- BORRACHA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO TERCEIRO ANO FACEIS 2 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL CONSOANTE FALTA?");
                  tft.setCursor(20, 50);
                  tft.println("_LOR  _OGUETE");
                  tft.setCursor(40, 110);
                  tft.println("A- V-F");
                  tft.setCursor(40, 160);
                  tft.println("B- F-F");
                  tft.setCursor(40, 210);
                  tft.println("C- F-V");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL PALAVRA");
                  tft.setCursor(20, 50);
                  tft.println("TRISSILABA?");
                  tft.setCursor(40, 110);
                  tft.println("A- PASTA");
                  tft.setCursor(40, 160);
                  tft.println("B- REGUA");
                  tft.setCursor(40, 210);
                  tft.println("C- CADERNO");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("EBA!");
              tft.setCursor(150, 70);
              tft.println("DEPOIS DE 2,");
              tft.setCursor(150, 110);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 150);
              tft.println("BRONZE!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (3);
              delay(5000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO TERCEIRO ANO FACEIS 3 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL CONSOANTE FALTA?");
                  tft.setCursor(20, 50);
                  tft.println("RE_OLHO  CA_EIRA");
                  tft.setCursor(40, 110);
                  tft.println("A- P-D");
                  tft.setCursor(40, 160);
                  tft.println("B- D-P");
                  tft.setCursor(40, 210);
                  tft.println("C- B-D");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;

                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL A PALAVRA");
                  tft.setCursor(20, 50);
                  tft.println("POLISSILABA?");
                  tft.setCursor(40, 110);
                  tft.println("A- DICIONARIO");
                  tft.setCursor(40, 160);
                  tft.println("B- ESTOJO");
                  tft.setCursor(40, 210);
                  tft.println("C- FOLHA");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;

                      }
                      delay(10);
                  }
                  flagnota=0;
                  
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO TERCEIRO ANO FACEIS 4 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL CONSOANTE FALTA?");
                  tft.setCursor(20, 50);
                  tft.println("FLO_  SORVE_E");
                  tft.setCursor(40, 110);
                  tft.println("A- V-R");
                  tft.setCursor(40, 160);
                  tft.println("B- R-D");
                  tft.setCursor(40, 210);
                  tft.println("C- R-T");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA 
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL A PALAVRA");
                  tft.setCursor(20, 50);
                  tft.println("POLISSILABA?");
                  tft.setCursor(40, 110);
                  tft.println("A- BORRACHA");
                  tft.setCursor(40, 160);
                  tft.println("B- TESOURA");
                  tft.setCursor(40, 210);
                  tft.println("C- CORRETIVO");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("EBA!");
              tft.setCursor(150, 70);
              tft.println("DEPOIS DE 4,");
              tft.setCursor(150, 110);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 150);
              tft.println("PRATA!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (2);
              delay(5000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO TERCEIRO ANO FACEIS 5 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("R ou RR:");
                  tft.setCursor(20, 50);
                  tft.println("_EDE  _OUPA");
                  tft.setCursor(40, 110);
                  tft.println("A- R-RR");
                  tft.setCursor(40, 160);
                  tft.println("B- R-R");
                  tft.setCursor(40, 210);
                  tft.println("C- RR-R");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("X ou CH:");
                  tft.setCursor(20, 50);
                  tft.println("LI_O  CAI_A");
                  tft.setCursor(40, 110);
                  tft.println("A- X-X");
                  tft.setCursor(40, 160);
                  tft.println("B- CH-X");
                  tft.setCursor(40, 210);
                  tft.println("C- X-CH");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO TERCEIRO ANO FACEIS 6 REVISA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("S ou SS:");
                  tft.setCursor(20, 50);
                  tft.println("CA_A  ME_A");
                  tft.setCursor(40, 110);
                  tft.println("A- S-SS");
                  tft.setCursor(40, 160);
                  tft.println("B- SS-S");
                  tft.setCursor(40, 210);
                  tft.println("C- S-S");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("S ou Z:");
                  tft.setCursor(20, 50);
                  tft.println("_ERO  _IPER");
                  tft.setCursor(40, 110);
                  tft.println("A- Z-S");
                  tft.setCursor(40, 160);
                  tft.println("B- Z-Z");
                  tft.setCursor(40, 210);
                  tft.println("C- S-Z");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("CONSEGUIMOS!");
              tft.setCursor(150, 70);
              tft.println("OBRIGADA POR");
              tft.setCursor(150, 110);
              tft.println("SUA AJUDA.");
              delay(5000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("JUNTOS SOMOS");
              tft.setCursor(150, 70);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 110);
              tft.println("OURO!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (1);
              delay(5000);
          
          }
          else               //--------------------------------------------PERGUNTAS DO TERCEIRO ANO DIFICEIS
          {
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO TERCEIRO ANO DIFICEIS 1 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL O SINAL?");
                  tft.setCursor(20, 50);
                  tft.println("QUAL O SEU NOME _");
                  tft.setCursor(40, 110);
                  tft.println("A- .");
                  tft.setCursor(40, 160);
                  tft.println("B- ?");
                  tft.setCursor(40, 210);
                  tft.println("C- !");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else //--------------------------------------------PERGUNTAS DO TERCEIRO ANO DIFICEIS OPÇÃO 1 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL O SINAL?");
                  tft.setCursor(20, 50);
                  tft.println("QUE DIA LINDO_");
                  tft.setCursor(40, 110);
                  tft.println("A- !");
                  tft.setCursor(40, 160);
                  tft.println("B- ,");
                  tft.setCursor(40, 210);
                  tft.println("C- ;");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota  + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO TERCEIRO ANO DIFICEIS 2 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("SEPARE AS PALAVRAS:");
                  tft.setCursor(20, 50);
                  tft.println("OCACHORROLATE.");
                  tft.setCursor(40, 110);
                  tft.println("A- o cachorrolate.");
                  tft.setCursor(40, 160);
                  tft.println("B- O cachorro late.");
                  tft.setCursor(40, 210);
                  tft.println("C- ocachorro late.");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // revisada
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("SEPARE AS PALAVRAS:");
                  tft.setCursor(20, 50);
                  tft.println("NAESCOLATEMMESA");
                  tft.setCursor(40, 110);
                  tft.println("A- na escolat em mesa");
                  tft.setCursor(40, 160);
                  tft.println("B- na escola tem mesa");
                  tft.setCursor(40, 210);
                  tft.println("C- Na escola tem mesa");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;

                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("EBA!");
              tft.setCursor(150, 70);
              tft.println("DEPOIS DE 2,");
              tft.setCursor(150, 110);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 150);
              tft.println("BRONZE!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (3);
              delay(5000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO TERCEIRO ANO DIFICEIS 3 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL A ESCRITA?");
                  tft.setCursor(20, 50);
                  tft.println("150");
                  tft.setCursor(40, 110);
                  tft.println("A- CENTO E QUARENTA");
                  tft.setCursor(40, 160);
                  tft.println("B- CENTO E CINQUENTA");
                  tft.setCursor(40, 210);
                  tft.println("C- CENTO E CINCO");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;

                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL A ESCRITA?");
                  tft.setCursor(20, 50);
                  tft.println("600");
                  tft.setCursor(40, 110);
                  tft.println("A- SEISCENTOS.");
                  tft.setCursor(40, 160);
                  tft.println("B- NOVECENTOS.");
                  tft.setCursor(40, 210);
                  tft.println("C- SETESSENTOS.");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;

                      }
                      delay(10);
                  }
                  flagnota=0;
                  
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO TERCEIRO ANO DIFICEIS 4 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL O SINAL?");
                  tft.setCursor(20, 50);
                  tft.println("EU GOSTO DE GATO_");
                  tft.setCursor(40, 110);
                  tft.println("A- ,");
                  tft.setCursor(40, 160);
                  tft.println("B- .");
                  tft.setCursor(40, 210);
                  tft.println("C- ?");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;

                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else // REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL O SINAL?");
                  tft.setCursor(20, 50);
                  tft.println("VAI A AULA HOJE_");
                  tft.setCursor(40, 110);
                  tft.println("A- ;");
                  tft.setCursor(40, 160);
                  tft.println("B- ?");
                  tft.setCursor(40, 210);
                  tft.println("C- !");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;

                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("EBA!");
              tft.setCursor(150, 70);
              tft.println("DEPOIS DE 4,");
              tft.setCursor(150, 110);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 150);
              tft.println("PRATA!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (2);
              delay(5000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO TERCEIRO ANO DIFICEIS 5 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("SEPARE AS PALAVRAS:");
                  tft.setCursor(20, 50);
                  tft.println("EUCOMIBOLACHA");
                  tft.setCursor(40, 110);
                  tft.println("A- Eu comi laranja.");
                  tft.setCursor(40, 160);
                  tft.println("B- eu comibolacha.");
                  tft.setCursor(40, 210);
                  tft.println("C- Eu comi bolacha.");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;

                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else //REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL O SINAL?");
                  tft.setCursor(20, 50);
                  tft.println("QUE CALOR_");
                  tft.setCursor(40, 110);
                  tft.println("A- ,");
                  tft.setCursor(40, 160);
                  tft.println("B- :");
                  tft.setCursor(40, 210);
                  tft.println("C- !");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota + 1;
                          flagnota = 1;

                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//--------------------------------------------PERGUNTAS DO TERCEIRO ANO DIFICEIS 6 REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL O SINAL?");
                  tft.setCursor(20, 50);
                  tft.println("MINHA CASA TEM PORTA");
                  tft.setCursor(40, 110);
                  tft.println("A- .");
                  tft.setCursor(40, 160);
                  tft.println("B- :");
                  tft.setCursor(40, 210);
                  tft.println("C- ,");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;

                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              else //REVISADA
              {
                  telaperg3();
                  tft.setCursor(20, 20);
                  tft.setTextColor(BLACK);
                  tft.setTextSize(2);
                  tft.println("QUAL A ESCRITA?");
                  tft.setCursor(20, 50);
                  tft.println("1000");
                  tft.setCursor(40, 110);
                  tft.println("A- MIL.");
                  tft.setCursor(40, 160);
                  tft.println("B- CEM.");
                  tft.setCursor(40, 210);
                  tft.println("C- MIL E UM.");
                  while (flagnota ==0 )
                  {
                      if (digitalRead(bta) == 0) //A
                      {
                          nota= nota + 1;
                          flagnota = 1;
                      }
                      if (digitalRead(btb) == 0)//B
                      {
                          nota= nota;
                          flagnota = 1;
                      }
                      if (digitalRead(btc) == 0)//C
                      {
                          nota= nota;
                          flagnota = 1;

                      }
                      delay(10);
                  }
                  flagnota=0;
              }
              delay(2000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("CONSEGUIMOS!");
              tft.setCursor(150, 70);
              tft.println("OBRIGADA POR");
              tft.setCursor(150, 110);
              tft.println("SUA AJUDA.");
              delay(5000);
              dialogo();
              tft.setCursor(150, 30);
              tft.setTextColor(BLACK);
              tft.setTextSize(2);
              tft.println("JUNTOS SOMOS");
              tft.setCursor(150, 70);
              tft.println("MEDALHA DE");
              tft.setCursor(150, 110);
              tft.println("OURO!");
              delay(5000);
              puloalfa(3);
              delay(2000);
              medalha (1);
              delay(5000); 
          }
          break;
      
    }

    alfaebeto();
    delay(5000);
    dialogo();
    tft.setCursor(150, 30);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.println("VOU PARA O");
    tft.setCursor(150, 70);
    tft.println("RECREIO.");
    tft.setCursor(150, 130);
    tft.println("TCHAU!");
    while (digitalRead(btd) == 1) //A
    {
    }
    dialogo();
    tft.setCursor(150, 30);
    tft.setTextColor(BLACK);
    tft.setTextSize(3);
    tft.println("NOTA:");
    tft.setCursor(150, 70);
    tft.println(nota);
    Serial.print("NOTA:");
    Serial.println(nota);
    while (digitalRead(btd) == 1) //A
    {
    }
}

void bateria (void)
{
  mappedValue = map(analogRead(A0), 0, 4095, 0, 3.3); 
  Serial.print("analogRead: ");
  Serial.println(mappedValue); 
  delay(200);

  if (mappedValue > 3.1 )
  {
    tft.fillRect(3, 3, 50, 25, AZULCEU);  //(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    tft.fillRect(4, 4, 40, 24, BLUE);  //(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    tft.fillRect(40, 11, 10, 10, BLUE);
  }
  if (mappedValue < 3.2 && mappedValue> 2.9)
  {
    tft.fillRect(3, 3, 50, 25, AZULCEU);  //(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    tft.fillRect(4, 4, 40, 24, GREEN);  //(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    tft.fillRect(40, 11, 10, 10, GREEN);
  }
  if (mappedValue < 3.0 )
  {
    tft.fillRect(3, 3, 50, 25, AZULCEU);  //(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    tft.fillRect(4, 4, 40, 24, RED);  //(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    tft.fillRect(40, 11, 10, 10, RED); 
  }
}

void telacarregamento(void)
{
    barra(10);
    delay(250);
    barra(20);
    delay(250);
    barra(30);
    delay(250);
    barra(40);
    delay(250);
    barra(50);
    delay(250);
    barra(60);
    delay(250);
    barra(70);
    delay(250);
    barra(80);
    delay(250);
    barra(90);
    delay(250);
    barra(100);
    delay(250);
}
void barra (int porcent)
{
  //(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
  tft.drawRoundRect(60, 90, 200, 30, 5, WHITE); // ALFA  +21,11
  if (porcent == 10)
  {
    tft.fillRoundRect(60, 90, 200, 30, 5, BLACK);
    delay(500);
    tft.fillRoundRect(65, 94, 19, 22, 5, YELLOW); //10%
  }
  if (porcent == 20)
  {
    tft.fillRoundRect(60, 90, 200, 30, 5, BLACK); 
    tft.fillRoundRect(65, 94, 19, 22, 5, YELLOW); //10%
    delay(500);
    tft.fillRoundRect(65, 94, 38, 22, 5, YELLOW); //20%
  }
  if (porcent == 30)
  {
    tft.fillRoundRect(60, 90, 200, 30, 5, BLACK);
    tft.fillRoundRect(65, 94, 38, 22, 5, YELLOW); //20%
    delay(500);
    tft.fillRoundRect(65, 94, 57, 22, 5, YELLOW); //30%
  }
  if (porcent == 40)
  {
    tft.fillRoundRect(60, 90, 200, 30, 5, BLACK); 
    tft.fillRoundRect(65, 94, 57, 22, 5, YELLOW); //30%
    delay(500);
    tft.fillRoundRect(65, 94, 76, 22, 5, YELLOW); //40%
  }
  if (porcent == 50)
  {
    tft.fillRoundRect(60, 90, 200, 30, 5, BLACK); 
    tft.fillRoundRect(65, 94, 76, 22, 5, YELLOW); //40%
    delay(500);
    tft.fillRoundRect(65, 94, 95, 22, 5, YELLOW); //50%
  }
  if (porcent == 60)
  {
    tft.fillRoundRect(60, 90, 200, 30, 5, BLACK); 
    tft.fillRoundRect(65, 94, 95, 22, 5, YELLOW); //50%
    delay(500);
    tft.fillRoundRect(65, 94, 114, 22, 5, YELLOW); //60%
  }
  if (porcent == 70)
  {
    tft.fillRoundRect(60, 90, 200, 30, 5, BLACK); 
    tft.fillRoundRect(65, 94, 114, 22, 5, YELLOW); //60%
    delay(500);
    tft.fillRoundRect(65, 94, 133, 22, 5, YELLOW); //70%
  }
  if (porcent == 80)
  {
    tft.fillRoundRect(60, 90, 200, 30, 5, BLACK); 
    tft.fillRoundRect(65, 94, 133, 22, 5, YELLOW); //70%
    delay(500);
    tft.fillRoundRect(65, 94, 152, 22, 5, YELLOW); //80%
  }
  if (porcent == 90)
  {
    tft.fillRoundRect(60, 90, 200, 30, 5, BLACK);
    tft.fillRoundRect(65, 94, 152, 22, 5, YELLOW); //80%
    delay(500);
    tft.fillRoundRect(65, 94, 171, 22, 5, YELLOW); //90%
  }
  if (porcent == 100)
  {
    tft.fillRoundRect(60, 90, 200, 30, 5, BLACK); 
    tft.fillRoundRect(65, 94, 171, 22, 5, YELLOW); //90%
    delay(500);
    tft.fillRoundRect(65, 94, 190, 22, 5, YELLOW); //100%
  }
}

void alfaebeto(void)
{
  tft.fillScreen(CINZA);
  ////////////////////////////////////////////////////////////////////////ALFA
  tft.drawCircle(70, 170, 50, YELLOW); // ALFA
  tft.fillCircle(70, 170, 50, YELLOW); // ALFA
  tft.fillCircle(55, 150, 12, WHITE); // OLHO ESQUERDA
  tft.fillCircle(55, 150, 3, BLACK); // OLHO ESQUERDA
  tft.fillCircle(86, 150, 12, WHITE); // OLHO DIREITO
  tft.fillCircle(86, 150, 3, BLACK); // OLHO DIREITO
  tft.setCursor(67, 165);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.println("U");
  tft.fillRoundRect(34, 175, 24, 10,3, RED);// BOCHECHA ESQUERDA
  tft.fillRoundRect(88, 175, 24, 10,3, RED);// BOCHECHA DIREITA

  ////////////////////////////////////////////////////////////////////////BETO

  tft.fillRect(180, 40, 110, 180, AZULCEU); 
  tft.fillCircle(205, 110, 10, RED); // BOCHECHA ESQUERDA
  tft.fillCircle(265, 110, 10, RED); // BOCHECHA ESQUERDA
  tft.drawCircle(235, 110, 13, BLACK); // BOCA DO BETO
  tft.fillRect(220, 85, 30, 30, AZULCEU); 
  tft.fillRoundRect(228, 90, 15, 25, 10, WHITE); //NARIZ BETO
  tft.fillCircle(215, 80, 12, WHITE); // OLHO ESQUERDA
  tft.fillCircle(215, 80, 3, BLACK); // OLHO ESQUERDA
  tft.fillCircle(255, 80, 12, WHITE); // OLHO DIREITO
  tft.fillCircle(255, 80, 3, BLACK); // OLHO DIREITO
}

void puloalfa(int nump)
{
  fundo();
  for (int i=0; i<=nump-1; i++)
  {
    //------------------------------------------PULO
    tft.fillRect(10, 40, 180, 160, AZULCEU); 
    tft.fillRect(1, 200, 320, 40, GREEN); //GRAMA
    bateria ();
    tft.drawCircle(70, 160, 50, YELLOW); // ALFA
    tft.fillCircle(70, 160, 50, YELLOW); // ALFA
    tft.fillCircle(55, 140, 12, WHITE); // OLHO ESQUERDA
    tft.fillCircle(55, 140, 3, BLACK); // OLHO ESQUERDA
    tft.fillCircle(86, 140, 12, WHITE); // OLHO DIREITO
    tft.fillCircle(86, 140, 3, BLACK); // OLHO DIREITO
    tft.setCursor(67, 155);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.println("U");
    tft.fillRoundRect(34, 165, 24, 10,3, RED);// BOCHECHA ESQUERDA
    tft.fillRoundRect(88, 165, 24, 10,3, RED);// BOCHECHA 
    delay(100);
    tft.fillRect(10, 40, 180, 160, AZULCEU); 
    tft.fillRect(1, 200, 320, 40, GREEN); //GRAMA
    tft.drawCircle(70, 140, 50, YELLOW); // ALFA
    tft.fillCircle(70, 140, 50, YELLOW); // ALFA
    tft.fillCircle(55, 120, 12, WHITE); // OLHO ESQUERDA
    tft.fillCircle(55, 120, 3, BLACK); // OLHO ESQUERDA
    tft.fillCircle(86, 120, 12, WHITE); // OLHO DIREITO
    tft.fillCircle(86, 120, 3, BLACK); // OLHO DIREITO
    tft.setCursor(67, 135);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.println("o");
    tft.fillRoundRect(34, 145, 24, 10,3, RED);// BOCHECHA ESQUERDA
    tft.fillRoundRect(88, 145, 24, 10,3, RED);// BOCHECHA DIREITA
    delay(100);
    tft.fillRect(10, 40, 180, 160, AZULCEU); 
    tft.fillRect(1, 200, 320, 40, GREEN); //GRAMA
    tft.drawCircle(70, 120, 50, YELLOW); // ALFA
    tft.fillCircle(70, 120, 50, YELLOW); // ALFA
    tft.fillCircle(55, 100, 12, WHITE); // OLHO ESQUERDA
    tft.fillCircle(55, 100, 3, BLACK); // OLHO ESQUERDA
    tft.fillCircle(86, 100, 12, WHITE); // OLHO DIREITO
    tft.fillCircle(86, 100, 3, BLACK); // OLHO DIREITO
    tft.setCursor(67, 115);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.println("o");
    tft.fillRoundRect(34, 125, 24, 10,3, RED);// BOCHECHA ESQUERDA
    tft.fillRoundRect(88, 125, 24, 10,3, RED);// BOCHECHA DIREITA
    delay(100);
    tft.fillRect(10, 40, 180, 160, AZULCEU); 
    tft.fillRect(1, 200, 320, 40, GREEN); //GRAMA
    tft.drawCircle(70, 140, 50, YELLOW); // ALFA
    tft.fillCircle(70, 140, 50, YELLOW); // ALFA
    tft.fillCircle(55, 120, 12, WHITE); // OLHO ESQUERDA
    tft.fillCircle(55, 120, 3, BLACK); // OLHO ESQUERDA
    tft.fillCircle(86, 120, 12, WHITE); // OLHO DIREITO
    tft.fillCircle(86, 120, 3, BLACK); // OLHO DIREITO
    tft.setCursor(67, 135);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.println("o");
    tft.fillRoundRect(34, 145, 24, 10,3, RED);// BOCHECHA ESQUERDA
    tft.fillRoundRect(88, 145, 24, 10,3, RED);// BOCHECHA DIREITA
    tft.fillRect(10, 40, 180, 160, AZULCEU);  
    tft.fillRect(1, 200, 320, 40, GREEN); //GRAMA
    delay(100);
    tft.drawCircle(70, 160, 50, YELLOW); // ALFA
    tft.fillCircle(70, 160, 50, YELLOW); // ALFA
    tft.fillCircle(55, 140, 12, WHITE); // OLHO ESQUERDA
    tft.fillCircle(55, 140, 3, BLACK); // OLHO ESQUERDA
    tft.fillCircle(86, 140, 12, WHITE); // OLHO DIREITO
    tft.fillCircle(86, 140, 3, BLACK); // OLHO DIREITO
    tft.setCursor(67, 155);
    tft.setTextColor(BLACK);
    tft.setTextSize(2);
    tft.println("U");
    tft.fillRoundRect(34, 165, 24, 10,3, RED);// BOCHECHA ESQUERDA
    tft.fillRoundRect(88, 165, 24, 10,3, RED);// BOCHECHA DIREITA
    //------------------------------------------PULO
  }
}

void medalha (int posi)
{
  fundo();
  tft.fillRect(1, 200, 320, 40, GREEN); //GRAMA
  bateria ();
  tft.fillTriangle(90, 40, 160, 140, 230, 40, WHITE);
  tft.fillTriangle(110, 50, 160, 120, 215, 50, AZULCEU);
    
  if (posi == 3)
  {
    tft.fillCircle(160, 160, 25, WHITE); // ALFA
    tft.fillCircle(160, 160, 25, BRONZE); // ALFA
  }
  if (posi == 2)
  {
    tft.fillCircle(160, 160, 25, WHITE); // ALFA
    tft.fillCircle(160, 160, 25, CINZA); // ALFA
  }
  if (posi == 1)
  {
    tft.fillCircle(160, 160, 25, WHITE); // ALFA
    tft.fillCircle(160, 160, 25, OURO); // ALFA
  }
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
        telanota(1); // acertou
        nota = nota + 1;
    }
    else
    {
        telanota(0);
        nota = nota;
    }
    flagnota=0;
}


void telaperg2(void)
{
  fundo();
  tft.fillRect(1, 200, 320, 40, GREEN); 
  tft.fillRect(10, 5, 305, 80, WHITE);
  tft.fillRect(30, 95, 260, 40, WHITE); 
  tft.fillRect(30, 145, 260, 40, WHITE); 
}

void telaperg3(void)
{
  fundo();
  tft.fillRect(1, 200, 320, 40, GREEN);
  tft.fillRect(10, 5, 305, 80, WHITE); 
  tft.fillRect(30, 95, 260, 40, WHITE); 
  tft.fillRect(30, 145, 260, 40, WHITE); 
  tft.fillRect(30, 195, 260, 40, WHITE); 
}

void dialogo(void)
{
  fundo();
  bateria ();
  tft.drawCircle(70, 120, 50, YELLOW); // ALFA
  tft.fillCircle(70, 120, 50, YELLOW); // ALFA
  tft.fillCircle(55, 100, 12, WHITE); // OLHO ESQUERDA
  tft.fillCircle(55, 100, 3, BLACK); // OLHO ESQUERDA
  tft.fillCircle(86, 100, 12, WHITE); // OLHO DIREITO
  tft.fillCircle(86, 100, 3, BLACK); // OLHO DIREITO
  tft.setCursor(67, 115);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.println("U");
  tft.fillRoundRect(34, 125, 24, 10,3, RED);// BOCHECHA ESQUERDA
  tft.fillRoundRect(88, 125, 24, 10,3, RED);// BOCHECHA DIREITA
  tft.fillTriangle(130, 125, 150, 110, 160, 160, WHITE);//BALÃO DE DIALOGO
  tft.fillRect(140, 20, 160, 160, WHITE); //BALÃO DE DIALOGO
}

void fundo(void)
{
  tft.fillScreen(AZULCEU);
  tft.fillRect(1, 200, 320, 40, GREEN);
}

void telanota(int retornonota)
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