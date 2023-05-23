#include "output.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>


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

int writeWithN(long long nbytes, unsigned long long (* rand64) (void), long length) {
  long long writtenBytes = 0;

  while(writtenBytes < nbytes) {
    int buffersz = (length < nbytes - writtenBytes) ? length : nbytes - writtenBytes;//min(length, nbytes - writtenBytes);
    void* memToUse = malloc(buffersz);
    if(!memToUse) {
      fprintf(stderr, "Error in allocating buffer");
      exit(1);
    }

    unsigned long long x;
    //fills every ULL'th size in the allocated buffer
    size_t i = 0;
    for(i = 0; i < buffersz / sizeof(x); i++) {
      x = rand64();
      memcpy(memToUse + i * sizeof(x), &x, sizeof(x));
    }
    //fill the remaining buffer
    x = rand64();
    memcpy(memToUse + i * sizeof(x), &x, buffersz % sizeof(x));
    int actuallyWritten = write(1, memToUse, buffersz);
    writtenBytes += actuallyWritten;
    free(memToUse);
  }

  return 0;
}
