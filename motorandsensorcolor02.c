int in1 = 5; // positivo do motor A
int in2 = 6; // negativo do motor A

int in3 = 9; // positivo do motor B
int in4 = 10; // negativo do motor B

int sensorPin = A0; // Pino para o analogRead (leitura analógica)
int LedB = 3;   // Pino digital 3 para o LED azul
int LedG = 4;  // Pino digital 4 para o LED verde
int LedR = 5;  // Pino digital 5 para o LED vermelho
int resultado, resultadoB, resultadoM, resultadoH;
int k = 10;  // tolerância de cor
int i = 0;
int matrizAcendeLed[] = {LedR, LedG, LedB};

// Declaração de funções para movimento
int paraFrente(int in1, int in3)
{
  analogWrite(in1, 80);
  analogWrite(in2, 0);
  analogWrite(in3, 80);
  analogWrite(in4, 0);
}

int paraTras(int in2, int in4)
{
  analogWrite(in1, 0);
  analogWrite(in2, 80);
  analogWrite(in3, 0);
  analogWrite(in4, 80);
}

int paraEsquerda(int in2, int in3)
{
  analogWrite(in1, 0);
  analogWrite(in2, 80);
  analogWrite(in3, 80);
  analogWrite(in4, 0);
}

int paraDireita(int in1, int in4)
{
  analogWrite(in1, 80);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 80);
}

int pararTotalmente(int in1, int in2, int in3, int in4)
{
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}

void setup()
{
  // Define os pinos LED como SAÍDA:
  pinMode(LedB, OUTPUT);
  pinMode(LedR, OUTPUT);
  pinMode(LedG, OUTPUT);
  // pinos dos motores A e B, de preferencia que sejam conectados em pinos PWM (~)
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  for (i = 0; i <= 2; i++)
  {
    digitalWrite(matrizAcendeLed[i], LOW);
  }
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  // Liga o LED vermelho
  digitalWrite(LedR, HIGH);
  // Atraso de 150 ms para estabilizar a leitura do LDR
  delay(150);
  // Lê os dados do sensor
  resultado = analogRead(sensorPin);
  resultadoM = map(resultado, 0, 1023, 0, 255);
  Serial.print("R,G,B = ");
  Serial.print(resultadoM);
  digitalWrite(LedR, LOW);
  delay(150);

  // Liga o LED verde
  digitalWrite(LedG, HIGH);
  // Atraso de 150 ms para estabilizar a leitura do LDR
  delay(150);
  // Lê os dados do sensor
  resultado = analogRead(sensorPin);
  resultadoH = map(resultado, 0, 1023, 0, 255);
  Serial.print(",");
  Serial.print(resultadoH);
  digitalWrite(LedG, LOW);
  delay(150);

  // Liga o LED azul
  digitalWrite(LedB, HIGH);
  // Atraso de 150 ms para estabilizar a leitura do LDR
  delay(150);
  // Lê os dados do sensor
  resultado = analogRead(sensorPin);
  resultadoB = map(resultado, 0, 1023, 0, 255);
  Serial.print(",");
  Serial.println(resultadoB);
  digitalWrite(LedB, LOW);
  delay(150);

  // Verifica a cor em relação aos valores de calibração
  if (abs(resultadoM - 52) < k && abs(resultadoH - 64) < k && abs(resultadoB - 81) < k)
  {
    Serial.println(" -> COR BRANCA!\n");
    paraFrente(in1, in3);
  }

  else if (abs(resultadoM - 55) < k && abs(resultadoH - 80) < k && abs(resultadoB - 105) < k)
  {
    Serial.println(" -> COR VERMELHA !\n");
    paraTras(in2, in4);
    //delay(1000);
    paraEsquerda(in2, in3);
    //delay(500);
  }
 
  else if (abs(resultadoM - 71) < k && abs(resultadoH - 81) < k && abs(resultadoB - 103) < k)
  {
    Serial.println(" -> COR VERDE !\n");
    paraTras(in2, in4);
    //delay(1000);
    paraDireita(in1, in4);
    //delay(500);
  }
 
  else if (abs(resultadoM - 138) < k && abs(resultadoH - 163) < k && abs(resultadoB - 166) < k)
 
  {
    Serial.println(" -> COR AZUL !\n");
    paraTras(in2, in4);
    //delay(1000);
    paraDireita(in1, in4);
    //delay(1500);
  }
 
  else if (abs(resultadoM - 67) < k && abs(resultadoH - 83) < k && abs(resultadoB) > 105)
  {
    Serial.println(" -> COR PRETO !\n");
  }
 
  else if (abs(resultadoM - 60) < k && abs(resultadoH - 79) < k && abs(resultadoB - 106) < k)
  {
    Serial.println(" -> COR MARROM !\n");
  }
 
  else if (abs(resultadoM - 54) < k && abs(resultadoH - 67) < k && abs(resultadoB - 95) < k)
  {
    Serial.println(" -> COR AMARELA !\n");
    paraTras(in2, in4);
    //delay(1000);
    pararTotalmente(in1, in2, in3, in4);
    //delay(4000);
    paraDireita(in1, in4);
  }

  else if (abs(resultadoM - 210) < k && abs(resultadoH - 206) < k && abs(resultadoB - 211) < k)
  {
    Serial.println(" -> COR ROSA !\n");
  }

  else if (abs(resultadoM - 165) < k && abs(resultadoH - 197) < k && abs(resultadoB - 205) < k)
  {
    Serial.println(" -> COR VERDE CLARA !\n");
  }
 
  else
  {
    Serial.println(" -> WTF ???\n");
  }
  //delay(2000);
}
