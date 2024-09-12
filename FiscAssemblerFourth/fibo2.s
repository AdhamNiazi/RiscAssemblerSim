;fibo2.s
;
;r0 will contain the 2nd fib
;r1 will contain the 1st fib
;r3 will contain the new fib
;r2 will contain 144
start:   not r0 r1         ; whatever is in r1, its negation is stored in r0
         and r0 r1 r0      ; and a value with its negation, you have zero.
         and r1 r0 r0      ; r1 = 0  anding r1 with 0 
         and r3 r0 r0      ; r3 = 0, anding r3 with 0 r3 is printed
         not r0 r1         ; r0 = 255 11111111
         add r0 r0 r0      ; r0 = 254 11111110
         not r0 r0         ; r0 = 1   00000001 
         add r3 r0 r1      ; r3 = r0 + r1 = 1 + 0
         and r2 r0 r0      ; r2 = r0 = 1
         and r3 r3 r3      ; r3 = r3 since fibo needs two 1's
         add r2 r2 r2      ; r2 = 2   00000010
         add r2 r2 r2      ; r2 = 4   00000100
         add r2 r2 r2      ; r2 = 8   00001000
         add r2 r2 r0      ; r2 = 9   00001001
         add r2 r2 r2      ; r2 = 18  00010010
         add r2 r2 r2      ; r2 = 36  00100100
         add r2 r2 r2      ; r2 = 72  01001000
         add r2 r2 r2      ; r2 = 144 10010000
looptop:
         and r1 r0 r0      ; r1 = r0 second to latest fib
         and r0 r3 r3      ; r0 = r3 latest fib calced
         add r3 r0 r1      ; r3 = r0 + r1 new fib number
         and r1 r2 r2      ; r1 = 144 since r1 is useless now we can change it
         not r1 r1         ; r1 = 01101111
         and r1 r3 r1      ; if r3 is 144 then notting this will make it 0
         bnz looptop
         add r1 r1 r2       
end:     bnz end

         