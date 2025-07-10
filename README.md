
# 🖥️ Proyecto: Monitor de Temperatura con Arduino y Flask

Este proyecto permite monitorear la temperatura en tiempo real usando un sensor LM35 conectado a un Arduino Uno, y visualizarla en una página web desarrollada en Flask. Además, permite configurar umbrales de temperatura y perfiles para diferentes ambientes.

---

## 📦 Materiales

- **Arduino Uno R3**
- **Sensor LM35**
- **Pantalla LCD 16x2 (con controlador HD44780)**
- **Potenciómetro (para contraste del LCD)**
- **3 LEDs**: rojo, verde, amarillo
- **Buzzer (zumbador pasivo)**
- **Cables macho-macho**
- **Protoboard**
- **Resistencias de 200 ohmios (para los LEDs)**
- **Cable USB para conexión Arduino**
- **Batería Toshiba 9V (opcional para alimentación externa)**

---

## 🖥️ Software Necesario

- **Arduino IDE**
    - [Descargar Arduino IDE](https://www.arduino.cc/en/software)

- **Python 3.12**
    - [Descargar Python](https://www.python.org/downloads/)

- **Visual Studio Code (opcional)**
    - [Descargar VS Code](https://code.visualstudio.com/)

---

## 📚 Librerías Python

Instalar desde la terminal o PowerShell:

```bash
pip install pyserial flask
```

---

## ⚡ Esquema de Conexión

### LM35

| Pin LM35 | Arduino |
| -------- | ------- |
| Vout     | A0      |
| GND      | GND     |
| Vcc      | 5V      |

### LCD 16x2

- RS → Pin 12
- E  → Pin 11
- D4 → Pin 5
- D5 → Pin 4
- D6 → Pin 3
- D7 → Pin 2
- Potenciómetro entre Vcc - GND (pin intermedio al pin VO del LCD)

### LEDs

| Color    | Pin Arduino |
| -------- | ----------- |
| Rojo     | 6           |
| Verde    | 7           |
| Amarillo | 8           |

### Buzzer

- Pin positivo → Pin 9
- Pin negativo → GND

---

## 🔌 Pasos para Configurar el Proyecto

### 1. Montaje del Circuito

- Conectar el LM35 al pin A0.
- Conectar la pantalla LCD 16x2.
- Conectar LEDs con resistencias de 200 Ω.
- Conectar buzzer.
- Alimentar Arduino vía USB o batería 9V (opcional).

### 2. Subir Código al Arduino

- Abrir el código Arduino en el IDE (archivo `.ino`).
- Conectar Arduino por USB.
- Seleccionar el puerto adecuado en el menú **Herramientas > Puerto**.
- Seleccionar la placa **Arduino Uno**.
- Subir el programa.

### 3. Configurar Python

- Instalar Python ≥ 3.12.
- Instalar dependencias:

    ```bash
    pip install pyserial flask
    ```

- Colocar los archivos del servidor Flask en una carpeta, por ejemplo:

    ```
    proyecto/
    ├── app.py
    ├── templates/
    │    └── index.html
    └── arduino/
         └── monitor_temperatura.ino
    ```

### 4. Ejecutar el Servidor Flask

Desde la carpeta del proyecto:

```bash
python app.py
```

- La aplicación estará disponible en:

    ```
    http://localhost:5000
    ```

---

## 🌐 Funcionalidades

✅ Lectura en tiempo real de la temperatura.  
✅ Visualización en LCD y en web.  
✅ LEDs y buzzer para alarmas:
   - Temperatura baja → LED amarillo + buzzer
   - Temperatura alta → LED rojo + buzzer
   - Temperatura normal → LED verde
✅ Configuración de umbrales mínimo y máximo vía web.  
✅ Selección de perfiles predefinidos (Aula, Biblioteca, Comedor, etc.)

---


## 🚀 Cómo Usar

1. Conectar Arduino al PC.
2. Ejecutar Flask:
    ```bash
    python app.py
    ```
3. Abrir navegador:
    ```
    http://localhost:5000
    ```
4. Visualizar temperatura y configurar umbrales o perfiles.

---

## 📝 Notas

- El servidor Flask detecta automáticamente el puerto del Arduino (CH340 o USB-SERIAL).
- Asegúrate de que ninguna otra aplicación (p. ej. Arduino Serial Monitor) esté usando el puerto COM mientras se ejecuta Flask.
- Los datos se actualizan automáticamente cada segundo en la web.

---
