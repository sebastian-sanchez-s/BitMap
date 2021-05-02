#!/bin/sh -x

if [ ! -z "$1" ]
then
    gcc $1 -I../includes -L../ -lbmp -lm -o app
fi
