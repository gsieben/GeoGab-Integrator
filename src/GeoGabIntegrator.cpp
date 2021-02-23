/**
 * @file Integrator.cpp
 * @author Gabriel Sieben gsieben@geogab.net
 * @brief 
 * @version 1.0.2
 * @date 2021-02-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <GeoGabIntegrator.h>

/**
 * Next Version Features: Different variable size
 */

/*!
 * @brief When creating an object of this method, the parameter defines the size of the array. The average is formed over all elements of this array. 
 * @parm Array size
 */
Integrator::Integrator(uint16 size) : SizeOfStack (size), DataArray (size)  {         // Constructor: e.g. Integrator integrator(20);
}

/*!
 * @brief Writes a new value into the array and averages it over the return value. 
 * @par Value witch will be added. The oldest value will be droped at the same moment. 
 * @return The average over all values in the array. 
 */
uint32 Integrator::add(uint32 wert) {
  if (FlagArrayNotFull) {                               // Flag=ture once the Array it not filled
    SumTotal+=wert;                                     // Add the value to the total sum. As the Sum is a 8bit variable (uint64) we need 4.294.967.296 4bit variables (uint) with a #ffffffff to overflow the total variable. So no need to worry.
    Average=((float)SumTotal/(ActualSlotIndex+1))+0.5;  // Divide by the amount of values and round correctly
  } else {
    SumTotal-=DataArray.at(ActualSlotIndex);            // The value that runs out of the range will be subtracted
    SumTotal+=wert;                                     // The new value will be added
    Average=((float)SumTotal/SizeOfStack)+0.5;          // Divide by the number of slots and round correctly
  }
  DataArray.at(ActualSlotIndex) = wert;                 // Save value to vector on the place of the droped value
  
  ActualSlotIndex++;                                    // Rise the slot counter
  if (ActualSlotIndex==SizeOfStack){                    // If we at the end
    ActualSlotIndex=0;                                  // Start using the first slot
    FlagArrayNotFull=false;                             // After a full first fill the flag must be set to false
  }

  return Average;                                       // Return the average
}

/*!
 * @brief Returns the actual value
 * @return I of all numbers.
 */
uint32 Integrator::value(){
  return Average;
}

/*!
 * @brief Request the size of the vector (amount of values which will be integratet.)
 * @return Size / Amount of values
 */
uint16 Integrator::size(){
  return SizeOfStack;
}

/*!
 * @brief Resets the Integrator
 */
void Integrator::reset(){
    FlagArrayNotFull=true;
    ActualSlotIndex=0;
}

/**
 * @brief Handles Error Requests. error() or. error(true) returns the error value. error(false) deletes the error status. 
 * 
 * @param job 
 * @return Error Code
 */
uint8 Integrator::error(bool job) {
  // job: true queries, false deletes, default is true;
  if (job) return FlagError;
  FlagArrayNotFull=false;
  return 0;
}

/*!
 * @brief Print Info Table
 */
void Integrator::printall(){
    Serial.println("FULL STATUS INFO of the GeoGab Integrator:");
    Serial.println("-----------------");
    Serial.printf("Integral Size:\t\t%d\r\n",SizeOfStack);
    Serial.printf("First Fill Mode:\t%s\r\n", FlagArrayNotFull ? "true" : "false");
    Serial.printf("Current Result:\t\t%d\r\n",Average);
    Serial.printf("Current Slot:\t\t%d\r\n",ActualSlotIndex);
    Serial.printf("Total:\t\t\t%llu\r\n",SumTotal);
    Serial.print("Version:\t\t");
    Serial.println(INTEGRATOR_VERSION);
    Serial.println("Array Content:");

    Serial.println("==================================");
    Serial.println("|\tLine\t|\tValue\t|");
    Serial.println("==================================");
    for (uint8_t i=0;i<SizeOfStack;i++) {
        Serial.printf("|\t%d\t|\t%d\t|\r\n",i,DataArray.at(i));
    }
    Serial.println("==================================");
}

/*!
 * @brief Return the Integrator Version
 */
String Integrator::version(){
  return INTEGRATOR_VERSION;
}