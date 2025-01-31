#!/bin/bash
tex=$1
base="$(basename ${tex} .tex)"
xelatex -8bit -shell-escape "${tex}" -output-directory="./"
xelatex -8bit -shell-escape "${tex}" -output-directory="./"
retval=$?
if [[ "${retval}" -eq 0 ]]; then
	inkscape --export-type=svg -n 1 "${base}.pdf"
	rm -v "${base}.aux" "${base}.log"
	rm -rfv "_minted-${base}"
fi
exit "${retval}"
