![GeoGab Logo](./images/GeoGab.svg)

# Gabriel A. Sieben (Physicist)
Here is a little code I wrote for my HomeDev Smarthings projects. I thought it could be useful for others too. Have fun. Gabriel :)

# Not yet released

# Integrator
This elegant, fast and simple function calculates the arithmetic mean (average) of sequentially coming numbers over a range specified by the programmer. For example, the average of the last 50 numbers of a non-terminating number sequence is formed. The physicist speaks here of a smoothing of the data or of a filter.

Such a smoothing has its advantages and disadvantages:

**Advantages**
- If the data oscillates around the actual value, one increases the precession of the data. 
- If you don't want to react immediately to every change, taking the mean value is an advantage. 

**Disadvantages**
- But if one wants to react quickly to a change, smoothing will be rather disadvantageous, because the change is delayed. 
- The mean value calculation costs memory. If one wants to integrate over 50 numerical values, one must store these 50 numerical values also. 


This feature is great for smoothing sensor data to make the results more accurate. Yes you read correctly! You can make the accuracy of your fluctuating temperature sensor more accurate with this statistical calculation. But it always depends on which sensor you use. The temperature sensor does not change its values very fast. It always oscillates around the actual value. Anyone who has ever read a DS1820 temperature sensor will see its oscillations. The different values are not an oscillating temperature. It is the inaccuracy of the sensor oscillating around the exact value. That is why the manufacturer of the sensor sends the data so far behind the decimal point, although he specifies the precession of the sensor much lower. If the average is taken over a series of measurements in which the temperature is considered stable, then the average value will approach the actual temperature. It is similar with an accelerometer. But this changes the actual value very quickly. The integrator is still useful to the measured values of the accelerometer. But in this case you must not use too many numbers for the average calculation. Just play around. 

# Instruction
## Create an object of the method Integrator: 
`Integrator integrator([Places], [width]);`

``[Places]``: Number of values over which to integrate
``[width]``: width of the values: uint8_t, uint16_t or uint32_t

## Add a value:
`average=integrator.add(value);`

## Query the current average value:
If you don't take the average in the above example right when you add the value, you can query it later.
This is done via: 
` average=itegrator.value();`
or by direct access to the public variable. 
`integrator.Average;`

### Further:
- If you want to know how many seats you have already occupied, use: `int number=integrator.size();`
- If you want to restart the calculation of average: `integrator.reset();`
- If you want to print the status of the integrator on the serial port: `integrator.printall();`
- If you want to query the version number of the integrator: `String version = integrator.version();`

## Memory consumption
If you integrate more than 50 numbers, you need the memory for 50 numbers in the requested width. 
- uint8_t: 1 byte*50
- unti16_t: 2bytes*50
- uint32_t: 4 bytes*50

## Limitations
- The possible size of the array over which the values are stored depends on the free memory. This is the nature of things. 
- No decimal numbers will be processed. I will not change this without a good reason. By multiplication you could move the decimal point and calculate with integer. 
- No negative numbers are processed. Number series that fluctuate around zero can be shifted to positive by shifting the zero axis (simply add a value).   The shift is subtracted from the average.
