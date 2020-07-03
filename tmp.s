.intel_syntax noprefix
.global main
main:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  lea rax, [rbp-16]
  push rax
  push 3
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  add rsp, 8
  lea rax, [rbp-8]
  push rax
  push 5
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  add rsp, 8
  lea rax, [rbp-8]
  push rax
  push 8
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  push 7
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  add rsp, 8
  lea rax, [rbp-16]
  push rax
  pop rax
  mov rax, [rax]
  push rax
  pop rax
  jmp .L.return.main
.L.return.main:
  mov rsp, rbp
  pop rbp
  ret
