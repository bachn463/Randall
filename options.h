#ifndef OPTIONS
#define OPTIONS

struct arguments {
  long long nbytes;
  char* output;
  char* input;
};

struct arguments checkArguments(int argc, char** argv);


#endif
