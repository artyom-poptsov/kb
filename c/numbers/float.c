//// float.c -- Program that demonstrates float representation in memory.

/* Copyright (C) 2017 Artyom V. Poptsov <poptsov.artyom@gmail.com>
 *
 * To the extent possible under law, the person who associated CC0 with
 * this work has waived all copyright and related or neighboring rights
 * to this work.  See
 * <https://creativecommons.org/publicdomain/zero/1.0/>
 */


//// Commentary:

/* This example is intended to show how floating point numbers are
 * represented in memory.
 *
 * This example shold be compiled as follows:
 *   gcc -lm float.c -o float
 *
 * Usage examples
 *   1. Show single number:
 *     ./float 1.1
 *   2. Show numbers in the range [1.0, 2.0] with step = 0.1:
 *     ./float 1.0 2.0
 *   3. Show numbers in the range [1.0, 2.0] with step = 0.01:
 *     ./float 1.0 2.0 0.01
 *
 * Also I think the presentation [1] is very helpful for understanding
 * the topic.
 *
 * [1]: <http://eng.usf.edu/~kaw/class/EML3041/handouts/pptfloatingpoint_IEE754format.pdf>
 */


//// Code:

#include <stdio.h>
#include <stdlib.h>             /* atof */
#include <math.h>               /* pow */

void
print_header ()
{
  puts ("   original    sign  exponent  mantissa");
  puts ("   number      :.....:  .......:");
  puts ("   :           ::       :");
  puts ("   :           VV       V");
  puts ("   V           seeeeeeeemmmmmmmmmmmmmmmmmmmmmmm");
  //        0.00000 = 0b00000000000000000000000000000000
}

float
int_to_fractional_part (int n)
{
  float f = n;
  int d = 10;
  while (n) {
    n /= 10;
    f /= 10;
  }

  return f;
}

void
print_help_and_exit (const char* pname)
{
  printf ("Usage: %s <number>\n", pname);
  printf ("Usage: %s <number1> <number2>\n", pname);
  printf ("Usage: %s <number1> <number2> <step>\n", pname);
}

void
print_binary (float f)
{
  unsigned int*  d = (int *) &f;
  int counter;
  int exponent, mantissa, sign;
  char sign_char;               /* '+' or '-' */
  printf ("%10.5f = 0b", f);
  for (counter = 31; counter >= 0; --counter) {
    printf ("%d", (*d >> counter) & 1);
  }
  putchar ('\n');
  //                 seeeeeeeemmmmmmmmmmmmmmmmmmmmmmm
  exponent = (*d & 0b01111111100000000000000000000000) >> 23;

  sign = (*d & (1 << 31)) ? 1 : 0;
  sign_char = sign ? '-' : '+';

  mantissa = *d & 0b11111111111111111111111;
  printf ("             s: %d (%c) e: %5d m: %d\n",
          sign, sign_char, exponent, mantissa);
  puts   ("             n = (-1)^s * (1.m) * 2^(e - 127)");
  printf ("               = (-1)^%d * (1.%d) * 2^(%d - 127)\n",
          sign, mantissa, exponent);
  printf ("               = %10.10lf\n",
          (sign ? -1 : 1) * (1 + int_to_fractional_part (mantissa))
          * pow (2, exponent - 127));
}

void
print_range (float start, float end, float step)
{
  float f;
  printf ("printing numbers from range [%f, %f]\n",
          start, end);
  puts ("with step = 0.1...\n");
  print_header ();
  for (f = start; f < end; f += step)
    print_binary (f);
}


//// Entry point.

int
main (int argc, char** argv)
{
  if (argc == 2)
    {
      print_header ();
      print_binary (atof (argv[1]));
    }
  else if (argc == 3)
    {
      float start = atof (argv[1]);
      float end   = atof (argv[2]);
      print_range (start, end, 0.1);
    }
  else if (argc == 4)
    {
      float start = atof (argv[1]);
      float end   = atof (argv[2]);
      float step  = atof (argv[3]);
      print_range (start, end, step);
    }
  else
    {
      print_help_and_exit(argv[0]);
    }

  return 0;
}

//// float.c ends here.
