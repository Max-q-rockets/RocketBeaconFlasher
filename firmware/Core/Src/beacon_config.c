#include "beacon_config.h"

/* Compiled-in defaults. The web configurator overwrites these in the .bin and
 * recomputes the checksum, so this is just the patch baseline. The struct must
 * live in its own flash section (see the linker script) so the tool can find
 * and patch it at a known address.                                            */
const BeaconConfig beacon_config
    __attribute__((section(".beacon_config"), used)) = {
    .magic            = {'B', 'C', 'O', 'N'},
    .rf_freq_hz       = 433225000,   /* 433.225 MHz                 */
    .max_power_dbm    = 14,          /* top of the power ramp       */
    .mode             = 0,           /* 0=FSK, 1=CW, 2=both         */
    .use_morse        = 1,

    /* FSK burst */
    .fsk_num_beeps    = 3,
    .fsk_high2low     = 1,           /* loudest beep first          */
    .fsk_arpeggio     = 0,           /* 1 = step tone up each beep  */
    .fsk_tone_hz      = 200,         /* base / starting tone        */
    .fsk_on_ms        = 200,
    .fsk_off_ms       = 200,

    /* CW burst (shorter beeps save power) */
    .cw_num_beeps     = 4,
    .cw_high2low      = 1,
    .cw_on_ms         = 40,
    .cw_off_ms        = 40,
    .cw_offset_hz     = 150,         /* per-beep pitch step         */

    /* timing */
    .burst_period_ms  = 2000,        /* every 2 s                   */
    .startup_delay_ms = 500,         /* ~0.5 s power-on gap         */
    .id_period_ms     = 600000,      /* callsign every 10 min       */

    .callsign         = "N0CALL",
    .config_version   = BEACON_CONFIG_VERSION,
    .checksum         = 0
};
