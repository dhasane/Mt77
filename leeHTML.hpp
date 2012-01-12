/**@file leeHTML.hpp
 * Lee un archivo en formato HTML e incluye su 
 * informaci�n a un �ndice.
 *
 * @package Mt77
 * @author Vladimir T�mara Pati�o. vtamara@pasosdeJesus.org
 * Dominio p�blico. 2009.  Sin garant�as
 * http://creativecommons.org/licenses/publicdomain/
 * @version   $Id: leeHTML.hpp,v 1.4 2010/01/06 11:48:45 vtamara Exp $
 */

#if !defined(LEEHTML_HPP)
#define LEEHTML_HPP

#include <string>
#include "NodoTrieS.hpp"

void insertaNormalizada(string pal, long ndoc, long p, NodoTrieS &t,
                        bool normalizaPal);

/** Construye un trieS a partir de un HTML */
void leeHTML(const char *na, long ndoc, NodoTrieS &t, bool normalizaPal);

#endif
