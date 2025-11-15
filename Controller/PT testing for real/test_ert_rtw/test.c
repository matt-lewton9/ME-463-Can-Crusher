/*
 * test.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "test".
 *
 * Model version              : 1.5
 * Simulink Coder version : 25.1 (R2025a) 21-Nov-2024
 * C source code generated on : Fri Nov 14 08:23:29 2025
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "test.h"
#include <string.h>
#include "rtwtypes.h"
#include <stddef.h>
#include "test_private.h"

/* Block signals (default storage) */
B_test_T test_B;

/* Block states (default storage) */
DW_test_T test_DW;

/* Real-time model */
static RT_MODEL_test_T test_M_;
RT_MODEL_test_T *const test_M = &test_M_;

/* Model step function */
void test_step(void)
{
  uint8_T b_SwappedDataBytes[2];
  uint8_T output_raw;

  /* MATLABSystem: '<Root>/I2C Write' incorporates:
   *  Constant: '<Root>/Constant'
   */
  b_SwappedDataBytes[0] = 1U;
  b_SwappedDataBytes[1] = test_P.Constant_Value;
  MW_I2C_MasterWrite(test_DW.obj_j.I2CDriverObj.MW_I2C_HANDLE, 109UL,
                     &b_SwappedDataBytes[0], 2UL, false, false);

  /* MATLABSystem: '<Root>/I2C Read' */
  output_raw = 4U;
  test_B.I2CRead_o2 = MW_I2C_MasterWrite
    (test_DW.obj_ib.I2CDriverObj.MW_I2C_HANDLE, 109UL, &output_raw, 1UL, true,
     false);
  if (test_B.I2CRead_o2 == 0) {
    MW_I2C_MasterRead(test_DW.obj_ib.I2CDriverObj.MW_I2C_HANDLE, 109UL,
                      &output_raw, 1UL, false, true);
    memcpy((void *)&test_B.I2CRead_o1, (void *)&output_raw, (size_t)1 * sizeof
           (uint8_T));
  } else {
    /* MATLABSystem: '<Root>/I2C Read' */
    test_B.I2CRead_o1 = 0U;
  }

  /* End of MATLABSystem: '<Root>/I2C Read' */
  /* MATLABSystem: '<Root>/I2C Read1' */
  output_raw = 5U;
  test_B.I2CRead1_o2 = MW_I2C_MasterWrite
    (test_DW.obj_i.I2CDriverObj.MW_I2C_HANDLE, 109UL, &output_raw, 1UL, true,
     false);
  if (test_B.I2CRead1_o2 == 0) {
    MW_I2C_MasterRead(test_DW.obj_i.I2CDriverObj.MW_I2C_HANDLE, 109UL,
                      &output_raw, 1UL, false, true);
    memcpy((void *)&test_B.I2CRead1_o1, (void *)&output_raw, (size_t)1 * sizeof
           (uint8_T));
  } else {
    /* MATLABSystem: '<Root>/I2C Read1' */
    test_B.I2CRead1_o1 = 0U;
  }

  /* End of MATLABSystem: '<Root>/I2C Read1' */
  /* MATLABSystem: '<Root>/I2C Read2' */
  output_raw = 6U;
  test_B.I2CRead2_o2 = MW_I2C_MasterWrite(test_DW.obj.I2CDriverObj.MW_I2C_HANDLE,
    109UL, &output_raw, 1UL, true, false);
  if (test_B.I2CRead2_o2 == 0) {
    MW_I2C_MasterRead(test_DW.obj.I2CDriverObj.MW_I2C_HANDLE, 109UL, &output_raw,
                      1UL, false, true);
    memcpy((void *)&test_B.I2CRead2_o1, (void *)&output_raw, (size_t)1 * sizeof
           (uint8_T));
  } else {
    /* MATLABSystem: '<Root>/I2C Read2' */
    test_B.I2CRead2_o1 = 0U;
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
  test_M->Timing.clockTick0++;
  if (!test_M->Timing.clockTick0) {
    test_M->Timing.clockTickH0++;
  }
}

/* Model initialize function */
void test_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)test_M, 0,
                sizeof(RT_MODEL_test_T));
  rtmSetTFinal(test_M, -1);

  /* External mode info */
  test_M->Sizes.checksums[0] = (1221589771U);
  test_M->Sizes.checksums[1] = (4008892068U);
  test_M->Sizes.checksums[2] = (2656462316U);
  test_M->Sizes.checksums[3] = (3671034645U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[5];
    test_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(test_M->extModeInfo,
      &test_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(test_M->extModeInfo, test_M->Sizes.checksums);
    rteiSetTFinalTicks(test_M->extModeInfo, -1);
  }

  /* block I/O */
  (void) memset(((void *) &test_B), 0,
                sizeof(B_test_T));

  /* states (dwork) */
  (void) memset((void *)&test_DW, 0,
                sizeof(DW_test_T));

  /* Start for MATLABSystem: '<Root>/I2C Write' */
  test_DW.obj_j.DefaultMaximumBusSpeedInHz = 400000.0;
  test_DW.obj_j.matlabCodegenIsDeleted = false;
  test_DW.objisempty = true;
  test_DW.obj_j.isInitialized = 1L;
  test_DW.obj_j.I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(0, MW_I2C_MASTER);
  test_DW.obj_j.BusSpeed = 100000UL;
  MW_I2C_SetBusSpeed(test_DW.obj_j.I2CDriverObj.MW_I2C_HANDLE, 100000UL);
  test_DW.obj_j.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/I2C Read' */
  test_DW.obj_ib.DefaultMaximumBusSpeedInHz = 400000.0;
  test_DW.obj_ib.matlabCodegenIsDeleted = false;
  test_DW.objisempty_h = true;
  test_DW.obj_ib.isInitialized = 1L;
  test_DW.obj_ib.I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(0, MW_I2C_MASTER);
  test_DW.obj_ib.BusSpeed = 100000UL;
  MW_I2C_SetBusSpeed(test_DW.obj_ib.I2CDriverObj.MW_I2C_HANDLE, 100000UL);
  test_DW.obj_ib.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/I2C Read1' */
  test_DW.obj_i.DefaultMaximumBusSpeedInHz = 400000.0;
  test_DW.obj_i.matlabCodegenIsDeleted = false;
  test_DW.objisempty_b = true;
  test_DW.obj_i.isInitialized = 1L;
  test_DW.obj_i.I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(0, MW_I2C_MASTER);
  test_DW.obj_i.BusSpeed = 100000UL;
  MW_I2C_SetBusSpeed(test_DW.obj_i.I2CDriverObj.MW_I2C_HANDLE, 100000UL);
  test_DW.obj_i.isSetupComplete = true;

  /* Start for MATLABSystem: '<Root>/I2C Read2' */
  test_DW.obj.DefaultMaximumBusSpeedInHz = 400000.0;
  test_DW.obj.matlabCodegenIsDeleted = false;
  test_DW.objisempty_j = true;
  test_DW.obj.isInitialized = 1L;
  test_DW.obj.I2CDriverObj.MW_I2C_HANDLE = MW_I2C_Open(0, MW_I2C_MASTER);
  test_DW.obj.BusSpeed = 100000UL;
  MW_I2C_SetBusSpeed(test_DW.obj.I2CDriverObj.MW_I2C_HANDLE, 100000UL);
  test_DW.obj.isSetupComplete = true;
}

/* Model terminate function */
void test_terminate(void)
{
  /* Terminate for MATLABSystem: '<Root>/I2C Write' */
  if (!test_DW.obj_j.matlabCodegenIsDeleted) {
    test_DW.obj_j.matlabCodegenIsDeleted = true;
    if ((test_DW.obj_j.isInitialized == 1L) && test_DW.obj_j.isSetupComplete) {
      MW_I2C_Close(test_DW.obj_j.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/I2C Write' */

  /* Terminate for MATLABSystem: '<Root>/I2C Read' */
  if (!test_DW.obj_ib.matlabCodegenIsDeleted) {
    test_DW.obj_ib.matlabCodegenIsDeleted = true;
    if ((test_DW.obj_ib.isInitialized == 1L) && test_DW.obj_ib.isSetupComplete)
    {
      MW_I2C_Close(test_DW.obj_ib.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/I2C Read' */
  /* Terminate for MATLABSystem: '<Root>/I2C Read1' */
  if (!test_DW.obj_i.matlabCodegenIsDeleted) {
    test_DW.obj_i.matlabCodegenIsDeleted = true;
    if ((test_DW.obj_i.isInitialized == 1L) && test_DW.obj_i.isSetupComplete) {
      MW_I2C_Close(test_DW.obj_i.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/I2C Read1' */
  /* Terminate for MATLABSystem: '<Root>/I2C Read2' */
  if (!test_DW.obj.matlabCodegenIsDeleted) {
    test_DW.obj.matlabCodegenIsDeleted = true;
    if ((test_DW.obj.isInitialized == 1L) && test_DW.obj.isSetupComplete) {
      MW_I2C_Close(test_DW.obj.I2CDriverObj.MW_I2C_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<Root>/I2C Read2' */
}
