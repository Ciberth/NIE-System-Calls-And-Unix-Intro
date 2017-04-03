# History of Unix

(See lesweek 1)

A **distribution** is the linux **kernel** (incl system calls and POSIX interface) + **services** (servers, daemons) + **utilities** (eg. GNU). And in a lot of cases with a _programming_ and _GUI environment_ (KDE, GNOME).


**Shell** = user interface (CLI) + command interpreter (_interactie_) + scripts (_niet interactief_).


# Bash intro

In bash **spaces** are **important**. I want to emphasize this before discussing anything else. In addition everything in bash (and linux/unix for that matter) is **case-sensitive**. Which is in my opinion a good thing! Furthermore in unix everything should be seen as a file and it uses a tree-structure to documentate and structure files. Lastly a file that starts with a . (dot) is called a hidden file.

The above things are godlike rules and should be the first thing you accept when working in bash. When performing commands for example the command ``shuf`` for creating numbers you should make note that you can add **options**. There are short-named options such as -n for example or long-named such as --head-count. I won't go into detail about the historical changes about these things but you should realise that both exist and that you **need** to look things up in the _man pages_ to see what they do. As an exercise try the following stuff in a bash terminal:

````sh 
shuf
man shuf 
shuf -n 5 -i 100-200
shuf -rn 5 -e {a..z}
```

When **constructing** a command you need the **man pages**, when **understanding a constructed command** you can use the site [explainshell](http://explainshell.com) for a nice overview of commands and options.



# Environment and Shell variables

```sh
declare -p 		# gives a list of all variables
x=123			# creates a variable
declare x=123	# declares a variable
echo $x			# will echo (show on outputstream) the contens of x

```

Note that don't use a $ when creating a variable. Afterwards you always use the $ sign to refer to that variable. 

The ``declare -x x`` is an interesting option to discuss. When creating a variable by default, any subshell of bash won't have access to that variable. With the ``declare -x VAR`` all subshells will have access to that variable (so you don't have to export).

## Interesting commands to try out as an example:

```sh
declare x=123
declare -x x
bash
declare -p x
env
exit
y=456
export y
env

``` 

# Options for bash

Bash is a program, just like the shuff command we introduced before. Therefore it is not that astonishing that bash itself has options of its own. We call them ``shell options``. 


```sh

set +/- o 		# shell options 
shop -o 		# shell options 

set -o 			# gives list of all options 
set +o 			# list so that you can parse them for scripts 

# interesting examples are 

set +/-o verbose
set +/-o xtrace
set +/-o noclobber 


```
