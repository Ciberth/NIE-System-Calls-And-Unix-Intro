# Best 2 theorie
lesweek3
02 / 03 / 17


# Basic commands

```sh
touch # commando voor bestande te maken/wijzigen

ls {0..9}

rm -f {0..9}

ls -l {0..9}

rm -f {5..8}

ls -l {0..9}

touch -c {0..9} # creeren van bestanden die aan het patroon voldoen achterwege laten

touch -cr qq {0..9} # tijdstamp overerven van qq ; interessant voor scripts om daarin onderscheid te maken 

ls -l {0..9}

touch -ct {0..9}

touch -ct 01311234 {0..9} # time letterlijk ingevuld 

ls -l


##### 


shuf -rn 20 -e {a..j}

shuf -rn 20 -e {a..j} | sort > x
shuf -rn 17 -e {a..j} | sort > y

cat x y # maar beetje raar want tis onder mekaar geprint

paste x y # je print ze naast mekaar 

# voor te vergelijken gebruik je comm (veronderstelt dat alles gesorteerd is)
 
comm x y

# eerste kolom 1e, tweede kolom 2e en derde kolom gemeenschappelijke

comm -13 x y # enkel de lijnen die in tweede kolom staan hou je over

# vergeet niet dat beide gesorteerd moeten zijn !!! 



# voor niet gesorteerde bestanden (typisch text)
# dan gebruik je diff

vi dido
vi dido2 

# je zou verschil tussen die twee bestanden willen weten 

diff dido dido2
# je krijgt overzichten van wat er bijgekomen is, gewijzigt is.
# nuttig voor extra lijnen, spaties op te sporen

# om de filter minder critisch te maken:
diff -i dido dido2 # case insensitive
diff dido dido2 | wc -l # geeft 46
diff -i dido dido2 | wc -l # geeft 34
diff -iw dido dido2 # white space negeren
diff -iwB dido dido2 # B staat voor lege lijnen negeren

diff -iwc2 dido dido2 # je ziet blokjes (en context twee keer)
diff -wBc2 dido dido2 # 
diff -wBu2 dido dido2 # geeft blokje context en de twee versies 

diff -wBy --suprress-common-lines dido dido2 # verschillen naast mekaar ; die suprress zorgt voor "nut" 

```

# MD5 verificatie bij downloads 

Hele variatie van utilities die verschillen in wat voor galoisveld ze werken.

```sh

ls -l ?? # bestanden p2 qq t1 t2

sha224sum ?? # ?? is voor elk van die filetjes 

sha224sum ?? > t # naar file voor te controleren 

cat t1

sha224sum -c t # dan krijg je ok 

touch qq 

sha224sum -c t # ook nog ok (hij kijkt bit voor bit)

vi qq # wijzig iets 

sha224sum -c t # 1 WARNING

# een andere is bvb sha512sum ?? 




shuf -rn 17 -e {a..j} > y

shuf -rn 14 -e {a..j} > x

shuf -rn 24 -e {a..j} > z 

paste x y z 

paste -d \; x y z # andere delimiter hier ; backslash anders denkt bash da het de scheiding is tussen twee opdrachten

paste -d \;;. v w x y z # spelen met delimiters kan de nabewerking makkelijker maken

paste -s -d \; v w z y z # tussen ; staan de lijnen van elk bestand

cat v # das ook nen shuf 

paste -s -d '' v # aanmekaar plakken, bvb voor wachtwoord fzo

```


Examenvraag van vorig jaar!!
(xargs)

```sh

# doel: matrix omkeren

# shuf gebruiken om random getallen te maken

shuf -rn36 -i 0..9

# groepeer ze per 6 en toon op scherm

shuf -rn36 -i 0..9 | xargs -n6 echo 

# zo krijg je de matrix waarmee we eigenlijk starten 
# strikt gezien is die echo nie nodig

shuf -rn36 -i 0..9 | xargs -n6 > x 

# alles op 1 lijn krijgen 

shuf -rn36 -i 0..9 | xargs -n1

xargs -n1 < x | split -l 6 

# per6 in stukjes hakken via split 

shuf -rn36 -i 0..9 | xargs -n1 | split -l 6 # l het aantal lijnen da je wil splitsen

# hij maakt standaard xaa xab blijkbaar !!! 
# split werkt maar op 1 bestand 

ls -ltr # hij heeft zes bestandjes gemaakt xaa xab xac ...

cat xaa # je ziet dat de eerste 6 zijn van de uitvoer, dus echt in stukken getrokken

# nu aanmekaar kleven

paste -d ' ' xa*

# dan zie je dat het getransponeerde is 

cat x 

split -l 1 x # opsplitsen in 1 lijn 
ls x*

cat xaa # 1 regel 

# geef je da een tweede argument

split -l 1 x y # tweede arg wordt gebruikt als prefix van de bestandsfile 

split -l 1 x '' # dan krijgen ze geen nummering
split -dl 1 x '' # dan heb je numerieke indices met 1 lijn groot  

# je kan ook splitsen in bytes

ls -lSr /etc # jwhois.conf

nl /etc/jwhois.conf 

split -dC 10K /etc/jwhois.conf #K is 1024 bytes d voor numeriek

# x00, x01, ... met grootte 

# terug oorspronkelijke:

cat x0* > t # en ge gaat zien da is precies hetzelfde bestand
# cat is niet gevoelig voor binaire informatie 

md5sum /etc/jwhois.conf t 
# de twee md5summen zijn hetzelfde 

# splitten en aan mekaar kleven met cat 

```


# Joinen van databanken via unix utilities

```sh

head c # competitors 
head winners.csv 

# stel je wil c joinen met winners

# joinen veronderstelt dat bestanden gesorteerd zijn op de sleutel die je wil joinen

# dus nu willen we sorteren van winners.csv
# c is gesorteerd op tweede kolom (en let op het moet lexicografisch gesorteerd zijn)
# dus we maken winners.csv gesorteerd op derde veld (sleutel van c tweede veld)

cp winners.csv w 

sort < w > w # da mag je nie doen! tis kapot 
cat w # leeg

# ge moogt da nooit behalve hier bij sort 

cp winners.csv w 
head w 
# sorteren op derde veld

sort -t \; -k3,3 -o w w
# -t delimiter
# nu ga je velden numeriek aanspreken (1-based)
# -k is sorteren op het derde veld maar nu sorteert hij VANAF daar 
# maar dus ook TOT het derde ,3
# je mag ook meerdere -k meegeven bvb -k2,2 (met volgorde van belang)
# -o w voor weer naar w te schrijven (ter plaatse aanpassen)

# je kan ook numeriek sorteren via -k3,3nr (n voor numeriek en r recursief)

head w 

head w c 
paste w c | head 

# koppelen veld 3 in eerste en veld 2 in tweede 


join -t \; -1 3 -2 2 w c

# welk veld gebruik je als eerste veld en welk in tweede 
# uitvoer is nie wa je wil 
# je wil daar series in filteren 

paste w c | head 

join -t \; -1 3 -2 2 w c -o 2.4,2.1,1.2,1.4,1.1 | head

# -o opsomming van veldekes 
# nationaliteit naam ...
# dus voor volgordekes 



join -t \; -1 3 -2 2 w c -a 2 # auto join 

# rechtse autojoin ma geef enkel degene da ge nie kunt vinden

join -t \; -1 3 -2 2 w c -v 2 | grep Paolo 

# dutsen die nooit gewonnen hebben 

```

Gebruik geen echo maar printf! 
Paar jaar geleden niet (omdat het extern was) maar nu is het intern. Vroeger was echo veel lichter dan printf. 

Voor informatie gebruik de help (intern) en niet de man pages. 


# Op bezoek gaan naar bestanden

```sh

locate TODO # vrij snel een antwoord

# het vervelende van die locate is dat u eigen net gemaakte TODO bestanden er nie gaan inzitten
# locate maakt snapshots (dikwijls een dag oud) en zoekt daarop 

locate -b TODO # enkel in de bestandsnamen 

locate -br TODO # regex 

# find /
# find .

find /usr/share -name TODO

# je geeft altijd criteria op (filters)
# zo zoek je naar bestanden die echt TODO noemen


# voor actuele toestand !!

find /usr/share -name *TODO* # mag niet JE MOET " " gebruiken

find /usr/share -name "*TODO*" 

find / -name "*TODO*" # serieus wa werk mee 


find /usr/share -name "*TODO*" -size +10k -mtime +200 # inhoudelijk gewijzigd geweest vroeger of later dan x dagen -200 voor minder

find /usr/share -name "*TODO*" \( -size +10k -mtime +200 \) # nu is het hetzij aan de size of hetzij aan de tijd

# modified time (inhoud) en changed time (attributen) dus toch ga changed wijzigen maar modified niet 

-print # doet hem er altijd impliciet bij maar tip gebruik -printf

find /usr/share -name "*TODO*" -size +10k -mtime +200 -printf "%8s %p\n" # dan krijg je size en path


# stel da je met elk van die bestanden iets doen (der zijn een 5tal verschillende methodes)

$(find /usr/share -name "*TODO*" -size +10k -mtime +200)

# uitvoer ter plaatse in commandline ;  je krijgt dus een geexpanseerde commandline
# HIER ZIT EEN LIMIET OP !! 

wc $(find /usr/share -name "*TODO*" -size +10k -mtime +200)

# krijg je voor elk de wc en de som 

# ALTERNATIEF IS XARGS 

find /usr/share -name "*TODO*" -size +10k -mtime +200 | xargs -n3 wc 
# groepjes maken van 3 en opdracht wc uitvoeren 

find /usr/share -name "*TODO*" -size +10k -mtime +200 | xargs -n4 wc 

# als je geen groepjes doet dan pakt hij zoveel mogelijk 

# -t toon wat er wordt uitgevoerd 
find /usr/share -name "*TODO*" -size +10k -mtime +200 | xargs -tn4 wc 

# -p voor interactieve vraagstelling
find /usr/share -name "*TODO*" -size +10k -mtime +200 | xargs -pn4 wc

# nuttig voor files te verwijderen 

# iets anders is -ok voor te vragen
# maar je hebt placeholder nodig en daarvoor {} (syntax)
# je kan ook zeggen move naar een doel via -ok mv {} doel

find /usr/share -name "*TODO*" -size +10k -mtime +200 -ok wc {} \;

# die \; grenst het gebied af 

# je kan ook ipv -ok ook -exec doen en dan zeg je onvoorwaardelijk "voer hem uit" 


find /usr/share -name "*TODO*" -size +10k -mtime +200 -exec wc {} \;

# dit is veel trager want de opdracht wordt telkens opnieuw uitgevoerd 
# ipv \; kan je \+ schrijven 
# dan voer je niet 1 voor 1 uit maar alles tesamen 


find /usr/share -name "*TODO*" -size +10k -mtime +200 -exec wc {} \+


# nog een andere manier

find /usr/share -name "*TODO*" -size +10k -mtime +200 -printf "wc %p\n" 

# die opdrachten worden niet uitgevoerd maar je maakt dus u opdrachten zoals je van plan bent om ze uit te voeren 
# wil je het uitvoeren dan pipe je naar bash | bash


find /usr/share -name "*TODO*" -size +10k -mtime +200 -printf "wc %p\n" | bash 

# opm slides: er staat een -0 en da is voor files die een spatie bevatten.
# spaties in filenames is miserie
# -print[0] | xargs [-0] zorgt ervoor dat je verandert van scheidingsteken 
# backspaces in files nog meer miserie 


```


# Filterprogrammas 

```sh
# pipen naar cat is toegelaten voor de opties anders niet eh 

vi t 
cat t 

cat -n t # lijnen genummerd

cat -b t # nummer ze niet  

cat -ns t # opeenvolgende lege lijnen mee nummeren of niet


echo $'bev\010er   ' > t

cat t # geeft beer 

# maar zitten er geen vieze characters in

cat -T t # nu zoek je tabs 
vi t # voeg x tab y toe 

cat -T t # en je krijgt x ^Iy

cat -E t # elke lijn wordt nu beindigd door een $ om het einde aan te tonen

cat -v t # nu zie je bev^Her en ^H is backspace 

cat tien # tien printen 

tac tien # lijn achterste voren 

rev tien # da gaat elke lijn inverteren character per character 

wc winners.csv # letters woorden lijnen 

wc -w winners.csv # geeft enkel woorden 


wc -w < winners.csv # nu krijg je geen bestandsnaam meer !!!! Handig voor in variabele te steken 



wc competitors.csv winners.csv 

wc -L competitors.csv winners.csv 
# geeft van elk de lengte van de grootste lijn 

# stel je wlt die lijn zien 

strings -n $(wc -L competitors.csv) competitors.csv 


cat tien # stel er zitten wa lege lijnen in

strings -n1 tien 
# alle lege lijnen ben je kwijt 


strings -n1 tien > t ; mv t tien # je moet tijdelijk bestand aanmaken 

head -n 4 tien 

head -n -4 tien # geeft 1 tot 6 dus de kop van de file behalve de laatste 4 

# je kan da ook binair b of characters c 

head -c -1 file # da maakt van een bestand alles behalve de laatste byte 

head -c -1 tien > t 

hexdump -C tien 
hexdump -C t 

head -c -100 tien | hexdump -C # gaat leeg zijn (heeft maar 21 bytes)


hexdump -C tien # allemaal 0a 

unix2dos tien 

hexdump -C tien # nu 0d 0a 

# stel je wilt weg 

tr -d '\r' < tien | hexdump -C 

# alle \r weg doen


echo 'x         y           z' | tr ' ' ',' # alle blancos vervangen door een ;

echo 'x         y           z' | tr -s ' ' ',' # squeze dus dan maar 1 ; meer 

```
