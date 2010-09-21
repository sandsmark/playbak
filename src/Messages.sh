#! /usr/bin/env bash
$EXTRACTRC `find . -name \*.rc` >> rc.cpp
$XGETTEXT *.cpp -o $podir/playbak.pot
rm -f *.cpp
