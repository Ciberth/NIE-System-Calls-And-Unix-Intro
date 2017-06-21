# Questions / Answers

1. Hoe kan je in 1 terminal gemakkelijk herhaaldelijk switchen tussen een man-pagina, een Bash shell en editor mode?
In een actief proces (programma) CTRL-Z’en brengt het proces naar de background (terug naar de terminal). Programma’s zijn terug te openen via 
```sh
fg %1 
fg %2 
fg %3
```

2. Bij het inpluggen van een usb stick (maakt niet uit welk type), geen popup weergeven op het systeem? 
```sh
ENV{UDISKS_IGNORE}:"1"      # in de rules.d file instellen bij device attributen
```

3. Inhoud van een map weergegeven zonder de .tmp en .bak files. In 1 commando zonder pipes. Hoe heet deze techniek? 
```sh
ls -d !(@(*.tmp|*.bak))		# Globbing
```

4. Een file wegschrijven zonder de laatste 512 bytes.
```sh
head -c -512 file.txt
```

5. Hoe toon je alle attributen van een device?
```sh
udevadm –a /dev/sda1			
udevadm info /dev/sda
```

6. Wat is het voordeel van devtmps tegenover de oude methode?
```
- Fouten bij configureren van een specifiek device is niet fataal voor globaal systeem
- Linux credo: Probeer zoveel mogelijk in usermode uit te voeren, gaat de stabiliteit ten goede komen
- Enkel drivers & /dev/nodes voor aanwezige devices
- Geschikt voor alle devices
- Consitent na elke boot of hotplug (want consistente naamgeving van elk device)
- Enkel drivers voor aanwezige devices (kernel stuur bij auto detectie de elementaire info (fabriekant en type device) naar udev sturen, dan gaat udev deze kernel module laden. Hij weet dit want bij de installatie van devices wordt een nieuw lijntje aangemaakt in modules.alias, als hij deze info hierin vindt dat gaat hij de modinfo laden)
- Hergebruik van major nummers (en dus alle applicaties op de hoogte van alle beschikbaar applicaties)
```

7. Hoe weet je of een opdracht builtin is? Hoe kan je van zo’n commando Hulp opvragen?
```sh
type -a printf
```

8. Geef 100 random getallen onder elkaar weer in decimale vorm van 64-bit lang.
```bash
shuf -i 1-100 -n 1
for (( i = 0; i < 100; i++ )); do head -c64 /dev/random ; done
for (( i = 0; i < 100; i++ )); do od -cd < /dev/random; done		
```

9. Een usb bestandsysteem is ergens opgeslagen op het systeem, na gebruik van welk commando kan ik het rechtstreeks benaderen?
```bash
dd if=/dev/sda1 of=test.img bs=512 count=1
```

10. Pipeline vertakkingen
```
Doormiddel van een | of via tee
```

11. Unset "y [x]", waarvoor dienen de accolades?
```
Anders zal hij de file yx wegdoen in plaats van de variabele in de array y op plaats x
Kevin: gebruikt globbing: zoekt naar een file yx en gaat deze verwijderen
```

12. Unit1 en unit2, hoe maak je die afhankelijk van elkaar in systemd? Geef 2 onafhankelijke manieren.
```
Doormiddel van een wants of requires bij unit1 voor unit 2 bij opstarten van unit 1 zal unit 2 ook worden opgestart
Wantedby of requiredby bij unit2 bij enabelen van de unit 2 zal bij unit1 een wants of requires worden gezet
```

13. Je mount een usb stick/filesystem en die is voorzien van label, hoe zorg je ervoor dat die altijd in dezelfde folder mount?
```
mount –L label map
```

14. 1gb extra swap geheugen voorzien, hoe doe je dat?
```sh
dd if=/dev/zero of=/root/swapfile bs=1M count=1024MB	    # File als swapspace gebruiken
chmod 600 /root/swapfile 		                            # (enkel root permissie geven)
mkswap /root/swapfile 
swapon /root/swapfile
```

15. Tracht een ex2 superblock te herstellen.
```sh
E2fsck –p EX2
```

16. Hoe weet System V welke achtergrond scripts moeten gestart/gestopt worden bij het betreden van een bepaald runlevel?
```
Er wordt een script uitgevoerd voor naar een bepaald runlevel wordt overgegaan, deze zijn te vinden in /etc/rc.d, deze ma bevat links naar deamons in init.d zodat het script voor een bepaald runlevel kan worden uitgevoerd bij het overgaan naar dat level
Kevin: bij het opstarten wordt het script /etc/rc#.d uitgevoerd waarbij # staat voor het level
```

17. Wat is het verschil tussen $root en root= in de GRUB? Of was deze vraag: Wat is het verschil tussen de Grub $root parameter en de linux eigen root= parameter?
```
$root is de partitie waar het kernelbeeld zich op bevindt
Root= instellen van de partitie waarom gezocht zal worden
```

18. Hoe kan je de output van een bestand zowel doorsturen naar een bestand als naar het scherm?
```
Gebruik makend van tee bv echo "iets" |tee t1
```

19. Hoe koppel je een schijf aan met (sysfs of was dit systemd of systemctl?) 
```sh
Systemctl start map-device.mount
```

20. Schrijf een functie die als enige parameter een variabele heeft, die vervolgens deze variabele kan manipuleren en deze aangepaste variabele teruggeven.

```sh
f(){
	local pin, pout
	pin =${!1}
	pout=...$pin...
	eval “$1=$pout”
}

Kevin:
function() {
    x = $1 + 5;
    return $x;
}
function 10;
echo $?;

```