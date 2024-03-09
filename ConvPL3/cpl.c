/*
                               ConvPL by kravietZ

          Uniwersalny konwerter standardow polskich znakow, freeware.

          Kontakt: Pawel Krawczyk http://ipsec.pl

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#ifndef __GNUC__
#include <share.h>
#include "stdafx.h"
# ifndef read
# define read _read
# endif
# ifndef close
# define close _close
# endif
# ifndef write
# define write _write
# endif
#endif /* not __GNUC__ */

#ifdef __GNUC__
#include <sys/file.h>
#include <sys/stat.h>
#endif

#ifndef O_BINARY    /* w gcc tego ni ma */
#define O_BINARY 0
#endif

#ifdef CGI          /* w CGI nie ma takich glupot */
#ifndef NO_LINE_CNT
#define NO_LINE_CNT
#endif
#endif

#include "polish.h"
#include "disph.h"
#define TEMP_FILE "tempxx.cpl"
#define TO_CRLF 1
#define TO_LF 2
#define buf_size 20*1024

typedef unsigned char ubyte;

static char ibuf[buf_size], obuf[buf_size];
static int ibuf_ptr = 0, obuf_ptr = 0, ibuf_lim = 0;
static int f_in=0,f_out=1;
#ifndef CGI
static int opt_mode=0;
#else
static int opt_mode=TO_LF;
#endif

const int ver_hi=2;
const int ver_lo=3;

#ifdef CGI
char *cont_type="text/content\0";
#endif


int indexx(ubyte ch, ubyte *ctab) /* czesto uzywana funkcja => inline */
/*
    zwraca indeks znaku ch w stringu okreslonym przez wskaznik ctab
    lub -1 jesli nie znajdzie znaku; indeksy zaczynaja sie od 0;
*/
{ int poss=0;
while((ch != *(ctab+poss) && (*(ctab+poss) != '\0'))) poss++;
if(*(ctab+poss) == '\0') return(-1);
 else
return(poss);
}; /* postab */

ubyte getxx (void)
{ int i;
  if (ibuf_ptr >= ibuf_lim) {               /* odebrane wszystkie? */
    ibuf_lim = read(f_in, ibuf, buf_size);  /* czytaj z pliku */
    if (ibuf_lim == 0) return -1;           /* nie ma wi‘cej w pliku */
    ibuf_ptr = 0;                           /* inicjuj wska¦nik znak¢w */
  }
  return ibuf[ibuf_ptr++];                  /* daj znak, zwi‘ksz wska¦nik */
}

void putxx (ubyte ch)
{
  if (obuf_ptr >= buf_size) {                /* bufor pe’ny? */
#ifndef CGI
    write(f_out, obuf, obuf_ptr);           /* zapisz bufor do pliku */
#else
    fwrite(obuf,obuf_ptr,1,stdout);
#endif
    obuf_ptr = 0;                           /* inicjuj wska¦nik znak¢w */
  }
  obuf[obuf_ptr++] = ch;                    /* znak do bufora, zwi‘ksz wsk. */
}

int ConvFile(char *cf_fname,char *cf_fnameo,char st1,char st2)
/*  
    czyta z nazwy cf_fname
    zapisuje do nazwy cf_fnameo
    st1 = std zrodlowy,
    st2 = docelowy
    parametr z zewnatrz: opt_mode (konwersja koncow linii)
*/
{
    ubyte *in_tab, *out_tab;
    int ps1;
    char ch1;
    long flen;

#ifndef NO_LINE_CNT
    long int n_line=0;  /* numer linii */
#endif

switch(st1)     /* najpierw kontrola poprawnosci standardow */
    {
/*  drobny trick umozliwiajacy przekodowanie u*x <-> MSDOS bez
    zmiany standardu polskich liter; szczegoly w cpl.txt */

    case '0': in_tab=p_Asc; st2='0'; break;
	case '1': in_tab=p_Maz; break;
	case '2': in_tab=p_FMaz; break;
	case '3': in_tab=p_IBML; break;
	case '4': in_tab=p_ISOL; break;
	case '5': in_tab=p_DHN; break;
	case '6': in_tab=p_CSK; break;
	case '7': in_tab=p_Cyf; break;
	case '8': in_tab=p_IEA; break;
	case '9': in_tab=p_Log; break;
	case 'a': in_tab=p_Mic; break;
	case 'b': in_tab=p_Ami; break;
	case 'c': in_tab=p_CPJ; break;
	case 'd': in_tab=p_FAT; break;
	case 'e': in_tab=p_Win3; break;
	case 'f': in_tab=p_XJP; break;
	case 'g': in_tab=p_Ven; break;
	case 'h': in_tab=p_Mac; break;
	case 'i': in_tab=p_TeX; break;
	case 'j': in_tab=p_Cor; break;
    default: fprintf(stderr,"\7\b\b\b\b\bnieznany standard wejsciowy \"%c\".\n",st1); return(255);
    } /* switch st1 */

switch(st2)
    {
    case '0': out_tab=p_Asc; break;
    case '1': out_tab=p_Maz; break;
    case '2': out_tab=p_FMaz; break;
    case '3': out_tab=p_IBML; break;
    case '4': out_tab=p_ISOL; break;
    case '5': out_tab=p_DHN; break;
    case '6': out_tab=p_CSK; break;
    case '7': out_tab=p_Cyf; break;
    case '8': out_tab=p_IEA; break;
    case '9': out_tab=p_Log; break;
    case 'a': out_tab=p_Mic; break;
    case 'b': out_tab=p_Ami; break;
    case 'c': out_tab=p_CPJ; break;
    case 'd': out_tab=p_FAT; break;
    case 'e': out_tab=p_Win3; break;
    case 'f': out_tab=p_XJP; break;
    case 'g': out_tab=p_Ven; break;
    case 'h': out_tab=p_Mac; break;
    case 'i': out_tab=p_TeX; break;
    case 'j': out_tab=p_Cor; break;
    default: fprintf(stderr,"\7\b\b\b\b\bnieznany standard wyjsciowy \"%c\".\n",st2); return(255);
    } /* switch st2 */

#ifndef CGI
    fprintf(stderr,"\n%s:      ",cf_fname);
#endif

if(!strcmp(cf_fname,"stdin")) f_in=0;
    else f_in=open(cf_fname,O_RDONLY|O_BINARY);

    if(f_in != -1)
    {

if(!strcmp(cf_fnameo,"stdout")) f_out=1;
    else f_out=open(cf_fnameo,O_CREAT|O_TRUNC|O_RDWR|
                              O_BINARY
#ifndef __MSDOS__
				, 0644
#endif
			      );

    if(f_out != -1)
	{

#ifdef CGI
    fprintf(stdout,"Content-Type: %s\n\n",cont_type);
#endif

while((ch1=getxx()) != -1)
    {   /* opt_mode = 0 jesli nie crlf, 1,2 jesli konw. crlf */

    switch(opt_mode) {

case TO_CRLF: { if(ch1==10) { putxx(13); putxx(10);

      #ifndef NO_LINE_CNT
    n_line++; fprintf(stderr,"\b\b\b\b\b%-5u",n_line);
	  #endif

	 } else { if( (ps1=indexx(ch1,in_tab)) != -1 ) putxx(*(out_tab+ps1)); else putxx(ch1); }; break; }

case TO_LF: { if(ch1==13) {

	  #ifndef NO_LINE_CNT
        n_line++; fprintf(stderr,"\b\b\b\b\b%-5u",n_line);
	  #endif

	   break; } else { if( (ps1=indexx(ch1,in_tab)) != -1 ) putxx(*(out_tab+ps1)); else putxx(ch1); }; break; }

default: { if( (ps1=indexx(ch1,in_tab)) != -1 ) putxx(*(out_tab+ps1)); else putxx(ch1);

	  #ifndef NO_LINE_CNT
        n_line++; fprintf(stderr,"\b\b\b\b\b%-5u",n_line);
	  #endif

	  break; }
    } /* switch */
}; /* while */

/* zrzucamy bufor do pliku */

    if (obuf_ptr < buf_size) {
#ifndef CGI
    write(f_out, obuf, obuf_ptr);           /* zapisz bufor do pliku */
#else
    fwrite(obuf,obuf_ptr,1,stdout);
#endif
        }

#ifndef CGI
       close(f_out);
#endif
     } /* open(f_out) */
     else { perror(cf_fnameo); exit(1); }

       close(f_in);

#ifndef CGI
       fprintf(stderr,"ok.\n");
#endif

     } /* open(f_in) */
else { perror(""); exit(1); }

return(0);

} /* convfile */

/*  ********************************** MAIN **********************/


int main(argc, argv)
int argc;
char **argv;

{

char swt[4];
char *p_swt=swt;
char st_in,st_out;
#ifdef CGI
 int i;
 char fnam1[]="filename.ext ";
#endif

#ifndef CGI /* w CGI nie ma skrotow itp. */
    char valid1[]="0123456789abcdefghijlmxyzSL\0";
    char valid2[]="0123456789abcdefghij-=\0";
#else
    char valid1[]="0123456789abcdefghij\0";
    char valid2[]="0123456789abcdefghij\0";
#endif

#ifndef CGI
fprintf(stderr,"\n[ConvPL] by kravietZ, v%u.%02u konwerter standardow polskich \
liter. Freeware.\n",ver_hi,ver_lo);
#endif

if(argc>1)
{

#ifndef CGI
/* sprawdz rozne mniej lub bardziej standardowe opcje */
if(!strcmp(argv[1],"-?") || !strcmp(argv[1],"--help") ||
   !strcmp(argv[1],"-h") || !strcmp(argv[1],"/?")) { DispH(); exit(1); }

if(!strcmp(argv[1],"-V") || strstr(argv[1],"--ver"))
    { fprintf(stdout,"%u.%u",ver_hi,ver_lo); exit(0); }

if(!strcmp(argv[1],"-S") || strstr(argv[1],"--stand"))
     { DispS(); exit(0); }

if(!strcmp(argv[1],"-L") || strstr(argv[1],"--lic"))
    { DispL(); exit(0); }

/* sprawdz konwersje koncow linii [ uzywam wlasnego index() ]*/
if(indexx('=',argv[1]) != -1) opt_mode=TO_CRLF;
if(indexx('-',argv[1]) != -1) opt_mode=TO_LF;
#endif

#ifndef CGI
/* sprawdzanie makr */
switch(*argv[1])
{
    case 'l':   strncpy(p_swt,"13",2); break;
    case 'm':   strncpy(p_swt,"31",2); break;
    case 'x':   strncpy(p_swt,"10",2); break;
    case 'y':   strncpy(p_swt,"30",2); break;
    case 'z':   strncpy(p_swt,"21",2); break;
/* te 2 zachowane dla kompatybilnosci z poprzednimi wersjami */
    case 'S':   DispS(); exit(1); /* lista standardow */
    case 'L':   DispL(); exit(1); /* licencja uzytkownika */
    default:   strcpy(p_swt,argv[1]);
}; /* sprawdzanie makr */
#else
    strncpy(p_swt,argv[1],3);
#endif

st_in=swt[0];
st_out=swt[1];

/*  wszystkie ew. przypisania zostaly dokonane; teraz sprawdzamy
    poprawnosc argumentow; jesli CGI to bledy pojda do logow */
if( (indexx(st_in,valid1) == -1) || (indexx(st_out,valid2) == -1))
{ fprintf(stderr,"Zly parametr \"%c%c\". Polecenie: cpl -?  wyswietli \
liste dostepnych opcji.\n",st_in,st_out); exit(1); }

#ifdef CGI
if(swt[2] == 'T')
        {
            strcpy(cont_type,"text/plain");
            strcpy(fnam1,(argv[1]+indexx('T',argv[1])+1) );
            ConvFile(fnam1,"stdout",st_in,st_out);
         }

else if(swt[2] == 'H')
        {
            strcpy(cont_type,"text/html");
            strcpy(fnam1,(argv[1]+indexx('H',argv[1])+1) );
            ConvFile(fnam1,"stdout",st_in,st_out);
        }
else
    {
        fprintf(stderr,"\nconvpl: brak separatora T lub H w linii polecen\n");
        exit(1);
    }
#endif

#ifndef CGI
if(argc==2) { ConvFile("stdin","stdout",st_in,st_out ); unlink("stdout"); exit(0);  }
  else
   if(argc==3) {
                 ConvFile(argv[2],TEMP_FILE,st_in,st_out );
                 unlink(argv[2]);
                 rename(TEMP_FILE,argv[2]);
/*               exit(0); */
                }
    else if(argc>3) {
                      ConvFile(argv[2],argv[3],st_in,st_out );
/*                    exit(0); */
                    }
#endif
} /* argc>1 */
      else
{
    DispH();
    return(1);
} /* argc<2 */

return(0);
} /* main */
