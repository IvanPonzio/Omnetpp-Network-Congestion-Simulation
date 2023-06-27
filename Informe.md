# Informe Científico: Protocolo de Resolución de Conflictos en Congestión de Redes utilizando Simulación Discreta

## Integrantes del grupo:
-Fernando Alvarado 
-Ivan Ponzio
-Armando Carral

## Resumen
En este trabajo, se aborda el problema del control de flujo y congestión en redes. Se propone una metodología basada en la simulación discreta para modelar y analizar el comportamiento de los protocolos de resolución de conflictos en situaciones de congestión. Primero comenzamos con las modificaciones del código propuestas por la catedra, creando los dos nodos extremos que se transmiten mensajes, conectados a traves de una cola, para luego realizar el correspondiente diagnóstico. Lo hicimos modificando el intervalo de tiempo en el que se generaban los mensajes. Probamos los dos casos de estudio. Luego procedimos a realizar las modificaciones e implementacion del algoritmo de control, con el objetivo de investigar cómo estos protocolos pueden evitar la pérdida de datos debido a la saturación de buffers, y se realizan experimentos utilizando simulaciones para evaluar su rendimiento. Los resultados obtenidos muestran el impacto del algoritmo en la reducción de la congestión y la mejora del flujo de datos.

## Introducción
El control de flujo y la congestión son problemas fundamentales en las redes de comunicación. En este trabajo, se busca resolver ambos conflictos para evitar la pérdida de datos. En el caso 1 se busca un control de flujo para evitar que el host emisor desborde a un host receptor que tiene un procesamiento más lento, ya que le llegan los mensajes a menor velocidad. En el caso 2 se busca un control de la congestión que se genera por la velocidad con la que la red entrega los mensajes al host receptor, ya que el emisor los envía más rápido. Para tratar con estos problemas, utilizamos la simulación discreta. Esta nos permite crear un entorno controlado para estudiar el comportamiento de los protocolos en diferentes escenarios de perdidas de paquetes. En lugar de considerar el sistema como dinámico, la simulación discreta se basa en representar los cambios en el sistema (llegada de mensajes, procesamiento de datos, transmisión de paquetes) como eventos discretos que ocurren en momentos específicos. Nos permite analizar el impacto de diferentes parámetros y condiciones de la red, y obtener resultados cuantitativos que nos permiten comparar y evaluar el rendimiento de los algoritmos. Tiene algunas limitaciones, como tener que definir correctamente los eventos discretos y los intervalos de tiempo en los que ocurren, para poder ver una representacion acertada de los cambios.

## Métodos
Como propuuesta para solucionar el problema previamente mencionado, implementamos un algoritmo de control de congestión basado en el TCP Reno. Nuestra hipótesis es que este algoritmo mejorará la capacidad de la red para manejar situaciones de congestión y reducirá la pérdida de datos. Agregamos una variable de ventana de congestión, la cual inicializamos en 1, y un umbral inicializado en 10. Cuando llega un mensaje que proviene del nodo receptor, el cual es de tipo Feedback, conteniendo el valor del buffer restante, llamamos a un handle de la congestion. Chequeamos si el buffer restante llega a 10, en cuyo caso volvemos a setear la ventana de congestion en 1 y avisamos al generador que reduzca su tasa de transmision; si no es así, chequeamos que la ventana de congestión no supere el umbral (lo dejamos fijo en 10) para aplicar crecimiento aditivo. Al establecer una puerta de conexion con el generador, también podemos hacer un control del flujo, haciendo que reduzca la velocidad en la que envia paquetes, en caso de que el buffer del receptor este por llenarse. Esperamos que el canal de conexion entre los nodos, a traves de canales de transporte que se comunican para enviarse Feedback, nos sirva para reducir la cantidad de paquetes perdidos vistos en el análisis previo. 

## Resultados
Realizamos una serie de experimentos utilizando simulaciones para evaluar el rendimiento del algoritmo de control de flujo implementado. Recopilamos datos sobre la congestión de la red, la pérdida de datos y el rendimiento del flujo. Presentamos los resultados obtenidos en forma de gráficos y tablas. Analizamos y discutimos los resultados, destacando las mejoras logradas en términos de reducción de la congestión y disminución de la pérdida de datos.
<image src="results/graficos/COvsCU.jpeg" alt="">
En el grafico se muestran la carga ofrecida contra la carga util, para el caso sin modificaciones y con modificaciones. Se puede ver que sin modificar, la carga util es menor que la ofrecida, ya que el receptor no puede procesar los paquetes a la misma velocidad que el emisor los envia. Cuando aplicamos el algoritmo, la carga util es mayor que la ofrecida, ya que el emisor envia los paquetes a una velocidad menor que la que la red los entrega al receptor.
<image src="results/graficos/IndiceDePerdidasPaquetes.jpeg" alt=""> 
En este podemos ver como cambian las perdidas de paquetes cuando modificamos el algoritmo. No se logra apreciar pero cuando aplicamos las modificaciones, la perdida de paquetes disminuye en gran cantidad, ademas de que al medir con los paquetes generados, con nuestro algoritmo estos se van a ir reduciendo. Cuando el intervalo es 0.15 en la version sin modificaciones, pierde 108 paquetes, en cambio, con el algoritmo, pierde 56 paquetes. Cuando es 0.1, sin modificaciones pierde 170 y con modificaciones, 79. 


<image src="results/graficos/caso1Interv01-NM1.png" alt="sin algoritmo" width=450>
<image src="results/graficos/caso1Interv01-M1.jpeg" alt="con algoritmo" width=480>

el primer grafico corresponde al caso 1 sin modificaciones, y el segundo con modificaciones. 

<image src="results/graficos/caso2Interv01-NM1.png" alt="sin algoritmo" width=450>
<image src="results/graficos/caso2Interv01-M1.jpeg" alt="con algoritmo" width=480>

el primer grafico corresponde al caso 2 sin modificaciones, y el segundo con modificaciones. 


<image src="results/graficos/caso1Interv01-NM2.png" alt="sin algoritmo" width=450>
<image src="results/graficos/caso1Interv01-M2.png" alt="con algoritmo" width=480>

el primer grafico corresponde al caso 1 sin modificaciones, y el segundo con modificaciones.

<image src="results/graficos/caso2Interv01-NM2.png" alt="sin algoritmo" width=450>
<image src="results/graficos/caso2Interv01-M2.png" alt="con algoritmo" width=480>

el primer grafico corresponde al caso 2 sin modificaciones, y el segundo con modificaciones.

## Conclusiones
En este informe, presentamos un estudio sobre el control de flujo y la congestión en redes de comunicación, utilizando la simulación discreta como herramienta principal. Implementamos un algoritmo de control de flujo y realizamos experimentos para evaluar su rendimiento. Los resultados obtenidos demuestran la efectividad del algoritmo en la reducción de la congestión y la perdida de paquetes. Sin embargo, se identificaron limitaciones y áreas para futuras mejoras, como puede ser una aun mayor reducción y también mejorar el retardo. Notamos que sin modificación, no se ven ningun cambio en un caso y otro, ya que lo único que sucede es que cambia en donde sucede la congestión. En general, este trabajo proporciona una base sólida para el desarrollo y la investigación futura en el campo del control de flujo y congestión en redes de comunicación.

## Bibliografia
Tanembaum. Computer Networks: quinta edición del 2011.
Manual del Omnetpp.