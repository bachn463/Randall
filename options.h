#ifndef OPTIONS
#define OPTIONS

struct arguments {
  long long nbytes;
  char* output;
  char* input;
};

void  checkArguments(int argc, char** argv, struct arguments* res);


#endif
