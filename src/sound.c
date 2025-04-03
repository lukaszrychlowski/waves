#include <sound.h>

void *capture_audio()
{
    snd_pcm_t* handle;
    snd_pcm_open(&handle, "plughw:CARD=LCSUSBAudio,DEV=0", SND_PCM_STREAM_CAPTURE, 0);
    snd_pcm_set_params(handle, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED, 2, 44100, 1, 500000);
    short buffer[128 * 2];

    while(1)
    {
        snd_pcm_readi(handle, buffer, 128);
        for(int i = 0; i < 128; i++) printf("%.3f\n", buffer[i] / 32768.0F);
    }

    snd_pcm_close(handle);
    pthread_exit(NULL);
}


