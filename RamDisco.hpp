/**
 *@file RamDisco.hpp
 * Operaciones en RAM y Disco
 *
 * @package Mt77
 * @author Vladimir T�mara Pati�o. vtamara@pasosdeJesus.org
 * Dominio p�blico. 2009.  Sin garant�as
 * http://creativecommons.org/licenses/publicdomain/
 * @version   $Id: RamDisco.hpp,v 1.11 2010/01/18 16:12:50 vtamara Exp $
 */

#if !defined(RamDisco_hpp)

#define RamDisco_hpp


#include <vector>
#include "comun.hpp"
#include "Pos.hpp"
#include "Doc.hpp"
#include "NodoTrieS.hpp"
#include "TrieSDisco.hpp"
#include <stdint.h>


using namespace std;

/**
 * Calcula tama�o en bytes requerido para escribir nodo y hermanos
 * sin descendientes con funci�n escribe 
 */
uint32_t
precalcula_escribe_con_hermanos(NodoTrieS *n);

/**
 * Calcula cuantos bytes requerir�a el procedimiento escribe
 * para representar el nodo, sus hermanos y descendientes
 */
uint32_t
precalcula_escribe(NodoTrieS *n);


/**
 * Escribe en formato plano en un stream
 * Primero se escribe mayor con hermanos en una cadena:
 * MENOR nhermano_1 nhijo_1 {p1_1..p1_n} SIG {p2_1..p2_m} nhermano_2 nhijo_2... MAYOR 00000 nhijo_k {pk_1..pk_s}\n
 * Despu�s hijos del menor al mayor.
 **/
void
escribePlanoStream(NodoTrieS *n, std::ostream &os, uint32_t desp = 0);


/** Lee un trieS de un stream donde est� almacenado en formato
 * extra-simple.
 * @param is Flujo de entrada
 * @return trieS que construye
 */
NodoTrieS *
leePlanoStream(std::istream &is) throw(string);

/**
 * Escribe en formato plano en un archivo
 * @param t TrieS por escribir
 * @param docs Documentos referenciados en t
 * @param na nombre del archivo por generar con �ndice
 * @param nrel Nombre del archivo por generar con relaci�n de documentos
 */
void
escribePlano(NodoTrieS &t, vector<Doc> &docs, const char *na, const char *nrel);

/** Lee un trieS de un archivo de nombre na donde est� almacenado.
 * Retorna vector de documentos indexados en idocs.
 * @param na Nombre del archivo con �ndice
 * @param nrel Nombre del archivo con relaci�n de documentos
 * @param docs Retorna en este relaci�n de documentos indexados leido de nrel
 * @return TrieS leido de na
 */
NodoTrieS *
leePlano(char *na, char *nrel, vector<Doc> &docs);


/** Elimina un documento de un �ndice.
 * Tanto en �ndice como en relaci�n de documentos.
 *
 * @param na Nombre del �ndice
 * @param nrel Nombre de la relaci�n
 * @param nd N�mero de documento por eliminar (>=1)
 *
 * @return Cantidad de documentos que quedan indexados
uint32_t
eliminaUnDoc(char *na, char *nrel, uint64_t nd);
 */
/**
 * Renumera �ltimo documento indexado y los que le siguen.
 *
 * @param na Nombre del �ndice
 * @param nrel Nombre de la relaci�n
 * @param nd Nuevo �ndice para el �ltimo documento indexado.
 *
 * @return Cantidad de documentos que quedan indexados
uint32_t
renumeraUltimoDoc(char *na, char *nrel, uint64_t nd);
 */

/**
 * Mezcla is1 con a2 y deja resultado en os.
 * @param is1 1er archivo de entrada, su cursor se espera sobre cadena del 
 * 	hermano menor
 * @param a2 2do trieS de entrada
 * @param saltacad Cuanto de la cadena de a2 debe saltarse
 * @param os salida, su cursor se espera al final --all� escribir� mezcla.
 * @param conHermanos1 procesar hermanos de is1
 * @param conHermanos2 procesar hermanos de a2
 * @param renum1 Renumeraci�n a documentos de is1
 * @param renum2 Renumeraci�n a documentos de a2
 *
 * Es un algoritmo similar al de escribeCopiaSubarbol:
 * 1. Escribe todos los hermanos del menor al mayor.  Para esto
 * 	recorre los hermanos de is1 y a2.
 * 2. Escribe todos los sub�rboles del menor al mayor. Para esto
 * 	recorre los sub�rboles necesarios  de is1 y a2
 */
uint32_t
mezclaDiscoRam(istream &is1, NodoTrieS *a2, int saltacad, iostream &os,
               bool conHermanos1, bool conHermanos2,
               vector<int64_t> *renum1, vector<int64_t> *renum2);


/**
 * Extrae sub�ndice correspondiente a un documento nd del �ndice en
 * disco is y lo agrega al �ndice en RAM t
 * @param is Indice en disco de entrada
 * @param t Indice en ram donde se agrega 
 * @param nd N�mero de documento por extraer de is
 * @param pcad Prefijo (en la primera llamada no recursiva debe ser "")
 */
void
subindiceDiscoaRAM(std::istream &is, NodoTrieS *t, uint32_t nd, 
		string pcad = "") 
        throw(string);

#endif
