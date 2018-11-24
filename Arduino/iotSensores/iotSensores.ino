#include <NewPing.h>
#include <Wire.h>

#define TRIG_PIN 6
#define ECHO_PIN 5 
#define DISTANCIA_MAX 50
#define SOUND_SENSOR_PIN A0
#define SOUND_THRESHOLD 500
#define LIGTH_SENSOR_PIN A3
#define LIGTH_THRESHOLD 600
//API utilizada para acionar o sonar
NewPing sonar(TRIG_PIN, ECHO_PIN, DISTANCIA_MAX);//Distancia em cm

//variavel para armazenar a distancia
float distancia = 0.0;
int soundReading =0;
int soundReadingBuffer = 0;
int ligthValue = 0;

void setup() {
  Wire.begin(8);                // entra no barramento i2c com o endereco 0x08
  Wire.onRequest(requestEvent); // registrando evento de escuta de dados

  pinMode(SOUND_SENSOR_PIN, INPUT);
  pinMode(LIGTH_SENSOR_PIN, INPUT);
  
  Serial.begin(9600);//iniciando porta serial
}

//loop principal
void loop() {

  distancia = sonar.ping()/US_ROUNDTRIP_CM;//Calculando em cm

  soundReading=analogRead(SOUND_SENSOR_PIN);

  ligthValue = analogRead(LIGTH_SENSOR_PIN);
  
  if(distancia < 20 && distancia >=1){
    Serial.print("Distancia em cm:");
    Serial.println(distancia);
  }

  if(soundReading > SOUND_THRESHOLD){
    soundReadingBuffer = soundReading; 
    Serial.print("Som capturado:");
    Serial.println(soundReading);
  }

  if(ligthValue > LIGTH_THRESHOLD)
  {
    Serial.print("luz off:");
    Serial.println(ligthValue);
  }
  
  //delay para nova leitura
  //delay(500);
}

int send = 0;
//4 primeiros digitos significam o sensor. Os 4 ultimos o evento
// funcao registrada no setup que serah chamada quando o master requisitar dados no barramento
void requestEvent() {

  //para distancia o sensor eh 0003 e 0001 -> sensor acionado (algo proximo)
  if(send == 0){
    if(distancia < 20 && distancia >=1){
      Wire.write("00010001");
    }else{//0002 -> sensor nao acionado
      Wire.write("00010002");
    }
    send = 1;
    return;
  }

  //para sensor de som 0002 e threshold ultrapassado eh 0001 -> sensor acionado (algo proximo)
  if(send ==1 ){
    if(soundReadingBuffer > SOUND_THRESHOLD){
      Wire.write("00020001");
    }else{//0002 -> sensor nao acionado
      Wire.write("00020002");
    }
    send = 2;
    soundReadingBuffer = 0;
    return;
  }

  //para sensor de luz 0003 e threshold ultrapassado eh 0001 -> sensor acionado
  if(send ==2 ){
    if(ligthValue > LIGTH_THRESHOLD){
      Wire.write("00030001");
    }else{//0002 -> sensor nao acionado
      Wire.write("00030002");
    }
    send = 0;
  }
}
