#!/bin/bash
set -e -u

CMAKE_CURRENT_SOURCE_DIR=$1
CMAKE_CURRENT_BINARY_DIR=$2
OUTPUT=$3

((cat ${CMAKE_CURRENT_BINARY_DIR}/goby-dev.doxy; bzr version-info --custom --template="PROJECT_NUMBER = \"Series: {branch_nick}, revision: {revno}, released on {date} \"") | doxygen - 

pushd $CMAKE_CURRENT_BINARY_DIR/latex
cat refman.tex | sed 's|\\chapter{Namespace Index}|\\appendix\\chapter{Namespace Index}|'  | sed 's|\\include|\\input|' | sed "s|\\\begin{document}|\\\graphicspath{{${CMAKE_CURRENT_BINARY_DIR}/latex}}\n\\\begin{document}|" > refman2.tex

mv refman2.tex refman.tex
make
cp refman.pdf $OUTPUT
popd

)
