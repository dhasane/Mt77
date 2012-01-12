/** @file Doc.hpp
 * Datos de un documento indexado
 *
 * @package Mt77
 * @author Vladimir T�mara Pati�o. vtamara@pasosdeJesus.org
 * Dominio p�blico. 2009.  Sin garant�as
 * http://creativecommons.org/licenses/publicdomain/
 * @version   $Id: Doc.hpp,v 1.8 2010/01/18 16:12:50 vtamara Exp $
 */


#if !defined(Doc_hpp)
#define Doc_hpp

#include "comun.hpp"

using namespace std;

/**
 * Clase que representa una posici�n en un archivo entre varios posibles.
 */
class Doc
{
        public:
                string URL; /**< URL del documento */
                string cond; /**< Condensado SHA-256 */
                string fecha; /**< Fecha de actualizaci�n */
                uint32_t numoc; /**< N�mero de ocurrencias (resultado de b�squeda)*/

                Doc(string u, string c, string f, long n = 0): 
			URL(u), cond(c), fecha(f), numoc(n)
                {
                        //cout << f << endl;
                        ASSERT(u.length() > 0);
                        ASSERT(u.length() < MAXLURL);
                        ASSERT(c.length() <= MAXLCONDENSADO);
                        ASSERT(f.length() == 10 && f[4] == '-' &&
                               f[7] == '-');
                }
};

/**
 * Env�a una representaci�n plana de un documento a un flujo de salida
 * @param os Flujo de salida
 * @param d Documento
 */
std::ostream &operator<<(std::ostream &os, Doc d);

/**
 * Comparacio entre 2 documentos de acuerdo al escalafon
 * @param d1 Primero
 * @param d2 Segundo
 * @return verdadero si y solo si d1 es menor que d2
 **/
bool operator<(Doc d1, Doc d2);


/**
 * Escribe vector de documentos
 * @param os Flujo de salida
 * @param vdoc Vector de documentos
 * @param reord Si no es NULL es reordenamiento para vdoc que debe
 * quedar en archivo
 **/
void escribeDocs(iostream &os, vector<Doc> &vdoc, 
		vector<int64_t> *reord = NULL);


/**
 * Lee vector de documentos
 * @param is Flujo de entrada
 * @return Vector de documentos 
 **/
vector<Doc> leeDocs(istream &is);


/**
 * Mezcla dos vectores de documentos.
 * @param docs1 Primer vector de documentos
 * @param docs2 Segundo vector de documentos por modificar
 *
 * @return array con renumeraci�n para el primer vector de documentos
 * para que coincida con la segunda.
 * Adem�s de requerirse agrega a docs2 documentos de docs1 que
 * le hicieran falta o pone las fechas m�s antiguas en caso
 * de coincidientes (para asegurar actualizaci�n si no hay sincronia).
 */
vector<int64_t> mezclaDocs(vector<Doc> &docs1, vector<Doc> &docs2);

#endif
