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
// M�dulo de entrada para el CoreNode. Separa las fibras �pticas en dos: canales de control, conectados a la unidad e control y canales de datos conectados a OXC.
//
simple CoreInput
{
    parameters:
        
        int numPorts; //N�mero de fibras de entrada
        string lambdasPerPort;  //N�mero de canales de datos por cada fibra
        string colours; // Color de cada canal de datos de cada fibra. Debe ser una lista de n�mero enteros separados por barras (cada barra representa una fibra). Se usa una cadena vacia si no se desea usar colores .Ejemplo: "2 3 4 | 4 3 2 | 5 4 3" (3 fibras con 3 lambdas cada una)
        @display("i=block/arrival");
    gates:
        input in[];
        output out[];
}
