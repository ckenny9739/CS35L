Connor Kenny
readme.txt

Here is a breakdown of what I did for the HW part of assignment 8:

Downloaded the srt.tgz and unzipped with
tar xzvf srt.tgz

Ran make check clean:
make clean check
rm -f *.o *.tmp 1-test.ppm 2-test.ppm 4-test.ppm 8-test.ppm srt srt.tgz
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o main.o main.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o raymath.o raymath.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter   -c -o shaders.o shaders.c
gcc -std=gnu99 -g -O2 -Wall -Wextra -Wno-unused-parameter -o srt main.o raymath.o shaders.o -lm
time ./srt 1-test.ppm >1-test.ppm.tmp

real 0m49.138s
user 0m49.155s
sys  0m0.001s
mv 1-test.ppm.tmp 1-test.ppm
time ./srt 2-test.ppm >2-test.ppm.tmp
./srt: Multithreading is not supported yet.

real   0m0.002s
user   0m0.000s
sys    0m0.001s
Makefile:35: recipe for target '2-test.ppm' failed
make: *** [2-test.ppm] Error 1

This gives me a baseline of roughly 49 seconds for the unparallel verison.

Now I have to alter the files to get it to run faster.

Finally, I have multithreaded the ray tracing program and increased the spead roughly 5 times.
I ran in to numerous problems, but my biggest hurdle was how to even get started.
At first, I thought that putting the entire for loop section of main.c into a new function was
too much for each thread, but after reading on piazza, it seemed like splitting it by the
width was the best option. This became fairly annoying because width was set to 131, which
does not divide into whole numbers (as a prime). I had to adjust for this by making the last
thread do the extra work that was a result of the division (131 / 8 = 16, 16 * 7 = 112,
Thread 8 had to do a width section of 19 instead of 16).

I also ran into the problem of messing with my bounds on the outer for loop to the point where
it was more time efficient to just start over from a previously saved version that I had, which
would run through the entire Makefile, but would fail because the output was incorrect.
After fiddling around with this old version, I used all the strategies I learned from my
previous attempt to be able to finish in roughly 1.5 hours. This lab is not a very difficult one,
but can be extremely confusing and time consuming if one does not think about the process
correctly. Examples of this are trying to include every local variable in main as an
element in my_data for each thread, splitting the widths incorrectly (not realizing that
the last one can just be from where the previous left off until width), working out a formula
for the start and end values of the for loop, not using global variables or using too many
globabl variables, etc. Basically, this lab was a lot of trial and error, but eventually
it all worked out and I was able to get it completed correctly.

This could have been slightly (emphasis on the slightly) improved by distributing the 3 extra
among the other threads,but for our purposes, I think my solution is exactly what we needed.
My basic solution is that I made each thread know where to start and stop as far as making
it embarrassingly parallel, along with its thread number and a struct that held the 3
floats for each pixel. If I did not do this last part, I ran into a lot of problems with
printing in the wrong order or printing uninitialized values.
Finally, I pulled the printing out of the my_worker function and printed from a dynamically
allocated array at the end. This eliminated the problem of printing in the wrong order,
so that I only had to deal with putting the values into the array in the correct order.
As far as conclusions, I think that multithreading is a great way to improve performance,
when it makes sense to put in the effort. This process was extremely computationally
intensive so parallelizing the computations is a perfect way to speed up the process.
I am sure that there are other trickier ways to improve performance, but
overall, an increase in ~5 speed up is an amazing deal in itself.
