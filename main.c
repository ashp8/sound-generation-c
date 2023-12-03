#include <stdio.h>
#include <stdlib.h>
#include <alsa/asoundlib.h>
#include <math.h>
#include <limits.h>

void generateSoundWave(short *buffer, int samples, double freq, int sampleRate);

int main(void){
	int sampleRate = 44100;
	int duration = 5;
	double freq = 440.0;

	int samples = sampleRate * duration;

	snd_pcm_t *pcm_handle;
	snd_pcm_open(&pcm_handle, "default", SND_PCM_STREAM_PLAYBACK, 0);
	
	// set the PCM format
	snd_pcm_set_params(pcm_handle, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED, 1, sampleRate, 1, 50000);

	short *buffer = malloc(samples * sizeof(short));
	generateSoundWave(buffer, samples, freq, sampleRate);
	snd_pcm_writei(pcm_handle, buffer, samples);

	snd_pcm_close(pcm_handle);
	free(buffer);

	return 0;
}


void generateSoundWave(short *buffer, int samples, double freq, int sampleRate){
	double amplitude = 0.1;
	for(int i = 0; i < samples; i++){
		double t = (double)i / sampleRate;
		buffer[i] = amplitude * SHRT_MAX * sin(2 * M_PI * freq * t);

	}
}
