//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package EdgeNode;

// Recibe los paquetes entrantes que han coincidido con alguna regla y los agrupa en r�fagas �pticas

simple Burstifier
{
    parameters:
        double maxTime @unit(s); // Tiempo m�ximo
        int maxSize @unit(B); // M�ximo tama�o de r�faga.
        int numPackets; // M�ximo n�mero de paquetes.
        double minOffset @unit(s); //minimo offset del BCP.
        double maxOffset @unit(s); // maximo offset del BCP.
        int minSizePadding @unit(B); //M�nimo tama�o que una r�faga debe tener. Si no logra este tama�o se usan bits de relleno para llegar a este valor. Si es cero, no se realizan tareas de relleno.
        bool addLastPacket; // Si es verdadero permite que el �ltimo paquete entre a la r�faga, incluso si �sta excede el tama�o de la r�faga. Si es falso, la r�faga se ensamblar� y el paquete entrante ser� el primero de la siguiente r�faga
        int tamHeader @unit(B); // Tama�o de cabecera de la r�faga.
        int tamHeaderPacket @unit(B); // Cabecera a�adida para cada paquete dentro de la r�faga.
        int destLabel; // Etiqueta de destino de la r�faga
        @display("i=block/queue");
        
        gates:
            input in;
            output out;
            
}