/** @file Operaciones.hpp
 * Realiza operaciones en un �ndice.
 *
 * @package Mt77
 * @author Vladimir T�mara Pati�o. vtamara@pasosdeJesus.org
 * Dominio p�blico. 2009. Sin garant�as
 * http://creativecommons.org/licenses/publicdomain/
 * @version   $Id: Operaciones.hpp,v 1.7 2010/01/18 16:12:50 vtamara Exp $
 */

#if !defined(Operaciones_hpp)
#define Operaciones_hpp

using namespace std;

#include "RamDisco.hpp"

/**
 * Muestra palabras y frecuencias contenidas en un �ndice.
 * @param is Flujo de entrada
 * @param pre Prefijo para indentar
 */
void
muestraStream(std::istream &is, string pre); //throw(char *)

/**
 * Lista por salida est�ndar palabras y frecuencias contenidas en �ndice.
 * @param noma Nombre de archivo con �ndice
 * @param nrel Nombre de archivo con relaci�n  de documentos
 */
void listaPalabras(char *noma, char *nrel) throw(string);

/**
 * Elimina del indice nomind el documento nd y deja resultado en noma
 * @param noma Nombre del �ndice de salida
 * @param nomind Nombre del �ndice de entrada
 * @param nd N�mero de documento a eliminar de nomind
 */
void
eliminaDoc(char *noma, char *nomind, uint32_t nd) throw(string);


/**
 * De un prefijo convierte a sitio
 * @param pref Prefijo
 * @return sitio
 */
string prefijoASitio(const char *pref);


/** 
 * Determina el formato de un archivo
 * @param narch Nombre del archivo
 * @return Formato
 */
string determinaFormato(string narch);


/**
 * Mezcla en disco dos �ndices
 * @param indsal Nombre del �ndice de salida
 * @param ind1 Nombre del primer �ndice por mezclar
 * @param ind2 Nombre del segundo �ndice por mezclar
 * @param nd Posici�n dentro de ind1 a partir del cual incluir
 * los de ind2.  Por convenci�n 0 es al final.
 */
void
mezclaDosDisco(const char *indsal, const char *ind1, const char *ind2,
               uint32_t nd = 0) throw(string);

/**
 * Agrega un documento a un �ndice
 *
 * @param indsal Indice de salida
 * @param inden Indice de entrada
 * @param nom Nombre de documento por agregar
 * @param metainformacion decide si se agrega o no
 * @param pref Prefijo para URL en nombre de documento
 * @param nd N�mero de documento en medio del �ndice existente en el que se pondr� nuevo documento o 0 para agregar al final
 */
void
agregaDoc(const char *indsal, const char *inden, const char *nom,
          bool metainformacion, const char *pref, uint32_t nd);


/**
 * Extrae del indice ind, el subindice del documento nd y lo pone en el
 * indice salida
 * @param ind Indice de entrada
 * @param salida indice de salida
 * @param nd Numero de documento por extraer del indice de entrada
 */
void
subindice(const char *ind, const char *salida, uint32_t nd);


#endif
