/*
 * Copyright (C) 2015 Artyom V. Poptsov <poptsov.artyom@gmail.com>
 *
 * To the extent possible under law, the person who associated CC0 with
 * this work has waived all copyright and related or neighboring rights
 * to this work.  See
 * <https://creativecommons.org/publicdomain/zero/1.0/>
 */

#include <stdio.h>

int
main(int argc, char** argv)
{
  int a = 0b10000000000000000000000000000001;
  int b = 0b00000000000000000000000000000001;
  printf ("a = %d\n", a);
  printf ("b = %d\n", b);
  return 0;
}
