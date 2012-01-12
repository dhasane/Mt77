// vim: set expandtab tabstop=8 shiftwidth=8 foldmethod=marker:
/**
 * Posici�n de una palabra en un documento
 *
 * @package   Mt77
 * @author    Vladimir T�mara <vtamara@pasosdeJesus.org>
 * 2008. Dominio p�blico. Sin garant�as.
 * http://creativecommons.org/licenses/publicdomain/ Dominio P�blico. Sin garant�as.
 * @version   $Id: Pos.hpp,v 1.13 2010/01/18 16:12:50 vtamara Exp $
*/

#if !defined(Pos_hpp)
#define Pos_hpp

#include "comun.hpp"
#include <stdint.h>

using namespace std;

/**
 * Clase que representa una posici�n en un archivo entre varios posibles.
 */
class Pos
{
        public:
                uint32_t numd;  /**< N�mero de documento */
                uint32_t numb;  /**< N�mero de byte en el que est� la palabra */
                Pos(uint32_t d, uint32_t n):numd(d), numb(n)
                {
                        ASSERT(d>0);
                        ASSERT(n>0);
                }

};

/**
 * Env�a una representaci�n plan de una posici�n a un flujo de salida
 * @param os Flujo de salida
 * @param p Posici�n
 */
std::ostream &operator<<(std::ostream &os, Pos p);

/**
 * Comparacio entre 2 posici�nes
 * @param p1 Primera
 * @param p2 Segunda
 * @return verdadero si y solo si p1 es menor que p2
 **/
bool operator<(Pos p1, Pos p2);

/**
 * Escribe lista de posiciones
 * @param os Flujo de salida
 * @param cpos Conjunto de posiciones, puede ser NULL
 *
 **/
void escribePos(iostream &os, set<Pos> *cpos);


/**
 * Calcula longitud que requerir�a escribePos para escribir cpos
 *
 * @param cpos Conjunto de posiciones, puede ser NULL
 * @return N�mero de bytes
 */
uint32_t longPos(set<Pos> *cpos);

/**
 * Saca copia de un conjunto de posiciones, renumerando los documentos.
 * @param p Posiciones iniciales
 * @param renum para renumerar posiciones.  
 *
 * @see leePos
 * @return Copia renumerada
 **/
set<Pos> *copiaPos(set<Pos> &p, vector<int64_t> *renum);

/**
 * Lee lista de posiciones
 * @param is Flujo de entrada
 * @param renum Si no es NULL renumera posiciones le�das de acuerdo a este
 * 	vector.
 *  	renum[0] tiene nuevo n�mero menos 1 para documento 1, ... 
 *  	renum[n-1] nuevo n�mero menos 1 para n-esimo documento.
 * 	Si renum[i] es -1 no se incluir� en la respuesta el documento i+1 esimo,
 *
 * @return Conjunto de posiciones --renumerados si renum no es NULL
 **/
set<Pos> *leePos(istream &is, vector<int64_t> *renum = NULL);


#endif
