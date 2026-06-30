#define HEAP_START 0x50000
#define HEAP_SIZE  0x40000

unsigned char* heap_ptr = (unsigned char*) HEAP_START;
unsigned int heap_used = 0;

void mm_init() {
    heap_ptr = (unsigned char*) HEAP_START;
    heap_used = 0;
}

void* kmalloc(unsigned int size) {
    if(heap_used + size > HEAP_SIZE) return 0;
    void* ptr = (void*) heap_ptr;
    heap_ptr += size;
    heap_used += size;
    return ptr;
}

unsigned int mm_get_used() { return heap_used; }
unsigned int mm_get_free() { return HEAP_SIZE - heap_used; }

void int_to_str(unsigned int num, char* buf) {
    char tmp[12];
    int i = 0, j = 0;
    if(num == 0) { buf[0]='0'; buf[1]=0; return; }
    while(num > 0) { tmp[i++] = (num % 10) + '0'; num /= 10; }
    while(i > 0) { buf[j++] = tmp[--i]; }
    buf[j] = 0;
}
