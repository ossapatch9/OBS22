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

package ControlNode;

//
// Conversor eléctrico óptico. Convierte las BCP eléctricas al dominio óptico (comienzo y final del BCP).
//
simple EOConverter
{
    parameters:
        double EOConversionDelay @unit(s); //Tiempo de procesamiento requerido para realizar la conversión electrico óptica
        double dataRate @unit(bps); // Velocidad de transmisión del canal óptico
        int numPorts; // Número de fibras
        @display("i=block/arrival");
    gates:
        input in;
        output out[];
}