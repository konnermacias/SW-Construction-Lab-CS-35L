Konner Macias | 004603916
TA: Shenkar
README - After-Action report
==============================
Issues I ran into:

--> I had the silliest mistake of all and did not remove the code
of the if statement of: if (nthreads != 1) throw an error. My code
would work for the first instance but for 2 threads this would of
course fail. I kept thinking something was wrong with my color
array calculation but finally realized this silly bug later.
Sometimes mistakes are right under your nose.

--> I did not set of the color array correctly and had to adjust
for the number of threads being used.
==============================
Performace

$ time ./srt 1-test.ppm >1-test.ppm.tmp
real	0m46.331s
user	0m46.325s
sys	0m0.003s

$ time ./srt 2-test.ppm >2-test.ppm.tmp
real	0m23.296s
user	0m46.314s
sys	0m0.002s

$ time ./srt 4-test.ppm >4-test.ppm.tmp
real	0m11.734s
user	0m46.574s
sys	0m0.002s

$ time ./srt 8-test.ppm >8-test.ppm.tmp
real	0m5.983s
user	0m46.327s
sys	0m0.001s

As the number of threads increases, the real time decreases but the
user and sys time does not fluctuate too much. This is due to 
parallelism, so with more threads each completing computations for
pixel rendering, it can be completed quicker.
==============================
