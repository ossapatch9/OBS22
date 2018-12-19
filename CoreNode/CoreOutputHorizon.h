/*
 * CoreOutputHorizon.h
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef COREOUTPUTHORIZON_H_
#define COREOUTPUTHORIZON_H_

#include<omnetpp.h>

// La tabla de horizonte guarda el tiempo donde cada canal óptico se encuentra disponible (Este tiempo es llamado, el horizonte).
// Esta tabla está estructurada como una vector bidimensional donde el primer componente el número del puerto y el segundo componente es el canal de datos:
//
// horizon[fibra][canal]
//
//Esta tabla no incluye los canales de control de la fibra porque éstos no necesitan valor de horizonte.
class CoreOutputHorizon : public cSimpleModule{
   protected:
      simtime_t **horizon; //Vector horizonte. Tiene dos dimensiones: horizon[port][lambda].
      int *portLambdas; //Número de canales de datos para cada puerto.

      virtual void initialize();
   public:
      virtual ~CoreOutputHorizon();
      // Encuentra el lambda cuyo horizonte (tiempo en el que el canal está libre) es el menor y el más cercano al valor del tiempo de llegada dado.
      // Parámetro: puerto de la fibra óptica para realizar la búsqueda
      // Parámetro: valor de arrivalTime usado para la búsqueda.
      int findNearestLambda(int port,simtime_t arrivalTime);
      // Actualiza el valor del horizonte al nuevo valor de tiempo.
      // Parámetro: puerto de la fibra óptica.
      // Parámetro: canal lambda para actualizar.
      // Parámetro: nuevo tiempo actualizado para el valor del horizonte.
      void updateHorizon(int port, int lambda, simtime_t newTime);
      // Retorna el horizonte actual del canal selecionado.
      // Parámetro: puerto de la fibra óptica.
      // Parámetro: longitud de onda del canal óptico.
      simtime_t getHorizon(int port,int lambda);
};

#endif /* COREOUTPUTHORIZON_H_ */
