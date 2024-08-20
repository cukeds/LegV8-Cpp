start: STURH x5, [x6, #0]
ADDI X6, X6, #0x2
SUBS X7, X2, X6
CBNZ X7, start
ADDI X5, X5, #0x2
ADD X6, X31, X31
CBZ X31, start
