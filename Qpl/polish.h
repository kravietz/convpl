
/*
        polish.h - declarations of Polish national characters

                               v4.3.20
                            public domain

                         polish.h by kravietZ

        Pliki polish.h i polish.c sa wlasnoscia publiczna (public domain)
        i moga byc uzywane w programach wszelkich rodzajow (rowniez
        komercyjnych).

        Autor:   Pawel Krawczyk <kravietz@pipeta.chemia.pk.edu.pl>
                                <2:486/19.19@fidonet>
*/

#define PCHCNT 18         /* liczba polskich znakow diakr. w alfabecie*/
#define PSTCNT 20         /* liczba zdefiniowanych standardow */

/* tablice */

/* BezPolsk: polskie znaki zastapione przez odpowiadajace znaki ASCII */
extern  unsigned char BezPolsk[];
extern  unsigned char AmigaPL[];        /* Amiga PL */
extern  unsigned char Corel;            /* Corel 2.0 */
extern  unsigned char CPJ[];            /* CP/J Elwro 800 Junior */
extern  unsigned char CSK[];            /* st. f-my CSK */
extern  unsigned char Cyfromat[];       /* st. f-my Cyfromat */
extern  unsigned char DHN[];            /* DHN (MS-DOS, ChiWriter-PL) */
extern  unsigned char Amiga_FAT[];      /* amigowski (diskmag FAT) */
extern  unsigned char FidoMazovia[];    /* Mazovia z c' (141) zastapionym
                                           przez c-cedilla (135) */
extern  unsigned char IEA[];            /* st. Instytutu Energii Atomowej
                                           w Swierku */
extern  unsigned char IBM_Latin2[];     /* IBM Latin-2, CP852 (MS-DOS,
                                           Windoza) */
extern  unsigned char ISO_Latin[];      /* ISO Latin-2 (Unix, Xwin) */
extern  unsigned char Logic[];          /* st. f-my (?) Logic */
extern  unsigned char Macintosh[];
extern  unsigned char Mazovia[];        /* Mazovia (MS-DOS) */
extern  unsigned char Microvex[];       /* st. f-my Microvex */
extern  unsigned char TeXPL[];
extern  unsigned char Ventura[];
extern  unsigned char Windows30[];      /* zalecany dla Windows 3.0 EE (CP1250)*/
extern  unsigned char XJP[];            /* amigowski XJP */

/* wskazniki */

extern  unsigned char *p_Asc;
extern  unsigned char *p_Ami;
extern  unsigned char *p_Cor;
extern  unsigned char *p_CPJ;
extern  unsigned char *p_CSK;
extern  unsigned char *p_Cyf;
extern  unsigned char *p_DHN;
extern  unsigned char *p_FAT;
extern  unsigned char *p_FMaz;
extern  unsigned char *p_IEA;
extern  unsigned char *p_IBML;
extern  unsigned char *p_ISOL;
extern  unsigned char *p_Log;
extern  unsigned char *p_Mac;
extern  unsigned char *p_Maz;
extern  unsigned char *p_Mic;
extern  unsigned char *p_TeX;
extern  unsigned char *p_Ven;
extern  unsigned char *p_Win3;
extern  unsigned char *p_XJP;

/*    end polish.h     */
