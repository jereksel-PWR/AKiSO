                opt f-g-h+l+o+
                org $1000

start           equ *
                ldy #6
				; Liczba którą chcemy skonwertować:
				lda #%11111010
				;
                jsr bintohex
                lda <text
                ldx >text
                jsr $ff80
                brk

bintohex		pha
				jsr pxdig
				pla
				lsr @  ; Przesunięcia bitowe w prawo
				lsr @
				lsr @
				lsr @
pxdig			and #%1111  ;Wyzerowanie bitów oprócz ostatnich 4
				ora #'0'    ;OR z zerem 
				cmp #'9'+1  ;Porównanie akumulatora z tym
				bcc pr
				adc #'A'-'9'-2 ;Jest to litera
pr				sta text,y
				dey
				rts

                org $2000
text            equ *
				dta b(8),b(8),b(8),b(8)
				dta b(8),b(8),b(8),b(8)
                dta b(10) ; '\n'
                dta b(0)

                org $2E0
                dta a(start)

                end of file
