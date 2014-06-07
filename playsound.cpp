#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/soundcard.h>

#include "common.hpp"

#define BUFFSIZE (LENGTH * RATE * SIZE * CHANNELS) // bytes sent to audio device

int init_audio_output()
{
  int deviceID, arg, status;
  deviceID = open("/dev/dsp", O_WRONLY, 0); 
  if (deviceID < 0) { 
    perror("Opening /dev/dsp failed\n"); 
    return deviceID;
  }
  arg = SIZE * 8;
  status = ioctl(deviceID, SOUND_PCM_WRITE_BITS, &arg);
  if (status == -1){
    perror("Unable to set sample size\n");
  }
  
  arg = CHANNELS;
  status = ioctl(deviceID, SOUND_PCM_WRITE_CHANNELS, &arg);
  if (status == -1){
    perror("Unable to set number of channels\n");
  }
  arg = RATE;
  status = ioctl(deviceID, SOUND_PCM_WRITE_RATE, &arg);
  if (status == -1){
    perror("Unable to set sampling rate\n");
  }
  
  return deviceID;
}

void write_output(short buf[], int deviceID) {
  int status;
  status = write(deviceID, buf, BUFFSIZE);
  if (status != BUFFSIZE){
    perror("Wrote wrong number of bytes\n");
  }
  status = ioctl(deviceID, SOUND_PCM_SYNC, 0);
  if (status == -1){
    perror("SOUND_PCM_SYNC failed\n");
  }
}

