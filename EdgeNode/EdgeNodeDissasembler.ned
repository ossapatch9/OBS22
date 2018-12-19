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

// Se encarga de desemblamblar la rafaga y abtraer la informacion necesaria de ésta
//Las BCP_INI recibidas con almacenadas en unas lista hasta que llega la rafaga con el mensaje de finalizacion (BCP_END)
// Una vez llega el final de la rafaga, se busca en la lista el ID que le corresponde, abstrae los paquetes y disminuye el contenido de la lista.

simple EdgeNodeDisassembler
{
    parameters:
        @display("i=block/rx");
        
    gates:
        input in[];
        output out;
}