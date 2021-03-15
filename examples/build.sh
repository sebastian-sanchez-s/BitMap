#!/bin/sh -x

if [ ! -z "$1" ]
then
    gcc $1 -I../ -L../ -lbmp -o app
fi
