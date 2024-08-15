start: STURH x5, [x6, #0]
ADD X6, X6, X3
SUBS X7, X2, X6
CBNZ X7, start
ADD X5, X5, X3
ADD X6, X31, X31
CBZ X31, start