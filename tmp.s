.intel_syntax noprefix
.global main
main:
  push rbp
  mov rbp, rsp
  sub rsp, 0
  push 9
  pop rdi
  mov rax, rsp
  and rax, 15
  jnz .L.call.1
  mov rax, 0
  call fib
  jmp .L.end.1
.L.call.1:
  sub rsp, 8
  mov rax, 0
  call fib
  add rsp, 8
.L.end.1:
  push rax
  pop rax
  jmp .L.return.main
.L.return.main:
  mov rsp, rbp
  pop rbp
  ret
.global fib
fib:
  push rbp
  mov rbp, rsp
  sub rsp, 8
  mov [rbp-8], rdi
  lea rax, [rbp-8]
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  cmp rax, rdi
  setle al
  movzb rax, al
  push rax
  pop rax
  cmp rax, 0
  je  .L.end.2
  push 1
  pop rax
  jmp .L.return.fib
.L.end.2:
  lea rax, [rbp-8]
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 1
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rdi
  mov rax, rsp
  and rax, 15
  jnz .L.call.3
  mov rax, 0
  call fib
  jmp .L.end.3
.L.call.3:
  sub rsp, 8
  mov rax, 0
  call fib
  add rsp, 8
.L.end.3:
  push rax
  lea rax, [rbp-8]
  push rax
  pop rax
  mov rax, [rax]
  push rax
  push 2
  pop rdi
  pop rax
  sub rax, rdi
  push rax
  pop rdi
  mov rax, rsp
  and rax, 15
  jnz .L.call.4
  mov rax, 0
  call fib
  jmp .L.end.4
.L.call.4:
  sub rsp, 8
  mov rax, 0
  call fib
  add rsp, 8
.L.end.4:
  push rax
  pop rdi
  pop rax
  add rax, rdi
  push rax
  pop rax
  jmp .L.return.fib
.L.return.fib:
  mov rsp, rbp
  pop rbp
  ret
