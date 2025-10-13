# ✈️ Gestión de Memoria Dinámica y Listas Enlazadas  
## 💻 Taller: Sistema de Tiquetes de Avión

## 📚 Curso  
- **Estructura de Datos**

## 👤 Integrante  
- **Wilner Andres Gonzalez Gonzalez**

---

## 📘 Descripción del Proyecto
Este proyecto simula el **proceso de venta de tiquetes y abordaje de un avión**, aplicando los conceptos de **memoria dinámica** y **listas enlazadas** en **C**.  

El sistema permite:
- Registrar pasajeros (género y primer apellido)  
- Simular el abordaje según el orden de venta  
- Diferenciar entre pasajeros que abordan y los que no (por sobreventa)  

---

## 🎯 Objetivos

- **Aprender a manejar memoria dinámica** en C mediante `malloc()` y punteros.  
- **Practicar listas enlazadas simples y dobles** para almacenar y organizar información.  
- **Simular un sistema real de venta y abordaje de tiquetes**, aplicando reglas de negocio como sobreventa y orden de abordaje.  
- **Desarrollar habilidades de programación estructurada**, con menú por consola y control de flujo.  

---

## 🧩 Versiones del Proyecto

| Versión | Tipo de Lista | Archivo | Descripción |
|:-------:|:-------------:|:------|:------------|
| 1️⃣ | Lista Simple | `TiquetesAvion.c` | Usa lista enlazada simple para almacenar pasajeros. |
| 2️⃣ | Lista Doble | `TiquetesAvionDoble.c` | Usa lista doblemente enlazada para permitir recorrido hacia adelante y atrás. |

---

## ⚙️ Funcionalidades del Menú

| Opción | Descripción |
|:------:|:------------|
| 1️⃣ | **Establecer Capacidad:** Define el número máximo de pasajeros que el avión puede abordar. |
| 2️⃣ | **Vender Tiquete:** Registra un pasajero si no se ha superado el límite de sobreventa y no ha iniciado el abordaje. |
| 3️⃣ | **Iniciar Abordaje:** Permite abordar a los pasajeros en el orden de venta hasta llenar la capacidad máxima. |
| 4️⃣ | **Ver Abordados:** Muestra la lista de pasajeros que lograron subir al avión. |
| 5️⃣ | **Ver No Abordados:** Muestra la lista de pasajeros que compraron tiquete pero no lograron abordar. |
| 6️⃣ | **Salir:** Finaliza la ejecución del programa. |

---

## 🧮 Reglas de Negocio

- ✨ **Sobreventa:** Se permite hasta un 10% más de la capacidad.  
- 🚫 **Restricción de venta:** No se pueden vender tiquetes una vez iniciado el abordaje.  
- 🔢 **Orden de abordaje:** Los pasajeros abordan en el **orden en que compraron su tiquete**.  
- ❌ **No abordados:** Los pasajeros que exceden la capacidad quedan en una lista separada.  

---

## 🖥️ Ejemplo de Ejecución

===== MENU PRINCIPAL =====

- Establecer capacidad del avion
- Vender tiquete
- Iniciar abordaje
- Ver pasajeros abordados
- Ver pasajeros no abordados
- Salir

---

## 🧱 Estructura del Nodo

- Lista Simple
```c
typedef struct nodo {
    char genero[20];
    char apellido[30];
    struct nodo *sig;
} nodo;

- lista Doble
```c
typedef struct nodo {
    char genero[20];
    char apellido[30];
    struct nodo *ant;
    struct nodo *sig;
} nodo;

Cada nodo representa un pasajero con:

👤 Género
🧾 Primer Apellido
🔗 Puntero(s) al siguiente y anterior nodo

Conceptos Aplicados

🧱 Memoria Dinámica: Uso de malloc() para crear nodos en tiempo de ejecución.
🔗 Listas Enlazadas Simples y Dobles: Manejo de punteros sig y ant para recorrer y organizar la lista.
🚦 Estructuras de Control: Uso de do-while, switch, if, while para el menú y la lógica del programa.
💡 Restricciones de negocio: Control de sobreventa y abordaje en orden de venta.

📁 Archivos Incluidos
TiquetesAvion.c → Lista enlazada simple
TiquetesAvionDoble.c → Lista doblemente enlazada
README.md → Documentación completa del proyecto

