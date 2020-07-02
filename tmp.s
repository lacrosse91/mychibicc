.intel_syntax noprefix
.global main
main:
  push rbp
  mov rbp, rsp
  sub rsp, 0
  push 2
  push 1
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rax
  cmp rax, 0
  je .L.end.1
  push 2
  pop rax
  jmp .L.return
.L.end.1:
  push 3
  pop rax
  jmp .L.return
.L.return:
  mov rsp, rbp
  pop rbp
  ret
