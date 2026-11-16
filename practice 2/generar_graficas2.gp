set terminal pngcairo size 800,600 enhanced font 'Verdana,10'
set grid lw 1 lt 0 lc rgb '#cccccc'
set style data linespoints
set key left top

# El uso de múltiples separadores extrae directamente los valores numéricos:
# $2=N, $4=N_elems, $6=Time, $8=Average, $10=Min, $12=Max
set datafile separator "|:"

log2(x) = log(x) / log(2)

# 1. Definición de ecuaciones teóricas O(N log N) para Operaciones Básicas (OB) y Tiempos (t)
f_merge_ob(x) = am_ob * x * log2(x) + bm_ob * x
f_merge_t(x)  = am_t * x * log2(x) + bm_t * x

f_qmin_ob(x) = aqmin_ob * x * log2(x) + bqmin_ob * x
f_qmin_t(x)  = aqmin_t * x * log2(x) + bqmin_t * x

f_qmean_ob(x) = aqmean_ob * x * log2(x) + bqmean_ob * x
f_qmean_t(x)  = aqmean_t * x * log2(x) + bqmean_t * x

f_qmed_ob(x) = aqmed_ob * x * log2(x) + bqmed_ob * x
f_qmed_t(x)  = aqmed_t * x * log2(x) + bqmed_t * x

# 2. Inicialización obligatoria para evitar el error "undefined variable" en fit
am_ob=1; bm_ob=1; am_t=1e-5; bm_t=1e-5;
aqmin_ob=1; bqmin_ob=1; aqmin_t=1e-5; bqmin_t=1e-5;
aqmean_ob=1; bqmean_ob=1; aqmean_t=1e-5; bqmean_t=1e-5;
aqmed_ob=1; bqmed_ob=1; aqmed_t=1e-5; bqmed_t=1e-5;

# 3. Ajustes automáticos (calculan coeficientes a partir de las columnas $2 y $8 u $6)
fit f_merge_ob(x) 'merge_resultados.dat' using 2:8 via am_ob, bm_ob
fit f_merge_t(x) 'merge_resultados.dat' using 2:6 via am_t, bm_t

fit f_qmin_ob(x) 'qs_min_quickshort_resultados.dat' using 2:8 via aqmin_ob, bqmin_ob
fit f_qmin_t(x) 'qs_min_quickshort_resultados.dat' using 2:6 via aqmin_t, bqmin_t

fit f_qmean_ob(x) 'qs_mean_quickshort_resultados.dat' using 2:8 via aqmean_ob, bqmean_ob
fit f_qmean_t(x) 'qs_mean_quickshort_resultados.dat' using 2:6 via aqmean_t, bqmean_t

fit f_qmed_ob(x) 'qs_median_quickshort_resultados.dat' using 2:8 via aqmed_ob, bqmed_ob
fit f_qmed_t(x) 'qs_median_quickshort_resultados.dat' using 2:6 via aqmed_t, bqmed_t

# --- GRÁFICAS ---

# Gráfica 1
set output '1_mergesort_ob_completa.png'
set title "MergeSort - Comparativa (Mín, Med, Máx) en OB y Ajuste"
set ylabel "Operaciones Básicas (OB)"
plot 'merge_resultados.dat' using 2:12 title 'Peor Caso' lc rgb '#cc0000' pt 9, \
     'merge_resultados.dat' using 2:8 title 'Medio' lc rgb '#009e73' pt 7, \
     'merge_resultados.dat' using 2:10 title 'Mejor Caso' lc rgb '#0072b2' pt 11, \
     f_merge_ob(x) title 'Ajuste O(N log N)' lc rgb '#000000' dt 2 lw 2

# Gráfica 2
set output '2_mergesort_tiempo.png'
set title "MergeSort - Tiempo Medio de Reloj y Ajuste"
set ylabel "Tiempo CPU (s)"
plot 'merge_resultados.dat' using 2:6 title 'Tiempo' lc rgb '#009e73' pt 7, \
     f_merge_t(x) title 'Ajuste O(N log N)' lc rgb '#000000' dt 2 lw 2

# Gráfica 3
set output '3_qs_min_ajuste.png'
set title "QuickSort min - Tiempos en OB y Ajuste"
set ylabel "Operaciones Básicas (OB)"
plot 'qs_min_quickshort_resultados.dat' using 2:8 title 'Medio (OB)' lc rgb '#d55e00' pt 7, \
     f_qmin_ob(x) title 'Ajuste O(N log N)' lc rgb '#000000' dt 2 lw 2

# Gráfica 4
set output '4_qs_min_ob_completa.png'
set title "QuickSort min - Comparativa (Mín, Med, Máx) en OB y Ajuste"
plot 'qs_min_quickshort_resultados.dat' using 2:12 title 'Peor Caso' lc rgb '#cc0000' pt 9, \
     'qs_min_quickshort_resultados.dat' using 2:8 title 'Medio' lc rgb '#d55e00' pt 7, \
     'qs_min_quickshort_resultados.dat' using 2:10 title 'Mejor Caso' lc rgb '#0072b2' pt 11, \
     f_qmin_ob(x) title 'Ajuste O(N log N)' lc rgb '#000000' dt 2 lw 2

# Gráfica 5
set output '5_qs_mean_ajuste.png'
set title "QuickSort mean - Tiempos en OB y Ajuste"
plot 'qs_mean_quickshort_resultados.dat' using 2:8 title 'Medio (OB)' lc rgb '#e69f00' pt 7, \
     f_qmean_ob(x) title 'Ajuste O(N log N)' lc rgb '#000000' dt 2 lw 2

# Gráfica 6
set output '6_qs_mean_ob_completa.png'
set title "QuickSort mean - Comparativa (Mín, Med, Máx) en OB y Ajuste"
plot 'qs_mean_quickshort_resultados.dat' using 2:12 title 'Peor Caso' lc rgb '#cc0000' pt 9, \
     'qs_mean_quickshort_resultados.dat' using 2:8 title 'Medio' lc rgb '#e69f00' pt 7, \
     'qs_mean_quickshort_resultados.dat' using 2:10 title 'Mejor Caso' lc rgb '#0072b2' pt 11, \
     f_qmean_ob(x) title 'Ajuste O(N log N)' lc rgb '#000000' dt 2 lw 2

# Gráfica 7
set output '7_qs_median_ajuste.png'
set title "QuickSort median - Tiempos en OB y Ajuste"
plot 'qs_median_quickshort_resultados.dat' using 2:8 title 'Medio (OB)' lc rgb '#cc79a7' pt 7, \
     f_qmed_ob(x) title 'Ajuste O(N log N)' lc rgb '#000000' dt 2 lw 2

# Gráfica 8
set output '8_qs_median_ob_completa.png'
set title "QuickSort median - Comparativa (Mín, Med, Máx) en OB y Ajuste"
plot 'qs_median_quickshort_resultados.dat' using 2:12 title 'Peor Caso' lc rgb '#cc0000' pt 9, \
     'qs_median_quickshort_resultados.dat' using 2:8 title 'Medio' lc rgb '#cc79a7' pt 7, \
     'qs_median_quickshort_resultados.dat' using 2:10 title 'Mejor Caso' lc rgb '#0072b2' pt 11, \
     f_qmed_ob(x) title 'Ajuste O(N log N)' lc rgb '#000000' dt 2 lw 2

# Gráfica 9
set output '9_qs_comparativa_reloj.png'
set title "Comparativa: Tiempo de Reloj en variantes QuickSort"
set ylabel "Tiempo CPU (s)"
plot 'qs_min_quickshort_resultados.dat' using 2:6 title 'QS Min' lc rgb '#d55e00' pt 7 lw 2, \
     'qs_mean_quickshort_resultados.dat' using 2:6 title 'QS Mean' lc rgb '#e69f00' pt 9 lw 2, \
     'qs_median_quickshort_resultados.dat' using 2:6 title 'QS Median' lc rgb '#cc79a7' pt 11 lw 2

# Gráfica 10
set output '10_comparativa_merge_qs_mejor.png'
set title "Comparativa: Tiempo Reloj (MergeSort vs Mejor QuickSort)"
plot 'merge_resultados.dat' using 2:6 title 'MergeSort' lc rgb '#009e73' pt 7 lw 2, \
     'qs_median_quickshort_resultados.dat' using 2:6 title 'QuickSort Median' lc rgb '#cc79a7' pt 11 lw 2