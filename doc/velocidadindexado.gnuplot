set terminal eepic
set output "velocidadindexado.tex"
set xlabel "Tama�o del corpus"
plot [0:162] "velindexado3.dat" with linespoint, "velindexado4.dat" with linespoint, "velindexado5.dat" with linespoint
