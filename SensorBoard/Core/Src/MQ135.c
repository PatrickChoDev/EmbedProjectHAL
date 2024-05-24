/*
 * MQ135.cpp
 *
 *  Created on: May 24, 2024
 *      Author: patrick
 */

#include "MQ135.h"
#include "math.h"

float MQ135_getCorrectionFactor(MQ135_t sensor, float t, float h) {
	    // Linearization of the temperature dependency curve under and above 20 degree C
	    // below 20degC: fact = a * t * t - b * t - (h - 33) * d
	    // above 20degC: fact = a * t + b * h + c
	    // this assumes a linear dependency on humidity
	    if(t < 20){
	        return CORA * t * t - CORB * t + CORC - (h-33.)*CORD;
	    } else {
	        return CORE * t + CORF * h + CORG;
	    }
}
float MQ135_getResistance(MQ135_t sensor) {
	  float val = *sensor.binder;
	  return ((4095./(float)val) - 1.)* sensor.rload;
}
float MQ135_getCorrectedResistance(MQ135_t sensor, float t, float h) {
	return MQ135_getResistance(sensor)/MQ135_getCorrectionFactor(sensor, t, h);
}
float MQ135_getPPM(MQ135_t sensor) {
	return PARA * pow((MQ135_getResistance(sensor)/sensor.rzero), -PARB);
}
float MQ135_getCorrectedPPM(MQ135_t sensor, float t, float h) {
	return PARA * pow((MQ135_getCorrectedResistance(sensor, t, h)/sensor.rzero), -PARB);
}
float MQ135_getRZero(MQ135_t sensor) {
	return MQ135_getResistance(sensor) * pow((ATMOCO2/PARA), (1./PARB));
}
float MQ135_getCorrectedRZero(MQ135_t sensor, float t, float h) {
	return MQ135_getCorrectedResistance(sensor, t, h) * pow((ATMOCO2/PARA), (1./PARB));
}

