.data
tmp: .asciz "%d"
buffor: .space 2000

.text
.global main
main:


# # Odłożenie rejestru bazowego na stos i skopiwanie obecnej
    # wartości wskaźnika stosu do rejestru bazowego
    pushl %ebp
    movl %esp, %ebp

    push $buffor
    push $tmp

    call scanf
    sub $8, %esp

    push buffor
    push $tmp

    call printf
    sub $8, %esp

    mov $0, %eax
    leave
	
	# usuwa ramke stosu
	#To jest rownowazne wykonaniu sekwencji:
                           #    mov esp, ebp ; Wyczysc stos ze zmiennych lokalnych.
                            #   pop ebp      ; Przywroc poprzedni wskaznik ramki stosu.
    ret

