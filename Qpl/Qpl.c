// Qpl.cpp : Defines the entry point for the console application.
//


#ifndef __GNUC__
#include <share.h>
#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>

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

#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#ifdef __GNUC__
#include <sys/stat.h>
#include <sys/file.h>
#define O_BINARY 0
#endif

#include "polish.h"                    /* min. wer. 4.3.20 */

#define BUF_SIZE (4*1024)              /* bufor 4K */
#define CSTCNT (PSTCNT-1)              /* nie bierzemy pod uwage BezPolsk */
#define T_LEN (CSTCNT*PCHCNT+CSTCNT)   /* trzeba policzyc dodatkowo zera */

typedef unsigned char ubyte;

const ubyte qver_h=2;
const ubyte qver_l=3;

/* 
   wagi zostaly okreslone na podstawie zliczen polskich znakow w pliku 
   zlozonym z kilku polskojezycznych tekstow o lacznej dlugosci 500KB
*/
int wagi[PCHCNT]={1,1,1,1,1,1,1,1,1,15,10,16,19,1,13,13,1,18}; /* wagi */
int wyn[CSTCNT];
int licznik[T_LEN];
int i,j,wynik1,sum1,ind1,res;
long dlug1=0;
ubyte o_stat=0, o_verb=0, o_batch=0;
char znaki[]="bjc675d28349h1ai9ef"; /* konwersja dla opcji -b */
char ch1;
char ibuf[BUF_SIZE], obuf[BUF_SIZE];
int ibuf_ptr = 0, obuf_ptr = 0, ibuf_lim = 0;
int f_in;

int getopts(char *opt1,int argc1, char **argv1)
{   int i;

    for(i=1;i<argc1;i++) if(!strcmp(argv1[i],opt1)) return(1);

/* else */
    return(0);
}

ubyte getxx(void)
{
  if (ibuf_ptr >= ibuf_lim) {               /* odebrane wszystkie? */
    ibuf_lim = read(f_in, ibuf, BUF_SIZE);  /* czytaj z pliku */
    if (ibuf_lim == 0) return -1;           /* nie ma wiecej w pliku */
    ibuf_ptr = 0;                           /* inicjuj wskaznik znakow */
  }
  return ibuf[ibuf_ptr++];                  /* daj znak, zwieksz wskaznik */
}

void ListC(int num1)
{   int i;
    for(i=0;i<PCHCNT;i++) fprintf(stdout,"%2u ",licznik[(num1*(PCHCNT+1))+i]);
    fprintf(stdout," (%u)",wyn[num1]);
}

void DispQH(void)
{
fprintf(stderr,"\
Skladnia: qpl <plik> [-v | -s | -b]\n\
Opcje   :\n\
        -s  rozpoznawanie statystyczne\n\
        -v  wyczerpujacy raport\n\
        -b  wynik w postaci parametru ConvPL\n\
\nSzczegoly w dokumentacji (qpl.txt).\n");

}

int main(argc,argv)
int argc;
char **argv;


{

fprintf(stderr,"[QueryPL] by kravietZ, v%u.%u, rozpoznawanie standardu \
polskich liter. Freeware.\n\n",qver_h,qver_l);

/* inicjalizacja licznikow */
for(i=0;i<T_LEN;i++) licznik[i]=0;

if(argc<2) { DispQH(); return(1); }


f_in= open(argv[1], O_RDONLY|O_BINARY);

if(f_in <0) perror(argv[1]);

    else

    {
        if(argc>2)
        {
            if(getopts("-s",argc,argv)) o_stat++;
            if(getopts("-v",argc,argv)) o_verb++;
            if(getopts("-b",argc,argv)) { o_batch++; o_verb=0; }
        }

        if(o_verb) fprintf(stderr,"Zliczanie polskich znakow...\n");
            else
            fprintf(stderr,"Rozpoznawanie standardu...\n");

        while((ch1=getxx()) != EOF)
        {
            dlug1++;
            if( (ubyte) ch1>127) /* po co sprawdzac zwykle znaki */
               for(i=0;i<T_LEN;i++)
                 if( ( (ubyte) ch1 == *(p_Ami+i)) ) licznik[i]++;

        } /* end zliczanie znakow */

/* zamkniecie pliku wejsciowego */
    close(f_in);

    if(o_verb)
    {
        fprintf(stderr,"Rozpoznawanie standardu. Poczekaj...\n");
        if(o_stat) fprintf(stderr,"Statystyka...\n");
    }


    for(i=0;i<CSTCNT;i++)
    {
        sum1=0;
        for(j=0;j<PCHCNT;j++)
        {
            ind1=(i*(PCHCNT+1))+j;
/* opcja statystyki (-s) */
           if(o_stat) licznik[ind1]=licznik[ind1]*wagi[j];
            sum1=sum1+licznik[ind1];
        }
        wyn[i]=sum1;
     } /* end zliczanie licznikow */

    wynik1=0;
    for(i=0;i<CSTCNT;i++) if(wyn[i] > wynik1) { wynik1=wyn[i]; res=i; }

    if(wynik1==0) res=255; /* jesli nie ma zadnych polskich znakow */

/* raport -v */

    if(o_verb) /* opcja -b wylacza opcje -v */
    {
      fprintf(stdout,"\n\
Tabela zgodnosci znalezionych w tekscie znakow z roznymi standardami.\n\
W kazdym wierszu znajduje sie 18 zliczen dla kazdego polskiego znaku diakryty-\n\
cznego. W nawiasie na koncu podana jest suma zliczen. Przy opcji -s kazde\n\
zliczenie jest dodatkowo przemnozone przez odpowiadajaca mu wage. Szczegoly\n\
algorytmu znajdziesz w dokumentacji.\n\n");
      fprintf(stdout,"\nAmiga PL    : "); ListC(0);
      fprintf(stdout,"\nCorel 2.0   : "); ListC(1);
      fprintf(stdout,"\nCP/J        : "); ListC(2);
      fprintf(stdout,"\nCSK         : "); ListC(3);
      fprintf(stdout,"\nCyfromat    : "); ListC(4);
      fprintf(stdout,"\nDHN         : "); ListC(5);
      fprintf(stdout,"\nAmiga FAT   : "); ListC(6);
      fprintf(stdout,"\nFidoMazovia : "); ListC(7);
      fprintf(stdout,"\nIEA         : "); ListC(8);
      fprintf(stdout,"\nCP852       : "); ListC(9);
      fprintf(stdout,"\nISO-8859/2  : "); ListC(10);
      fprintf(stdout,"\nLogic       : "); ListC(11);
      fprintf(stdout,"\nMacintosh   : "); ListC(12);
      fprintf(stdout,"\nMazovia     : "); ListC(13);
      fprintf(stdout,"\nMicrovex    : "); ListC(14);
      fprintf(stdout,"\nTeX PL      : "); ListC(15);
      fprintf(stdout,"\nVentura     : "); ListC(16);
      fprintf(stdout,"\nCP1250      : "); ListC(17);
      fprintf(stdout,"\nAmiga XJP   : "); ListC(18);
      fprintf(stdout,"\n");
    } /* o_verb */

    fprintf(stderr,"\nPlik           : %s\n",argv[1]);
    fprintf(stderr,"Dlugosc        : %ld\n",dlug1);
    fprintf(stderr,"Metoda         : %s",(o_stat ? "statystyczna\n" : "standard\n"));
    fprintf(stderr,"Polskie litery : ");

   switch(res)
   {
   case 0:  fprintf(stderr,"Amiga PL\n"); break;
   case 1:  fprintf(stderr,"Corel 2.0\n"); break;
   case 2:  fprintf(stderr,"CP/J (Elwro 800 Junior)\n"); break;
   case 3:  fprintf(stderr,"CSK\n"); break;
   case 4:  fprintf(stderr,"Cyfromat\n"); break;
   case 5:  fprintf(stderr,"DHN (lub Logic)\n"); break;
   case 6:  fprintf(stderr,"Amiga FAT\n"); break;
   case 7:  fprintf(stderr,"FidoMazovia\n"); break;
   case 8:  fprintf(stderr,"IEA\n"); break;
   case 9:  fprintf(stderr,"CP852 (IBM-Latin/2)\n"); break;
   case 10: fprintf(stderr,"ISO-8859/2 (ISO-Latin/2)\n"); break;
   case 11: fprintf(stderr,"Logic (lub DHN)\n"); break;
   case 12: fprintf(stderr,"Macintosh\n"); break;
   case 13: fprintf(stderr,"Mazovia\n"); break;
   case 14: fprintf(stderr,"Microvex\n"); break;
   case 15: fprintf(stderr,"TeX PL\n"); break;
   case 16: fprintf(stderr,"Ventura\n"); break;
   case 17: fprintf(stderr,"CP1250 (Windows 3.0 EE)\n"); break;
   case 18: fprintf(stderr,"Amiga XJP\n"); break;
   default: fprintf(stderr,"brak polskich znakow w pliku\n"); break;
    } /* switch */

/* wyrzuca parametr dla ConvPL, jesli brak polskich liter to 0 */
   if(o_batch) {
             if(res != 255)
                        {
                          fprintf(stderr,"ConvPL         : ");
                          fprintf(stdout,"%c",znaki[res]);
                          fprintf(stderr,"\n");
                        }
                        else fprintf(stdout,"0");
                }
   } /* end open ok */

    return(0);
}

