;Sumar dos numeros de 16 bits apuntados por los registros X y Z el resulado se guardara en la direccion X

ld r18,X+
ld r19,X

ld r20,Z+
ld r21,Z

add r18,r20
adc r19,r21

st -X, r18
st X, r19

