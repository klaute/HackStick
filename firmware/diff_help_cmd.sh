#!/bin/bash

cat tty.h | grep "_.*\[\]" | grep -v "_str" | grep const | grep prog_char | sed -e "s/.* \"//ig" | sed -e "s/\";$//ig"  | uniq | sort > a
cat help.h  | grep ":" | sed -e "s/:.*$//ig" | grep "\t" | sed -e "s/\\\t//ig" | uniq | sort > b

diff a b | grep "<"

