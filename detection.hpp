#ifndef DETECTION_H
#define DETECTION_H

void detection_init(void); // Prepares for face detection
void detection(void); // Updates head position in each call (modifies ShiftX,ShiftY,Distance global parameters)

#endif
