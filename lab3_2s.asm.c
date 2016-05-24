.global rdtsc  # nazwa funkcji
.type rdtsc,@function

#W języku Asembler funkcję również należy zadeklarować na początku kodu (w sekcji text) korzystając z poniższej składni:
rdtsc:   # fuckja ktora mierzy ilosc cykli wykonanych przez procesor od uruchomienia

    xorl %eax,%eax    # ta funkcja ma zwrocic jakis czas
    cpuid    # funkcja serializujaca nie wiemy co gdzie i kiedy a dzieki temu gwarantuje ze wszystkie instrukcje zostana wykonane po kolei lub ogolnie
    rdtsc      # wywolanie ffukcji tej
    ret   #powrot 

