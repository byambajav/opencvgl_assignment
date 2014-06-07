#ifndef PLAYSOUND_H
#define PLAYSOUND_H

int init_audio_output(); // Opens audio source and returns the device's ID
void write_output(short buf[], int deviceID); // Writes given buffer to given audio device

#endif

