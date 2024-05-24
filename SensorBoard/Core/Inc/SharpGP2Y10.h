/*
 * SharpGP2Y10.h
 *
 *  Created on: May 24, 2024
 *      Author: patrick
 */

#ifndef INC_SHARPGP2Y10_H_
#define INC_SHARPGP2Y10_H_

#define SharpGP2Y10_SAMPLINGTIME 280
#define SharpGP2Y10_DELTATIME 40
#define SharpGP2Y10_SLEEPINGTIME 9680

#include "stm32f4xx.h"

// Include necessary headers (e.g., for GPIO functions)

typedef struct {
  uint32_t *buffer;
  GPIO_TypeDef* ledPort;  // Pointer to GPIO port for LED control (optional)
  uint16_t ledPin;       // LED pin number (optional)
  float dustDensity;    // Calculated dust density
  float volMeasured;    // Measured voltage from sensor
  float calcVoltage;    // Internally calculated voltage
  float vccVol;         // Supply voltage (default: 5.0V)
} SharpGP2Y10_t;
// Function prototypes (assuming they are defined elsewhere)
void SharpGP2Y10_init(SharpGP2Y10_t* sensor, uint32_t* buffer, GPIO_TypeDef* ledPort, uint16_t ledPin, float vccVol);
float SharpGP2Y10_getDustDensityField(SharpGP2Y10_t* sensor);
float SharpGP2Y10_getDustDensity(SharpGP2Y10_t* sensor);
float SharpGP2Y10_getVoltageField(SharpGP2Y10_t* sensor);
float SharpGP2Y10_getVoltage(SharpGP2Y10_t* sensor);
int SharpGP2Y10_getADCField(SharpGP2Y10_t* sensor);
int SharpGP2Y10_getADC(SharpGP2Y10_t* sensor);


#endif /* INC_SHARPGP2Y10_H_ */
