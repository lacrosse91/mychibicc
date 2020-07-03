.intel_syntax noprefix
.global main
main:
  push rbp
  mov rbp, rsp
  sub rsp, 8
  lea rax, [rbp-8]
  push rax
  push 3
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  add rsp, 8
  lea rax, [rbp-8]
  push rax
  push 2
  pop rdi
  pop rax
  imul rdi, 8
  add rax, rdi
  push rax
  lea rax, [rbp-8]
  push rax
  pop rdi
  pop rax
  sub rax, rdi
  cqo
  mov rdi, 8
  idiv rdi
  push rax
  pop rax
  jmp .L.return.main
.L.return.main:
  mov rsp, rbp
  pop rbp
  ret
