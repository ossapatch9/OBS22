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
//Modulo encargado de orientar el camino del BCP, asignando para él el puerto de salida, la longitud de onda por la cual viajara la ragafa y la direccion de destino.
//Este modulo descubre la red usando la herramienta incluida en cToplogy, que permite trabajar mediante grafos, con los nodos de toda la red
//el algoritmo usado para este erutamiendo, es de tipo estático y permite hallar la ruta mas corta entre dos nodos.

package CoreNode;

simple RoutingNuevo
{
    parameters:
        @display("i=block/table2");
        
}