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
//Mensaje que posse una estructura de clase "Cola" encargada de implementar metodos para el almacenamiento, extraccion o envio 
//de rafagas
//
class cQueue;

packet Burst
{
@customize(true); //permite usar el mensaje como una clase virtual, implementado metodos que pueden ser tratados directamente en C++
cQueue Messages; //cola de mensajes
int numPackets = -1;

simtime_t minOffset = -1;
simtime_t maxOffset = -1;

int sourceAddress = -1;  //direccion de origen
int destAddress = -1; //direccion de destino

int numSaltos; //variable numero de saltos para retardo de procesamiento

int secuencia = -1; //Variable para probabilidad de bloqueo
int idBurstifier = -1;

int secNum= -1;
int sendId = -1;
}