.data 
    pressAnyKey db "������� ����� �������...", "$"          ; ������ � ����������
    fileName db 'D:\Programms\emu8086\vdrive\D\Text.txt', 0 ; ��� ����� 'D:\Text.txt'
    bufferString db 40                                      ; ����� ��� ������
    str2 db "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"         ; ������ �� �������� "$"
    handleFile dw 0                                         ; ���������� �����

.stack
    dw 128 dup(0) ; ����

.code
start:
    mov ax, data
    mov es, ax
    xor cx, cx

file:
    mov si, 82h
    lea di, fileName
    rep movsb               ; ����������� ������ �� SI � DI � ������� �������������� ���������� ���������

    mov ds, ax
    mov dx, offset fileName
    mov ah, 3Dh             ; �������� ����� � ������� ���������� 21h, ������� 3Dh
    mov al, 02h             ; ��������� ������ ������� � ����� (������ � ������)
    
    int 21h
    jc exit                 ; �������� ����� CF �� ������

    mov handleFile, ax

    mov cx, 0
    mov dx, 0
    mov bx, handleFile
    mov ax, 4200h           ; ��������� ������ ������ � �����

    int 21h
    
    mov ah, 3Fh             ; �������� �������� 3Fh � ������� AH ��� ������ ������ �� �����
    lea dx, bufferString
    mov cx, 256             ; �������� �������� 256 � ������� CX ��� ������ ������������� ���������� ��������

    int 21h

    mov ah, 3Eh             ; �������� �������� 3Eh � ������� AH ��� �������� �����

    int 21h

    mov di, offset bufferString
    mov cx, 0FFh            ; �������� �������� 0FFh � ������� CX ��� �������� �������� � ������
    xor ax, ax
    repnz scasb             ; ����� ������� '$' � ������ bufferString � ������� ���������� �������� �� ������� ���������
    not cx                  ; �������������� �������� CX
    dec cx
    xor ch, ch
    mov es, cx
    lea si, bufferString

change:
    xor bx, bx 
    mov bx, [si]

    sub bx, 10 
    cmp bl, 0       ; ��������� �������� ����� �������� BX � �����
    je end1         ; ������� � ����� end1, ���� �������� ����� ����

    sub bx, 3 
    cmp bl, 0       ; ��������� �������� ����� �������� BX � �����
    je end1         ; ������� � ����� end1, ���� �������� ����� ����

    mov [si], ' '   ; ������ ������� � [si] �� ������

end1:
    lodsb           ; �������� ����� �� ������, ���������� ��������� SI, � AL, � ������������� �������� SI
    loop change     ; ���������� �������� �������� CX �� ������� � ����������� ������� � ����� change, ���� �������� CX �� ����� ����

    mov dx, offset fileName 
    mov ah, 3Dh     ; �������� �����
    mov al, 02h     ; ��������� ������ ������� � ����� (������ � ������)

    int 21h
    jc exit         ; ������� � ����� exit, ���� ���� CF ���������� (������)

    mov handleFile, ax

    mov cx, 0 
    mov dx, 0 
    mov bx, handleFile 
    mov ax, 4200h   ; ��������� ������ ������ � �����

    int 21h 

    xor cx, cx 
    mov ah, 40h     ; ������ � ����
    lea dx, bufferString 
    mov bx, handleFile 
    mov cx, es 

    int 21h 

    jmp close_file ; ����������� ������� � ����� close_file

close_file:
    mov ah, 3Eh         ; �������� �����
    int 21h
    lea dx, pressAnyKey ; �������� ������ ������ pressAnyKey � ������� DX
    mov ah, 9           ; ����� ������
    int 21h             ; ����� ���������� 21h ��� ������ ������

    ; �������� ������� �������
    mov ah, 1           ; ������ ������� � ���������� ��� ���
    int 21h       

exit:
    mov ax, 4c00h 
    int 21h 

end start               ; ��������� ����� ����� � ���������� ���������������.