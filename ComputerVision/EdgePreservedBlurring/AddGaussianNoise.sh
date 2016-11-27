#!/bin/bash
export IFSHOME=$HOME/ifsHOME
export PATH=.:$IFSHOME/MacX64/ifsbin:$PATH
export DYLD_LIBRARY_PATH=$IFSHOME/MacX64/ifslib
gauss -i BLUR1.ifs -o BLUR1.V1.ifs -s 3