# Interesting One-liners and explanation in bash

1. [Search specific string in a file over multiple files](#searchmul)
2. [Man pages, info and help](#man)
3. [Generate a random password](#pass)
4. [File omleiding](#omleiding)
5. [Shell globbing](#globbing)


## Search specific string in a file over multiple files <a name="searchmul"></a>

```sh
find . -type f -name "*.c" -exec grep -il 'fork()' {} \;
find . -type f -name "*.sh" -exec grep -il '\[\[' {} \;
```

## Man pages, info and help <a name="man"></a>

```sh
man -f kill     # overzicht 
apropos kill    # zelfde

man kill
man 2 kill

info kill       # emacs manier - vaak met meer vbn

man -k dhcp     # gaat in man pages op zoek naar dhcp

nl --help       # commands hebben vaak --help

help shopt      # help gaat op interne commandos
help case       # via opties: -s voor syntax
                # -d voor description
                # -m voor man formaat

```

## Generate a random password <a name="pass"></a>

```sh
shuf -rn 16 -e {a..z}
shuf -rn 16 -e {a..z} | paste -sd ''
```

## File omleiding <a name="omleiding"></a>

```sh
ls -l t xxx >> t1 2> t2     # Uitvoer omleiden en appenden naar t1
                            # Error omleiden naar t2
ls -l t xxx > t1 2>&1       # Hier uitvoer naar t1 en error naar uitvoer
                            # dus ook naar t1, let op volgorde!
```

## Shell globbing <a name="globbing"></a>

```sh
        # patronen
        # * willekeurig gelijk hoeveel keer 
        # ? 1 willekeurig karakter 
ls * 
ls a*
ls t? 
ls t[a-z]*
```

## Extended globbing

```sh
            # Make sure to check if extended globbing is on
            # In interactive mode ~> on
            # In scripts ~> off

ls -d -d @(*.d|*.conf)

            # All files that answer to .d OR .conf

ls -d !(@(*.d|*.conf))

            # Everything EXCEPT .d and .conf

```

## Reduce numbers

```sh
shuf -rn100 -e y y y y y y y y n | rm -iv {00..99} 

                # You only let 1 live
```

## Rotating a matrix of numbers

```sh
shuf -rn36 -i 0..9      
                    # creating random numbers

shuf -rn36 -i 0..9 | xargs -n6 echo 

                    # group them in columns

shuf -rn36 -i 0..9 | xargs -n6 > x 

                    # x holds the matrix now

xargs -n1 < x | split -l 6

                    # every 6 we split

shuf -rn36 -i 0..9 | xargs -n1 | split -l 6 

                    # total example without x
cat xaa

paste -d ' ' xa*


```

## Wc insert result in variable trick 

```sh
wc -w < winners.csv         # nu krijg je geen bestandsnaam meer

strings -n $(wc -L competitors.csv) competitors.csv 

                            # wc -L geeft grootste lijn
                            # strings gebruiken om deze te zien
```

## Tr trick to chomp whitespace

```sh
echo 'x         y           z' | tr ' ' ','     # alle blancos vervangen door een ,

echo 'x         y           z' | tr -s ' ' ','  # squeze dus dan maar 1 , meer
```


## Join 

```sh
```

## Grep 

```sh
dig google.com | grep -A1 ";; ANSWER SECTION:" | grep -v ";; ANSWER SECTION:" 
            # Basicly grep the ;; ANSWER SECTION and 1 extra line ~> A1
            # Then invert the selection with -v
            # Meaning we get the line after ;; ANSWER SECTION
```

## Primenumbers

```sh
x=0 ; while ((++x)) ; do y=($(factor $x)) ; ((${#y[@]} == 2)) && echo $x ; sleep 0.5 ; done 
```


## IP adresses

```sh
```