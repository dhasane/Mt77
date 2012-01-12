/** @file comun.hpp
 * Datos comunes.
 *
 * @package Mt77
 * @author Vladimir T�mara Pati�o. vtamara@pasosdeJesus.org
 * Dominio p�blico. 2008. Sin garant�as
 * http://creativecommons.org/licenses/publicdomain/
 * @version   $Id: comun.hpp,v 1.11 2010/01/18 16:12:50 vtamara Exp $
 */


#if !defined(Comun_hpp)
#define Comun_hpp

#include <set>
#include <string>
#include <ostream>
#include <sstream>
#include <stdint.h>

#ifdef ASSERT
#undef ASSERT
#endif
#ifdef NDEBUG
#define ASSERT(x) ((void)0)
#warning NDEBUG activo compilando sin ASSERT
#else
#define ASSERT(x) \
  if (! (x)) \
  { \
    stringstream _sa; _sa.clear(); _sa.str(""); \
    _sa << __FILE__ << ":" << __LINE__ << "Fall� aserci�n " << #x << " \n"; \
    throw std::string(_sa.str()); \
  }
#endif

/** M�xima longitud de un URL --de documentaos indexables */
const uint32_t MAXLURL = 1024;

/** M�xima longitud de un condensado */
const uint32_t MAXLCONDENSADO = 64;

/** M�xima longitud de un hexadecimal.  Usado por lo menos en
 *  indice de documento en posici�n, posiciones dentro del �ndice. */
const uint32_t MAXLHEX = 8;

/** M�xima longitud de un 128b (n�mero en base 128).  Por usar en
 * �ndice de documento, posici�n, ``apuntadores'' al archivo 
 */
const int MAXL128B = 5;

/**
 * M�xima longitud de un n�mero en formato escogido para archivo 
 **/
const int MAXLNUMERO = MAXL128B;

/** M�xima longitud de un decimal. Empleado por lo menos para
 * indexar documentos referenciados por un �ndice. */
const int MAXLDEC = 10;

/** Tama�o m�ximo de una cadena indexable */
const uint32_t MAXCAD = 32;

using namespace std;

/** Marca en �ndice */
const string MARCAIND = "Mt77:�ndiceP5";


/** Marca en relaci�n de documentos */
const string MARCAREL = "Mt77:relaci�nP5";


/** Caracter que marca final de una cadena en archivo */
const char FINCADENA = '{';

/**
 * Verifica nombre de �ndice, y genera nombre de relaci�n de documentos
 * asociada
 * @param na Nombre de �ndice
 * @param nrel con espacio para MAXLURL caracteres, retorna nombre de rel.
 */
void verificaNombre(const char *na, char *nrel) throw(string);


/**
 * Formatea un conjunto a un flujo de salida
 * @param os Flujo de s�lida
 * @param c Conjunto
 * @return El mismo flujo de s�lida recibido pero tras env�ar una represntaci�n
 * plan del conjunto
 */
template <class T>
std::ostream &
operator<<(std::ostream &os, set<T> c)
{
        os <<"{";
        typename set<T>::iterator i;
        string sep = "";
        for (i = c.begin(); i != c.end(); i++) {
                os << sep << *i;
                sep = ", ";
        }
        os <<"}";
        return os;
}

/**
 * Retorna el prefijo com�n m�s largo de dos cadenas
 * @param a Primera cadena
 * @param b Segunda cadena
 **/
string prefijo_comun_mas_largo(string a, string b);

/**
 * Retorna cadena de error con posici�n de is
 * @param is Flujo de entrada
 * @param m Cadena con error 
 * @return Cadena con mensaje de error precedido de posici�n en is
 **/
std::string errorFormato(std::istream &is, string m);

/**
 * Lee una cadena
 * @param is flujo de entrada
 **/
string leeCad(istream &is) throw(string);

/**
 * Lee un n�mero hexadecimal 
 * @param is flujo de entrada
 **/
long leeHex(std::istream &is) throw(string);


/**
 * Escribe en os un entero como hexadecimal de 8 digitos.
 * @param os Flujo de salida
 * @param n N�mero por escribir como hexadecimla de 8 d�gitos
 **/
void escribeHex(std::ostream &os, uint32_t n);

/**
 * Lee un n�mero en base 128.
 * Cada digito es un caracter entre '0' (ASCII 48) y el de ASCII 175.
 * Con 5 d�gitos de estos puede representarse m�s de 4294967295 = 0xFFFFFFFF 
 * @param is flujo de entrada
 **/
long lee128b(std::istream &is) throw(string);


/**
 * Escribe en os un entero en base 128.
 * @see lee128b
 * @param os Flujo de salida
 * @param n N�mero por escribir en base 128
 **/
void escribe128b(std::ostream &os, uint32_t n);

/**
 * Convierte n�mero a cadena en base 128b
 * @see lee128b
 * @param n N�mero por retornar
 */
string n128b_c(uint32_t n);

/**
 * Convierte n�mero en base 128 a entero
 * @see lee128b
 * @param s Cadena con n�mro en base 128
 */
uint32_t c_n128b(string s);

/**
 * Retorna longitud de un n�mero en base 128
 * @param n n�mero
 *
 * @return longitud
 */
inline uint32_t
long128b(uint32_t n)
{
        return MAXL128B;
}


/**
 * Lee un n�mero en formato escogido para desplazamientos
 * @param is flujo de entrada
 **/
inline uint32_t
leeNDesp(std::istream &is) throw (std::string)
{
        return lee128b(is);
}


/**
 * Escribe un n�mero en el formato escogido para desplazamientos
 * @param os Flujo de salida
 * @param n N�mero por escribir 
 **/
inline void
escribeNDesp(std::ostream &os, uint32_t n)
{
        escribe128b(os, n);
}


/**
 * Retorna longitud del n�mero n al escribirlo con escribeNDesp
 */
inline uint32_t
longNDesp(uint32_t n)
{
        return MAXL128B;
}


/**
 * Normaliza caracter
 * @param c Caracter 
 * @return Cadena que corresponde (tipicamente may�scula o vac�o)
 */
string normalizaCaracter(char c);

/**
 * Normaliza cadena
 * @param s Cadena por normalizar
 * @return Cadena normalizada
 **/
string normaliza(string s);

/**
 * Convierte primer caracter de cadena u8 con codificaci�n UTF-8 al
 * caracter que le corresponde en codificaci�n latin1.
 * Inspirado en 
 * - utf8_decode de 
 * http://svn.apache.org/repos/asf/stdcxx/branches/4.1.3/util/charmap.cpp
 * - latin1_toUtf8 de expat
 *
 * @param u8 Cadena en UTF-8
 * @param latin1 Caracter de salida
 * @return Cantidad de bytes leidos de u8 para la conversi�n
 */
int car_utf8_a_latin1(const char *u8, char *latin1);

/**
 * Convierte cadena u8 con codificaci�n UTF-8 a latin 1 (ISO8859-1).
 *
 * @param u8 Cadena en UTF-8
 * @param len Longitud de u8
 * @return Cadena convertida
 * 
 */
string utf8_a_latin1(const char *u8, int len);

/**
 * Divide una cadena de acuerdo a un delimitador
 * @param delimitador subcadena que marca donde dividir
 * @param cad Cadena por dividir
 *
 * @return Vector de subcadenas 
 */
vector<string> estalla(const string &delimitador, const string &cad);


/**
 * Crea un directorio temporal y retorna su nombre.
 * Basado en pagina man de mktemp.
 * @return Ruta del directorio temporal
 */
string directorio_temp();


#endif
