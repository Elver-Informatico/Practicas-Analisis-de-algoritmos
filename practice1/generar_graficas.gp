# ====================================================================
# Configuración global
# ====================================================================
set terminal pngcairo size 900,600 font "Arial,11"
set datafile separator "|"
set grid

# Función para extraer el valor numérico a la derecha del carácter ":"
val(col) = real(substr(stringcolumn(col), strstrt(stringcolumn(col), ":") + 1, strlen(stringcolumn(col))))

# ====================================================================
# Gráfica 1: Comparativa de Tiempos de CPU (InsertSort vs BubbleSort)
# ====================================================================
set output "comparativa_tiempos.png"
set title "Comparativa de Tiempos Medios de CPU"
set xlabel "Tamaño de entrada (N)"
set ylabel "Tiempo medio de CPU (segundos)"
set key top left

plot "insert_resultados.dat" using (val(1)):(val(3)) with linespoints title "InsertSort" lw 2 pt 7 linecolor rgb "blue", \
     "bubble_resultados.dat" using (val(1)):(val(3)) with linespoints title "BubbleSort" lw 2 pt 5 linecolor rgb "red"

# ====================================================================
# Gráfica 2: Operaciones Básicas - InsertSort (Medio, Mínimo, Máximo)
# ====================================================================
set output "obs_insertsort.png"
set title "Operaciones Básicas - InsertSort"
set xlabel "Tamaño de entrada (N)"
set ylabel "Número de Ejecuciones de la OB (Comparaciones)"
set key top left

plot "insert_resultados.dat" using (val(1)):(val(4)) with linespoints title "Promedio (Average)" lw 2 pt 7 linecolor rgb "blue", \
     "insert_resultados.dat" using (val(1)):(val(5)) with linespoints title "Mínimo observado (Min)" lw 1.5 pt 9 linecolor rgb "dark-green", \
     "insert_resultados.dat" using (val(1)):(val(6)) with linespoints title "Máximo observado (Max)" lw 1.5 pt 5 linecolor rgb "orange"

# ====================================================================
# Gráfica 3: Operaciones Básicas - BubbleSort (Medio, Mínimo, Máximo)
# ====================================================================
set output "obs_bubblesort.png"
set title "Operaciones Básicas - BubbleSort"
set xlabel "Tamaño de entrada (N)"
set ylabel "Número de Ejecuciones de la OB (Comparaciones)"
set key top left

plot "bubble_resultados.dat" using (val(1)):(val(4)) with linespoints title "Promedio (Average)" lw 2 pt 7 linecolor rgb "red", \
     "bubble_resultados.dat" using (val(1)):(val(5)) with linespoints title "Mínimo observado (Min)" lw 1.5 pt 9 linecolor rgb "dark-green", \
     "bubble_resultados.dat" using (val(1)):(val(6)) with linespoints title "Máximo observado (Max)" lw 1.5 pt 5 linecolor rgb "orange"