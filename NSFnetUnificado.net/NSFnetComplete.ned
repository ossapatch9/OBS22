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
//Red OBS/WDM implementada usando la topologia de la red NSFNet, Ccompuesta por 14 nodos y 21 enlaces bidireccionales


package NSFnetUnificado.net;


import EdgeAndCore2.EdgeCore;


network NSFnetComplete
{
    parameters:
        int lambdasEdge; //Number of data channels in the fiber connecting edge and core
        int lambdasCore;  //Number of data channels in the fiber connecting cores
        @display("bgb=7300,5000;bgi=maps/usa,s;bgg=1000,2,snow1;bgs=0.075,km");

    
    submodules:
        edgeCore1: EdgeCore {
            edgeHost.lambdasEdge1 = lambdasEdge;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.Host.sourceAddress = 1;
            //coreNode.RTF = "core1.dat"; //CAMBIADO
            numPorts = 4;
            @display("p=906.6666,520;is=vs");
            
            gates:
             in[80];
             out[80];          
}
 
        edgeCore2: EdgeCore {
            edgeHost.Host.sourceAddress = 2;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.lambdasEdge1 = lambdasEdge;
            //coreNode.RTF = "core2.dat"; //CAMBIADO
            numPorts = 4;
            @display("p=346.66666,2346.6665;is=vs");
            
            gates:
            in[80];
            out[80];
}

        edgeCore3: EdgeCore {
            edgeHost.Host.sourceAddress = 3;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.lambdasEdge1 = lambdasEdge;
            //coreNode.RTF = "core3.dat";  //CAMBIADO
            numPorts = 4;
            @display("p=813.3333,3133.3333;is=vs");
            
            gates:
            in[80];
            out[80];

}

        edgeCore4: EdgeCore {
            edgeHost.Host.sourceAddress = 4;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.lambdasEdge1 = lambdasEdge;
            //coreNode.RTF = "core4.dat"; //CAMBIADO
            numPorts = 4;
            @display("p=1666.6666,2240;is=vs");
            
            gates:
            in[80];
            out[80];

}

        edgeCore5: EdgeCore {
            edgeHost.Host.sourceAddress = 5;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.lambdasEdge1 = lambdasEdge;
            //coreNode.RTF = "core5.dat"; //CAMBIADO
            numPorts = 4;
            @display("p=2600,2546.6665;is=vs");
            
            gates:
            in[80];
            out[80];

}

        edgeCore6: EdgeCore {
            edgeHost.Host.sourceAddress = 6;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.lambdasEdge1 = lambdasEdge;
            //coreNode.RTF = "core6.dat"; //CAMBIADO
            numPorts = 5;
            @display("p=3519.9998,4160;is=vs");
            
            gates:
            in[80];
            out[80];

}

        edgeCore7: EdgeCore {
           edgeHost.Host.sourceAddress = 7;
           edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
           edgeHost.lambdasEdge1 = lambdasEdge;
           //coreNode.RTF = "core7.dat"; //CAMBIADO
           numPorts = 3;
           @display("p=3519.9998,2146.6665;is=vs");
           
            gates:
            in[80];
            out[80];

}

        edgeCore8: EdgeCore {
            edgeHost.Host.sourceAddress = 8;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.lambdasEdge1 = lambdasEdge;
            //coreNode.RTF = "core8.dat"; //CAMBIADO
            numPorts = 4;
            @display("p=4586.6665,2240;is=vs");
            
            gates:
            in[80];
            out[80];

}

        edgeCore9: EdgeCore {
            edgeHost.Host.sourceAddress = 9;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.lambdasEdge1 = lambdasEdge;
            //coreNode.RTF = "core9.dat"; //CAMBIADO
            numPorts = 5;
            @display("p=5546.6665,2146.6665;is=vs");
            
            gates:
            in[80];
            out[80];

}

        edgeCore10: EdgeCore {
            edgeHost.Host.sourceAddress = 10;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.lambdasEdge1 = lambdasEdge;
            //coreNode.RTF = "core10.dat"; //CAMBIADO
            numPorts = 4;
            @display("p=5146.6665,1453.3333;is=vs");
            
            gates:
            in[80];
            out[80];

}

        edgeCore11: EdgeCore {
            edgeHost.Host.sourceAddress = 11;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.lambdasEdge1 = lambdasEdge;
            //coreNode.RTF = "core11.dat"; //CAMBIADO
            numPorts = 4;
            @display("p=6506.6665,1946.6666;is=vs");
            
            gates:
            in[80];
            out[80];

}

        edgeCore12: EdgeCore {
            edgeHost.Host.sourceAddress = 12;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.lambdasEdge1 = lambdasEdge;
            //coreNode.RTF = "core12.dat"; //CAMBIADO
            numPorts = 4;
            @display("p=6146.6665,2746.6665;is=vs");
            
            gates:
            in[80];
            out[80];

}

        edgeCore13: EdgeCore {
            edgeHost.Host.sourceAddress = 13;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.lambdasEdge1 = lambdasEdge;
            //coreNode.RTF = "core13.dat"; //CAMBIADO
            numPorts = 3;
            @display("p=5466.6665,3533.3333;is=vs");
            
            gates:
            in[80];
            out[80];
            
}
        
        edgeCore14: EdgeCore {
            edgeHost.Host.sourceAddress = 14;
            edgeHost.Host.source.destAddresses = "1 2 3 4 5 6 7 8 9 10 11 12 13 14";
            edgeHost.lambdasEdge1 = lambdasEdge;
            //coreNode.RTF = "core14.dat"; //CAMBIADO
            numPorts = 4;
            @display("p=6306.6665,1453.3333;is=vs");
            
            gates:
            in[80];
            out[80];
            
}
    
        connections allowunconnected:
        
        //se pone lambdasEdge + 1 para que los enlaces comiencen después del número de lambdas edge establecido
        //además no se coloca en todos porque solo se coloca para que cada enlace comience después del lambda edge
        //las demás conexiones se asignan paulatinamente en orden
            
        //Core 1
        //Core 1 to core 2:
        for i=0..lambdasCore {
            edgeCore1.out[i+(lambdasEdge+1)] --> edgeCore2.in[i+(lambdasEdge+1)];
            edgeCore2.out[i+(lambdasEdge+1)] --> edgeCore1.in[i+(lambdasEdge+1)];
        }
        //Core 1 to core 3: 
        for i=0..lambdasCore {
            edgeCore1.out++ --> edgeCore3.in[i+(lambdasEdge+1)];
            edgeCore3.out[i+(lambdasEdge+1)] --> edgeCore1.in++;
        }
        //Core 1 to core 8: 
        for i=0..lambdasCore {
            edgeCore1.out++ --> edgeCore8.in[i+(lambdasEdge+1)];
            edgeCore8.out[i+(lambdasEdge+1)] --> edgeCore1.in++;
        }
        
        
        //Core 2
        //Core 2 to core 1 ya esta en core 1

        //Core 2 to core 3
        for i=0..lambdasCore {
            edgeCore2.out++ --> edgeCore3.in++;
            edgeCore3.out++ --> edgeCore2.in++;
        }

        //Core 2 to core 3
        for i=0..lambdasCore {
            edgeCore2.out++ --> edgeCore4.in[i+(lambdasEdge+1)];
            edgeCore4.out[i+(lambdasEdge+1)] --> edgeCore2.in++;
        }
        
        //Core 3
        //Core 3 to core 1 ya esta en core 1 

        //Core 3 to core 2 ya esta en el core 2

        //core 3 to core 6
        for i=0..lambdasCore {
            edgeCore3.out++ --> edgeCore6.in[i+(lambdasEdge+1)];
            edgeCore6.out[i+(lambdasEdge+1)] --> edgeCore3.in++;
        }

        //Core 4
        //Core 4 to core 2 ya esta en core 2

        //Core 4 to core 5 
        for i=0..lambdasCore {
            edgeCore4.out++ --> edgeCore5.in[i+(lambdasEdge+1)];
            edgeCore5.out[i+(lambdasEdge+1)] --> edgeCore4.in++;
        }

        //Core 4 to core 10 
        for i=0..lambdasCore {
            edgeCore4.out++ --> edgeCore10.in[i+(lambdasEdge+1)];
            edgeCore10.out[i+(lambdasEdge+1)] --> edgeCore4.in++;
        }
        
        //Core 5
        //Core 5 to core 4 ya esta en core 4

        //Core 5 to core 6
        for i=0..lambdasCore {
            edgeCore5.out++ --> edgeCore6.in++;
            edgeCore6.out++ --> edgeCore5.in++;
        }

        //Core 5 to core 7
        for i=0..lambdasCore {
            edgeCore5.out++ --> edgeCore7.in[i+(lambdasEdge+1)];
            edgeCore7.out[i+(lambdasEdge+1)] --> edgeCore5.in++;
        }

        //Core 6
        //Core 6 to core 3 ya esta en core 3
        //Core 6 to core 5 ya esta en core 5

        //Core 6 to core 12 
        for i=0..lambdasCore {
            edgeCore6.out++ --> edgeCore12.in[i+(lambdasEdge+1)];
            edgeCore12.out[i+(lambdasEdge+1)] --> edgeCore6.in++;
        }

        //Core 6 to core 13
        for i=0..lambdasCore {
            edgeCore6.out++ --> edgeCore13.in[i+(lambdasEdge+1)];
            edgeCore13.out[i+(lambdasEdge+1)] --> edgeCore6.in++;
        }
        
        //Core 7
         //Core 7 to core 5 ya esta en core 5   

        //Core 7 to core 5
        for i=0..lambdasCore {
            edgeCore7.out++ --> edgeCore8.in++;
            edgeCore8.out++ --> edgeCore7.in++;
        }

          //Core 8
          //Core 8 to core 1 ya esta en core 1 
          //Core 8 to core 7 ya esta en core 7

        //Core 8 to core 9 
        for i=0..lambdasCore {
            edgeCore8.out++ --> edgeCore9.in[i+(lambdasEdge+1)];
            edgeCore9.out[i+(lambdasEdge+1)] --> edgeCore8.in++;
        }

          //Core 9
          //Core 9 to core 8 ya esta en core 8

        //Core 9 to core 11
        for i=0..lambdasCore {
            edgeCore9.out++ --> edgeCore11.in[i+(lambdasEdge+1)];
            edgeCore11.out[i+(lambdasEdge+1)] --> edgeCore9.in++;
        }

        //Core 9 to core 13
        for i=0..lambdasCore {
            edgeCore9.out++ --> edgeCore13.in++;
            edgeCore13.out++ --> edgeCore9.in++;
        }

        //Core 9 to core 14
        for i=0..lambdasCore {
            edgeCore9.out++ --> edgeCore14.in[i+(lambdasEdge+1)];
            edgeCore14.out[i+(lambdasEdge+1)] --> edgeCore9.in++;
        }
        
        //Core 10
        //Core 10 to core 4 ya esta en core 4

        //Core 10 to core 11 
        for i=0..lambdasCore {
            edgeCore10.out++ --> edgeCore11.in++;
            edgeCore11.out++ --> edgeCore10.in++;
        }

        //Core 10 to core 11
        for i=0..lambdasCore {
            edgeCore10.out++ --> edgeCore14.in++;
            edgeCore14.out++ --> edgeCore10.in++;
        }

          //Core 11
          //Core 11 to core 9 ya esta en core 9
          //Core 11 to core 10 ya esta en core 10

        //Core 11 to core 12
        for i=0..lambdasCore {
            edgeCore11.out++ --> edgeCore12.in++;
            edgeCore12.out++ --> edgeCore11.in++;
        }

          //Core 12
          //Core 12 to core 6 ya esta en core 6
          //Core 12 to core 11 ya esta en core 11  

        //Core 12 to core 14
        for i=0..lambdasCore {
            edgeCore12.out++ --> edgeCore14.in++;
            edgeCore14.out++ --> edgeCore12.in++;
        }

          //Core 13
          //Core 13 to core 6 ya esta en core 6
          //Core 13 to core 9 ya esta en core 9   

          //Core 14
          //Core 14 to core 9 ya esta en core 9
          //Core 14 to core 10 ya esta en core 10
          //Core 14 to core 12 ya esta en core 12
       
}
