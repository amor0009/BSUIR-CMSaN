.model small

.stack 100h

.data 
    isEndOfGame db 0

    block equ 44FEh
               
    outSize equ 2
    carPoz dw 3278
    carSize equ 3
    number dw 0200h
    delayTime dw 0A2C3h
    
    leftBorder db 20
    rightBorder db 20
    
    car dw 01DBh, 01DBh, 01DBh
    deleteStr dw 00DBh, 00DBh, 00DBh
    barrier dw block, block, block, block, block
    
    scoreMsg dw 0253h, 0263h, 026Fh, 0272h, 0265h, 023Ah
    score dw 0
    exitMsg dw 0250h, 0272h,0265h,0273h,0273h,0220h,0245h,0253h,0243h,0220h,0274h, 026Fh, 0220h, 0265h, 0278h, 0269h, 0274h
    exitSize db 17 
    gameOver dw 0247h, 0261h, 026Dh, 0265h,0220h, 024Fh, 0276h, 0265h, 0272h
    i db 10
    gameOverSize db 9          
.code
	

; ��������� kbHandler ������������ ������� ������ �� ����������.
; ��� ��������� ������ � ���������� � ���������, ���� �� ������ ������� 'a' ��� 'd'.
; ���� ������ ������� 'a', �� ���������� ����������� ���������� �����,
; ���� ������ ������� 'd', �� ���������� ����������� ���������� ������.
; � ��������� ������� ��������� ���������� ���������� ��������� ����������.
kbHandler proc
    mov ah, 01        ; ��������� ������ � ����������
    int 16h
    mov dl, al        ; ��������� ��������� ������
    mov ah, 0Ch       ; ������� ������ �� �����
    int 21h
    mov al, dl        ; ��������������� �������� �������
    cmp al, 'a'       ; ���������� �� ��������� ������� 'a'
    je aPressed       ; ���� �����, ��������� � ����� aPressed
    cmp al, 'd'       ; ���������� �� ��������� ������� 'd'
    je dPressed       ; ���� �����, ��������� � ����� dPressed
    jne kbHandlerContinue ; ���� �� ���� �� ������� �� ���������, ��������� � ����� kbHandlerContinue
aPressed:
    sub carPoz, 2     ; �������� 2 �� ���������� carPoz
    jmp kbHandlerContinue ; ��������� � ����� kbHandlerContinue
dPressed:
    add carPoz, 2     ; ��������� 2 � ���������� carPoz
    jmp kbHandlerContinue ; ��������� � ����� kbHandlerContinue
kbHandlerContinue:

    ret               ; ���������� ���������� �� ���������
kbHandler endp

; ��������� randomGenerator ���������� ��������� �����.
; ��� ���������� ���������� 21h ��� ��������� �������� �������,
; ������� ������������ � �������� ������ ��� ��������� ���������� �����.
; ����� ��� ����� ���������� ����� �� 10 � ���������� ���������.
randomGenerator proc
    push ax           ; ��������� ��������
    push bx
    push cx
    xor bx, bx        ; �������� ������� bx
    mov ah, 2Ch       ; �������� ������� �����
    int 21h
    mov bl, dl      
    mov ah, 00h       ; �������� ������� �����
    int 1Ah
    mov ax, dx        
    mul bx
    mov bx, 10        ; ��������� 10 � ������� bx
    mov al, dl      
    xor dx, dx 
    div bx            ; ����� ax �� bx
    pop cx
    pop bx
    pop ax
    ret               
randomGenerator endp

; ��������� showBorder ���������� ������� ������.
; ��� ���������� ��������� randomGenerator ��� ������ ���������� �����,
; ������� ����������, � ����� ������� ������ ���� ���������� �������.
; ���� ����� ������ ��� ����� 3, �� ������� ����� ���������� �����,
; ���� ����� ������ ��� ����� 6, �� ������� ����� ���������� ������.
; � ��������� ������� ��������� ���������� ���������� ��������� ����������.
showBorder proc
    pusha             
    xor dx, dx        
    xor di, di       
    call randomGenerator ; �������� ��������� randomGenerator
    cmp dl, 3         ; ���������� �������� dl � 3   
    jbe left
    cmp dl, 6
    jae right
showBorderContinue:

    mov di, 0
    mov cl, leftBorder
showBorderLoop:

    add di, 2
    loop showBorderLoop
    mov es:[di], block

    add di, 80
    mov es:[di], block
    mov cl, rightBorder
showBorderLoop2:
    add di, 2
    loop showBorderLoop2
    popa
    ret
left:
    cmp leftBorder, 1      ; ���������� �������� leftBorder � 1
    je showBorderContinue  ; ���� �����, ��������� � ����� showBorderContinue
    dec leftBorder         ; ��������� �������� leftBorder �� 1
    inc rightBorder        ; ����������� �������� rightBorder �� 1
    jmp showBorderContinue ; ��������� � ����� showBorderContinue

right:
    cmp rightBorder, 1     ; ���������� �������� rightBorder � 1
    je showBorderContinue  ; ���� �����, ��������� � ����� showBorderContinue
    inc leftBorder         ; ����������� �������� leftBorder �� 1
    dec rightBorder        ; ��������� �������� rightBorder �� 1
    jmp showBorderContinue ; ��������� � ����� showBorderContinue

showBorder endp

showCar proc
    mov di, carPoz         ; �������� �������� carPoz � ������� DI
    mov es:[di],     0F4FEh; �������� �������� 0F4FEh � ������, �� ������ DI � �������� ES
    mov es:[di] + 2, 07FFEh 
    mov es:[di] + 4, 0F3FEh 
    ret                   

showCar endp ; ����� ��������� showCar

moveScreen proc
    mov ah, 07h   ; ��������� ������ ����
    mov al, 1     ; ����� ����� ��������� ����
    xor bh, bh    
    xor cx, cx    
    mov dh, 24    
    mov dl, 79    
    int 10h       
    ret          

moveScreen endp 

deleteCar proc
    mov di, carPoz          ; �������� �������� carPoz � ������� DI
    mov si, offset deleteStr; �������� ����� ������ deleteStr � ������� SI
    mov cx, carSize         ; �������� �������� carSize � ������� CX
    rep movsw               ; �������� ���� ������, �� ������� ��������� SI, � ������, �� ������� ��������� DI,
                            ; � ����������� ����, ������������ ��������� CX
deleteCar endp

isCrush proc
    mov si, carPoz         ; �������� �������� carPoz � ������� SI
    sub si, 160            ; �������� 160 �� �������� �������� SI
    mov cx, carSize  
isCrushLoop:
    mov ax, es:[si]        ; �������� �������� �� ������, �� ������ SI � �������� ES, � ������� AX
    cmp ax, block          ; ���������� �������� �������� AX �� ��������� block
    je isCrushContinue     ; ���� �����, ��������� � ����� isCrushContinue
    add si, 2             
    loop isCrushLoop       ; ��������� �������� �������� CX �� 1 �, ���� ��� �� ����� 0, ��������� � ����� isCrushLoop
    ret                    

isCrushContinue:
    mov isEndOfGame, 1     
    ret

isCrush endp

nextFrameDelay proc
    mov ah, 86h            ; ������ �������� ������� �������
    mov dx, delayTime      ; ��������� �������� �������
    sub delayTime, 10     ; ��������� �������� ������� �� 10
    mov cx, 0              ; ��������� 0 � ������� cx
    int 15h                ; �������� ���������� 15h

nextFrameDelay endp

showScore proc
    scoreLen dw 20          ; ��������� �������� 20 � ���������� scoreLen
    inc score              
    mov di, 24160+70        ; ��������� ����� ��������� ������
    mov si, offset scoreMsg 
    mov cx, 6               
    rep movsw              ; ��������� �������� MOVSW cx ���
    mov ax, score          ; ��������� �������� ���������� score � ������� ax
    mov cx, 5              ; ��������� �������� 5 � ������� cx
    mov di, 24160+20+70   ; ��������� ����� ��������� ������
showScoreLoop:
    mov bx, 10            
    xor dx, dx             
    div bx                 ; ����� �������� ax �� bx, ��������� ����������� � ax, ������� � dx
    add dl, '0'            ; ���������� �������� '0' � dl
    add number, dx         
    mov si, offset number  
    movsw                  
    mov number, 0200h      ; ��������� �������� 0200h � ���������� number
    sub di, 4              
    loop showScoreLoop     ; ��������� �������� cx �, ���� ��� �� ����� 0, ��������� ����
    ret                   


createBarrier proc
    call randomGenerator         ; �������� ��������� randomGenerator
    xor bx, bx                   
    xor ax, ax                   
    mov al, dl                   
    mov bx, 8                    ; ��������� �������� 8 � ������� bx
    mul bx                       ; �������� �������� ax �� bx, ��������� ����������� � ax
    mov dl, 0                    
    mov dl, leftBorder           ; ��������� �������� leftBorder � ������� dl
    mov di, dx                  
    add di, dx                  
    add di, ax                   
    mov si, offset barrier       ; ��������� ����� ������� barrier
    mov cx, 5                    ; ��������� �������� 5 � ������� cx
    rep movsw                    ; ��������� �������� MOVSW cx ���

createBarrierEnd:
    ret                           
createBarrier endp

sendGameOver proc

    mov ah, 06h ; ��������� ������� � ������� ����� ���� ������
    xor al, al  ; ������� ������� ����� 0
    xor bh, bh  ; �������� ������� ����� 0
    xor cx, cx  ; ������������� ���������� ������� � 0
    mov dh, 25  ; ������������� ������ ������� � 25
    mov dl, 80  ; ������������� ������� ������� � 80
    int 10h

    inc score           
    mov di, 12*160+70   ; ��������� ������ ������ ������ ��� ������ ����� � ����� ������
    mov si, offset scoreMsg 
    mov cx, 6
    rep movsw 

    mov ax, score       ; �������� �������� ����� � ������� ax
    mov cx, 5
    mov di, 12*160+20+70; ��������� ������ ������ ������ ��� ������ ����� ����� � ����� ������

showScoreLoop1:         ; ���������, ���� �� ������� ��� ����� �����
    mov bx, 10 
    xor dx, dx 
    div bx 
    add dl, '0' 
    add number, dx 
    mov si, offset number 
    movsw               ; ����������� ����� �� si � di (������� �����)

    mov number, 0200h   ; ��������� number ������ 0200h (������� number ��� ��������� �������� �����)
    sub di, 4 

    loop showScoreLoop1 ; ��������� ����, ���� �� ������� ��� ����� �����
 
    mov di, 13*160+64   ; ��������� ������ ������ ������ ��� ������ ��������� "Press ESC to exit" � ����� ������
    mov si, offset exitMsg 
    mov cl, exitSize 
    rep movsw

    mov di, 11*160+72   ; ��������� ������ ������ ������ ��� ������ ��������� "Game Over" � ����� ������
    mov si, offset gameOver 
    mov cl, gameOverSize 
    rep movsw 
close:                  ; ����� ��� �������� ���������
    mov ah, 00          ; ��������� ������� ���������� ���������� � 0
    int 16h             ; ����� ���������� 16h ��� ���������� ������� �������
    cmp al, 1bh         ; ��������� �������� ������
    jne close   
    mov ax, 0003h
	int 10h 
	
    mov ah, 4Ch
    int 21h
    ret
sendGameOver endp    

begin:
    mov ax, @data         ; �������� �������� ������ ������ � ������� AX
    mov ds, ax            
    mov ax, 0003          ; ��������� ����������� 80x25 16-������� ��������� �����
    int 10h               
    mov ax, 0B800h        ; �������� �������� ������ ����������� � ������� AX
    mov es, ax           

    xor bx, bx            
    xor cx, cx            
    mov cl, 21            
    fenceLoop0:           ; ����� �����

        mov es:[bx], BLOCK ; ������ �������� BLOCK � ������, ���������� �� ������ ES:BX
        add bx, 2          
    loop fenceLoop0       

    add bx, 39 * 2        
    mov cx, 80 - 39       
    sub cl, 21            
    fenceLoop1:           ; ����� �����

        mov es:[bx], BLOCK; ������ �������� BLOCK � ������, ���������� �� ������ ES:BX
        add bx, 2          
    loop fenceLoop1       

    call moveScreen       ; ����� ��������� moveScreen

myLoop:                   ; ����� �����
    call nextFrameDelay   
    call deleteCar        
    call kbHandler        
    call showBorder       
    call isCrush         
    cmp isEndOfGame, 1    ; ��������� �������� isEndOfGame � 1
    je end:               ; ������� � ����� end, ���� ���������� ��������� �������

    call moveScreen       
    call showCar          
    call showScore        
    dec i                 
    cmp i, 0              
    jne myLoop            
    mov i, 10             
    call createBarrier    
    jmp myLoop            

end:                     ; ����� ����� ���������
    call sendGameOver     
    
end begin               