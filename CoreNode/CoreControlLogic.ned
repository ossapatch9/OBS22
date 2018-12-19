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

package CoreNode;

//
// Control logico: es el encargado de establecer o liberar conexiones basadas en la informacion contenida en el BCP.
//
// Una vez este modulo reciba un BCP electrico, envia un peticion a la tabla de enrutamiento la cual actualiza la informacion del destino, longitud de onda y puerto de salida de la rafaga
// Por ultimo, el modulo actualiza la informacion del BCP, tomada de la tabla de enrutmiento, y envia la rafaga al siguiente modulo, paralelamente, envia un automenSaje para el establecimiento o liberacion del canal OXC.
//

simple CoreControlLogic
{
    parameters:
        double guardTime @unit(s); //Tiempo de guarda colocado entre la reserva de OXC  el tiempo de llegada de la ráfaga.
        double BCPProcessingDelay @unit(s); //Tiempo de procesamiento del BCP
        double dataRate @unit(bps); //Velocidad de transmisión del canal óptico. Usado para calcular los tiempos no establecidos de las conexiones OXC.
        string reportFile; // Nombre del archivo para guardar información sobre las ráfagas que cruzan el nodo core. "" no guarda nada.
        @display("i=block/cogwheel");
    gates:
        input in;
        output out;
}
