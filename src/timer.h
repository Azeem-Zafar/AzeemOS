unsigned int tick = 0;

void port_write(unsigned short port, unsigned char data) {
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned char port_read_b(unsigned short port) {
    unsigned char result;
    __asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void timer_handler() {
    tick++;
    port_write(0x20, 0x20);
}

void keyboard_handler() {
    port_read_b(0x60);
    port_write(0x20, 0x20);
}

void timer_install() {
    port_write(0x20, 0x11);
    port_write(0xA0, 0x11);
    port_write(0x21, 0x20);
    port_write(0xA1, 0x28);
    port_write(0x21, 0x04);
    port_write(0xA1, 0x02);
    port_write(0x21, 0x01);
    port_write(0xA1, 0x01);
    port_write(0x21, 0xFC);
    port_write(0xA1, 0xFF);

    port_write(0x43, 0x36);
    port_write(0x40, 0x9C);
    port_write(0x40, 0x2E);

    idt_set_gate(32, (unsigned int) timer_handler, 0x08, 0x8E);
    idt_set_gate(33, (unsigned int) keyboard_handler, 0x08, 0x8E);
}
