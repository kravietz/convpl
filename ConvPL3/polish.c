/*
        polish.c - definitions of Polish national characters

                               v4.3.20
                            public domain

                         polish.c by kravietZ

        Uwaga: przy dodawaniu nowych standardow nalezy pamietac
        nie  tylko o definicji tablicy  ale tez odpowiadajacego
        jej wskaznika i uzupelnieniu polish.h.

        Pliki polish.h i polish.c sa wlasnoscia publiczna (public domain)
        i moga byc uzywane w programach wszelkich rodzajow (rowniez
        komercyjnych).

        1) Tablice zawieraja kody dziesietne polskich znakow w nastepujacej
        kolejnosci:

             A, C' E, L- N' O' S' Z' Z. a, c' e, l- n' o' s' z' z.

        2) Ostatnia czesc numeru wersji polish.h okresla ilosc zdefiniowanych
        standardow. Pierwsza i druga sa wlasciwym numerem wersji - odpowiednio
        major i minor.

        3) Jako standard zdefiniowany jest rowniez brak polskich liter (ASCII).

        4) Definicje sa ulozone alfabetycznie.

        Autor:   Pawel Krawczyk <kravietz@pipeta.chemia.pk.edu.pl>
                                <2:486/19.19@fidonet>
        Aktualna wersja:
        ftp://pipeta.chemia.pk.edu.pl/pub/convpl/

*/

#ifndef __GNUC__
#include "stdafx.h"
#endif

unsigned char BezPolsk[]={ /* polskie znaki zastapione przez odpowiadajace znaki ASCII */
 65, 67, 69, 76, 78, 79, 83, 90, 90, 97, 99,101,108,110,111,115,122,122,0 };

unsigned char AmigaPL[]={ /* Amiga PL */
194,202,203,206,207,211,212,218,219,226,234,235,238,239,243,244,250,251,0 };

unsigned char Corel[]={ /* Corel 2.0 */
194,199,202,206,209,211,212,218,219,226,231,234,238,241,243,244,250,251,0 };

unsigned char CPJ[]={ /* standard systemu CP/J z komputera Elwro 800 Junior */
193,195,197,204,206,207,211,218,217,225,227,229,236,238,239,243,250,248,0 };

unsigned char CSK[]={ /* st. f-my CSK */
128,129,130,131,132,133,134,136,135,160,161,162,163,164,165,166,168,167,0 };

unsigned char Cyfromat[]={ /* st. f-my Cyfromat */
128,129,130,131,132,133,134,136,135,144,145,146,147,148,149,150,152,151,0 };

unsigned char DHN[]={ /* DHN (MS-DOS, ChiWriter-PL) */
128,129,130,131,132,133,134,136,135,137,138,139,140,141,142,143,145,144,0 };

unsigned char Amiga_FAT[]={ /* odkryty przez Edwina Wierszelisa w dyskowym magazynie FAT */
192,193,194,195,196,197,198,200,199,230,231,234,238,241,243,245,251,254,0 };

unsigned char FidoMazovia[]={ /* Mazovia z c' (141) zastapionym przez c-cedilla (135) */
143,149,144,156,165,163,152,160,161,134,135,145,146,164,162,158,166,167,0 };

unsigned char IEA[]={ /* st. Instytutu Energii Atomowej w Swierku */
143,128,144,156,165,153,235,157,146,160,155,130,159,164,162,135,168,145,0 };

unsigned char IBM_Latin2[]={ /* IBM Latin-2, CP852 (MS-DOS) */
164,143,168,157,227,224,151,141,189,165,134,169,136,228,162,152,171,190,0 };

unsigned char ISO_Latin[]={ /* ISO Latin-2, ISO 8859-2 */
161,198,202,163,209,211,166,172,175,177,230,234,179,241,243,182,188,191,0 };

unsigned char Logic[]={ /* st. f-my (?) Logic */
128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,0 };

unsigned char Macintosh[]={
132,140,162,252,193,238,229,143,251,136,141,171,184,196,151,230,144,253,0 };

unsigned char Mazovia[]={ /* Mazovia (MS-DOS) */
143,149,144,156,165,163,152,160,161,134,141,145,146,164,162,158,166,167,0 };

unsigned char Microvex[]={ /* st. f-my Microvex */
143,128,144,156,165,147,152,157,146,160,155,130,159,164,162,135,168,145,0 };

unsigned char TeXPL[]={
129,130,134,138,139,211,145,153,155,161,162,166,170,171,243,177,185,187,0 };

unsigned char Ventura[]={ /* Ventura */
151,153,165,166,146,143,142,144,128,150,148,164,167,145,162,132,130,135,0 };

unsigned char Windows30[]={ /* zalecany dla Windows 3.0 EE (Eastern Europe) */
165,198,202,163,209,211,140,143,175,185,230,234,179,241,243,156,159,191,0 };

unsigned char XJP[]={ /* XJP (Amiga) */
198,199,202,206,209,211,213,219,222,230,231,234,238,241,243,245,251,254,0 };

unsigned char *p_Asc=BezPolsk; /* ASCii */
unsigned char *p_Ami=AmigaPL;
unsigned char *p_Cor=Corel; /* Corel 2.0 */
unsigned char *p_CPJ=CPJ;
unsigned char *p_CSK=CSK;
unsigned char *p_Cyf=Cyfromat;
unsigned char *p_DHN=DHN;
unsigned char *p_FAT=Amiga_FAT;
unsigned char *p_FMaz=FidoMazovia;
unsigned char *p_IEA=IEA;
unsigned char *p_IBML=IBM_Latin2; /* IBM Latin2, CP852 */
unsigned char *p_ISOL=ISO_Latin; /* ISO Latin2 */
unsigned char *p_Log=Logic;
unsigned char *p_Mac=Macintosh;
unsigned char *p_Maz=Mazovia;
unsigned char *p_Mic=Microvex;
unsigned char *p_TeX=TeXPL;
unsigned char *p_Ven=Ventura;
unsigned char *p_Win3=Windows30;
unsigned char *p_XJP=XJP;

/* end polish.c */
