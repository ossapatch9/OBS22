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


//También conocido como BCP. Mensaje de control para la transmisión en OBS.
//
//El campo "Kind" identifica las clases de este mensaje:
//
// - <b>kind 1</b>: Inicio del BCP óptico
// - <b>kind 2</b>: Fin del BCP óptico
// - <b>kind 3</b>: BCP eléctrico (usado en CoreControlUnit)

packet BurstControlPacket
{
    simtime_t deltaArriveBurst = -1; //Diferencia entre el tiempo actual y el tiempo estimado de llegada de la ráfaga
    int colorBurst = -1; //color de la ráfaga
    int label = -1; //Etiqueta de destino

    int idBurstifier = -1; //id del Burstifier
    int numSeq = -1; //Número de secuencia dentro de packet burstifier

    int idSend = -1; //Identificador del Burst sender. No usado como un id

    int burstSize = -1; // Tamaño asociado de la ráfaga
    
    //variable para numero de saltos, usada para el calculo de retardo de procesamiento
    int numSaltos;
}