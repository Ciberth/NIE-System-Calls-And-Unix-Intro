# Week 6: Theorie op 23/03/17

## Filedescriptoren

```sh

ls - l 

        # in /proc/1710/fd # is proces 1710 van in andere terminal 

        # file descriptoren -> voor omleidingen
        # en hier zie je dan standaarduitvoer, invoer ... naar wa ze gemapt zijn.

        # je kan via exec opdracht zelf filedescriptoren openen

        # nummertje of variable die je meegeeft aan exec voor fd 
        # 3 is bvb nog vrij 
        # en dan moet je kiezen hoe je het opent (in lees/schrijfmode of een enkele)
        # < lees mode
        # tel is map  

exec 3 <tel 

        # doe je nu ls -l dan zie je voor dat proces 
        # merk ook op dat de read van < komt 
        
3 -> /root/tel

exec 4>t 

4 -> /root/t 

        # met een write rechten 

        # je kan ook openen met beide r/w via 

        # -n zonder linefeed 

echo -n abcdefghijklmnopqrstuvwyz > x

exec 5<>x 

        # ls -l geeft dan rw

cat tel 

        # geeft volledige inhoud van bestand

read lijn < tel ; echo $lijn 

        # dan krijg je eerste lijn van het bestand 
        # ook als je het meermaals na mekaar doet! 

while read lijn < tel ; do echo $lijn ; done 

        # dan krijg je oneindige lus op eerste lijn 

while read lijn ; do echo $lijn ; done < tel 

        # dan ga je wel alle lijnen uitlezen 
        # let op dit heeft wel gebreken! 
        # denk bvb aan een header uitlezen en dan pas de rest
        # veel vrijheid heb je hier dus niet 


        # met file descriptoren gaat da beter 

read lijn <&3 ; echo $lijn 

        # eerste keer een 
        # voer je opnieuw uit dan heb je twee
        # dan drie
        # ... 

        # hij gaat dus een voor een afgaan 

while read lijn <&3 ; do echo $lijn ; done 

        # is dus een veel logischere constructie

exec 3<&- 

        # afsluiten van bestand  
        # het < teken maakt nie veel uit mag ook > zijn maar volg de conventie toch maar 

exec 3<tel 
read lijn <&3 ; echo $lijn 
read lijn <&3 ; echo $lijn 
read lijn <&3 ; echo $lijn 

cat <&3 

        # zal dan alles inlezen vanaf de pointer dus NA de eerste drie 
        # vier
        # vijf
        # ...

echo gelijkwat >&4 

        # bestand t uitvoer 
cat t 

        # invoer toevoegen

echo nogiets >>&4 

        # mag dus niet (hij heeft ook fout) !! u fd heeft nen pointer 

echo nogiets >&4


cat t           # gelijkwat en nogiets 
cat tien >&4    # plakt dan heel de inhoud van bestand tien eraan 

exec 4>&-       # afsluiten 


                # openen op andere manier 

exec 4>>t       # de inhoud van het huidige bestand ga je niet verwijderen !! 

                # je plaatst u pointer dus onmiddelijk na de inhoud! 

echo "volgenderegel" >&4 

cat t           # bestaande inhoud is er nog


                # in lees/schrijf modus mag je niet denken dat je twee pointers hebt!!!! 

cat x           # abcdefghijklmnopqrstuvwyz 

read -n1 k <&5 ; echo $k 

        # a 
        # nog een keer uitvoeren b nog een keer c ...

        # 0 toevoegen bvb 

echo -n 0 >&5 ; cat x 

        # abc0defghijklmnopqrstuvwyz
        # read je dan nog keer dan zal je e krijgen dan f dan g 
        # op de plaats waar je bent lees je in en op die plaats ga je wegschrijven 
        # dus 1 pointer !

        # je hebt ook geen respect voor lijnscheidingsteken!

exec 4<&-
exec 5<&- 

            # opnieuw teken boeit niet zoveel

            # je kan ook een nr laten generen ipv zelf te kiezen

exec {fd}<lees 

            # je weet nie welk nrke ma hij zal het doen ; hier wast bvb 10 

echo $fd    # geeft ook tien 

            # read lijn <&${fd} ma {} is nie nodig

read lijn <&$fd

echo $lijn 
cat lees 

                # vo af te sluiten heb je eig een probleem 

exec {fd}<&-    # lukt wel (maar de moreau dacht van niet)


exec 3<lees 
read lijn <&3 ; echo $lijn 

                # aap
                # tweede keer noot derde keer mies


                # je wil omleiding doen naar ander bestand maar je wil terugkeren
                # idee: maak gebruik van tijdelijke filedescriptor 

                # fd kopieren zogezegd 

exec {fd}<&3    # zie dit als een copy van rechts naar links 

exec 3<tel      # 3 dus aanpassen van 3 die is nu omgeleid naar nieuw bestand 

read lijn <&3 ; echo $lijn 

                # doe je dus uit nieuwe bestand 

                # nu moet je terug kopieren als je terug wilt keren 
                # en de fd (hier tien) mag je dan afsluiten 
                # die beide kan je in een keer! dankzij die -

exec 3<&${fd}-

                # nu zit je terug in je bestand waar je het laatst hebt gelezen 
                # (de pointer is dus nog gelijk!)

                # EXAMEN ook omwisselen van file descriptoren doe je zo 

                # 3 naar lees 
                # 4 naar tel 
                # nu kopieren 
                # doe je dus weer met een tijdelijke fd 

exec 4<tel 

        # exec {fd}<&3 # lees dit als de inhoud van 3 komt in tijdelijke terecht 
        # dan vier copy in de drie en copy van tijdelijke in 4
        # - om de tien (den tijdelijke) terug af te sluiten 
        # anders exec {fd}<&- gebruiken 

exec{fd}<&3 ; exec 3<&4 ; exec 4<&${fd}- 

        # merk dus ook op dat u kopietjes ook de plaats van de pointer mee kopieren!! 

        # wrm zou je da nu doen
        # wel standaard invoer en standaard uitvoer is soms interessant 
        # programmas gelijk tee werken slechts op 1 van beide 
        # standaarduitvoer is gebuffered
        # standaarderror is niet gebuffered (nooit)
        # dus da kan soms ook iets zijn da je anders wil 

        # interactief demonstreren is een ramp 

        # in een interactieve sessie moet je nie foefelen met kanalen 0 en 1 
        # 1 kan wel bvb we gaan eens omleiden naar een ander venster 


exec 1>/dev/pts/1 

ls      # zie je dan in het venster naar waar je hebt omgeleid :p 

exec 2>/dev/pts/3 

        # dan ga in je huidige prompt en dus alles wa je intypt ga ook naar ander venster gestuurd worden
        # dus je typt in 1 venster, ziet wat je typt in den 3 en ziet resultaat/uitvoer in den 1 xD 

        # en dienen 255 fd is eigenlijk nen backup 

exec 2>&255
exec 1>&255

        # danku 255 

        # 7 bestandjes koppelen aan 7 fds 

ls 0?   # 01 02 03 04 05 06 07

```

## For en vervolg

```sh


for f in $(ls 0?) ; do echo $f ; done 

        # prints 1-7

i=0; for f in $(ls 0?) ; do exec {t[i]}<$f ; ((i++)) ; done 

declare -p t 

read lijn <&${t[6]}     # dan lees je eigenlijk uit je 7e bestandje 
echo $lijn 
cat 07 

                        # vo af te sluiten moet je zelfde doen 

for x in ${t[@]} ; do echo $x ; done 

                        # alle filedescriptoren

for x in ${t[@]} ; do {x}<&- ; done 

                        # werkt niet en je zou denken $x willen zetten maar
                        # da mag je nie zeggen want hem wil da vervangen 

                        # dus je wil u gerief efkens uitstellen 
                        # je construeert een opdracht die je pas daarna wil uitvoeren 

                        # dit willen we eigenlijk uitvoeren

for x in ${t[@]} ; do echo "exec $x<&-" ; done

                        # ipv te tonen evalueren

for x in ${t[@]} ; do eval "exec $x<&-" ; done



exec{fd}<&1 ; exec 1<&2 ; exec 2<&${fd}-    
    
                        # dit is onzin!!!


{fd}<&1 ; 1<&2 ; 2<&${fd} 

                        # dit mag wel want dit doe je enkel op de opdrachtregel!!  
                        # je hebt er dus geen enkel restant van 


ls -l {01..09}

                        # 8 en 9 bestaan niet dus foutenkanaal

                        # tee je splitst naar nog steeds zelfde console 
                        # en je leidt ook om naar bestand bvb logging/archief 

ls -l {01..09} | tee t 

cat t                   # zie je standaarduitvoer terwijl je ent error wil 

                        # standaardfouten omleiden naar standaarduitvoer 

ls -l {01..09} 2>&1 | tee t 

                        # dan bevat bestand ook beide!

                        # wil je enkel fouten dan moet je wel switchen

ls -l {01..09} 2>&1 | tee t 


{fd}<&1 ; 1<&2 ; 2<&${fd} ls -l {01..09} | tee t 

                        # nu is je fouten (enkel fouten) in t # voor logging 
                        # dus gedurende de levensduur van je commando

```

## (Un)named pipes en vervolg

```sh


            # (un)named pipes kan je via bestand of via fd 

mkfifo p

ls - l p    # dan zie je dat da device file is 

cat tien >p # da blokkeert 
            # de afspraak is als je pipe gebruikt da hij blijft hangen tot een ander proces iets ga inlezen in die pipe 

            # dus in ander venster  

ls -l p 

exec 3<p 

            # in u ander venster is het nu gelukt dus die pipe zit vol met die lijntjes uit tien
            # nu kan je op u gemak readen 

read lijn <&3 ; echo $lijn 

            # dan krijg je eerste lijn, nog eens dan tweede, ...

while read lijn <&3 ; do echo $lijn ; done

            # doe je nog keer read dan zit er niet meer in pipe is dus leeg
            # langs de zendkant heeft hij de pipe afgeslopen
            # langs de zend is hij dus afgesloten 

            # mag zelfde naam zijn want elk process heeft zijn eigen fd 
exec 3>p 

            # in ander venster lezen zal nu blokkeren 
            # pas als je in zendvenster iets ga schrijven 

echo " iets nieuws" >&3
echo " nog iets nieuws" >&3

            # in ontvangszender zal hij dan wel kunnen readen 

            # dus het openen van den ene kant zal blokkeren tot de andere kant ok is 

            # beste manier om vanuit kindprocess data door te sturen naar ouderproces

read -t5    # is timeout zo kan je returnen 

read -t5 lijn <&3 ; echo $lijn $?

            # &? returncode 
            # foutcode 142 -> timeout 

```


Hoofdstuk drie effe zo laten tot na paasverlof


## Hoofdstuk 11: Introduction to shell scripts 

Zie overzichtje slide 

In de eerste fase gaat parser die omleidingen doorvoeren (dus plaats in je opdracht maakt niet uit)

Brace expansion wordt super vroeg gedaan!! Als je het wil gebruiken kan je soms niet om da het zo vroeg is. In andere shells is da veel later (en eigenlijk beter maja bash eh).

## Brace expansion

```sh 

                    # vb brace expansion 

echo {0..8}

echo {0..8..2}      # in stapkes van twee 

echo {000..8..2}    # nullen, vooraan 

echo {a..d}

                    # stel je wil beiden 

echo {000..8..2}{a..d} 

                    # dit maakt alle mogelijke combinaties 


echo {{000..8..2},{a..d}} 

                    # dit geeft unie 

echo {{0..9},{a..f}} 

                    # allee hexa getallen

echo {{0..9},{a..f}}{{0..9},{a..f}} 

                    # allee combinaties van 00 tot ff 

echo honderden{twee,drie,vier,vijf}duizend 

                    # nadeel van de plaats is het volgende 

x=15
y=20

echo {$x..$y}           # dan krijg je letterlijk die string
eval "echo {$x..$y}"    # dan zal hij het wel doen

```


## Tilde expansion 

Hij gaat da mogelijk anders interpreteren 

```sh

cd ~            # homemap 

                # ma je hebt meer aan pushd en popd 
                # behoed u op strings met een ~ want ze worden anders opgevat/geinterpreteerd

```

## Command substitution

Boek is iets te sumier (die fds)

```sh 

ls -l {01..07}

wc -l $(ls -l {01..07})     # vb 

                            # je kan ook vaak tss " " plaatsen 

locate TODO 

wc -l $(locate TODO)        # alle lijnscheidingstekens zijn vervangen door spaties 

                    # kan soms wel kwaad 
                    # allee whitespace wordt vervangen door 
                    # eerste parameter dat in IFS staat (meestal spatie)
                    # wil je da behouden dus dan moet je 

wc -l "$(locate TODO)" 

                    # dan behou je de line endings

                    # : de zinloze opdracht 
                    # while(:) bvb 

ls -l <(:)

                    # je maakt een file descriptor en die verwijst naar een named pipe 

                    # je maakt er dus een om ingelezen te worden 
                    # met de volledige uitvoering van het programma (hier :)

                    # het heeft wel maar een levensduur van de opdrachtregel zelf 
                    # en hij heeft enkel de readpermissie dus 
                    # enkel bedoelt om uitgelezen te worden 

                    # doe je nu 

ls -l >(:)

                    # dan heb je write dus en ist de bedoeling da je er in pushed 
                    # dit is dus process substitution

 head competitors.csv 

 cut -d \; -f1,4 competitors.csv 

 cut -d \; -f4,1 competitors.csv 
 
                    # dus omwisselen, maar da ga nie :| 
                
                    # oplossing 

<(head competitors.csv | cut -d \; -f1 ) 

                    # da ding gedraagd zich nu als een bestand 
                    # het maakt iets tijdelijks aan die zichzelf zal opkuisen

cat <(head competitors.csv | cut -d \; -f1 ) 

                    # bvb ma das wel dwaas 

paste -d \; <(head competitors.csv | cut -d \; -f4 ) <(head competitors.csv | cut -d \; -f1 )

                    # en dan hebde wel u goesting gekregen :j 

cut -d \; -f3 winners.csv | sort | uniq | wc

                    # 501 
                    # je wil join commando simuleren 
                    # dus nummerkes gebruiken 


cut -d \; -f3 winners.csv | sort | uniq | xargs printf ";%d;\n"

                    # elk van die items tss ; geplaatst 

grep -f <(cut -d \; -f3 winners.csv | sort | uniq | xargs printf ";%d;\n") winners.csv 


grep -f <(cut -d \; -f3 winners.csv | sort | uniq | xargs printf ";%d;\n") competitors.csv | wc -l 

                    # 504 ohlala 3 te veel 

grep -f <(cut -d \; -f3 winners.csv | sort | uniq | xargs printf ";%d;\n") competitors.csv | cut -d \; -f2 | sort | uniq -d 

                    # drie nummers 
                    # wie zijn da dan wel 


grep -f <(grep -f <(cut -d \; -f3 winners.csv | sort | uniq | xargs printf ";%d;\n") competitors.csv | cut -d \; -f2 | sort | uniq -d )

                    # dan krijg je overzicht 
                    # overlopers die van nationaliteit veranderen :p 





x=0; wc -l lees tel tien | while read ; do ((x++)) ; echo $x ; done

                    # tellerke tot 4 


x=0; wc -l lees tel tien | while read ; do ((x++)) ; done ; echo $x 

                    # tellerke terug 0 eh ahja want twordt uitgevoerd in een subshell

x=0; wc -l lees tel tien | { while read ; do ((x++)) ; done ; echo $x ; } 

                    # 4 dan dankzij de { }


while read; do ((x++)) ; done < <(wc -l lees tel tien) 
                    
                    # eerste < is omleiding SPATIE (moet) en dan <() van commandsubstitution

echo $x 
                    # is hier nu ter beschikking  


x=0 ; while read; do ((x++)) ; done < <(wc -l lees tel tien) ; echo $x 

                    # OPMERKING

eerste | tweede     # subshell
                    # kan je altijd schrijven als 
tweede < <(eerste)  # huidige shell 


exec {fd}< <(wc -l lees tel tien)

                    # maakt named pipe 
                    # kijk in /proc/1710/fd met ls -l 

x=0 ; while read <&${fd}; do ((x++)) ; done 
echo $x 

                    # 4
                    # mooiste oplossing volgens Moreau 


                    # opmkering over performantie fd 
                    # bij leesoperaties boeit het niet veel hier is het niet noemenswaardig
                    # ma bij schrijfoperaties (uitvoer) zijn fds veel performanter! 


eerste | tweede 
    kan je ook schrijven als 
eerste > >(tweede) 

                    # maar voor goede toepassing te zien voor dit 
                    # da is voor volgende week 

```
