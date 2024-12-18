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
	

; Процедура kbHandler обрабатывает нажатия клавиш на клавиатуре.
; Она считывает символ с клавиатуры и проверяет, была ли нажата клавиша 'a' или 'd'.
; Если нажата клавиша 'a', то происходит перемещение автомобиля влево,
; если нажата клавиша 'd', то происходит перемещение автомобиля вправо.
; В остальных случаях программа продолжает выполнение следующей инструкции.
kbHandler proc
    mov ah, 01        ; считываем символ с клавиатуры
    int 16h
    mov dl, al        ; сохраняем считанный символ
    mov ah, 0Ch       ; выводим символ на экран
    int 21h
    mov al, dl        ; восстанавливаем значение символа
    cmp al, 'a'       ; сравниваем со значением символа 'a'
    je aPressed       ; если равны, переходим к метке aPressed
    cmp al, 'd'       ; сравниваем со значением символа 'd'
    je dPressed       ; если равны, переходим к метке dPressed
    jne kbHandlerContinue ; если ни одно из условий не выполнено, переходим к метке kbHandlerContinue
aPressed:
    sub carPoz, 2     ; вычитаем 2 из переменной carPoz
    jmp kbHandlerContinue ; переходим к метке kbHandlerContinue
dPressed:
    add carPoz, 2     ; добавляем 2 к переменной carPoz
    jmp kbHandlerContinue ; переходим к метке kbHandlerContinue
kbHandlerContinue:

    ret               ; возвращаем управление из процедуры
kbHandler endp

; Процедура randomGenerator генерирует случайное число.
; Она использует прерывание 21h для получения текущего времени,
; которое используется в качестве семени для генерации случайного числа.
; Затем она делит полученное число на 10 и возвращает результат.
randomGenerator proc
    push ax           ; сохраняем регистры
    push bx
    push cx
    xor bx, bx        ; обнуляем регистр bx
    mov ah, 2Ch       ; получаем текущее время
    int 21h
    mov bl, dl      
    mov ah, 00h       ; получаем текущее время
    int 1Ah
    mov ax, dx        
    mul bx
    mov bx, 10        ; загружаем 10 в регистр bx
    mov al, dl      
    xor dx, dx 
    div bx            ; делим ax на bx
    pop cx
    pop bx
    pop ax
    ret               
randomGenerator endp

; Процедура showBorder отображает границу экрана.
; Она использует процедуру randomGenerator для выбора случайного числа,
; которое определяет, с какой стороны должна быть нарисована граница.
; Если число меньше или равно 3, то граница будет нарисована слева,
; если число больше или равно 6, то граница будет нарисована справа.
; В остальных случаях программа продолжает выполнение следующей инструкции.
showBorder proc
    pusha             
    xor dx, dx        
    xor di, di       
    call randomGenerator ; вызываем процедуру randomGenerator
    cmp dl, 3         ; сравниваем значение dl с 3   
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
    cmp leftBorder, 1      ; Сравнивает значение leftBorder с 1
    je showBorderContinue  ; Если равны, переходит к метке showBorderContinue
    dec leftBorder         ; Уменьшает значение leftBorder на 1
    inc rightBorder        ; Увеличивает значение rightBorder на 1
    jmp showBorderContinue ; Переходит к метке showBorderContinue

right:
    cmp rightBorder, 1     ; Сравнивает значение rightBorder с 1
    je showBorderContinue  ; Если равны, переходит к метке showBorderContinue
    inc leftBorder         ; Увеличивает значение leftBorder на 1
    dec rightBorder        ; Уменьшает значение rightBorder на 1
    jmp showBorderContinue ; Переходит к метке showBorderContinue

showBorder endp

showCar proc
    mov di, carPoz         ; Помещает значение carPoz в регистр DI
    mov es:[di],     0F4FEh; Помещает значение 0F4FEh в память, по адресу DI в сегменте ES
    mov es:[di] + 2, 07FFEh 
    mov es:[di] + 4, 0F3FEh 
    ret                   

showCar endp ; Конец процедуры showCar

moveScreen proc
    mov ah, 07h   ; прокрутка экрана вниз
    mov al, 1     ; число строк прокрутки вниз
    xor bh, bh    
    xor cx, cx    
    mov dh, 24    
    mov dl, 79    
    int 10h       
    ret          

moveScreen endp 

deleteCar proc
    mov di, carPoz          ; Помещает значение carPoz в регистр DI
    mov si, offset deleteStr; Помещает адрес строки deleteStr в регистр SI
    mov cx, carSize         ; Помещает значение carSize в регистр CX
    rep movsw               ; Копирует блок памяти, на который указывает SI, в память, на который указывает DI,
                            ; с количеством байт, определенным регистром CX
deleteCar endp

isCrush proc
    mov si, carPoz         ; Помещает значение carPoz в регистр SI
    sub si, 160            ; Вычитает 160 из значения регистра SI
    mov cx, carSize  
isCrushLoop:
    mov ax, es:[si]        ; Помещает значение из памяти, по адресу SI в сегменте ES, в регистр AX
    cmp ax, block          ; Сравнивает значение регистра AX со значением block
    je isCrushContinue     ; Если равны, переходит к метке isCrushContinue
    add si, 2             
    loop isCrushLoop       ; Уменьшает значение регистра CX на 1 и, если оно не равно 0, переходит к метке isCrushLoop
    ret                    

isCrushContinue:
    mov isEndOfGame, 1     
    ret

isCrush endp

nextFrameDelay proc
    mov ah, 86h            ; Задаем значение функции таймера
    mov dx, delayTime      ; Загружаем задержку времени
    sub delayTime, 10     ; Уменьшаем задержку времени на 10
    mov cx, 0              ; Загружаем 0 в регистр cx
    int 15h                ; Вызываем прерывание 15h

nextFrameDelay endp

showScore proc
    scoreLen dw 20          ; Загружаем значение 20 в переменную scoreLen
    inc score              
    mov di, 24160+70        ; Загружаем адрес экранного буфера
    mov si, offset scoreMsg 
    mov cx, 6               
    rep movsw              ; Повторяем операцию MOVSW cx раз
    mov ax, score          ; Загружаем значение переменной score в регистр ax
    mov cx, 5              ; Загружаем значение 5 в регистр cx
    mov di, 24160+20+70   ; Загружаем адрес экранного буфера
showScoreLoop:
    mov bx, 10            
    xor dx, dx             
    div bx                 ; Делим значение ax на bx, результат сохраняется в ax, остаток в dx
    add dl, '0'            ; Прибавляем значение '0' к dl
    add number, dx         
    mov si, offset number  
    movsw                  
    mov number, 0200h      ; Загружаем значение 0200h в переменную number
    sub di, 4              
    loop showScoreLoop     ; Уменьшаем значение cx и, если оно не равно 0, выполняем цикл
    ret                   


createBarrier proc
    call randomGenerator         ; Вызываем процедуру randomGenerator
    xor bx, bx                   
    xor ax, ax                   
    mov al, dl                   
    mov bx, 8                    ; Загружаем значение 8 в регистр bx
    mul bx                       ; Умножаем значение ax на bx, результат сохраняется в ax
    mov dl, 0                    
    mov dl, leftBorder           ; Загружаем значение leftBorder в регистр dl
    mov di, dx                  
    add di, dx                  
    add di, ax                   
    mov si, offset barrier       ; Загружаем адрес массива barrier
    mov cx, 5                    ; Загружаем значение 5 в регистр cx
    rep movsw                    ; Повторяем операцию MOVSW cx раз

createBarrierEnd:
    ret                           
createBarrier endp

sendGameOver proc

    mov ah, 06h ; Установка курсора в верхний левый угол экрана
    xor al, al  ; Столбец курсора равен 0
    xor bh, bh  ; Страница курсора равна 0
    xor cx, cx  ; Устанавливаем координаты курсора в 0
    mov dh, 25  ; Устанавливаем строку курсора в 25
    mov dl, 80  ; Устанавливаем столбец курсора в 80
    int 10h

    inc score           
    mov di, 12*160+70   ; Установка адреса начала строки для вывода счета в видео памяти
    mov si, offset scoreMsg 
    mov cx, 6
    rep movsw 

    mov ax, score       ; Загрузка значения счета в регистр ax
    mov cx, 5
    mov di, 12*160+20+70; Установка адреса начала строки для вывода числа счета в видео памяти

showScoreLoop1:         ; Повторять, пока не выведем все цифры числа
    mov bx, 10 
    xor dx, dx 
    div bx 
    add dl, '0' 
    add number, dx 
    mov si, offset number 
    movsw               ; Скопировать слово из si в di (вывести цифру)

    mov number, 0200h   ; Установка number равной 0200h (очистка number для следующей итерации цикла)
    sub di, 4 

    loop showScoreLoop1 ; Повторяем цикл, пока не выведем все цифры числа
 
    mov di, 13*160+64   ; Установка адреса начала строки для вывода сообщения "Press ESC to exit" в видео памяти
    mov si, offset exitMsg 
    mov cl, exitSize 
    rep movsw

    mov di, 11*160+72   ; Установка адреса начала строки для вывода сообщения "Game Over" в видео памяти
    mov si, offset gameOver 
    mov cl, gameOverSize 
    rep movsw 
close:                  ; Метка для закрытия программы
    mov ah, 00          ; Установка функции прерывания клавиатуры в 0
    int 16h             ; Вызов прерывания 16h для считывания нажатой клавиши
    cmp al, 1bh         ; Сравнение значения регист
    jne close   
    mov ax, 0003h
	int 10h 
	
    mov ah, 4Ch
    int 21h
    ret
sendGameOver endp    

begin:
    mov ax, @data         ; Загрузка базового адреса данных в регистр AX
    mov ds, ax            
    mov ax, 0003          ; Настройка видеорежима 80x25 16-цветный текстовый режим
    int 10h               
    mov ax, 0B800h        ; Загрузка базового адреса видеопамяти в регистр AX
    mov es, ax           

    xor bx, bx            
    xor cx, cx            
    mov cl, 21            
    fenceLoop0:           ; Метка цикла

        mov es:[bx], BLOCK ; Запись значения BLOCK в память, адресуемую по адресу ES:BX
        add bx, 2          
    loop fenceLoop0       

    add bx, 39 * 2        
    mov cx, 80 - 39       
    sub cl, 21            
    fenceLoop1:           ; Метка цикла

        mov es:[bx], BLOCK; Запись значения BLOCK в память, адресуемую по адресу ES:BX
        add bx, 2          
    loop fenceLoop1       

    call moveScreen       ; Вызов процедуры moveScreen

myLoop:                   ; Метка цикла
    call nextFrameDelay   
    call deleteCar        
    call kbHandler        
    call showBorder       
    call isCrush         
    cmp isEndOfGame, 1    ; Сравнение значения isEndOfGame с 1
    je end:               ; Переход к метке end, если предыдущее сравнение истинно

    call moveScreen       
    call showCar          
    call showScore        
    dec i                 
    cmp i, 0              
    jne myLoop            
    mov i, 10             
    call createBarrier    
    jmp myLoop            

end:                     ; Метка конца программы
    call sendGameOver     
    
end begin               