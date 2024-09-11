#include <Arduino.h>

const int pinLedVM = 5;  // LED vermelho
const int pinLedAM = 17; // LED amarelo
const int pinLedVD = 16; // LED verde
const int pinPotenciometro = 36;

unsigned long anteriorMillisPot = 0;
const unsigned long pausePot = 1000; // Tempo de espera para a leitura do potenciômetro

// Tempo para piscar o LED vermelho (em milissegundos)
const unsigned long intervaloPiscar = 500; 
unsigned long ultimoMillisPiscar = 0;

// Protótipos de funções
// void LerPotenciometro();
// void LerPotenciometroNew();
// void LerPotencAcenderLed();

void setup() {
  Serial.begin(921600);

  pinMode(pinLedVM, OUTPUT);
  pinMode(pinLedAM, OUTPUT);
  pinMode(pinLedVD, OUTPUT);

  // Inicialize todos os LEDs como apagados
  digitalWrite(pinLedVM, LOW);
  digitalWrite(pinLedAM, LOW);
  digitalWrite(pinLedVD, LOW);

  // Tempo para abrir a janela do Monitor Serial
  delay(2000);

  Serial.println("Teste de leitura de potenciômetro.");
}

void loop() {
  unsigned long correnteMillis = millis();
  
  if (correnteMillis - anteriorMillisPot >= pausePot) {
    anteriorMillisPot = correnteMillis; // Recomeça a contagem
    int vlrPotenciometro = analogRead(pinPotenciometro);

    Serial.print("Valor do potenciômetro: ");
    Serial.println(vlrPotenciometro);

    // Desliga todos os LEDs inicialmente
    digitalWrite(pinLedVM, LOW);
    digitalWrite(pinLedAM, LOW);
    digitalWrite(pinLedVD, LOW);

    // Verifica o estado do potenciômetro e controla os LEDs
    if (vlrPotenciometro >= 4000) {
      // Temperatura Fora do Padrão: LEDs verde e amarelo acesos, vermelho piscando
      digitalWrite(pinLedVD, HIGH); // Verde aceso
      digitalWrite(pinLedAM, HIGH); // Amarelo aceso
      
      // Controle de piscar o LED vermelho
      if (correnteMillis - ultimoMillisPiscar >= intervaloPiscar) {
        ultimoMillisPiscar = correnteMillis;
        int estadoVermelho = digitalRead(pinLedVM);
        digitalWrite(pinLedVM, !estadoVermelho); // Alterna o estado do LED vermelho
      }
    } else if (vlrPotenciometro >= 3500) {
      // Temperatura Elevada: Apenas LED vermelho aceso
      digitalWrite(pinLedVM, HIGH);
    } else if (vlrPotenciometro >= 3000) {
      // Temperatura Atenção: Apenas LED amarelo aceso
      digitalWrite(pinLedAM, HIGH);
    } else if (vlrPotenciometro >= 2000) {
      // Temperatura Normal: Apenas LED verde aceso
      digitalWrite(pinLedVD, HIGH);
    }
  }
}