#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//checks argumnents
struct arguments checkArguments(int argc, char** argv) {

  
  long long nbytes = -1;
  int badargs = 0;
  int goodargs = 0;
  //defaults
  char* input = "rdrand";
  char* output = "stdio";

  //had to move this before opt parsing because getopt permutes the order of arguments
  int i;
  for(i = 1; i < argc; i++) {
    //    fprintf(stderr, "%s\n", argv[i]);
    //    fprintf(stderr, "%s\n", argv[argc-1]);
    if(argv[i][0] != '-' && argv[i - 1][0] != '-') {
      //fprintf(stderr, "%s, %s\n", argv[i], argv[i-1]);
      if(goodargs) {
	fprintf(stderr, "Too many arguments given\n");
	badargs++;
	break;
      }
      char* endptr;
      nbytes = strtoll(argv[i], &endptr, 10);
      goodargs++;
    }
  }
  int opt;
  while((opt = getopt(argc, argv, "i:o:")) != -1) {
    //    fprintf(stderr, "%c", (char)opt);
    if(opt == 'i') {
      input = optarg;
    } else if(opt == 'o') {
      output = optarg;
    } else if(opt == ':') {
      fprintf(stderr, "The -%c option requires an operand\n", optopt);
      badargs++;
    } else if(opt == '?') {
      fprintf(stderr, "The -%c option does not exist\n", optopt);
      badargs++;
    }
  }
  //  fprintf(stderr, "O: %s\n", output);
  //  fprintf(stderr, "I: %s\n", input);
  //  fprintf(stderr, "N: %lld\n", nbytes);

  if(nbytes == 0)
    exit(0);

  if(badargs > 0 || goodargs == 0) {
    fprintf(stderr, "Error in usage: must be in the form %s options nbytes\n", argv[0]);
    exit(1);
  }

  struct arguments res;
  res.nbytes = nbytes;
  res.output = output;
  res.input = input;
  
  return res;
}
