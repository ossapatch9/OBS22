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
// Interfaz óptica para el nodo edge. Tiene un ensambladror que recibe paquetes y los agrupa en ráfagas. Al mismo y tiempo, recibe las rágafas y las desensambla.
//
module EdgeNodeComplete
{
    parameters:
        string outColours; // Vector de colores para canales de datos de salida.
        int numInLambdas; // Número de canales de datos de entrada.
        int numOutLambdas; //Número de canales de datos de salida.
        @display("i=block/classifier2");
        
    gates:
        
        input in[];
        output out[];

        input inSource;
        output outDestiny;

    submodules:

        edgeNodeAssembler: EdgeNodeAssembler {
            parameters:
                colours = outColours;
                numLambdas = numOutLambdas;
                @display("p=75,86");

            gates:
                out[numOutLambdas +1];
        }

         edgeNodeDisassembler: EdgeNodeDisassembler 
        {
            parameters:
            //colours = inColours;
            @display("p=75,156");
            
            gates:
                in[numInLambdas+1];
        }
    connections:

        inSource --> edgeNodeAssembler.in;

        for i=0..numOutLambdas 
        {
            edgeNodeAssembler.out++ --> out++;
        }
        
        for i=0..numInLambdas 
        {
        in++-->edgeNodeDisassembler.in++;
        }
        
        edgeNodeDisassembler.out-->outDestiny;

}
