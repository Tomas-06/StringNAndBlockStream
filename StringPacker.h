/* StringPacker.h
 * Este header facilita el manejo de strings de un tamaño variable
 * pero acotado, se base en arrays<char,N> y define 
 * PackString(s) y s = UnpackString(a)
 * 
 * Si s.length()>=N, entonces solo guarda los primeros N caracteres de s en a,
 * sino, guarda todos los caracteres de s en a y agrega un '\0' al final. Esto
 * implica que dado:
 *   a=PackString(s), t=UnpackString(a)
 *   entonces s!=t si |a|<|s|
 * Pero si se vuelve a aplicar:
 * 	 a=PackString(t), u=UnpackString(a)
 *   entonces se cumple t==a.
 * Características de la solución:
 * - Los arreglos tienen un tamaño fijo.
 * - El tamaño del array denota la capacidad máxima real de caracteres 
 *   del array, no la cantidad de caracteres menos uno.
 * - No requiere conocer conocer el concepto punteros para usar la solución.
 * - No requiere conocer conocer el concepto del centinela '\0' para usar
 *   la solución.
 * - El centinela se usa internamente para strings más cortos que el array 
 *   que lo contiene.
 * 
 * Ejemplo de uso:
 *  #include <string>
 *  #include <array>
 *  #include <cassert>
 *  #include "PackString.h"
 *
 *  std::string s = "Hello, World!";
 *  std::array<char,5> a = PackString(s);
 *  std::string t = UnpackString(a);
 *  assert(t=="Hello");
 *
 * Esp. Ing. José María Sola
 * Profesor
 * UTN FRBA
 */

#include <string>
#include <array>

/* Implemantation based upon 
http://stackoverflow.com/questions/8165659/why-cant-c-deduce-template-type-from-assignment
*/

using std::size_t;
using std::array;
using std::string;

/* Provides the constructs to pack strings with a simple and clear syntax:
 * a=PackString(s)
 */
struct PackString{
	string theString;
	
	// Build from string
	PackString(const string& aString) : theString(aString) {}
	
	// User-defined conversion: from string to array<char,N>
	template<size_t N>
	inline operator array<char, N>(){
		array<char, N> anArray;
		auto len = theString.length();
		
		if( len < N ){
			theString.copy(anArray.data(), len);
			anArray.at(len) = '\0';
		}else
			theString.copy(anArray.data(), N);
			
	    return anArray;
	}
};

/* Constructs a string from an array up to the first null characater 
 * or the end of the array
 */
template<size_t N> 
inline string UnpackString(const array<char,N>& a){
	string s;
	
	for(auto c : a){
		if(c=='\0')
			break;
		s.push_back(c);
	}
	
	return s;
}

