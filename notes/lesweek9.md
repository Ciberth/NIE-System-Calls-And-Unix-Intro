# Week 9: Theorie op 27/04/17

## Exitstatus

Exitstatus als alles ok is, is 0!

$? geeft de exitstatus

De waarden tussen 128 en 256 worden gebruikt voor conditities als de instructies afgebroken worden

kill -l 152
kill -l 130
kill -l 143
kill -l 137

Dus gebruik geen exitstatus groter dan 128


Je mag niet $?==0 op een scalaire manier (overbodig) vergelijken je schrijft
if/while opdracht als argument

```sh

test
[...]   # evenwaardig aan test je roept hier dus een programma (test) op

        # enkele nuttige zaken da je er in kan zetten --> zie slide
        # waslijst aan predicaten dus
        # twee strings vergelijken is eigenlijk via == kijken of beide strings aan patronen gelijk zijn
        # stringA == stringB is dus enkel een letterlijke stringvergelijking als er geen wildcharacters in staan
        # anders vergelijken ze dus patronen

        # je kan ook regexp doen (enige zonder hulpprogrammas die extern zijn)

stringA =~ regexp 

        # mag niet tussen // staan
        # geen " oid gebruiken!

        # je kan dus -nt newer than of -ot older than gebruiken voor timestamps

        # conventie tussen numerieke en lexicale vergelijken zijn omgekeerd als die in perl


        # gebruik [[ ... ]] die maakt het leven veel eenvoudiger!

        # en bij cijfer vergelijkingen gebruik ((...))

        # staat er een $ voor dan:
        # een aantal numerieke gescheiden door kommas
        # gebruik je zonder $ dan doe da bijna hetzelfde behalve da de laatste instructie 
        # geen returnwaarde geeft van de laatste instructie maar wel een exitstatus

$((..., ...))   # geeft returnwaarde van tweede instructie
((...,...))     # geeft een exit code van de laatste instructie


                # vb.


while read      # read geeft exitstatus en zal werken zolang er een lijn beschikbaar is en niet eof tegenkomt

                # dus

while read ; do echo $REPLY ; done < dido 

                # file regel per regel ingelezen


while read ; do [[ $REPLY == *ee* ]] && echo $REPLY ; done < dido

                # dit heeft niets te maken met file globbing!
                # alle strings die aan dit patroon voldoen

                # ofwel aan mekaar plakken met && ...
                # ofwel extended globbing

while read ; do [[ $REPLY == *@(ee|oo)* ]] && echo $REPLY ; done < dido

                # da is tssweg tss gwne globbing en regex

while read ; do [[ $REPLY =~ ([aeiou][^aeiou]*){12} ]] && echo $REPLY ; done < words

                # 12 klinkers 
                # gaat dus op zoek naar lijnen die substring voldoen
                # resultaat: curiositeitenverzamelingen, evangelisatieverenigingen, geheelonthoudersvereninignen

while read ; do [[ $REPLY =~ ([aeiou][^aeiou]*){12} ]] && { echo $REPLY ; break ;} ; done < words

                # nu gaat hem stoppen na da hij curiousiteitenverzamelingen vind 



while read ; do [[ $REPLY =~ ([aeiou][^aeiou]*){21} ]] && { echo $REPLY ; break ;} ; done < words

                # brandverzekeringsmaatschappij


                # [[ -v ]] 
                # kijken of de variabele bestaat of niet 
                # ~> equivalent met de exists in perl!

T[i]            # ~> zonder $ om te checken of da bestaat  


if [[ (test1 || test2 ) && test3 ]] ... 

                # of

if ( [[ test1 ]] || [[test2]] ) && [[test3]] ...

                # de || hebben wel een andere betekenis
                # in eerste is het een or
                # in tweede is het samenplakken van exitstatussen

                # twee verschillende vormen van predikaten aan mekaar kleven
                # syntactisch is het dus anders wie het doet 
                # in eerste vorm is het het test programma
                # in het tweede is het bash zelf

                # de bovenste is eigenlijk efficienter
                # als bash ronde haken ziet dan roept hij een subshell op
                # maak je van de ( ) accolades dan blijf je in dezelfe shell 


if { [[ test1 ]] || [[test2]] ; } && [[test3]] ...

                # merk wel op de ; alltijd na de instructies 

                # ; ik ga onvoorwaardelijk een rij van instructies uitvoeren
                # || doet het voorwaardelijk

                # bij || kan je lazy evaluation doen en heb je verpakte if test 
                # test1 niet uitvoeren en test2 wel dan zal test3 uitgevoerd worden
                # en omgekeerd
                # bij beide false dan zal test3 nie uitgevoerd worden

                # dus nen if kan je schrijven als

cmd && { cmd ; cmd ; ... ; cmd ;} || {cmd ; cmd ; cmd ; }

                # bash kijkt naar het geheel dus 
                # && true block
                # || false block

                # NEN EXIT UIT () (dus subshell) is waardelooos! !!!! EXAMEN
                # exit moet gebeuren in de shell waar je in zit 
                # nie in de subshell die je sowieso verlaat

                # vroeger was case de enige manier om aan patroonherkenning te doen
                # nu zou je denken die case heeft geen recht van leven meer


                # vergeet je de syntax vraag de help

help case 
help for
help while 


case 458 in 
    *0*) echo 0;;
    *1*) echo 1;;
    *2*) echo 2;;
    *3*) echo 3;;
    *4*) echo 4;;
    *5*) echo 5;;
    *6*) echo 6;;
    *7*) echo 7;;
    *8*) echo 8;;
    *9*) echo 9;;
esac


                # uitvoer is dan 4
                # van zodra hij dus 1 vindt die waar is dan stopt em 

                # maar die ;; is nie het enige alternatief da je kan doen





```

## Switch in bash

```sh

# Markdown kan hier misschien nie zo goe mee om xD

case 458 in 
    *0*) echo 0;;&
    *1*) echo 1;;&
    *2*) echo 2;;&
    *3*) echo 3;;&
    *4*) echo 4;;&
    *5*) echo 5;;&
    *6*) echo 6;;&
    *7*) echo 7;;&
    *8*) echo 8;;&
    *9*) echo 9;;&
esac

                # nu krijg je
                # 4
                # 5
                # 8

                # Een derde mogelijkheid is

case 458 in 
    *0*) echo 0;&
    *1*) echo 1;&
    *2*) echo 2;&
    *3*) echo 3;&
    *4*) echo 4;&
    *5*) echo 5;&
    *6*) echo 6;&
    *7*) echo 7;&
    *8*) echo 8;&
    *9*) echo 9;&
esac

                # geeft 4 5 6 7 8 9 
                # dus alles vanaf den eerste true

                # dus drie keuzes en je kan die mengen ook -> nie aan te raden

                # ;;& is alles uitvoeren
                # ;; stoppen als eerste gevonden is
                # ;& alles uiitvoeren vanaf daar
                # 
                # gekke constructies zijn mogelijk!

```

## For in bash

```sh 

for var in ... ; do     
    ...
done 

                # geen $ bij var 
                # den IFS bepaalt hier wa er zal geinterpreteerd worden

for (( ...,... ; ...,... ; ...,... )) ; do 
    ...
done

                # constructie is dan uiteindelijk te vergelijken me nen while 

                # lijn per lijn verwerken

rm -f log
while read lijn ; do ... >> log ; done < bestand 

                # met fdn is beter als je bestanden wil joinen of mergen want anders heb je dubbele while nodig
                # bestanden onafhankelijk openen -> file descriptoren

                # DUS conclusie: vanaf da je twee bestanden simultaat moet verwerken gebruik filedescriptoren!!
                # zeker bij grote bestanden!


exec {fd}<bestand


while read lijn <&${fd} ; do ... ; done 
exec {fd}<&-

                # ZIE SLIDES!!
                # je moet exec zien als een copy maken van rechterargument naar linkerargument

                # bij filedescriptor bestaat << niet
                # bij << bestand ga je bestaande info dus nie verwijderen da kan wel


                # WAARSCHIJNLIJK EXAMEN, herharling, veel vragen herhaald, 
                # duidelijk voorkeur DOEN KENNEN DOEN!!!!!!!!!


                # zie slides
                # verwerken string teken per teken is gefoefelen!!! 
                # eerste stuk die while
                # beter is die for maar nog steeds nie ideaal

                # <<< kan je gebruiken --> lezen uit nen string

while read -n1 char ; do 
... ; done <<< "$string" 

                # meest efficiente manier om nen string te manipuleren!!! 

                # vb 

x=$(tail -1 dido)

echo $x

                # Keep here your watch, and never part.

while read -n1 ; do echo $REPLY ; done

                # nu verwacht hem vanop standaardinvoer

while read -n1 ; do echo $REPLY ; done <<< "$x"

                # " " voor lijnscheidingstekens enzo hij vervangt leden van IFS door een spatie


                # lijn per lijn verwerken 


opdracht | { while read lijn ; do 
...
done
...
}

                # tss { } om die variabele die je aangepast hebt in done blok da je die nog nie kwijt bent 
                # anders is alles weg

                # makkelijker en handiger

while read lijn ; do ... ; done < <(opdracht)

                # process substitution


                ### FILE DESCRIPTOREN EN PROCESS SUBSTITUTION ZIJN BELANGRIJK VOOR EXAMEN
                # je vind daar weinig over
```

## Mktemp

```sh

                # tijdelijke bestanden maaken via mktemp

mktemp 123XXX3456XXXX 

                # hij zoekt naar laatste reeks van xn en daar gaat hem random stuff invullen
                # hij geeft op standaarduitvoer het bestand en hij heeft het gratis getouched


x=$(mktmp -u 123XXX3456XXXX)
echo $x

                # nie vergeten vuiligheid op te kuisen
                # tijdelijke map kan ook via -d 

                # TRAPS !!! interessant

                ## Schrijven van scriptje

                # t van tabel
                # # nie verwarre me perl in perl laatste index 
                # hier aantal elementen (verschilt een)

i=0 ; while ((++i)) ; do t=($(factor $i)) ; ((${#t[@]}==2)) && echo $i ; done



( i=0 ; while ((++i)) ; do t=($(factor $i)) ; ((${#t[@]}==2)) && p=$i ; done ) &

kill %

kill -l 

                # twee signalen die dienen voor trap
                # signalen 10 en 12 

                # dus '' code die je binnenkrijgt als je 10 binnenkrijgt

(trap 'echo priem\($n\)=$p' 10 ; i=0 ; n=0 ; while ((++i)) ; do t=($(factor $i)) ; ((${#t[@]}==2)) && { p=$i ; ((n++)) ; } ; done ) &




(trap 'echo na $((SECONDS-s) priem\($n\)=$p' 10 ; i=0 ; n=0 ; s=$SECONDS ; while ((++i)) ; do t=($(factor $i)) ; ((${#t[@]}==2)) && { p=$i ; ((n++)) ; } ; done ) &

kill -10 %

                # geeft dan na 12s priem(291)=1901
                # geen io s!!

                # wil je nu da processen stoppen 
                # beleefd: kill -2
                # iets meer nadruk: 15
                # kill -9 # keel over
                # 9 kan je ook nie opvangen

                # 2 en 15 is meer voor achtergrondprocessen/ daemons en dan wil em schoon afsluiten en verwijderen en netjes proberen afsluiten
                # ^C kan ook opgevangen worden

kill %          # dan gaat het eruit maar hem niets verteld wa zijn huidige toestand was
                # je kan dus zoveel signaalhandlers schrijven da je wilt



(trap 'echo na $((SECONDS-s) priem\($n\)=$p' 10 ; i=0 ; n=0 ; s=$SECONDS ; while ((++i)) ; do t=($(factor $i)) ; ((${#t[@]}==2)) && { p=$i ; ((n++)) ; } ; done ) &

kill -2 %

                # en tis eruit 
                # de netste manier

(trap 'echo na $((SECONDS-s) priem\($n\)=$p' 10 2; i=0 ; n=0 ; s=$SECONDS ; while ((++i)) ; do t=($(factor $i)) ; ((${#t[@]}==2)) && { p=$i ; ((n++)) ; } ; done ) &

                # reageer op dezelfde manier als 10

kill -10 %
                # hij zegt het u 

kill -2 %

                # hij zegt het u nog en draait nog altijd

                # je hebt het killen eigenlijk vermeden

kill -15 % 

                # dan zal hij da doen zonder meer

(trap 'echo na $((SECONDS-s) priem\($n\)=$p' 10 2; trap '' 15 ; i=0 ; n=0 ; s=$SECONDS ; while ((++i)) ; do t=($(factor $i)) ; ((${#t[@]}==2)) && { p=$i ; ((n++)) ; } ; done ) &

                # da is de conventie trap '' 15 om te zeggen doe niets maar reageer er ook nie op 

kill -2 %

kill -10 %

kill -15 %

                # hij zegt niets en heeft process ook niet gekilled
                # "ik maag mezelf ongevoelig voor die killsignalen"

                # kill -9 kan je NIET opvangen --> sowieso eruit
                # je kan ook nie iets nuttig vertellen!

kill -9 %

                # bij tijdelijke bestanden moet je dus alle redenen opvangen om u tijdelijke bestanden te verwijderen
                #--> gebruik signaal 0

                # 0 --> alle redenen wrm men programma beindigd
                # niet echt een signaal eigenlijk eerder een pseudosignaal
                # om wa voor reden ook (behalve 9) voer dan ... uit vooraleer het beindigd word
                # om op te kuisen


trap 'echo na $((SECONDS-s) priem\($n\)=$p' 10 2; trap '' 15 ; i=0 ; n=0 ; s=$SECONDS ; while ((++i)) ; do t=($(factor $i)) ; ((${#t[@]}==2)) && { p=$i ; ((n++)) ; } ; done 

                # in foreground lopen 

                # ^C voeren ga nie 
                # je kan kill -9 nie sturen dus --> andere terminal

pstree -p | grep bash


```


