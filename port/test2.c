#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>

    void play_tone(int frequency, int duration_ms) {
        Beep(frequency, duration_ms);
    }
#elif __APPLE__
    #include <AudioToolbox/AudioToolbox.h>
    #include <math.h>
    #include <unistd.h>

    typedef struct {
        double frequency;
        double sampleRate;
        double theta;
    } ToneContext;

    static OSStatus RenderTone(void *inRefCon, AudioUnitRenderActionFlags *ioActionFlags,
                               const AudioTimeStamp *inTimeStamp, UInt32 inBusNumber, UInt32 inNumberFrames,
                               AudioBufferList *ioData) {
        ToneContext *toneContext = (ToneContext *)inRefCon;
        double theta = toneContext->theta;
        double theta_increment = 2.0 * M_PI * toneContext->frequency / toneContext->sampleRate;
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

        toneContext->theta = theta;

        return noErr;
    }

    void play_tone(int frequency, int duration_ms) {
        AudioComponentInstance toneUnit;
        AudioComponentDescription defaultOutputDescription = {
            .componentType = kAudioUnitType_Output,
            .componentSubType = kAudioUnitSubType_DefaultOutput,
            .componentManufacturer = kAudioUnitManufacturer_Apple,
            .componentFlags = 0,
            .componentFlagsMask = 0
        };

        AudioComponent defaultOutput = AudioComponentFindNext(NULL, &defaultOutputDescription);
        AudioComponentInstanceNew(defaultOutput, &toneUnit);

        AudioUnitInitialize(toneUnit);

        // Set the render callback
        AURenderCallbackStruct input;
        ToneContext toneContext = { .frequency = frequency, .sampleRate = 44100.0, .theta = 0 };
        input.inputProc = RenderTone;
        input.inputProcRefCon = &toneContext;
        AudioUnitSetProperty(toneUnit, kAudioUnitProperty_SetRenderCallback, kAudioUnitScope_Input, 0, &input, sizeof(input));

        // Set the format
        AudioStreamBasicDescription streamFormat = {
            .mSampleRate = 44100,
            .mFormatID = kAudioFormatLinearPCM,
            .mFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagIsPacked,
            .mFramesPerPacket = 1,
            .mChannelsPerFrame = 1,
            .mBitsPerChannel = sizeof(float) * 8,
            .mBytesPerPacket = sizeof(float),
            .mBytesPerFrame = sizeof(float)
        };

        AudioUnitSetProperty(toneUnit, kAudioUnitProperty_StreamFormat, kAudioUnitScope_Input, 0, &streamFormat, sizeof(streamFormat));

        // Start playing
        AudioOutputUnitStart(toneUnit);

        usleep(duration_ms * 1000);

        // Stop playing
        AudioOutputUnitStop(toneUnit);
        AudioUnitUninitialize(toneUnit);
        AudioComponentInstanceDispose(toneUnit);
    }
#endif

int main() {
    int frequency = 440; // Frequency in Hz (A4 note)
    int duration = 1000; // Duration in milliseconds

    printf("Playing tone: %d Hz for %d ms\n", frequency, duration);
    play_tone(frequency, duration);

    return 0;
}