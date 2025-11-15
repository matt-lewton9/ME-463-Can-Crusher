/*
 * test_types.h
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

#ifndef test_types_h_
#define test_types_h_
#include "MW_SVD.h"
#include "rtwtypes.h"

/* Custom Type definition for MATLABSystem: '<Root>/I2C Write' */
#include "MW_SVD.h"
#ifndef struct_tag_BczSCX0m9Gp7rApo3jZAxG
#define struct_tag_BczSCX0m9Gp7rApo3jZAxG

struct tag_BczSCX0m9Gp7rApo3jZAxG
{
  MW_Handle_Type MW_I2C_HANDLE;
};

#endif                                 /* struct_tag_BczSCX0m9Gp7rApo3jZAxG */

#ifndef typedef_c_arduinodriver_ArduinoI2C_te_T
#define typedef_c_arduinodriver_ArduinoI2C_te_T

typedef struct tag_BczSCX0m9Gp7rApo3jZAxG c_arduinodriver_ArduinoI2C_te_T;

#endif                             /* typedef_c_arduinodriver_ArduinoI2C_te_T */

#ifndef struct_tag_NY00b9HBulK1thgQUijEwC
#define struct_tag_NY00b9HBulK1thgQUijEwC

struct tag_NY00b9HBulK1thgQUijEwC
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  c_arduinodriver_ArduinoI2C_te_T I2CDriverObj;
  uint32_T BusSpeed;
  real_T DefaultMaximumBusSpeedInHz;
};

#endif                                 /* struct_tag_NY00b9HBulK1thgQUijEwC */

#ifndef typedef_codertarget_arduinobase_inter_T
#define typedef_codertarget_arduinobase_inter_T

typedef struct tag_NY00b9HBulK1thgQUijEwC codertarget_arduinobase_inter_T;

#endif                             /* typedef_codertarget_arduinobase_inter_T */

#ifndef struct_tag_kHIoPIOtGLhFJAEYiu4mFB
#define struct_tag_kHIoPIOtGLhFJAEYiu4mFB

struct tag_kHIoPIOtGLhFJAEYiu4mFB
{
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  c_arduinodriver_ArduinoI2C_te_T I2CDriverObj;
  uint32_T BusSpeed;
  real_T DefaultMaximumBusSpeedInHz;
};

#endif                                 /* struct_tag_kHIoPIOtGLhFJAEYiu4mFB */

#ifndef typedef_codertarget_arduinobase_int_j_T
#define typedef_codertarget_arduinobase_int_j_T

typedef struct tag_kHIoPIOtGLhFJAEYiu4mFB codertarget_arduinobase_int_j_T;

#endif                             /* typedef_codertarget_arduinobase_int_j_T */

/* Parameters (default storage) */
typedef struct P_test_T_ P_test_T;

/* Forward declaration for rtModel */
typedef struct tag_RTM_test_T RT_MODEL_test_T;

#endif                                 /* test_types_h_ */
