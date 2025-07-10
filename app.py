from flask import Flask, render_template, request, redirect, url_for
import serial.tools.list_ports
import serial
import time

app = Flask(__name__)

# Variables globales
arduino = None
temperatura_actual = None
umbral_min = None
umbral_max = None

# Detectar puerto disponible
def detectar_puerto():
    puertos = serial.tools.list_ports.comports()
    for puerto in puertos:
        if "Arduino" in puerto.description or "CH340" in puerto.description or "USB-SERIAL" in puerto.description:
            return puerto.device
    return None

# Inicializar conexión una sola vez
def inicializar_arduino():
    global arduino
    if arduino and arduino.is_open:
        return  # Ya conectado

    puerto = detectar_puerto()
    if puerto:
        try:
            arduino = serial.Serial(puerto, 9600, timeout=1)
            time.sleep(2)  # Espera inicial para que el Arduino esté listo
        except:
            arduino = None

# Leer datos sin reiniciar el puerto
def leer_datos():
    global temperatura_actual, umbral_min, umbral_max, arduino
    if arduino and arduino.is_open:
        try:
            arduino.write(b"STATUS\n")
            inicio = time.time()
            while time.time() - inicio < 2:
                if arduino.in_waiting:
                    linea = arduino.readline().decode().strip()
                    if linea.startswith("TEMP:"):
                        temperatura_actual = float(linea.replace("TEMP:", ""))
                    elif linea.startswith("UMBRALMIN:"):
                        umbral_min = float(linea.replace("UMBRALMIN:", ""))
                    elif linea.startswith("UMBRALMAX:"):
                        umbral_max = float(linea.replace("UMBRALMAX:", ""))
            return True
        except:
            return False
    return False

@app.route('/')
def index():
    inicializar_arduino()
    conectado = leer_datos()
    return render_template('index.html',
                           temperatura=temperatura_actual,
                           umbral_min=umbral_min,
                           umbral_max=umbral_max,
                           arduino_conectado=conectado)

@app.route('/set_umbral', methods=['POST'])
def set_umbral():
    global arduino
    min_temp = request.form.get('min_temp')
    max_temp = request.form.get('max_temp')

    if arduino and arduino.is_open:
        try:
            if min_temp:
                arduino.write(f"SETMIN:{min_temp}\n".encode())
            if max_temp:
                arduino.write(f"SETMAX:{max_temp}\n".encode())
        except:
            pass
    return redirect(url_for('index'))

@app.route('/set_perfil', methods=['POST'])
def set_perfil():
    global arduino
    perfil = request.form.get('perfil')
    perfiles = {
        "aula": (20.0, 24.0),
        "biblioteca": (19.0, 23.0),
        "comedor": (21.0, 25.0),
        "sala": (20.0, 24.0),
        "dormitorio": (18.0, 22.0),
        "oficina": (20.0, 24.0),
        "datacenter": (18.0, 22.0),
        "almacen": (15.0, 25.0),
        "hospital": (20.0, 23.0)
    }

    if perfil in perfiles and arduino and arduino.is_open:
        min_temp, max_temp = perfiles[perfil]
        try:
            arduino.write(f"SETMIN:{min_temp}\n".encode())
            arduino.write(f"SETMAX:{max_temp}\n".encode())
        except:
            pass

    return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)
