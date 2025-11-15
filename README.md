Tp Final de Arduino - Laboratorio de Computacion 1 
Secuencia de juegos.
Descripción del sistema: //TERMINAR

Integrantes del grupo:
ALFONZO TAMARA: tamaralalfonzo20@gmail.com
FERRANDO FLORENCIA:	ferrando.florencia.a@gmail.com
ZARATE ALACIEL: alacielzarate@gmail.com

Materia: Laboratorio de computación 1.

Docentes: Matias Jose Gagliardo, Pedro Facundo Iriso.

Descripción general y funcionalidades: Este sistema de Arduino propone 2 juegos de entretenimiento mediante un sistema de luces Led y Botones
El primer juego consta de 5 luces, para desafiar los reflejos del usuario estas luces se prenderán y apagarán en secuencia, el objetivo es tocar el botón cuando la luz roja del medio se encuentre encendida, en el momento exacto. El usuario cuenta con 3 intentos para lograrlo y avanzar al 2do juego.
El segundo intento puede es similar a uno de "simón dice", el usuario deberá replicar una secuencia de luces, repitiendo el patrón al pulsar los botones correspondientes. El usuario cuenta con 3 intentos para lograrlo.

Requisitos funcionales cumplidos:
⦁	Control de Entradas y Salidas: el sistema cuenta con diferentes entradas (como los botones, potenciómetro) y salidas (leds, display, buzzer).
⦁	Contador de Flancos: el sistema de botones detecta cuando se presiona uno de acuerdo al juego en curso. 
⦁	Control Lógico por Tiempo: cuenta con control de tiempo en función de las acciones del usuario (si presiona o no un botón) y de las luces led, el tiempo que se mantiene presionado un botón, etc.
⦁	Control Lógico por Máquina de Estados: se incorporó correctamente el estado de botones, potenciómetros (para la dificultad de los juegos) y el switch/interruptor (para comenzar el juego). 

Componentes utilizados:
⦁	Arduino UNO
⦁	Protoboard
⦁	Cables
⦁	Leds
⦁	Display 
⦁	Resistencias
⦁	Botones
⦁	Buzzer
⦁	Servo
⦁	Potenciómetro
⦁	Switch/Interruptor

Diagrama eléctrico o de conexiones:
<img width="1999" height="1545" alt="download" src="https://github.com/user-attachments/assets/04ac3760-69fe-4415-8039-b55c72c5a37e" />

<img width="1999" height="1545" alt="image" src="https://github.com/user-attachments/assets/ccca54cf-38c9-4977-a60a-856fea5efc58" />

Maquina de estados (diagrama o explicación):
<img width="2030" height="1543" alt="_Diagrama de flujo" src="https://github.com/user-attachments/assets/a3a8ade9-991f-4aad-9726-6bc5875e97ce" />

Instrucciones de uso y ejecución:
Al comenzar el juego, mediante pantalla se muestra un mensaje, inmediatamente las luces del primer juego comienzan a encenderse. Al mismo tiempo el usuario puede regular la velocidad del juego mediante el potenciómetro, haciendo que se incremente la dificultad. Teniendo en cuenta el objetivo del primer juego, se deberá presionar el botón del extremo derecho hasta asertar cuando la led del medio se encienda, se cuentan con 3 intentos para lograrlo. El buzzer emite una melodia de victoria al ganar el juego.
Cuando el usuario gana el primer juego, comienza el segundo, una secuencia de luces, donde se encienden únicamente 3 leds.
Al igual que en el juego anterior, el usuario puede modificar la velocidad del mismo mediante el potenciómetro, aunque a medida que avanza la velocidad se incrementa de forma automática. En este caso cuenta con dos intentos para ganar. En la primera secuencia de luces se encienden 3 leds, el usuario deberá repetir la misma de forma exitosa. Durante la segunda y tercera secuencia, se encienden 4 y 5 leds respectivamente. Si el usuario repite todas las secuencias correctamente, gana el juego y escucha una melodia de victoria mediante el buzzer, a la vez activa el servo para obtener el premio. En caso contrario pierde el juego.

Imágenes o video demostrativo: //agregar!!!!!!!!!!****
<img width="978" height="760" alt="image" src="https://github.com/user-attachments/assets/4ef63a39-c0cc-47f9-8da5-792b9d3aaa53" />

Créditos: a las integrantes del grupo ¯⁠\⁠_⁠(⁠ツ⁠)⁠_⁠/⁠¯.
