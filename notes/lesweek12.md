# Week 12: Theorie op 19/05/17

Indien er weinig geheugen over is moet er gebruik gemaakt worden van swap-space.


```sh

free
free -m         # overzicht van gebruikte geheugen en virtueel geheugen (swap)

swapon          # dan zie je waar je swap space vandaan komt

rm t 
head -c 20m < /dev/zero > t 

ls -l t         # 20 mega groot met allemaal nulletjes

mkswap t

                # nu kan je toevoegen aan swapspace

swapon t 
                # hij geeft melding dat je beter een chmod had gedaan van da filetje

swapon 
                # nu zie je da hij samengesteld is uit meerdere files, dat hij meerdere files gebruikt

swapoff t       # om de swapspace te verwijderen

                # hopelijk heb je dat niet nodig


```

Voor doorsnee gebruikers is mounten te ingewikkeld om zelf te doen. 1 van de oplossingen is een achtergrondprocess die luistert naar de berichten die de udev daemon behandeld (udisks). Udisks is een achtergrondprocess die luistert naar en als hij ziet dat er mountable devices zijn dan zal hij da mounten voor u automatisch doen en op de desktop een prompt tonen.

Bij standaard linux zal je dus een prompt tonen als je een device inplugt. Analoog zoals dat op windows gebeurt. In de udev regels kan je kijken 


```sh

cd /etc/udev/rules.d
ls

82-udisks2-les.rules    # heeft jomoreau gemaakt 
                        # afhankelijk van welke udisks draait moet je wel rekening mee houden

                        # inhoud van 82-udisks2-les.rules

KERNEL=="sd*", ENV{ID_FS_LABEL}=="ROOD", ENV{UDISKS_IGNORE}="1", ENV{UDISKS_FILESYTEM_SHARED}="1"
KERNEL=="sd*", ENV{ID_FS_LABEL}=="WIT", ENV{UDISKS_IGNORE}="1", ENV{UDISKS_FILESYTEM_SHARED}="1"
KERNEL=="sd*", ENV{ID_FS_LABEL}=="GEEL", ENV{UDISKS_IGNORE}="1", ENV{UDISKS_FILESYTEM_SHARED}="1"
KERNEL=="sd*", ENV{ID_FS_LABEL}=="ZWART", ENV{UDISKS_IGNORE}="1", ENV{UDISKS_FILESYTEM_SHARED}="1"
KERNEL=="sd*", ENV{ID_FS_LABEL}=="ORANJE", ENV{UDISKS_IGNORE}="1", ENV{UDISKS_FILESYTEM_SHARED}="1"

KERNEL=="sd*", ENV{ID_FS_UUID}=="BA21-890E", ENV{UDISKS_IGNORE}="1"
KERNEL=="sr*", ENV{UDISKS_IGNORE}="1"
KERNEL=="loop*", ENV{UDISKS_IGNORE}="1"

                        # einde inhoud

ls /media/ 

udisksctl               # zo monsterprogramma ctl 

udisksctl monitor       # kijken welke berichten hij onderschept

udisksctl info -b /dev/oranje1 

                        # individuele info van een device

udisksctl mount -b /dev/oranje1 

                        # mounten
ls /media/ORANJE

udisksctl unmount -b /dev/oranje1 

                        # merk op unmount niet umount

                        # dit is de huidige moderne manier via udisks daemon
                        # meerdere manieren dus om devices te mounten
``` 


## Systemd

Het mounten in map wordt door systemd ook gezien als softwarecomponent gelijk een ander. 

```sh

cd /etc/systemd/system/
ls

                        # filekes vb root-geel.mount 
                        # die filekes zeggen beschouw het mounten als softwarecomonent

cat root-geel.mount     # formaat is windows ini bestanden

                        # inhoud
[Mount]
What=/dev/geel
Where=/root/geel
Type=vfat

                        # je kan ook opties meegeven Options=ro # read only bvb
                        # einde inhoud

                        # de inhoud van die Where is ook de naam van het bestand die twee MOETEN consistent zijn
                        # /root/geel/ --> root-geel met extensie .mount
                        # dan beschouwt de systemd daemon dan ziet hij het als softwarecomponent

                        # je kan UUDI, PARTUUID, LABEL gebruiken bij What
cat root-rood.mount
                        # inhoud
[Mount]
What=UUID="12F9-5D2C"
Where=/root/geel
Type=vfat
                        # einde inhoud

lsblk -f                # het is niet gemount 

ls /root/rood           # lege map maar die moet gemaakt zijn!! 

systemctl start root-rood.mount

lsblk -f                # het is nu gekoppeld 

systemctl status root-rood.mount 

                        # die softwarecomponent is "actief" 

systemctl show root-rood.mount

ls /root/rood

                        # achtergrond process -> .service
                        # voor te mounten -> .mount
                        # systemd ziet dus alles als softwarecomponenten die hij moet behandelen

systemctl stop root-rood.mount

                        # mapje weer leeg
                        # voordeel is 

```



Het swap proces, de paginering daemon en de init deamon zijn de enige die niet in user space draaien.

## System V init

Ga je nog op alle unix smaken vinden en ook linux heeft dit altijd ondersteund.

init process is het eerste dat opgestart wordt in de gebruikersmodus (de rest in kernel) en een keer da het draait dan alles in usermodus.

Der zijn twee alternatieven op gekomen als initn van de toekomst (upstart en systemd). Ubuntu (upstart) is nu ook echter overgestapt op wat de red had distributie heeft gemaakt en da is systemd proces.

Op unix bestaat systemd nie die werken nog met het oude system v


```sh
                # er wordt naar de /etc/inittab gekeken

cd /etc
vi inittab

                # er staan hier regeltjes in 

                # dit zegt default runlevel 5

id:5:initdefault:

                # hoe lager runlvl hoe minder je mag
                # 3 bvb is multi user met netwerking maar geen gui
                # runlvl 6 is rebooten
                # runlvl 0 is shutdown

                # System initialization

si::sysinit:/etc/rc.d/rc.sysinit 

                # (in die filekes kan je veel van bash leren)

                # je kan init 3 doen om van runlevel te veranderen (dynamisch)

                # in systemd is een softwarecomponent veel ruimer dan hier 
                # hier is het typisch achtergrondprocessen

cd /etc/rc.d/init.d

ls

                # (bash) shell scripts 
                # conventie is dat deze scripts dezelfde naam hebben als de softwarenaam om het te starten
                # vb named, snmpd

vi snmpd

                # in inittab zie je da dialect met nrs

cd /etc/rc5.d   # dus runlvl is hier 5
                # dus wat daar staat is een verzameling wat er moet gebeuren 
                # als je naar dat runlvl gaat of als je van dat runlvl komt

                # die hebben een prefix van S of van K

                # de conventie is

                # als ik overga van runlvl 5 dan moeten alle scripts met een S lettertje wel die moeten gestart worden
                # als ik runlvl 5 verlaat dan moeten alle scripts met een K uitgevoerd 
                # (komt overeen met services die gestopt moeten worden)

                # S -> naar runlvl
                # K -> verlaat runlvl

                # het nummertje staat er om in die volgorde uitgevoerd te worden

ls -l 
                # dit zijn symbolische links naar ../init.d/...
                # bvb S95atd -> ../init.d/atd 

                # in /etc/rc6.d zitten vooral K's snmp heeft nog een S om te zeggen "kga rebooten" 

                # zo kan je runlvl 27 maken en die bevolken met symbolische linken

chkconfig --list 

                # hier zie je overzicht waarmee je checks kan zetten om in runlvls dingen te wijzigen
                # dus hier kan je zeggen daemon x wil ik aan of uitzetten in runlvl 4 

```


Tot daar de oude manier van werken.

**Voordelen systemd tov system V init (zie ook slides)**
- concept is uitgebreider (niet enkel achtergrondprocessen)
- ge moet geen bash meer kennen (configuratie is met init bestanden), duidelijk uit windows overgenomen en da is heiligschennis in de unix wereld
- de afhankelijkheden tss de componenten (beschrijven) daar heb je veel mogelijkheden voor
- opstartprocedure gebeurt zeer parallel (men wil zo snel mogelijk alles opstarten), onmiddelijk login prompt tonen terwijl sommige dingen nog nie opgestart zijn
- je kan services starten die getriggered worden door events (vb inpluggen van stick die mount kan starten, of timerkes)
- stel da een daemon om de vijf minuten plat ligt, die kan je automatisch herstarten
- resources quotas opleggen 
- uniform beheer (systemctl)
- uniforme logging (journalctl)
- verschillen wegwerken tussen distributies

**Controversiële aspecten**
- het doet meer dan aanvankelijk de bedoeling was (dingen die niets met opstartprocedure te maken hebben zoals bvb naam pc, tijd)
- den torvals ziet zijn kindje in handen van wa duitsers 
- udev nodig? ahn dan ook systemd

```sh

systemctl                   # monsterprogramma die alles doet
systemctl list-units        # geeft overzicht van alle componenten die op dit moment actief zijn
systemctl list-units | less

                            # het begrijp service wordt ook veralgemeend 
                            # bvb als het maar 1 keer opgestart wordt:
                            # .target 
                            # .mount
                            # .service
                            # .timer
                            # .slice

systemctl is-active snmpd.service 
                            
                            # geeft active

echo $?                     # exit status 0 wordt teruggeven dus handig in scripts

systemctl is-active root-rood.mount 

                            # unknown 


                            # unit bestanden zelf maken doe je in bepaalde map
                            # in /lib/systemd/system

cd /lib/systemd/system
                            # die hebben precies dezelfde naam als de 
                            # service die ze moeten beschrijven

declare -p PS1              # voor prompt aan te passen grote W naar kleine w veranderen

                            # de parallele map is de /etc/systemd/system
                            # en alles wat je in de etc map zet heeft voorrang op de lib

cd /etc/systemd/system

ls                          # er zijn submapjes die dienen voor kleine wijzigingen die dan gemerged worden

cat sssd.service.d/journal.conf 

                            # extensie .conf

systemctl cat sssd.service  # die cat is dus de verzameling van de bestandjes
                            # edit bestaat ook voor wijziging door te voeren en die zal dan submapje zelf maken

                            # active dead bestaat en das dan zoiets van "keb mijn taken uitgevoerd" maar ik run niemeer


systemctl --list-units | grep target


systemctl list-dependencies graphical.target 

                            # en je krijgt boomstructuur

systemctl get-default       # wat hem zal doen als hij boot
                            # is den target en zal daarvoor al de afhankelijkheden ook opstarten 

                            # equivalent van init bestaat ook
                            # je wil multiuser blijve werken ma gui boeit mij nie
                            # traditioneel: init 3 

systemctl isolate multi-user.target 

                            # en hij zal dus ook weg gaan uit graphical
                            # dus elk van die commando's stopt die component die nie in den andere zaten

systemctl is-active graphical.target # inactive

                            # zonder reboot terug naar graphical

systemctl start graphical.target 

                            # nu ga hem deel van de bootprocedure terug afgaan, gnome enzo

                            # in omgekeerde volgorde bekijken doe je via --reverse

                            # stukje bij slice hieronder

systemctl show snmpd.service | grep CPU

                            # resultaten die je hier ziet kan je dan samenzetten met anderen dingen 
                            # (slice maken) en dan zeggen 
                            # "ik wil nie da die dingen samen 10% van men geheugen gebruiken" bvb 

```

## Unit types:

- services: daemons
- targets: equivalent van runlevels (afhankelijkheden om actief te maken) Die dependecies kan je opvragen met show-dependencies
- timer: alternatief voor cron, maar je moet die timer afhankelijkheden geven die zegt wat hij moet doen. Den timer doet op zich niets dus je moet er voor zorgen dat hij in cascade iets doet. Maw koppelen aan andere componenten
- devices: reageren op wat de udev daemon zegt
- socket: zeer algemeen, traditioneel een achtergrondprocess (webserver bvb die luistert op inkomende berichten),  hier is idee dat achtergondprocess altijd uit twee targets bestaan, de service die iets doet en de socket die naar nieuwe dingen luistert. Dus als er enen binnenkomt dan zal target starten en nieuwe aanvragen zal em bufferen en a la FIFO activiteiten te verwerken. Voordeel: als je de service wil herconfigueren dan moe je enkel de service herstarten en mag je de socket laten draaien en de clients zullen van niets weten. Je kan een socket dus niet zien los van een service ALTIJD IN EEN KOPPEL (in de beschrijving van de socket zal er staan welke service ze zal moeten opstarten om te communiceren met de berichten van de client)
-path: laat u toe om een map of een file in de gaten te houden (al is het maar lezen, wijzigen), maw monitor. Dus hier weer een koppel waar je service aan zal koppelen. Je kan wel nie meegeven wat er gebeurd is aan die file of map. Dus de trigger wordt gelanceerd maar wat de trigger was (of is) da weet de gekoppelde service nie.
- (auto)mount, swap: zie mount gedeelde (mount units)
- snapshot: via systemctl snapshot, dan neem je van je huidige situatie een snapchot zodat je kan rollbacken (momentopname dus)
- slice: een cgroep maken da is een verzameling van processen (een linux kernel principe niet systemd) en je zegt elke unit heeft zijn eigen cgroep en als ik de cgroep stop dan kill ik alle processen in die cgroep. Als nen traditionele service stopt en je start hem terug dan kan hem zo nog wa dingen overhouden wa tot onverwachte situaties kan zorgen. Via die cgroep ben je zeker dat alles de nek omgewringt is. Slice biedt een veralgemening van. Je kan verschillende units verzamelen in een slice. Het is dus ook een verzameling van componenten maar met een ander doel. Het heeft als doel dat je quota's gaat koppelen. 



Timer, socket en path zonder service hebben geen enkele zin!!


systemd is de pletwals applicatie (die trekt alles naar zich toe en vermoselt alles) = D 