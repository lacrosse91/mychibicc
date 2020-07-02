.intel_syntax noprefix
.global main
main:
  push rbp
  mov rbp, rsp
  sub rsp, 0
  mov rax, rsp
  and rax, 15
  jnz .L.call.1
  mov rax, 0
  call ret32
  jmp .L.end.1
.L.call.1:
  sub rsp, 8
  mov rax, 0
  call ret32
  add rsp, 8
.L.end.1:
  push rax
  pop rax
  jmp .L.return.main
.L.return.main:
  mov rsp, rbp
  pop rbp
  ret
.global ret32
ret32:
  push rbp
  mov rbp, rsp
  sub rsp, 0
  push 32
  pop rax
  jmp .L.return.ret32
.L.return.ret32:
  mov rsp, rbp
  pop rbp
  ret
