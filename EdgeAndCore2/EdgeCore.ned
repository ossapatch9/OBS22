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
//Este modulo permite unificar los nodos edge y core para que hagan parte de un modulo compuesto, estoy implica organizar conexiones de forma adecuada
package EdgeAndCore2;

import CoreNode.CoreNode;
import EdgeAndHost.EdgeHost;


module EdgeCore
{
    parameters:
        int x = 3;
        int numPorts;
        int lambdasEdge; //Number of data channels in the fiber connecting edge and core
        int lambdasCore;  //Number of data channels in the fiber connecting cores
        @display("i=abstract/switch");

    gates:
        input in[100];
        output out[100];

    submodules:
        edgeHost: EdgeHost {
            @display("p=83,86");

            gates:
                in[lambdasEdge+1];
                out[lambdasEdge+1];
        }
        coreNode: CoreNode {
            numPorts = numPorts;
            @display("p=186,86");
        }

    connections allowunconnected:

        for i=0..lambdasEdge {
            edgeHost.out[i] --> coreNode.in++;
            coreNode.out++ --> edgeHost.in[i];

        }

        for j=0..((lambdasCore + 1)*(numPorts-1)-1) {
            coreNode.out++ --> out[j+(lambdasEdge+1)]; //si lambdas edge y core son diferentes, se debe cambiar eso y lo de abajo
            in[j+(lambdasEdge+1)] --> coreNode.in++;

        }
}
