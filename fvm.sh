#!/usr/bin/env bash

fvm_help() {
    echo "FVM Script Help"
    echo " ./fvm.sh build"
    echo "      Build FVM"
}

fvm_build() {
    #TODO: Use other compilers
    dmd src/fvm/*.d #-v
}

if [ -z $1 ]; then
    hc_help
    exit
fi

if [ "$(type -t "fvm_$1")" = "function" ]; then
    "fvm_$@"
else
    >&2 echo "Unknown command: '$@'. Type '$0 help' for more information."
    exit 1
fi