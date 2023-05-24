# Make x86-64 random byte generators.

# Copyright 2015, 2020, 2021 Paul Eggert

# This program is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.

# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

# Optimization level.  Change this -O2 to -Og or -O0 or whatever.
OPTIMIZE =

# The C compiler and its options.
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -Wall -Wextra -fanalyzer \
  -march=native -mtune=native -mrdrnd

# The archiver command, its options and filename extension.
TAR = tar
TARFLAGS = --gzip --transform 's,^,randall/,'
TAREXT = tgz

default: randall

randall: *.c *.h
	$(CC) $(CFLAGS) *.c -o $@

assignment: randall-assignment.$(TAREXT)
assignment-files = COPYING Makefile randall.c
randall-assignment.$(TAREXT): $(assignment-files)
	$(TAR) $(TARFLAGS) -cf $@ $(assignment-files)

submission-tarball: randall-submission.$(TAREXT)
submission-files = $(assignment-files) \
  notes.txt *.c *.h # More files should be listed here, as needed.
randall-submission.$(TAREXT): $(submission-files)
	$(TAR) $(TARFLAGS) -cf $@ $(submission-files)

repository-tarball:
	$(TAR) -czf randall-git.tgz .git

.PHONY: default clean assignment submission-tarball repository-tarball

clean:
	rm -f *.o *.$(TAREXT) randall
check:
	./randall 10 | wc -c | grep 10
	./randall -o stdio -i /dev/urandom 2048 | wc -c | grep 2048
	./randall -i /dev/urandom 10 | wc -c | grep 10
	./randall -o 1024 -i mrand48_r 10 | wc -c | grep 10
	./randall -o stdio -i mrand48_r 100 | wc -c | grep 100
	./randall -o 1024 -i rdrand 128 | wc -c | grep 128
	./randall -i mrand48_r 10 -o 1 | wc -c | grep 10
	./randall -i mrand48_r 100 -o stdio | wc -c | grep 100
	./randall -i rdrand 128 -o 16 | wc -c | grep 128
	./randall -o 1024 -i rdrand 2048 | wc -c | grep 2048
	./randall -o 1024 -i /dev/urandom 2048 | wc -c | grep 2048
	./randall -i /dev/urandom 1024 -o 10 | wc -c | grep 1024
	./randall -o stdio -i rdrand 4096 | wc -c | grep 4096
	./randall 10000 | wc -c | grep 10000
	./randall -o 256 -i rdrand 512 | wc -c | grep 512
	./randall 10 -i /dev/urandom | wc -c | grep 10
	./randall -o 2 32 | wc -c | grep 32
	./randall -i rdrand 16 | wc -c | grep 16
