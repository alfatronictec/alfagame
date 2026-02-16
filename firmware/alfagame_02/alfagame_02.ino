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

void telacarregamento(void);
void dialogo(void);
void puloalfa(int nump);
void alfaebeto(void);
void telanota(int retornonota);
void tela_pergunta(const char* frase1, const char* frase2, const char* frase3, const char* frase4, const char* frase5, int resp_correta);
void tela_bronze(void);
void tela_prata(void);
void tela_ouro(void);

//Setup
void setup(void)
{
  Serial.begin(115200);
  Serial.println("");
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(AZULCEU);
  tft.fillRect(1, 200, 320, 40, GREEN);
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
      tft.fillScreen(AZULCEU);
      tft.fillRect(1, 200, 320, 40, GREEN);
      tft.fillRect(1, 200, 320, 40, GREEN);
      tft.fillRect(10, 5, 305, 80, WHITE); 
      tft.fillRect(30, 95, 260, 40, WHITE); 
      tft.fillRect(30, 145, 260, 40, WHITE); 
      tft.fillRect(30, 195, 260, 40, WHITE); 
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
      tft.fillScreen(AZULCEU);
      tft.fillRect(1, 200, 320, 40, GREEN);
      tft.fillRect(1, 200, 320, 40, GREEN); 
      tft.fillRect(10, 5, 305, 80, WHITE);
      tft.fillRect(30, 95, 260, 40, WHITE); 
      tft.fillRect(30, 145, 260, 40, WHITE); 
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
          if (nivel == 1)//PERGUNTAS DO PRIMEIRO ANO FACEIS REVISADAS
          {
              delay(1000);
              p1 = random(3); 
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)//PERGUNTAS DO PRIMEIRO ANO FACEIS 1 REVISADA
              {
                tela_pergunta("JUNTE AS VOGAIS:", "A + I =","A- AI","B- IA","C- AE",1);
              }
              else if (p1==1)
              {
                tela_pergunta("JUNTE AS VOGAIS:", "I + A =","A- AI","B- IA","C- AE",2);
              }
              else 
              {
                tela_pergunta("JUNTE AS VOGAIS:", "E + U =","A- UE","B- EU","C- UA",2);

              }

              delay(1000);
              p1 = random(3);  
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0) //PERGUNTAS DO PRIMEIRO ANO FACEIS 2 REVISADA
              {
                tela_pergunta("QUAL PALAVRA QUE INICIA", "COM A MESMA LETRA: SOL","A- RATO","B- SAPO","C- TOSA",2);
              }
              else if (p1 == 1)
              {
                tela_pergunta("QUAL PALAVRA QUE INICIA", "COM A MESMA LETRA: RIR","A- RATO","B- SAPO","C- TOSA",1);
              }
              else 
              {
                tela_pergunta("QUAL PALAVRA QUE INICIA", "COM A MESMA LETRA: CASA","A- CAMA","B- MACA","C- BALA",1);
              }

              tela_bronze();

              p1 = random(3);  // retorna 0, 1 ou 2
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
        
              if (p1==0)//PERGUNTAS DO PRIMEIRO ANO FACEIS 3 REVISADA
              {
                tela_pergunta("JUNTE AS VOGAIS:", "U + I =","A- IAU","B- UO","C- UI",3);
              }
              else if (p1==1)
              {
                tela_pergunta("JUNTE AS VOGAIS:", "A + U =","A- AU","B- UO","C- IU",1);
              }
              else 
              {
                tela_pergunta("JUNTE AS VOGAIS:", "A + O =","A- OA","B- AO","C- UI",2);
              }

              delay(1000);
              p1 = random(3); 
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
        
              if (p1==0)//PERGUNTAS DO PRIMEIRO ANO FACEIS 4 REVISADA
              {
                tela_pergunta("QUAL PALAVRA QUE INICIA", "COM A MESMA LETRA: GATO","A- JOGO","B- HORA","C- GOLA",3);
              }
              else if (p1==1)
              {
                tela_pergunta("QUAL PALAVRA QUE INICIA", "COM A MESMA LETRA: JAULA","A- JOGO","B- HORA","C- GOLA",1);
              }
              else
              {
                tela_pergunta("QUAL PALAVRA QUE INICIA", "COM A MESMA LETRA: LIVRO","A- VIDRO","B- LAPIS","C- SINO",2);
              }

              tela_prata();

              p1 = random(3); 
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO PRIMEIRO ANO FACEIS 5 REVISA
              {
                tela_pergunta("JUNTE AS VOGAIS", "O + I =","A- IO","B- IUO","C- OI",3);
              }
              else if (p1==1)
              {
                tela_pergunta("JUNTE AS VOGAIS", "A + I =","A- IO","B- AI","C- AU",2);
              }
              else
              {
                tela_pergunta("JUNTE AS VOGAIS", "E + I =","A- EIA","B- EI","C- OU",2);
              }

              delay(1000);
              p1 = random(3);  // retorna 0, 1 ou 2
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)//--------------------------------------------PERGUNTAS DO PRIMEIRO ANO FACEIS 6 REVISADA
              {
                tela_pergunta("QUANTAS LETRAS TEM", "A PALAVRA: LUA","A- 5","B- 3","C- 6",2);
              }
              else if (p1 == 1)
              {
                tela_pergunta("QUANTAS LETRAS TEM", "A PALAVRA: BALA","A- 5","B- 3","C- 4",3);             
              }
              else
              {
                tela_pergunta("QUANTAS LETRAS TEM", "A PALAVRA: CHUVA","A- 5","B- 3","C- 6",1);
              }

              tela_ouro();
          }
          //----------------------------------------------------PERGUNTAS DO PRIMEIRO ANO DIFICEIS----------------------------------------------------------------------------------
          else
          {
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)//PERGUNTAS DO PRIMEIRO ANO DIFICEIS 1
              {
                tela_pergunta("COMPLETE A ORDEM DAS VOGAIS:", "A __ I __ __","A- E U O","B- E I O","C- E O U",3);
              }
              else
              {
                tela_pergunta("QUAL A VOGAL QUE FALTA?", "AN__L","A- U","B- I","C- E",3);
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)//PERGUNTAS DO PRIMEIRO ANO DIFICEIS 2
              {
                tela_pergunta("OVELHA RIMA COM:", "","A- ABELHA","B- AREIA","C- COLMEIA",1);
              }
              else
              {
                tela_pergunta("COMPLETE A ORDEM:", "A B C D E F __ __ __","A-  G - H - I ","B-  J - K - L","C-  G - J - L ",1);
              }

              tela_bronze();

              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)//PERGUNTAS DO PRIMEIRO ANO DIFICEIS 3
              {
                tela_pergunta("QUAIS VOGAIS FALTAM:", "__ I T __", "A-  A - U", "B-  O - O", "C-  O - U", 2);
              }
              else                                       
              {
                tela_pergunta("QUEM VEM ANTES E DEPOIS:", "__ M __", "A- L _ N", "B- N _ L", "C - O _ P", 1);
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO PRIMEIRO ANO DIFICEIS 4
              {
                tela_pergunta("SOL NAO", "RIMA COM:", "A- FAROL", "B- NUVEM", "C- ANZOL", 2);
              }
              else
              {
                tela_pergunta("QUAIS AS LETRAS FALTANTES:", "_ B C D _ F G H _ J", "A- VOGAIS", "B- CONSOANTES", "C- AMBAS", 1);
              }

              tela_prata();

              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO PRIMEIRO ANO DIFICEIS 5
              {
                tela_pergunta("MARQUE A PALAVRA", "COM 3 VOGAIS:", "A- QUEIJO", "B- PAO", "C- BANANA", 3);
              }
              else
              {
                tela_pergunta("QUAIS AS CONSOANTES FALTAM:", "_ A _ A", "A- D-F", "B- F-D", "C- F-V", 2);
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0) // PERGUNTAS DO PRIMEIRO ANO DIFICEIS 6
              {
                tela_pergunta("RETANGULO RIMA", "COM:", "A- CIRCULO", "B- QUADRADO", "C- TRIANGULO", 3);
              }
              else
              {
                tela_pergunta("COMPLETE AS PALAVRAS:", "_ELA  _OCA", "A- F-V", "B- F-F", "C- V-F", 3);
              }

              tela_ouro();
          }
          break;

        case 2:
          if (nivel == 1)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO FACEIS
          {
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)//--------------------------------------------PERGUNTAS DO SEGUNDO ANO FACEIS 1
              {
                tela_pergunta("QUAL REPRESENTA", "A LETRA: G", "A- j", "B- g", "C- i", 2); 
              }
              else 
              {
                tela_pergunta("COMPLETE AS CONSOANTES:", "RIA__0", "A- CH", "B- LH", "C- NH", 1);
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO SEGUNDO ANO FACEIS 2 
              {
                tela_pergunta("COMPLETE A PARLENDA:", "_ _ FEIJAO COM ARROZ.", "A- DOIS-UM", "B- UM-QUATRO", "C- UM-DOIS", 3);
              }
              else 
              {
                tela_pergunta("QUANTAS SILABAS TEM:", "COZINHA", "A- 3", "B- 2", "C- 4", 1);
              }

              tela_bronze();

              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)//PERGUNTAS DO SEGUNDO ANO FACEIS 3
              {
                tela_pergunta("COMPLETE AS CONSOANTES:", "LI __ O", "A- VR", "B- BR", "C- CR", 1);
              }
              else
              {
                tela_pergunta("QUANTAS SILABAS TEM:", "PARALELEPIPEDO", "A- 7", "B- 5", "C- 4", 1);
              }
              
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO SEGUNDO ANO FACEIS 4
              {
                tela_pergunta("COMPLETE AS CONSOANTES:", "COE__O", "A- LH", "B- NH", "C- CH", 1);
              }
              else
              {
                tela_pergunta("DESEMBARALHE AS LETRAS:", "P I S L A", "A- PISCA", "B- LAPIS", "C- CAPIS", 2);
              }

              tela_prata();

              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO SEGUNDO ANO FACEIS 5
              {
                tela_pergunta("DESEMBARALHE AS LETRAS:", "X I A B A C A", "A- ABACAXI", "B- CAIXA", "C- XICARA", 1);
              }
              else
              {
                tela_pergunta("COMPLETE A PARLENDA:", "_ _ REPITO OUTRA VEZ", "A- CINCO-SEIS", "B- CINCO-SETE", "C- SEIS-SETE", 1);
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO SEGUNDO ANO FACEIS 6
              {
                tela_pergunta("COMPLETE A PARLENDA:", "_ _ FEIJAO NO PRATO", "A- TRES-QUATRO", "B- DOIS-QUATRO", "C- TRES-CINCO", 1);
              }
              else
              {
                tela_pergunta("MARQUE A PALAVRA IGUAL:", "SABADO", "A- SEGUNDA-FEIRA", "B- DOMINGO", "C- SABADO", 3);
              }

              tela_ouro();
          }

          else  // PERGUNTAS DO SEGUNDO ANO DIFICEIS
          {
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO SEGUNDO ANO DIFICEIS 1
              {
                tela_pergunta("COMPLETE O ALFABETO:", "A b c d e F G H I j k l m", "A- n o p q r s t", "B- N O P R S T", "B- N o p S T", 1);
              }
              else
              {
                tela_pergunta("MARQUE A PALAVRA", "MONOSSILABA:", "A- GLOBO", "B- QUEIJO", "C- GOL", 3);
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO SEGUNDO ANO DIFICEIS 2
              {
                tela_pergunta("COMPLETE COM AS SILABAS:", "_ _ _ _ _ _ DO", "A- QUI-DRO", "B- QUA-DRA", "C- QUO-DRE", 2);
              }
              else
              {
                tela_pergunta("DESCUBRA A PALAVRA:", "TE SE", "A- SETE", "B- SETA", "C- SATO", 1);
              }

              tela_bronze();

              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO SEGUNDO ANO DIFICEIS 3 
              {
                tela_pergunta("DESCUBRA A PALAVRA:", "JO EST TO", "A- ESTOJO", "B- REPOLHO", "C- JOELHO", 1);
              }
              else
              {
                tela_pergunta("DESCUBRA A PALAVRA:", "LA BO", "A- CADO", "B- BOCA", "C- BOLA", 3);
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)//  PERGUNTAS DO SEGUNDO ANO DIFICEIS 4
              {
                tela_pergunta("DESCUBRA A PALAVRA:", "RA GI FA", "A- GIRAFA", "B- FARMACIA", "C- FAROFA", 1);
              }
              else
              {
                tela_pergunta("DESCUBRA A PALAVRA:", "PA TO SA", "A- BABOSA", "B- SAPATO", "C- PATOSA", 2);
              }

              tela_prata();

              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO SEGUNDO ANO DIFICEIS 5 REVISADA
              {
                tela_pergunta("COMPLETE A FRASE:", "O __ ESTA BRILHANDO.", "A- GATO", "B- LIVRO", "C- SOL", 3);
              }
              else 
              {
                tela_pergunta("CORRIJA A PALAVRA:", "AMIGOOS", "A- AMOR", "B- AMIGOS", "C- AMIZADE", 2);
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO SEGUNDO ANO DIFICEIS 6
              {
                tela_pergunta("SEPARE CORRETAMENTE:", "LUA", "A- LUA", "B- L-U-A", "C- LU-A", 3);
              }
              else
              {
                tela_pergunta("QUAL A SILABA FINAL:", "MESA", "A- ME", "B- MI", "C- SA", 3);
              }
              
              tela_ouro();
          } 
          break;

        case 3:
          if (nivel == 1)      //--------------------------------------------PERGUNTAS DO TERCEIRO ANO FACEIS
          {
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);
              if (p1==0)// PERGUNTAS DO TERCEIRO ANO FACEIS 1
              {
                tela_pergunta("QUAL CONSOANTE FALTA?", "TA_ETE  _INGO", "A- P-B", "B- P-R", "C- B-P", 1);
              }
              else
              {
                tela_pergunta("QUAL PALAVRA", "DISSILABA?", "A- APONTADOR", "B- LIVRO", "C- BORRACHA", 2);
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO TERCEIRO ANO FACEIS 2 REVISADA
              {
                tela_pergunta("QUAL CONSOANTE FALTA?", "_LOR  _OGUETE", "A- V-F", "B- F-F", "C- F-V", 2);
              }
              else
              {
                tela_pergunta("QUAL PALAVRA", "TRISSILABA?", "A- PASTA", "B- REGUA", "C- CADERNO", 3);
              }

              tela_bronze();

              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO TERCEIRO ANO FACEIS 3 REVISADA
              {
                tela_pergunta("QUAL CONSOANTE FALTA?", "RE_OLHO  CA_EIRA", "A- P-D", "B- D-P", "C- B-D", 1);
              }
              else
              {
                tela_pergunta("QUAL A PALAVRA", "POLISSILABA?", "A- DICIONARIO", "B- ESTOJO", "C- FOLHA", 1);  
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO TERCEIRO ANO FACEIS 4 REVISADA
              {
                tela_pergunta("QUAL CONSOANTE FALTA?", "FLO_  SORVE_E", "A- V-R", "B- R-D", "C- R-T", 3);
              }
              else 
              {
                tela_pergunta("QUAL A PALAVRA", "POLISSILABA?", "A- BORRACHA", "B- TESOURA", "C- CORRETIVO", 3);
              }

              tela_prata();

              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO TERCEIRO ANO FACEIS 5 REVISADA
              {
                tela_pergunta("R ou RR:", "_EDE  _OUPA", "A- R-RR", "B- R-R", "C- RR-R", 2);
              }
              else
              {
                tela_pergunta("X ou CH:", "LI_O  CAI_A", "A- X-X", "B- CH-X", "C- X-CH", 1);
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO TERCEIRO ANO FACEIS 6
              {
                tela_pergunta("S ou SS:", "CA_A  ME_A", "A- S-SS", "B- SS-S", "C- S-S", 3);
              }
              else
              {
                tela_pergunta("S ou Z:", "_ERO  _IPER", "A- Z-S", "B- Z-Z", "C- S-Z", 2);
              }

              tela_ouro();
          }
          else // PERGUNTAS DO TERCEIRO ANO DIFICEIS
          {
              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO TERCEIRO ANO DIFICEIS 1
              {
                tela_pergunta("QUAL O SINAL?", "QUAL O SEU NOME _", "A- .", "B- ?", "C- !", 2);
              }
              else
              {
                tela_pergunta("QUAL O SINAL?", "QUE DIA LINDO_", "A- !", "B- ,", "C- ;", 1);
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO TERCEIRO ANO DIFICEIS 2
              {
                tela_pergunta("SEPARE AS PALAVRAS:", "OCACHORROLATE.", "A- o cachorrolate.", "B- O cachorro late.", "C- ocachorro late.", 2);
              }
              else
              {
                tela_pergunta("SEPARE AS PALAVRAS:", "NAESCOLATEMMESA", "A- na escolat em mesa", "B- na escola tem mesa", "C- Na escola tem mesa", 3);
              }

              tela_bronze();

              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO TERCEIRO ANO DIFICEIS 3
              {
                tela_pergunta("QUAL A ESCRITA?", "150", "A- CENTO E QUARENTA", "B- CENTO E CINQUENTA", "C- CENTO E CINCO", 2);
              }
              else
              {
                tela_pergunta("QUAL A ESCRITA?", "600", "A- SEISCENTOS", "B- NOVECENTOS", "C- SETESSENTOS", 1);   
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO TERCEIRO ANO DIFICEIS 4
              {
                tela_pergunta("QUAL O SINAL?", "EU GOSTO DE GATO_", "A- ,", "B- .", "C- ?", 2);
              }
              else
              {
                tela_pergunta("QUAL O SINAL?", "VAI A AULA HOJE_", "A- ,", "B- .", "C- ?", 3);
              }

              tela_prata();

              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO TERCEIRO ANO DIFICEIS 5
              {
                tela_pergunta("SEPARE AS PALAVRAS:", "EUCOMIBOLACHA", "A- Eu comi laranja", "B- eu comibolacha.", "C- Eu comi bolacha.", 3);
              }
              else
              {
                tela_pergunta("QUAL O SINAL?", "QUE CALOR_", "A- ,", "B- :", "C- !", 3);
              }

              delay(1000);
              p1= (random(1,333) % 2 );
              Serial.print("NUMERO ALEATORIO:");
              Serial.println(p1);

              if (p1==0)// PERGUNTAS DO TERCEIRO ANO DIFICEIS 6
              {
                tela_pergunta("QUAL O SINAL?", "MINHA CASA TEM PORTA", "A- .", "B- :", "C- ,", 1);
              }
              else
              {
                tela_pergunta("QUAL A ESCRITA?", "1000", "A- MIL", "B- CEM", "C- MIL E UM", 1);
              }

              tela_ouro();
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
  tft.fillScreen(AZULCEU);
  tft.fillRect(1, 200, 320, 40, GREEN);
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

void tela_bronze(void)
{
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
  tft.fillScreen(AZULCEU);
  tft.fillRect(1, 200, 320, 40, GREEN);
  bateria ();
  tft.fillTriangle(90, 40, 160, 140, 230, 40, WHITE);
  tft.fillTriangle(110, 50, 160, 120, 215, 50, AZULCEU);
  tft.fillCircle(160, 160, 25, WHITE); // ALFA
  tft.fillCircle(160, 160, 25, BRONZE); // ALFA
  delay(5000);
}

void tela_prata(void)
{
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
  tft.fillScreen(AZULCEU);
  tft.fillRect(1, 200, 320, 40, GREEN);
  bateria ();
  tft.fillTriangle(90, 40, 160, 140, 230, 40, WHITE);
  tft.fillTriangle(110, 50, 160, 120, 215, 50, AZULCEU);
  tft.fillCircle(160, 160, 25, WHITE); // ALFA
  tft.fillCircle(160, 160, 25, CINZA); // ALFA
  delay(5000);
}

void tela_ouro(void)
{
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
  tft.fillScreen(AZULCEU);
  tft.fillRect(1, 200, 320, 40, GREEN);
  bateria ();
  tft.fillTriangle(90, 40, 160, 140, 230, 40, WHITE);
  tft.fillTriangle(110, 50, 160, 120, 215, 50, AZULCEU);
  tft.fillCircle(160, 160, 25, WHITE); // ALFA
  tft.fillCircle(160, 160, 25, OURO); // ALFA
  delay(5000);
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

void dialogo(void)
{
  tft.fillScreen(AZULCEU);
  tft.fillRect(1, 200, 320, 40, GREEN);
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