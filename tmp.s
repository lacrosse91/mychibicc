.intel_syntax noprefix
.global main
main:
  push rbp
  mov rbp, rsp
  sub rsp, 0
.L.begin.1:
  push 3
  pop rax
  jmp .L.return
  jmp .L.begin.1
.L.end.1:
  push 5
  pop rax
  jmp .L.return
.L.return:
  mov rsp, rbp
  pop rbp
  ret
