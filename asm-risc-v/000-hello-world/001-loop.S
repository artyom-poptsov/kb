  .data
  # "asciz" adds '\0' at the end of a string.
hello:  .asciz  "Hello, World!\n"

  .text
main:
  # Load immediate into t0 register.
  li    t0, 5

  # Start of the loop.
loop:
  # Call "print" procedure.
  li    a7, 4
  la    a0, hello
  ecall
  # Decrement the counter.
  addi  t0, t0, -1

  # If t0 > 0 then branch to "loop" label.
  # "bgt" means "branch if greater than".
  bgt   t0, x0, loop

  # Call "exit" procedure.
  li    a7, 10
  ecall
