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
// Conversor �ptico-el�ctrico. Reune el inicio y final de los BCPs y crea un BCP el�ctrico incluyendo informaci�n  sobre la fibra de entrada y el tiempo de llegada del iniBCP.
//
simple OEConverter
{
    parameters:
        double OEConversionDelay @unit(s); //Tiempo de procesamiento requerido para realizar la conversi�n �ptico electr�nica
        @display("i=block/arrival");
    gates:
        input in[];
        output out;
}

