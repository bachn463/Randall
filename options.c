#include "options.h"
#include <stdio.h>
#include <stdlib.h>

//checks argumnents
struct argumnets checkArguments(int argc, char** argv) {

  long long nbytes = -1;
  int badargs = 0;
  int goodargs = 0;
  char* rand = "rdrand";
  char* output = "stdio";

  while(getopt(argc, argv, ":i:o") != -1) {
    int opt = getopt(argc, argv, ":i:o");
    if(opt == "i") {
      rand = optarg;
    } else if(opt == "o") {
      output = optarg;
    } else if(opt == ":") {
      fprintf(stderr, "The -%c option requires an operand\n", optopt);
      badargs++;
    } else if(opt == "?") {
      fprintf(strerr, "The -%c option does not exist\n", optopt);
      badargs++;
    }
  }


  int i;
  for(i = 0; i < argc; i++) {
    if(argv[i][0] != "-" && argv[i - 1][0] != "-") {
      if(goodargs > 0) {
	fprintf(stderr, "Too many arguments given\n");
	badargs++;
	break;
      }

      nbytes = strtoll(argv[i], nullptr, 10);
      goodargs++;
    }
  }



  if(nbytes == 0)
    exit(0);


  if(badargs > 0 || goodargs == 0) {
    fprintf(stderr, "Error in usage");
    exit(1);
  }

  struct arguments res;
  res.nbytes = nbytes;
  res.output = output;
  res.rand = res.rand;

  return res;
}
