  .data
  # "asciz" adds '\0' at the end of a string.
hello:  .asciz  "Hello, World!\n"

  .text
main:
  li    a7, 4
  la    a0, hello
  ecall

  # Call "exit" procedure.
  li    a7, 10
  ecall
