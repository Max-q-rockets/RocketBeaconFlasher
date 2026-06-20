#ifndef BEACON_CONFIG_H
#define BEACON_CONFIG_H

#include <stdint.h>

/* ---------------------------------------------------------------------------
 * Patchable beacon configuration block (config version 4, 72 bytes, packed).
 *
 * The web configurator finds the "BCON" magic in the compiled .bin, writes the
 * user's settings into this struct, and recomputes the checksum. The firmware
 * reads it at startup. Do NOT hand-edit values in the field; change the
 * compiled-in defaults in beacon_config.c instead.
 *
 * Power ramp: within each burst the per-beep power steps evenly from
 * max_power_dbm down to -9 dBm. With several beeps at descending power, the
 * quietest beeps drop out first as you move away from the beacon, so the number
 * of audible beeps gives a coarse range/direction cue. The *_high2low flag sets
 * whether the loudest beep comes first (1) or last (0).
 * ------------------------------------------------------------------------- */

#define BEACON_CONFIG_VERSION 4

typedef struct __attribute__((packed)) {
    uint8_t  magic[4];          /* 0  : {'B','C','O','N'}                     */
    uint32_t rf_freq_hz;        /* 4  : center frequency, e.g. 433225000      */
    int8_t   max_power_dbm;     /* 8  : top of the power ramp, -9 .. 22        */
    uint8_t  mode;              /* 9  : 0=FSK, 1=CW, 2=both (alternate)        */
    uint8_t  use_morse;         /* 10 : 1 = send periodic callsign ID          */
    uint8_t  fsk_num_beeps;     /* 11 : beeps per FSK burst                     */
    uint8_t  fsk_high2low;      /* 12 : 1 = loudest FSK beep first              */
    uint8_t  cw_num_beeps;      /* 13 : beeps per CW burst                      */
    uint8_t  cw_high2low;       /* 14 : 1 = loudest CW beep first               */
    uint8_t  fsk_arpeggio;      /* 15 : 1 = FSK tone steps up each beep         */
    uint32_t fsk_tone_hz;       /* 16 : FSK audio tone                          */
    uint32_t fsk_on_ms;         /* 20 : FSK beep duration                       */
    uint32_t fsk_off_ms;        /* 24 : gap between FSK beeps                    */
    uint32_t cw_on_ms;          /* 28 : CW beep duration                        */
    uint32_t cw_off_ms;         /* 32 : gap between CW beeps                     */
    uint32_t cw_offset_hz;      /* 36 : per-beep CW frequency step              */
    uint32_t burst_period_ms;   /* 40 : time between bursts                      */
    uint32_t startup_delay_ms;  /* 44 : gap before the first burst              */
    uint32_t id_period_ms;      /* 48 : time between callsign IDs               */
    char     callsign[12];      /* 52 : null-padded                             */
    uint32_t config_version;    /* 64 : = 4                                      */
    uint32_t checksum;          /* 68 : XOR of the 17 words at bytes 0..67       */
} BeaconConfig;

extern const BeaconConfig beacon_config;

#endif /* BEACON_CONFIG_H */
