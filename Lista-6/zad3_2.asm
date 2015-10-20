
                opt f-g-h+l+o+
                org $1000

start           equ *


				lda #'5'         ;liczba która chcemy wypisac
                sta word+0        ;zapisujemy j¹ w byte	

				lda #'4'         ;liczba która chcemy wypisac
                sta word+1        ;zapisujemy j¹ w byte	
				
				lda #'1'         ;liczba która chcemy wypisac
                sta word+2        ;zapisujemy j¹ w byte
				
				lda #'1'         ;liczba która chcemy wypisac
                sta word+3        ;zapisujemy j¹ w byte

				lda #'1'         ;liczba która chcemy wypisac
                sta word+4        ;zapisujemy j¹ w byte				

				;Tutaj konwertujemy liczbê 54111
				;Liczba zostaje zapisana w byte(+1)
				;Aby j¹ zobaczyæ: emu6502.exe -v -m -b 2001 -e 2002 zad3_2.obx
				
				lda #0
				ldx #4
				ldy #0
				
				sed 0


ascii			clc
				ROL byte+1 ;Przesuniêcie bitowe - pomnozenie przez 2
				ROL byte+0
				lda byte+0
				pha			;Backup na stosie
				lda byte+1
				pha

				ROL byte+1 ;Pomnozenie przez 2
				ROL byte+0
				clc
				ROL byte+1 ;Pomnozenie przez 2
				ROL byte+0
				clc

				pla			;Zdjecie ze stosu
				ADC byte+1  ;Pomnozenie przez 2
				sta byte+1
				pla
				adc byte+0	;Pomnozenie przez 2
				sta byte+0


				clc
				lda word,y
				and #$f     ;Zdobycie wartoœci podanej liczby (binarnej)
				adc byte+1  ;Dodanie jej do byte+1
				php			; Backup carry
				sta byte+1  ;Wrzucienie akumulatora do byte+1
				lda byte+0  ;Wczytanie wartoœci byte
				plp			;I flagi carry
				adc #0		;Dodanie flagi carry
				sta byte+0	;Ponowne wrzucenie do pamieci
				
				clc
				INY
				DEX
				BPL ascii
				CLD

                brk
				
				

				org $2000
			
char            dta b(0)
byte            dta b(0)
				dta b(0)
word            dta b(0)
				dta b(0)
				dta b(0)
				dta b(0)
				dta b(0)

				
                org $2E0
                dta a(start)

                end of file
