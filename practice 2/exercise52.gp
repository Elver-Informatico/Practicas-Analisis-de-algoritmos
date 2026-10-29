set terminal pngcairo size 900,600 font "Arial,11"
set datafile separator "|"
set grid

val(col) = real(substr(stringcolumn(col), strstrt(stringcolumn(col), ":") + 1, strlen(stringcolumn(col))))

set output "quicksort_comparativa.png"
set title "Operaciones Básicas - QuickSort (promedio)"
set xlabel "Tamaño de entrada (N)"
set ylabel "Número medio de OBs"
set key top left

plot "qs_min_quickshort_resultados.dat"    using (val(1)):(val(4)) with linespoints lw 2 title "QuickSort Min", \
     "qs_mean_quickshort_resultados.dat"   using (val(1)):(val(4)) with linespoints lw 2 title "QuickSort Mean", \
     "qs_median_quickshort_resultados.dat" using (val(1)):(val(4)) with linespoints lw 2 title "QuickSort Median"