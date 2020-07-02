.intel_syntax noprefix
.global main
main:
  push rbp
  mov rbp, rsp
  sub rsp, 0
  push 1
  add rsp, 8
  push 2
  add rsp, 8
  push 3
  pop rax
  jmp .L.return
.L.return:
  mov rsp, rbp
  pop rbp
  ret
