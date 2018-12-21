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
// Este módulo maneja la viabilidad de los canales de datos de salida del CoreNode.
//Guarda el registro de las longitudes de onda que estan ocupadas, liberadas, o que pueden usarse para encaminar una rafaga.
//
// No se encuentra conectado a otro móudlo.
//
simple ControlOutputHorizon
{
    parameters:
        int numPorts; // Número de fibras de salida
        string lambdasPerPort; //Número de canales de datos por cada fibra
        @display("i=block/table");
}

