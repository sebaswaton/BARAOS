#!/bin/bash

# Script para compilar y ejecutar BaraOS en QEMU

echo "Compilando BaraOS..."

# Limpiar archivos anteriores
make clean

# Compilar el sistema
make

if [ $? -eq 0 ]; then
    echo "Compilación exitosa. Ejecutando en QEMU..."
    echo "Presiona Ctrl+Alt+G para liberar el cursor del mouse"
    echo "Presiona Ctrl+A, X para salir de QEMU"
    
    # Ejecutar en QEMU
    qemu-system-i386 -fda os-image.bin
else
    echo "Error en la compilación"
    exit 1
fi