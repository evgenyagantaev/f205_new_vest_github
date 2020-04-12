#ifndef QRS_OBJ_H
#define QRS_OBJ_H

#include "main.h"

static char message[64];

#define WINDOW_LENGTH 17
#define SAMPLES_TO_DROP_DEFAULT 10
#define RIGHT_WINDOW_MARGIN 7


// threshold values for r-pick detection
static const uint16_t AMPLITUDELEASTTHRESHOLD = 35;
static const uint16_t AMPLITUDEMOSTTHRESHOLD = 135;
static const uint16_t RLEASTLENGTH = 2;
static const uint16_t RMOSTLENGTH = 7;
// length of local window (piece of ecg sample buffer)
static const uint16_t QRSWINDOWLENGTH = WINDOW_LENGTH;
// constants definitions for array of markers
static const uint16_t EMPTYMARKER = 0;
static const uint16_t WHITEMARKER = 1;
static const uint16_t REDMARKER = 2;
static const uint16_t BLUEMARKER = 3;

static const uint16_t QRSSUSPENDPERIOD = 60;



int32_t qrs_window[WINDOW_LENGTH];
int32_t isoline_window[WINDOW_LENGTH];
int32_t order_numbers[WINDOW_LENGTH];
int32_t markers[WINDOW_LENGTH];
static int samples_to_drop_in_window = SAMPLES_TO_DROP_DEFAULT;

static int qrs_new_sample_added_flag;
static int qrs_suspend_flag = 0;

static int32_t qrs_suspend_marker = 0;
//static int32_t samples_counter;
// bazovyi uroven' izolinii, pri kotorom proizoshlo prevyshenie poroga
// pri detektirovanii R-zubtca
// my zamorazhivaem etot uroven', kak tol'ko detektirovali prevyshenie
static int32_t base_isoline;
// index of r-pick beginning
static int r_start;
// index of r-pick ending
static int r_finish;
// index of r-pick local maximum
static int r_max_index;

// marker of the newest detected r-pick
static int r_marker;
// marker of the old detected r-pick
static int old_rmarker;
static uint32_t new_rr_interval = 0;
static int new_rr_interval_calculated_flag = 0;

// flag that indicates, is local buffer ready for analysis or not
static int local_buffer_ready_flag;
// local buffer counter; counts number of samples in local buffer
static int qrs_buffer_counter;

// asystoly shift counter
static int asystolyShiftCounter = 0;





#endif // QRS_OBJ_H
