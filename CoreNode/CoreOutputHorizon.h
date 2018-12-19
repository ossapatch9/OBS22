/*
 * CoreOutputHorizon.h
 *
 *  Created on: 3/04/2013
 *      Author: Tatiana y Adriana
 */

#ifndef COREOUTPUTHORIZON_H_
#define COREOUTPUTHORIZON_H_

#include<omnetpp.h>

// La tabla de horizonte guarda el tiempo donde cada canal �ptico se encuentra disponible (Este tiempo es llamado, el horizonte).
// Esta tabla est� estructurada como una vector bidimensional donde el primer componente el n�mero del puerto y el segundo componente es el canal de datos:
//
// horizon[fibra][canal]
//
//Esta tabla no incluye los canales de control de la fibra porque �stos no necesitan valor de horizonte.
class CoreOutputHorizon : public cSimpleModule{
   protected:
      simtime_t **horizon; //Vector horizonte. Tiene dos dimensiones: horizon[port][lambda].
      int *portLambdas; //N�mero de canales de datos para cada puerto.

      virtual void initialize();
   public:
      virtual ~CoreOutputHorizon();
      // Encuentra el lambda cuyo horizonte (tiempo en el que el canal est� libre) es el menor y el m�s cercano al valor del tiempo de llegada dado.
      // Par�metro: puerto de la fibra �ptica para realizar la b�squeda
      // Par�metro: valor de arrivalTime usado para la b�squeda.
      int findNearestLambda(int port,simtime_t arrivalTime);
      // Actualiza el valor del horizonte al nuevo valor de tiempo.
      // Par�metro: puerto de la fibra �ptica.
      // Par�metro: canal lambda para actualizar.
      // Par�metro: nuevo tiempo actualizado para el valor del horizonte.
      void updateHorizon(int port, int lambda, simtime_t newTime);
      // Retorna el horizonte actual del canal selecionado.
      // Par�metro: puerto de la fibra �ptica.
      // Par�metro: longitud de onda del canal �ptico.
      simtime_t getHorizon(int port,int lambda);
};

#endif /* COREOUTPUTHORIZON_H_ */
