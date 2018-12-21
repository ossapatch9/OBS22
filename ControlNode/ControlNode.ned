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
// Dispositivo para conmutación en la arquitectura OBS.
//
module ControlNode
{
    parameters:
        int numPorts; //Número def fibras
        string lambdasPerInPort; //Número de canales de datos de entrada por cada fibra
        string lambdasPerOutPort; //Número de canales de daos de salida por cada fibra 
        string inputColours; // Color de cada canal de datos de entrada de cada fibra. Debe ser una lista de números enteros separados por barras (cada barra representa una fibra). Se usa una cadena vacia si no se desea usar colores .Ejemplo: "2 3 4 | 4 3 2 | 5 4 3" (3 fibras con 3 longitudes de onda cada una)
        string outputColours; // Color de cada canal de datos de salida de cada fibra. Debe ser una lista de números enteros separados por barras (cada barra representa una fibra). Se usa una cadena vacia si no se desea usar colores .Ejemplo: "2 3 4 | 4 3 2 | 5 4 3" (3 fibras con 3 longitudes de onda cada una)
        string variableCoreNode ="Nodo Core";
        @display("bgb=434,264;i=block/switch");
    gates:
        input in[];
        output out[];

    submodules:

        coreInput: ControlInput {
            parameters:
                numPorts = numPorts;
                colours = inputColours;
                lambdasPerPort = lambdasPerInPort;
                @display("p=79,139");

            gates:
                in[sizeof(out)];
                out[sizeof(out)];
        }

        coreControlUnit: ControlControlUnit {
            parameters:
                numPorts = numPorts;
                lambdasPerOutPort = lambdasPerOutPort;
                @display("p=212,58");

            gates:
                in[numPorts]; //Una compuerta para el canal BCP
                out[numPorts]; //Una compuerta para el módulo de salida
        }

        coreOutput: ControlOutput {
            parameters:
                numPorts = numPorts;
                colours = outputColours;
                lambdasPerPort = lambdasPerOutPort;
                @display("p=336,139");

            gates:
                in[sizeof(out)];
                out[sizeof(out)];
        }

        OXC: OpticalCrossConnect {
            parameters:
                @display("p=212,194");

            gates:
                in[sizeof(in)-numPorts]; //porque por los primero puertos pasan los BCP, por lo tanto no se toman esos puertos
                out[sizeof(out)-numPorts];
        }

        routingNuevo: RoutingNuevo {
            @display("p=375,45");
        }
    connections:
        //Conexión de los canales de control de entrada
        for i=0..sizeof(in)-1 {
            in++ --> coreInput.in[i];
        }

        //Conexión de los canales de control de salida
        for i=0..sizeof(out)-1 {
            coreOutput.out[i] --> out++;
        }

        //Conexión de los canales de control con la unidad de control
        for i=0..numPorts-1 {
            coreInput.out[i] --> coreControlUnit.in[i];
            coreControlUnit.out[i] --> coreOutput.in[i];
        }

        //Conexión de los canales de datos de entrada
        for i=numPorts..sizeof(in)-1 {
            coreInput.out[i] --> OXC.in[i-numPorts];
        }

        //Conexión de los canales de datos de salida
        for i=numPorts..sizeof(out)-1 {
            OXC.out[i-numPorts] --> coreOutput.in[i];
        }
}
