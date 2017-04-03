# Week 1: Theorie op 16/02/17

```sh

```


# Inleiding

Theorie examen: 20 tal vraagjes


# 1.1 Levels in a Linux system

Een os bestaat uit een aantal software elementen en hardware elementen. Het is het OS dat er voor zorgt dat deze samenwerking goed gaat, dit gebeurt via **systeemaanroepen**.

Merk op dat er onderscheid gemaakt moet worden tussen de kernel modus en de user modus. 

In Unix spreken we van POSIX API die gemapt worden op systeemaanroepen. Het voordeel is dat een programma die voldoet aan die API automatisch geporteert kan worden naar andere distributies (dus een gemeenschappelijke API).

## Populariteit van Unix

Unix is oud OS (jaren 70). De oorsprong van Unix: er zijn er twee System V (ATNT, Bellabs in België) en BSD (Berkely Universiteit). Grootste reden was de kostprijs van software en hardware en onderhoud er van. 

Rond de jaren 80 is er een kentering gekomen, namelijk commercialisering. Er zijn varianten ontwikkelt (vrij noodzakelijk om tekortkomingen op te lossen). Bvb. netwerkondersteuning, multiple systemische processing, grafische werkstations...

In de jaren 80 kwam de pc ook op. Die versies van at&nt en berkely draaiden niet op intel processoren. De hobbyisten van de jaren tachtig bleven op hun honger zitten! Er was dus een grote nood die soort mensen.

Mimix is een distributie met pedagogische doeleinden. Voor de hobbyisten was dat nog steeds te elementair. Dus het was wachten tot de freeBSD (heeft toch nog even geduurt) en anderzijds de GNU groep die de utilities wou vrij ter beschikking stellen.  

En dan kwam de Linus. Moest linux er niet geweest zijn dan was freeBSD waarschijnlijk groter geworden (en freeBSD is een heel OS, terwijl linux zelf maar een kernel is en eigen compilatie op hardware nodig). Geen pretje om met een "naakte" linux versie te werken tot een OS. Dan kwamen distributies.

Een **distributie** is dus de linux **kernel** (incl systeemaanroepen en POSIX interface) + **services** (servers, daemons) + **utilities** (doorgaans GNU). Zeer dikwijs wordt dit aangevuld door _programmeeromgevingen_ en _GUI omgeving_ (KDE, GNOME).


# Users

Om te schakelen tussen gewone gebruiker en root:

```sh
su - # inloggen
sudo opdracht # individueel commando
```

# The Bourne Shell

Te vinden in ``/bin/sh``.

**Shell** = user interface (CLI) + command interpreter (_interactie_) ++ uitvoering scripts (_niet interactief_).

Alternatieven zijn:
- Bourne: sh (bash) [Linux]
- Korn: ksh [System V] en pdksh
- Joy: csh [BSD] en tcsh
- Falstad: zsh

(Objectief volgens M: Bash is vrijwel de slechtste! Deze zou pas op de vierde plaats komen.)

In principe kan je elke soort shell draaien op je toestel

Raadpleegbaar via: ``chsh -l`` (voor een lijst, let op je ziet meer) en ``chsh -s`` voor de shell te wijzigen (dodelijk voor root!).

Het probleem met zo een bash shell is dat dit onderhouden moet worden (en dat door 1 persoon). Het loopt dus logischerwijs wat achter.  

# 2.2 Using the shell

De syntax is opdracht [opties] [argumenten].

Vb

```sh
cat tien # voor bestand tien (met cijfers 1 tot 10) te lezen
shuf tien # voor uitvoer van tien maar geshuffeld
```

Je kan opties meegeven op de lange manier via --langenaam of kort via -n

Vb

```sh
shuf --head-count 5 tien
```

Die namen van die opties zijn vaak lang en niet per se intuitief (dus je moet ze opzoeken).

Vb range van getallen door elkaar hasselen

```sh
shuf --head-count 5 --input-range 100-200
```

Als je --input-range ziet staan is het duidelijk maar om er op te komen is dat niet prettig.

De traditionele unix manier (uit de jaren zeventig) maakt gebruik van de **short opties**.

Alternatieve van vorig voorbeeld is

```sh
shuf -n 5 -i 100-200
```

Dat is de traditionele manier (duidelijk korter).


Combinatie is ook mogelijk

(r is repeat)

```sh
shuf -rn 5 -i 1-10
```
(voor willekeurige lettertjes)

(e zegt dat je niet uit bestand leest maar dat je het volgende beschouwd als input)

```sh
shuf -rn 5 -e {a..z}
```

```sh
shuf -rn 5 -e aap noot mies
```

De BSD stijl is bvb ``ps aux``.
IBM JCL stijl is bvb ``dd if=.. of=..``.


## Environment and Shell Variables

De opdracht ``declare -p`` geeft u een lijst van alle variabelen die ingesteld zijn.

Een variabele doe je ``x=123`` en oproepen via ``echo $x``.

Een mooiere manier is ``declare x=123``. Het voordeel is dat je attributen kan meegeven. Je kan bvb zeggen "mijn waarde mag niet gewijzigd worden" of "mijn variabele als ik die een waarde geef moet die automatisch naar uppercase gezet worden". Bash is wat dat betreft zeer oudbollig.

Het x attribuut is wel interessant. 

```sh
declare x=123
declare -p x 
declare -p ${!B*} # geeft u overzicht van alle variabelen die met een B beginnen
declare -p ${!A*} # geeft ze allemaal omdat er geen zijn (dus ge krijgt alles)
declare -p ${!P*} # hier zijn er met -x

```

**Als ik een subshell opstart dan worden die attributen overgeërft (dat is het attribuut x) !!**

```sh
declare -x x 
bash
declare -p x
# om het weg te doen
declare +x x # dus + iets neemt het weg - past iets toe 
env # geeft u overzicht van enkel die attributen die x hebben
export ... # doet niet anders dan declare -x
#stel x bestaat
echo $x 
unset x 
echo $x # je krijgt nu niets
#stel je wilt nu een fout krijgen --> opties
```

(Typisch bash, in andere shells is dit anders!)


Opties: helaas is er geen uniforme manier. 
Je hebt dus opties die het gedrag van de shell beïnvloeden.

Bvb genereer fout als variabele niet ingevuld is. 
Dit doe je met shell options en doe je via ``set +/- o`` of ``shopt -o``. Dit moet je beschouwen als schakelaars.

```sh
set -o # geeft lijst van alle opties
set +o # dezelfde info maar nu in de vorm dat hoe je ze hierin krijgt (voor programmatische verwerking)

# handig in shell scripts
set +/-o verbose # volledige vermelding voor elke regel
set +/-o xtrace
set +/-o noclobber # 

# stel file t (met wat letters)
ls > t # bestand t is omzeep

# met die optie noclobber (set -C)
set -C
echo xazeqsd > t # hij gaat da nie willen doen (zo vermijd je dat je bestaande bestandjes kapot maakt)
set +C 
## nu gaat da wel 

echo $x # leeg 

set -u 
echo $x # een fout omdat hij unbound is 


set -e 
declare -p 
echo $shell # inhoud opvragen van variabele die bestaat 
echo $x # x bestaat niet
#

unset x 
set -e 
set -u 
echo $x # u shell is kapot 
# dus als er een fout optreed dat hij zijn eigen de nek omwringt 
# dus zeer foutbestandigproof 
# dus set -e is zeer goed zodat er niets verkeerd gaat
# van zodra je een shell script schrijft met onvoldoende foutopvang zet maar die set -e 

```

### shopt

= andere manier 

maar ook voor zaken die niet via posix ingesteld kunnen worden 

```sh

shopt -p # zien
shopt -s # set
shopt -u # unset

```

**Hier moet je 1 onthouden voor in scripts: de extglob functie (staat in de interactieve shell standaard aan maar in scripts standaard uit) !!!!**

Dus vanvoor in je script de extglob aanzetten ``shopt -s extglob``.

Recursief in map via ** is via globstar bvb.
Noaseglob optie aan zetten dan krijg je ook grote letters bij ls a*.
Nocasematch optie aanzetten is bvb interessant bij string vergelijking dat het er niet toe doet
strings vgln met == operator (omgekeerd in perl)

 

## 2.9 The command path

Sommige zijn **builtin** (door bash implemented) anderen zijn extern.

Vb intern is printf. Soms is intern trager (een constructie met doel voor externe (zie later)).

Hoe kan je da weten?

via het commando **type**. Het eerste dat je moet weten is of het extern of intern is voor help nadien.

```sh

type -t printf # als je da commando ingebouwd 
type -at printf # dan krijg je alle versies 
type -a printf # plaats waar ze staan (het pad)

# een ander alternatief voor het volledige pad te gebruiken bij extern gebruk is het uitschakelen van builtin opdracht
enable -n printf # zet dus de builtin uit
enable printf # voor terug te gebruiken 

# hier moet je rekening mee houden bij updates!!!! 

which -a shuf # geeft alle versies van een bepaald commando 

type -t shuf # geeft type
type -a shuf
type shuf # geeft shuf is hashed (/usr/bin/shuf) -> externe programma vlugger vinden

declare -p BASH_CMDS # toont welke da we onlangs gebruikt hebben

```


PATH kan je aanvullen met ``PATH+=:dir`` doe dit nooit voor root!

Alle opties die je aan bash meegeeft worden beschouwd als set opties dus scripts uitvoeren doe dat met bash en argument.


```sh

echo aa`ls` * ? $shell # waslijst van speciale tekens 
# hier vrees je dat de shell er speciaal gerief mee gaat doen-> opl wegslashen

echo aa\`ls\` # je kan "" gebruiken voor letterlijke dingen 

echo "aa`ls` * ? $shell" # zwakke manier van quoting

echo 'aa`ls` * ? $shell' # straffe manier van quoting 

# nu gaat alles individueel gebackslashed worden 

#aanraden: schrijf er een $ voor dus $'..' -> posix manier van quoting

echo $'aa`ls` * ? $she\x66ll' # zal die \x66 dus hexademicaal interpreteren  

echo $'aa`ls` * ? $she\x0all' # \x0a linefeed die hij zal doen 

```

Stel random passwoord generen

```sh

shuf -rn 16 -e {a..z} # het concateneren moet je niet zoeken in shuf 

shuf -rn 16 -e {a..z} | paste -sd '' # en je hebt wat je wil 

###### KAN GEVRAAGD WORDEN
```

