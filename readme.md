# Seminarksa Naloga Operacijski Sistemi
## Vzporedno pakiranje tekstovnih datotek
Naloga je ustvariti 2 C programa, zapni in odpni, ki bosta vzela kot argumente imena datotek, jih prebrala in
bodisi zapakirala v krajšo skrčeno obliko ali pa odpakirala v originalno obliko.
Vsaka podana datoteka ustvari svojo nit in se zapakira/odpakira neodvisno od ostalih datotek.

Vsebina se izpiše na standard output (terminal), lahko pa se preusmeri v poljubno datoteko s shell preusmeritvijo 
(> znak, sledeč z imenom datoteke v katero hočemo shranit output).


### Vrsta pakiranja
Program uporablja RLE (Run-Length-Encoding), ki nadomesti ponavljajoče, zaporedne znake s
4-byte-nim celim številom (ki pove kolikokrat se karakter ponovi), 
ter pripne znak na koncu (v realnosti izpiše najprej celo število in nato izpiše znak na terminal).

Med pakiranjem se izgubijo podatki o koncu in začetku datoteke, tako da ko odpneno datoteko,
dobimo eno samo datoteko, tudi če smo zapakirali ali odpakirali več datotek.


### Niti
Program ustvari za vsak podan argument novo nit, s pomočjo knjižnice pthread 
(izključujoč prvi argument argv[0], ker to je sama .c datoteka).

Vsaka nit dobi podano ime datoteke in jo proba zapeti, oziroma odpeti.


### Znane težave (mnogo njih)
Ker vsaka nit posebej izpisuje na output, neodvisna od druge, je velika možnost da se posamezne črke pomešajo med seboj,
še posebej če jih je veliko. Problem bi se dalo rešiti tako da bi vsaka nit počakala da prejšnja konča... kar bi pa 
izničilo bistvo večih niti in bi bilo bolje imeti samo 1 zaporedno sled.

Programa imata tudi težavo ko izpisujemo output v datoteko (> out.z), kadar je input slab.
Za najboljšo uporabo priporočam, da se skrbno preveri, da je podani argument res pravo ime datoteke, ki jo želimo pakirati.

**./zapni test1.txt test2.txt > test.z** bi bil vredu ukaz naprimer.

### Postopek reševanja te seminarske naloge (in končni obup, da bom kdaj razumel C jezik)
Sprva je bila ideja preprosta:
1. Vzeti string iz datoteke.
2. Iti črko po črko in če se ponavljajo,
3. jih spremeniti v številko + črko.
4. Vse to združevati v nov string in ga izpisati.
   
(Odpeti nazaj pa na podoben način)

Kakor se izkaže, upravljanje s tabelami znakov (C ne pozna stringov), potrebuje goro znanja o kazalcih, kazalcih kazalcev,
in vrsto drugih stvari, kar mi nikoli ni uspelo razumeti v dosti velikem merilu, da bi lahko sam izpisal taka 2 programa.

Pthreads po drugi strani ni "*prevelik*" zaplet razvozljati, ampak v kombinaciji z ostalim veseljem, ki ga C jezik določa,
se je izkazalo, da ne bom v tako kratkem času zmogel intuitivno razumeti tega jezika dovolj, da rešim to nalogo brez 
googlanja rešitev.

Tako da, na koncu sem vzel rešitev najdeno tukaj https://github.com/mmajamaa/parallel-zip
in se odločil, da bolje kot izpisati svojo polomljeno verzijo, vzamem njeno in čim bolje probam razumeti,
kako in zakaj je kje kaj naredila.

Načeloma vem kaj vsak del kode dela (v teoriji vsaj), ampak iz svoje glave ne bi znal to napisati, vsaj ne v danem roku.