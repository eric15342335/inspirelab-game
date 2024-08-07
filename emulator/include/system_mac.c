#include <AudioToolbox/AudioToolbox.h>
#include <CoreFoundation/CoreFoundation.h>
#include <math.h>
#include <stdlib.h>
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

void _beep(int frequency, int duration) {
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

#define MAX_KEYS 6

CGKeyCode pressedKeys[MAX_KEYS];
int pressedKeyCount = 0;
pthread_mutex_t keyMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_t thread;

void addKey(CGKeyCode keyCode) {
    for (int i = 0; i < pressedKeyCount; i++) {
        if (pressedKeys[i] == keyCode) return; // Key already in array
    }
    if (pressedKeyCount < MAX_KEYS) {
        pressedKeys[pressedKeyCount++] = keyCode;
    }
}

void removeKey(CGKeyCode keyCode) {
    for (int i = 0; i < pressedKeyCount; i++) {
        if (pressedKeys[i] == keyCode) {
            // Move last element to this position and decrease count
            pressedKeys[i] = pressedKeys[--pressedKeyCount];
            return;
        }
    }
}

bool is_key_pressed(CGKeyCode keyCode) {
    bool pressed = false;
    pthread_mutex_lock(&keyMutex);
    for (int i = 0; i < pressedKeyCount; i++) {
        if (pressedKeys[i] == keyCode) {
            pressed = true;
            break;
        }
    }
    pthread_mutex_unlock(&keyMutex);
    return pressed;
}

CGEventRef keyboardCallback(CGEventTapProxy proxy, CGEventType type, CGEventRef event, void *refcon) {
    (void)proxy;
    (void)refcon;
    if (type != kCGEventKeyDown && type != kCGEventKeyUp) {
        return event;
    }

    CGKeyCode keyCode = (CGKeyCode)CGEventGetIntegerValueField(event, kCGKeyboardEventKeycode);

    pthread_mutex_lock(&keyMutex);
    if (type == kCGEventKeyDown) {
        addKey(keyCode);
    } else if (type == kCGEventKeyUp) {
        removeKey(keyCode);
    }
    pthread_mutex_unlock(&keyMutex);

    return event;
}

void* eventTapThread(void* arg) {
    (void)arg;
    CFMachPortRef eventTap;
    CFRunLoopSourceRef runLoopSource;

    eventTap = CGEventTapCreate(kCGSessionEventTap, kCGHeadInsertEventTap, 0,
                                kCGEventMaskForAllEvents, keyboardCallback, NULL);

    if (!eventTap) {
        fprintf(stderr, "Failed to create event tap\n");
        return NULL;
    }

    runLoopSource = CFMachPortCreateRunLoopSource(kCFAllocatorDefault, eventTap, 0);
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopCommonModes);
    CGEventTapEnable(eventTap, true);

    CFRunLoopRun();

    return NULL;
}

void pthread_init(){
    pthread_create(&thread, NULL, eventTapThread, NULL);
}
