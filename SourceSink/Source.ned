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
//Modulo que genera los paquetes provenientes de un computador, para ser enviados a las red y llegar a un destino

package SourceSink;

simple Source
{
    parameters:
        int address; //Dirección origen
        string destAddresses;  // Direcciones de destino
        volatile double sendIaTime @unit(s); // tiempo entre la generación de paquetes
        volatile int packetLength @unit(byte);  // longitud del mensaje
        @display("i=block/source");
        @signal[endToEndDelay](type="simtime_t");
        @signal[numberHops](type="int");
        @signal[sourceAddress](type="int");
        @statistic[endToEndDelay](title="end-to-end delay of arrived packets";unit=s;record=vector,mean,max;interpolationmode=none);
        @statistic[numberHops](title="hop count of arrived packets";interpolationmode=none;record=vector?,mean,max);
        @statistic[sourceAddress](title="source address of arrived packets";interpolationmode=none;record=vector?);
    gates:
        output out;
}
