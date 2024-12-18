.data 
    pressAnyKey db "Нажмите любую клавишу...", "$"          ; Строка с сообщением
    fileName db 'D:\Programms\emu8086\vdrive\D\Text.txt', 0 ; Имя файла 'D:\Text.txt'
    bufferString db 40                                      ; Буфер для строки
    str2 db "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"         ; Строка из символов "$"
    handleFile dw 0                                         ; Дескриптор файла

.stack
    dw 128 dup(0) ; Стек

.code
start:
    mov ax, data
    mov es, ax
    xor cx, cx

file:
    mov si, 82h
    lea di, fileName
    rep movsb               ; Копирование строки из SI в DI с помощью повторяющегося строкового оператора

    mov ds, ax
    mov dx, offset fileName
    mov ah, 3Dh             ; Открытие файла с помощью прерывания 21h, функции 3Dh
    mov al, 02h             ; Установка режима доступа к файлу (чтение и запись)
    
    int 21h
    jc exit                 ; Проверка флага CF на ошибку

    mov handleFile, ax

    mov cx, 0
    mov dx, 0
    mov bx, handleFile
    mov ax, 4200h           ; Установка режима чтения в файле

    int 21h
    
    mov ah, 3Fh             ; Загрузка значения 3Fh в регистр AH для чтения данных из файла
    lea dx, bufferString
    mov cx, 256             ; Загрузка значения 256 в регистр CX для чтения максимального количества символов

    int 21h

    mov ah, 3Eh             ; Загрузка значения 3Eh в регистр AH для закрытия файла

    int 21h

    mov di, offset bufferString
    mov cx, 0FFh            ; Загрузка значения 0FFh в регистр CX для подсчета символов в строке
    xor ax, ax
    repnz scasb             ; Поиск символа '$' в строке bufferString и подсчет количества символов до первого вхождения
    not cx                  ; Инвертирование значения CX
    dec cx
    xor ch, ch
    mov es, cx
    lea si, bufferString

change:
    xor bx, bx 
    mov bx, [si]

    sub bx, 10 
    cmp bl, 0       ; Сравнение младшего байта регистра BX с нулем
    je end1         ; Переход к метке end1, если значение равно нулю

    sub bx, 3 
    cmp bl, 0       ; Сравнение младшего байта регистра BX с нулем
    je end1         ; Переход к метке end1, если значение равно нулю

    mov [si], ' '   ; Замена символа в [si] на пробел

end1:
    lodsb           ; Загрузка байта из памяти, адресуемой регистром SI, в AL, и автоинкремент регистра SI
    loop change     ; Уменьшение значения регистра CX на единицу и циклический переход к метке change, если значение CX не равно нулю

    mov dx, offset fileName 
    mov ah, 3Dh     ; Открытие файла
    mov al, 02h     ; Установка режима доступа к файлу (чтение и запись)

    int 21h
    jc exit         ; Переход к метке exit, если флаг CF установлен (ошибка)

    mov handleFile, ax

    mov cx, 0 
    mov dx, 0 
    mov bx, handleFile 
    mov ax, 4200h   ; Установка режима чтения в файле

    int 21h 

    xor cx, cx 
    mov ah, 40h     ; Запись в файл
    lea dx, bufferString 
    mov bx, handleFile 
    mov cx, es 

    int 21h 

    jmp close_file ; Безусловный переход к метке close_file

close_file:
    mov ah, 3Eh         ; Закрытие файла
    int 21h
    lea dx, pressAnyKey ; Загрузка адреса строки pressAnyKey в регистр DX
    mov ah, 9           ; Вывод строки
    int 21h             ; Вызов прерывания 21h для вывода строки

    ; Ожидание нажатия клавиши
    mov ah, 1           ; Чтение символа с клавиатуры без эхо
    int 21h       

exit:
    mov ax, 4c00h 
    int 21h 

end start               ; Установка точки входа и завершение ассемблирования.