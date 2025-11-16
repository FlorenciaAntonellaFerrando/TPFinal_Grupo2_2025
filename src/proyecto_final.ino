#include <LiquidCrystal_I2C.h>
#include <Servo.h>
# define PRENDIDO 2
# define BTN1 3
# define BTN2 4
# define BTN3 5
# define PIN_SERVO 6
# define VELOCIDAD 250
# define BUZZER 9
int leds[] = {13,12,11,10,8}; //pines
int contLed = 0; //indice de leds
int tiempoVelocidad = VELOCIDAD;
int millisBtn1 = 0;
int millisBtn2 = 0;
int millisBtn3 = 0;
int millisServo = 0;
int estadoAnteriorBtn1 = LOW;
int estadoAnteriorBtn2 = LOW;
int estadoAnteriorBtn3 = LOW;
int direccion = 1; //toma 2 posible valores 1 y -1 para indicar el sentido de las luces
unsigned long tiempoAnterior = 0;
int intentosJuego1 = 2;
int ganasteJuego1 = false;
bool limpiar = false; //indica si debe limpiar la pantalla
char estado = 'A';
unsigned long tiempoInicioServo = 0; // Para controlar el tiempo de espera del servo
int estadoServo = 0; // 0: Inactivo, 1: Mover a 90, 2: Esperar en 90, 3: Mover a 0, 4: Esperar en 0, 5: Terminado


LiquidCrystal_I2C display(0x27, 16, 2); //instancio lcd
Servo servo;


void setup(){
  Serial.begin(9600);
  
  //Leds
  for(int i = 0; i < 5; i ++){
      pinMode(leds[i], OUTPUT);
  }
  //Botones
  pinMode(PRENDIDO, INPUT); // prende y apaga el juego
  pinMode(BTN1, INPUT); // Boton para el juego 1
  pinMode(BTN2, INPUT); // juego 2
  pinMode(BTN3, INPUT); // juego 2
  
  todosApagados();
  
  //lcd
  display.init(); 
  display.backlight(); // Enciende la luz de fondo
  
  //Servo
  servo.attach(PIN_SERVO);
  servo.write(0);// posición inicial
  
  // buzzer
  pinMode(BUZZER, OUTPUT);
}

void todosApagados(){
	for(int i = 0; i < 5; i ++){
      digitalWrite(leds[i], LOW);
  }
}

void controladorLeds(int contLed) {
  todosApagados();
  switch (contLed) {
    case 0:
      digitalWrite(leds[0], HIGH);
      break;
    case 1:
      digitalWrite(leds[1], HIGH);
      break;
    case 2:
      digitalWrite(leds[2], HIGH);
      break;
    case 3:
      digitalWrite(leds[3], HIGH);
      break;
    case 4:
      digitalWrite(leds[4], HIGH);
      break;
    default:
      todosApagados();
      break;
  }
}


void printLCDInit(){
  display.setCursor(0,0);
  display.print("Equipo 2");
}

void limpiarPantalla(bool &limpiar){
	if(limpiar){
		display.clear();
		limpiar = false;
		Serial.println("lIMPIAR!");
		Serial.println(limpiar);
	}
}

void melodiaVictoria(){
  tone(BUZZER, 523); delay(150); // Do
  tone(BUZZER, 659); delay(150); // Mi
  tone(BUZZER, 784); delay(150); // Sol
  tone(BUZZER, 1047); delay(300); // Do alto
  noTone(BUZZER);
  delay(100);
  tone(BUZZER, 784); delay(150); // Sol
  tone(BUZZER, 1047); delay(300); // Do alto
  noTone(BUZZER);
}

void moverServo(){
    unsigned long tiempoActual = millis();

    switch(estadoServo){
        case 0: // Estado inicial: Inactivo, esperando para empezar
            // No hace nada hasta que se le indique iniciar (por ejemplo, desde el case 'S' en loop)
            break;

        case 1: // Mover a 90 grados
            servo.write(90);
            tiempoInicioServo = tiempoActual; // Guarda el tiempo cuando se movió a 90
            estadoServo = 2; // Pasa al estado de esperar en 90
            Serial.println("Servo a 90");
            break;

        case 2: // Esperar 3 segundos en 90 grados
            if(tiempoActual - tiempoInicioServo >= 3000){
                estadoServo = 3; // Pasa al estado de mover a 0
                Serial.println("Esperó 3s en 90");
            }
            break;

        case 3: // Mover a 0 grados
            servo.write(0);
            tiempoInicioServo = tiempoActual; // Guarda el tiempo cuando se movió a 0
            estadoServo = 4; // Pasa al estado de esperar en 0
            Serial.println("Servo a 0");
            break;

        case 4: // Esperar 3 segundos en 0 grados
            if(tiempoActual - tiempoInicioServo >= 3000){
                estadoServo = 5; // Pasa al estado de terminado
                Serial.println("Esperó 3s en 0");
            }
            break;

        case 5: // Terminado
            // El servo ya hizo su secuencia.
            // Aquí puedes cambiar el estado principal del juego a 'F'
            estado = 'F';
            estadoServo = 0; // Reinicia el estado del servo para futuras ejecuciones si es necesario
            Serial.println("Servo terminado, estado a F");
            break;
    }
}

void loop(){

  //printLCDInit();
  Serial.println(estado);
  switch(estado){
	case 'A':
		if(digitalRead(PRENDIDO) == HIGH){
			estado = 'B';
            intentosJuego1 = 2;
			tiempoVelocidad = VELOCIDAD;
		}
		break;
		
	case 'B':
		limpiarPantalla(limpiar);
		
	  if(digitalRead(PRENDIDO) == LOW && intentosJuego1 >= -1){
		  estado = 'A';
	  }
	  if(digitalRead(PRENDIDO) == HIGH && intentosJuego1 >= -1){
		limpiar = true;
		intentosJuego1 = 2;
		display.setCursor(0,0);
		display.print("Juego 1");
		
		while(intentosJuego1 >= 0 && digitalRead(PRENDIDO) == HIGH){
			display.setCursor(0,1);
			display.print("N# intentos");
			display.setCursor(12,1);
			display.print(intentosJuego1 + 1);
			unsigned long tiempoActual = millis();
			
			if(tiempoActual - tiempoAnterior > tiempoVelocidad){
				contLed += direccion;
				tiempoAnterior = tiempoActual;
			}
			if(contLed >= sizeof(leds) / sizeof(leds[0])){
				direccion = -1;
			}
			if(contLed <= 0){
				direccion = 1;
			}
			
			int estadoBtn1 = digitalRead(BTN1);
			if(estadoBtn1 == HIGH && estadoAnteriorBtn1 ==LOW ){
				if(tiempoActual - millisBtn1 > 10){
					digitalWrite(leds[contLed], HIGH);
					if(leds[contLed] == 11){
						Serial.println("Ganaste!");
						display.clear();
						display.setCursor(3,1);
						display.print("!!YOU WIN!!");
						intentosJuego1 = -2;
					}else{
						Serial.println("fallaste!");
						intentosJuego1 --;
						tiempoVelocidad -= 50;
						display.setCursor(12,1);
						display.print(intentosJuego1 + 1);
					}
					delay(3000);
				}
			}else{
				estadoAnteriorBtn1 = estadoBtn1;
				millisBtn1 = tiempoActual;
			}
			controladorLeds(contLed);
		  }
		}
	  
		if(intentosJuego1 == -2){
			display.setCursor(0,1);
			display.print("Pasar a JUEGO 2");
			display.setCursor(9,0);
			display.print("GANASTE");
			melodiaVictoria();
			estado = 'C';
			delay(3000);
		}
		if(intentosJuego1 == -1){
			display.setCursor(0,1);
			display.print("T.T");
			display.setCursor(0,0);
			display.print("PERDISTE");
			estado = 'X';
			delay(3000);
		}
		break;
	
	case 'C':
		// Juego 2
		break;
	
	case 'S':
		moverServo();
		break;
	case 'F':
		limpiarPantalla(limpiar);
		display.setCursor(0,1);
		display.print("GRACIAS TOTALES");
		if(digitalRead(PRENDIDO) == HIGH){
			display.setCursor(0,0);
			display.print("SW reset");
		}else{
			limpiar = true;
			limpiarPantalla(limpiar);
			estado = 'A';
		}
		break;
	default:
		limpiarPantalla(limpiar);
		if(digitalRead(PRENDIDO) == HIGH){
			display.setCursor(0,0);
			display.print("SW reset");
		}else{
			limpiar = true;
			limpiarPantalla(limpiar);
			estado = 'A';
		}
		break;
	}
}
