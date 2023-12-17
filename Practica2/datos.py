import pandas as pd
import re

# Lee el archivo de texto
with open('datos.txt', 'r') as file:
    contenido = file.read()

# Encuentra todas las secuencias que coincidan con el patrón
patron = r'\{([^}]*)\}'
resultados = re.findall(patron, contenido)

# Convierte las cadenas de texto encontradas en listas de números
datos = [list(map(float, resultado.split(','))) for resultado in resultados]

# Crea un DataFrame de pandas
df = pd.DataFrame(datos)
# Obtener el valor mínimo por columna
minimos = df.min()

# Obtener el valor máximo por columna
maximos = df.max()

# Imprimir los resultados
print("Mínimos por columna:")
print(minimos)

print("\nMáximos por columna:")
print(maximos)

# Muestra el DataFrame
print(df)

df.to_csv('datos.csv', index=False, header=False)