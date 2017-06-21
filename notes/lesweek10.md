# Week 10: Theorie op 04/05/17

(na stukje bash veel notes niet geschreven hier zie Sander, Ine, ...!!)

Nog klein stukje bash


Pseudosignalen: exit (0), debug, return, err en die kan je opvangen

Debug: wordt uitgevoerd telkens er een instructie w uitgevoerd (en die je ook kan opvangen)


Bij het schrijven van scripts zou het een automatisme moeten zijn om eerst



```sh

        # priemgetallen

i=0; n=0 ; while((++i)) ; do f=($(factor $i)) ; ((${#f[@]}==2)) && { ((n++)) ; p=$i ; echo $n:$p ;} ; done

        # set -/+ : aanzetten voor extra info


i=0; n=0 ; while((++i)) ; do f=($(factor $i)) ; ((${#f[@]}==2)) && { set -x ; ((n++)) ; p=$i ; set +x } ; done


        # in die verwerking tss () voor traphandler te beperken


(trap ': i=$i s=$SECONDS ' DEBUG ) ; i=0; n=0 ; while((++i)) ; do f=($(factor $i)) ; ((${#f[@]}==2)) && { set -x ; ((n++)) ; p=$i ; set +x } ; done

        # : de zinloze opdracht
        # geef je argumenten mee aan : dan gebruik je da om defaultwaarden te geven
        # ma hier doe je da dan om de argumenten op de opdrachtlijn te zien

        # debug signalen worden enkel gegeneerd in set+x/-x blokken



(trap ': i=$i s=$SECONDS ' DEBUG ) ; i=0; n=0 ; while((++i)) ; do f=($(factor $i)) ; ((${#f[@]}==2)) && { ((n++)) ; p=$i ; set -x ; set +x } ; done

        # dan doe je extreem en doe je dus activering en deactivering sebiet


```


## Stringbewerkingen


```sh

__DATA__            # van in perl kan je doen op volgende manier:

x='een
twee
$(ls)
drie'

declare -p x

rev <<< "$x"        # voor inlezen van string


                    # stel echter stringdefinitie met " " dan zijn alle substituties mogelijk

x="een
twee
$(ls)
drie"

                    # dan ziet em een opdracht da em moe uitvoeren

declare -p x 
rev <<< "$x"        # dan alles van uitvoer van ls ook

                    # here strings (<<<) en here documents (XXX)

                    # je mag de << vergeten eigenlijk das de oude manier
                    # LABEL afspreken en dan leest hem in tot ge weer label doet 

rev << HGF #enter
een
twee
$(ls)
drie
HGF

                    # die $ls wordt ook geinterpreteerd  


                    # voor als je wilt dat het niet geinterpreteerd worden 1 char ' '
rev << H'G'F #enter
een
twee
$(ls)
drie
H'G'F

                    # een andere afspraak is bij - da alle leadingtabs verwijderd 

rev << -HGF #enter
een
twee
$(ls)
drie
-HGF

                    ## maar belangrijker dus <<< 
                    #### EINDE BASH


```



Terug naar hoofdstuk 3: Devices

Major & minor nummer stuff met inodes

in een traditionele unix /dev map is het structureel (vlakke structuur) verdeeld terwijl in linux zit da al vol van verwijzingen 


in sys map heb je voor elk mogelijke device een submap 
voor sommige dingen krijg je hierarchie van devices 

vb je hebt een disk, in stukken gehakt in partities en voor elke partitie zal je mapje hebben sda3 binnen sda, block, pci bus ... devices (zie slides)


De meeste "gewone" files in deze folder zijn attributen die gebruikt worden bij opstartfase en die de kernel gebruikt.

/sys/devices/pci0000:00/000/atal/host0/target/////block/sda
hier kan je dan cat size doen
cat dev geeft 8:0 (major nr 8, minor nr 0)

**COMMAND**

``lspci -v``

gaat alles opzoeken en inhoud gaan uitprinten
het is dus die sys structuur gaat opzoeken en verzamelen

**COMMAND**

``lsscsi -v``

geeft u informatie 


**COMMAND**
udevadm info

gaat tonen wat de kernel allemaal verzameld heeft aan info in de opstartprocedure

**COMMAND**
udevadm info /dev/sda3

dan krijg je de details die verzameld zijn in deze map

E: staat voor **environment** (in de sys map)
P: (maar 1) dat is het volledige **path** naar de sys map
N: de **naam** in de device map (de die da je als parameter op gaf)
S: **symbolische links** in de device map
het zijn dus mappen in de device structuur die gaan verwijzen naar de officiele map (P)


```sh
 
udevadm info -q path /dev/sda3
udevadm info -q symlink /dev/sda3
udevadm info -q name /dev/sda3


udevadm info -a /dev/sda3 | less 

            # alle eigenschappen van een device met die van ouderdevice, diskcontrollere, ... 
            # tot je bovenaan in hierarchie zit

udevadm info -e | less              # van alle devices alles

udevadm info -e | grep ^P | wc -l   # geeft 267

            # udevadm is een administratie programma die geassocieerd is aan een relatief recent techniek 

            # en daardoor afgesplitst is van linux



            # usb inpluggen

lsblk -f    # om te kijken

umount /run/media/root/...

            # nummering is inconsistent!!


            # kernel doet aan hardwaredetectie via IPC --> blijft in kernelmodus 
            # en dan doorgestuurd naar udev in user modus die zoveel mogelijk doet 
            # mislukt het dan crashed het device maar nie u systeem

udevadm monitor -k 

            # nen monitor van devices


ls -l /dev/zwart

            # en is symbolische link
            # na uittrekken, en andere insteken is het weer symbolische link naar dezelfde maar andere usb
            # ma ge moet u da nie aantrekken



            # ... udev :/


            # volgorde van regels is wel belangrijk!!

/lib/udev/rules.d

declare -p PS1

            # dan uitvoeren en van de grote W een kleine w maken

declare -x PS1="\\w\$ "

            # je moet je verplaatsen naar /etc/udev/rules.d
            # voor regels toe te voegen 
            # en dan worden alle files op 1 hoop gegooid

            # je kan meerdere conditionals en meerdere acties hebben

KERNEL=="sd*", ATTRS{serial}=="AA040127..", ATTRS{idVendor}=="090c", SYMLINK+="wit%n"

            # wees zo specifiek mogelijk zodat aan alle conditionals (attrs) voldaan is voor die simlink gemaakt wordt

SUBSYSTEMS=="scsi" 

            # da is een voorbeeld van een verwijzing naar ouderdevices
            # er moet dus eenen zijn die scsi noemt

ACTION!="add", GOTO=".." 

            # goto vaak einde en gaat eigenlijk rest regels negeren

hwdb.d      # ook folder op hoogte van rules.d

```


