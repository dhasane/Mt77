#!/bin/sh
# Pruebas de regresi�n a Mt77
# Dominio p�blico. 2009. vtamara@pasosdeJesus.org

#function x {

echo "�ndice vacio:"
rm -rf r0.indice; ../indexador r0.indice t.indice "http://r" "" > r0.out 2>&1
../buscador r0.indice LA 1 0 sincopiarecientes >> r0.out 2>&1
../operaindice lista r0.indice >> r0.out 2>&1
rm -rf rc0.indice; ../indexador rc0.indice t.indice "http://r" "" >> r0.out 2>&1
#echo "ram" >> r0.out 2>&1
#../operaindice mezclaram rm0.indice r0.indice rc0.indice >> r0.out 2>&1
#../operaindice lista rm0.indice >> r0.out 2>&1
../operaindice mezcladisco rd0.indice r0.indice rc0.indice >> r0.out 2>&1
../operaindice lista rd0.indice >> r0.out 2>&1

cmp r0.out esp/r0.out
if (test "$?" != "0") then {
	echo "** ERROR: r0 fall�";
} fi;

echo "Creaci�n de �ndices";
rm -f r1.indice; ../indexador r1.indice t.indice "http://r/" r1.txt 
rm -f verdad.indice; ../indexador verdad.indice t.indice "http://pasosdeJesus/" verdad.txt 

#function t {

echo "B�squeda sobre �ndice"
(../buscador r1.indice CONOCERE�S  1 0 sincopiarecientes;
../buscador r1.indice LA 1 0 sincopiarecientes ;
../buscador r1.indice VERDAD 1 0 sincopiarecientes ;
../buscador r1.indice Y  1 0 sincopiarecientes;
../buscador r1.indice VERDAD 1 0 sincopiarecientes ;
../buscador r1.indice OS 1 0 sincopiarecientes ;
../buscador r1.indice HAR� 1 0 sincopiarecientes ;
../buscador r1.indice LIBRES 1 0 sincopiarecientes ;
../buscador r1.indice INEXISTENTE 1 0 sincopiarecientes;
../operaindice lista r1.indice ) | grep -v "\"fecha\":" > r1.out 2>&1

cmp r1.out esp/r1.out
if (test "$?" != "0") then {
	echo "** ERROR: r1 fall�";
} fi;

echo "B�squeda de metainformaci�n"
(../buscador r1.indice sitio:r 1 0 sincopiarecientes;
../buscador r1.indice sitio:s 1 0 sincopiarecientes;
../buscador r1.indice tipo:texto 1 0 sincopiarecientes;
../buscador r1.indice tipo:xrlt 1 0 sincopiarecientes;
../buscador r1.indice titulo:r1 1 0 sincopiarecientes;
../buscador r1.indice titulo:s 1 0 sincopiarecientes;
../buscador r1.indice titulo:txt 1 0 sincopiarecientes ) | grep -v "fecha\":" > r1m.out 2>&1

cmp r1m.out esp/r1m.out
if (test "$?" != "0") then {
	echo "** ERROR: r1m fall�";
} fi;


echo "Caso vac�o";
(rm -f nse.indice; ../indexador nse.indice t.indice "http://r/" "nombre con espacio.txt" "nombre con e�e.txt";
../buscador nse.indice HOLA 1 0 sincopiarecientes;
../buscador nse.indice "" 1 0 sincopiarecientes;
../operaindice lista nse.indice ) | grep -v "fecha:\"" > nse.out

cmp nse.out esp/nse.out
if (test "$?" != "0") then {
	echo "** ERROR: nse fall�";
} fi;


echo "Creaci�n de otro �ndice";
rm -f r4.indice; ../indexador r4.indice t.indice "http://r/" r4.txt 


cmp r1.out esp/r1.out
if (test "$?" != "0") then {
	echo "** ERROR: r1 fall�";
} fi;


echo "Otro �ndice";
rm -f r2.indice; ../indexador r2.indice t.indice "http://r/" r2.txt 

echo "B�squeda sobre �ndice"

(../buscador r2.indice CONOCERE�S 1 0 sincopiarecientes ;
../buscador r2.indice CREA 1 0 sincopiarecientes ;
../buscador r2.indice UNIG�NITO 1 0 sincopiarecientes ;
../buscador r2.indice VIDA 1 0 sincopiarecientes ;
../buscador r2.indice ETERNA 1 0 sincopiarecientes ;
../buscador r2.indice QUE 1 0 sincopiarecientes ;
../buscador r2.indice HIJO 1 0 sincopiarecientes ;
../operaindice lista nse.indice) | grep -v "fecha\":" > r2.out 2>&1
cmp r2.out esp/r2.out
if (test "$?" != "0") then {
	echo "** ERROR: r2 fallo";
} fi;
echo "Mezcla"

../operaindice mezclaram rm.indice r1.indice r2.indice
(../buscador rm.indice VERDAD 1 0 sincopiarecientes ;
../buscador rm.indice HIJO 1 0 sincopiarecientes ;
../buscador rm.indice DIOS 1 0 sincopiarecientes ;
../buscador rm.indice Y 1 0 sincopiarecientes ) | grep -v "fecha\":" > rm.out 2>&1
cmp rm.out esp/rm.out
if (test "$?" != "0") then {
	echo "** ERROR: rm -f fallo";
} fi;


../operaindice mezclaram rm2.indice rm.indice r1.indice r2.indice
cmp rm.indice rm2.indice
if (test "$?" != "0") then {
	echo "** ERROR: rm2 y rm -f deber�an ser identicos";
} fi;

echo "Otra mezcla"

rm -f ro.indice; ../indexador ro.indice t.indice "http://r/" r1.txt r2.txt 

cmp ro.indice rm.indice
if (test "$?" != "0") then {
	echo "** ERROR: ro y rm deber�an ser identicos";
} fi;

echo "Comparando mezcla en memoria con mezcla en disco"
rm -f mateo.indice; ../indexador mateo.indice t.indice ./ mateo.txt
rm -f marcos.indice; ../indexador marcos.indice t.indice ./ marcos.txt
rm -f lucas.indice; ../indexador lucas.indice t.indice ./ lucas.txt
rm -f juan.indice; ../indexador juan.indice t.indice ./ juan.txt

../operaindice mezclaram mm.indice marcos.indice mateo.indice
../operaindice mezcladisco md.indice marcos.indice mateo.indice
cmp mm.indice md.indice
if (test "$?" != "0") then {
	echo "** ERROR: mm y md deber�an ser identicos";
} fi;

../operaindice mezclaram mm2.indice mm.indice lucas.indice
../operaindice mezcladisco md2.indice md.indice lucas.indice
cmp mm2.indice md2.indice
if (test "$?" != "0") then {
	echo "** ERROR: mm2 y md2 deber�an ser identicos";
} fi;

../operaindice mezclaram mm3.indice mm2.indice juan.indice
../operaindice mezcladisco md3.indice md2.indice juan.indice
cmp mm3.indice md3.indice
if (test "$?" != "0") then {
	echo "** ERROR: mm3 y md3 deber�an ser identicos";
} fi;

../operaindice mezclaram mmt.indice marcos.indice mateo.indice lucas.indice juan.indice
cmp mmt.indice md3.indice
if (test "$?" != "0") then {
	echo "** ERROR: mmt y md3 deber�an ser identicos";
} fi;

(../buscador md3.indice VERDAD 1 0 sincopiarecientes ;
../buscador md3.indice HIJO 1 0 sincopiarecientes ;
../buscador md3.indice DIOS 1 0 sincopiarecientes ;
../buscador md3.indice Y 1 0 sincopiarecientes ) | grep -v "fecha\":" > rm3.out 2>&1
cmp rm3.out esp/rm3.out
if (test "$?" != "0") then {
	echo "** ERROR: rm3 fallo";
} fi;

echo "B�squeda de varias palabras"
../buscador r1.indice "LA VERDAD" 1 0 sincopiarecientes | grep -v "fecha\":" > r5.out 2>&1;
../buscador r1.indice "VERDAD VERDAD" 1 0 sincopiarecientes | grep -v "fecha\":" >> r5.out 2>&1;
../buscador r1.indice "OS VERDAD" 1 0 sincopiarecientes | grep -v "fecha\":" >> r5.out 2>&1;
../buscador r1.indice "LIBRES OS VERDAD" 1 0 sincopiarecientes | grep -v "fecha\":" >> r5.out 2>&1;
../buscador r1.indice "CONOCERE�S LA VERDAD Y LA VERDAD OS HAR� LIBRES" 1 0 sincopiarecientes | grep -v "fecha\":" >> r5.out 2>&1;
../buscador r1.indice "OS VERDAD LIBRES" 1 0 sincopiarecientes | grep -v "fecha\":" >> r5.out 2>&1;
../buscador r1.indice "OS Y Y Y Y Y VERDAD LIBRES" 1 0 sincopiarecientes | grep -v "fecha\":" >> r5.out 2>&1;
../buscador r1.indice "FALSO VERDAD" 1 0 sincopiarecientes  | grep -v "fecha\":" >> r5.out 2>&1
cmp r5.out esp/r5.out
if (test "$?" != "0") then {
	echo "** ERROR: r5 fallo";
} fi;


echo "En XML"
rm -f rx.indice; ../indexador rx.indice t.indice http://h/ p2.xrlat
(../buscador rx.indice "organizacionresponsable:pasos" 1 0 sincopiarecientes;
../buscador rx.indice "organizacion:religiosa" 1 0 sincopiarecientes;
../buscador rx.indice "organizacion:noesta" 1 0 sincopiarecientes;
../buscador rx.indice "nombre:vi" 1 0 sincopiarecientes;
../buscador rx.indice "departamento:CAUCA" 1 0 sincopiarecientes;
../buscador rx.indice "iglesia:Cruzada" 1 0 sincopiarecientes;
../buscador rx.indice "sexo:Femenino" 1 0 sincopiarecientes;
../buscador rx.indice "noesta:noesta" 1 0 sincopiarecientes;
../buscador rx.indice "sexo:masculino" 1 0 sincopiarecientes) | grep -v "fecha\":" > rx.out 2>&1
cmp rx.out esp/rx.out
if (test "$?" != "0") then {
	echo "** ERROR: rx fallo";
} fi;

rm -f bdc-ene2009.indice; ../indexador bdc-ene2009.indice t.indice http://127.0.0.1:17443/ bdc-ene2009.xrlat
../operaindice lista bdc-ene2009.indice > bdc.out
cmp bdc.out esp/bdc.out
if (test "$?" != "0") then {
	echo "** ERROR: bdc fallo";
} fi;

echo "En ODT"
rm -f poema_ser_como_ninos.indice; ../indexador poema_ser_como_ninos.indice t.indice http://ejemplo.com/ poema_ser_como_ninos.odt
../operaindice lista poema_ser_como_ninos.indice > poema_ser_como_ninos.lista
cmp poema_ser_como_ninos.lista esp/poema_ser_como_ninos.lista
if (test "$?" != "0") then {
	echo "** ERROR: poema_ser_como_ninos.lista fallo";
} fi;

echo "En HTML"
rm -f html.indice; ../indexador html.indice t.indice http://ejemplo.com/ html.html
../operaindice lista html.indice > html.lista
cmp html.lista esp/html.lista
if (test "$?" != "0") then {
	echo "** ERROR: html.lista fallo";
} fi;

echo "Elimina un documento"

rm -f ro.indice; ../indexador ro.indice t.indice "http://r/" r1.txt r2.txt 
../buscador ro.indice "CONOCERE�S" 1 0 sincopiarecientes | grep -v "fecha\":" > ro2.out 2>&1;
../operaindice eliminadoc ro2.indice ro.indice 1 
../buscador ro2.indice "CONOCERE�S" 1 0 sincopiarecientes | grep -v "fecha\":" >> ro2.out 
../operaindice lista ro2.indice >> ro2.out 
cmp ro2.out esp/ro2.out
if (test "$?" != "0") then {
	echo "** ERROR: ro2 fallo";
} fi;


echo "Mezcla indices no necesariamente al final"
rm -f ra1.indice; ../indexador ra1.indice t.indice "http://r/" r1.txt
rm -f ra2.indice; ../indexador ra2.indice t.indice "http://r/" r2.txt
../operaindice mezcladisco ra3.indice ra1.indice ra2.indice 1
../operaindice mezcladisco ra4.indice ra1.indice ra2.indice 2
../operaindice grafo ra3.indice > ra.out #| awk '/.*/ { n = n + 1; if (n>2) { print $0; }}' > /tmp/z1
../operaindice grafo ra4.indice >> ra.out

rm -f ra5.indice; ../indexador ra5.indice t.indice "http://pasosdeJesus/" verdad.txt 
rm -f ra6.indice; ../operaindice mezcladisco ra6.indice ra4.indice ra5.indice 1
../operaindice grafo ra6.indice >> ra.out
../operaindice mezcladisco ra7.indice ra4.indice ra5.indice 2
../operaindice grafo ra7.indice >> ra.out
../operaindice mezcladisco ra8.indice ra4.indice ra5.indice 3
../operaindice grafo ra8.indice >> ra.out

cmp ra.out esp/ra.out
if (test "$?" != "0") then {
	echo "** ERROR: ra fallo";
} fi;

echo "Agrega documentos a un �ndice"
cp r1.indice rd1.indice; cp r1.relacion rd1.relacion
../indexador rd1.indice t.indice "http://r/" r2.txt
../operaindice grafo rd1.indice > rd.out #| awk '/.*/ { n = n + 1; if (n>2) { print $0; }}' > /tmp/z1

../indexador rd1.indice t.indice "http://r/" verdad.txt poema_ser_como_ninos.odt
../operaindice grafo rd1.indice >> rd.out #| awk '/.*/ { n = n + 1; if (n>2) { print $0; }}' > /tmp/z1

cmp rd.out esp/rd.out
if (test "$?" != "0") then {
	echo "** ERROR: rd fallo";
} fi;


echo "Comparando mezcla en disco con agregar documento en disco"

rm -f marcos.indice; ../indexador marcos.indice t.indice ./ marcos.txt
time (rm -f juan.indice; ../indexador juan.indice t.indice ./ juan.txt; ../operaindice mezcladisco mmj.indice marcos.indice juan.indice)
time (cp marcos.indice mmja.indice; cp marcos.relacion mmja.relacion; ../indexador mmja.indice t.indice "./" juan.txt)
cmp mmj.indice mmja.indice
if (test "$?" != "0") then {
	echo "** ERROR: mmj y mmja deber�an ser identicos";
} fi;

time (rm -f mateo.indice; ../indexador mateo.indice t.indice ./ mateo.txt; ../operaindice mezcladisco mmj.indice juan.indice mateo.indice; rm -f marcos.indice; ../indexador marcos.indice t.indice ./ marcos.txt; ../operaindice mezcladisco mmj2.indice mmj.indice marcos.indice; rm -f lucas.indice; ../indexador lucas.indice t.indice ./ lucas.txt; ../operaindice mezcladisco mmj.indice mmj2.indice lucas.indice;)
time (cp juan.indice mmja.indice; cp juan.relacion mmja.relacion; ../indexador mmja.indice t.indice "./" mateo.txt marcos.txt lucas.txt)
cmp mmj.indice mmja.indice
if (test "$?" != "0") then {
	echo "** ERROR: mmj y mmja deber�an ser identicos";
} fi;


echo "Comparando indexado en grupos"
rm -f -f t.indice 
rm -f rg1.indice; MT77MAXG=120 ../indexador rg1.indice t.indice "http://r/" r1.txt r2.txt 
if (test ! -f t.indice) then {
	echo "No se uso temporal t.indice";
} fi;
rm -f rgt1.indice; ../indexador rgt1.indice t.indice "http://r/" r1.txt r2.txt 
cmp rg1.indice rgt1.indice
if (test "$?" != "0") then {
	echo "** ERROR: rg1 y rgt1 deber�an ser identicos";
} fi;


echo "B�squeda de cadenas"
(../buscador r1.indice "CONOCERE�S"  1 0 sincopiarecientes;
../buscador r1.indice "CONOCEREIS LA VERDAD" 1 0 sincopiarecientes ;
../buscador r1.indice "\"Y LA VERDAD OS HAR� LIBRES\"" 1 0 sincopiarecientes
../buscador md3.indice "HIJO DE DIOS" 1 0 sincopiarecientes
../buscador md3.indice '"HIJO DE DIOS"' 1 0 sincopiarecientes
) | grep -v "fecha\":" > rc1.out 2>&1

cmp rc1.out esp/rc1.out
if (test "$?" != "0") then {
	echo "** ERROR: rc1 fall�";
} fi;

echo "En PDF"
rm -f pdf.indice; ../indexador pdf.indice t.indice http://ejemplo.com/ OpenHymnalChristmas2009.pdf
../operaindice lista pdf.indice > pdf.lista
cmp pdf.lista esp/pdf.lista
if (test "$?" != "0") then {
	echo "** ERROR: pdf.lista fallo";
} fi;

#}

echo "Extrae sub�ndice"
../operaindice subindice rsub.indice r1.indice 1
../operaindice lista rsub.indice > rsub.lista
cmp rsub.lista esp/rsub.lista
if (test "$?" != "0") then {
	echo "** ERROR: rsub.lista fallo";
} fi;

../operaindice subindice rsubm.indice mmj.indice 1 # Saca Mateo
cmp rsubm.indice juan.indice
if (test "$?" != "0") then {
	echo "** ERROR: rsubm.indice y mateo.indice deber�a ser iguales";
} fi;



