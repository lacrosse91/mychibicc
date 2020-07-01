.intel_syntax noprefix
.global main
main:
  push rbp
  mov rbp, rsp
  sub rsp, 208
  lea rax, [rbp-8]
  push rax
  push 2
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  add rsp, 8
  lea rax, [rbp-24]
  push rax
  push 3
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  add rsp, 8
  lea rax, [rbp-8]
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  jmp .L.return
.L.return:
  mov rsp, rbp
  pop rbp
  ret
