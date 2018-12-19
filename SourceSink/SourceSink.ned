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
//Modulo compuesto que contiene el Host, compuesto por un origen y un destino.

package SourceSink;


module SourceSink
{
    parameters:
        int sourceAddress;
        @display("i=device/pc");

    gates:

        input in;
        output out;

    submodules:
        source: Source {
            parameters:
                address = sourceAddress;
                @display("p=97,193");
        }
        sink: Sink {
            @display("p=97,115");
        }

    connections:
        source.out --> out;
        in --> sink.in;
}
