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

packet ScheduleBurst
{
    int listIndex = -1; //Campo de índice usado por BurstList.
    int idBurst = -1; //Id de la ráfaga (Burst).
    simtime_t sendTime = -1; //Tiempo programado para enviar la ráfaga.
    simtime_t minOffset = -1; //offset mínimo.
    simtime_t maxOffset = -1; //offset máximo.
}