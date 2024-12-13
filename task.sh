#!/bin/bash
tex=$1
base="$(basename ${tex} .tex)"
xelatex "${tex}" -output-directory="./"
xelatex "${tex}" -output-directory="./"
inkscape --export-type=svg -n 1 "${base}.pdf"
