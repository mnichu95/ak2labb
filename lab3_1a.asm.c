.data
tmp: .asciz "%s"       # przechowuje argument %s czyli char 
buffor: .space 2000    # rozmiar bufora

.text
.global main
main:

# # Odłożenie rejestru bazowego na stos i skopiwanie obecnej
    # wartości wskaźnika stosu do rejestru bazowego
	
    pushl %ebp    # wrzucasz na stos ebp
    movl %esp, %ebp      # wrzucasz wskaznik stosu do ebp

    push $buffor         # wrzuc miejsce na argumenty char na stos
    push $tmp            # wrzuc typ na stos

    call scanf     # wywolaj fukcje z C wczytujaca
    sub $8, %esp    # odejmij 8 od wskaznik wierzcholka stosu bo bedzie wywwolywana inna fukcja 

    push $buffor         # wrzuc argumenty char na stos
    push $tmp     # wrzuc dana typ char

    call printf  # wywolaj fukcje z C drukujaca znak
    sub $8, %esp   # odejmij 8 od wskaznika wierzcholka stosu

    mov $0, %eax   
    leave     	# usuwa ramke stosu
	#To jest rownowazne wykonaniu sekwencji:
                           #    mov esp, ebp ; Wyczysc stos ze zmiennych lokalnych.
                            #   pop ebp      ; Przywroc poprzedni wskaznik ramki stosu.
							
    ret    # wroc

