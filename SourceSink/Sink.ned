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

package SourceSink;

//Como el objetivo es analizar el RWA en redes opticas OBS/WDM, el modulo Sink se encarga de borrar los paquetes que llegan al
//destino, ya que no se analizará el tratamiento, luego de llegar al destino, y al mismo tiempo, esto permite liberar memoria
//dinamica para mejorar el rendimiento de la red durante el analisis.

simple Sink
{
    parameters:
        //int comparisonType = default(2); //Type of comparison.
        //double timeTolerance @unit(s) = default(0s); //Tolerance to compare time values.
        //string patternFile; //File with the pattern to be compared with the output.
        //string outputFile; //File where the output will be saved.
        @display("i=block/sink");
    gates:
        input in;
}