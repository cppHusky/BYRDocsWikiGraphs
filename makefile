svg:pdf
ifdef tex
	base=$$(basename ${tex} .tex) && inkscape --export-type=svg -n 1 "$${base}.pdf"
endif
pdf:
ifdef tex
	xelatex -8bit --shell-escape ${tex} -output-directory="./"
	xelatex -8bit --shell-escape ${tex} -output-directory="./"
endif
clean:
	rm -fv *.pdf *.svg *.aux *.log _minted-*
