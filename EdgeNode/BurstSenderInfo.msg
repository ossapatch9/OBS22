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
//clase mensaje que almacenara de forma temporal la informacion de la rafaga y luego la transmitira al BCP.

class BurstSenderInfo
{
      int burstId = -1; // Identificador interno de la r�faga usado s�lo por el m�dulo sender. Este id es independiente de cualquier otro id.
      int idBurstifier = -1; // Identificador del Burstifier. Es una parte del identificador de la r�faga
      int numSeq = -1; // N�mero de secuencia. Es otra parte del identificador de la r�faga.
      int assignedLambda = -1; //lambda Asignado.
      int label = -1; // Etiqueta de destino.
}