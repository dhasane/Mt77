/**@file leePDF.hpp
 * Lee un archivo en formato PDF e incluye su 
 * informaci�n a un �ndice.
 *
 * @package Mt77
 * @author Vladimir T�mara Pati�o. vtamara@pasosdeJesus.org
 * Dominio p�blico. 2009.  Sin garant�as
 * http://creativecommons.org/licenses/publicdomain/
 * @version   $Id: leePDF.hpp,v 1.2 2010/01/06 10:09:30 vtamara Exp $
 */

#if !defined(LEEPDF_HPP)
#define LEEPDF_HPP

#include <string>
#include "comun.hpp"
#include "NodoTrieS.hpp"


/**
 * Convierte un archivo en formato PDF  a texto plano y agrega las palabras del 
 * documento al �rbol [t].
 * @param na           Nombre del archivo
 * @param ndoc         N�mero de documento que corresponde al archivo na
 * @param &t           �rbol al cual deben agregarse palabras y sus posiciones
 * @param normalizaPal �ndica si deben normalizarse o no las
 * palabras leidas
 *
 * @return void
 */
void leePDF(const char *na, long ndoc, NodoTrieS &t, bool normalizaPal)
throw(std::string);

#endif
