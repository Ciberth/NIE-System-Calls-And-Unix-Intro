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