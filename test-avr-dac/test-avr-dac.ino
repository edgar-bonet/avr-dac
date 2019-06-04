/*
 * === test-avr-dac.ino: Drive an avr-dac from an Arduino. ===
 *
 * This is a companion program to avr-dac.S, an AVR implementation of a
 * PDM DAC. This program sends a demo waveform to the avr-dac, one
 * sample at a time, using shiftOut(). The avr-dac is slow in shifting
 * in: each logic level should be held for at least 26 of its cycles
 * (3.25 us). It turns out that digitalWrite() and shiftOut() are slow
 * enough that there is no need to insert extra delays.
 *
 * The waveform is sent repeatedly at a rate of ~ 7.6 ksamp/s and has
 * then a fundamental frequency of 118 Hz. Most of the conversion noise
 * is expected to be above 75 kHz.
 *
 * Wiring:
 *   Arduino   avr-dac (default assignment)
 *       8  -->  CLK   (PB0)
 *       9  -->  DAT   (PB1)
 *      10  -->  LATCH (PB2)
 *               OUT   (PB3)  -->  RC filter
 *
 * Copyright (c) 2019 Edgar Bonet Orozco.
 * This file is part of avr-dac, licensed under the terms of the MIT
 * license. See file LICENSE for details.
 */

#include <math.h>

/* Output pins. */
#define CLK    8
#define DAT    9
#define LATCH 10

#define WAVEFORM_LENGTH 64

/*
 * Pre-computed waveform. Since the Arduino is slow at math, we get
 * better timings by pre-computing the whole waveform at setup().
 */
uint8_t waveform[WAVEFORM_LENGTH];

/*
 * A nice oscillation, with one large and three small peaks.
 * Period = 2 pi, range = [-1, 1].
 */
float wave(float x)
{
    const float min = -1.51956, max = 4,
                amp = (max-min)/2, avg = (max+min)/2;
    float y = cos(x) + cos(2*x) + cos(3*x) + cos(4*x);
    return (y - avg) / amp;
}

void setup()
{
    /* Populate waveform[]. */
    for (int i = 0; i < WAVEFORM_LENGTH; i++) {
        float phase = 2*M_PI * i / WAVEFORM_LENGTH;
        waveform[i] = 128.5 + 96 * wave(phase);
    }
    pinMode(CLK,   OUTPUT);
    pinMode(DAT,   OUTPUT);
    pinMode(LATCH, OUTPUT);
}

void loop()
{
    static int i = 0;
    shiftOut(DAT, CLK, MSBFIRST, waveform[i++]);
    if (i >= WAVEFORM_LENGTH) i = 0;
    digitalWrite(LATCH, HIGH);
    digitalWrite(LATCH, LOW);
}
