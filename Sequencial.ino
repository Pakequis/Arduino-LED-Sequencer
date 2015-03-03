/********************************
    Multi sequencial de LEDs 
    com Arduino - 07/10/2014
      
http://www.pakequis.com.br/2014/10/multi-sequencial-de-leds-com-arduino.html
**********************************/

//Sequencias dos LEDs
const int seq1[] = {1,2,4,8,16,32,64,128,256,512,256,128,64,32,16,8,4,2};
const int seq2[] = {3,6,12,24,48,96,192,384,768,384,192,96,48,24,12,6};
const int seq3[] = {1,3,7,15,31,63,127,255,511,1023,1022,1020,1016,1008,992,960,896,768,512,0};
const int seq4[] = {7,14,28,56,112,224,448,896,448,224,112,56,28,14};
const int seq5[] = {1022,1021,1019,1015,1007,991,959,895,767,511,767,895,959,991,1007,1015,1019,1021};
const int seq6[] = {513,771,903,975,1023,510,252,120,48,0,48,120,252,510,1023,975,903,771,513,0};
const int seq7[] = {1016,1009,995,967,911,799,575,127,575,799,911,967,995,1009};
const int seq8[] = {48,120,252,510,1023,975,903,771,513,0};
const int seq9[] = {80,65,81,85,69,75,73,83,46,67,79,77,46,66,82};

//Quantidade de passos em cada sequencia
const int tamanho_seq[9] = {18,16,20,14,18,20,14,10,15};

int chave1 = 10;	 //Entradas para
int chave2 = 11;	 //as chaves de 
int chave3 = 12;	 //selecao

int entrada_ad = 0;	 //Potenciometro na entrada 0
int contador = 0;	 //Contador
int valor_pot = 0;       //Valor da tensao no potenciometro
int valor_chave = 0;     //Valor lido das chaves
unsigned long tempo = 0; //Tempo entre as transicoes

void setup()
{
  DDRD = B11111111;	//Todos os pinos do portal D como saida
  DDRB = B00000011;	//Bits 0 e 1 do portal B como saida
	
  PORTD = 0;		//Zera saidas
  PORTB = 0;		//Zera saidas
}

void loop()
{
  //Le as tres chaves ao mesmo tempo e guarda o valor
  valor_chave = (PINB >> 2) & 7;
	
  //Le o valor do potenciometro
  valor_pot = analogRead(entrada_ad);
	
  //converte o valor da tensao para o tempo de transicao (40ms a 250s)
  tempo = map(valor_pot,0,1023,40,250);
	
  //tempo entre as transicoes
  delay(tempo);	
	
  //Executa um passo da sequencia
  sequencia();
}

//Atualiza os portais
void controla_saidas(int valor_saidas)
{
  PORTD = (valor_saidas & 255);		//LSB para o Portal D
  PORTB = (valor_saidas >> 8) & 3;      //MSB para o Portal B
}

//Executa um passo da sequencia
void sequencia()
{
  int valor = 0;
  switch (valor_chave)	//Verifica a posicao das chaves
  {
    case 0:		
      valor = seq1[contador];
      contador++;
      if (contador > (tamanho_seq[valor_chave] - 1))
      {
        contador = 0;
      }
      break;
	
    case 1:
      valor = seq2[contador];
      contador++;
      if (contador > (tamanho_seq[valor_chave] - 1))
      {
        contador = 0;	
      }
      break;
		
    case 2:
      valor = seq3[contador];
      contador++;
      if (contador > (tamanho_seq[valor_chave] - 1))
      {
        contador = 0;	
      }
      break;
		
    case 3:
      valor = seq4[contador];
      contador++;
      if (contador > (tamanho_seq[valor_chave] - 1))
      {
        contador = 0;	
      }		
      break;
		
    case 4:
      valor = seq5[contador];
      contador++;
      if (contador > (tamanho_seq[valor_chave] - 1))
      {
        contador = 0;	
      }		
      break;
		
    case 5:
      valor = seq6[contador];
      contador++;
      if (contador > (tamanho_seq[valor_chave] - 1))
      {
        contador = 0;	
      }		
      break;
		
    case 6:
      valor = seq7[contador];
      contador++;
      if (contador > (tamanho_seq[valor_chave] - 1))
      {
        contador = 0;	
      }		
      break;
		
    case 7:
      valor = seq8[contador];
      contador++;
      if (contador > tamanho_seq[valor_chave])
      {
        contador = 0;	
      }		
      break;

    default:
      valor = 1365;	//Para indicar uma sequencia invalida
      contador = 0;
      break;
    }
    controla_saidas(valor);
}

