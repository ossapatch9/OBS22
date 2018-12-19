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
// Auto-mensaje usado en CoreControlUnit para programar las conexiones y desconexiones del módulo OXC.
//
// Este tipo de mensaje puede tomar dos valores:
//
// - OBS_SCHEDULE_OXC (1)
// - OBS_UNSCHEDULE_OXC (2): En este caso, solo será leído el campo inGate.
//
message OBS_ControlUnitInfo
{
    int inGate = -1; // compuerta de entrada OXC 
    int outGate = -1; //compuerta de salida OXC 
}
