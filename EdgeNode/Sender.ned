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

package EdgeNode;

//Modulo encargado de la se�alizacion y de convertir la rafaga a su formato de paquete de control y de datos
//Los mensajes que puede recibir este modulo varian entre, mensajes provenientes de cualquier burstifier
//o automensajes que identifican el estado de la rafaga a ser enviada.
//Segun la clase de mensaje esta moduo actua:
//Si recibe un mensaje de una rafaga optica, se encarga de encontrar la longitud de onda con el horizonte mas cercano. (Timempo libre mas pr�ximo)
//Posteriormente la clase BurstSenderInfo alamcena la informa correspondiente a la rafaga y autoprograma un mensaje para
//establecer el envio del BCP.
//Es modulo almacena la rafagas en una lista, cada rafaga posee un tiempo de envio determinado. Sin emabrgo, esta lsta es limintada
//y posee un n�mero maximo de elementos, si esta lista se llena y llega alguna rafaga, �sta ser� eliminada.
//
//La rafaga al mismo tiempo debe confirmar que el canal est� libre durante el tiempo de envio
//
//
//Cuando el mensaje de inicio de BCP se programa, se env�a un auto mensaje con el tipo de estado de rafaga que se quiere enviar
//Cada clase mensaje representa un estado de la rafaga: En primer lugar, se genera el BCP ini, posteriormente, teniendo en
//cuenta el tama�o del mensaje y la velocidad de transmision, envia el fin del BCP y programa la transmision de la rafaga
//, de igual forma tenendp en cuenta la velocidad y el tama�o de la rafaga, se programa el final de la misma.

simple Sender
{
    parameters:
        string colours; // Color de cada canal de salida de control. Debe ser una lista den�mero enteros separados por espacios. Se una una variable string vacia si no se desean colores.
        int numLambdas; // Numeros de canales de datos de salida.
        double dataRate @unit(bps); //Tasa de transmisi�n del canal �ptico.
        int BCPSize @unit(B); // Tama�o del BCP.
        int maxSchedBurstSize @unit(B); //M�ximo tama�o del la cola de r�fagas (0 = infinito).
        int maxSchedBurstElems; // M�ximo n�mero de elementos de la cola de r�fagas (0 = infinito).
        double guardTime @unit(s); // Offset entre transmisiones consecutivas de r�fagas.
        bool testing; // Si es verdadero, el m�dulo no trata de autoregistrarse (se usa para testear este m�dulo fuera del nodo Edge).
        @display("i=block/fork");
        
    gates:
        input in[];
        output out[];
}