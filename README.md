[ConvPL] by kravietZ                                                17.09.08
                                                                (ISO-8859-2)


                         Uniwersalny konwerter
                       standardow polskich znakow
                                 v2.3


ConvPL jest programem freeware, rozprowadzanym wraz z kodem
zrodlowym. To co go wyroznia od innych tego typu programow, to liczba
obslugiwanych standardow, dowolnosc kierunkow konwersji i maksymalnie
uproszczona - choc dajaca wiele mozliwosci - linia polecen.


:SKLADNIA:
~~~~~~~~~~

        cpl <nn>[<konwersja>] [<wejscie.txt>] [<wyjscie.txt>]

Parametr <nn> to dwie cyfry/litery, okreslajace standard zrodlowy (pierwsza)
i docelowy (druga) przeprowadzanej konwersji.

Parametr <konwersja> okresla rodzaj opcjonalnie stosowanej konwersji
zakonczenia linii pomiedzy DOSem a Unixem i Amiga.

Parametry "wejscie.txt" i "wyjscie.txt" to nazwy plikow odpowiednio
zrodlowego i docelowego.

********************************************************************
Podanie tylko jednej nazwy - pliku wejsciowego - spowoduje zapisanie
tekstu po konwersji pod ta sama nazwa.
********************************************************************


:OBSLUGIWANE STANDARDY:
~~~~~~~~~~~~~~~~~~~~~~~

Dostepne standardy (podajemy dwie cyfry/litery):

         0: bez polskich liter (ASCII,CP473) a: Microvex
         1: Mazovia                          b: <Amiga> Amiga PL
         2: FidoMazovia                      c: CP/J (Elwro 800 Junior)
         3: IBM-Latin/2 (CP852)              d: <Amiga> FAT
         4: ISO-Latin/2 (ISO-8859/2)         e: Windows 3.0 (CP1250)
         5: DHN                              f: <Amiga> XJP
         6: CSK                              g: Ventura
         7: Cyfromat                         h: Macintosh
         8: IEA                              i: TeX PL
         9: LOGIC                            j: Corel 2.0

:skroty:

Zamiast najczesciej stosowanych konwersji mozna stosowac skroty. Podajemy
wowczas tylko jedna litere:

             l: Mazovia na IBM-Latin/2
             m: IBM-Latin/2 na Mazovie

             x: Mazovia na ASCII
             y: IBM-Latin/2 na ASCII

             z: Fido-Mazovia na Mazovie

Dowolnosc konwersji jest calkowita, z jednym wyjatkiem. Standard ASCII nie
moze byc standardem zrodlowym konwersji (przyczyna jest oczywista - zeby nie
pokaszani‡ calego tekstu - ale jest od tej reguly wyjatek! patrz UWAGI).

:konwersja zakonczen linii:

ConvPL umozliwia rownolegla konwersje pomiedzy tekstem spod DOSa, a tekstem
spod Unixa czy Amigi. Rodzaj docelowej konwersji okreslaja parametry:

          -: konwersja do tekstu Unixa (Amigi)  -> NL
          =: konwersja do tekstu DOSa           -> CR+LF

Zmienilem wystepujace w poprzednich wersjach oznaczenia tych parametrow
(/,\), poniewaz bekslesz jest znakiem specjalnym pod U*xem. Nowe ustawienia
mozna rownie latwo zapamietac: pod U*xem koniec linii to jeden znak (NL),
wiec jedna kreska: "-"; pod DOSem sa to dwa znaki (CR+LF), stad dwie
kreski: "=". ;)

Patrz rowniez rozdzial Uwagi, akapit Konwersja Unix<->DOS.

:PRACA W TRYBIE FILTRU:
~~~~~~~~~~~~~~~~~~~~~~~

ConvPL moze pracowac rowniez w trybie filtru. Brak nazw plikow we/wy
spowoduje pobranie tekstu z standardowego urzadzenia wejscia - stdin
(klawiatura) i zapisanie go do standardowego wyjscia - stdout (monitor,
terminal, drukarka). Przyklady:

        cpl l                      - kazda linia wpisywana z klawiatury bedzie
                                     pojawiala sie ponizej po wcisnieciu
                                     <Enter>, znaki z kodu Mazovia beda
                                     zamieniane na IBM Latin 2

        cpl l <joke.txt >prn       - konwersja pliku joke.txt i wyslanie
                                     wynikow bezposrednio na drukarke (DOS);

        cpl l <joke.txt >joke2.txt - rownoznaczne poleceniu "cpl l joke.txt"

Jesli nie chcemy zasmiecac sobie dysku, wydajemy nastepujace polecenia:

        cpl l <joke.txt >nul (MSDOS) lub >/dev/null (Unix)

Tryb filtru umozliwia rowniez przetwarzanie tekstu w potoku (pipe).

Przyklad:

      type joke1.txt | cpl 14- >joke3.txt (MSDOS)
      cat joke.txt1 joke2.txt | cpl14- >joke3.txt (Unix)

Przyjmujac, ze pliki joke.txt i joke2.txt sa napisane oryginalnie
w Mazovii i pod MSDOSem, takie polecenie spowoduje polaczenie obu plikow,
konwersje z Mazovii na ISO-Latin-2, i przy okazji z CR+LF -> NL, a nastepnie
zapis do pliku joke3.txt.

Uruchamiajac ConvPL w tym trybie nalezy uwazac na pomylki takie jak ta:

        cpl l joke.txt >prn

-tekst zostanie przekonwertowany zgodnie z regula 13 (skrot "l"), ale na
drukarke nie zostanie wyslany, gdyz ConvPL bedzie go zapisywal do pliku
joke.txt a nie na standardowe wyjscie. W rzeczywistosci powyzsze (bledne)
polecenie oznacza: konwertuj plik joke.txt, zapisujac wynik pod ta sama nazwa,
zas na drukarke wysylaj wyjscie przez program normalnie wyswietlane na ekranie,
czyli komunikaty.

Polecenie ponizsze spowoduje najprawdopodobniej uszkodzenie oryginalnego pliku,
wiec nalezy sie go wystrzega‡:

        cpl l <joke.txt >joke.txt (obie nazwy takie same!)

Po prostu, system straci glowe probujac rownoczesnie czyta‡ i pisa‡
do pliku, a ucierpi na tym tenze plik.

Pamietajmy: aby uruchomic ConvPL w trybie filtru, potok danych musi
przychodzic ze stdin i wychodzic na stdout (a nie czesciowo z pliku, czesciowo
z potoku). Jesli nie wiesz o co chodzi, to poczytaj o potokach, filtrach oraz
roli symboli <, |, > itp. w poleceniach DOSa i Unixa.


:UWAGI:
~~~~~~~
:komentarz do standardow:

Za definicje Amiga PL dziekuje Marcinowi Kadziolce <2:484/15.16@fidonet>.

Definicje dodane w wersji 1.75 udostepnil mi Edwin Wierszelis
<2:482/16@fidonet>, autor konwertera KPN.

"Standard" ASCII to oczywiscie zwykle literki ASCII, zastepujace odpowiednie
polskie znaki. Taki tekst zwie sie zwykle "polskawym", a standard okresla
jako CP473 (podstawowa, amerykanska strona kodowa).

Fido-Mazovia jest polformalnym standardem, przyjetym w srodowisku sieci
Fido. Jedyna roznica w stosunku do klasycznej Mazovii to zamiana znaku
c' (141) na c-cedilla (135), wynikajaca ze wzgledow technicznych.

Standard IBM-Latin/2 (CP852), rozpowszechniony glownie w srodowisku DOSa,
jest lansowany m.in. przez Micro$oft.

ISO-8859/2, znany tez jako ISO-Latin/2 jest standardem rozpowszechnionym
zwlaszcza w systemach unixowych, pracujacych pod X-windowsami. Jest rowniez
standardem zalecanym przez Polskie Normy oraz uznanym za obowiazujacy
w polskojezycznym WWW.

Standard FAT jest jednym z amigowskich dialektow, znalezionym w diskmagu
FAT przez Edwina Wierszelisa.

Standard Windows 3.0 jest uproszczona, 8-bitowa wersja UniCode, zdefiniowana
jako strona kodowa 1250 (CP1250). Znany tez jako Windows-EE, czyli strona
kodowa dla Europy Wschodniej.

Standard DHN jest rozpowszechniony wraz z polskim ChiWriterem.

:konwersja tekstu Unix<->DOS:

Pod Unixem kazda linijka tekstu konczy sie znakiem NL (new line) o kodzie 0xa,
rownoznaczny DOSowemu LF (line feed). Pod DOSem zakonczenie linii stanowi
para znakow CR+LF, czyli 0x0d,0x0a. Parametr "-" wymusza zakonczenie linii
znakiem NL, zas "=" - para CR+LF. Brak okreslonego kierunku konwersji
nie spowoduje zadnej zmiany koncow linii w pliku wynikowym. Parametry konwersji
zakonczen linii dodaje sie "na trzeciego" do parametrow konwersji standardow.

UWAGA: od wersji 2.01 istnieje mozliwosc wykonywania konwersji zakonczen linii
bez zmiany standardu polskich znakow. Wystarczy jako standard zrodlowy
podac ASCII - "0" (do tej pory bylo to niedopuszczalne), zas jako drugi
parametr opcje konwersji zakonczen linii "-" lub "=".  Drugi parametr,
podany zgodnie z konwencja i okreslajacy standard docelowy jest w tym
wypadku ignorowany. A zatem, kazdy z ponizszych przykladow ma takie samo
dzialanie:

        cpl 0- joke.txt
        cpl 00- joke.txt
        cpl 02- joke.txt         ("2" jest tu ignorowane)

czyli konwersje zakonczen linii do pojedynczych NL, bez naruszania
polskich liter.

:kod zrodlowy:

Program byl z powodzeniem kompilowany Borlandem 3.1, gcc 2.7.0 pod Linuxem
(a.out) oraz DJGPP pod DOSem (gcc 2.6.3). Prosze o kontakt w razie wystapienia
niekompatybilnosci kodu zrodlowego w innych systemach.

:licznik linii:

Typowy "wodotrysk". Zwalnia prace o ok. 30%. Standardowo wylaczony, w celu
wlaczenia trzeba przekompilowac zrodla bez opcji NO_LINE_COUNT. Licznik jest
zawsze wylaczony podczas pracy w trybie stdin/stdout (czyli zazwyczaj jako
filtr, CGI itp.).

:CGI:

Poczawszy od wersji 2.02 mozna CPL skompilowac jako CGI, czyli program
wspolpracujacy z serwerem WWW. W tej wersji CPL traci niepotrzebne opcje
oraz modyfikacji ulega sposob wywolywania. Skladnia CPL-CGI jest nastepujaca:

        cpl <nn><T | H><nazwa.pliku>     (bez odstepow!)

Gdzie nn to standard zrodlowy i docelowy (bez zmian) a T/H okresla
typ tekstu wg standardu MIME:

        H:      text/html  (tekst zrodlowy HTML)
        T:      text/plain (kazdy inny tekst)

Przyklad:

        cpl 4eHplik.html = konwersja ISO-Latin do Windows, plik typu HTML
        cpl 41Tplik.txt  = ISO-Latin do Mazovii, zwykly plik tekstowy

Wywolanie z dokumentow HTML (w formacie URLa) powinno wygladac np. tak:

        http://host.domena.pl/cgi-bin/cpl?3eHplik.html

:inne opcje:

-?, -h,
    /?, --help: wyswietlaja liste wszystkich dostepnych parametrow,
                skladnie linii komend itp.
-V,  --version: wyswietla (na stdout) numer wersji CPL
-L, --licencja: wyswietlana licencje uzytkowania programu.
-S, --standard: wyswietlaja tabelke wszystkich obslugiwanych
                standardow polskich znakow.

:HISTORIA:
~~~~~~~~~~

1.0     pierwsza wersja (quick fix dla pakietu PGP-pl);
1.2     definicje standardow przeniesione do polish.c; pare nowych definicji;
1.3     Amiga PL; nowy uklad polish.c;
1.5     nieco przyspieszona praca; nowy kod zrodlowy, makefile;
1.6     skroty dla najczesciej uzywanych konwersji; tryb stdin/stdout (filtr)
1.7     konwersja miedzy tekstem unixowym (amigowym) i DOSowym
1.72    licznik linii
1.75    nowe definicje (Win 3.0, FAT, XJP, CP/J);
1.76    nowe definicje (Ventura, Macintosh, TeX PL i Corel);
1.90    dodana konwersja wielu plikow, pare innych zmian;
2.00    napisany w 90% od nowa, usuniete stare pluskwy, wprowadzone nowe ;)
        dodane rozpoznawanie standardow
2.01    kilka dodatkow, zmiany w interpretacji niektorych polecen (patrz Uwagi)
2.02    mozliwosc skompilowania jako CGI; umozliwia to wywolywanie CPL przez
        serwer WWW i konwersje tekstow dokonywana on-line (patrz Uwagi)
        _ta wersja nie byla przeze mnie jeszcze dostatecznie przetestowana,
        uzywaj raczej 2.01 jesli nie potrzebujesz nowych funkcji_
2.3	wersja odkurzona po 12 latach



[QueryPL] by kravietZ                                              



                           Narzedzie do rozpoznawania
                           standardow polskich znakow



QueryPL jest programem freeware, rozprowadzanym wraz z kodem
zrodlowym. Sluzy do rozpoznawania standardu kodowania polskich znakow
w plikach tekstowych, jesli standard ten jest nieznany lub niepewny.

:SKLADNIA:
~~~~~~~~~~

             qpl <plik> [-s | -v | -b]

Jako pierwszy argument podaje sie zawsze plik ktory ma byc sprawdzony.
Po nazwie pliku moga nastepowac dwa opcjonalne argumenty:

        -s      uzycie metody statystycznej, generalnie pewniejszej
                i koniecznej w niektorych wypadkach; patrz rozdzial
                ALGORYTM i UWAGI nr 3.

        -v      wyswietlenie szczegolowych informacji o pracy programu,
                tabeli zgodnosci itp.

        -b      podanie wyniku analizy w postaci parametru dla
                programu ConvPL - cyfry lub litery; opcji tej mozna
                uzyc do automatycznego konwertowania plikow
                o nieznanym standardzie, podstawiajac uzyskany znak
                do linii polecen CPL jako standard zrodlowy; patrz
                dokumentacja ConvPL; opcja -b automatycznie wylacza
                opcje -v

:ALGORYTM:
~~~~~~~~~~
Zasada dzialania jest nastepujaca: zliczane sa wszystkie wystapienia
wszystkich polskich znakow narodowych. Poniewaz znaki powtarzaja sie
w roznych standardach, kazde wystapienie jest zliczane oddzielnie
dla kazdego ze standardow. Nastepnie wystapienia wszystkich znakow
sa sumowane w obrebie standardow. Wygrywa standard, w ktorym zmiescilo
sie wiecej znakow znalezionych w tekscie.

Moze sie zdarzyc ze w tekscie beda wystepowac znaki nie majace funkcji
znakow diakrytycznych (np. jako elementy tabelki), ale nalezace do ktoregos
z licznych standardow. W pewnych przypadkach moga one zmienic wynik analizy
zwyklych zliczen, prowadzac do zlego wyboru standardu. Dla zapobiezenia
temu QPL moze dodatkowo wykorzystac wiedze o tym, jak czesto kazdy z
znakow diakrytycznych wystepuje w normalnym, polskim tekscie. Metode
statystyczna, wykorzystujaca te funkcje, wlacza sie opcja -s.

W tym wypadku, przed zsumowaniem zliczen kazde z nich zostanie pomnozone
przez odpowiedni wspolczynnik, wskazujacy z jaka czestotliwoscia dana
litera zwykle wystepuje. Tabele zliczen znakow dla obu metod wyswietla
opcja -v.

Opcji -s nalezy uzywac do tekstow, w ktorych poza normalnymi polskimi
znakami wystepuja inne znaki, mogace byc znakami diakrytycznymi w jakims
innym standardzie. Warto tez jej sprobowac, gdy metoda standardowa daje
w wyniku jakis rzadki i niespotykany standard.

:UWAGI:
~~~~~~~
1) Winietka programu i wszystkie informacje sa wyswietlane na stderr,
dzieki czemu sa "niewidzialne" przy zrzucaniu wyjscia do pliku,
filtrowaniu itp. Tabela zgodnosci (-v) i wynik - parametr dla ConvPL (-b)
sa natomiast wyswietlane na stdout (nigdy razem, bo jedno wyklucza drugie).

2) QPL jest rozprowadzany razem z konwerterem ConvPL. Zdecydowalem sie
na rozprowadzanie go w postaci odrebnego programu z powodow praktycznych.
Jako taki, moze on miec wieksze mozliwosci, wiecej zastosowan i bogatsza
linie polecen. Wspolprace miedzy obydwoma programami - w celu np. automatyzacji
konwersji mozna dosc latwo zapewnic sobie za pomoca skryptow (U*x) lub baczow
(MSDOS/4DOS).

3) Rozroznienie standardow DHN i Logic jest trudne, bo skladaja sie one
z tych samych znakow, a roznica miedzy nimi polega na tym, ze cztery
sa zamienione kolejnoscia. QPL zazwyczaj trafnie rozpoznaje roznice
przy uzyciu metody statystycznej (-s), jednak w wyniku podaje na wszelki
wypadek obie mozliwosci. Druga z nich jest mniej prawdopodobna,
ale teoretycznie jest mozliwa.

4) Nie ksztalce sie na wydziale majacym cokolwiek wspolnego z informatyka,
a oba algorytmy sam sobie wykombinowalem. W zwiazku z tym przyjmuje kazdy
zarzut o nieefektywnosc, brak oryginalnosci, poziom przedszkola itp. byle
na odpowiednim poziomie merytorycznym. ;)

Historia:
1.0     pierwsza wersja

QueryPL jest rozprowadzany na tych samych warunkach co ConvPL.
Sa one wyswietlane po wydaniu polecenia: cpl --licencja.

..............................................................................
Autor            : Pawel Krawczyk <pawel.krawczyk@hush.com>
Najnowsza wersja : http://ipsec.pl/cpl


