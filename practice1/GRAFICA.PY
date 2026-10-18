from collections import Counter
import re
import matplotlib.pyplot as plt

# 1. Leer en modo binario ("rb") para omitir problemas de codificación (UTF-8, UTF-16, etc.)
with open("datos.txt", "rb") as file:
    contenido = file.read()

# 2. Extraer todos los dígitos (0 al 9) directamente de los bytes
datos = [int(d) for d in re.findall(rb"\d", contenido)]

if not datos:
    print(
        "No se encontraron dígitos en datos.txt. Revisa que el archivo contenga información."
    )
else:
    # 3. Contar la frecuencia absoluta de cada dígito
    frecuencias = Counter(datos)
    numeros = list(range(10))  # Números del 0 al 9
    conteos = [frecuencias.get(n, 0) for n in numeros]

    # 4. Generar la gráfica de barras
    plt.figure(figsize=(10, 6))
    barras = plt.bar(
        numeros,
        conteos,
        color="royalblue",
        edgecolor="black",
        alpha=0.85,
        zorder=2,
    )

    # Imprimir la frecuencia exacta arriba de cada barra
    for barra in barras:
        yval = barra.get_height()
        if yval > 0:
            plt.text(
                barra.get_x() + barra.get_width() / 2,
                yval + (max(conteos) * 0.01),
                f"{yval}",
                ha="center",
                va="bottom",
                fontsize=10,
                fontweight="bold",
            )

    plt.title(
        "Frecuencia de Dígitos (Práctica 1, Sección 1 - Grupo 9)",
        fontsize=13,
        pad=15,
    )
    plt.xlabel("Dígito", fontsize=11)
    plt.ylabel("Frecuencia Absoluta", fontsize=11)
    plt.xticks(numeros)
    plt.grid(axis="y", linestyle="--", alpha=0.7, zorder=1)

    # Margen superior para evitar recortar las etiquetas de conteo
    plt.ylim(0, max(conteos) * 1.15)

    plt.tight_layout()
    plt.show()