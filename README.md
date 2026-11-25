# Sensores y actuadores con sockets — C + Java

Simulación de un pequeño sistema **IoT distribuido** en el que programas escritos en **C** y en **Java** se comunican entre sí por red mediante **sockets UDP y TCP**. Demuestra que la comunicación por sockets es independiente del lenguaje.

## 🏗️ Arquitectura
```
┌────────┐  UDP   ┌──────────────────┐  TCP   ┌─────────────────────────┐
│ Sensor │ ─────► │ Gestor de medidas│ ─────► │ Actuador de temperatura │
└────────┘        │(decide si actuar)│ ─────► │ Actuador de luz         │
                  └──────────────────┘        └─────────────────────────┘
```

| Componente | Lenguaje | Protocolo | Función |
|---|---|---|---|
| `sensor.c` | C | UDP (cliente) | Genera medidas aleatorias de temperatura o luz y las envía al gestor |
| `GestorDeMedidas.java` | Java | UDP (servidor) → TCP (cliente) | Recibe las medidas y, si están fuera de rango, avisa al actuador correspondiente |
| `ActivadorT.java` | Java | TCP (servidor) | Actuador de temperatura: activa el climatizador |
| `activadorL.c` | C | TCP (servidor) | Actuador de luz: enciende la luz |

Todas las IP y puertos se piden por consola al arrancar (con validación), así que los componentes pueden ejecutarse en máquinas distintas.

## ▶️ Cómo ejecutarlo
```bash
cd "Sockets c y Java"
gcc activadorL.c -o activadorL
gcc sensor.c -o sensor
javac ActivadorT.java GestorDeMedidas.java
```
Arranca en este orden (cada uno en una terminal):
1. `./activadorL` y `java ActivadorT` (actuadores)
2. `java GestorDeMedidas`
3. `./sensor`

## 📄 Documentación
La memoria de la entrega está en `Sockets c y Java/MEMORIA SEGUNDA ENTREGA.docx`.

## 🛠️ Tecnologías
C (POSIX sockets) · Java (`java.net`) · UDP · TCP
