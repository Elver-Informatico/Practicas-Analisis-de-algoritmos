# Configuración global del terminal y parseo
set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set grid lw 1 lt 0 lc rgb '#cccccc'
set style data linespoints
set key left top
set xlabel "Tamaño de la permutación (N)"
set ylabel "Operaciones Básicas (OB)"
set datafile separator "|"

# Función de extracción de valores de las columnas "Clave:Valor"
get_val(s) = real(substr(s, strstrt(s, ":")+1, strlen(s)))
log2(x) = log(x) / log(2)

# Ecuaciones de ajuste O(N log N) calculadas empíricamente
fit_qs_min(x) = 1.383 * x * log2(x) - 2.798 * x
fit_qs_mean(x) = 1.396 * x * log2(x) - 2.938 * x
fit_qs_median(x) = 1.198 * x * log2(x) - 0.939 * x
fit_merge(x) = 1.005 * x * log2(x) - 0.317 * x

# ---------------------------------------------------------
# 1. QuickSort_min: Tiempos (OB) y ajuste
# ---------------------------------------------------------
set output '1_qs_min_ajuste.png'
set title "QuickSort_min - Medio empírico vs Ajuste Teórico"
plot 'qs_min_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(4))) title 'QS Min (Datos)' lc rgb '#d55e00' pt 7, \
     fit_qs_min(x) title 'Ajuste 1.383*N*log2(N)' lc rgb '#000000' dt 2 lw 2

# ---------------------------------------------------------
# 2. QuickSort_min: Mejor, Peor, Medio y Ajuste
# ---------------------------------------------------------
set output '2_qs_min_completa.png'
set title "QuickSort_min - Desglose (Mín, Med, Máx) y Ajuste"
plot 'qs_min_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(6))) title 'Peor Caso (Máx)' lc rgb '#cc0000' pt 9, \
     'qs_min_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(4))) title 'Medio' lc rgb '#d55e00' pt 7, \
     'qs_min_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(5))) title 'Mejor Caso (Mín)' lc rgb '#0072b2' pt 11, \
     fit_qs_min(x) title 'Ajuste (Medio)' lc rgb '#000000' dt 2 lw 2

# ---------------------------------------------------------
# 3. QuickSort_mean: Tiempos (OB) y ajuste
# ---------------------------------------------------------
set output '3_qs_mean_ajuste.png'
set title "QuickSort_mean - Medio empírico vs Ajuste Teórico"
plot 'qs_mean_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(4))) title 'QS Mean (Datos)' lc rgb '#e69f00' pt 7, \
     fit_qs_mean(x) title 'Ajuste 1.396*N*log2(N)' lc rgb '#000000' dt 2 lw 2

# ---------------------------------------------------------
# 4. QuickSort_mean: Mejor, Peor, Medio y Ajuste
# ---------------------------------------------------------
set output '4_qs_mean_completa.png'
set title "QuickSort_mean - Desglose (Mín, Med, Máx) y Ajuste"
plot 'qs_mean_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(6))) title 'Peor Caso (Máx)' lc rgb '#cc0000' pt 9, \
     'qs_mean_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(4))) title 'Medio' lc rgb '#e69f00' pt 7, \
     'qs_mean_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(5))) title 'Mejor Caso (Mín)' lc rgb '#0072b2' pt 11, \
     fit_qs_mean(x) title 'Ajuste (Medio)' lc rgb '#000000' dt 2 lw 2

# ---------------------------------------------------------
# 5. QuickSort_median: Tiempos (OB) y ajuste
# ---------------------------------------------------------
set output '5_qs_median_ajuste.png'
set title "QuickSort_median - Medio empírico vs Ajuste Teórico"
plot 'qs_median_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(4))) title 'QS Median (Datos)' lc rgb '#009e73' pt 7, \
     fit_qs_median(x) title 'Ajuste 1.198*N*log2(N)' lc rgb '#000000' dt 2 lw 2

# ---------------------------------------------------------
# 6. QuickSort_median: Mejor, Peor, Medio y Ajuste
# ---------------------------------------------------------
set output '6_qs_median_completa.png'
set title "QuickSort_median - Desglose (Mín, Med, Máx) y Ajuste"
plot 'qs_median_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(6))) title 'Peor Caso (Máx)' lc rgb '#cc0000' pt 9, \
     'qs_median_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(4))) title 'Medio' lc rgb '#009e73' pt 7, \
     'qs_median_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(5))) title 'Mejor Caso (Mín)' lc rgb '#0072b2' pt 11, \
     fit_qs_median(x) title 'Ajuste (Medio)' lc rgb '#000000' dt 2 lw 2

# ---------------------------------------------------------
# 7. MergeSort: Tiempo medio (OB) y ajuste
# ---------------------------------------------------------
set output '7_merge_ajuste.png'
set title "MergeSort - Medio empírico vs Ajuste Teórico"
plot 'merge_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(4))) title 'MergeSort (Datos)' lc rgb '#56b4e9' pt 7, \
     fit_merge(x) title 'Ajuste 1.005*N*log2(N)' lc rgb '#000000' dt 2 lw 2

# ---------------------------------------------------------
# 8. Comparativa MergeSort vs QuickSort_median
# ---------------------------------------------------------
set output '8_comparativa_merge_qsmedian.png'
set title "Comparativa de Tiempos (OB): MergeSort vs Mejor QuickSort (Median)"
plot 'merge_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(4))) title 'MergeSort' lc rgb '#56b4e9' pt 7 lw 2, \
     'qs_median_quickshort_resultados.dat' using (get_val(stringcolumn(1))):(get_val(stringcolumn(4))) title 'QuickSort Median' lc rgb '#009e73' pt 5 lw 2