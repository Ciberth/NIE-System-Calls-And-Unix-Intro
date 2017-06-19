# Week 11: Theorie op 18/05/17


Vervolg udev

## Udev-daemon

Deze luistert naar berichten van de kernel. Deze zal op zijn beurt acties ondernemen op basis van deze berichten. De eigen udev rules kunnen dan zorgen dat bepaalde acties ondernomen worden specifiek op die machine.

Belangrijk: **Deze udev-daemon staat volledig in user mode!**

"Probeer zoveel mogelijk in user modes uit te voeren", dit komt de stabiliteit van je system ten goede! (Een linux paradigma)

De udev-daemon zal netjes het probleem oplossen dat traditionele unix systemen hadden (de volgorde van het inpluggen van een usb stick bepaalde de namen).


```sh
lsblk                   # Partities en devices zien

ls /dev/disk            # geeft by-id, by-label, by-path, by-uuid

ls /dev/disk/by-uuid/   # hier zit een soft link naar ../../sdc (wat hier de usb stick was)

                        # gebruik udev rules voor naam te geven, een synoniem name !! zie vorige les BELANGRIJK EXAMEN
                        # zodat je dit kan doen

ls -l /dev/oranje       # je ziet dat het een logische link is 


                        # voor elke driver er aanwezig is op het toestel welke dingen bij elkaar hoort

/lib/modules/$(uname -r)/modules.aliases

``` 

Het starten van de kernel moet zo snel mogelijk gebeuren, daarom moet de versie van de kernel zo minimaal mogelijk zijn. 

ALs de kernel via auto probing bepaalde devices herkent dan zal hij dit bericht aanvullen met properties en doorsturen naar de udev-daemon. Het is udev die kijkt of er een device driver is voor die specifieke attributen. Alles gebeurt in user modus!

```sh
lspci           # overzicht
lspci -nv       # welke drivers zijn daarvoor geladen en de -n voor de nummerkes te vertalen

lspci -nv | grep -e "^0" -e driver 

                # udev heeft dit dynamisch geladen


```

Dynamisch laden door udev kan je ook forceren. Dit is als het ware simuleren dat je het aparaat in en uit trekt. 
Je kan heel da proces opnieuw simuleren met de structuur van lspci 

```sh

cd /sys/bus/pci/drivers
declare -p          
                    # nog iets
                    # declare -w .... grote W door kleine w vervangen voor heel het pad 

ls
                    # hier vind je de e1000

ls -l e1000

                    # allemaal modules
                    # de modules die op dat moment de controller ondersteunen wel daar is een logische link gemaakt
                    # dus hier zie je bvb die e1000 driver een logische link heeft die verwijst naar een aparaat (.../devices/pci..)
                    # ehci-pci is voor usb 

blkid               # geef identificatie van usb devices en eigenschappen

lsblk -f            # hier zie je da ook 

                    # nu gaan we foefelen
                    # je weet identificiatie en je ziet bind en unbind

echo -n 0000:00:0b.0 > unbind 

                    # -n voor geen scheidingsteken plaatsen in unbind

lsblk -f            # heel die usb controller is weg 

echo -n 0000:00:0b.0 > bind 

                    # nu plug je de usb controller in zijn geheel weer in 

lsblk -f            # ze staan er weer in


cd e1000

```

Het is de koppeling die verdwijnt maar het komt er echt op neer da je het in en uit trekt zogezegd. En zo kan je een reboot vermijden. Straffer dan nen ifconfig down en up. 


```sh

udevadm test -a add|remove /sys/... 
                
                    # simuleren wat het effect zou zijn als je opnieuw zou inpluggen

                    # udev regels opnieuw laden moet je wel doen!!
udevadm control -R  # van reload rules, lees ze keer allemaal opnieuw in
                    # ze worden echter nog nie sebiet toegepast (tenzij op nieuw ingeplugde devices)
                    # voor reeds ingeplugde gebruik je trigger
udevadm trigger 

```

Einde derde hoofdstuk


Volgende komt uit hoofdstuk 4



```sh

cat /dev/oranje1 > dump     # je kan da inlezen en naar file dumpen
                            # heel de stick wordt nu gekopieerd naar een file



```

In window spreekt men van c drive, d drive die elk een partitie voorstellen. Op linux heb je da nie daar zit alles onder de root folder.
Veel van de mapjes onder linux zijn ook virtueel (dus niets op schijf)
tmp map is een deel van het geheugen dat je kan misbruiken als filesysteem maar bestaat ook louter in het geheugen

## Mounten

= het koppelen van een file structuur aan de logische structuur onder de root folder.

"wat wil ik mounten in wat" 

Destination moet altijd leeg zijn en bestaan!

```sh

ls oranje                   # leeg

mount /dev/oranje1 oranje   # map oranje1 in de map oranje

ls oranje                   # geeft nu alles wa op usb stick stond

unmount oranje              # je geeft de koppeling los
ls oranje                   # tis terug leeg

mount                       # geeft overzichtje (denk ik)

```


## Traditionele manier = unix

```sh

cat /etc/fstab              # mounts die gebeuren bij opstarten, dus wat em automatisch moet mappen

                            # je maakt dus gebruik van een label (uuid) als identificatie zodat het mounten altijd werkt!

                            # kijk naar kolommen!

mount -t devpt -o gid=5,mode=620 devpts /dev/pts 

                            # da haalt hem allemaal uit etc/fstab uit de verschillende kolommen
                            # bij de rest staat optie default (geen opties)

                            # de nummerkes geven aan in welke volgorde ze moeten uitgevoerd worden
                            # (eerst nen root en dan pas zijn kindjes want anders gaat dat niet)
                            # je kan ook devpts,noauto hebben en dan moet hem deze skippen
                            # het andere voordeel is dat je dan mount /dev/pts kan doen zonder een tweede parameter

```

## Mountopties

bij koppels is de linkse den default (dus rw moe je nie echt opgeven en exec ook nie das default)

```sh

mount -o ro /dev/oranje1 oranje

ls oranje

mount -o rw,remount /dev/oranje1 oranje     # remounten

mkdir mem
ls mem

        # je kan tmpfs zoveel mounten da je wilt, je zegt dan das een deel van het geheugen da ik opoffer
        # mount -o hoeveelgeheugenwiljereserveren -t tmpfs [device] [doel] 
        # die eerste parameter device is nie echt logisch maja

mount -o size=600m -t tmpfs tmpfs mem
ls mem              # blijft leeg
cp dump mem/1
ls -l mem
cp dump mem/2
cp dump mem/3
cp dump mem/4
cp dump mem/5
cp dump mem/6
                    # error writing mem/6 no space left on device
ls -l mem

mount -o size=800m,remount -t tmpfs tmpfs mem 

                    # EXAMEN!!!!!

                    # inhoud is niet gewijzigd =D 
                    # maar je kan wel copy doen nu van den 6 !! 

umount mem          # in ene keer alles wa in die geheugenstructuur zat kwijt 
                    # wel trappen ! voor geen vuile filekes wel hier voor die unmount

mount | grep tmpfs  # !


umount oranje1      # unmount voor je stick uittrekt

ls -l dump

                    # loopdevice maken
                    # en da loopdevice koppelen aan map 
                    # maar er is een bypass om loop te negeren

losetup             # leeg -> geen loop devices

mount -o loop dump oranje
                    # loop device gecreerd en inhoud van bestandje van u map is den inhoud
losetup             # niet leeg
ls oranje 
umount oranje
ls oranje
losetup             # terug leeg


```

Wat nuttig is, is om via mount te kijken of iets geladen is en in geheugen zit bvb

Andere opties, zie slides


```sh
ls /dev/wit*

ls wit

lsblk -f

                    # normaal
mount /dev/wit1 wit
                    # inhoud zit er in
umount wit

lsblk -f

mount -U D46C-A917 wit
mount -L WIT wit

blkid               # overzicht devices en labels

umount wit

```

Volgende optie van mounten die de moeite waard is:


```sh
mount               # is eigenlijk zelfde als cat /etc/mtab
                    # in fases waar de /etc/mtab nog read only is moet je 
                    # de mount -n gebruiken (want het kan niet normaal gemount worden zogezegd)

                    # INTERESSANT BIND optie

                    # chroot jails -> afgesloten omgeving voor specifiek proces 
                    # (apart filesysteem die maar aan beperkte dingen kan)

pwd 
mkdir jail
                    # map bevolken met filekes

chroot /root/jail bash

                    # indruk dat da de rootmap is en zoeke naar bash ma die map is leeg dus em vind da nie
                    # ge moet maken da in de nieuwe root een beperkt aantal dingen zitten die em kan uitvoeren

cd root/jail

which bash          # usr/bin/bash

mkdir -p usr/bin    # usr en usr bin

ls -R

cp /usr/bin/bash /root/jail/usr/bin/bash 
                    
                    # goed idee? nee

ln /usr/bin/bash /root/jail/usr/bin/bash 

                    # hardlink!

stat /usr/bin/bash /root/jail/usr/bin/bash 

                    # zelfde inode hier 1861
                    # zelfde fileke komt op verschillende plaatsen voor 
                    # binnen hetzelfde filesysteem


                    # bash uitvoeren werkt nog altijd niet
                    # hij gaat naar /root/jail hij beschouwt da als root 
                    # ma bash heeft dynamic link libraries nodig en die moeten daar ook staan

                    # gelukkig opdracht die zegt welke externe programmas bash nodig heeft !!!! examen

ldd bash            # overzicht vier filekes

ls -lad /lib/libtinfo.so.5 

                    # ma da is een symbolische link naar een ander bestand
                    # enkel de symbolische link kopieren is nie nuttig
                    # je kan dus geen gebruik maken van symlinks maar enkel van hard links!

ls -lad /lib        # is logische link naar /usr/lib


                    # om da op te lossen wa moeten we doen?
                    # in onze jail moeten we een map hebben voor lib


mkdir -p /root/jail/usr/lib

ln -s usr/lib /root/jail/usr/lib

cd /root/jail/usr/lib

ldd /usr/bin/bash

cp /usr/lib/libtinfo.so.5 . 

                    # dan ebde weer veel kopies -> weer hardlinks

                    # da bestandje is wel weer logische link 

                    # der is een optie cp -l !!! niet ln -l 

                    # cp -l zegt kga files kopieren maar als ik symlinks tegenkom dan kopieer ik de doellinken

cp -l /usr/lib/libtinfo.so.5 libtinfo.so.5
ls

stat /usr/lib/libtinfo.so.5 libtinfo.so.5 

                    # niet dezelfde bestandjes, andere inodes!!
                    # want twas nen symlink naar dienen 9 hier

stat /usr/lib/libtinfo.so.9 libtinfo.so.5 

                    # wel dezelfde inode dus wel dezelfde bestandjes!!
                    # moest het op een ander filesysteem staan dan had 
                    # hem geen hardlink kunnen maken 
                    # en ging men echt een kopie gedaan hebben!!



cp -l /usr/lib/libdl.so.2 libdl.so.2
cp -l /usr/lib/libc.so.6 libc.so.6

ls                  # allemaal zit er in

                    # jail opstarten gaat wel

chroot /root/jail bash

                    # kill kan, printf kan, echo kan
                    # ls KAN NIET 
                    # find KAN NIET

                    # voor oplossing te testen in jail

cd ../bin           # tzit enkel bash in

ln $(which find) find 

ldd find 
                    # weer al die kopieren


cp -l               # to the rescue !! EXAMEN !! 


rm -f lib/*         # al de libs weg

                    # je zou nen link willen maken naar den echte userlib van de lib
                    # maar hard kan nie en symbolisch kan niet 
                    # MOUNT TO THE RESCUE

ls lib
                        # leeg
mount -B /usr/lib lib   # echte userlib mappen in den lib met de BIND optie

                        # het maakt symbolische links als het ware
                        # -r recursief achtig 

ls lib                  # je ziet volledig, het is een volledige copy geworden

                        # als je nu jail uitvoert 


chroot /root/jail bash

                        # je kan in jail
                        # je kan find uitvoeren
                        # je kan geen ls uitvoeren

                        # dus nu enkel hardlinks leggen van de locatie van de programmas en TIS AL
                        # enkel den exe linken 
                        # de libs lost den mount wel op !!

                        # EXAMEN !!!!!!! 

                        # laatste opmerking
                        # je gaat uit jail

chroot /root/jail 
                        # zou bash moeten oproepe ma doe da nie 
                        # der is een symlink te weinig

                        # namelijk bin -> usr/bin

ls -lad *

ln -s /usr/bin bin

                    # en dan werkt chroot /root/jail ook !

                    # jail opkuisen 

                    # rm -rf * # bij sym links en hard links geen probleem 
                    # maar bij die mount OEI OEI OEI 

umount usr/lib
                    # kan nie als em nog busy is zelfs

ls usr/lib
                    # leeg

rm -rf jail/*       # geen gevaar meer 

                    # anders oei oei oei  


```



