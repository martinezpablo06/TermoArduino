# TermoArduino
control de temperatura para calentador de agua electrico controlado con arduino

el circuiro se puede utilizar tanto para corriente domestica (220v/ 110v ac)
como para 12v o 24v dc, muy importante para voltajes dc repetar la polaridad de 
los conectores y utilizar un calentador de agua acorde a cada voltaje

--------------------------------------------------------------------------------
instrucciones de uso:

al encender figura la temperatura prestablecida 80 grados.(se puede modificar en la linea 24 del archivo .ino)
con los botones laterales se puedde subir o bajar la temperatura de corte de a 1 grado
el boton central da inicio da paso de corriente al calentador, siendo visible la temperatura actual 
el proceso se detiene cuando se alcanza la temperatura deseada o se vuelve a pulsal el boton central
al finalizar el buzzer emite 3 pitidos y se visualiza la temperatura actual.
si se vuelve a pulsar el boton central el proceso comienza otra vez, al seteo de la temperatura de corte

el aparato tambien se puede usar como termometro, (sin necesidad de tener el calentador conectado)
presionando al iniciar los 2 botones laterales de forma simultanea.
si pulsa el boton central comienza el seteo de la temperatura de corte




