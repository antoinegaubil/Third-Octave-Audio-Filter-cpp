#ifndef tiers_h
#define tiers_h


//Libraries
#include <iostream>
#include <string>
#include <cmath>
#include <complex>
#include <cctype>
#include <algorithm>
#include <random>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>

//Githubs
#include "src/coeff-butter.h" //put in comments "#include "src/coeff-cheby2"" to use ButterWorth.
//#include "src/coeff-cheby2" //put in comments "#include "src/coeff-butter.h"" to use chebyshev II.
#include "src/FiltFilt.h"
#include "src/downsample.h"

//Source Files
#include <third2/src/Framer.cpp>
#include <third2/src/DFProcess.cpp>
#include <third2/src/FiltFilt.cpp>
#include <third2/src/Filter.cpp>
#include <third2/src/MathUtilities.cpp>

using namespace std;


int third_octave(vector<double> wavedata, double F[], float samplingrate);





//Apply Third-octave filter with butterworth coefficients
int third_octave(vector<double> wavedata, double F[], float samplingrate)
{
    vector<double> data(samplingrate);
    float FrequencyTable[33] = {12.5,16,20,25.0, 31.5, 40.0, 50.0, 63.0, 80.0, 100.0, 125.0, 160.0, 200.0, 250.0, 315.0, 400.0, 500.0, 630.0, 800.0, 1000.0,1250.0, 1600.0, 2000.0, 2500.0, 3150.0, 4000.0, 5000.0, 6300.0, 8000.0, 10000.0, 12500.0, 16000.0, 20000.0};
    
    for (int k=0; k<samplingrate; k++)
    {
        data[k] = wavedata[k];
    }
    
    //THIRD OCTAVE FOR FREQUENCES 1600Hz TO 20,000Hz
    for (int i =21; i <33; i++)
    {
        
        //vector<double> in;
        //in.insert(in.begin(),begin(data), end(data));
        vector <double> y_filtfilt_out;
        vector<double> output(samplingrate);
        double sum =0;

        vector iir_a = {A[i][0],A[i][1],A[i][2],A[i][3],A[i][4],A[i][5],A[i][6]};
        vector iir_b = {B[i][0],B[i][1],B[i][2],B[i][3],B[i][4],B[i][5],B[i][6]};

        vector<double> a(iir_a);
        vector<double> b(iir_b);
        vector<double> out;
        
  
        FiltFilt f({ a, b });
        f.process(data.data(), out.data(),samplingrate, output);
 
    
        for (int j =0; j < samplingrate; j++)
        {
            sum+=pow(output[j],2);
        }
        
        F[i] = sum/samplingrate;
    }



    int sampling = samplingrate+1;
    int i =0;
    

    //THIRD OCTAVE FOR FREQUENCES 12.5Hz TO 1250Hz
    for (int j =6; j>-1; j--)
    {
        Resample(data,sampling-1,data,sampling/2);
        vector<double> in;
        //in.insert(in.begin(),begin(data), end(data));
        vector<double> output(samplingrate);

        double sum =0;
        i = 23;
       
        vector iir_a = {A[i][0],A[i][1],A[i][2],A[i][3],A[i][4],A[i][5],A[i][6]};
        vector iir_b = {B[i][0],B[i][1],B[i][2],B[i][3],B[i][4],B[i][5],B[i][6]};
        vector<double> y_filtfilt_out;
    
        vector<double> a(iir_a);
        vector<double> b(iir_b);
        vector<double> out;
        
    
        FiltFilt f({ a, b });
        f.process(data.data(), out.data(), sampling/2, output);
     
        
        for (int j =0; j < sampling/2; j++)
        {
            sum+=pow(output[j],2);
        }

        F[j*3+2] = sum/(sampling/2);
        
        sum =0;
        i=22;
        
        vector iir_d = {A[i][0],A[i][1],A[i][2],A[i][3],A[i][4],A[i][5],A[i][6]};
        vector iir_c = {B[i][0],B[i][1],B[i][2],B[i][3],B[i][4],B[i][5],B[i][6]};
    
    
        vector<double> d(iir_d);
        vector<double> c(iir_c);
        vector<double> out2;
    
        FiltFilt n({ d, c });
        n.process(data.data(), out2.data(), sampling/2, output);
        
        for (int j =0; j < sampling/2; j++)
        {
            sum+=pow(output[j],2);
        }

      
        
        F[j*3+1] = sum/(sampling/2);

        sum =0;
        i=21;
        
        vector iir_g = {A[i][0],A[i][1],A[i][2],A[i][3],A[i][4],A[i][5],A[i][6]};
        vector iir_e = {B[i][0],B[i][1],B[i][2],B[i][3],B[i][4],B[i][5],B[i][6]};
        
        vector<double> g(iir_g);
        vector<double> e(iir_e);
        vector<double> out3;
        
        FiltFilt m({ g, e });
        m.process(data.data(), out3.data(), sampling/2, output);
 
        
        for (int j =0; j < sampling/2; j++)
        {
            sum+=pow(output[j],2);
        }
        
        F[j*3] = sum/(sampling/2);
 

        sum =0;
        sampling= sampling/2 + 1;

    }
 
  
    
    //CONVERSION TO DECIBELS
    for (int i =0; i<33; i++)
    {
        F[i] = 20*log10(F[i]/0.00002);
    }
    
    
    return F[33];
}


//--end--

#endif /* tiers_h */
