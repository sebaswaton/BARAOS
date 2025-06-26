[org 0x7c00]
[bits 16]

start:
    mov ax, 0x07c0
    add ax, 288
    mov ss, ax
    mov sp, 4096
    
    mov ax, 0x07c0
    mov ds, ax
    
    ; Limpiar pantalla
    mov ah, 0x00
    mov al, 0x03
    int 0x10
    
    ; Mostrar mensaje de carga
    mov si, loading_msg
    call print_string
    
    ; Cargar kernel desde el sector 2
    mov ah, 0x02    ; función leer sectores
    mov al, 5       ; número de sectores a leer
    mov ch, 0       ; cilindro 0
    mov cl, 2       ; sector 2
    mov dh, 0       ; cabeza 0
    mov dl, 0       ; drive 0
    mov bx, 0x1000  ; dirección donde cargar
    int 0x13
    
    jc load_error
    
    ; Saltar al kernel
    jmp 0x1000:0x0000
    
load_error:
    mov si, error_msg
    call print_string
    jmp $

print_string:
    lodsb
    or al, al
    jz done
    mov ah, 0x0e
    int 0x10
    jmp print_string
done:
    ret

loading_msg db 'Cargando BaraOS...', 13, 10, 0
error_msg db 'Error cargando kernel!', 13, 10, 0

times 510-($-$$) db 0
dw 0xaa55