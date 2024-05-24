/*
 * SharpGP2Y10.c
 *
 *  Created on: May 24, 2024
 *      Author: patrick
 */

#include "SharpGP2Y10.h"


void SharpGP2Y10_init(SharpGP2Y10_t* sensor, uint32_t* buffer, GPIO_TypeDef* ledPort, uint16_t ledPin, float vccVol) {
  sensor->ledPort = ledPort;
  sensor->ledPin = ledPin;
  sensor->vccVol = vccVol;
  sensor->buffer = buffer;
}

void SharpGP2Y10_calc(SharpGP2Y10_t* sensor) {
  HAL_GPIO_WritePin(sensor->ledPort, sensor->ledPin, GPIO_PIN_RESET); // turn on LED
//  HAL_Delay(SharpGP2Y10_SAMPLINGTIME);          // Sampling time

  sensor-> volMeasured = *sensor->buffer;

//  HAL_Delay(SharpGP2Y10_DELTATIME);
  HAL_GPIO_WritePin(sensor->ledPort, sensor->ledPin, GPIO_PIN_SET); // turn off LED
//  HAL_Delay(SharpGP2Y10_SLEEPINGTIME);

  sensor->calcVoltage = sensor->volMeasured * (sensor->vccVol / 4096.0f);
  sensor->dustDensity = 0.17f * sensor->calcVoltage - 0.1f;

  if (sensor->dustDensity < 0.0f) {
    sensor->dustDensity = 0.0f;
  }
}

float SharpGP2Y10_getDustDensity(SharpGP2Y10_t* sensor) {
  SharpGP2Y10_calc(sensor);
  return sensor->dustDensity;
}

float SharpGP2Y10_getVoltage(SharpGP2Y10_t* sensor) {
  SharpGP2Y10_calc(sensor);
  return sensor->calcVoltage;
}

int SharpGP2Y10_getADC(SharpGP2Y10_t* sensor) {
  SharpGP2Y10_calc(sensor);
  return sensor->volMeasured;
}
