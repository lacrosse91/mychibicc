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
  lea rax, [rbp-16]
  push rax
  lea rax, [rbp-8]
  push rax
  pop rax
  mov rax, [rax]
  push rax
  pop rsi
  pop rdi
  mov rax, rsp
  and rax, 15
  jnz .L.call.1
  mov rax, 0
  call foo
  jmp .L.end.1
.L.call.1:
  sub rsp, 8
  mov rax, 0
  call foo
  add rsp, 8
.L.end.1:
  push rax
  pop rax
  jmp .L.return.main
.L.return.main:
  mov rsp, rbp
  pop rbp
  ret
.global foo
foo:
  push rbp
  mov rbp, rsp
  sub rsp, 16
  mov [rbp-16], rdi
  mov [rbp-8], rsi
  lea rax, [rbp-16]
  push rax
  pop rax
  mov rax, [rax]
  push rax
  pop rax
  mov rax, [rax]
  push rax
  lea rax, [rbp-8]
  push rax
  pop rax
  mov rax, [rax]
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  jmp .L.return.foo
.L.return.foo:
  mov rsp, rbp
  pop rbp
  ret
