GLOBAL get_key

section .text

get_key:
	push rbp
	mov rbp,rsp

	mov rax,0
	in al,60h

	mov rsp,rbp
	pop rbp

	ret

