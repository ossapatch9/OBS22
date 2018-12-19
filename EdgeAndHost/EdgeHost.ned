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
//
//Modulo que permite unificar el modulo edge y los computadores que enviaran los paquetes de informacion
//
package EdgeAndHost;

import EdgeNode.EdgeNodeComplete;
import SourceSink.SourceSink;

module EdgeHost
{
    parameters:
        int lambdasEdge1; //Number of data channels in the fiber connecting edge1 and core1
        @display("i=abstract/opticalswitch");

    gates:
        input in[];
        output out[];

    submodules:

        Edge: EdgeNodeComplete {
            parameters:
                numInLambdas = lambdasEdge1;
                numOutLambdas = lambdasEdge1;
                @display("p=143,106");
            gates:
                in[lambdasEdge1+1];
                out[lambdasEdge1+1];  
        }
        Host: SourceSink {
            @display("p=67,106");
        }

    connections:

        Host.out --> Edge.inSource;
        Edge.outDestiny --> Host.in;

        for i=0..lambdasEdge1 {
            Edge.out[i] --> out++;
            in++ --> Edge.in[i];

        }
}