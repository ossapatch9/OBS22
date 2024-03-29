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

package CoreNode;

//
// M�dulo compuesto, unidad de control. Permite realizar conversi�n OE/EO; adem�s la unidad e control actua por separado y es la reponsabl del enrutamiento adecuado a traves de la red.
//
module CoreControlUnit
{
    parameters:
        double dataRate @unit(bps); //Velocidad de transmisi�n del canal �ptico
        int numPorts; // N�mero de fibras
        string lambdasPerOutPort; //N�mero de canales de datos de salida por cada fibra
        @display("i=block/cogwheel");

    gates:
        input in[]; //Entrada �ptica
        output out[]; //Salida �ptica

    submodules:

        GatesHorizon: CoreOutputHorizon {
            parameters:
                numPorts = numPorts;
                lambdasPerPort = lambdasPerOutPort;
                @display("p=173,49");
        }


        OE: OEConverter {
            parameters:
                @display("p=53,165");
            gates:
                in[sizeof(in)];
        }

        EO: EOConverter {
            parameters:
                dataRate = dataRate;
                numPorts = numPorts;
                @display("p=294,165");
            gates:
                out[sizeof(out)];

        }
        ControlLogic: CoreControlLogic {
            parameters:
                dataRate = dataRate;
                @display("p=173,136");

        }

    connections:
        for i=0..sizeof(in)-1 {
            in++ --> OE.in[i];
        }

        OE.out --> ControlLogic.in;
        ControlLogic.out --> EO.in;

        for i=0..sizeof(out)-1 {
            EO.out[i] --> out++;
        }

}


