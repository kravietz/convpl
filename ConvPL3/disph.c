/*
    ConvPL by kravietZ

    DispH()     tekst pomocy
    DispL()     licencja uzytkownika
    DispS()     lista zaimplementowanych standardow

    tekst pomocy oraz licencja sa wyswietlane na stdout, aby ulatwic
    skierowanie ich do pliku; pozostale napisy wyswietlane sa na
    stderr
*/

#include <stdio.h>
#include "polish.h"

#ifndef __GNUC__
#include "stdafx.h"
#endif

extern short int ver_hi,ver_lo;

void DispH(void) {    /* help */
    fprintf(stdout,"Skladnia: cpl <nn>[opcja] [<wejscie.txt>] [<wyjscie.txt>]\
    \nCyfry <nn> okreslaja standard zrodlowy i docelowy. Dostepne standardy:\
    \n  0: bez polskich liter (ASCII,CP473) a: Microvex\
    \n  1: Mazovia                          b: Amiga PL\
    \n  2: FidoMazovia                      c: CP/J (Elwro 800 Junior)\
    \n  3: IBM-Latin/2 (CP852)              d: Amiga FAT\
    \n  4: ISO-Latin/2 (ISO-8859/2)         e: Windows 3.0 (CP1250)\
    \n  5: DHN                              f: Amiga XJP\
    \n  6: CSK                              g: Ventura\
    \n  7: Cyfromat (IINTE-ISIS)            h: Macintosh\
    \n  8: IEA                              i: TeX PL\
    \n  9: LOGIC                            j: Corel 2.0"
#ifndef CGI
"    \nSkroty <nn>: l: Mazovia->IBM Latin2   m: IBM Latin2->Mazovia\
    \n             x: Mazovia->ASCII        y: IBM Latin2->ASCII\
    \n             z: Fido-Mazovia->Mazovia\
    \nOpcje DOS/Unix/Amiga (zakonczenia linii):\
    \n  -: -> Unix, Amiga   (konwersja CR+LF --> NL)\
    \n  =: -> DOS           (konwersja NL --> CR+LF)\
    \nInne: -S, --standardy: tabelka standardow\
    \n      -L,  --licencja: licencja programu"
#else
"    \nProgram jest teraz skompilowany jako CGI.\
    \nContent-Type: T: text/plain  H: text/html\
    \nPrzyklad uzycia: cpl 41Tplik.txt = ISO LAtin -> Mazovia, text/plain"
#endif
"    \nSzczegolowy opis programu w dokumentacji (cpl.txt). <ConvPL v%u.%u>\
    \n",ver_hi,ver_lo);
};

void DispL(void) { /* licencja */
fprintf(stdout,"\n\
ConvPL i QueryPL sa programami freeware. Autor zachowuje pelnie praw autorskich\n\
do obu programow. Ich uzywanie jest darmowe tylko w przypadku wykorzystania\n\
przez osoby prywatne lub w instytucjach edukacyjnych. W innych przypadkach\n\
nalezy skontaktowac sie z autorem programu w celu ustalenia warunkow licencji.\n\
Program mozna bez przeszkod rozprowadzac ale pod warunkiem ze w sklad pakietu\n\
wchodza w niezmienionej postaci: pliki wykonywalne, kod zrodlowy\n\
oraz dokumentacja.\n\
Zabronione jest pobieranie oplat za udostepnianie tego programu, za wyjatkiem\n\
niewielkich oplat na wyrownania kosztow dystrybucji.\n\
AUTOR NIE DAJE ZADNEJ GWARANCJI DZIALANIA I NIE PONOSI ODPOWIEDZIALNOSCI\n\
ZA EWENTUALNE USZKODZENIE LUB UTRATE DANYCH POWSTALA, POSREDNIO LUB\n\
BEZPOSREDNIO, W WYNIKU DZIALANIA TEGO PROGRAMU. Niezaleznie od tego, autor\n\
oczywiscie doklada staran by program takich rzeczy nie robil.\n\
\n\
Pawel Krawczyk <kravietz@pipeta.chemia.pk.edu.pk> <2:486/19.19@fidonet>\
\n"); };

void DispS(void) { /* standardy */
    fprintf(stdout,"\
                           ACELNOSZZacelnoszz\n\
                           ------------------\n\
AmigaPL                  : %s\n\
ASCII (CP473)            : %s\n\
Corel 2.0                : %s\n\
CP/J (Elwro)             : %s\n\
CSK                      : %s\n\
Cyfromat                 : %s\n\
DHN                      : %s\n\
FAT (Amiga)              : %s\n\
FidoMazovia              : %s\n\
IEA                      : %s\n\
IBM-Latin/2 (CP852)      : %s\n\
ISO-Latin/2 (ISO-8859/2) : %s\n\
Logic                    : %s\n\
Macintosh                : %s\n\
Mazovia                  : %s\n\
Microvex                 : %s\n\
TeX PL                   : %s\n\
Ventura                  : %s\n\
Windows-EE (CP1250)      : %s\n\
XJP (Amiga)              : %s\n\
",p_Ami,p_Asc,p_Cor,p_CPJ,p_CSK,p_Cyf,p_DHN,p_FAT,p_FMaz,p_IEA,p_IBML,
p_ISOL,p_Log,p_Mac,p_Maz,p_Mic,p_TeX,p_Ven,p_Win3,p_XJP);
}
