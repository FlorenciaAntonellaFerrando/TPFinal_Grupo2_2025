#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define PRENDIDO 2
#define BTN1 3
#define BTN2 4
#define BTN3 5
#define PIN_SERVO 6
#define VELOCIDAD 250
#define POTENCIOMETRO A0
#define BUZZER 9

int leds[] = {13, 12, 11, 10, 8}; // pines
int contLed = 0;				  // indice de leds
int tiempoVelocidad = VELOCIDAD;
int millisBtn1 = 0;
int millisBtn2 = 0;
int millisBtn3 = 0;
int millisServo = 0;
int estadoAnteriorBtn1 = LOW;
int estadoAnteriorBtn2 = LOW;
int estadoAnteriorBtn3 = LOW;
int direccion = 1; // toma 2 posible valores 1 y -1 para indicar el sentido de las luces
unsigned long tiempoAnterior = 0;
int intentosJuego1 = 2;
int intentosJuego2 = 1;
int ganasteJuego1 = false;
bool limpiar = false; // indica si debe limpiar la pantalla
char estado = 'A';
const int PINES_DISPONIBLES[] = {8, 10, 11};
const int NUM_PINES_DISPONIBLES = 3;
unsigned long tiempoInicioServo = 0; // Para controlar el tiempo de espera del servo
int estadoServo = 0;				 // 0: Inactivo, 1: Mover a 90, 2: Esperar en 90, 3: Mover a 0, 4: Esperar en 0, 5: Terminado
int secuencia1[3]; //secuencia para el juego 2
int secuencia2[4]; //secuencia para el juego 2
int secuencia3[5]; //secuencia para el juego 2
int faseJuego2 = 1; 
unsigned long tiempoPrendidoLED = 2000;
unsigned long tiempoApagadoLED = 1000;

LiquidCrystal_I2C display(0x27, 16, 2); // instancio lcd
Servo servo;

void setup()
{
	Serial.begin(9600);

	// Leds
	for (int i = 0; i < 5; i++)
	{
		pinMode(leds[i], OUTPUT);
	}
	// Botones
	pinMode(PRENDIDO, INPUT); // prende y apaga el juego
	pinMode(BTN1, INPUT);	  // Boton para el juego 1
	pinMode(BTN2, INPUT);	  // juego 2
	pinMode(BTN3, INPUT);	  // juego 2

	todosApagados();

	// lcd
	display.init();
	display.backlight(); // Enciende la luz de fondo

	// Servo
	servo.attach(PIN_SERVO);
	servo.write(0); // posición inicial

	// Lee el ruido eléctrico de un pin analógico sin conectar (A1)
	randomSeed(analogRead(A1));

	// buzzer
	pinMode(BUZZER, OUTPUT);
}

void todosApagados()
{
	for (int i = 0; i < 5; i++)
	{
		digitalWrite(leds[i], LOW);
	}
}

void apagarTodoMenos(int led)
{
	for (int i = 0; i < 5; i++)
	{
		if (i != led)
		{
			digitalWrite(leds[i], LOW);
		}
		else
		{
			digitalWrite(leds[i], HIGH);
		}
	}
}

void controladorLeds(int contLed)
{
	todosApagados();
	switch (contLed)
	{
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

void generarSecuenciaAleatoria(int arraySalida[], int tamano)
{
	for (int i = 0; i < tamano; i++)
	{
		// 1. Generar un índice aleatorio: Un número entre 0 y 2 (ambos incluidos).
		//    random(max) genera un valor de [0, max-1]. Usamos random(3).
		int indiceAleatorio = random(NUM_PINES_DISPONIBLES);

		// 2. Asignar el valor del pin correspondiente al array de salida.
		arraySalida[i] = PINES_DISPONIBLES[indiceAleatorio];
	}
}

void printLCDInit()
{
	display.setCursor(0, 0);
	display.print("Equipo 2");
}

void limpiarPantalla(bool &limpiar)
{
	if (limpiar)
	{
		display.clear();
		limpiar = false;
		Serial.println("lIMPIAR!");
		Serial.println(limpiar);
	}
}

void imprimirSecuencia(const int array[], int longitud)
{
	Serial.print("[");
	for (int i = 0; i < longitud; i++)
	{
		Serial.print(array[i]);
		if (i < longitud - 1)
		{
			Serial.print(", ");
		}
	}
	Serial.println("]");
}

void mostrarSecuencia(int secuencia[], int longitud)
{

	todosApagados();
	Serial.println("mostrar Secuencia que entra en funcion");
	imprimirSecuencia(secuencia, longitud);

	
	int valorPotenciometro = 0;
	for (int i = 0; i < longitud; i++)
	{
		Serial.print("Encendiendo: ");
		Serial.println(secuencia[i]);
		digitalWrite(secuencia[i], HIGH);
		valorPotenciometro = analogRead(POTENCIOMETRO);
		tiempoPrendidoLED = map(valorPotenciometro, 0, 1023, 100, 1200);
		tiempoApagadoLED = map(valorPotenciometro, 0, 1023, 80, 500);
		unsigned long inicioEncendido = millis();
		Serial.print("tiempoPrendidoLED ");
		Serial.println(tiempoPrendidoLED);
		while (millis() - inicioEncendido < tiempoPrendidoLED)
		{
			// solo espera prendido
		}

		Serial.print("Apagando: ");
		Serial.println(secuencia[i]);
		digitalWrite(secuencia[i], LOW);
		unsigned long inicioApagado = millis();

		while (millis() - inicioApagado < tiempoApagadoLED)
		{
			// solo espera apagado
		}
	}
	todosApagados();
}

bool leerSecuencia(int secuencia[], int largo)
{
	// BTN1 => LED 8
	// BTN2 => LED 10
	// BTN3 => LED 11
	int correcto = true;
	int lectura[largo];
	int index = 0;

	imprimirSecuencia(secuencia, largo);
	while (index < largo)
	{
		int estadoBtn1 = digitalRead(BTN1);
		int estadoBtn2 = digitalRead(BTN2);
		int estadoBtn3 = digitalRead(BTN3);
		unsigned long tiempoActual = millis();
		if (estadoBtn1 == HIGH && estadoAnteriorBtn1 == LOW)
		{
			if (tiempoActual - millisBtn1 > 10)
			{
				tone(BUZZER, 523, 250);
				lectura[index] = 8;
				digitalWrite(8, HIGH);
				delay(500);
				digitalWrite(8, LOW);
				index++;
			}
		}
		else
		{
			estadoAnteriorBtn1 = estadoBtn1;
			millisBtn1 = tiempoActual;
		}
		if (estadoBtn2 == HIGH && estadoAnteriorBtn2 == LOW)
		{
			if (tiempoActual - millisBtn2 > 10)
			{
				tone(BUZZER, 523, 250);
				lectura[index] = 10;
				digitalWrite(10, HIGH);
				delay(500);
				digitalWrite(10, LOW);
				index++;
			}
		}
		else
		{
			estadoAnteriorBtn2 = estadoBtn2;
			millisBtn2 = tiempoActual;
		}
		if (estadoBtn3 == HIGH && estadoAnteriorBtn3 == LOW)
		{
			if (tiempoActual - millisBtn3 > 10)
			{
				tone(BUZZER, 523, 250);
				lectura[index] = 11;
				digitalWrite(11, HIGH);
				delay(500);
				digitalWrite(11, LOW);
				index++;
			}
		}
		else
		{
			estadoAnteriorBtn3 = estadoBtn3;
			millisBtn3 = tiempoActual;
		}
	}

	for (int i = 0; i < largo; i++)
	{
		if (secuencia[i] != lectura[i])
		{
			correcto = false;
		}
	}
	return correcto;
}

void melodiaVictoria()
{
	tone(BUZZER, 523);
	delay(150); // Do
	tone(BUZZER, 659);
	delay(150); // Mi
	tone(BUZZER, 784);
	delay(150); // Sol
	tone(BUZZER, 1047);
	delay(300); // Do alto
	noTone(BUZZER);
	delay(100);
	tone(BUZZER, 784);
	delay(150); // Sol
	tone(BUZZER, 1047);
	delay(300); // Do alto
	noTone(BUZZER);
}

void melodiaDerrota()
{
	tone(BUZZER, 392); delay(250); // Sol
	tone(BUZZER, 330); delay(250); // Mi
	tone(BUZZER, 262); delay(400); // Do (grave)
	noTone(BUZZER);
}

void melodiaInicioJuego1()
{
	tone(BUZZER, 262, 100); // Do (grave)
	delay(120);
	tone(BUZZER, 392, 100); // Sol
	delay(120);
	tone(BUZZER, 523, 150); // Do
}

void melodiaFinal()
{
    // Parte 1: Ascenso
	tone(BUZZER, 262); delay(200); // Do (grave)
	tone(BUZZER, 330); delay(200); // Mi
	tone(BUZZER, 392); delay(200); // Sol
	tone(BUZZER, 523); delay(400); // Do
    noTone(BUZZER);
    delay(100);
    // Parte 2: Conclusión triunfante
    tone(BUZZER, 784); delay(250); // Sol (alto)
    tone(BUZZER, 1047); delay(500); // Do (muy alto)
    noTone(BUZZER);
}

void moverServo()
{
	unsigned long tiempoActual = millis();
	switch (estadoServo)
	{
	case 0: // Estado inicial: Inactivo, esperando para empezar
		// No hace nada hasta que se le indique iniciar (por ejemplo, desde el case 'S' en loop)
		break;

	case 1: // Mover a 90 grados
		servo.write(90);
		tiempoInicioServo = tiempoActual; // Guarda el tiempo cuando se movió a 90
		estadoServo = 2;				  // Pasa al estado de esperar en 90
		Serial.println("Servo a 90");
		break;

	case 2: // Esperar 3 segundos en 90 grados
		if (tiempoActual - tiempoInicioServo >= 3000)
		{
			estadoServo = 3; // Pasa al estado de mover a 0
			Serial.println("Esperó 3s en 90");
		}
		break;

	case 3: // Mover a 0 grados
		servo.write(0);
		tiempoInicioServo = tiempoActual; // Guarda el tiempo cuando se movió a 0
		estadoServo = 4;				  // Pasa al estado de esperar en 0
		Serial.println("Servo a 0");
		break;

	case 4: // Esperar 3 segundos en 0 grados
		if (tiempoActual - tiempoInicioServo >= 3000)
		{
			estadoServo = 5; // Pasa al estado de terminado
			Serial.println("Esperó 3s en 0");
		}
		break;

	case 5: // Terminado
		// El servo ya hizo su secuencia.
		estado = 'F';
		estadoServo = 0; // Reinicia el estado del servo para futuras ejecuciones si es necesario
		Serial.println("Servo terminado, estado a F");
		break;
	}
}

void loop()
{

	// printLCDInit();
	Serial.println(estado);
	switch (estado)
	{
	case 'A':
		if (digitalRead(PRENDIDO) == HIGH)
		{
			estado = 'B';
			intentosJuego1 = 2;
			tiempoVelocidad = VELOCIDAD;
		}
		break;

	case 'B':
		limpiarPantalla(limpiar);
		
		if (digitalRead(PRENDIDO) == LOW && intentosJuego1 >= -1)
		{
			estado = 'A';
		}
		if (digitalRead(PRENDIDO) == HIGH && intentosJuego1 >= -1)
		{
			limpiar = true;
			intentosJuego1 = 2;
			display.setCursor(0, 0);
			display.print("Juego 1");

			while (intentosJuego1 >= 0 && digitalRead(PRENDIDO) == HIGH)
			{
				display.setCursor(0, 1);
				display.print("N# intentos");
				display.setCursor(12, 1);
				display.print(intentosJuego1 + 1);
				unsigned long tiempoActual = millis();

				if (tiempoActual - tiempoAnterior > tiempoVelocidad)
				{
					contLed += direccion;
					tiempoAnterior = tiempoActual;
				}
				if (contLed >= sizeof(leds) / sizeof(leds[0]))
				{
					direccion = -1;
				}
				if (contLed <= 0)
				{
					direccion = 1;
				}

				int estadoBtn1 = digitalRead(BTN1);
				if (estadoBtn1 == HIGH && estadoAnteriorBtn1 == LOW)
				{
					if (tiempoActual - millisBtn1 > 30)
					{	
						tone(BUZZER, 523, 250);
						digitalWrite(leds[contLed], HIGH);
						if (leds[contLed] == 11)
						{
							Serial.println("Ganaste!");
							display.clear();
							display.setCursor(3, 1);
							display.print("!!YOU WIN!!");
							intentosJuego1 = -2;
						}
						else
						{
							Serial.println("fallaste!");
							intentosJuego1--;
							tiempoVelocidad -= 50;
							display.setCursor(12, 1);
							display.print(intentosJuego1 + 1);
							while(millis() - tiempoActual < 500){
								//espera para mostrar el led
							}
						}
					}
				}
				else
				{
					estadoAnteriorBtn1 = estadoBtn1;
					millisBtn1 = tiempoActual;
				}
				controladorLeds(contLed);
			}
		}

		if (intentosJuego1 == -2)
		{
			display.setCursor(0, 1);
			display.print("Pasar a JUEGO 2");
			display.setCursor(9, 0);
			display.print("GANASTE");
			melodiaVictoria();
			estado = 'C';
			delay(2000);
		}
		if (intentosJuego1 == -1)
		{
			display.setCursor(0, 0);
			display.print("PERDISTE");
			estado = 'X';
			melodiaDerrota();
			delay(2000);
		}
		// inicializo valores del juego 2
		intentosJuego2 = 1;
		break;

	case 'C':
		limpiar = true;
		limpiarPantalla(limpiar);
		todosApagados();
		display.setCursor(0, 0); 	
		display.print("Juego 2");
		display.setCursor(0, 1);
		display.print("N# intentos");
		display.setCursor(13, 1);
		display.print(intentosJuego2 + 1);
		// Reiniciamos los valores para un nuevo juego
		intentosJuego2 = 1; 
		faseJuego2 = 1;
		limpiar = true;
		limpiarPantalla(limpiar);
		// Generamos las secuencias UNA SOLA VEZ al inicio del juego
		generarSecuenciaAleatoria(secuencia1, 3);
		generarSecuenciaAleatoria(secuencia2, 4);
		generarSecuenciaAleatoria(secuencia3, 5);
		
		// Cambiamos al estado 'D' que será el motor del juego
		estado = 'D';
		delay(1000); // Pausa para que el jugador se prepare
		break;

	case 'D':
		display.setCursor(0, 0); 	
		display.print("Juego 2");
		display.setCursor(0, 1);
		display.print("N# intentos");
		display.setCursor(13, 1); 
		display.print(intentosJuego2 + 1);

		if (faseJuego2 == 1) {
			mostrarSecuencia(secuencia1, 3);
			if (!leerSecuencia(secuencia1, 3)) {
				intentosJuego2--;
				display.setCursor(0, 1);
				display.print("N# intentos");
				display.setCursor(13, 1);
				display.print(intentosJuego2 + 1);
				if (intentosJuego2 >= 0) { // Segunda oportunidad
					mostrarSecuencia(secuencia1, 3);
					if (!leerSecuencia(secuencia1, 3)) {
						intentosJuego2--;
						display.setCursor(0, 1);
						display.print("N# intentos");
						display.setCursor(13, 1);
						display.print(intentosJuego2 + 1);
					};
				}
			}
			if (intentosJuego2 >= 0) faseJuego2 = 2; // Avanza a la siguiente fase
		}
		
		else if (faseJuego2 == 2) {
			mostrarSecuencia(secuencia2, 4);
			if (!leerSecuencia(secuencia2, 4)) {
				intentosJuego2--;
				display.setCursor(0, 1);
				display.print("N# intentos");
				display.setCursor(13, 1);
				display.print(intentosJuego2 + 1);
				if (intentosJuego2 >= 0) {
					mostrarSecuencia(secuencia2, 4);
					if (!leerSecuencia(secuencia2, 4)) {
						intentosJuego2--;
						display.setCursor(13, 1);
						display.print(intentosJuego2 + 1);
					}
				}
			}
			if (intentosJuego2 >= 0) faseJuego2 = 3; // Avanza
		}

		else if (faseJuego2 == 3) {
			mostrarSecuencia(secuencia3, 5);
			if (!leerSecuencia(secuencia3, 5)) {
				intentosJuego2--;
				display.setCursor(0, 1);
				display.print("N# intentos");
				display.setCursor(13, 1);
				display.print(intentosJuego2 + 1);
				if (intentosJuego2 >= 0) {
					mostrarSecuencia(secuencia3, 5);
					if (!leerSecuencia(secuencia3, 5)) {
						intentosJuego2--;
						display.setCursor(0, 1);
						display.print("N# intentos");
						display.setCursor(13, 1);
						display.print(intentosJuego2 + 1);
					}
				}
			}
			if (intentosJuego2 >= 0) faseJuego2 = 4; // Fase de victoria
		}

		// Comprobación del resultado del juego
		if (intentosJuego2 < 0) {
			// PERDISTE
			display.setCursor(0,0);
			display.print("PERDISTE");
			estado = 'X';
			melodiaDerrota();
			delay(2000);
		} else if (faseJuego2 == 4) {
			// GANASTE
			display.setCursor(0,1);
			display.print("Fin Juego 2");
			display.setCursor(9,0);
			display.print("GANASTE");
			melodiaVictoria();
			estado = 'S';
			estadoServo = 1;
			delay(2000);
		}
		break;


	case 'S':
		moverServo();
		break;
	case 'F':
		limpiarPantalla(limpiar);
		display.setCursor(0, 1);
		display.print("GRACIAS TOTALES");
		void melodiaFinal();
		if (digitalRead(PRENDIDO) == HIGH)
		{
			estado = 'Z';
		}
		else
		{
			limpiar = true;
			limpiarPantalla(limpiar);
			estado = 'A';
		}
		break;
	case 'Z':
		limpiarPantalla(limpiar);
		if (digitalRead(PRENDIDO) == HIGH)
		{
			display.setCursor(0, 0);
			display.print("Reset Arduino");
		}
	default:
		limpiarPantalla(limpiar);
		todosApagados();
		if (digitalRead(PRENDIDO) == HIGH)
		{
			display.setCursor(0, 0);
			display.print("SW reset");
		}
		else
		{
			limpiar = true;
			limpiarPantalla(limpiar);
			estado = 'A';
		}
		break;
	}
}