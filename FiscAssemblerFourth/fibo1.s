;fibo1.s
;
start:   not r0 r1         ; whatever is in r1, its negation is stored in r0
         and r0 r1 r0      ; and a value with its negation, you have zero.
         and r1 r0 r0      ; r1 = 0  anding r1 with 0 
         and r3 r0 r0      ; r3 = 0, anding r3 with 0 r3 is printed
         not r0 r1         ; r0 = 255 11111111
         add r0 r0 r0      ; r0 = 254 11111110
         not r0 r0         ; r0 = 1   00000001 
looptop:
         add r3 r0 r1      ; r3 = r0 + r1
         and r0 r1 r1      ; r0 = r1 
         and r1 r3 r3      ; r1 = r3
         bnz looptop
         