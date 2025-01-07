#!/bin/bash
tex=$1
base="$(basename ${tex} .tex)"
xelatex "${tex}" -output-directory="./"
xelatex "${tex}" -output-directory="./"
retval=$?
if [[ "${retval}" -eq 0 ]]; then
	inkscape --export-type=svg -n 1 "${base}.pdf"
	rm -v "${base}.aux" "${base}.log"
fi
exit "${retval}"
