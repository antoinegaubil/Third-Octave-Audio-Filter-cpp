# Third-Octave-Audio-Filter-C++

Third octave audio filter using either Chebyshev II or ButterWorth coefficients.

The coefficients have already been downloaded and are under the src/coeff-butter & src/coeff-cheby2 header files.
To use ButterWorth or Cheby2 coefficients, #include the header file you want in the "third-octave.h" line 18/19. 

The filter is using ButterWorth coefficients by default.

To implement the filter, download the git repo and change the header search path of your code to the full path of the location of the repo.

Simply include the header file and call the "third_octave()" function:

#include <third-octave.h>

Call the function from your main file :

third_octave(wavedata, F, samplingrate);

wavedata is your data vector.
F is the output of the function.
samplingrate is the wanted samplingrate. 


