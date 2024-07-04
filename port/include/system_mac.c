#include <AudioToolbox/AudioToolbox.h>
#include <CoreFoundation/CoreFoundation.h>
#include <math.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "system_mac.h"

// Callback function to generate the audio data
void AudioCallback(void *userData, AudioQueueRef queue, AudioQueueBufferRef buffer) {
    int frequency = *((int *)userData);
    int sampleRate = 44100;
    int frames = buffer->mAudioDataBytesCapacity / sizeof(float);
    float *data = (float *)buffer->mAudioData;

    static double phase = 0.0;
    double phaseStep = (2.0 * M_PI * frequency) / sampleRate;

    for (int i = 0; i < frames; ++i) {
        data[i] = sin(phase);
        phase += phaseStep;
        if (phase >= (2.0 * M_PI)) phase -= (2.0 * M_PI);
    }

    buffer->mAudioDataByteSize = frames * sizeof(float);
    AudioQueueEnqueueBuffer(queue, buffer, 0, NULL);
}

void beep(int frequency, int duration) {
    // Audio format
    AudioStreamBasicDescription format;
    format.mSampleRate = 44100;
    format.mFormatID = kAudioFormatLinearPCM;
    format.mFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagIsPacked;
    format.mFramesPerPacket = 1;
    format.mChannelsPerFrame = 1;
    format.mBitsPerChannel = sizeof(float) * 8;
    format.mBytesPerPacket = sizeof(float);
    format.mBytesPerFrame = sizeof(float);

    // Audio queue
    AudioQueueRef queue;
    AudioQueueNewOutput(&format, AudioCallback, &frequency, NULL, kCFRunLoopCommonModes, 0, &queue);

    // Allocate and prime buffers
    int bufferCount = 3;
    int bufferSize = 44100 * sizeof(float) * duration / 1000; // duration in ms
    for (int i = 0; i < bufferCount; ++i) {
        AudioQueueBufferRef buffer;
        AudioQueueAllocateBuffer(queue, bufferSize, &buffer);
        AudioCallback(&frequency, queue, buffer);
    }

    // Start the queue
    AudioQueueStart(queue, NULL);

    // Sleep for the duration
    usleep(duration * 1000);

    // Stop the queue
    AudioQueueStop(queue, true);
    AudioQueueDispose(queue, true);
}

bool is_key_pressed(char smallkey) { //unix version requires small letters
    
    initscr(); // Initialize the ncurses screen
    raw(); // Line buffering disabled
    keypad(stdscr, TRUE); // Enable function keys
    noecho(); // Don't echo while we do getch
    int ch;

    timeout(0); // Non-blocking getch
    while ((ch = getch()) != ERR) {
        if (ch == smallkey) {
            endwin(); // End the ncurses mode
            return true;
        }
    }
    endwin(); // End the ncurses mode
    return false;
}