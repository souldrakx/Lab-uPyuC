;Escribir 0x00 en toda la SRAM

ldi r30,0x00
ldi r31,0x2

ldi r16,0x00

L1:
st Z+,r16

cpi r30,0xFF
brne @@L1
cpi r31,0x21
brne @@L1