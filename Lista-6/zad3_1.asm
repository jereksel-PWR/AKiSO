
                opt f-g-h+l+o+
                org $1000

start           equ *

                lda #$00         ;starsze bity liczby kt�ra chcemy wypisac
                sta byte        ;zapisujemy j� w byte
                
                lda #$ff         ;m�odsze bity liczby kt�ra chcemy wypisac
                sta byte+1        ;zapisujemy j� w byte				
				
                lda #00         ;czyscimy akumulator
                ldx #16          ;ustawiamy iterator petli na 16 (ilosc bit�w podanej liczby)
                sed             ;wlaczamy tryb dziesietny

bcd          	asl byte+1	; Przesuni�cie bitowe
				rol byte+0  ; Przesuni�cie bitowe z dodaniem carry na pocz�tku 
				;Dwie poprzednie instrukcje przesuwaj� w lewo ca�� liczb� zapisan� w byte(+1)
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
