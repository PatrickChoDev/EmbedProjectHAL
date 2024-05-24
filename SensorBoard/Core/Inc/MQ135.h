#pragma once
#ifndef __MQ135_H
#define __MQ135_H

/// Parameters for calculating ppm of CO2 from sensor resistance
#define PARA 116.6020682
#define PARB 2.769034857

/// Parameters to model temperature and humidity dependence
#define CORA .00035
#define CORB .02718
#define CORC 1.39538
#define CORD .0018
#define CORE -.003333333
#define CORF -.001923077
#define CORG 1.130128205

/// Atmospheric CO2 level for calibration purposes,
/// from "Globally averaged marine surface monthly mean data"
/// available at https://gml.noaa.gov/ccgg/trends/gl_data.html
#define ATMOCO2 415.58 // Global CO2 Aug 2022

#include "stm32f4xx_hal.h"


typedef struct {
	uint32_t *binder;
	  float rload;     // Load resistance on the board in kOhm (default: 10.0)
	  float rzero;     // Calibration resistance (default: 76.63)
} MQ135_t;

// Function prototypes (assuming they are defined elsewhere)
float MQ135_getCorrectionFactor(MQ135_t sensor, float t, float h);
float MQ135_getResistance(MQ135_t sensor);
float MQ135_getCorrectedResistance(MQ135_t sensor, float t, float h);
float MQ135_getPPM(MQ135_t sensor);
float MQ135_getCorrectedPPM(MQ135_t sensor, float t, float h);
float MQ135_getRZero(MQ135_t sensor);
float MQ135_getCorrectedRZero(MQ135_t sensor, float t, float h);

#endif
