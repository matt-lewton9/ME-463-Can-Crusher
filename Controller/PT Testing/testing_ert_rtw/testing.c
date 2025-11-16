/*
 * testing.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "testing".
 *
 * Model version              : 1.8
 * Simulink Coder version : 25.1 (R2025a) 21-Nov-2024
 * C source code generated on : Thu Nov 13 14:03:39 2025
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "testing.h"
#include <string.h>
#include "rtwtypes.h"
#include <stddef.h>
#include "testing_private.h"

/* Block signals (default storage) */
B_testing_T testing_B;

/* Block states (default storage) */
DW_testing_T testing_DW;

/* Real-time model */
static RT_MODEL_testing_T testing_M_;
RT_MODEL_testing_T *const testing_M = &testing_M_;

/* Model step function */
void testing_step(void)
{
  uint8_T output_raw;

  /* MATLABSystem: '<Root>/Analog Input' */
  testing_DW.obj_m.AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogIn_GetHandle
    (59UL);

  /* MATLABSystem: '<Root>/Analog Input' */
  MW_AnalogInSingle_ReadResult
    (testing_DW.obj_m.AnalogInDriverObj.MW_ANALOGIN_HANDLE,
     &testing_B.AnalogInput, MW_ANALOGIN_UINT16);

  /* MATLABSystem: '<Root>/I2C Read' */
  output_raw = 7U;
  testing_B.I2CRead_o2 = MW_I2C_MasterWrite
    (testing_DW.obj_g.I2CDriverObj.MW_I2C_HANDLE, 109UL, &output_raw, 1UL, true,
     false);
  if (testing_B.I2CRead_o2 == 0) {
    MW_I2C_MasterRead(testing_DW.obj_g.I2CDriverObj.MW_I2C_HANDLE, 109UL,
                      &output_raw, 1UL, false, true);
    memcpy((void *)&testing_B.I2CRead_o1, (void *)&output_raw, (size_t)1 *
           sizeof(uint8_T));
  } else {
    /* MATLABSystem: '<Root>/I2C Read' */
    testing_B.I2CRead_o1 = 0U;
  }

  /* End of MATLABSystem: '<Root>/I2C Read' */
  /* MATLABSystem: '<Root>/I2C Read1' */
  output_raw = 5U;
  testing_B.I2CRead1_o2 = MW_I2C_MasterWrite
    (testing_DW.obj_b.I2CDriverObj.MW_I2C_HANDLE, 88UL, &output_raw, 1UL, true,
     false);
  if (testing_B.I2CRead1_o2 == 0) {
    MW_I2C_MasterRead(testing_DW.obj_b.I2CDriverObj.MW_I2C_HANDLE, 88UL,
                      &output_raw, 1UL, false, true);
    memcpy((void *)&testing_B.I2CRead1_o1, (void *)&output_raw, (size_t)1 *
           sizeof(uint8_T));
  } else {
    /* MATLABSystem: '<Root>/I2C Read1' */
    testing_B.I2CRead1_o1 = 0U;
  }

  /* End of MATLABSystem: '<Root>/I2C Read1' */
  /* MATLABSystem: '<Root>/I2C Read2' */
  output_raw = 6U;
  testing_B.I2CRead2_o2 = MW_I2C_MasterWrite
    (testing_DW.obj.I2CDriverObj.MW_I2C_HANDLE, 88UL, &output_raw, 1UL, true,
     false);
  if (testing_B.I2CRead2_o2 == 0) {
    MW_I2C_MasterRead(testing_DW.obj.I2CDriverObj.MW_I2C_HANDLE, 88UL,
                      &output_raw, 1UL, false, true);
    memcpy((void *)&testing_B.I2CRead2_o1, (void *)&output_raw, (size_t)1 *
           sizeof(uint8_T));
  } else {
    /* MATLABSystem: '<Root>/I2C Read2' */
    testing_B.I2CRead2_o1 = 0U;
  }

  /* End of MATLABSystem: '<Root>/I2C Read2' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The resolution of this integer timer is 0.1, which is the step size
   * of the task. Size of "clockTick0" ensures timer will not overflow during the
   * application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  testing_M->Timing.clockTick0++;
  if (!testing_M->Timing.clockTick0) {
    testing_M->Timing.clockTickH0++;
  }
}

/* Model initialize function */
void testing_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)testing_M, 0,
                sizeof(RT_MODEL_testing_T));
  rtmSetTFinal(testing_M, -1);

  /* External mode info */
  testing_M->Sizes.checksums[0] = (3923556422U);
  testing_M->Sizes.checksums[1] = (3669867023U);
  testing_M->Sizes.checksums[2] = (266100537U);
  testing_M->Sizes.checksums[3] = (2237703999U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    testing_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(testing_M->extModeInfo,
      &testing_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(testing_M->extModeInfo, testing_M->Sizes.checksums);
    rteiSetTFinalTicks(testing_M->extModeInfo, -1);
  }

  /* block I/O */
  (void) memset(((void *) &testing_B), 0,
                sizeof(B_testing_T));

  /* states (dwork) */
  (void) memset((void *)&testing_DW, 0,
                sizeof(DW_testing_T));

  /* Start for MATLABSystem: '<Root>/Analog Input' */
  testing_DW.obj_m.matlabCodegenIsDeleted = false;
  testing_DW.objisempty_d = true;
  testing_DW.obj_m.isInitialized = 1L;
  testing_DW.obj_m.AnalogInDriverObj.MW_ANALOGIN_HANDLE = MW_AnalogInSingle_Open
    (59UL);
  testing_DW.obj_m.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/I2C Read' */
  testing_DW.obj_g.DefaultMaximumBusSpeedInHz = 400000.0;
  testing_DW.obj_g.matlabCodegenIsDeleted = false;
  testing_DW.objisempty_n = true;
  testing_DW.obj_g.isInitialized = 1L;
  testing_DW.obj_g.I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(0, MW_I2C_MASTER);
  testing_DW.obj_g.BusSpeed = 100000UL;
  MW_I2C_SetBusSpeed(testing_DW.obj_g.I2CDriverObj.MW_I2C_HANDLE, 100000UL);
  testing_DW.obj_g.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/I2C Read1' */
  testing_DW.obj_b.DefaultMaximumBusSpeedInHz = 400000.0;
  testing_DW.obj_b.matlabCodegenIsDeleted = false;
  testing_DW.objisempty_m = true;
  testing_DW.obj_b.isInitialized = 1L;
  testing_DW.obj_b.I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(0, MW_I2C_MASTER);
  testing_DW.obj_b.BusSpeed = 100000UL;
  MW_I2C_SetBusSpeed(testing_DW.obj_b.I2CDriverObj.MW_I2C_HANDLE, 100000UL);
  testing_DW.obj_b.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/I2C Read2' */
  testing_DW.obj.DefaultMaximumBusSpeedInHz = 400000.0;
  testing_DW.obj.matlabCodegenIsDeleted = false;
  testing_DW.objisempty = true;
  testing_DW.obj.isInitialized = 1L;
  testing_DW.obj.I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(0, MW_I2C_MASTER);
  testing_DW.obj.BusSpeed = 100000UL;
  MW_I2C_SetBusSpeed(testing_DW.obj.I2CDriverObj.MW_I2C_HANDLE, 100000UL);
  testing_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void testing_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/Analog Input' */
  if (!testing_DW.obj_m.matlabCodegenIsDeleted) {
    testing_DW.obj_m.matlabCodegenIsDeleted = true;
    if ((testing_DW.obj_m.isInitialized == 1L) &&
        testing_DW.obj_m.isSetupComplete) {
      testing_DW.obj_m.AnalogInDriverObj.MW_ANALOGIN_HANDLE =
        MW_AnalogIn_GetHandle(59UL);
      MW_AnalogIn_Close(testing_DW.obj_m.AnalogInDriverObj.MW_ANALOGIN_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/Analog Input' */
  /* Terminate for MATLABSystem: '<Root>/I2C Read' */
  if (!testing_DW.obj_g.matlabCodegenIsDeleted) {
    testing_DW.obj_g.matlabCodegenIsDeleted = true;
    if ((testing_DW.obj_g.isInitialized == 1L) &&
        testing_DW.obj_g.isSetupComplete) {
      MW_I2C_Close(testing_DW.obj_g.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/I2C Read' */
  /* Terminate for MATLABSystem: '<Root>/I2C Read1' */
  if (!testing_DW.obj_b.matlabCodegenIsDeleted) {
    testing_DW.obj_b.matlabCodegenIsDeleted = true;
    if ((testing_DW.obj_b.isInitialized == 1L) &&
        testing_DW.obj_b.isSetupComplete) {
      MW_I2C_Close(testing_DW.obj_b.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/I2C Read1' */
  /* Terminate for MATLABSystem: '<Root>/I2C Read2' */
  if (!testing_DW.obj.matlabCodegenIsDeleted) {
    testing_DW.obj.matlabCodegenIsDeleted = true;
    if ((testing_DW.obj.isInitialized == 1L) && testing_DW.obj.isSetupComplete)
    {
      MW_I2C_Close(testing_DW.obj.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/I2C Read2' */
}
