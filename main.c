#include <stdio.h>
#include <vorbis/vorbisenc.h>

#include "factorial.h"

int main() {
    const char *inputWavFile = "input.wav";
    const char *outputOggFile = "output.ogg";
    
    enc1(inputWavFile, outputOggFile);

    return 0;
}