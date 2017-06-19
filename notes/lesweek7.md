# Week 7: Theorie op 30/03/17

## Command substitution

Overdrijf daar nie mee, het is echt bedoelt voor **externe** commandos


```sh
x=17
y=$(echo $x)            # niet goed 
y=$x

y=$(printf "%06d" $x)   # ook hier ga je nieuwe bashshell gebruiken om daar intern command in te voeren
echo $y                 # dat is jammer, vaak hebben die commandos een omweg om da te vermeiden
                        # bij printf is da de -v 

x=545
printf -v y "%06d" $x   # zonder de omweg van command substitution
echo $y

```

Het kan dus vaak vermeden worden!

Een tweede is **process substitution**.  <(..)

(= omleiden naar tijdelijke files vermijden)

```sh
<(expr)>(expr)

shuf -rn120 -e {a..z} | xargs -n 6 | tr -d ' '


shuf -rn120 -e {a..z} | xargs -n 6 | tr -d ' ' | tee a b c | nl 

            # opgesplitst in 4 kanalen 3 ervan naar bestandjes 

shuf -rn120 -e {a..z} | xargs -n 6 | tr -d ' ' | tee >(grep -n a ) | nl 

            # vaak ga je dan omleiden naar een bestandje 


shuf -rn120 -e {a..z} | xargs -n 6 | tr -d ' ' | tee >(grep -n a > a) >(grep -n b > b) >(grep -n c > c) | nl > d 

            # 1 keer uitgevoerd 4 kanalen naar 4 bestanden 

echo '' > x 
cat a x b x c 

            # zo zie je ze mooi onder mekaar met lege lijn tussen 

paste d <(cat a x b x c)

``` 

## bash functies 

```sh
            # functie syntax
f () { }

f () { wc -l tel lees ; }

            # vergeet de ; niet 

            # oproepen via 
f 

            # met parameters 

f () {echo $2 $1; }

f eerste tweede derde 

            # in principe is dit by value 
            # maar je kan dit omzeilen 

            # returnwaardes zo goed als onbestaand ; je kan 1 terug geven nen int 

f () {echo $2 $1 ; return 200 ; } 
f ; echo $? 

            # geeft 200 


f () {echo $2 $1 ; return 300 ; } 

            # geeft 44 

f () {echo $2 $1 ; return -1 ; } 

            # geeft 255 

            # er wordt dus modulo 256 gedaan 


f () {echo tijdens: $x ;}
x=ervoor
echo ervoor: $x ; f ; echo erna: $x  

            # blijft telkens mooi hetzelfde 
            # stel functie veranderen naar 

f () {x=aangepast ; echo tijdens: $x ;}
echo ervoor: $x ; f ; echo erna: $x  

            # ervoor: ervoor 
            # tijdens: aangepast 
            # erna: aangepast 

unset x 
echo ervoor: $x ; f ; echo erna: $x  

            # dan is x letterlijk leeg ervoor 

            # omzeilen via declare of local 
            # (= in functie zelfde betekenis als declare )

f () {declare x=aangepast ; echo tijdens: $x ;}
x=ervoor
echo ervoor: $x ; f ; echo erna: $x  

            # ervoor: ervoor 
            # tijdens: aangepast 
            # erna: ervoor 

            # zo is je variable niet "kapot" 
          
            # overzicht van alle functies die gedeclared zijn 

declare -F  # enkel de naam niet de inhoud 
            # yum, git 

declare -F | grep -v -e _yu 

            # _gi

declare -fp _userland 
declare -fp _xfunc 
declare -fp _tilde 

            # functies kunde nie vanuit kindshell naar boven exporteren 
            # omgekeerd kan wel maar daar zijde eigenlijk niets mee eh  

help source # synoniem voor . 

            # dus . kjkjk # zal uitvoeren van source commando 
help .      # wel laten volgenen door spatie 

f           # wil je bvb weg dan doe je  

unset -f f 
f           # bestaat niet meer 
```


## Variabelen 

```sh 

x=abcdefghijklmnopqrstuvwxyz 

declare y=abc       # precies hetzelfde 

echo $y 

                    # gebruiken is $ assigneren is zonder $ 

declare -x y =abc   # om te gebruiken in kindshellen 

declare -u y=abc    # attribuut uppercase meegeven
echo $y             # ABC 
y=oiuhjqsdrHJQSKDJSDqsdjqjs 

                    # echo zal nu allemaal caps zetten 

                    # bash loopt achter, andere shells zitten voor op da vlak 
                    # vb rechts aligneren 

                    # var leegmaken en var stuk maken 
                    # zijn twee verschillende dingen 

echo $y 
y=                  # lege inhoud 
echo $y 

unset y 
echo $y             # krijg je ook niets maar da kan je opvangen met optie 
                    # da je enkel kan werken op ingevulde vars 

                    # twee verschillende testen tussen ingevuld / defined 

y=iets 

z=343 

z+=57

echo $z  
                    # 34357 je doet dus een stringconcatenatie 

((z+=57))
echo $z             # 400

                    # ander soort substitutie 

                    # het read commando wordt ook vaak gebruikt om variabelen in te vullen 
                    # opties maken u leven eenvoudiger!!

                    # geef je niets aan dan komt het van standaardinvoer (interactief)

read < <(...)       # <(...) gedraagt zich ook als bestand eh merk op de spatie!! 

read <<< "$x"       # lezen van nen var tss " " als je lijnscheidingstekens wil respecteren en 



head competitors.csv 

read < competitors.csv 

                    # je ziet niets maar hij heeft wel iets gedaan 
                    # vergelijkbaar met $_ bestaat er REPLY

declare -p REPLY    # beter dan echo -> declare -p die interpreteerd niet! 

                    # eerste lijn dus 

read a b c < competitors.csv 

                    # conventie is dat invoerlijn wordt geparsed 
                    # de laatste wordt altijd gebruikt om den overschot te pakken 
                    # a = CHMELAR 
                    # b = al de rest 
                    # parsing was dus op whitespace 

                    # mogelijkheid is om IFS te wijzigen maar je moet die altijd terugzetten 
                    # bewaren en terugzetten moede dan doen --> maar das omslachtig 

declare -p IFS      # nu zie je da nie 

hexdump -C <<< "$IFS" 

                    # vo te zien wa er zit 20 09 0a 

                    # EXAMEN!! 

IFS=\; read a b c < competitors.csv 

                    # deze heeft maar nen impact op deze enkele regel 
                    # tijdelijk instellen op ; 

declare -p a 
declare -p b 
declare -p c 

                    # te weinig vars opgegeven en de laatste ga altijd weglopen met de rest !! 

                    # stel je wil ifs wijzigen in een blokje van twee lijnen 

{read a b c < competitors.csv ; read a b c < competitors.csv ; } 

                    # je leest wel terug de eerste lijn :/


IFS=\; {read a b c < competitors.csv ; read a b c < competitors.csv ; } 

                    # mag dus niet want tis een samengestelde opdracht 

                    # omzeilen door functie 


f() {read a b c < competitors.csv ; read a b c < competitors.csv ; }

IFS=\; f            # en werkt perfect 

echo $x 

y=iets              # geen spaties 
y= iets             # syntax zoekt hij de opdracht iets en daarvoor stel je y in op niets 

y =iets             # je voert y uit met als parameter met =iets 


read y              # prompt zal nie terugkomen 

read -n10 y         # dan kan je invoer geven en zal het er in staan 
                    # na het tiende karakter sluit ik af hij kijkt dus nie 
                    # naar scheidingstekens tenzij da je vroeger entert 

read -N10 y         # nu ga hij vroeger ook nie stoppen # IK WIL TIEN KARAKTERS

declare -p y 

read -t10 y         # read met nen timeout 

read -d; y          # intik tot ; 


IFS=, read -d\; a b c d 

                    # hij zal geparsed worden op , na een ; 
                    # invoer is bvb 000,111,222,333,,,^
                    # dus ge sluit u invoer af met ; 

declare -p a 
declare -p d 


echo $x             # eerste letter van 

read -n1 y <<< $x 
echo $y 

exec 3< <(echo $x) 
read -n1 y <&3 ; echo $y 
read -n1 y <&3 ; echo $y 
read -n1 y <&3 ; echo $y 
exec 3<&- 

                    # is via fds 

echo $x 

echo ${x}0000

echo ${#x}          # geeft lengte van de string 

echo ${x#*e}        # eet stuk vooraan op 

echo ${x%*e}        # zoekt patroon waar string eindigt op e 

echo ${x%e*}        # alles vanaf de e weg 

y=abcde0fghijk0lmnq 

echo ${y}

echo ${y#*0} 

                    # let op zuinig <> greedy --> het is de zuinige manier 
                    # patroon zo zuinig mogelijk invullen
                    # greedy is via ## en %%

echo ${y##*0}       # het herhalen maakt er dus greedy van 

declare -p PWD 

pushd /etc/sysconfig/network-scripts/ 


declare -p PWD 

                    # we willen nu de oudermap bekomen bvb

echo ${PWD%/*}      # niet greedy en alles behalve laatste patroon (laatste patroon kwijt dus)

echo ${PWD#${PWD%/*}/} 

                    # gefoefel 
                    # vanvoor stuk opeten en vanachter stuk opeten 

                    # alternatief via greedy is iets leesbaarder geworden 

echo ${PWD##*/}


y=$(grep -e oo -e ee dido)

declare -p y 

                    # we willen alle oo s vervangen door iets anders 

echo ${y//oo/}      # // staat voor vervangstring zoeken en daarna door wa je wil vervangen hier dus leeg 

echo ${y//oo/@@} 


echo ${y/oo/@@}     # doe je maar 1 / dan doet hij het maar 1 keer  // is dus voor globale substitutie 

                    # stel je wil twee substituties tegelijk te doen -> extended globbing en zoek faciliteiten versterken elkaar

                    # EXAMEN 

echo ${y//@(oo|ee)/@@} 



y=abc0000def000xyz 

                    # begin en eind van string het ^ en $ dus 

                    # /# is dus patroon dat vooraan in de string staat
                    # /% is patroon voor achteraan de string

y=abc0000def00xyz 


echo ${y//0}

echo ${y/*(0)/}     # u patroon laat ze toch staan,
echo ${y/*(0)/-}    # dan zie je vooraan -
echo ${y/+(0)}      # dan wel ok 

echo $y 

echo ${y-default}   # hij laat het met rust want string is ingevuld 

unset y 
echo ${y-default}   # dan gaat hij y invullen met default 

                    # maar enkel als de variabele niet bestaat! 
                    # is hem leeg dan zal hem ook me rust laten 

                    # wil je dit ook bij lege strings gebruik dan 

echo ${y:-default}  # dus hier enkel me rust alst daadwerkelijk met iets is ingevuld 

y= 
echo ${y:-default}
                    # maar 
declare -p y        # hem heeft da nie gewijzigd 

${y:=ls}            # hij gaat de aanpassing doen en dus het commando uitvoeren 
                    # vaak wil je da wel nie 

echo $y             # geeft ls 


                    # EXAMEN


: ${y:=ls}          # gebruik leeg commando maar die parameter 
                    # dwingt u de parameter in te stellen !! 

                    # dus nu geeft
echo $y             # ls 

                    # de manier om variabelen in te stellen 

: {y:=ls} ${z:=ddfdf} 

echo ${y:+iets}     # inverse van - dus gebruik iets als y ingevuld is 

                    # enige vb da we kunne denken is als soort accumulator 

cat tel             # en je wil al de woorden aan mekaar kleven 

for x in $(cat tel) ; do echo $x ; done 

s= ; for x in $(cat tel) ; do s+="-"$x ; done ; echo $s 

                    # scheidingsteken sta ook in den eerste  


s= ; for x in $(cat tel) ; do s+=${s:+"-"}$x ; done ; echo $s 

                    # bespaart u weer nen if test 
                    # die leading - zal dus weg zijn want s is nog nie ingevuld 
                    # :+ leeg en onbestaand wordt op dezelfde hoop gesmeten 

: ${s?iets}

unset s 

: ${s?iets}
                    # bash maakt van zijn oren 
                    # middel om zeker te zijn of iets bestaat 
                    # en je krijgt vermelding van welke variabele er niet bestaat 

: ${s:?iets}
                    # zal dan de lege string ook meepakken 
                    # zo n constructie vervangt een if 

: ${s:?$LINENO}
                    # geeft output bash: s: 462 # zinvol in een script 

echo ${x}

x=$(cat tel)


echo ${x^}

echo ${x^^}^        # alles naar uppercase # probeer da maar te onthouden 

echo ${x^^[aeiou]}  # alle klinkers worden dan naar upper case gedaan


echo ${x^^[^aeiou]}

x=abcdefghijklmnopqrstuvwxyz

echo ${x:5:7}       # van positie 5 tot 7 

echo ${x:5:-7}      # vanaf 5 maar de 7 laatste niet 

echo ${x:-15:-7}    # geeft dan volledige string omdat :- de default waarde 
                    # als var nie ingevuld is en x is ingevuld dus in dit geval 
                    # ge moet SPATIE zetten of tss ()

echo ${x:(-15):-7}

                    # of

echo ${x: -15:-7}

a=1
b=2
c=3

y=b 

echo ${y}           # geeft u de string b en je wilt eigenlijk referenties/pointer

echo ${!y}          # geeft dan 2

y=c 
echo ${!y}

L=a 

echo ${!L}


echo ${!L*}

                    # geeft u L LANG LESSOPEN LINENO LINES ... 
                    # overzicht van alle variabelen die beginnen met 

echo ${!LI*}        # of 
echo ${!LI@}



                    # functie dat kwadrateert 

kw () { : ; }

a=10

kw () { echo $(($1*$1)) ; }

kw 10 

kw a                # ok 
echo $a             # is nog steeds 10 en we willen by reference eigenlijk de inhoud veranderen 

kw () {echo $1 ;}

kw a 


kw () { echo $1 ${!1} ; }
kw a                # geeft a 10 


kw () { echo $1=$((${!1}*${!1})) ; }

kw () { eval $1=$((${!1}*${!1})) ; }

a=10

kw a 

echo $a             # 100 

                    # eval ga hem dan echt gelijk stellen en wijzigen

```



