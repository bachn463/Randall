/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
   instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <cpuid.h>
#include <errno.h>
#include <immintrin.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "options.h"
#include "output.h"
#include "rand64-hw.h"
#include "rand64-sw.h"
#include "mrand.h"
#include "cpu.h"

/* Main program, which outputs N bytes of random data.  */
int
main (int argc, char **argv)
{
  /* Check arguments.  */
  struct arguments args = checkArguments(argc, argv);
  long long nbytes = args.nbytes;
  char* input = args.input; //rdrand, mrand48_r, or filepath
  char* output = args.output; //stdio or N
  
  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  void (*initialize) (char* filepath);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);

  if(strcmp(input, "rdrand") == 0) {
    if(rdrand_supported()) {
      initialize = hardware_rand64_init;
      rand64 = hardware_rand64;
      finalize = hardware_rand64_fini;
    } else {
      fprintf(stderr, "rdrand is not supported on your CPU\n");
      exit(1);
    }
  } else if(strcmp(input, "mrand48_r") == 0) {
    initialize = mrand48_init;
    rand64 = mrand48_rng;
    finalize = mrand48_fini;
  } else if(input[0] == '/' && strlen(input) > 1) {
    initialize = software_rand64_init;
    rand64 = software_rand64;
    finalize = software_rand64_fini;
  } else {
    fprintf(stderr, "-i option but have rdrand, mradn48_r, or a filepath starting with /\n");
    exit(1);
  }

  initialize(input);
  int output_errno = 0;
  if(strcmp(output, "stdio") == 0) {//can also check if nbytes is -1/unchanged from checkArgs
    output_errno = tostdout(nbytes, rand64);
  } else {
    int n = strlen(output);
    for(int i = 0; i < n; i++) {
      if(!isdigit(output[i])) {
	fprintf(stderr, "-o option must have a positive integer\n");
	exit(1);
      }
    }

    char* endptr;
    long long outputN = strtoll(output, &endptr, 10);
    if(!outputN) {
      fprintf(stderr, "-o option must have a positive integer\n");
      exit(1);
    }
    output_errno = writeWithN(nbytes, rand64, outputN);
  }

  finalize();
  return !!output_errno;



}
