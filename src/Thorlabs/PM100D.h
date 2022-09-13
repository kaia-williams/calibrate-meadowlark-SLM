/****************************************************************************

   Thorlabs PM100x Series VISA instrument driver

   This driver supports PM100A, PM100D, PM100USB, PM160, PM160T, PM200, and 
   PM400 optical power meters.
   
   FOR DETAILED DESCRIPTION OF THE DRIVER FUNCTIONS SEE THE ONLINE HELP FILE
   AND THE PROGRAMMERS REFERENCE MANUAL.

   Copyright:  Copyright(c) 2008-2016, Thorlabs (www.thorlabs.com)
   Author:     Michael Biebl (mbiebl@thorlabs.com),
			   Diethelm Krause (dkrause@thorlabs.com),
			   Thomas Schlosser (tschlosser@thorlabs.com)

   Disclaimer:
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


   Header file

   Date:          Jul-08-2016
   Built with:    NI LabWindows/CVI 2012 (12.0.1)
   Software-Nr:   09.180.xxx
   Version:       3.2.0

   Changelog:     see 'readme.rtf'

****************************************************************************/


#ifndef _PM100D_DRIVER_HEADER_
#define _PM100D_DRIVER_HEADER_

#include <vpptype.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C"
{
#endif


/*===========================================================================

 Macros

===========================================================================*/
/*---------------------------------------------------------------------------
 USB instrument identification
---------------------------------------------------------------------------*/
#define PM100D_VID_THORLABS            (0x1313)   // Thorlabs
#define PM100D_PID_PM100D_DFU          (0x8070)   // PM100D with DFU interface enabled
#define PM100D_PID_PM100A_DFU          (0x8071)   // PM100A with DFU interface enabled
#define PM100D_PID_PM100USB            (0x8072)   // PM100USB with DFU interface enabled
#define PM100D_PID_PM160USB_DFU        (0x8073)   // PM160 on USB with DFU interface enabled
#define PM100D_PID_PM160TUSB_DFU       (0x8074)   // PM160T on USB with DFU interface enabled
#define PM100D_PID_PM400_DFU           (0x8075)   // PM400 on USB with DFU interface enabled
#define PM100D_PID_PM101_DFU           (0x8076)   // PM101 on USB with DFU interface enabled 
#define PM100D_PID_PM102_DFU           (0x8077)   // PM102 on USB with DFU interface enabled 

#define PM100D_PID_PM100D              (0x8078)   // PM100D w/o DFU interface
#define PM100D_PID_PM100A              (0x8079)   // PM100A w/o DFU interface
#define PM100D_PID_PM160USB            (0x807B)   // PM160 on USB w/o DFU interface
#define PM100D_PID_PM160TUSB           (0x807C)   // PM160T on USB w/o DFU interface
#define PM100D_PID_PM400               (0x807D)   // PM400 on USB w/o DFU interface
#define PM100D_PID_PM101               (0x807E)   // PM101 on USB w/o DFU interface  
#define PM100D_PID_PM102               (0x807F)   // PM102 on USB w/o DFU interface   

#define PM100D_PID_PM200               (0x80B0)   // PM200 

/*---------------------------------------------------------------------------
 Find pattern for 'viFindRsrc()'
---------------------------------------------------------------------------*/
// find PM100D
#define TLPM_FIND_PATTERN             "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x8070 || VI_ATTR_MODEL_CODE==0x8078)}"

// find PM100A
#define PM100A_FIND_PATTERN           "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x8071 || VI_ATTR_MODEL_CODE==0x8079)}"

// find PM100USB
#define PM100USB_FIND_PATTERN         "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && VI_ATTR_MODEL_CODE==0x8072}"

// find PM160 on USB interface
#define PM160USB_FIND_PATTERN         "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x8073 || VI_ATTR_MODEL_CODE==0x807B)}"

// find PM160T on USB interface
#define PM160TUSB_FIND_PATTERN        "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x8074 || VI_ATTR_MODEL_CODE==0x807C)}"

// find PM200
#define PM200_FIND_PATTERN            "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && VI_ATTR_MODEL_CODE==0x80B0}"

// find PM400
#define PM400_FIND_PATTERN            "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x8075 || VI_ATTR_MODEL_CODE==0x807D)}"

// find PM101
#define PM101_FIND_PATTERN            "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x8076 || VI_ATTR_MODEL_CODE==0x807E)}"

// find PM102
#define PM102_FIND_PATTERN            "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x8077 || VI_ATTR_MODEL_CODE==0x807F)}"

// find any PM100
#define PM100_FIND_PATTERN            "USB?*::0x1313::0x807?::?*::INSTR"

// find any PM100/PM160/PM200 with USB interface
#define PMxxx_FIND_PATTERN            "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x8070 || VI_ATTR_MODEL_CODE==0x8078 || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8071 || VI_ATTR_MODEL_CODE==0x8079 || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8072 || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8073 || VI_ATTR_MODEL_CODE==0x807B || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8074 || VI_ATTR_MODEL_CODE==0x807C || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8075 || VI_ATTR_MODEL_CODE==0x807D || " \
																			 "VI_ATTR_MODEL_CODE==0x8076 || VI_ATTR_MODEL_CODE==0x807E || " \
																			 "VI_ATTR_MODEL_CODE==0x8077 || VI_ATTR_MODEL_CODE==0x807F || " \
                                                                             "VI_ATTR_MODEL_CODE==0x80B0)}"

// find bluetooth devices 
#define PMBT_FIND_PATTERN             "ASRL?*::INSTR"

// find serial port devices 
#define PMUART_FIND_PATTERN           "ASRL?*::INSTR"

/*---------------------------------------------------------------------------
 Buffers
---------------------------------------------------------------------------*/
#define PM100D_BUFFER_SIZE            256      // General buffer size
#define PM100D_ERR_DESCR_BUFFER_SIZE  512      // Buffer size for error messages


/*---------------------------------------------------------------------------
 Error/Warning Codes
   Note: The instrument returns errors within the range -512 .. +1023. 
   The driver adds the value VI_INSTR_ERROR_OFFSET (0xBFFC0900). So the 
   driver returns instrumetn errors in the range 0xBFFC0700 .. 0xBFFC0CFF.
---------------------------------------------------------------------------*/
// Offsets
#undef VI_INSTR_WARNING_OFFSET
#undef VI_INSTR_ERROR_OFFSET

#define VI_INSTR_WARNING_OFFSET        (0x3FFC0900L)
#define VI_INSTR_ERROR_OFFSET          (_VI_ERROR + 0x3FFC0900L)   //0xBFFC0900

// Driver errors
#define VI_INSTR_ERROR_NOT_SUPP_INTF   (VI_INSTR_ERROR_OFFSET + 0x01L)   /* BFFC0901, -1074001663 */  

// Driver warnings
#undef VI_INSTR_WARN_OVERFLOW
#undef VI_INSTR_WARN_UNDERRUN
#undef VI_INSTR_WARN_NAN

#define VI_INSTR_WARN_OVERFLOW         (VI_INSTR_WARNING_OFFSET + 0x01L)   //0x3FFC0901
#define VI_INSTR_WARN_UNDERRUN         (VI_INSTR_WARNING_OFFSET + 0x02L)   //0x3FFC0902
#define VI_INSTR_WARN_NAN              (VI_INSTR_WARNING_OFFSET + 0x03L)   //0x3FFC0903


/*---------------------------------------------------------------------------
 Attributes
---------------------------------------------------------------------------*/
#define PM100D_ATTR_SET_VAL           (0)
#define PM100D_ATTR_MIN_VAL           (1)
#define PM100D_ATTR_MAX_VAL           (2)
#define PM100D_ATTR_DFLT_VAL          (3)

/*========================================================================*//**
\defgroup   TLPM_INDEX_x  Indices
\details	Index of one user power calibration (identified by the sensor serial number)
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define PM100D_INDEX_1 (1)
#define PM100D_INDEX_2 (2) 
#define PM100D_INDEX_3 (3) 
#define PM100D_INDEX_4 (4) 
#define PM100D_INDEX_5 (5) 
/**@}*/  /* TLPM_INDEX_x */    


/*===========================================================================

 GLOBAL USER-CALLABLE FUNCTION DECLARATIONS (Exportable Functions)

===========================================================================*/
/*===========================================================================

 Init/close

===========================================================================*/
/*---------------------------------------------------------------------------
 Initialize - This function initializes the instrument driver session and
 returns an instrument handle which is used in subsequent calls.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_init (ViRsrc resourceName, ViBoolean IDQuery, ViBoolean resetDevice, ViPSession instrumentHandle);

/*---------------------------------------------------------------------------
 Close an instrument driver session
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_close (ViSession instrumentHandle);

/*===========================================================================

 Resource Functions.

===========================================================================*/
ViStatus _VI_FUNC PM100D_findRsrc (ViSession instrumentHandle, ViUInt32 *resourceCount);
ViStatus _VI_FUNC PM100D_getRsrcName (ViSession instrumentHandle, ViUInt32 index, ViChar resourceName[]);
ViStatus _VI_FUNC PM100D_getRsrcInfo (ViSession instrumentHandle, ViUInt32 index, ViChar modelName[], ViChar serialNumber[], ViChar manufacturer[], ViBoolean *deviceAvailable);

/*===========================================================================

 Configuration Functions.

===========================================================================*/
/*===========================================================================
 Subclass: Configuration Functions - System
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get date and time
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setTime (ViSession instrumentHandle, ViInt16  year, ViInt16  month, ViInt16  day, ViInt16  hour, ViInt16 minute, ViInt16  second);
ViStatus _VI_FUNC PM100D_getTime (ViSession instrumentHandle, ViInt16 *year, ViPInt16 month, ViPInt16 day, ViPInt16 hour, ViPInt16 minute, ViPInt16 second);

/*---------------------------------------------------------------------------
 Set/get line frequency
---------------------------------------------------------------------------*/
#define PM100D_LINE_FREQ_50   (50) // line frequency in Hz
#define PM100D_LINE_FREQ_60   (60) // line frequency in Hz

ViStatus _VI_FUNC PM100D_setLineFrequency (ViSession instrumentHandle, ViInt16  lineFrequency);
ViStatus _VI_FUNC PM100D_getLineFrequency (ViSession instrumentHandle, ViPInt16 lineFrequency);

/*---------------------------------------------------------------------------
 Get battery voltage
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_getBatteryVoltage (ViSession instrumentHandle, ViPReal64 voltage);

/*===========================================================================
 Class: Configuration Functions - System - Instrument Registers
===========================================================================*/
/*---------------------------------------------------------------------------
 Write/read register contents
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_writeRegister (ViSession instrumentHandle, ViInt16 reg, ViInt16 value);
ViStatus _VI_FUNC PM100D_readRegister (ViSession instrumentHandle, ViInt16 reg, ViPInt16 value);
ViStatus _VI_FUNC PM100D_presetRegister (ViSession instrumentHandle);

#define PM100D_REG_STB                (0)   // Status Byte Register
#define PM100D_REG_SRE                (1)   // Service Request Enable
#define PM100D_REG_ESB                (2)   // Standard Event Status Register
#define PM100D_REG_ESE                (3)   // Standard Event Enable
#define PM100D_REG_OPER_COND          (4)   // Operation Condition Register
#define PM100D_REG_OPER_EVENT         (5)   // Operation Event Register
#define PM100D_REG_OPER_ENAB          (6)   // Operation Event Enable Register
#define PM100D_REG_OPER_PTR           (7)   // Operation Positive Transition Filter
#define PM100D_REG_OPER_NTR           (8)   // Operation Negative Transition Filter
#define PM100D_REG_QUES_COND          (9)   // Questionable Condition Register
#define PM100D_REG_QUES_EVENT         (10)  // Questionable Event Register
#define PM100D_REG_QUES_ENAB          (11)  // Questionable Event Enable Reg.
#define PM100D_REG_QUES_PTR           (12)  // Questionable Positive Transition Filter
#define PM100D_REG_QUES_NTR           (13)  // Questionable Negative Transition Filter
#define PM100D_REG_MEAS_COND          (14)  // Measurement Condition Register
#define PM100D_REG_MEAS_EVENT         (15)  // Measurement Event Register
#define PM100D_REG_MEAS_ENAB          (16)  // Measurement Event Enable Register
#define PM100D_REG_MEAS_PTR           (17)  // Measurement Positive Transition Filter
#define PM100D_REG_MEAS_NTR           (18)  // Measurement Negative Transition Filter
#define PM100D_REG_AUX_COND           (19)  // Auxiliary Condition Register
#define PM100D_REG_AUX_EVENT          (20)  // Auxiliary Event Register
#define PM100D_REG_AUX_ENAB           (21)  // Auxiliary Event Enable Register
#define PM100D_REG_AUX_PTR            (22)  // Auxiliary Positive Transition Filter
#define PM100D_REG_AUX_NTR            (23)  // Auxiliary Negative Transition Filter

// STATUS BYTE bit definitions (see IEEE488.2-1992 §11.2)
#define PM100D_STATBIT_STB_AUX        (0x01)   // Auxiliary summary
#define PM100D_STATBIT_STB_MEAS       (0x02)   // Device Measurement Summary
#define PM100D_STATBIT_STB_EAV        (0x04)   // Error available
#define PM100D_STATBIT_STB_QUES       (0x08)   // Questionable Status Summary
#define PM100D_STATBIT_STB_MAV        (0x10)   // Message available
#define PM100D_STATBIT_STB_ESB        (0x20)   // Event Status Bit
#define PM100D_STATBIT_STB_MSS        (0x40)   // Master summary status
#define PM100D_STATBIT_STB_OPER       (0x80)   // Operation Status Summary

// STANDARD EVENT STATUS REGISTER bit definitions (see IEEE488.2-1992 §11.5.1)
#define PM100D_STATBIT_ESR_OPC        (0x01)   // Operation complete
#define PM100D_STATBIT_ESR_RQC        (0x02)   // Request control
#define PM100D_STATBIT_ESR_QYE        (0x04)   // Query error
#define PM100D_STATBIT_ESR_DDE        (0x08)   // Device-Specific error
#define PM100D_STATBIT_ESR_EXE        (0x10)   // Execution error
#define PM100D_STATBIT_ESR_CME        (0x20)   // Command error
#define PM100D_STATBIT_ESR_URQ        (0x40)   // User request
#define PM100D_STATBIT_ESR_PON        (0x80)   // Power on
		
// QUESTIONABLE STATUS REGISTER bit definitions (see SCPI 99.0 §9)
#define PM100D_STATBIT_QUES_VOLT      (0x0001) // questionable voltage measurement
#define PM100D_STATBIT_QUES_CURR      (0x0002) // questionable current measurement
#define PM100D_STATBIT_QUES_TIME      (0x0004) // questionable time measurement
#define PM100D_STATBIT_QUES_POW       (0x0008) // questionable power measurement
#define PM100D_STATBIT_QUES_TEMP      (0x0010) // questionable temperature measurement
#define PM100D_STATBIT_QUES_FREQ      (0x0020) // questionable frequency measurement
#define PM100D_STATBIT_QUES_PHAS      (0x0040) // questionable phase measurement
#define PM100D_STATBIT_QUES_MOD       (0x0080) // questionable modulation measurement
#define PM100D_STATBIT_QUES_CAL       (0x0100) // questionable calibration
#define PM100D_STATBIT_QUES_ENER      (0x0200) // questionable energy measurement
#define PM100D_STATBIT_QUES_10        (0x0400) // reserved
#define PM100D_STATBIT_QUES_11        (0x0800) // reserved
#define PM100D_STATBIT_QUES_12        (0x1000) // reserved
#define PM100D_STATBIT_QUES_INST      (0x2000) // instrument summary
#define PM100D_STATBIT_QUES_WARN      (0x4000) // command warning
#define PM100D_STATBIT_QUES_15        (0x8000) // reserved

// OPERATION STATUS REGISTER bit definitions (see SCPI 99.0 §9)
#define PM100D_STATBIT_OPER_CAL       (0x0001) // The instrument is currently performing a calibration.
#define PM100D_STATBIT_OPER_SETT      (0x0002) // The instrument is waiting for signals it controls to stabilize enough to begin measurements.
#define PM100D_STATBIT_OPER_RANG      (0x0004) // The instrument is currently changing its range.
#define PM100D_STATBIT_OPER_SWE       (0x0008) // A sweep is in progress.
#define PM100D_STATBIT_OPER_MEAS      (0x0010) // The instrument is actively measuring.
#define PM100D_STATBIT_OPER_TRIG      (0x0020) // The instrument is in a “wait for trigger” state of the trigger model.
#define PM100D_STATBIT_OPER_ARM       (0x0040) // The instrument is in a “wait for arm” state of the trigger model.
#define PM100D_STATBIT_OPER_CORR      (0x0080) // The instrument is currently performing a correction (Auto-PID tune).
#define PM100D_STATBIT_OPER_SENS      (0x0100) // Optical powermeter sensor connected and operable.
#define PM100D_STATBIT_OPER_DATA      (0x0200) // Measurement data ready for fetch.
#define PM100D_STATBIT_OPER_THAC      (0x0400) // Thermopile accelerator active.
#define PM100D_STATBIT_OPER_11        (0x0800) // reserved
#define PM100D_STATBIT_OPER_12        (0x1000) // reserved
#define PM100D_STATBIT_OPER_INST      (0x2000) // One of n multiple logical instruments is reporting OPERational status.
#define PM100D_STATBIT_OPER_PROG      (0x4000) // A user-defined programming is currently in the run state.
#define PM100D_STATBIT_OPER_15        (0x8000) // reserved

// Thorlabs defined MEASRUEMENT STATUS REGISTER bit definitions
#define PM100D_STATBIT_MEAS_0         (0x0001) // reserved
#define PM100D_STATBIT_MEAS_1         (0x0002) // reserved
#define PM100D_STATBIT_MEAS_2         (0x0004) // reserved
#define PM100D_STATBIT_MEAS_3         (0x0008) // reserved
#define PM100D_STATBIT_MEAS_4         (0x0010) // reserved
#define PM100D_STATBIT_MEAS_5         (0x0020) // reserved
#define PM100D_STATBIT_MEAS_6         (0x0040) // reserved
#define PM100D_STATBIT_MEAS_7         (0x0080) // reserved
#define PM100D_STATBIT_MEAS_8         (0x0100) // reserved
#define PM100D_STATBIT_MEAS_9         (0x0200) // reserved
#define PM100D_STATBIT_MEAS_10        (0x0400) // reserved
#define PM100D_STATBIT_MEAS_11        (0x0800) // reserved
#define PM100D_STATBIT_MEAS_12        (0x1000) // reserved
#define PM100D_STATBIT_MEAS_13        (0x2000) // reserved
#define PM100D_STATBIT_MEAS_14        (0x4000) // reserved
#define PM100D_STATBIT_MEAS_15        (0x8000) // reserved

// Thorlabs defined Auxiliary STATUS REGISTER bit definitions
#define PM100D_STATBIT_AUX_NTC        (0x0001) // Auxiliary NTC temperature sensor connected.
#define PM100D_STATBIT_AUX_EMM        (0x0002) // External measurement module connected.
#define PM100D_STATBIT_AUX_2          (0x0004) // reserved
#define PM100D_STATBIT_AUX_3          (0x0008) // reserved
#define PM100D_STATBIT_AUX_EXPS       (0x0010) // External power supply connected
#define PM100D_STATBIT_AUX_BATC       (0x0020) // Battery charging
#define PM100D_STATBIT_AUX_BATL       (0x0040) // Battery low
#define PM100D_STATBIT_AUX_IPS        (0x0080) // Apple(tm) authentification supported. True if an authentification co-processor is installed.
#define PM100D_STATBIT_AUX_IPF        (0x0100) // Apple(tm) authentification failed. True if the authentification setup procedure failed.
#define PM100D_STATBIT_AUX_9          (0x0200) // reserved
#define PM100D_STATBIT_AUX_10         (0x0400) // reserved
#define PM100D_STATBIT_AUX_11         (0x0800) // reserved
#define PM100D_STATBIT_AUX_12         (0x1000) // reserved
#define PM100D_STATBIT_AUX_13         (0x2000) // reserved
#define PM100D_STATBIT_AUX_14         (0x4000) // reserved
#define PM100D_STATBIT_AUX_15         (0x8000) // reserved

/*===========================================================================
 Subclass: Configuration Functions - Display
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get display brightness
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setDispBrightness (ViSession instrumentHandle, ViReal64 val);
ViStatus _VI_FUNC PM100D_getDispBrightness (ViSession instrumentHandle, ViPReal64 pVal);

/*---------------------------------------------------------------------------
 Set/get display contrast
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setDispContrast (ViSession instrumentHandle, ViReal64 val);
ViStatus _VI_FUNC PM100D_getDispContrast (ViSession instrumentHandle, ViPReal64 pVal);


/*===========================================================================
 Subclass: Configuration Functions - Calibration message
===========================================================================*/
/*---------------------------------------------------------------------------
 Get calibration message
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_getCalibrationMsg (ViSession instrumentHandle, ViChar _VI_FAR message[]);

/*===========================================================================
 Subclass: Configuration Functions - Sense - Average
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get average count
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setAvgTime (ViSession instrumentHandle, ViReal64 avgTime);
ViStatus _VI_FUNC PM100D_getAvgTime (ViSession instrumentHandle, ViInt16 attribute, ViReal64 *avgTime);

/*---------------------------------------------------------------------------
 Set/get average count
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setAvgCnt (ViSession instrumentHandle, ViInt16 averageCount);
ViStatus _VI_FUNC PM100D_getAvgCnt (ViSession instrumentHandle, ViPInt16 averageCount);

/*===========================================================================
 Subclass: Configuration Functions - Sense - Correction
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get attenuation
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setAttenuation (ViSession instrumentHandle, ViReal64 attenuation);
ViStatus _VI_FUNC PM100D_getAttenuation (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 attenuation);

/*---------------------------------------------------------------------------
 Dark current adjustment
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_startDarkAdjust (ViSession instrumentHandle);
ViStatus _VI_FUNC PM100D_cancelDarkAdjust (ViSession instrumentHandle);
ViStatus _VI_FUNC PM100D_getDarkAdjustState (ViSession instrumentHandle, ViPInt16 state);
ViStatus _VI_FUNC PM100D_getDarkOffset (ViSession instrumentHandle, ViPReal64 darkOffset);

#define PM100D_STAT_DARK_ADJUST_FINISHED  (0)
#define PM100D_STAT_DARK_ADJUST_RUNNING   (1)

/*---------------------------------------------------------------------------
 Set/get beam diameter
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setBeamDia (ViSession instrumentHandle, ViReal64 beamDiameter);
ViStatus _VI_FUNC PM100D_getBeamDia (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 beamDiameter);

/*---------------------------------------------------------------------------
 Set/get wavelength
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setWavelength (ViSession instrumentHandle, ViReal64 wavelength);
ViStatus _VI_FUNC PM100D_getWavelength (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 wavelength);

/*---------------------------------------------------------------------------
 Set/get photodiode responsivity
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setPhotodiodeResponsivity (ViSession instrumentHandle, ViReal64 response);
ViStatus _VI_FUNC PM100D_getPhotodiodeResponsivity (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 responsivity);

/*---------------------------------------------------------------------------
 Set/get thermopile responsivity
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setThermopileResponsivity (ViSession instrumentHandle, ViReal64 response);
ViStatus _VI_FUNC PM100D_getThermopileResponsivity (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 responsivity);

/*---------------------------------------------------------------------------
 Set/get pyrosensor responsivity
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setPyrosensorResponsivity (ViSession instrumentHandle, ViReal64 response);
ViStatus _VI_FUNC PM100D_getPyrosensorResponsivity (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 responsivity);

/*===========================================================================
 Subclass: Configuration Functions - Sense - Current
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get current range auto
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setCurrentAutoRange (ViSession instrumentHandle, ViBoolean currentAutorangeMode);
ViStatus _VI_FUNC PM100D_getCurrentAutorange (ViSession instrumentHandle, ViPBoolean currentAutorangeMode);

#define PM100D_AUTORANGE_CURRENT_OFF  (0)
#define PM100D_AUTORANGE_CURRENT_ON   (1)

/*---------------------------------------------------------------------------
 Set/get current range
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setCurrentRange (ViSession instrumentHandle, ViReal64 current_to_Measure);
ViStatus _VI_FUNC PM100D_getCurrentRange (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 currentValue);

/*---------------------------------------------------------------------------
 Set/get current reference value
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setCurrentRef (ViSession instrumentHandle, ViReal64 currentReferenceValue);
ViStatus _VI_FUNC PM100D_getCurrentRef (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 currentReferenceValue);

/*---------------------------------------------------------------------------
 Set/get current reference state
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setCurrentRefState (ViSession instrumentHandle, ViBoolean currentReferenceState);
ViStatus _VI_FUNC PM100D_getCurrentRefState (ViSession instrumentHandle, ViPBoolean currentReferenceState);

#define PM100D_CURRENT_REF_OFF  (0)
#define PM100D_CURRENT_REF_ON   (1)

/*===========================================================================
 Subclass: Configuration Functions - Sense - Energy
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get energy range
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setEnergyRange (ViSession instrumentHandle, ViReal64 energyToMeasure);
ViStatus _VI_FUNC PM100D_getEnergyRange (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 energyValue);

/*---------------------------------------------------------------------------
 Set/get energy reference value
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setEnergyRef (ViSession instrumentHandle, ViReal64 energyReferenceValue);
ViStatus _VI_FUNC PM100D_getEnergyRef (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 energyReferenceValue);

/*---------------------------------------------------------------------------
 Set/get energy reference state
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setEnergyRefState (ViSession instrumentHandle, ViBoolean energyReferenceState);
ViStatus _VI_FUNC PM100D_getEnergyRefState (ViSession instrumentHandle, ViPBoolean energyReferenceState);

#define PM100D_ENERGY_REF_OFF (0)
#define PM100D_ENERGY_REF_ON  (1)

/*===========================================================================
 Subclass: Configuration Functions - Sense - Frequency
===========================================================================*/
/*---------------------------------------------------------------------------
 Get frequency range
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_getFreqRange (ViSession instrumentHandle, ViPReal64 lowerFrequency, ViPReal64 upperFrequency);

/*===========================================================================
 Subclass: Configuration Functions - Sense - Power
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get power range auto
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setPowerAutoRange (ViSession instrumentHandle, ViBoolean powerAutorangeMode);
ViStatus _VI_FUNC PM100D_getPowerAutorange (ViSession instrumentHandle, ViPBoolean powerAutorangeMode);

#define PM100D_AUTORANGE_POWER_OFF  (0)
#define PM100D_AUTORANGE_POWER_ON   (1)

/*---------------------------------------------------------------------------
 Set/get power range
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setPowerRange (ViSession instrumentHandle, ViReal64 power_to_Measure);
ViStatus _VI_FUNC PM100D_getPowerRange (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 powerValue);

/*---------------------------------------------------------------------------
 Set/get power reference value
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setPowerRef (ViSession instrumentHandle, ViReal64 powerReferenceValue);
ViStatus _VI_FUNC PM100D_getPowerRef (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 powerReferenceValue);

/*---------------------------------------------------------------------------
 Set/get power reference state
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setPowerRefState (ViSession instrumentHandle, ViBoolean powerReferenceState);
ViStatus _VI_FUNC PM100D_getPowerRefState (ViSession instrumentHandle, ViPBoolean powerReferenceState);

#define PM100D_POWER_REF_OFF  (0)
#define PM100D_POWER_REF_ON   (1)

/*---------------------------------------------------------------------------
 Set/get power unit
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setPowerUnit (ViSession instrumentHandle, ViInt16 powerUnit);
ViStatus _VI_FUNC PM100D_getPowerUnit (ViSession instrumentHandle, ViPInt16 powerUnit);

#define PM100D_POWER_UNIT_WATT   (0)
#define PM100D_POWER_UNIT_DBM    (1)


/*===========================================================================
 Subclass: Configuration Functions - Sense - Voltage
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get voltage range auto
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setVoltageAutoRange (ViSession instrumentHandle, ViBoolean voltageAutorangeMode);
ViStatus _VI_FUNC PM100D_getVoltageAutorange (ViSession instrumentHandle, ViPBoolean voltageAutorangeMode);

#define PM100D_AUTORANGE_VOLTAGE_OFF  (0)
#define PM100D_AUTORANGE_VOLTAGE_ON   (1)

/*---------------------------------------------------------------------------
 Set/get voltage range
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setVoltageRange (ViSession instrumentHandle, ViReal64 voltage_to_Measure);
ViStatus _VI_FUNC PM100D_getVoltageRange (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 voltageValue);

/*---------------------------------------------------------------------------
 Set/get voltage reference value
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setVoltageRef (ViSession instrumentHandle, ViReal64 voltageReferenceValue);
ViStatus _VI_FUNC PM100D_getVoltageRef (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 voltageReferenceValue);

/*---------------------------------------------------------------------------
 Set/get voltage reference state
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setVoltageRefState (ViSession instrumentHandle, ViBoolean voltageReferenceState);
ViStatus _VI_FUNC PM100D_getVoltageRefState (ViSession instrumentHandle, ViPBoolean voltageReferenceState);

#define PM100D_VOLTAGE_REF_OFF  (0)
#define PM100D_VOLTAGE_REF_ON   (1)


/*===========================================================================
 Subclass: Configuration Functions - Sense - Peak
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get peak threshold
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setPeakThreshold (ViSession instrumentHandle, ViReal64 peakThreshold);
ViStatus _VI_FUNC PM100D_getPeakThreshold (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 peakThreshold);

/*===========================================================================
 Subclass: Configuration Functions - Sense - External NTC
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get NTC coefficients
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setExtNtcParameter (ViSession instrumentHandle, ViReal64 r0Coefficient, ViReal64 betaCoefficient);
ViStatus _VI_FUNC PM100D_getExtNtcParameter (ViSession instrumentHandle, ViInt16 attribute, ViReal64 *r0Coefficient, ViReal64 *betaCoefficient);

/*===========================================================================
 Subclass: Configuration Functions - Input
===========================================================================*/
/*===========================================================================
 Subclass: Configuration Functions - Input - Photodiode
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get photodiode input filter state
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setInputFilterState (ViSession instrumentHandle, ViBoolean inputFilterState);
ViStatus _VI_FUNC PM100D_getInputFilterState (ViSession instrumentHandle, ViPBoolean inputFilterState);

#define PM100D_INPUT_FILTER_STATE_OFF  (0)
#define PM100D_INPUT_FILTER_STATE_ON   (1)

/*===========================================================================
 Subclass: Configuration Functions - Input - Thermopile
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get thermopile accelerator state
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setAccelState (ViSession instrumentHandle, ViBoolean accelState);
ViStatus _VI_FUNC PM100D_getAccelState (ViSession instrumentHandle, ViPBoolean accelState);

#define PM100D_ACCELERATION_STATE_OFF  (0)
#define PM100D_ACCELERATION_STATE_ON   (1)

/*---------------------------------------------------------------------------
 Set/get thermopile accelerator mode
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setAccelMode (ViSession instrumentHandle, ViBoolean accelMode);
ViStatus _VI_FUNC PM100D_getAccelMode (ViSession instrumentHandle, ViPBoolean accelMode);

#define PM100D_ACCELERATION_MANUAL     (0)
#define PM100D_ACCELERATION_AUTO       (1)

/*---------------------------------------------------------------------------
 Set/get thermopile acceleration tau (time constant)
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setAccelTau (ViSession instrumentHandle, ViReal64 accelTau);
ViStatus _VI_FUNC PM100D_getAccelTau (ViSession instrumentHandle, ViInt16 attribute, ViPReal64 accelTau);

/*===========================================================================
 Subclass: Configuration Functions - Input - Custom Sensor
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get custom sensor input adapter type
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setInputAdapterType (ViSession instrumentHandle, ViInt16 type);
ViStatus _VI_FUNC PM100D_getInputAdapterType (ViSession instrumentHandle, ViPInt16 type);


/*===========================================================================

 Data Functions.

===========================================================================*/
/*---------------------------------------------------------------------------
 Measure current
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_measCurrent (ViSession instrumentHandle, ViPReal64 current);

/*---------------------------------------------------------------------------
 Measure voltage
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_measVoltage (ViSession instrumentHandle, ViPReal64 voltage);

/*---------------------------------------------------------------------------
 Measure power
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_measPower (ViSession instrumentHandle, ViPReal64 power);

/*---------------------------------------------------------------------------
 Measure energy
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_measEnergy (ViSession instrumentHandle, ViPReal64 energy);

/*---------------------------------------------------------------------------
 Measure frequency
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_measFreq (ViSession instrumentHandle, ViPReal64 frequency);

/*---------------------------------------------------------------------------
 Measure sensor temperature
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_measSensTemperature (ViSession instrumentHandle, ViPReal64 temperature);

/*---------------------------------------------------------------------------
 Measure power density
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_measPowerDens (ViSession instrumentHandle, ViPReal64 powerDensity);

/*---------------------------------------------------------------------------
 Measure energy density
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_measEnergyDens (ViSession instrumentHandle, ViPReal64 energyDensity);

/*---------------------------------------------------------------------------
 Measure auxiliary voltages
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_measAuxAD0 (ViSession instrumentHandle, ViPReal64 voltage);
ViStatus _VI_FUNC PM100D_measAuxAD1 (ViSession instrumentHandle, ViPReal64 voltage);

/*---------------------------------------------------------------------------
 Measure Environment Monitor values
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_measEmmHumidity (ViSession instrumentHandle, ViPReal64 humidity);
ViStatus _VI_FUNC PM100D_measEmmTemperature (ViSession instrumentHandle, ViPReal64 temperature);

/*---------------------------------------------------------------------------
 Measure External NTX values
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_measExtNtcTemperature (ViSession instrumentHandle, ViReal64 *temperature);
ViStatus _VI_FUNC PM100D_measExtNtcResistance (ViSession instrumentHandle, ViReal64 *resistance);

/*===========================================================================

 Sensor Information.

 ===========================================================================*/
/*---------------------------------------------------------------------------
 Get sensor information
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_getSensorInfo (ViSession instr, ViChar _VI_FAR name[], ViChar _VI_FAR snr[], ViChar _VI_FAR message[], ViPInt16 pType, ViPInt16 pStype, ViPInt16 pFlags);

// Sensor types
#define SENSOR_TYPE_NONE               0x0   // No sensor. This value is used to mark sensor data for 'no sensor connected'.
#define SENSOR_TYPE_PD_SINGLE          0x1   // Single photodiode sensor. Only one ipd input active at the same time.
#define SENSOR_TYPE_THERMO             0x2   // Thermopile sensor
#define SENSOR_TYPE_PYRO               0x3   // Pyroelectric sensor
#define SENSOR_TYPE_4Q				   0x4	 // 4Q Sensor

// Sensor subtypes
#define SENSOR_SUBTYPE_NONE            0x0   // No sensor. This value is used to mark RAM data structure for 'no sensor connected'. Do not write this value to the EEPROM.

   // Sensor subtypes of single photodiode sensors
#define SENSOR_SUBTYPE_PD_ADAPTER      0x01  // Photodiode adapter (no temperature sensor)
#define SENSOR_SUBTYPE_PD_SINGLE_STD   0x02  // Standard single photodiode sensor (no temperature sensor)
#define SENSOR_SUBTYPE_PD_SINGLE_FSR   0x03  // One single photodiode. Filter position set by a slide on the sensor selects responsivity data set to use. (no temperature sensor)
#define SENSOR_SUBTYPE_PD_SINGLE_STD_T 0x12  // Standard single photodiode sensor (with temperature sensor)

   // Sensor subtypes of thermopile sensors
#define SENSOR_SUBTYPE_THERMO_ADAPTER  0x01  // Thermopile adapter (no temperature sensor)
#define SENSOR_SUBTYPE_THERMO_STD      0x02  // Standard thermopile sensor (no temperature sensor)
#define SENSOR_SUBTYPE_THERMO_STD_T    0x12  // Standard thermopile sensor (with temperature sensor)

   // Sensor subtypes of pyroelectric sensors
#define SENSOR_SUBTYPE_PYRO_ADAPTER    0x01  // Pyroelectric adapter (no temperature sensor)
#define SENSOR_SUBTYPE_PYRO_STD        0x02  // Standard pyroelectric sensor (no temperature sensor)
#define SENSOR_SUBTYPE_PYRO_STD_T      0x12  // Standard pyroelectric sensor (with temperature sensor)

#define PM100D_SENS_FLAG_IS_POWER      0x0001 // Power sensor
#define PM100D_SENS_FLAG_IS_ENERGY     0x0002 // Energy sensor
#define PM100D_SENS_FLAG_IS_RESP_SET   0x0010 // Responsivity settable
#define PM100D_SENS_FLAG_IS_WAVEL_SET  0x0020 // Wavelength settable
#define PM100D_SENS_FLAG_IS_TAU_SET    0x0040 // Time constant tau settable
#define PM100D_SENS_FLAG_HAS_TEMP      0x0100 // Temperature sensor included


/*===========================================================================

 Utility Functions.

===========================================================================*/
/*---------------------------------------------------------------------------
 Identification query
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_identificationQuery (ViSession instrumentHandle, ViChar _VI_FAR manufacturerName[], ViChar _VI_FAR deviceName[], ViChar _VI_FAR serialNumber[], ViChar _VI_FAR firmwareRevision[]);

/*---------------------------------------------------------------------------
 Reset the instrument.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_reset (ViSession instrumentHandle);

/*---------------------------------------------------------------------------
 Run Self-Test routine.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_selfTest (ViSession instrumentHandle, ViPInt16 selfTestResult, ViChar _VI_FAR description[]);

/*---------------------------------------------------------------------------
 Switch error query mode 
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_errorQueryMode (ViSession instrumentHandle, ViBoolean mode);

/*---------------------------------------------------------------------------
 Error Query
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_errorQuery (ViSession instrumentHandle, ViPInt32 errorNumber, ViChar _VI_FAR errorMessage[]);

/*---------------------------------------------------------------------------
 Get error description. 
 This function translates the error return value from the instrument driver
 into a user-readable string.
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_errorMessage (ViSession instrumentHandle, ViStatus statusCode, ViChar _VI_FAR description[]);

/*---------------------------------------------------------------------------
 Revision Query
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_revisionQuery (ViSession instrumentHandle, ViChar _VI_FAR instrumentDriverRevision[], ViChar _VI_FAR firmwareRevision[]);

/*---------------------------------------------------------------------------
 Communication Timeout Value
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setTimeoutValue (ViSession instrumentHandle, ViUInt32 value);
ViStatus _VI_FUNC PM100D_getTimeoutValue (ViSession instrumentHandle, ViUInt32 *value);

/*===========================================================================
 Class: Utility-Digital I/O
===========================================================================*/
/*---------------------------------------------------------------------------
 Set/get digital I/O direction
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setDigIoDirection (ViSession instrumentHandle, ViBoolean IO0, ViBoolean IO1, ViBoolean IO2, ViBoolean IO3);
ViStatus _VI_FUNC PM100D_getDigIoDirection (ViSession instrumentHandle, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);

#define PM100D_IODIR_IN    (VI_OFF)
#define PM100D_IODIR_OUT   (VI_ON)

/*---------------------------------------------------------------------------
 Set/get digital I/O output data
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_setDigIoOutput (ViSession instrumentHandle, ViBoolean IO0, ViBoolean IO1, ViBoolean IO2, ViBoolean IO3);
ViStatus _VI_FUNC PM100D_getDigIoOutput (ViSession instrumentHandle, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);

#define PM100D_IOLVL_LOW   (VI_OFF)
#define PM100D_IOLVL_HIGH  (VI_ON)

/*---------------------------------------------------------------------------
 Get digital I/O port data
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_getDigIoPort (ViSession instrumentHandle, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);


/*===========================================================================
 Class: Utility-Raw Instrument I/O
===========================================================================*/
/*---------------------------------------------------------------------------
 Write to Instrument
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_writeRaw (ViSession instrumentHandle, ViString command);

/*---------------------------------------------------------------------------
 Read from Instrument
---------------------------------------------------------------------------*/
ViStatus _VI_FUNC PM100D_readRaw (ViSession instrumentHandle, ViChar _VI_FAR buffer[], ViUInt32 size, ViPUInt32 returnCount);


#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif

#endif   /* _PM100D_DRIVER_HEADER_ */

/****************************************************************************

  End of Header file

****************************************************************************/
