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

// Recibe los paquetes entrantes que han coincidido con alguna regla y los agrupa en ráfagas ópticas

simple Burstifier
{
    parameters:
        double maxTime @unit(s); // Tiempo máximo
        int maxSize @unit(B); // Máximo tamaño de ráfaga.
        int numPackets; // Máximo número de paquetes.
        double minOffset @unit(s); //minimo offset del BCP.
        double maxOffset @unit(s); // maximo offset del BCP.
        int minSizePadding @unit(B); //Mínimo tamaño que una ráfaga debe tener. Si no logra este tamaño se usan bits de relleno para llegar a este valor. Si es cero, no se realizan tareas de relleno.
        bool addLastPacket; // Si es verdadero permite que el último paquete entre a la ráfaga, incluso si ésta excede el tamaño de la ráfaga. Si es falso, la ráfaga se ensamblará y el paquete entrante será el primero de la siguiente ráfaga
        int tamHeader @unit(B); // Tamaño de cabecera de la ráfaga.
        int tamHeaderPacket @unit(B); // Cabecera añadida para cada paquete dentro de la ráfaga.
        int destLabel; // Etiqueta de destino de la ráfaga
        @display("i=block/queue");
        
        gates:
            input in;
            output out;
            
}