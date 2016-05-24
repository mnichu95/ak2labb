#odpalanie ./lab1 < dupa.txt

.data
EXIT_SUCCESS = 0
SYSEXIT = 1
STDIN = 0
STDOUT = 1
SYSREAD = 3   # symbole
SYSWRITE = 4
#etykieta
base: .ascii "000 "   # ta dyrekstywa umieszcza cos w pamieciu wspodziewa sie napisu w cudzyslowiu przeksztalca kazdy znak na kod ascii
base_len = . - base   #roznica elementowo - adrs biezacy odjac adres etykieta base

.bss       

#Ta dyrektywa, .lcomm, utworzy symbol, my_buffer, który referuje do 500-bajtowej lokalizacji pamięci której możemy użyć jako bufor.     
.comm stin, 1   # na wejsce
in_len = 1

.comm stout, 4   # bufor na wyjscie 
out_len = 4

.text
.global _start

_start:

        mov $stin, %ecx      # bufor do przychowywanego znaku
        mov $in_len, %edx    #dlugosc wczytanego znaku 1 bajt
        mov $SYSREAD, %eax     # sysread wywolanie funkcji odczytujacej
        mov $STDIN, %ebx      # to co weszlo na strumien wejsciwoy wkladam do ebx
        INT $0x80

        cmp $0, %eax         # porownanie z 0 rejestru eax sprawdzam czy nie puste jestli tak do do wyjscia
        je end   # jesli rowne do wyjscia

        mov base, %eax      # wrzucenie szablonu do eax
        mov %eax, stout      # wrzucenie eax nba strumien wyjsciowy
        mov $0, %eax			#wyzerowanie rejestru eax
        movb stin, %al			#przenies bajtowy do rejestru al zawartosc stin
        mov $10, %bl		# wloz 10 do bl
        mov $2, %esp		# wloz 2 do esp

        repeat:   # petla
        div %bl			# dzielarka podziel rejest al przez bl  reszta w ah
        addb %ah, stout(%esp)   # reszta z dzielenia w ah wrzucenie jej na strumien wyjsciowy esp "przesuwanie liczb w szablonie"(poprzez dzielenie przez 10 otrzymane reszty tworza dziesietny obraz kodu ascii)
        mov $0, %ah   # wyzeruowanie rejestru z reszta
        dec %esp   # dekrementuj esp - zeby wlozyc nastepna reszte

        cmp $-1, %esp       
        jne repeat  # skocz jezeli nierowne porownaj z -1 jak nierowne skocz do petli i powtorzx procedure

        mov $stout, %ecx     # strumien wyjsciowy wrzucamy do ecx
        mov $out_len, %edx   # dlugosc bufora (szablonu) z obrazen dziesietnym wrzucona do edx
        mov $SYSWRITE, %eax  # wywolanie funkcji zapisu syswrite i wrzucenie do eax
        mov $STDOUT, %ebx 	# wywolanie funkcji sytemowej standartowego strumienia wuyjsciowego do ebx
        INT $0x80   # wywolanie przerwaniea

        jmp _start  # skok na poczatek procedur - wykonaie dla kolejncyh znakow

end:
##jak  bedzie 0 wczesniej przy comperze to skok tutaj bo nie ma wiecej znakow

      mov $SYSEXIT, %eax   # wywolanie fun. systemowej 
      mov $EXIT_SUCCESS, %ebx   # wywolanie ze z sukcesem
      INT $0x80   # wywolanie przerwania
                                                                                                                                    



