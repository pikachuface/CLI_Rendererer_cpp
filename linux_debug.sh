#!/bin/bash

project=ConsoleGameCPP

builddir=debug
executabledir=bin

rootdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

mkdir -p ${builddir}
pushd ${builddir}

cmake -G "Unix Makefiles" ${rootdir}  

popd

mkdir ${executabledir}

cmake --build ${builddir} 
