# iot-device-rasp

Trabalho de conclusão da disciplina ARQUITETURA EM APLICAÇÕES MÓVEIS E IOT do MBA da FIAP

Aplicações:

**BananaPi -> Aplicação em Python 2.7.15**

Definições da Placa
http://wiki.banana-pi.org/Banana_Pi_BPI-M1

Sistema Operacional
https://docs.armbian.com/User-Guide_Getting-Started/

Setup I2C
https://www.abelectronics.co.uk/kb/article/1061/i2c--smbus-and-armbian-linux

Identificando a porta de I2C
$ i2cdetect -y 1

Bibliotecas Python
https://github.com/amaork/libi2c

https://github.com/ozgur/python-firebase
para essa biblioteca, instalar com esse comando após do download
$sudo python setup.py install

As bibliotecas já foram adicionadas ao projeto.

**Arduino -> IDE Arduíno 1.8.7**

As bibliotecas do Arduino e I2C do Ubuntu(BananPi) trabalham com esses pinos
Pino I2C SDA (Data) BananaPi ligado ao Pino A4 SDA do Arduino 
Pino I2C SCL (Clock) BananaPi ligado ao Pino A5 SCL do Arduino  
GND -> Nível lógico Ground, que será ligado ao Ground do Arduino (qualquer GND da placa)

