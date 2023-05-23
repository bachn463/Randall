#include "options.h"
#include <stdio.h>
#include <stdlib.h>

bool writebytes (unsigned long long x, int nbytes)
{
  do
  {
    if (putchar (x) < 0)
            return false;
    x >>= CHAR_BIT;
    nbytes--;
  }
  while (0 < nbytes);

  return true;
}

int tostdout(long long nbytes, unsigned long long (* rand64) (void)) {
  int wordsize = sizeof rand64 ();
  int output_errno = 0;

  do
    {
      unsigned long long x = rand64 ();
      int outbytes = nbytes < wordsize ? nbytes : wordsize;
      if (!writebytes (x, outbytes))
	{
	  output_errno = errno;
	  break;
	}
      nbytes -= outbytes;
    }
  while (0 < nbytes);

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
    }

  return !!output_errno;
}

int writeToN(long long nbutes, unsigned long long (* rand64) (void), long length) {
  long long writtenBytes = 0;

  while(writtenBytes < nbytes) {
    int buffersz = min(length, nbytes - writtenBytes);
    void* memToUse = malloc(buffersz);
    if(!memToUse) {
      fprintf(stderr, "Error in allocating buffer");
      exit(1);
    }

    unsigned long long x;
    //fills every ULL'th size in the allocated buffer
    for(int i = 0; i < buffersz / sizeof(x); i++) {
      x = rand64();
      memcpy(mem + i * sizeof(x), &x, size(x));
    }
    //fill the remaining buffer
    x = rand64();
    memcpy(mem + i * sizeof(x), &x, buffersz % sizeof(x));
    writtenBytes += buffersz;
    fwrite(mem, 1, buffersz, stdout);
    free(mem);
  }

  return 0;
}
