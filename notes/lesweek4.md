# Week 4: Theorie op 09/03/17

## Nog enkele filtercommandos

Naast head bestaat ook tail

```sh

cat tien                    # tien lijnen

tail -n 4 tien              # toont laatste vier lijnen

tail -n +4 tien             # geef me alles vanaf de vierde lijn van het bestand

head -n 3 tien

tail -n +3 tien             # de twee stukken hebben een gemeenschappelijke lijn (de drie)

head -n -3 tien             # alles behalve de laatste drie lijnen

tail -n 3 tien              # hier heb je geen overlap (hier is de zeven er niet bij, bij de vorige wel)

tail -n +3 tien | head -n 2 # dan krijg je 3 4 dus vanaf 3 (offset) in grootte 2 

wc                          # telt aantal woorden, lijnen, bytes

nl                          # alternatief met cat maar traditioneel gebruik je nl

                            # twee opties zijn interessant bij nl

nl dido                     # lege lijnen worden niet genummerd

nl -ba didi                 # nu wel 

nl -ba -nrz dido            # vast formaat voor naverwerking


                            # cut interesant als je al je whitespace vervangt door 1 enkele whitespace

head -20 dido | nl                  # dan is het vervelend da er white space tussen staat
head -20 dido | tr 'a-z' 'A-Z'      # translate voor conversie, dus mapping van kleine letter naar grote letter 
head -20 dido | tr 'aeiou' '.....'  # of
head -20 dido | tr 'aeiou' ':.'     # merk op da de a op : wordt gemapt en de rest (eiou) wordt gemapt op .

                            # we willen nu da de whitespaces samengeperst wordt tot 1 whitespace

head -20 dido | nl | tr -s ' \t' ' ' 

                            # nu kan je dat dan deftig gebruiken 

                            # je kan cut ook op kolommen gebruiken (niet enkel velden), 
                            # veel andere commandos heb je daar nie voor

                            # bvb nen ls die in kolommen staat
                            # bvb van char 2 tot 9 en dan stukje verder

ls -l

                            # -c voor chars gevolgd door welk van je kolommen
ls -l | cut -c 2-9

ls -l | cut -c 2-9,40-      # alles tot einde
ls -l | cut -c 2-9,30-      # wat je niet mag doen is die volgorde omkeren

head c                      # skiers en je wil kol 1 of 3 (da was nen csv)

cut -d \; -f 3 1 < c        # dienen vlieger ga nie op hij geeft ze gelijk hij ze heeft ingelezen


                            # dus cut vooral interessant als je met kolommen werkt in een vaste formatering

                            # stel je wilt 1 kol niemeer hebben

cut -d \; -f 2 --complement < c 

                            # strings gebruiken we voor printable chars op te sporen



                            # od: dump voor binaire gegevens
                            # alternatief voor hexdump merk op dat hun opties niet overeen komen

                            # sort -c optie controleert of invoer gesorteerd is
                            # interessant voor uniq en join worden gebruikt want die gaan er van uit dat het gesorteerd is
                            # voorwaardelijk testen is beter en vraagt minder rekenwerk

paste w c | head            # winnaars en competitors


join -t \; -1 3 -2 2 -à 2.1 # delimitter en uit eerste file derde kol, uit tweede twee

                            # nu krijg je reeks van iedereen die ne keer gewonnen heeft

join -t \; -1 3 -2 2 -à 2.1 | uniq              # geen goed idee je MOET er voor zorgen da hij gesorteerd is
join -t \; -1 3 -2 2 -à 2.1 | sort | uniq       # overzicht
join -t \; -1 3 -2 2 -à 2.1 | sort | uniq -u    # welke komen maar 1 keer voor
join -t \; -1 3 -2 2 -à 2.1 | sort | uniq -d    # welke komen meerdere keren voor
join -t \; -1 3 -2 2 -à 2.1 | sort | uniq -c    # tel 

join -t \; -1 3 -2 2 -à 2.1 | sort | uniq -c | sort -nr | head -10

                            # dan krijg je top tien met aantal
                            # uniq -c wordt te weinig gebruikt EXA

                            # grep



head c 

grep BEL c                  # weer deelstring van de regex dus geeft nie echt wa we willen

grep BEL$ c

grep -e BEL$ -e NED$ c      # meerdere regex die aan mekaar worden ge or d veel handiger!!

                            # je kan ook je regex lijn per lijn in een bestandje plaatsen

cat alpen                   # inhoud is
AUT
SUI
USA
FRA
ITA
GER
SWE
NOR
CAN
LIE
SLO
CRO

paste w c | head 

join -t \; -1 3 -2 2 -o 2.4 w c | grep -f alpen | nl 

                        # dan hou je over wat er in die landen was 

                        # vaak wil je inverse dan gebruik je -v 

join -t \; -1 3 -2 2 -o 2.4 w c | grep -vf alpen | sort | uniq -c 
    
                        # meer weer hier de sort dan uniq op


join -t \; -1 3 -2 2 -o 2.4 w c | grep -xvf alpen | sort | uniq -c 

                        # de x zegt dat de volledige lijn moet voldoen aan de regex 
                        # (dus zogezegd tss ^ en $)


                        # denk bvb aan killen van een proces, 
                        # stel da je proces 12 is dan wil je niet dat 11234 ook wordt gekilled 
                        # want die beantwoord partieel aan de optie


dig gonzo.iii.hogent.be | grep ";; ANSWER SECTION:" 
    
                        # stel je wilt nu net erna of ervoor of errond dan gebruik je -b

dig gonzo.iii.hogent.be | grep -A1 ";; ANSWER SECTION:" | grep -v ";; ANSWER SECTION:" 

                        # dan heb je enkel de lijn over die interesseert (dus zonder de ;; ANSWER SECTION:)




grep -c a 0?            # tel aantal keer hoeveel regex (hier a) voorkomt

grel -l a 0?            # alle bestanden waar a wel in voorkomt

grep -L a 0?            # alle bestanden waar a niet in voorkomt 


                        # tr
                        # alles dat geen lettertje is verwijderen is bvb nuttig om alles aan mekaar te plakken

cat tien

                        # bvb verwijder alle line feeds c is complement d delete

tr -c '0-9' '' < tien 

tr -dc '0-9' < tien     # nu staat alles aan mekaar


                        # secret weapon is perl 

head w 

cut -d \; -f4 < w       # de disciplines

cut -d \; -f4 < w | sort | uniq -c 

                        # weer niet vergeten eerst te sorteren!
                        # nu wil je totaal sommeke erbij

cut -d \; -f4 < w | sort | uniq -c | perl -e '' 

                        # -e perl script tss de ' '


cut -d \; -f4 < w | sort | uniq -c | perl -ne '' 

                        # de -n: while lus over diamond operator  


cut -d \; -f4 < w | sort | uniq -c | perl -ne 'print' 
    
                        # hem print zelf default $_


cut -d \; -f4 < w | sort | uniq -c | perl -ane 'print' 
        
                        # -a: split over standaard whitespace en je krijgt @F


cut -d \; -f4 < w | sort | uniq -c | perl -ane 'print "$F[0]\n" '

cut -d \; -f4 < w | sort | uniq -c | perl -ane 'print; $s+=$F[0]\; END{printf "%7s\n",$s} '

                        # perl heeft keywords END en BEGIN die ook al zit hij in de while het maar 1 keer zal uitvoeren
                        

                        # xargs 

ls -1 0?

                        # lijntjes van bestanden

ls -1 0? | xargs echo   # standaard effect je plakt dus die uitvooer samen en geef echo mee

ls -1 0? | xargs -t echo 


ls -1 0? | xargs -n 3 -t echo   # groepjes van drie

ls -1 0? | xargs -p echo        # interactief vragen 


```



## File types

```sh

ls -l dido
stat dido

            # rechten aantal links eigenaar groep file size time of last modification name

            # rechten wijzigen

chmod g+w,g-x,o+r dido

chmod 740 dido

```

# tussendoor

```
r = 4 = 2²
w = 2 = 2^1
x = 1 = 2^0

```

== optellen == voor getal van de chmod

dus chmod 777 geeft iedereen alles 700 geeft enkel root alles 744 laat iedereen lezen maar root alles enzoverder
(getallekes moet ik eens controleren)

```md

#	    Permission				    rwx
7	    read, write and execute	    rwx
6	    read and write			    rw-
5	    read and execute		    r-x
4	    read only				    r--
3	    write and execute		    -wx
2	    write only				    -w-
1	    execute only			    --x
0	    none					    ---
```

```sh

                # bij nieuwe bestanden gaat hij kijken naar dit ding

umask 0022      # standaard 

ùmask -p 
umask -S        # huidige instelling 

umask 0077
umask -S        # bekijk op bitmanier

rm t
touch t
stat t

umask 0022

```

Vierde bit: set user bit (de 4), set groep bit (de 2), de sticky bit (1)
user bit use case: je hebt een bestand die door een andere gebruiker uitgevoerd mag worden als root ma enkel da bestand
groep bit use case: door set groep id bit in te stellen op de map, ga je zeggen de groepsid van de map wordt gekozen door de map ipv de persoon, bij shared folders worden ze dan automatisch gecreerd met het groepsid van de map die voor eens en altijd gemaakt is

sticky bit use case: wordt tegenwoordig ingesteld op mappen, betere naam: restricted permition bit
dat geld voor mappen die gemeenschappelijk zijn
als je da op een map hoog zet en iemand maakt bestand in dan is hij de enige (de eigenaar) die het kan verwijderen


kleine s wil zeggen beide staan aan
grote S wil zegegn dat enkel setguid aan staat
kleine t beide, T enkel sticky bit


# Proces manipulatie

```sh

ps

ps -ef 

echo $$                         # eigen procesID

pgrep bash                      # je krijgt lijst die aan da patroon voldoen

prgrep bash | grep -vx "$$"

                                # dan zit je eigen proces er nie zit en gebruik de x da het nie een substring kan zijn

prgrep -a bash                  # nu krijg je ook de opdrachtlijn


pstree | less                   # vi interface

pstree -p | less

                                # merk op dat je niet kan weten of een process ready of running is 
                                # maar wel of hij blocked (stopped in unix)

                                # illustratie via programmatje

                                # merk op geen ++$x omdat het numeriek is!
                                # priemgetallen
                                # (( )) numeriek vergelijken

x=0 ; while ((++x)) ; do y=($(factor $x)) ; ((${#y[@]} == 2)) && echo $x ; sleep 0.5 ; done 

                                # sleep gebruikt floating point getallen

                                # kill stuurt signalen naar gelijk wat process

kill -l                         # geeft overzicht van alle signalen die je kan sturen
                                # maar drie tal die kunnen killen

                                # SIGKILL, SIGINT, SIGTERM (2,15,9)

                                # eigenlijk in drie fases
                                # eerst stuur je 2 wil je aub vriendelijk afsluiten
                                # dan 15 # kom jong sluit maar af
                                # dan 9 # zonder slag of stoor afbreken

prgrep bash | grep -vx $$

kill -9 1709

                                # je ehbt ook 2 stoppen, de ene kan je opvangen de andere nie

prgrep bash | grep -vx $$

kill -19 3623                   # nu is hem in geblokkeerde toestand
kill -CONT 3623                 # zal hem nu weer laten verder doen


                    ## ACHTERGROND draaien &

(x=0 ; while ((++x)) ; do y=($(factor $x)) ; ((${#y[@]} == 2)) && echo $x ; sleep 0.5 ; done ) > p &

                                # uitvoer omleiden en & 

tail -f p                       # om groeiend bestand in de gaten te houden
tail -F p                       # als hij keer gesloten en opgen is zal -f hangen dus beter!!!

                                # hoe kan je nu aan da proces geraken (id had 4025)

kill -19 4025                   # en het is ook gestopped
kill -18 4025                   # en het is weer aant draaien

                                # tzou wel jammer zijn da je da altijd in een ander terminal venster moet doen
                                # ~> gebruik jobs!

jobs

jobs -l                         # nr en state krijg je dan ook 

                                # nummer tss [] is je jobnr

                                # nu kan je kill -19 in zelfde terminal ook sturen via

kill -19 %1                     # % zijn de jobnrs

jobs -l 

kill -18 %+                     # terug 

                                # de + is het laatste da je naar achtergrond hebt gestuurd
                                # de - is de voorlaatste



                                # als je zelfde opdracht wil starten mag je niet naar hetzelfde bestand omleiden

... > q 

                                # na uitvoering toch nog naar achtergrond sturen is via CTRL^Z

                                # MAAR groot verschil met & (die nog draait) is da hij nu nog gestopped is!!!!

                                # je moet het na je CTRL^Z nog nen stamp geven 

jobs

kill -18%                       # hij pakt zelf den laatste impliciet

man bash

CTRL^Z                          # die man bash blijft daar staan op de plaats waar hij stond

                                # nu test ge u gerief

                                # en je wil nu terug keren naar je man pagina

                                # terug in foreground brengen
jobs
fg %                            # en je zit terug in u man bash

man bash

man kill

fg %-                           # goe kunne switchen tss twee man pages in zelfde terminal 
                                # (je mag alleen niet quiten maar je moet CTRL^Z)

                                # handig als je dus wil itereren tussen twee man pages


                                # stel je bent geen root

su - 

                                # nu root

CTRL^Z ga nu nie gaan           # login shell alat zich nie onderbreken
                                # er is wel een opdracht via suspend

suspend                         # juist hetzelfde als CTRL^Z

suspend -f 

en dan terugkeren via fg %

                                # voordeel is da je je passwoord nie altijd opnieuw moet ingeven

                                # stel da we nu nog een maken die vragen gaat stellen

                                # dus om de tien wacht achter input

(x=0 ; while ((++x)) ; do y=($(factor $x)) ; ((${#y[@]} == 2)) && echo $x ; sleep 0.5 ; ((x%10)) || read ; done )

                    # nog nie in foreground

                    # nu omleiden en achtergrond

(x=0 ; while ((++x)) ; do y=($(factor $x)) ; ((${#y[@]} == 2)) && echo $x ; sleep 0.5 ; ((x%10)) || read ; done ) > r &

                    # vergeet nie ge behoudt running status

                    # nu moe je weer starten want hij wacht op input

kill -18 %5

                    # werkt nog steeds niet hij blijft op stopped staan want hij wil invoer hebben
                    # en je kan geen invoer geven als hij in background is

                    # je moet het dus naar foreground brengen

fg%
                    # enter
CTRL^Z
                    # nu is hij weer vertrokken


                    # den truck om te overleven wnr een stom program wacht op nen enter

(x=0 ; while ((++x)) ; do y=($(factor $x)) ; ((${#y[@]} == 2)) && echo $x ; sleep 0.5 ; ((x%10)) || read ; done ) s & 

                    # je wilt eignelijk dat hij het invoerkanaal negeert
                    # je sluit het invoerkanaal af

                    # dat gebeurt met 1<&- (sluit het invoerkanaal af)

(x=0 ; 1<&- ; while ((++x)) ; do y=($(factor $x)) ; ((${#y[@]} == 2)) && echo $x ; sleep 0.5 ; ((x%10)) || read ; done )

                    # meeste programmas hebben dan wel fout maar kunnen verder
                    # voor foutenkanaal naar vuilbak te voeren kan je dan
                    # 2> /dev/null sturen

(x=0 ; 1<&- ; while ((++x)) ; do y=($(factor $x)) ; ((${#y[@]} == 2)) && echo $x ; sleep 0.5 ; ((x%10)) || read ; done ) > s 2> /dev/null &



```





