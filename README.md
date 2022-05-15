# Third-Octave-Audio-Filter-C++

Third octave audio filter using either Chebyshev II or ButterWorth coefficients for frequencies between 12.5Hz and 20,000Hz using the frequency table below.

FrequencyTable[33] = {12.5,16,20,25.0, 31.5, 40.0, 50.0, 63.0, 80.0, 100.0, 125.0, 160.0, 200.0, 250.0, 315.0, 400.0, 500.0, 630.0, 800.0, 1000.0,1250.0, 1600.0, 2000.0, 2500.0, 3150.0, 4000.0, 5000.0, 6300.0, 8000.0, 10000.0, 12500.0, 16000.0, 20000.0};

The filter uses Christophe Couvreur's Third Octave Filter structure : , which I have translated to C++.

Christophe Couvreur uses 2 digital filters : 

- FiltFilt : Performs zero-phase digital filtering by processing the input data x in both the forward and reverse directions. After filtering the data in the forward direction, the function reverses the filtered sequence and runs it back through the filter. 

- Downsample : Downsamples the signal for frequencies between 12.5Hz to 1250Hz.

These 2 matlab functions have been translated to C++ and can be found here :

FiltFilt : https://github.com/c4dm/qm-dsp

Downsample : https://gist.github.com/pixelpusher/c394da7c668db8d8c6560e0fe80c7287


The coefficients have already been calculated through MatLab and are under the src/coeff-butter & src/coeff-cheby2 header files.
To use ButterWorth or Cheby2 coefficients, #include the header file you want in the "third-octave.h" line 18/19. 

The filter is using ButterWorth coefficients by default.

To implement the filter, download the git repo and change the header search path of your code to the full path of the location of the repo.

Simply include the header file and call the "third_octave()" function:
```
#include <third-octave.h>
```

Call the function from your main file :

```
third_octave(wavedata, F, samplingrate);
```
wavedata is your data vector.

F is the output of the function.

samplingrate is the wanted samplingrate. 

To display the output frequency by frenquency :
```
for (int i = 0; i<33; i++)
{
std::cout << "Value of Octave : " << F[i] << " at frequency : " << FrequencyTable[i] << "Hz" << std::endl;
}
```

