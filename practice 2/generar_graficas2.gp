# ====================================================================
# Configuración global
# ====================================================================
set terminal pngcairo size 900,600 font "Arial,11"
set datafile separator "|"
set grid

# Función para extraer el valor numérico a la derecha del carácter ":"
val(col) = real(substr(stringcolumn(col), strstrt(stringcolumn(col), ":") + 1, strlen(stringcolumn(col))))


# ====================================================================
# Gráfica 1: Operaciones Básicas - MergeSort (Medio, Mínimo, Máximo)
# ====================================================================
set output "obs_mergesort.png"
set title "Operaciones Básicas - MergeSort"
set xlabel "Tamaño de entrada (N)"
set ylabel "Número de Ejecuciones de la OB (Comparaciones)"
set key top left

plot "merge_resultados.dat" using (val(1)):(val(4)) with linespoints title "Promedio (Average)" lw 2 pt 7 linecolor rgb "red", \
     "merge_resultados.dat" using (val(1)):(val(5)) with linespoints title "Mínimo observado (Min)" lw 1.5 pt 9 linecolor rgb "dark-green", \
     "merge_resultados.dat" using (val(1)):(val(6)) with linespoints title "Máximo observado (Max)" lw 1.5 pt 5 linecolor rgb "orange"