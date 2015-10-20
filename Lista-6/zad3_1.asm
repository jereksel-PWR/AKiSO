
                opt f-g-h+l+o+
                org $1000

start           equ *

                lda #$00         ;starsze bity liczby która chcemy wypisac
                sta byte        ;zapisujemy j¹ w byte
                
                lda #$ff         ;m³odsze bity liczby która chcemy wypisac
                sta byte+1        ;zapisujemy j¹ w byte				
				
                lda #00         ;czyscimy akumulator
                ldx #16          ;ustawiamy iterator petli na 16 (ilosc bitów podanej liczby)
                sed             ;wlaczamy tryb dziesietny

bcd          	asl byte+1	; Przesuniêcie bitowe
				rol byte+0  ; Przesuniêcie bitowe z dodaniem carry na pocz¹tku 
				;Dwie poprzednie instrukcje przesuwaj¹ w lewo ca³¹ liczbê zapisan¹ w byte(+1)
				lda word+0  ; Reszta jest analogiczna do zadania 2
				adc word+0
				sta word+0
				lda word+1
				adc word+1
				sta word+1
				lda word+2
				adc word+2
				sta word+2
				dex
				bne bcd
				cld
                
				
		        lda word+2          ;wypisanie drugiej cyfry starszego bajtu
                jsr print		
				
			    lda word+1          ;wypisanie pierwszej cyfry mlodszego bajtu
                lsr @				;dzielenie przez 16
				lsr @
				lsr @
				lsr @
                jsr print	
				
                lda word+1          ;wypisanie drugiej cyfry starszego bajtu
                jsr print

                lda word            ;wypisanie pierwszej cyfry mlodszego bajtu
                lsr @
				lsr @
				lsr @
				lsr @
                jsr print

                lda word            ;wypisanie drugiej cyfry mlodszego bajtu
                jsr print

                brk

print           and #$f
                ora #'0'
                sta char
                lda <char
                ldx >char
                jsr $ff80
                rts

				org $2000
				
char            dta b(0)
byte            dta b(0)
				dta b(0)
word            dta b(0)
				dta b(0)
				dta b(0)

                org $2E0
                dta a(start)

                end of file
