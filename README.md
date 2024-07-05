GITHUB: https://github.com/SebaVCH/TallerEstructura3

README Integrantes: Sebastián Vega Chepillo; 21.349.057-5; sebastian.vega03@alumnos.ucn.cl Maximiliano Alfredo Pasten Nayem; 20.169.262-8; maximiliano.pasten@alumnos.ucn.cl

Sistema de Gestión de Transacciones Financieras
Descripción del Problema
Implementar un sistema para gestionar transacciones financieras de un banco. El sistema debe permitir registrar transacciones, detectar patrones de fraude, y generar reportes detallados.
Información sobre los Objetos Creados al Iniciar el Programa

Durante el inicio del programa, se crean los siguientes objetos:
•	Los siguientes objetos son creados a partir del archivo “listadoTransacciones.txt” y son del tipo transacción
{ID: 001, Cuenta Origen: Juan, Cuenta Destino: Pedro, Monto: 1000, Fecha y Hora: 08/06/2024-13:34, Lugar: Coquimbo/Chile}
{ID: 002, Cuenta Origen: Maria, Cuenta Destino: Lucia, Monto: 250, Fecha y Hora: 08/06/2024-14:45, Lugar: Buenos Aires/Argentina}
{ID: 003, Cuenta Origen: Carlos, Cuenta Destino: Ana, Monto: 300, Fecha y Hora: 08/06/2024-15:10, Lugar: Lima/Peru}
{ID: 004, Cuenta Origen: Luis, Cuenta Destino: Sofia, Monto: 500, Fecha y Hora: 08/06/2024-16:22, Lugar: Sao Paulo/Brazil}
{ID: 005, Cuenta Origen: Jorge, Cuenta Destino: Marta, Monto: 750, Fecha y Hora: 08/06/2024-17:30, Lugar: Bogota/Colombia}
{ID: 006, Cuenta Origen: Laura, Cuenta Destino: Miguel, Monto: 200, Fecha y Hora: 08/06/2024-18:15, Lugar: La Serena/Chile}
{ID: 007, Cuenta Origen: Andres, Cuenta Destino: Roberto, Monto: 900, Fecha y Hora: 08/06/2024-19:05, Lugar: Montevideo/Uruguay}
{ID: 008, Cuenta Origen: Elena, Cuenta Destino: Fernando, Monto: 1200, Fecha y Hora: 08/06/2024-20:00, Lugar: Caracas/Venezuela}
{ID: 009, Cuenta Origen: Patricia, Cuenta Destino: Alejandro, Monto: 650, Fecha y Hora: 08/06/2024-21:45, Lugar: Asuncion/Paraguay}
{ID: 010, Cuenta Origen: Ricardo, Cuenta Destino: Daniela, Monto: 800, Fecha y Hora: 08/06/2024-22:10, Lugar: Quito/Ecuador}
{ID: 011, Cuenta Origen: Farfenchos, Cuenta Destino: Farfenchas, Monto: 100000, Fecha y Hora: 02/07/2024-13:59, Lugar: Mexico City/Mexico}
{ID: 012, Cuenta Origen: Pablito, Cuenta Destino: Clavito, Monto: 10000, Fecha y Hora: 03/07/2024-14:50, Lugar: Iquique/Chile}
{ID: 013, Cuenta Origen: Farfenchos, Cuenta Destino: Farfenchas, Monto: 1000, Fecha y Hora: 02/07/2024-13:59, Lugar: Mexico City/Mexico}
{ID: 014, Cuenta Origen: Farfenchos, Cuenta Destino: Farfenchas, Monto: 1000, Fecha y Hora: 02/07/2024-14:00, Lugar: Mexico City/Mexico}
{ID: 015, Cuenta Origen: Farfenchos, Cuenta Destino: Farfenchas, Monto: 1000, Fecha y Hora: 02/07/2024-14:30, Lugar: Mexico City/Mexico}
{ID: 016, Cuenta Origen: Farfenchos, Cuenta Destino: Farfenchas, Monto: 1000, Fecha y Hora: 02/07/2024-14:31, Lugar: Mexico City/Mexico}
{ID: 017, Cuenta Origen: Farfenchos, Cuenta Destino: Farfenchas, Monto: 1000, Fecha y Hora: 02/07/2024-14:32, Lugar: Mexico City/Mexico}
{ID: 018, Cuenta Origen: Farfenchos, Cuenta Destino: Farfenchas, Monto: 1000, Fecha y Hora: 02/07/2024-14:33, Lugar: Mexico City/Mexico}
{ID: 019, Cuenta Origen: Farfenchos, Cuenta Destino: Farfenchas, Monto: 1000, Fecha y Hora: 02/07/2024-14:34, Lugar: Iquique/Chile}

•	Además, se crean varios nodos que le corresponden a cada una de las transacciones mencionadas anteriormente.
•	Y se crean 2 árboles, el primer árbol llamado “ arbolTransacciones”, el cual contiene todas las transacciones sin excepciones, y el  “arbolSospechoso” el cual se crea solo para contener transacciones sospechosas.

Contenido de los Archivos

El proyecto se compone de varios archivos que cumplen funciones específicas:
Archivos de Código Fuente
- main.cpp: Contiene el programa principal que controla la lógica del sistema y las funciones que se usarán al ejecutar el código.
- arbolAVL.cpp y arbolAVL.h: Implementan el árbol AVL utilizado para almacenar y gestionar las transacciones.
- transaccion.cpp y transaccion.h: Definen la estructura de una transacción, almacenando información como el ID, cuentas de origen y destino, monto, fecha y hora, y lugar.


Archivos de Datos
- listadoTransacciones.txt: Archivo de texto que contiene la información de las transacciones realizadas.

Funcionalidades del Sistema

Agregar Nueva Transacción
Permite registrar una nueva transacción con un ID único, cuenta de origen, cuenta de destino, monto, fecha y hora, y lugar.

Buscar Transacción
Permite buscar una transacción específica utilizando su ID.

Eliminar Transacción
Permite eliminar una transacción específica utilizando su ID.

Modificar Transacción
Permite modificar los detalles de una transacción existente.

Cargar Transacciones desde Archivo
Carga todas las transacciones desde el archivo listadoTransacciones.txt al iniciar el programa.

Guardar Transacción en Archivo
Guarda una nueva transacción en el archivo listadoTransacciones.txt.


Instrucciones para Compilar y Ejecutar

Para compilar y ejecutar el programa, sigue estos pasos:

1. Abre la terminal en el directorio del proyecto.
2. Compila el programa utilizando el siguiente comando:
   g++ src/src/*.cpp -o taller
  
3. Ejecuta el programa con el siguiente comando:
   ./taller  

Instrucciones de Uso
1. Ejecuta el programa.
2. Se mostrará un menú de opciones, donde se podrá elegir entre varias opciones:
   - Agregar nueva transacción
   - Buscar transacción
   - Modificar transacción (eliminarla o modificar valores)
   - Generar reporte de transacciones
   - Definir criterios para determinar transacciones sospechosas

3. Sigue las instrucciones proporcionadas por el programa para realizar las diferentes acciones y los resultados se guardarán en el archivo `listadoTransacciones.txt`.
