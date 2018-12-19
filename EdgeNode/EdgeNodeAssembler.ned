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

//Modulo compuesto denominado ensamblardos, ya que agrupa los paquetes que han coindido con las reglas, los almacena en 
//rafagas, y posteriormente los trata para obtener su correspondiente BCP y la rafaga de datos.

package EdgeNode;

module EdgeNodeAssembler
{
     parameters:
        string colours; // Vector identificador de colores para cada canal de salida de salida. Debe ser una lista de númueros enteros separada por espacios. Se usa una variable string vacia si no se desean usar colores.
        int numBurstifiers; //debe ser igual a numOuts, salidas del clasificador
        string rulesFile; //reglas provenientes de classifier
        int numLambdas; // Número de canales de salidas de datos (canal de control no incluido).
        @display("i=block/tx");
    gates:
        input in;
        output out[]; //Salida óptica

    submodules:

        classifier: Classifier {

            parameters:
                numOuts = numBurstifiers;
                rules = rulesFile;
                @display("p=125,110");
            gates:
                out[numBurstifiers];
        }

        burstifier[numBurstifiers]: Burstifier {

            parameters:
                @display("p=197,171");
        }

        sender: Sender {

            parameters:
                colours=colours;
                numLambdas = numLambdas;
                @display("p=272,231");
            gates:
                in[numBurstifiers];
                out[numLambdas+1];
        }
        
connections:
    
         in --> classifier.in;
        
         for i=0..numBurstifiers-1 {
            classifier.out[i] --> burstifier[i].in;
            burstifier[i].out --> sender.in[i];
        }
        
        for i=0..numLambdas {
            sender.out[i] --> out++;
        }

}
