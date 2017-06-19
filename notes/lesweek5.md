# Week 5: Theorie op 16/03/17

## Herhaling vorige week (dus belangrijk voor examen IMO) - Procesen

```sh


(rm p ; x=0 ; while ((++x)) ; do y=($(factor $x)) ; ((${#y[@]} == 2)) && echo $x  >> p; sleep 1 ; ((x%10)) || read ; done )

            # C^Z (sowieso geblokkeerd) vs & (niet geblokkeerd) in achtergrond

jobs

jobs - l    # signaal 18 naar job 1 
            # of korter 

bg 
cat p  

bg %1       # of korter bg % (omdat er maar 1 is)

jobs -l 

            # door die read instructie bij 20, zit da proces nu te wachten 
            # input kan je nooit geven aan een proces die in background draait
            # je moet het in foreground brengen, input geven en dan naar background terug zetten als je da wil 


%           # de foreground command wordt hier op losgelaten 

            # dus nu is da proces op de fg op input aant wachten 
            # nu kan je input geven en weer met ^Z in bg brengen

bg % 
jobs        # runnen zal nie lang duren want bij 30 zal hij weer op input zitten wachten 

            # Doel is nu om invoerkanaal af te sluiten van da programma

            # eerst mond snoeren

jobs
kill %
rm p 


(rm p ; 0<&- x=0 ; while ((++x)) ; do y=($(factor $x)) ; ((${#y[@]} == 2)) && echo $x  >> p; sleep 1 ; ((x%10)) || read ; done )

            # invoerkanaal afsluiten <&- die &- is sluit da kanaal af uitvoer zou > zijn 
            # ; 0<&- ; lukt wel maar het werkt enkel op deze opdracht, dus tss de ; ; 
            # als je da wil omleiden dan moet je het doen op het niveau van de while instructie 

(rm p ; x=0  ; while ((++x)) ; do y=($(factor $x)) ; ((${#y[@]} == 2)) && echo $x  >> p; sleep 1 ; ((x%10)) || read ; done 0<&- 2>/dev/null) &

            # 0<&- #invoerkanaal afgesloten
            # 2>/devl/null fouten naar dev/null

jobs 
bg % 
jobs 
            # blijft running
cat p 
            # die komt dus read tegen, krijgt fout maar het programma overleeft die fout 
            # let dus op waar je da precies zet/moet zetten
            # of u programma daar tegen kan is een andere discussie

kill %


(rm p ; exec 0<&- ; x=0 ;  while ((++x)) ; do y=($(factor $x)) ; ((${#y[@]} == 2)) && echo $x  >> p; sleep 1 ; ((x%10)) || read ; done 2>/dev/null) &

            # gebruik je het over meerdere lijnen gebruik dan exec 
            # dus hier blijft het geldig tot je het inverteert of het script ten einde is

^Z 
bg % 
tail -F p 


            # stel meerdere processen in achtergrond 

jobs 

jobs -l 

wait        # zolang je die wait gebruikt zal je foreground programma wachten 
wait -n     # wacht tot gelijk welke job in de achtergrond er iets mee gebeurd

wait -n ; tail p 

            # nu deze job van status veranderen, vanuit een ander console venster 

            # merk op dat je in een ander venster die jobs nie gaat vinden 
            # wat wel kan 

jobs 
kill -9 2913 

            # dan zie je dat de tail wordt uitgevoerd 

            # overzicht
bg 
fg 
kill 
jobs 

```



## Hoofdstuk 3: Devices 

Wat linux nu doet is eigenlijk anders dan want unix vroeger deed. 
Wa linux nu doet is voor na de paasvakantie - udev enzo.
Unix komt nu.

Kijk naar de /dev en /sys map.

```sh
ls -ladH /dev/* | sort 

```



1 kolom: major nr en is een verwijzing nr welk stuurprogramma er moet gebruikt worden (beetje het type)
tweede kolom: (minor nr) zorgt ervoor dat als 1e gelijk is da ze onderscheidt kunnen worden

Een device spreek je aan met een file. Alles in unix zijn files.
Alle utilities van files kan je dus ook gebruiken en afvuren op devices. 

verschil blok en char device = het stuurprogramma die bepaalt hoe da device in de lijst zich zal manifesteren 

Nu blijkt dat char devices makkelijker te ontwikkelen zijn. Daardoor zie je minder blok devices.

Blok devices bieden gebufferde toegang, waardoor je merkwaardig genoeg eender welke data naar sturen 1 byte of 100 bytes. De devicedriver die zorgt ervoor dat bijkomende buffers zal invullen als het blijkt dat er meer data gevraagd wordt dat in de buffer zit.

Bij char devices is het andersom en moet je meedoen met wat de controller u ter beschikking stelt. Is het byte per byte dan moede maar werken byte per byte. 

s socket devices 
p pipe devices (weer mappen waar weer devices kunnen in staan)


De volledige sys en dev mappen is een wir war van directories en zit vol van symbolische links. 


## Device files 

```sh
blockdev --report               # geeft overzichtje
blockdev --help | grep get      # generisch programma dankzij device files
```

Men streeft naar een uniforme naamgeving

### Block devices 

(denk vaak aan massaopslaag)

sd* is typisch voor disken via SCSI protocol
sr* is voor CD en DVD (read only drives)
sg* is voor CD en DVD writers (maar merk op voor interactie is er geen block device maar een char device)

Je hebt ook loop block devices: loop*

usb stick inpluggen -> 

```sh

ls /dev/oranje1                 # pas na inpluggen is dit beschikbaar
                                # catten en omleiden naar bestand 
cat /dev/oranje1 > o1
^Z 
bg %                            # niet vergeten want ctrl z stopped het ook  
wait -n 

        # Nu is heel de inhoud van de usb stick gekopieerd in da bestand 
        # dus da bestand is een hele mirror eigenlijk 
        # wil je iets backuppen dit is een manier om dat te doen 
        
        # de vraag is nu hoe kun je hier een device aan koppelen om de inhoud te bekijken
        # ~> loop block device 
        # EXAMEN  

losetup --find --show o1 

        # -- find zoek zelf een nrke 
        # -- show zeg mij wa nrke het is

        # nu gedraagt /dev/loop1 zich alsof de usb stick ingeplugged is dus nu zien we block device 
        # nu kunnen we block device koppelen aan een map -> mounten

mkdir oranje1

mount /dev/loop1 oranje1/ 

cd oranje1 

ls      # NIET LEEG 

cd 

unmount oranje1/        # voor de koppeling vrij te geven 

losetup                 # voor te zien welke loop we hebben 

losetup -d /dev/loop1   # voor te verwijderen  


ls -lad /dev/st* 

ls -lad /proc/self/fd/*

                        # dev/pts/0 is u vensterke (terminal) 
                        # binnen u grafische omgeving 

ls -ladH /proc/self/fd/*

                        # dan zie je dat het character devices zijn 

                        # zit ge niemeer in u grafische omgeving maar via f2 enzo daar dan 

ls -lad /proc/self/fd/* # dan zie je dat er staat /dev/tty2 en da zijn ook characterdevices 

chvt 1                  # change virtualterminal en nummer 1 voor grafische omgeving in fedora 


            # je kan het kanaal van je terminal omleiden (stel da je anders wil interageren dan de spatie) 

            # doe da echter nie in je werkomgeving (terminal) maar in bestandjes kan het wel

cat single  # met contents 

trap 'stty echo icanon' EXIT    # als je control c doet voer dan deze opdracht uit 
stty -echo -icanon min 1        # niet echon en reageren op 1 enkele datatransfer 
while : ; do   
    k=$(dd count=1 bs=1 2> /dev/null)
    echo -n $k | hexdump -C 
echo . 
done


./single 

                # vanaf je nu letter indrukt krijg je gerief 
                # eindig met ctrl c 

stty sane       # da ka voor beterschap zorgen om terminal beter te krijgen 

tput init       # tput en reset ; da is ook een mogelijk redmiddel voor je terminal te redden 
tput reset 


tput reset | hexdump -c 

                # welke bytes da hem stuurt en da is terminal afhankelijk 

cvht 2 

tput reset | hexdump -c 

                # en tis al anders 

echo $TERM      # is Linux 

chvt 1 

echo $TERM      # is xterm-256color 

tput smso       # set modus on stand out (bold)
tput rmso 


smso = $(tput smso)
rmso = $(tput rmso)
rmul = $(tput rmul)
smul = $(tput smul)

                # allemaal specifiek voor deze terminal 

hexdump -C <<< $smul 

echo een twee drie ${smso}vier${rmso} vijf zes 

                # so stand out 
                # ul underline 
                # progress bar is zelfde principe

                # sleep kan me double overweg 

((x=2**30)) ; while ((x/=2)) ; do echo $x ; sleep 0.5 ; done 

                # gaat aftellen van 2^30 tot ge 1 uit komt 

                # stel uitvoer beperken 

                # alles staat onder mekaar 

((x=2**30)) ; while ((x/=2)) ; do echo -n $x ; sleep 0.5 ; done 


                # kga onthouden waar cursor staat en daar terugkeren 

                # sc store cursor 
                # rc recall cursor 

((x=2**30)) ; tput sc ; while ((x/=2)) ; do tput rc ; echo $x ; sleep 0.5 ; done 

                # maar nu wordt uitvoer staan van de lange uitvoer 


((x=2**30)) ; tput sc ; while ((x/=2)) ; do tput rc ; tput ed ; echo $x ; sleep 0.5 ; done 

```

## Iets anders 

```sh

ls {01..99}

            # 8 en 9 bestaan niet -> foutenkanaal 
            # rest uitvoerkanaal


ls {01..99} 2>/dev/null | wc -l 

            # stel je wilt aantal foutlijnen tellen!! (EXAMEN)

ls {01..99} 2>&1 1>/dev/null | wc -l 

            # volgorde is van belang!!


ls 0?       # 01 tot 07

            # geef me filkes die a bevatten 

grep a $(ls 0? 2> /dev/null)

grep a $(ls 1? 2> /dev/null) 

            # er zijn er geen en hij blijft hangen 

            # hij moet niets zoeken, er zijn er geen 
            # ambetant in scripts 

            # je doet grep a van niets dus die wacht op standaardinvoer 

            # dus in een script moe je rekening houden met het feit da er niets kan zijn 
            # opl 


grep a $(ls 1? 2> /dev/null) /dev/null 

            # als hij geen file vind zal dev null er staan en anders doe hem niets verkeerd 
            # da lijkt raar maar da is om u code te doen besparen.

            # exec is maar 1 keer nodig en geld voor alles da erna komt 
            # en dankzij devices kunne we zien wa me wa gelinkt is  
            # exec is gevaarlijker tss () of {} is ietske veiliger dan 

            
            # ingeval da er teveel files zijn voor grep dan verpak je via xargs 

ls -l 0? | xargs grep a 

ls -l 0? | xargs -n 5 grep a

ls -l 0? | xargs -n 4 grep a

ls -l 0? | xargs -n 6 grep a

ls -l 0? | xargs -n 2 grep a

ls -l 0? | xargs -n 3 grep a


ls -l 0? | xargs -n 5 -t grep a


ls -l 0? | xargs -n 4 -t grep a


ls -l 0? | xargs -n 3 -t grep a

        # zogezegd geeft ge maar 1 file (door de groepjes) dan zegt grep nie waar hij het gevonden heeft, den uil 
        # hoe omzeil je dat:


ls -l 0? | xargs -n 3 grep a /dev/null 

        # nu zoekt hij mintens in 2 files 

        # conclusie EXAMEN
        # /dev/null meegeven als bijkomend argument kan veel code besparen!

```

## Logbestand-ish

```sh

x=0 ; while ((++x)) ; do echo $x >> p ; sleep 0.1 ; done &

tail -F p 

        # we willen de uitvoerwegsmijten maar het programma den indruk geven da het nog bestaat 

rm p ; ln -s /dev/null p 
        
        # je voert een symbolische link uit 
        # p wa moe ik er mee doen -> omleiden naar dev null

ls p    # der besta nen p 

ls -l p # programma blijft draaien maar den uitvoer wordt weggesmeten 

        # ben je plots weer geinteresseerd dan moe je de link vergeten

rm p 

tail -F p 

        # bestand leegmaken 

> p 

        # dev/zero kan je gebruiken als invoerbestand vb met dd of head 

head -c 60 < /dev/zero | hexdump -C 

        # dan krijg je 60 bytes die allemaal nullekes hebben 

        # wa ga je nu doen als je 60 streepkes wilt hebben, 2000 spaties 
        # gebruik translate 
        # EXAMEN 


head -c 60 < /dev/zero | tr '\0' '-' > t 

cat t 

                # 60 streepkes maar geen scheidingsteken

echo '' >> t    # dan krijg je linefeed

                # dev/random gebruik het niet! 

head -c 20 < /dev/random 

                # gevaarlijk dus veiliger 

head -c 200 < /dev/random | hexdump -C 

                # na een paar keer uitvoeren zal hij blokkeren 
                # hij werkt met entropiepool, en als die op is moet die weer opgevuld worden 
                # geeft zeer goede randomgeneratoren maar potentieel partiele timeouts 

                # gebruik niet random maar urandom 

head -c 20 < /dev/urandom | hexdump -C 

                # den RNG is zogezegd wa minder goe maar die zal nooit time outen 

                # combinatie /dev/urandom device en octal dump (od)

                # we willen 20 ip adressen 
                # 4 bytes per lijn
                # -An geen offset
                # -t d decimale uitvoer over bytelengte 1 (signed integer)
                # -t u1 voor unsigned 
                # -t x2 voor hexadeciaaml

head -c 80 < /dev/urandom | od -An -w4 -t u1

                # dan nog wa prutsen 

head -c 80 < /dev/urandom | od -An -w4 -t u1 | tr -s ' ' '.'

head -c 80 < /dev/urandom | od -An -w4 -t u1 | tr -s ' ' '.' | cut -c 2-

                # 10 random ipv6 adressen

head -c 160 < /dev/urandom | od -An -w16 -t x2

head -c 160 < /dev/urandom | od -An -w16 -t x2 | tr ' ' ':' | cut -c 2-

                # od zegt ik wil per lijn zoveel bytes hebben en hoe uitschrijven
                # urandom en od 


ls -ladH /dev/st*

ls -ladH /dev/st* | nl 
                
                # die omleiding naar ander programma is een named pipe dus standaarduitvoer is plots pipe device geworden 
                # dus tijdens de levensduur van een programma wordt het omgeleid 

cd /dev/fd

ls 

                # voor het huidig process, welke fd's heb ik open 

ls - l *        # dan zie je wat er mee gebeurd is 

ls /dev/fd

                # dan zie je dat /dev/fd naar /proc/self/fd wijst 
                # en da dus elk proces daar een ding krijgt 

echo $$ # 1776

                # in ander venster 

cd /proc/1776/fd 

                # en dan kan je dus extern gaan kijken wat er gebeurd is 

```

## Some new fancy stuff

```sh

        # NIEUW EXAMEN 

cat kop 
cat staart 

        # je wil iets tussen beide plaatsen maar interactief toevoegen 

        # dus eigenlijk 
        # cat kop      <invoer>    staart 
        # en aan mekaar plakken


cat kop /dev/fd/0 staart > t 

        # nu vraagt hij input 

CTRL^D

cat t 
        # je wilt bestand tonen en tegelijk aantal woorden en lijnen

cat t | wc 

        # maar dan ben je invoer kwijt 

cat t | tee /dev/fd/1 | wc 

        # maar das nie wa je wilt je hebt standaarduitvoer en dan telwerk 

cat t | tee /dev/fd/2 | wc 

        # truckje dus omda je uitvoer hebt gestuurd naar foutenkanaal 
        # waardoor het op scherm wordt getoond en naar uitvoer 
        # zodat er op gepiped (geteld kan worden)

```