/** @file NodoTrieS.hpp
 *
 * Trie especial en RAM. 
 * Apropiado para mantener posiciones de palabras en textos
 * en espa�ol  con codificaci�n ISO-8859-1
 * Basado en http://www.pasosdejesus.org/vtamara/estinf2006-1/proy-s/index.html
 *
 * @package Mt77
 * @author Vladimir T�mara Pati�o. vtamara@pasosdejesus.org
 * Dominio p�blico. 2008. Sin garant�as
 * http://creativecommons.org/licenses/publicdomain/
 * @version   $Id: NodoTrieS.hpp,v 1.18 2011/03/29 23:07:26 vtamara Exp $
 */

#include <set>
#include <string>
#include <vector>
#include <stdint.h>

#if !defined(NodoTrieS_hpp)

#define NodoTrieS_hpp

using namespace std;

#include "Pos.hpp"

/**
 * Un nodo de un TrieS con apuntador a hermano menor e hijo mayor.
 *
 * Invariante: Arbol n-ario, hermanos ordenados lexicogr�ficamente
 * de menor a mayor.
 * En lista de hermanos no hay 2 con prefijo com�n (i.e 
 * todos comienzan por letra diferente)
 */
class NodoTrieS
{

        private:
                string cad;
                NodoTrieS *hermano_mayor; //< Lista de hijos
                NodoTrieS *hijo_menor; 	//< Lista de hijos
                set<Pos> cpos; //< Referencia a posiciones de esta palabra

                friend NodoTrieS *mezcla(NodoTrieS *a1, NodoTrieS *a2);
                friend uint32_t precalcula_escribe_actual(NodoTrieS *n);
                friend uint32_t precalcula_escribe_con_hermanos(NodoTrieS *n);
                friend uint32_t precalcula_escribe(NodoTrieS *n);
                friend void escribePlanoStream (NodoTrieS *n,
                                                iostream &os, 
						uint32_t desp /*= 0*/);
                friend class TrieSDiscoCasoPrueba;
                friend uint32_t escribeCopiaNodoRam(iostream &os, NodoTrieS *a,
                                                NodoTrieS **phijo,
                                                vector<int64_t>* renum);
                friend uint32_t escribeCopiaSubarbolRam(iostream &os, NodoTrieS *a,
                                                    int saltacad,
                                                    bool conHermanos,
                                                    vector<int64_t>* renum);
                friend uint32_t mezclaDiscoRam(istream &is1, NodoTrieS *a2,
                                           int saltacad,
                                           iostream &os, bool conHermanos1,
                                           bool conHermanos2,
                                           vector<int64_t> *renum1,
                                           vector<int64_t> *renum2);
                friend uint32_t escribeCopiaNodoRam(iostream &os, NodoTrieS *a,
                                                int saltacad,
                                                NodoTrieS **phijo,
                                                vector<int64_t>* renum);
        public:
                /** Constructora.
                 * Responsabilidad de liberar hijo_menor y hermano_mayor pasa a
                 * este nodo, esperando m�s eficiencia en mezclas. 
                * @param cad Cadena
                * @param hijo_menor Apuntador a Hijo menor
                * @param hermano_mayor Apuntador a hermano mayor
                * @param cpos conjunto de posiciones donde est� la palabra
                 **/
                NodoTrieS(string cad = "", NodoTrieS *hijo_menor=NULL,
                          NodoTrieS *hermano_mayor = NULL,
                          set<Pos> cpos = set<Pos>());

                /** Constructora que recibe una posici�n.
                 * Responsabilidad de liberar hijo_menor y hermano_mayor pasa a
                 * este nodo, esperando m�s eficiencia en mezclas. 
                 * Inicializa conjunto de posiciones con una posici�n i.e. p.
                * @param cad Cadena
                * @param hijo_menor Apuntador a Hijo menor
                * @param hermano_mayor Apuntador a hermano mayor
                * @param p posici�n inicial
                 **/
                NodoTrieS(string cad, NodoTrieS *hijo_menor,
                          NodoTrieS *hermano_mayor, Pos p);

                /** Destructora.
                 * Libera recursivamente hijo_menor y hermano_mayor 
                 */
                ~NodoTrieS();

                /**
                 * Retorna copia de posiciones en palabra para depuraci�n
                 */
                set<Pos> depuracpos()
                {
                        return cpos;
                }

                /** Busca la palabra pal. Retorna lista de posiciones en las que
                 * aparece.   
                * @param pal Palabra por buscar
                 * @return NULL en caso de que la palabra no este.
                 */
                set<Pos> busca(string pal);

                /** Inserta una ocurrencia mas de la palabra pal, reportandola en
                 * posicion p.  
                * @param pal Palabra por insertar
                * @param p Posici�n donde aparece 
                 * @return Nueva raiz.
                 * @exception Memoria si la memoria se agota al insertar. En ese
                 * caso se garantiza que el arbol queda en un estado consistente.
                 */
                void inserta(string pal, Pos p);

		/** 
		 * Inserta una palabra normalizandola antes si normaliza es true
		 * @param pal Palabra por insertar 
		 * @param numdoc Numero de documento en el que insertar�
		 * @param pini Posici�n inicial donde insertar�
		 * @param normaliza Indica si debe o no normalizar
		 */
		void insertaNormalizando(string pal, uint32_t numdoc, 
				uint32_t p, bool normalizaPal);

                /** Inserta m�s ocurrencias de la palabra pal, reportandolas en
                 * posiciones npos.  
                * @param pal Palabra por insertar
                * @param npos Posiciones donde aparece
                 * @return Nueva raiz.
                 * @exception Memoria si la memoria se agota al insertar. En ese
                 * caso se garantiza que el arbol queda en un estado consistente.
                 */
		void
		inserta(string pal, set<Pos> *npos);


                /**
                 * Escribe representacion de TrieS como 
                * �rbol en el formato de dotty.
                * @param os  Flujo donde escribir�
                * @param pref Prefijo para indentaci�n
                * @param primero Si es el primer nodo
                * @param mayor Si es el mayor de los hermanos del nivel
                 */
                void aDotty(ostream &os, string pref = "",
                            bool primero = true, bool mayor = true) throw(string);

                /**
                 * Con prop�sitos de depuraci�n, retorna cadena con 
                * �rbol en preorden.
                 */
                string preorden();

                /** Renumera documentos referenciados en posiciones de trieS de
                 * acuerdo a vector renum.   Una posici�n cuyo documento sea el
                 * n�mero p (>=1) pasar� a ser el n�mero renum[p-1] (>=1).
                * @param renum Vector para renumerar
                 */
                void renumeraDocs(vector<int64_t> renum);

                /**
                 * Divide la cadena c en palabras e inserta cada una con 
                * la etiqueta dada en el �rbol, referenciando el documento 
                * numdoc desde la posici�n inicial posini.
                 * @param c Cadena con palabras por insertar
                 * @param etiqueta Por agregar a cada palabra
                 * @param numdoc N�mero de documento del cual provienen
                 * @param pini Posici�n inicial en documento de la cadena c
                 */
                void insertaConEtiqueta(string c, string etiqueta,
                                                   uint32_t numdoc, 
						   uint32_t pini);

};


/** Construye un trieS a partir de un texto plano
 * @param na Archivo
 * @param ndoc N�mero de documento
 * @param t Donde se leera trieS
 * @param normalizaPal Si debe o no normalizar cada palabra leida
 **/
void leeTexto(const char *na, uint32_t ndoc, NodoTrieS &t,
              bool normalizaPal = true);


#endif
