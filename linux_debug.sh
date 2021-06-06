#!/bin/bash

project=ConsoleGameCPP

builddir=bin/debug

rootdir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

mkdir -p ${builddir}
pushd ${builddir}

cmake -G "Unix Makefiles" ${rootdir}  

popd

cmake --build ${builddir} 
