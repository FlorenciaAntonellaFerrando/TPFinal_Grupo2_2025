Tp Final de Arduino - Laboratorio de Computacion 1 
Secuencia de juegos.

Integrantes del grupo:
ALFONZO TAMARA: tamaralalfonzo20@gmail.com
FERRANDO FLORENCIA:	ferrando.florencia.a@gmail.com
ZARATE ALACIEL: alacielzarate@gmail.com
QUIROGA DAIANA: daiana.m.quiroga@gmail.com

Materia: Laboratorio de computación 1.

Docentes: Matias Jose Gagliardo, Pedro Facundo Iriso.

Descripción general y funcionalidades: Este sistema de Arduino propone 2 juegos de entretenimiento mediante un sistema de luces Led y Botones
El primer juego consta de 5 luces, para desafiar los reflejos del usuario estas luces se prenderán y apagarán en secuencia, el objetivo es tocar el botón cuando la luz roja del medio se encuentre encendida, en el momento exacto. El usuario cuenta con 3 intentos para lograrlo y avanzar al 2do juego.
En el segundo juego el usuario deberá replicar una secuencia de luces, repitiendo el patrón al pulsar los botones correspondientes. El usuario cuenta con 3 intentos para lograrlo, la dificultad puede incrementarse mediante potenciómetro.

Requisitos funcionales cumplidos:
⦁	Control de Entradas y Salidas: el sistema cuenta con diferentes entradas (como los botones, potenciómetro) y salidas (leds, display, buzzer).
⦁	Contador de Flancos: el sistema de botones detecta cuando se presiona uno de acuerdo al juego en curso, monitorea el estado de los botones, y calcula el tiempo en el cual se presionan.
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

Esquema eléctrico:
<img width="1999" height="1545" alt="download" src="https://github.com/user-attachments/assets/04ac3760-69fe-4415-8039-b55c72c5a37e" />
<img width="1999" height="1545" alt="image" src="https://github.com/user-attachments/assets/ccca54cf-38c9-4977-a60a-856fea5efc58" />

Diagrama de conexiones:
<img width="916" height="624" alt="image" src="https://github.com/user-attachments/assets/14439153-bb90-42ef-a9a5-36517be362f8" />

Diagrama de maquina de estados:
![INICIO (1)](https://github.com/user-attachments/assets/d6333a84-be79-453e-a472-673e823ebd10)


Instrucciones de uso y ejecución:
Al comenzar el juego, mediante pantalla se muestra un mensaje, inmediatamente las luces del primer juego comienzan a encenderse. Al mismo tiempo el usuario puede regular la velocidad del juego mediante el potenciómetro, haciendo que se incremente la dificultad. Teniendo en cuenta el objetivo del primer juego, se deberá presionar el botón del extremo derecho hasta asertar cuando la led del medio se encienda, se cuentan con 3 intentos para lograrlo. El buzzer emite una melodia de victoria al ganar el juego. Cuando el usuario pierde en el primer intento la velocidad de las luces se incrementa automáticamente, a su vez el buzzer emite una melodia de derrota.
Cuando el usuario gana el primer juego, comienza el segundo, una secuencia de luces, donde se encienden únicamente 3 leds, formando 3 secuencias diferentes.
El usuario puede modificar la velocidad del mismo mediante el potenciómetro. En este caso cuenta con dos intentos para ganar. En la primera secuencia de luces se encienden 3 leds, el usuario deberá repetir la misma de forma exitosa presionando los botones correspondientes. Durante la segunda y tercera secuencia, se encienden 4 y 5 leds respectivamente. Si el usuario repite todas las secuencias correctamente, gana el juego y escucha una melodia de victoria mediante el buzzer, a la vez activa el servo para obtener el premio. En caso contrario pierde el juego y el buzzer emite una melodia de derrota.

Imágenes o video demostrativo: 
![foto final](https://github.com/user-attachments/assets/0f9e3d83-4d9b-40e0-a72b-44adfb8a44f0)

![WhatsApp Image 2025-11-15 at 17 17 59](https://github.com/user-attachments/assets/e7cf2436-091a-4a6d-bd43-779ec8c4d81e)

![WhatsApp Image 2025-11-16 at 21 06 53](https://github.com/user-attachments/assets/f99e3d15-6651-4cd6-b3e7-1186a0fe48c2)

Los videos se encuentran en la carpeta media, a disposición para descargarlos, o bien en el siguiente enlace para acceder mediante drive: https://drive.google.com/drive/folders/12KCKWD86lNKBZqg8CSxYaXRbglvW2ETn?usp=sharing 


Créditos: a las integrantes del grupo ¯⁠\⁠_⁠(⁠ツ⁠)⁠_⁠/⁠¯.
