# Best 2 theorie
23 / 02 / 17

# Utilities en dergelijke (Standard I/O)

- Van sommige utilities is het wel degelijk de bedoeling dat je de **opties** kan en kent!
- Principe van standaard I/O maakt gebruik van invoer/uitvoer/error kanalen: STDIN, STDOUT en STDERR.
- **Filterprogrammas** verwerken tekst via STDIN en STDOUT.
- **Pipelines**


Standaard invoer (0) kan je omleiden.

```sh
cat tien # heeft 1 tot 10 gescheiden door enter
nl # nl zal de stdin naar console omleiden STDOUT
# ctrl+D voor invoer af te sluiten (CTRL+Z op windows)
nl 0< tien # lijntjes nummeren van wat er in tien staat
nl < tien # hetzelfde; default is dus 0 
0< tien nl # doet ook hetzelfde; je mag de omleidingen zetten waar je wil (niet duidelijk)

shuf -i 1_20 # stout

shuf -i 1-20 1> bestand # naar bestand schrijven
shuf -i 1-20 > bestand # naar bestand schrijven maar 1 doe je vaak niet

ls -l t xxx # xxx is niet aanwezig -> op uitvoerkanaal: no such file
# dus merk op dat je twee gescheiden uitvoerkanalen te zien (beide worden naar console gericht)
# je kan beide omleiden
ls -l t xxx > t1 2> t2
# merk op niets komt nog op je terminal
cat t1
cat t2 
# de info (err, uitv) zitten daar nu in

ls -l t xxx >> t1 2> t2 
# >> voor concatenatie ; typisch om te loggen


# let op !

ls -l t xxx > t1 2> t1 # dus je zit met twee onafh kanalen naar dezelfde file te schrijven 
# je krijgt dan onzin!!

# mooie manier is:

ls -l t xxx > t1 2>&1 # je zegt dus waar kanaal op dit ogenblik is omgeleid
# dus je zegt 1 is naar omgeleid en ik leid twee ook naar dat dan
# van de volgorde ben je wel totaal niet zeker 
# hier is de VOLGORDE wel van belang!

ls -l t xxx 2>&1 > t1
# foutenkanaal nog steeds naar console 
# (want op da moment wijst uitvoer nog naar console) en uitvoerkanaal naar bestand


# let op een ; (bij {} nodig! ; bij () niet nodig -> dus doe beide!)
{ shuf -i 1-5 ; pgrep bash ; } > t 
# accolades: groeperen van opdrachten
# beide uitvoeren ga nu naar bestand omgeleid worden 

# kleine variatie ()
( shuf -i 1-5 ; pgrep bash ; ) > t 

# nu heb je wel twee bashen gestart
# nu voer je alles uit in een kindproces!! 
# dus je ziet huidige bash en kindproces van de prgrep

fun () { shuf -i 1-5 ; pgrep bash ; } >> t 
# functiedefinitie
# louter door deze opdracht uit te voeren gebeurt er niets! 

# tipje: bestand legen
> t # leegmaken + maken 

fun 
fun 

# telkens zal je bestand worden aangevult 
# functies ben je wel kwijt als je bash sessie verlaat ; expliciet met: 
unset set 



shuf -rn10 -i 1-10

# welke getallen komen dubbel voor?

# oplossingmethode: schrijven naar uitvoerbestand; sorteren; weer wegschrijven en dan kijken
# je kan bestanden vermijden via pipes 

shuf -rn10 -i 1-10 | sort -n | uniq -d 

# "omleidingen naar tijdelijk bestand en da als invoer geven" en op het eind van de rit worden ze verwijdigt

# je mag nie overdrijven bvb pipen naar cat
shuf -rn10 -i 1-10 | cat # niet zinvol!
shuf -rn10 -i 1-10 | cat -E # kan bvb al wel

# wat ook not done is 

cat t | nl # overbodig ; cat pipen naar iets 
nl < t # veel beter want je hebt subshell minder


# wat we ook nie willen zien staan

x='een
twee
drie'

# wordt weinig gedaan te weinig ;)
# je kan ook omleiden naar een variabele!

declare -p x 

# stel je wilt lijnen nummer 

echo $x | nl # sowieso fout ; je vervangt lijnscheidingstekens door blancos!
# echo doet dat ; als je alle speciale tekens wil behouden moet je var tss " " doen
echo "$x" | nl # ma toch ook niet goed eh weer subshell

nl <<< "$x" # dan krijg je juist hetzelfde effect zonder de pipeline!
# als je de inhoudt van een var wil pipen naar utility doe dan utility <<< "$var"


shuf -rn10 i- 1-10 | sort -n | uniq -d 
# invoer die je had ben je wel kwijt dus hoe bewijs je da nu 
# stel nu da je tussendoor dingen wil bewaren? -> tee commando
# deze gaat opsplitsen in meerdere takken

shuf -rn10 -i 1-10 | tee t1 t2 | sort -n | uniq -d

# er worden dus drie kanalen gemaakt
# 1 kanaal t1, 1 naar t2 en 1 naar stdout 

cat t1 # oorspronkelijke getallen

# wat we nog meer kunne is opsplitsen en voor elke opsplitsing gaan we onafhankelijk pipelines gebruiken
# tee -a komt erop neer dat je bestand gaat aanvullen 


shuf -rn10 -i 1-10 | tee -a t1 | sort -n | uniq -d


```

## RTFM

Enerzijds de which en type. 
Stel we willen iets weten over kill commando 

```sh
man -f kill # opdrachten kunnen meerdere ladingen dekken, syscal of commando bvb
# met -f zie je een overzicht van waar er allemaal iets zit (hier 4) nummers zijn sectienummers
man 2 kill 
man kill # dan krijg je eerste in de rij
# man is gepiped naar less 
# zoeken met / en via n ga je naar volgende ; q afsluiten
info kill 
# hier gebruik je niet less maar emacs manier ctrl s zoeken ; h voor help
# dikwijls zie je in de info pages meer voorbeelden 

# als je naam van de opdracht niet weet wat dan?

man -k dhcp # gaat gaan kijken in alle man pages en zoekt sleutelwoord
# je krijgt lijst van waar je wel man pages zal vinden

# dit is allemaal voor externe commandos
# voor interne kan je da nie doen (dan krijg je volledige man page van bash)
#vb man shopt

nl --help # bijna alles heeft de --help optie 
nl --help | less 

# voor interne gebruik je help (gaat enkel voor interne!)

help shopt # geeft deeltje van bash manpage maar beperkt tot shopt 
# dit gaat ook voor sleutelwoorden 
help case # voor syntax bvb 
# er zijn ook opties
help -s set # krijg je syntax 
help -d set # krijg je description
help -m set # man formaat 
help -s for 

```

## Linux Directory Hierarchy 

Hierarchisch filesysteem (net zoals windows).

```sh
getconf PATH_MAX . # geeft 4096  
getconf NAME_MAX . # geeft 255

tree /etc | less 
tree -d /etc | less # enkel directories
# volledig pathname via -f 
tree -df /etc | less 
# zonder indentering
tree -idf /etc | less 
# beperking voor niveaus 
tree -idfL 2 /etc | less

cd /etc/init.d 
cd .. # oudermap 
cd ~ # eigen home map 

pushd /etc/init.d # dan ga je daar naar toe ; werk verrichten 

pushd /etc/sysconfig/network-scripts # je gaat naar andere map 

# nu heeft stack gemaakt 

popd # en je keert terug naar vorige locatie 
popd # en je kan terug keren

# om de stack te bekijken gebruik je 
dirs 

```

Een groot deel van het filesysteem zitten enkel in het geheugen. 
Bvb. de submap /proc zit daar vol van 

```sh
cat /proc/uptime # hoelang draait systeem al (eerste is aantal seconden ; tweede idle time)

cat /proc/version # versie 
```

Directories maken

```sh 
cd / 
cd 
mkdir a/b/c/d # gaat niet want bovenliggende mappen besta niet 
mkdir a/b/c/d -p # maak meteen alle tussenliggende niveaus die nog niet bestaan
ls -lR a 
rmdir a # gaat niet want hij is niet leeg
rmdir -p a # nog steeds niet want hij is niet leeg 
rmdir -p a/b/c/d # vanuit het kind zal hij da wel willen doen 

rm -rf # force verwijder recursief 
```

## Symbolic Links

```sh 
ls /etc/sysconfig/network-scripts/ifcfg-eth0 

# link leggen naar deze in huidige map bvb 
# het gedraagt zich als een copy commando eerst bron dan target

ln /etc/sysconfig/network-scripts/ifcfg-eth0 eth0 
cat /etc/sysconfig/network-scripts/ifcfg-eth0
cat eth0
# als de ene wijzigt dan de andere ook dus fysiek hetzelfde bestand 
# wil je fysieke locatie te weten komen dan gebruik je stat 
stat /etc/sysconfig/network-scripts/ifcfg-eth0
stat eth0 

# of 
stat /etc/sysconfig/network-scripts/ifcfg-eth0 eth0 

# Komt overeen met pointerish gedrag
rm eth0 # je verwijderd de verwijzing maar niet het oorspronkelijke bestand 

# Dit zijn allemaal harde links 
# nadeel: zijn beperkt tot hetzelfde filesysteem!
# je kan nooit hard link leggen op ander filesysteem
# hard link kan ook geen map behandelen 

# oplossing is soft links ln -s 

ln -s /etc/sysconfig/network-scripts/ifcfg-eth0 eth0 
# moderne manier is ln -s (dan heb je geen problemen met andere filesysteem EN je kan ook link leggen naar map (ook naar gesharede drive bvb))

stat /etc/sysconfig/network-scripts/ifcfg-eth0 eth0 

# andere locatie nu! Hij laat wel degelijk nu een bestandje achter (denk aan shortcuts)
# verwijderen gebeurt op dezelfde manier: rm eth0

cd /etc/init.d 
pwd
# is da echt of is da een omleiding? 
pwd -P # etc/rc.d/init.d dus tis een verwijzing eigenlijk 

# linux zit er vol van je kan da zien met 
tree /etc | less # de pijltjes 

# in windows spreekt men van file junctions

```

## Shell Globbing


```sh
# patronen
# * willekeurig gelijk hoeveel keer 
# ? 1 willekeurig karakter 
ls * 
ls a*
ls t? 
ls t[a-z]*

```

Je kan deze uitbreiden en dat noemt extended Globbing

```sh 

cd /etc 
ls 
# alle files die eindigen met string .f of .conf (gaat niet met gwne globbing)
# op zich bash kent geen regex maar we benaderen het zo wel 
ls -d # niet binnen directories diep gaan 
ls -d .d | .conf # maja da pipen ga nie eh in bash
ls -d .d @(.d|.conf) # geef mij alle bestanden die beantwoorden aan .d OF .conf

ls -d -d @(*.d|*.conf) 

# combineren gaat ook 

ls -d !(@(*.d|*.conf)) # alles behalve die en die en die EXAMEN
# extend glob staat standaard af op niet interactieve omgeving (remember)
# zet da aan in u script bovenaan eh! 

# ook als je strings vergelijkt kan je zeggen beantwoord een string aan een bepaalt patroon

# gebruik je de -d niet dan geeft hij de directory zelf 

ls -l *
ls -ld * 
# twee soorten aanpassingsdata: modify datum (inhoud) - changed datum (attributen) 

.bestand # hidden

ls -la # dan zie je ze wel 
# let op de . ..
# . is huidige map 
# .. is de ouder map 

# stel da je alles wil zien staan behalve de rest niet 
ls -A 

# sorteren 
ls -l # alfabetisch
ls -lt # tijd 
ls -lS # size
ls -lSr # size omgekeerd 
ls -lSR # dan wel recursief 
# case insensitive vaak -i maar soms f van font # herdefiniëren ga niet zo makkelijk 

ls # kolomgebasseerd 
ls -1Sr # geeft uitvoer in 1 enkele regel !!!

stat t # attributen van een bestand 
# attribuut vs extended attribuut 
# afh waar het bijgehouden wordt 
# attribuut - read permissie bvb 
# extended - acls enzo 
# met ls inhoud en attributen
# wil je extended attributen zien dan gebruik je stat!! 

file t # da probeert aan de hand van de extensie van een bestand en ook inhoudelijk de file te bekijken wat voor soort file het is 
file /usr/bin/dir # geeft info als LSB executable 
# de aard van het bestand dus 
# t geeft ASCII text 

stat /
stat -f / # hoe groot is da filesysteem enzo vrije plaats op disk


mkdir d 
touch {0..9} # wordt tot de shell geexpandeerd 
ls {0..9}
cp {0..9} # twee argumenten meegeven is source, doel dus da zou gaan maar nu staan er tien 
# hij zal zeggen da laatste is geen map 
# moest da wel zo zijn dan zou hij het gedaan hebben
cp {0..9} d 
# nu is d netjes ingevuld 
# in d aantal verwijderen
rm d/{4..7}
ls d 
cp {0..9} d # hij doet de copy opnieuw of ze daar nu staan of niet 
rm d/{4..7}
ls d 
cp -i {0..9} d # interactieve modus nu gaat hij telkens vragen of hij moet kopieren als het bestaat 
# -f voor geforceerd 

touch * # recentere wijzigtime 
rm {7..9}
cd ..
cp -u {0..9} d 
cd d 
ls -l 
# alles heeft nu recente filedata hebben 
# dus hoofddir heeft time van voor tien uur in d na tien uur 
# met -u ga je niet overschrijven als zijn time recenter is 
# en time wordt dan time van de copy maar da wil je niet daarom optie -p


cd d 
rm {7..9} 
cd ..
cp -up {0..9} d
ls -l d 
# soort update maar je behoudt de fileddata van de bron!! 


touch {00..99}
ls {00..99}

# rm vaak alias voor rm -i #interactieve modus zoda hij vraagt moet ik het vernietigen of niet 

# mooie bypas

rm -i {00..99} 

# je gaat yes gebruiken
yes yes 

yes y | rm -i {00..99}
ls -l {00..99}
# stel je wil vraagjes niet zien verschijnen

touch {00..99}
yes y | rm -r {00..99} 2> /dev/null # de vuilbak

# kleine variatie
touch {00..99}

yes y n # hij ga toch altijd y interpreteren
yes 'y 
n' # maar da is nu ynynyny

yes 'y 
n' | rm -iv {00..99} 2> /dev/null # den helft wel den helft niet eh 

toch {00..99}

shuf -rn20 -e y y y y y y y y y n # random opvolging met gewicht y/n 

shuf -rn100 -e y y y y y y y y n | rm -iv {00..99} # ik laat 1 van de tien leven (decimeren)

ls -l {00..99} 2> /dev/null # er blijft maar tien percent over 

shuf -rn100 -e y y y y y y y y n | rm -iv {00..99} # stel nog keer 

# er blijft maar 1 over

# EXAMEN is interessante oefening !!!!
# random files vernietigen is shuf en pipen naar rm 

```