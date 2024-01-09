/*typedef struct Motor {
  int IN1;
  int IN2;
} Motor; */


int MOTOR1_IN1 = 4;
int MOTOR1_IN2 = 5;
int MOTOR2_IN1 = 6;
int MOTOR2_IN2 = 7;


// Motor motor1 = { MOTOR1_IN1, MOTOR1_IN2 };
// Motor motor2 = { MOTOR2_IN1, MOTOR2_IN2 };


// Matriz com os pinos onde o LED RGB vai ser conectado
int matrizPinodosLEDS[] = { 11, 12, 13 };


// Uma variável booleana para indicar se o sensor foi calibrado
boolean calibragem_cores_realizada = false;


//Matriz de floats para armazenar o valor das cores
float matrizCores[]  = { 0, 0, 0 };
float matrizBranco[] = { 0, 0, 0 };
float matrizPreto[]  = { 0, 0, 0 };


//Variável para armazenar a média das leitura
int mediaLeituras;


void setup()
{  
  //Declaração dos pinos como de saída  
  pinMode(11, OUTPUT);//LED VERMELHO  
  pinMode(12, OUTPUT);//LED GREENN  
  pinMode(13, OUTPUT);//LED BLUE   //Inicia a comunicação serial  


  pinMode(MOTOR1_IN1, OUTPUT);
  pinMode(MOTOR1_IN2, OUTPUT);
  // pinMode(motor2.IN1, OUTPUT);
  // pinMode(motor2.IN2, OUTPUT);


  Serial.begin(9600);
}


boolean running = false;


void loop()
{
  /*  
  // Verifica se o calibragem_cores_realizada de branco foi calibrado  
  checa_calibragem_branco();
  //Checa qual é a cor  
  checaCores();  
  // Imprime na Serial o valor das cores  
  mostraCores();
  */
  Serial.println("running");
  if (!running) {
    digitalWrite(MOTOR1_IN1, HIGH);
    digitalWrite(MOTOR1_IN2, LOW);
    analogWrite(10, 200);
    running = true;
  }
  // digitalWrite(motor2.IN1, LOW);
  // digitalWrite(motor2.IN2, HIGH);
}




// Verifica se o calibragem_cores_realizada de branco foi calibrado
void checa_calibragem_branco() {  
  //checa se o balanço de branco foi feito  
  if (!calibragem_cores_realizada) {
    calibra_cores();  
  }
}




//Configura o calibragem_cores_realizada de Branco
void calibra_cores(){  
  //Calibrando o branco!  
  Serial.println("Calibrando o branco");  
  delay(5000);  
  for (int i = 0; i <= 2; i++) {    
    digitalWrite(matrizPinodosLEDS[i], HIGH);    
    delay(100);
    matrizBranco[i] = mediaSensor(5);
    Serial.println(matrizBranco[i]);
    digitalWrite(matrizPinodosLEDS[i], LOW);
    delay(100);  
  }  


  //Calibrando o preto!  
  Serial.println("Calibrando o preto");  
  delay(5000);  
  for (int i = 0; i <= 2; i++) {    
    digitalWrite(matrizPinodosLEDS[i], HIGH);
    delay(100);
    matrizPreto[i] = mediaSensor(5);
    digitalWrite(matrizPinodosLEDS[i], LOW);
    Serial.println(matrizPreto[i]);
    delay(100);
  }


  //Avisa que a calibragem foi feita  
  Serial.println("Sensor Calibrado");  
  calibragem_cores_realizada = true;  
  delay(3000);
}


//Checa a cor
void checaCores(){  
  for (int i = 0; i <= 2; i++) {
    digitalWrite(matrizPinodosLEDS[i], HIGH);
    delay(100);
    matrizCores[i] = mediaSensor(5);
    float cinzaDif = matrizBranco[i] - matrizPreto[i];
    matrizCores[i] = (matrizCores[i] - matrizPreto[i]) / (cinzaDif)*255;
    digitalWrite(matrizPinodosLEDS[i], LOW);
    delay(100);
  }
}


int mediaSensor(int vezes){  
  int somatorio = 0;
  int A0 = 0; // porta analogica A0


  for (int i = 0; i < vezes; i++) {
    somatorio += analogRead(A0);
    delay(10);
  }


  return somatorio / vezes;
}


/*
void mostraCores(){
  int red   = int(matrizCores[0]);
  int green = int(matrizCores[1]);
  int blue  = int(matrizCores[2]);
  Serial.print("R = ");  
  Serial.println(red);
  Serial.print("G = ");  
  Serial.println(green);  
  Serial.print("B = ");  
  Serial.println(blue);


  int eh_vermelho = red>green & red>blue & (green + blue)/2.0<50;
  if (eh_vermelho){
    Serial.println("Vermelho");
    digitalWrite(motor1.IN1, HIGH);
    digitalWrite(motor1.IN2, LOW);
    digitalWrite(motor2.IN1, LOW);
    digitalWrite(motor2.IN2, HIGH);
    analogWrite(9, 80);
    analogWrite(10, 80);
  }


  int eh_verde = green>red & green>blue;
  if (eh_verde){
    Serial.println("Verde");
    digitalWrite(motor1.IN1, HIGH);
    digitalWrite(motor1.IN2, LOW);
    digitalWrite(motor2.IN1, LOW);
    digitalWrite(motor2.IN2, HIGH);
    analogWrite(9, 80);
    analogWrite(10, 80);
  }


  int eh_azul = blue>red & blue>green;
  if (eh_azul){
    Serial.println("Azul");
    digitalWrite(motor1.IN1, HIGH);
    digitalWrite(motor1.IN2, LOW);
    digitalWrite(motor2.IN1, HIGH);
    digitalWrite(motor2.IN2, LOW);
    analogWrite(9, 80);
    analogWrite(10, 80);
  }


  int eh_branco = (green + blue + red) > 800;
  if (eh_branco){
    Serial.println("Branco");
    digitalWrite(motor1.IN1, LOW);
    digitalWrite(motor1.IN2, HIGH);
    digitalWrite(motor2.IN1, HIGH);
    digitalWrite(motor2.IN2, LOW);
    analogWrite(9, 80);
    analogWrite(10, 80);
  }


  int eh_preto = (red+green/3.0) <= 20;
  if (eh_preto){
    Serial.println("Preto");
    digitalWrite(motor1.IN1, LOW);
    digitalWrite(motor1.IN2, HIGH);
    digitalWrite(motor2.IN1, HIGH);
    digitalWrite(motor2.IN2, LOW);
    analogWrite(9, 80);
    analogWrite(10, 80);
  }
}
*/
