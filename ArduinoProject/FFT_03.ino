// /*#include "arduinoFFT.h"

// /*
// These values can be changed in order to evaluate the functions
// */
// #define CHANNEL A0
// const uint16_t samples = 64; //This value MUST ALWAYS be a power of 2
// const double samplingFrequency = 100; //Hz, must be less than 10000 due to ADC
// unsigned int sampling_period_us;
// unsigned long microseconds;

// /*
// These are the input and output vectors
// Input vectors receive computed results from FFT
// */
// double vReal[samples];
// double vImag[samples];

// /* Create FFT object */
// ArduinoFFT<double> FFT = ArduinoFFT<double>(vReal, vImag, samples, samplingFrequency);

// #define SCL_INDEX 0x00
// #define SCL_TIME 0x01
// #define SCL_FREQUENCY 0x02
// #define SCL_PLOT 0x03

// void setup()
// {
//   sampling_period_us = round(1000000*(1.0/samplingFrequency));
//   Serial.begin(9600);
//   while(!Serial);
//   Serial.println("Ready");
// }

// void loop()
// {
//   /*SAMPLING*/
//   microseconds = micros();
//   for(int i=0; i<samples; i++)
//   {
//       int sensorRead = analogRead(CHANNEL);
//       vReal[i] = (sensorRead + 0.5) * (5.0 / 1023.0);
//       vImag[i] = 0;
//       Serial.println(vReal[i]);
//       while(micros() - microseconds < sampling_period_us){
//         //empty loop
//       }
//       microseconds += sampling_period_us;
//   }

  
//   /* Print the results of the sampling according to time 
//   Serial.println("Data:");
//   PrintVector(vReal, samples, SCL_TIME);
//   FFT.windowing(FFTWindow::Hamming, FFTDirection::Forward);	// Weigh data 
//   Serial.println("Weighed data:");
//   PrintVector(vReal, samples, SCL_TIME);
//   FFT.compute(FFTDirection::Forward); // Compute FFT 
//   Serial.println("Computed Real values:");
//   PrintVector(vReal, samples, SCL_INDEX);
//   Serial.println("Computed Imaginary values:");
//   PrintVector(vImag, samples, SCL_INDEX);
//   FFT.complexToMagnitude(); // Compute magnitudes 
//   Serial.println("Computed magnitudes:");
//   PrintVector(vReal, (samples >> 1), SCL_FREQUENCY);
//   double x = FFT.majorPeak();
//   Serial.println(x, 6); //Print out what frequency is the most dominant.
//   */
//   while(1); /* Run Once */
//   // delay(2000); /* Repeat after delay */
// }

// void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
// {
//   for (uint16_t i = 0; i < bufferSize; i++)
//   {
//     double abscissa;
//     /* Print abscissa value */
//     switch (scaleType)
//     {
//       case SCL_INDEX:
//         abscissa = (i * 1.0);
// 	break;
//       case SCL_TIME:
//         abscissa = ((i * 1.0) / samplingFrequency);
// 	break;
//       case SCL_FREQUENCY:
//         abscissa = ((i * 1.0 * samplingFrequency) / samples);
// 	break;
//     }
//     Serial.print(abscissa, 6);
//     if(scaleType==SCL_FREQUENCY)
//       Serial.print("Hz");
//     Serial.print(" ");
//     Serial.println(vData[i], 4);
//   }
//   Serial.println();
// }
