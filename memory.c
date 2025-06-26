#include "memory.h"

#define HEAP_START 0x100000
#define HEAP_SIZE 0x100000

static char heap[HEAP_SIZE];
static int heap_used = 0;

void* malloc(int size) {
    if (heap_used + size > HEAP_SIZE) {
        return 0; // No hay suficiente memoria
    }
    
    void* ptr = &heap[heap_used];
    heap_used += size;
    return ptr;
}

void free(void* ptr) {
    // Implementación simple: no liberar memoria realmente
    // En un OS real necesitarías un allocator más sofisticado
}