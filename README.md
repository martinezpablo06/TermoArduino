# TermoArduino
control de temperatura para calentador de agua electrico

el circuiro se puede utilizar tanto para calentadores de agua de corriente domestica
(220v/ 110v ac) como para calentadores de 12v o 24v dc,muy importante 
para voltajes dc respetar la polaridad de las conecciones y
utilizar una fuente de alimentacion para arduino adecuada para cada voltaje,
al igual que un calentador de agua acorde a cada voltaje

--------------------------------------------------------------------------------
instrucciones de uso:

1- seleccion de temperatura:
al encender figura la temperatura prestablecida 90 grados.(se puede modificar en la linea 24 del archivo .ino)
con los botones laterales se puedde subir o bajar la temperatura de corte de a 1 grado.

  - guardar temperatura selecionada:
  al presionar de forma simultanea ambos botones laterales, se guarda la temperatura en memoria.

  - funcion termometro: (sin necesidad de tener el calentador conectado)
  al encender presionar de forma simultanea al boton izquierdo y el central.

2a- calentamiento simple:
al presionar el boton central se permte el paso de corriente al calentador, siendo visible la temperatura actual. 
el proceso se detiene cuando se alcanza la temperatura deseada o se vuelve a pulsal el boton central
al finalizar el buzzer emite 3 pitidos y se visualiza la temperatura actual.

2b- mantener caliente:
al presionar de forma simultanea el boton central y el boton derecho, al igual que el caso anterior,
se permte el paso de corriente al calentador, siendo visible la temperatura actual. luego de alcanzar 
la temperatura establecida, cada vez que la temperatura del agua baje 4 grados (modificable linea 171 .ino)
el calentador se vuelve a encerder hasta que otra vez se alcanse la temperatura establecida.
el proceso se detiene alpulsar el boton central

3-reiniciar
luego, al pulsar el boton central se retorna al paso 1. Seleccion de temperatura.







