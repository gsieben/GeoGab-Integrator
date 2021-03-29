/**
 * @file Integrator.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 1.0.3
 * @date 2021-02-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef GeoGabIntegrator_h
#define GeoGabIntegrator_h

#include <Arduino.h> 
#include <vector> 

#define INTEGRATOR_VERSION "1.0.3"

/*!
 * @brief GeoGab Integrator: This elegant, fast and simple function averages sequentially coming numbers over a range specified by the programmer. 
 * @function add(int) Adds a value to the integrator
 * @function value() Returns the acual integration value
 * @function size() Returs the ammount of value which will be integrated
 * @function reset() Resets the function. 
 * @function printall() Prints informations about the fuction on the serial port
 */
class Integrator {
  public: 
    Integrator(uint16_t size=10);      // The constructor creates an array of the required size. Without size specification it creates an array of 10 values 

    uint32_t add(uint32_t);
    uint32_t value();
    uint16_t size();
    void reset();
    uint8_t error(bool job); 
    void printall();
    String version();

    uint32_t Average=0;                 // Average value. The average value is very simple to calculate. It is simply the total sum (SumTotal) divided by the number of values (SizeOfStack).
    uint8_t FlagError=0;                // Error Flag. 0 = No Error, 1 = Overflow Error

  private:                            // There is no need to share these necessary variables. The user of the library could not do anything with these values.
    uint16_t SizeOfStack=0;             // Size of the stack. The array (or stack) is defined when the object will be created. This is the advantage of the vector over the array, where this is not possible. 
    uint64_t SumTotal =0;               // Sum of all values. And this is the tick. You don't sum up every round over the whole stack. You add the newly added value and subtract the oldest value, which is no longer in the sum range. 
    uint16_t ActualSlotIndex=0;         // Das ist die Nummer des aktuellen Slots im Array. An dieser Stelle wird der alte Wert gelesen, damit er von der Summe abgezogen werden kann. Anschließend wir er mit dem neuen Wert überschrieben, der zur Summe dazugezählt wird.
    std::vector<uint32_t> DataArray;    // Vector - the better array! An array size must be defined befor the object will be create. But not the vector. We request memory on demand.
    bool FlagArrayNotFull=true;       // Bevore the array is filled, we can only caculate the average over the ammount of values we have
};

#endif
