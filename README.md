# BaraOS - Sistema Operativo Simple para Gestión de Archivos

BaraOS es un sistema operativo minimalista diseñado específicamente para la gestión de archivos. Está desarrollado en C y Assembly, y puede ejecutarse en QEMU desde MSYS2 en Windows.

## Características

- **Sistema de archivos virtual en memoria**
- **Interfaz de línea de comandos intuitiva**
- **Comandos básicos de gestión de archivos**
- **Booteable desde disco**
- **Compatible con QEMU**

## Comandos Disponibles

- `help` - Mostrar lista de comandos
- `clear` - Limpiar pantalla
- `ls` - Listar archivos y directorios
- `pwd` - Mostrar directorio actual
- `mkdir <nombre>` - Crear directorio
- `touch <archivo>` - Crear archivo vacío
- `rm <nombre>` - Eliminar archivo o directorio
- `cd <directorio>` - Cambiar directorio
- `cat <archivo>` - Mostrar contenido de archivo
- `echo <texto> > <archivo>` - Escribir texto a archivo

## Requisitos

### En Windows con MSYS2:
```bash
# Instalar herramientas necesarias
pacman -S mingw-w64-x86_64-gcc
pacman -S nasm
pacman -S qemu
pacman -S make
```

### En Linux:
```bash
# Ubuntu/Debian
sudo apt-get install gcc nasm qemu-system-x86 make

# Arch Linux
sudo pacman -S gcc nasm qemu make
```

## Compilación y Ejecución

1. **Clonar el repositorio:**
```bash
git clone https://github.com/tuusuario/BaraOS.git
cd BaraOS
```

2. **Compilar:**
```bash
make
```

3. **Ejecutar en QEMU:**
```bash
make run
# o
./run.sh
```

## Estructura del Proyecto

```
BaraOS/
├── boot.asm          # Bootloader
├── kernel.c          # Kernel principal
├── kernel_entry.asm  # Punto de entrada del kernel
├── screen.c          # Driver de pantalla
├── screen.h          # Header de pantalla
├── keyboard.c        # Driver de teclado
├── keyboard.h        # Header de teclado
├── filesystem.c      # Sistema de archivos
├── filesystem.h      # Header de sistema de archivos
├── string.c          # Funciones de cadenas
├── string.h          # Header de cadenas
├── memory.c          # Gestión de memoria
├── memory.h          # Header de memoria
├── link.ld           # Script del linker
├── Makefile          # Script de compilación
├── run.sh            # Script de ejecución
└── README.md         # Este archivo
```

## Uso

Una vez que BaraOS esté ejecutándose en QEMU:

1. **Explorar el sistema:**
```
/$ ls
[DIR]  home
[DIR]  bin
[FILE] readme.txt
```

2. **Crear archivos y directorios:**
```
/$ mkdir documentos
/$ touch mi_archivo.txt
/$ echo Hola Mundo > saludo.txt
```

3. **Navegar entre directorios:**
```
/$ cd home
/home$ ls
[FILE] usuario.txt
/home$ cd ..
/$ pwd
/
```

4. **Ver contenido de archivos:**
```
/$ cat readme.txt
Bienvenido a BaraOS!
Sistema de archivos simple.
```

## Controles en QEMU

- **Ctrl+Alt+G** - Liberar cursor del mouse
- **Ctrl+A, X** - Salir de QEMU
- **Ctrl+Alt+F** - Pantalla completa

## Limitaciones

- Sistema de archivos solo en memoria (no persistente)
- Máximo 100 archivos/directorios
- Tamaño máximo de archivo: 512 bytes
- No soporta subdirectorios anidados profundamente

## Desarrollo

Este es un proyecto educativo que demuestra conceptos básicos de:
- Desarrollo de sistemas operativos
- Gestión de archivos
- Programación en modo real y protegido
- Drivers básicos de hardware

## Contribuir

1. Fork el proyecto
2. Crea una rama para tu feature (`git checkout -b feature/AmazingFeature`)
3. Commit tus cambios (`git commit -m 'Add some AmazingFeature'`)
4. Push a la rama (`git push origin feature/AmazingFeature`)
5. Abre un Pull Request

## Licencia

Este proyecto está bajo la licencia MIT. Ver el archivo `LICENSE` para más detalles.

## Autor

Desarrollado como proyecto educativo para demostrar conceptos de sistemas operativos y gestión de archivos.
