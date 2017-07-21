Resultados_hw3.pdf: Resultados_hw3.tex  Resultados_hw3.pdf
	pdflatex $<

Resultados_hw3.pdf : datos.dat Plots_Planetas.py
	python Plots_Planetas.py

datos.dat : a.out
	./a.out

a.out : Planetas.c
	gcc -lm Planetas.c

clean :
	rm datos.dat  Resultados_hw3.pdf a.log a.aux a.out
