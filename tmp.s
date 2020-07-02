.intel_syntax noprefix
.global main
main:
  push rbp
  mov rbp, rsp
  sub rsp, 8
  lea rax, [rbp-8]
  push rax
  push 0
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  add rsp, 8
.L.begin.1:
  lea rax, [rbp-8]
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 10
  pop rdi
  pop rax
  cmp rax, rdi
  setl al
  movzb rax, al
  push rax
  pop rax
  cmp rax, 0
  je .L.end.1
  lea rax, [rbp-8]
  push rax
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
  pop rdi
  pop rax
  mov [rax], rdi
  push rdi
  add rsp, 8
  jmp .L.begin.1
.L.end.1:
  lea rax, [rbp-8]
  push rax
  pop rax
  mov rax, [rax]
  push rax
  pop rax
  jmp .L.return
.L.return:
  mov rsp, rbp
  pop rbp
  ret
