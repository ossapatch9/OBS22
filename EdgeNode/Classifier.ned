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

//
// Este modulo se encarga de asignar una compuerta de salida, que dependera de la direccion y la prioridad del paquete.
// Por el momento las reglas hacen referencias unicamente a la direccion de destino y a la clase o prioridad del paquete
// En un futuro se pueden incluir más reglas que contenga informacion especifica del paquete
//
simple Classifier
{
    parameters:
        @display("i=block/classifier");
        int numOuts; //Número de salidas ( deben ser iguales al número reglas (i en classifier.cc)y las compuertas de salida).
        string rules; // Archivo de texto plano que contiene las reglas.
        
     gates:     
         input in;
         output out[];
}
