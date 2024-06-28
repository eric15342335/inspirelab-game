#ifndef DRIVER_H
#define DRIVER_H

#include "oled_min.h"
#include <time.h>

// OLED commands
#define JOY_init OLED_init
#define JOY_OLED_end _OLED_doNothing
#define JOY_OLED_send(b) _OLED_setBuffer(b)
#define JOY_OLED_data_start(y)                                                         \
    {                                                                                  \
        OLED_setpos(0, y);                                                             \
        OLED_data_start();                                                             \
    }
#ifdef _WIN32
    #include <windows.h>
    void DLY_ms(int milliseconds) {
        Sleep(milliseconds);
    }
#else
    #include <time.h>
    void DLY_ms(int milliseconds) {
        struct timespec ts;
        ts.tv_sec = milliseconds / 1000;
        ts.tv_nsec = (milliseconds % 1000) * 1000000;
        nanosleep(&ts, NULL);
    }
#endif

// Platform-specific includes and JOY_sound function
#ifdef _WIN32
    #include <windows.h>

    void JOY_sound(int frequency, int duration_ms) {
        Beep(frequency, duration_ms);
    }
#elif __APPLE__
    #include <AudioToolbox/AudioToolbox.h>
        static OSStatus RenderTone(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags,
                               const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames,
                               AudioBufferList *ioData) {
        double sampleRate = 44100;
        double theta = 0;
        double theta_increment = 2.0 * M_PI * (*(int *)inRefCon) / sampleRate;
        float amplitude = 0.25;

        for (UInt32 frame = 0; frame < inNumberFrames; frame++) {
            float sample = (float)(sin(theta) * amplitude);
            for (UInt32 channel = 0; channel < ioData->mNumberBuffers; channel++) {
                float *buffer = (float *)ioData->mBuffers[channel].mData;
                buffer[frame] = sample;
            }
            theta += theta_increment;
            if (theta > 2.0 * M_PI) {
                theta -= 2.0 * M_PI;
            }
        }

        return noErr;
    }

    void JOY_sound(int frequency, int duration_ms) {
        // Generate a tone using AudioToolbox
        AudioComponentInstance toneUnit;
        AudioComponentDescription defaultOutputDescription;
        defaultOutputDescription.componentType = kAudioUnitType_Output;
        defaultOutputDescription.componentSubType = kAudioUnitSubType_DefaultOutput;
        defaultOutputDescription.componentManufacturer = kAudioUnitManufacturer_Apple;
        defaultOutputDescription.componentFlags = 0;
        defaultOutputDescription.componentFlagsMask = 0;

        AudioComponent defaultOutput = AudioComponentFindNext(NULL, &defaultOutputDescription);
        AudioComponentInstanceNew(defaultOutput, &toneUnit);

        AudioUnitInitialize(toneUnit);

        // Set the render callback
        AURenderCallbackStruct input;
        input.inputProc = RenderTone;
        input.inputProcRefCon = &frequency;
        AudioUnitSetProperty(toneUnit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input, 0, &input, sizeof(input));

        // Start playing
        AudioOutputUnitStart(toneUnit);

        usleep(duration_ms * 1000);

        // Stop playing
        AudioOutputUnitStop(toneUnit);
        AudioUnitUninitialize(toneUnit);
        AudioComponentInstanceDispose(toneUnit);
    }

#endif

#endif // DRIVER_H

// Platform-specific includes and sleep functions

