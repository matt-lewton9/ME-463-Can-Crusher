/*
 * testing.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "testing".
 *
 * Model version              : 1.3
 * Simulink Coder version : 25.1 (R2025a) 21-Nov-2024
 * C source code generated on : Tue Nov 11 19:50:42 2025
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef testing_h_
#define testing_h_
#ifndef testing_COMMON_INCLUDES_
#define testing_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "MW_AnalogIn.h"
#include "MW_I2C.h"
#endif                                 /* testing_COMMON_INCLUDES_ */

#include "testing_types.h"
#include <string.h>
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                (&)
#endif

/* Block signals (default storage) */
typedef struct {
  uint16_T AnalogInput;                /* '<Root>/Analog Input' */
  uint8_T I2CRead2_o1;                 /* '<Root>/I2C Read2' */
  uint8_T I2CRead2_o2;                 /* '<Root>/I2C Read2' */
  uint8_T I2CRead1_o1;                 /* '<Root>/I2C Read1' */
  uint8_T I2CRead1_o2;                 /* '<Root>/I2C Read1' */
  uint8_T I2CRead_o1;                  /* '<Root>/I2C Read' */
  uint8_T I2CRead_o2;                  /* '<Root>/I2C Read' */
} B_testing_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  codertarget_arduinobase_int_o_T obj; /* '<Root>/I2C Read2' */
  codertarget_arduinobase_int_o_T obj_b;/* '<Root>/I2C Read1' */
  codertarget_arduinobase_int_o_T obj_g;/* '<Root>/I2C Read' */
  codertarget_arduinobase_inter_T obj_m;/* '<Root>/Analog Input' */
  boolean_T objisempty;                /* '<Root>/I2C Read2' */
  boolean_T objisempty_m;              /* '<Root>/I2C Read1' */
  boolean_T objisempty_n;              /* '<Root>/I2C Read' */
  boolean_T objisempty_d;              /* '<Root>/Analog Input' */
} DW_testing_T;

/* Real-time Model Data Structure */
struct tag_RTM_testing_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};

/* Block signals (default storage) */
extern B_testing_T testing_B;

/* Block states (default storage) */
extern DW_testing_T testing_DW;

/* Model entry point functions */
extern void testing_initialize(void);
extern void testing_step(void);
extern void testing_terminate(void);

/* Real-time Model object */
extern RT_MODEL_testing_T *const testing_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'testing'
 */
#endif                                 /* testing_h_ */
