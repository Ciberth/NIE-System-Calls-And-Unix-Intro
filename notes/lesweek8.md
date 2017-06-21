# Week 8: Theorie op 20/04/17













## Arithmetic substiturion/expansion

```sh

$((..., ... , ...)) # waarbij elke ... een integer bewerking is 
                    # merk ook op dat je geen ; gebruikt maar , voor het scheiden van instructies


echo $((pi=22/7,bpi=335/113,bpi-pi)) 

                    # returnwaarde van laatste zal hij geven hier het verschil

                    # geeft -1 dit is een onverwacht resultaat
                    # omdat hij overal met integers werkt



echo $((pi=2200000000/7,bpi=33500000000/113,bpi-pi))

                    # geeft -12642

echo $pi 
echo $bpi           # zijn beide beschikbaar 

echo $((024))

                    # octaal geeft 20

echo $((029))       # geeft error
echo $((0x29))      # geeft 41
echo $((3#21022))   # geeft 197
echo$((36#54sgz65)) # geeft groot getal

echo $((62#a))      # is 10
echo $((62#A))      # is 36

                    # grootste da je kan doen is 64 
                    # da is alles daarnet (kleine en grote letter) + @ en _

echo $((64#_))      # geeft 63

echo $((64#_@ * 3))

echo $((3*$pi))
                    # gelijk aan
echo $((3*pi))


                    ### oproepen van scripts 
                    # er is geen limiet aan aantal parameters
                    # als je je script oproept met bash script parameters 
                    # dan kan je je parameters maar in beperkte mate beinvloeden
                    # dit via set

set aap noot wim    # zo komt aap in $1, noot in $2
echo $2

cat tel             # tien regetjes van een tot tien

set $(cat tel)      # onthou enkel () opdracht zal uitgevoerd worden alsof aparte opdracht is 
echo $1
echo $10            # kan niet dan krijg je een0
echo ${10}          # geeft wel correct tien

wc words            # bevat alle nederlands talige woorden met 200000 woorden
set -- $(cat words) # 200000 parameters dus

                    # TIP: aanraden geef -- mee !!!!!!!
                    # dit is om te vermijden dat alles als parameters moeten opgevat te worden
                    # anders zou er soms een optie kunne meegegeven worden wa nie bedoeling is
                    # -- zegt da is nie het geval

tail words
echo ${178430}


set -- $(cat tel)   # altijd als je gebruik maakt van set dan 
                    # vertrek je vanaf nul dus de rest is hier nu allemaal weg

echo $1 ${10}

                    # een tien

shift               # zonder parameter
                    # je neemt eerste parameter weg en boel opschuiven

echo $1 ${10}
                    # geeft enkel twee
echo $1 $9
                    # geeft twee en tien

shift 3

echo $1 $6
                    # vijf en tien

                    ### LET OP ADDERTJE komt straks aan bod


echo ${6^^[aeiou]}

                    # geeft tIEn

                    # @ staat eigenlijk voor de gehele parameterlijst

echo ${@}           # gehele actuele parameterlijst

echo ${@^^[aeiou]}
                    # overal op toegepast

                    # bash is een vat vol incosistenties

echo ${#@}          # je zou verwachte da je lengte van alle strings (parameters) zou krijgen
                    # je krijgt echter een andere interpretatie en je krijgt het aantal parameters
                    # en dus ook laatste index van je parameterlijst = index van laatste parameter
                    # dit is ook hetzelfde als
echo $#



echo ${@:2:2} 
                    # geeft zes zeven
                    # het gaat in de volledige lijst de tweede parameter er zoveel tonen
                    # dus toon den tweede en de volgende (in totaal twee)

echo ${@:-2:2}
                    # geef me parameterlijst vanaf vanachter geteld met lengte twee
                    # negen en tien

echo ${@:-3:-2}
                    # da mag niet die derde parameter mag niet negatief zijn !! 

                    ## STEL JE WIL SPECIFIEKE PARAMETER WIJZIGEN !!!!! EXAMEN

set -- $(cat tel)

echo ${@}

set -- ${@:1:5} "iets anders" ${@:6}

echo ${@}

```

## Lussen

```sh

            # while lus kan je gebruiken maar is een destructieve manier 

while [[ "${@}"]] ; do echo $1 ; shift ; done

            # is eigenlijk een test ; dus ZOLANG parameterlijst gegevens bevat DAN
            # NADEEL is dus da je alles nu wel kwijt bent

set -- $(cat tel)

            # dit komt overeen met de foreach van perl

for x in "${@}" ; do echo $x ; done 

            # nummertje van argument ben je wel kwijt
            # wil je da nummerke dan heb je enkel klassieke for lus

            # eigenlijk speciale vorm van arithmetic expension

for ((i=1;i<=$#;i++)) ; do echo $i ; done 

            # merk weer op da je $i niet moet schrijven maar i mag omda het toch een cijferke is

for ((i=1;i<=$#;i++)) ; do echo $i ${@:i:1} ; done 

            # of andere manier via ! (da pointermechanisme)

for ((i=1;i<=$#;i++)) ; do echo $i ${!i} ; done 


            ## STEL JE WIL DE VIJF LAATSTE PARAMETER BEKOMEN

set -- $(cat words)

echo ${@:-1:1}

            # geeft zworen

echo ${@:-100:1} 

            # 99e laatste woord



while [[ "${@}"]] ; do echo $1 ; shift 2 ; done
            
            # geen probleem geeft per 2 dan natuurlijk

            # weer bevolken


while [[ "${@}"]] ; do echo $1 ; shift 3 ; done

            # geeft oneindige lus (geen veelvoud van 3)


shift 3 ; echo ${@} 

            # zal altijd shift 3 doen tot hij niemeer kan EN DAN DOE HEM NIETS de stommerik
            # bvb zit enkel tien in dan doe je shift 3 dan blijft er tien in zitten

shift 3 ; echo $? 

            # foutcode is $?
            # dus eerste paar keer 0
            # laatste keer krijg je 1 dus hem is nie gebeurd 


set -- ${@:-...} 

            # ookal is er niets opgegeven van parameters doe alsof dit de parameters zijn

            # twee soorten tabellen en lijken op hashes van perl
            # enerzijds de geindexeerde en anderzijds de associatieve tabellen

t[5]=aap
declare -p t

t[8]=beer
declare -p t

            # meerdere indices tegelijkertijd

t=([2]=kat [7]=hond) 

            # je definieert de tabel volledig opnieuw
            # wil je dat de oude bewaard blijven dan 
            # moet je de += notatie gebruiken

t+=([2]=kat [7]=hond) 

            # EXAMEN

declare -p t

t+=(vogel vis) 

            # ik ga tabel wijzigen en behou alles wat ik had dus nu ga je achteraan toevoegen

t+=($(cat lees)) 

            # let op het verschil tss de soorten () () de een is command substitution de andere tabelwijziging

declare -p t 


t+=([0]=mens [3]=kanarie)

            # verwijderen

unset t[2]  # ok
declare -p t

unset t[5]  # ok 
declare -p t

unset t[3]  # nok 
declare -p t 

            # kanarie blijft staan
            # wat is er hier mis
            
            # hij heeft een ls gedaan en daar staat er een t3

unset t[3]  # er wordt aan fileglobbing gedaan 
            # is er een file die hier aan voldoet 

            # GEBRUIK DUS ALTIJD "" !! EXAMEN !!

unset "t[3]"

                # zo verhinder je file globbing

                # ook bij die while "${@}" doen zoda "iets anders" geen problemen geeft en maar 1 parameter blijft !! 

echo ${t[26]}   # indexen
echo ${t[260]}  # bestaat hem nie dan krijg je blanco (niet een fout)


unset t[260]
                # ook geen fout

echo "${t[@]}"  # !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                # krijg je alles na mekaar


echo "${!t[@]}" 

                # !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                # zo krijg je volledige lijst van al uw indices
                # de keys van een hash in perl 
                # de exists van perl wil je wellicht ook

```

## Test [[]]

```sh

                # van specifieke index willen we weten bestaat hem of niet

[[]]            # zelfde als test 
                # -v en daarna naam van variabele

[[ -v x ]] && echo bestaat || echo bestaat niet

declare -p x
unset x 
[[ -v x ]] && echo bestaat || echo bestaat niet


[[ -v t[8] ]] && echo bestaat || echo bestaat niet

[[ -v t[6] ]] && echo bestaat || echo bestaat niet

                # is bijgevolg de exists van in perl

                # nu willen we de tabel inverteren

                # associatieve tabel als het ware


for i in ${!t[@]} ; do echo $i ; done

                # lijstje van al de indices



for i in ${!t[@]} ; do  ${t[i]} $i ; done


for i in ${!t[@]} ; do inv[${t[i]}]=$i ; done

declare -p inv

                # ga dus nie goe
                # je moet a priori zeggen da u tabel string geindexeerd mag zijn
                # da doe je via

declare -A inv  # let wel op je kan nie converteren dus door ons ding hierbove besta inv al 
unset inv

declare -A inv

for i in ${!t[@]} ; do inv[${t[i]}]=$i ; done

declare -p inv


echo ${inv[@]}

echo ${!inv[@]}


echo ${inv[beer]}

y=8
echo ${t[y]}
                # krijg je beer

x=beer
echo ${inv[x]}

                # hij zoekt index met string x

echo ${inv[$x]}

                # dan krijg je 8 
                # gebruik dus eig steeds $ 

echo ${inv[@]}


echo ${"t[@]"}

declare -p t 


echo ${t[25]}
                        # weide
echo ${t[25]^^[aeiou]}
                        # wEIdE
echo ${t[@]^^[aeiou]}
                        # ook ok van alles dan

                        # !!!!!!!!!!!!!!!!
echo ${#t[@]}           # je zou verwachten lengtes van elk van die strings
                        # nee je krijgt het aantal effectief ingevulde elementen !! 
                        # (niet laatste index eh!)

echo ${#inv[@]}         # ook 23

declare -p inv

echo ${inv[@]:4:2}      # 8 en 28 
echo ${inv[@]: -2}      # 21 0

declare -p t

echo ${t[@]: -1}        # schapen goed
echo ${t[@]: 5:1}       # je verwacht kat maar je krijgt beer
echo ${t[@]: 4:1}       # weer beer
echo ${t[@]: 8:1}       # beer 
                        # je krijgt eerste element waarvan index hoger of 
                        # gelijk is aan wat je opgegeven heeft hier is [8]=beer
                        # M -> zinloos


t=([1]=een [2]=twee [4]=vier [8]=acht [16]=zestien)

echo ${t[@]: -1:1}
echo ${t[@]: -2:1}
echo ${t[@]: -8:1}
                        # allemaal zestien
echo ${t[@]: -9:1}
                        # acht

unset t 
declare -A t

t=([1]=een [2]=twee [4]=vier [8]=acht [16]=zestien)

declare -p t 

                        # nu heb je volgorde nie in de hand
echo ${t[@]: -1:1}      # acht 
echo ${t[@]: -2:1}      # vier 





head competitors.csv
read x < competitors.csv

echo $x 

unset t 
read -a t < competitors.csv 

                        # je gaat het dus niet in variabele inlezen maar in een tabel 

declare -p t 

                        # hem heeft nu op standaardscheidingstekens gedaan
                        # opl

IFS=\; read -a t < competitors.csv

declare -p t

echo ${t[3]}



unset t 

wc -l competitors.csv
                        # 2406

                        # NIEUW !!!!!!!
                        # tabel t ga gemaakt worden
                        # geef je niets dan verwacht hij invoer van standaardinvoer

mapfile t

                        # stoppen met ctrl D

                        # standaard zit scheidingslijn erin dit wegdoen (de chomp van perl) is -t 

mapfile -t t < competitors.csv

                        # ipv standaardinvoer van bestand

declare -p t

cat dido

grep -E \([aeiouy][aeiouy].*\){4} dido 

                        # vier keer opeenvolgende klinker op de lijn


                        # ZEER TOEPASBAAR EXAMEN !!!! NIEUW !!! 

mapfile -t t < <(grep -E \([aeiouy][aeiouy].*\){4} dido)

                        # dat reageert nu als bestand <() niet $() anders krijge we op commandline

declare -p t 

                        # elk van de lijnen zijn nu tabellen 

                        # voor aan te vullen via mapfile (snotparameters)

mapfile -s -n -O -t 

                        # SNOT !!!! 


mapfile -s 100 -n 5 -O 10 -t t < competitoris.csv

                        # -s 100 eerste 100 interesseren mij niet 
                        # -n 5: vijf lijnen vertrekkende van 100e offset 
                        # -O 10: elementen die nie in tabel staan nie overschrijven er

                        # zie man pages ^ fuzzy beschrijving



echo $SECONDS

s=$SECONDS

echo $((SECONDS-s))
                        # 32

                        # $ zijn weer weg omda we enkele numerieke waarden verwachten


grep ee dido | sort | nl
# vind 22 lijnen
echo $?                 # geeft nu 0 dus opdracht is correct uitgevoerd

grep aa dido | sort | nl 
                        # vind niets
echo $?                 # geeft toch ook 0
                        # de exitstatus geeft enkel da van de laatste dus van de nl 
                        # dus grep was wel niet nul maar sort en nl wel
                        # dus soms gedetailleerde exitstatus opvragen

declare -p PIPESTATUS 

                        # en dan zie je een tabel met grootte van het aantal commando's (ofwel aantal pipes -1)

                        # hier zie je dan 1 0 0 

                        # dus je moet dan testen op PIPESTATUS

(( ${PIPESTATUS[0]} > 0 )) && echo niet gevonden || echo wel gevonden 


                        # !! EXAMEN !!

``` 