/*========================================================================*//**

	\file		TLPM.h
	\brief		Thorlabs PM100x Series VISA instrument driver
	\details	This driver supports PM100A, PM100D, PM100USB, PM101, PM102, PM103, PM160, PM160T, PM200 and 
	PM400 optical power meters.

	FOR DETAILED DESCRIPTION OF THE DRIVER FUNCTIONS SEE THE ONLINE HELP FILE
	AND THE PROGRAMMERS REFERENCE MANUAL.

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

	\date          Oct-10-2018
	\copyright     copyright(c) 2017-2018 Thorlabs GmbH

	Changelog:     see 'readme.rtf'

*//*=========================================================================*/
#ifndef _TLPM_DRIVER_HEADER_
#define _TLPM_DRIVER_HEADER_

#include <vpptype.h>

#if defined(__cplusplus) || defined(__cplusplus__)
extern "C"
{
#endif

#if defined(_WIN64)
	#define CALLCONV            __fastcall
#elif (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)) && !defined(_NI_mswin16_)
	#define CALLCONV            __stdcall
#endif

#ifdef IS_DLL_TARGET
	#undef _VI_FUNC
	#define _VI_FUNC __declspec(dllexport) CALLCONV
#elif defined BUILDING_DEBUG_EXE
	#undef _VI_FUNC
	#define _VI_FUNC
#else
	#undef _VI_FUNC
	#define _VI_FUNC __declspec(dllimport) CALLCONV
#endif	  

/*========================================================================*//**
\defgroup   TLPM_VID_x TLPM_PID_x  USB instrument identification  
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define TLPM_VID_THORLABS            (0x1313)   // Thorlabs
#define TLPM_PID_TLPM_DFU            (0x8070)   // PM100D with DFU interface enabled
#define TLPM_PID_PM100A_DFU          (0x8071)   // PM100A with DFU interface enabled
#define TLPM_PID_PM100USB            (0x8072)   // PM100USB with DFU interface enabled
#define TLPM_PID_PM160USB_DFU        (0x8073)   // PM160 on USB with DFU interface enabled
#define TLPM_PID_PM160TUSB_DFU       (0x8074)   // PM160T on USB with DFU interface enabled
#define TLPM_PID_PM400_DFU           (0x8075)   // PM400 on USB with DFU interface enabled
#define TLPM_PID_PM101_DFU           (0x8076)   // PM101 on USB with DFU interface enabled (Interface 0 TMC, Interface 1 DFU)
#define TLPM_PID_PM102_DFU           (0x8077)   // PM102 on USB with DFU interface enabled (Interface 0 TMC, Interface 1 DFU)
#define TLPM_PID_PM103_DFU           (0x807A)   // PM103 on USB with DFU interface enabled (Interface 0 TMC, Interface 1 DFU)

#define TLPM_PID_PM100D              (0x8078)   // PM100D w/o DFU interface
#define TLPM_PID_PM100A              (0x8079)   // PM100A w/o DFU interface
#define TLPM_PID_PM160USB            (0x807B)   // PM160 on USB w/o DFU interface
#define TLPM_PID_PM160TUSB           (0x807C)   // PM160T on USB w/o DFU interface
#define TLPM_PID_PM400               (0x807D)   // PM400 on USB w/o DFU interface
#define TLPM_PID_PM101               (0x807E)   // reserved
#define TLPM_PID_PMTest              (0x807F)   // PM Test Platform

#define TLPM_PID_PM200               (0x80B0)   // PM200 
#define TLPM_PID_PM5020              (0x80BB)   // PM5020 1 channel benchtop powermeter (Interface 0 TMC, Interface 1 DFU)
/**@}*/  /* TLPM_PID_x */

/*========================================================================*//**
\defgroup   TLPMxxx_FIND_PATTERN  Find pattern for 'viFindRsrc()' 
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
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
#define PM101_FIND_PATTERN            "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x8076)}"

// find PM102
#define PM102_FIND_PATTERN            "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x8077)}"

// find PM103
#define PM103_FIND_PATTERN            "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && VI_ATTR_MODEL_CODE==0x807A}"

// find PMTest
#define PMTest_FIND_PATTERN           "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && VI_ATTR_MODEL_CODE==0x807F}"

// find any PM100
#define PM100_FIND_PATTERN            "USB?*::0x1313::0x807?::?*::INSTR"

// find PM5020
#define PM5020_FIND_PATTERN           "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && VI_ATTR_MODEL_CODE==0x80BB}"

// find any PM100/PM160/PM200 with USB interface
#define PMxxx_FIND_PATTERN            "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x8070 || VI_ATTR_MODEL_CODE==0x8078 || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8071 || VI_ATTR_MODEL_CODE==0x8079 || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8072 || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8073 || VI_ATTR_MODEL_CODE==0x807B || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8074 || VI_ATTR_MODEL_CODE==0x807C || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8075 || VI_ATTR_MODEL_CODE==0x807D || " \
																			 "VI_ATTR_MODEL_CODE==0x8076 || VI_ATTR_MODEL_CODE==0x807E || " \
																			 "VI_ATTR_MODEL_CODE==0x8077 || VI_ATTR_MODEL_CODE==0x807F || " \
																			 "VI_ATTR_MODEL_CODE==0x807A || VI_ATTR_MODEL_CODE==0x80BB ||" \
                                                                             "VI_ATTR_MODEL_CODE==0x80B0)}"

// find bluetooth devices 
#define PMBT_FIND_PATTERN			"ASRL?*::INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x807C || VI_ATTR_MODEL_CODE==0x807B)}"

// find serial port devices 
#define PMUART_FIND_PATTERN_VISA	"ASRL?*::INSTR"
#define PMUART_FIND_PATTERN_COM		"COM?*"  
/**@}*/  /* TLPMxxx_FIND_PATTERN */

/*========================================================================*//**
\defgroup   TLPM_x_BUFFER_x  Buffers
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define TLPM_BUFFER_SIZE            256      // General buffer size
#define TLPM_ERR_DESCR_BUFFER_SIZE  512      // Buffer size for error messages
/**@}*/  /* TLPM_x_BUFFER_x */

/*========================================================================*//**
\defgroup   TLPM_ERROR_CODES_x  Error codes for TLVISA functions
\details 	Note: The instrument returns errors within the range -512 .. +1023. 
   The driver adds the value VI_INSTR_ERROR_OFFSET (0xBFFC0900). So the 
   driver returns instrumetn errors in the range 0xBFFC0700 .. 0xBFFC0CFF.
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
// Offsets
#undef VI_INSTR_WARNING_OFFSET
#undef VI_INSTR_ERROR_OFFSET

#define VI_INSTR_WARNING_OFFSET        (0x3FFC0900L)
#define VI_INSTR_ERROR_OFFSET          (_VI_ERROR + 0x3FFC0900L)   /* BFFF0900, -1073805056 */

// Driver errors
#define VI_INSTR_ERROR_NOT_SUPP_INTF   (VI_INSTR_ERROR_OFFSET + 0x01L)   /* BFFC0901, -1074001663 */  

// Driver warnings
#undef VI_INSTR_WARN_OVERFLOW
#undef VI_INSTR_WARN_UNDERRUN
#undef VI_INSTR_WARN_NAN

#define VI_INSTR_WARN_OVERFLOW         (VI_INSTR_WARNING_OFFSET + 0x01L)   /* 3FFC0901, 1073481985 */
#define VI_INSTR_WARN_UNDERRUN         (VI_INSTR_WARNING_OFFSET + 0x02L)   /* 3FFC0902, 1073481986 */
#define VI_INSTR_WARN_NAN              (VI_INSTR_WARNING_OFFSET + 0x03L)   /* 3FFC0903, 1073481987 */
/**@}*/  /* TLPM_ERROR_CODES_x */

/*========================================================================*//**
\defgroup   TLPM_ATTR_x  Attributes
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define TLPM_ATTR_SET_VAL           (0)
#define TLPM_ATTR_MIN_VAL           (1)
#define TLPM_ATTR_MAX_VAL           (2)
#define TLPM_ATTR_DFLT_VAL          (3)
#define TLPM_ATTR_AUTO_VAL          (9)  
/**@}*/  /* TLPM_ATTR_x */  

/*========================================================================*//**
\defgroup   TLPM_CHANNEL_x  Attributes
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define TLPM_DEFAULT_CHANNEL   (1)
#define TLPM_SENSOR_CHANNEL1   (1)
#define TLPM_SENSOR_CHANNEL2   (2)
/**@}*/  /* TLPM_CHANNEL_x */  

/*========================================================================*//**
\defgroup   TLPM_INDEX_x  Indices
\details	Index of one user power calibration (identified by the sensor serial number)
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define TLPM_INDEX_1 (1)
#define TLPM_INDEX_2 (2) 
#define TLPM_INDEX_3 (3) 
#define TLPM_INDEX_4 (4) 
#define TLPM_INDEX_5 (5) 
/**@}*/  /* TLPM_INDEX_x */

/*========================================================================*//**
\defgroup   TLPM_PEAK_FILTER_x  Indices
\details	Index is used to set the peak filter for the signal incoming (PM103)
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define TLPM_PEAK_FILTER_NONE (0)
#define TLPM_PEAK_FILTER_OVER (1)
/**@}*/  /* TLPM_PEAK_FILTER_x */

/*========================================================================*//**
\defgroup   TLPM_METHODS_x Functions
\ingroup    TLPM_x
\brief      Functions provided by TLVISA library, e.g. communicating with devices.
@{
*//*=========================================================================*/   
ViStatus _VI_FUNC TLPMX_init (ViRsrc resourceName, ViBoolean IDQuery, ViBoolean resetDevice, ViPSession vi); 
ViStatus _VI_FUNC TLPMX_close (ViSession vi);   

/*========================================================================*//**
\defgroup   TLPM_METHODS_RM_x Resource Manager TLVISA library functions
\ingroup    TLPM_METHODS_x
\brief      Functions provided by TLVISA library for managing resources, e.g. finding resources.
@{
*//*=========================================================================*/
ViStatus _VI_FUNC TLPMX_findRsrc (ViSession vi, ViPUInt32 resourceCount);
ViStatus _VI_FUNC TLPMX_getRsrcName (ViSession vi, ViUInt32 index, ViChar resourceName[]);
ViStatus _VI_FUNC TLPMX_getRsrcInfo (ViSession vi, ViUInt32 index, ViChar modelName[], ViChar serialNumber[], ViChar manufacturer[], ViPBoolean deviceAvailable);
/**@}*/  /* TLPM_METHODS_RM_x */

/*========================================================================*//**
\defgroup   TLPM_STATUS_REGISTER_x Resource Manager TLVISA library functions
\ingroup    TLPM_METHODS_x
\brief      Functions provided by TLVISA library for managing the status flags
@{
*//*=========================================================================*/
ViStatus _VI_FUNC TLPMX_writeRegister (ViSession vi, ViInt16 reg, ViInt16 value);
ViStatus _VI_FUNC TLPMX_readRegister (ViSession vi, ViInt16 reg, ViPInt16 value);
ViStatus _VI_FUNC TLPMX_presetRegister (ViSession vi);

/*========================================================================*//**
\defgroup   TLPM_REGISTER_FLAGS_x  Status register flags
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define TLPM_REG_STB                (0)   ///< Status Byte Register
#define TLPM_REG_SRE                (1)   ///< Service Request Enable
#define TLPM_REG_ESB                (2)   ///< Standard Event Status Register
#define TLPM_REG_ESE                (3)   ///< Standard Event Enable
#define TLPM_REG_OPER_COND          (4)   ///< Operation Condition Register
#define TLPM_REG_OPER_EVENT         (5)   ///< Operation Event Register
#define TLPM_REG_OPER_ENAB          (6)   ///< Operation Event Enable Register
#define TLPM_REG_OPER_PTR           (7)   ///< Operation Positive Transition Filter
#define TLPM_REG_OPER_NTR           (8)   ///< Operation Negative Transition Filter
#define TLPM_REG_QUES_COND          (9)   ///< Questionable Condition Register
#define TLPM_REG_QUES_EVENT         (10)  ///< Questionable Event Register
#define TLPM_REG_QUES_ENAB          (11)  ///< Questionable Event Enable Reg.
#define TLPM_REG_QUES_PTR           (12)  ///< Questionable Positive Transition Filter
#define TLPM_REG_QUES_NTR           (13)  ///< Questionable Negative Transition Filter
#define TLPM_REG_MEAS_COND          (14)  ///< Measurement Condition Register
#define TLPM_REG_MEAS_EVENT         (15)  ///< Measurement Event Register
#define TLPM_REG_MEAS_ENAB          (16)  ///< Measurement Event Enable Register
#define TLPM_REG_MEAS_PTR           (17)  ///< Measurement Positive Transition Filter
#define TLPM_REG_MEAS_NTR           (18)  ///< Measurement Negative Transition Filter
#define TLPM_REG_AUX_COND           (19)  ///< Auxiliary Condition Register
#define TLPM_REG_AUX_EVENT          (20)  ///< Auxiliary Event Register
#define TLPM_REG_AUX_ENAB           (21)  ///< Auxiliary Event Enable Register
#define TLPM_REG_AUX_PTR            (22)  ///< Auxiliary Positive Transition Filter
#define TLPM_REG_AUX_NTR            (23)  ///< Auxiliary Negative Transition Filter
#define TLPM_REG_OPER_COND_1        (24)  ///< Operation Condition Register Channel 1
#define TLPM_REG_OPER_COND_2        (25)  ///< Operation Condition Register Channel 2
#define TLPM_REG_AUX_DET_COND       (26)  ///< Auxiliary Condition Register DET


// STATUS BYTE bit definitions (see IEEE488.2-1992 §11.2)
#define TLPM_STATBIT_STB_AUX        (0x01)   ///< Auxiliary summary
#define TLPM_STATBIT_STB_MEAS       (0x02)   ///< Device Measurement Summary
#define TLPM_STATBIT_STB_EAV        (0x04)   ///< Error available
#define TLPM_STATBIT_STB_QUES       (0x08)   ///< Questionable Status Summary
#define TLPM_STATBIT_STB_MAV        (0x10)   ///< Message available
#define TLPM_STATBIT_STB_ESB        (0x20)   ///< Event Status Bit
#define TLPM_STATBIT_STB_MSS        (0x40)   ///< Master summary status
#define TLPM_STATBIT_STB_OPER       (0x80)   ///< Operation Status Summary

// STANDARD EVENT STATUS REGISTER bit definitions (see IEEE488.2-1992 §11.5.1)
#define TLPM_STATBIT_ESR_OPC        (0x01)   ///< Operation complete
#define TLPM_STATBIT_ESR_RQC        (0x02)   ///< Request control
#define TLPM_STATBIT_ESR_QYE        (0x04)   ///< Query error
#define TLPM_STATBIT_ESR_DDE        (0x08)   ///< Device-Specific error
#define TLPM_STATBIT_ESR_EXE        (0x10)   ///< Execution error
#define TLPM_STATBIT_ESR_CME        (0x20)   ///< Command error
#define TLPM_STATBIT_ESR_URQ        (0x40)   ///< User request
#define TLPM_STATBIT_ESR_PON        (0x80)   ///< Power on
        
// QUESTIONABLE STATUS REGISTER bit definitions (see SCPI 99.0 §9)
#define TLPM_STATBIT_QUES_VOLT      (0x0001) ///< questionable voltage measurement
#define TLPM_STATBIT_QUES_CURR      (0x0002) ///< questionable current measurement
#define TLPM_STATBIT_QUES_TIME      (0x0004) ///< questionable time measurement
#define TLPM_STATBIT_QUES_POW       (0x0008) ///< questionable power measurement
#define TLPM_STATBIT_QUES_TEMP      (0x0010) ///< questionable temperature measurement
#define TLPM_STATBIT_QUES_FREQ      (0x0020) ///< questionable frequency measurement
#define TLPM_STATBIT_QUES_PHAS      (0x0040) ///< questionable phase measurement
#define TLPM_STATBIT_QUES_MOD       (0x0080) ///< questionable modulation measurement
#define TLPM_STATBIT_QUES_CAL       (0x0100) ///< questionable calibration
#define TLPM_STATBIT_QUES_ENER      (0x0200) ///< questionable energy measurement
#define TLPM_STATBIT_QUES_10        (0x0400) ///< reserved
#define TLPM_STATBIT_QUES_11        (0x0800) ///< reserved
#define TLPM_STATBIT_QUES_12        (0x1000) ///< reserved
#define TLPM_STATBIT_QUES_INST      (0x2000) ///< instrument summary
#define TLPM_STATBIT_QUES_WARN      (0x4000) ///< command warning
#define TLPM_STATBIT_QUES_15        (0x8000) ///< reserved

// OPERATION STATUS REGISTER bit definitions (see SCPI 99.0 §9)
#define TLPM_STATBIT_OPER_CAL       (0x0001) ///< The instrument is currently performing a calibration.
#define TLPM_STATBIT_OPER_SETT      (0x0002) ///< The instrument is waiting for signals it controls to stabilize enough to begin measurements.
#define TLPM_STATBIT_OPER_RANG      (0x0004) ///< The instrument is currently changing its range.
#define TLPM_STATBIT_OPER_SWE       (0x0008) ///< A sweep is in progress.
#define TLPM_STATBIT_OPER_MEAS      (0x0010) ///< The instrument is actively measuring.
#define TLPM_STATBIT_OPER_TRIG      (0x0020) ///< The instrument is in a “wait for trigger” state of the trigger model.
#define TLPM_STATBIT_OPER_ARM       (0x0040) ///< The instrument is in a “wait for arm” state of the trigger model.
#define TLPM_STATBIT_OPER_CORR      (0x0080) ///< The instrument is currently performing a correction (Auto-PID tune).
#define TLPM_STATBIT_OPER_SENS      (0x0100) ///< Optical powermeter sensor connected and operable.
#define TLPM_STATBIT_OPER_DATA      (0x0200) ///< Measurement data ready for fetch.
#define TLPM_STATBIT_OPER_THAC      (0x0400) ///< Thermopile accelerator active.
#define TLPM_STATBIT_OPER_11        (0x0800) ///< reserved
#define TLPM_STATBIT_OPER_12        (0x1000) ///< reserved
#define TLPM_STATBIT_OPER_INST      (0x2000) ///< One of n multiple logical instruments is reporting OPERational status.
#define TLPM_STATBIT_OPER_PROG      (0x4000) ///< A user-defined programming is currently in the run state.
#define TLPM_STATBIT_OPER_15        (0x8000) ///< reserved

// Thorlabs defined MEASRUEMENT STATUS REGISTER bit definitions
#define TLPM_STATBIT_MEAS_0         (0x0001) ///< reserved
#define TLPM_STATBIT_MEAS_1         (0x0002) ///< reserved
#define TLPM_STATBIT_MEAS_2         (0x0004) ///< reserved
#define TLPM_STATBIT_MEAS_3         (0x0008) ///< reserved
#define TLPM_STATBIT_MEAS_4         (0x0010) ///< reserved
#define TLPM_STATBIT_MEAS_5         (0x0020) ///< reserved
#define TLPM_STATBIT_MEAS_6         (0x0040) ///< reserved
#define TLPM_STATBIT_MEAS_7         (0x0080) ///< reserved
#define TLPM_STATBIT_MEAS_8         (0x0100) ///< reserved
#define TLPM_STATBIT_MEAS_9         (0x0200) ///< reserved
#define TLPM_STATBIT_MEAS_10        (0x0400) ///< reserved
#define TLPM_STATBIT_MEAS_11        (0x0800) ///< reserved
#define TLPM_STATBIT_MEAS_12        (0x1000) ///< reserved
#define TLPM_STATBIT_MEAS_13        (0x2000) ///< reserved
#define TLPM_STATBIT_MEAS_14        (0x4000) ///< reserved
#define TLPM_STATBIT_MEAS_15        (0x8000) ///< reserved

// Thorlabs defined Auxiliary STATUS REGISTER bit definitions
#define TLPM_STATBIT_AUX_NTC        (0x0001) ///< Auxiliary NTC temperature sensor connected.
#define TLPM_STATBIT_AUX_EMM        (0x0002) ///< External measurement module connected.
#define TLPM_STATBIT_AUX_UPCS       (0x0004) ///< User Power Calibration supported by this instrument 
#define TLPM_STATBIT_AUX_UPCA       (0x0008) ///< User Power Calibration active status				  
#define TLPM_STATBIT_AUX_EXPS       (0x0010) ///< External power supply connected
#define TLPM_STATBIT_AUX_BATC       (0x0020) ///< Battery charging
#define TLPM_STATBIT_AUX_BATL       (0x0040) ///< Battery low
#define TLPM_STATBIT_AUX_IPS        (0x0080) ///< Apple(tm) authentification supported. True if an authentification co-processor is installed.
#define TLPM_STATBIT_AUX_IPF        (0x0100) ///< Apple(tm) authentification failed. True if the authentification setup procedure failed.
#define TLPM_STATBIT_AUX_9          (0x0200) ///< reserved
#define TLPM_STATBIT_AUX_10         (0x0400) ///< reserved
#define TLPM_STATBIT_AUX_11         (0x0800) ///< reserved
#define TLPM_STATBIT_AUX_12         (0x1000) ///< reserved
#define TLPM_STATBIT_AUX_13         (0x2000) ///< reserved
#define TLPM_STATBIT_AUX_14         (0x4000) ///< reserved
#define TLPM_STATBIT_AUX_15         (0x8000) ///< reserved
/**@}*/  /* TLPM_REGISTER_FLAGS_x */  

/**@}*/  /* TLPM_STATUS_REGISTER_x */  

/*========================================================================*//**
\defgroup   TLPM_METHODS_SYSTEM_x System Functions
\ingroup    TLPM_METHODS_x
\brief      The System class groups functions for general system level control.
@{
*//*=========================================================================*/

	/*========================================================================*//**
	\defgroup   TLPM_METHODS_SYSTEM_DATE_TIME_x System Date Time Functions
	\ingroup    TLPM_METHODS_SYSTEM_x
	\brief      System date and time control.
	@{
	*//*=========================================================================*/
		/*========================================================================*//**
		\defgroup   TLPM_TIME_MODE_x  Summer or Winter time
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_WINTERTIME   (0) 
		#define TLPM_SUMMERTIME   (1)		
		/**@}*/  /* TLPM_TIME_MODE_x */ 
	ViStatus _VI_FUNC TLPMX_sendNTPRequest (ViSession vi, ViBoolean timeMode, ViInt16 timeZone, ViChar IPAddress[]);
	ViStatus _VI_FUNC TLPMX_setTime (ViSession vi, ViInt16  year, ViInt16  month, ViInt16  day, ViInt16  hour, ViInt16 minute, ViInt16  second);
	ViStatus _VI_FUNC TLPMX_getTime (ViSession vi, ViPInt16 year, ViPInt16 month, ViPInt16 day, ViPInt16 hour, ViPInt16 minute, ViPInt16 second);
	ViStatus _VI_FUNC TLPMX_setSummertime (ViSession vi, ViBoolean timeMode);
	ViStatus _VI_FUNC TLPMX_getSummertime (ViSession vi, ViPBoolean timeMode);
	/**@}*/  /* TLPM_METHODS_SYSTEM_DATE_TIME_x */  

	/*========================================================================*//**
	\defgroup   TLPM_METHODS_SYSTEM_LINE_FREQUENCY_x System Line Frequency Functions
	\ingroup    TLPM_METHODS_SYSTEM_x
	\brief      Line frequency setup.
	@{
	*//*=========================================================================*/
	ViStatus _VI_FUNC TLPMX_setLineFrequency (ViSession vi, ViInt16  lineFrequency);
	ViStatus _VI_FUNC TLPMX_getLineFrequency (ViSession vi, ViPInt16 lineFrequency);

		/*========================================================================*//**
		\defgroup   TLPM_LINE_FREQUENCY_FLAGS_x  Line Frequency Flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_LINE_FREQ_50   (50) ///< line frequency in Hz
		#define TLPM_LINE_FREQ_60   (60) ///< line frequency in Hz
		/**@}*/  /* TLPM_LINE_FREQUENCY_FLAGS_x */ 

	/**@}*/  /* TLPM_METHODS_SYSTEM_LINE_FREQUENCY_x */  

	/*========================================================================*//**
	\defgroup   TLPM_METHODS_SYSTEM_BATTERY_x System Battery Functions
	\ingroup    TLPM_METHODS_SYSTEM_x
	\brief      Battery information.
	@{
	*//*=========================================================================*/
	ViStatus _VI_FUNC TLPMX_getBatteryVoltage (ViSession vi, ViPReal64 voltage);   
	/**@}*/  /* TLPM_METHODS_SYSTEM_BATTERY_x */  

	/*========================================================================*//**
	\defgroup   TLPM_METHODS_SYSTEM_DISPLAY_x System Display Functions
	\ingroup    TLPM_METHODS_SYSTEM_x
	\brief      The Display class groups functions for display control.
	@{
	*//*=========================================================================*/
	ViStatus _VI_FUNC TLPMX_setDispBrightness (ViSession vi, ViReal64 val);
	ViStatus _VI_FUNC TLPMX_getDispBrightness (ViSession vi, ViPReal64 pVal);

	ViStatus _VI_FUNC TLPMX_setDispContrast (ViSession vi, ViReal64 val);
	ViStatus _VI_FUNC TLPMX_getDispContrast (ViSession vi, ViPReal64 pVal);
	/**@}*/  /* TLPM_METHODS_SYSTEM_DISPLAY_x */ 
	
	/*========================================================================*//**
	\defgroup   TLPM_METHODS_SYSTEM_SOUND_x System Sound Functions
	\ingroup    TLPM_METHODS_SYSTEM_x
	\brief      Plays and controls the sound of the device
	@{
	*//*=========================================================================*/
	ViStatus _VI_FUNC TLPMX_beep (ViSession instrumentHandle);
	/**@}*/  /* TLPM_METHODS_SYSTEM_SOUND_x */ 

/**@}*/  /* TLPM_METHODS_SYSTEM_x */  

/*========================================================================*//**
\defgroup   TLPM_METHODS_MEASURE_x Measure Functions
\ingroup    TLPM_METHODS_x
\brief      This class of functions transfers measurement data from the instrument.
@{
*//*=========================================================================*/
	/*========================================================================*//**
	\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_x Measure Configure Functions
	\ingroup    TLPM_METHODS_MEASURE_x
	\brief      The Configure class contains functions to control the measurement capabilities of the instrument.
	@{
	*//*=========================================================================*/
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_INPUT_x Measure Configure Input Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      The Configure class contains functions to control the measurement capabilities of the instrument.
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPMX_setInputFilterState (ViSession vi, ViBoolean inputFilterState, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getInputFilterState (ViSession vi, ViPBoolean inputFilterState, ViUInt16 channel);
			/*========================================================================*//**
			\defgroup   TLPM_INPUT_FILTER_FLAGS_x  Input Filter Flags
			\ingroup    TLPM_MACROS_x
			@{
			*//*=========================================================================*/
			#define TLPM_INPUT_FILTER_STATE_OFF  (0)
			#define TLPM_INPUT_FILTER_STATE_ON   (1)
			/**@}*/  /* TLPM_INPUT_FILTER_FLAGS_x */ 

		ViStatus _VI_FUNC TLPMX_setAccelState (ViSession vi, ViBoolean accelState, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getAccelState (ViSession vi, ViPBoolean accelState, ViUInt16 channel);

			/*========================================================================*//**
			\defgroup   TLPM_INPUT_ACCELERATION_STATES_x  Input Accelerateion Flags
			\ingroup    TLPM_MACROS_x
			@{
				*//*=========================================================================*/
			#define TLPM_ACCELERATION_STATE_OFF  (0)
			#define TLPM_ACCELERATION_STATE_ON   (1)
			/**@}*/  /* TLPM_INPUT_ACCELERATION_STATES_x */  

		ViStatus _VI_FUNC TLPMX_setAccelMode (ViSession vi, ViBoolean accelMode, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getAccelMode (ViSession vi, ViPBoolean accelMode, ViUInt16 channel);
		
			/*========================================================================*//**
			\defgroup   TLPM_INPUT_ACCELERATION_MODES_x  Input Filter Flags
			\ingroup    TLPM_MACROS_x
			@{
			*//*=========================================================================*/  
			#define TLPM_ACCELERATION_MANUAL     (0)
			#define TLPM_ACCELERATION_AUTO       (1)
			/**@}*/  /* TLPM_INPUT_ACCELERATION_MODES_x */   


		ViStatus _VI_FUNC TLPMX_setAccelTau (ViSession vi, ViReal64 accelTau, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getAccelTau (ViSession vi, ViInt16 attribute, ViPReal64 accelTau, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_setInputAdapterType (ViSession vi, ViInt16 type, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getInputAdapterType (ViSession vi, ViPInt16 type, ViUInt16 channel);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_INPUT_x */  
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_AVERAGE_x Measure Configure Average Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the measurement averaging of the instrument.
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPMX_setAvgTime (ViSession vi, ViReal64 avgTime, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getAvgTime (ViSession vi, ViInt16 attribute, ViPReal64 avgTime, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_setAvgCnt (ViSession vi, ViInt16 averageCount, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getAvgCnt (ViSession vi, ViPInt16 averageCount, ViUInt16 channel);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_AVERAGE_x */ 
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_CORRECTION_x Measure Configure Correction Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the input corrections of the instrument.
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPMX_setAttenuation (ViSession vi, ViReal64 attenuation, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getAttenuation (ViSession vi, ViInt16 attribute, ViPReal64 attenuation, ViUInt16 channel);
		
		ViStatus _VI_FUNC TLPMX_startDarkAdjust (ViSession vi, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_cancelDarkAdjust (ViSession vi, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getDarkAdjustState (ViSession vi, ViPInt16 state, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setDarkOffset (ViSession vi, ViReal64 darkOffset, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getDarkOffset (ViSession vi, ViPReal64 darkOffset, ViUInt16 channel);

		/*========================================================================*//**
		\defgroup   TLPM_STAT_DARK_ADJUST_FLAGS_x  Dark adjustment status flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_STAT_DARK_ADJUST_FINISHED  (0)
		#define TLPM_STAT_DARK_ADJUST_RUNNING   (1)
		/**@}*/  /* TLPM_STAT_DARK_ADJUST_FLAGS_x */ 
		
		ViStatus _VI_FUNC TLPMX_setBeamDia (ViSession vi, ViReal64 beamDiameter, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getBeamDia (ViSession vi, ViInt16 attribute, ViPReal64 beamDiameter, ViUInt16 channel);
		
		ViStatus _VI_FUNC TLPMX_setWavelength (ViSession vi, ViReal64 wavelength, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getWavelength (ViSession vi, ViInt16 attribute, ViPReal64 wavelength, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_setPhotodiodeResponsivity (ViSession vi, ViReal64 response, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getPhotodiodeResponsivity (ViSession vi, ViInt16 attribute, ViPReal64 responsivity, ViUInt16 channel);
		
		ViStatus _VI_FUNC TLPMX_setThermopileResponsivity (ViSession vi, ViReal64 response, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getThermopileResponsivity (ViSession vi, ViInt16 attribute, ViPReal64 responsivity, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_setPyrosensorResponsivity (ViSession vi, ViReal64 response, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getPyrosensorResponsivity (ViSession vi, ViInt16 attribute, ViPReal64 responsivity, ViUInt16 channel);

		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_CORRECTION_x */    
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_CURRENT_MEASUREMENT_x Measure Configure Current Measurement Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles current measurement related items of the instrument. 
		\details	This set of functions is only useable with sensor types that produce an electrical current as measurement value (Photodiodes).
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPMX_setCurrentAutoRange (ViSession vi, ViBoolean currentAutorangeMode, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getCurrentAutorange (ViSession vi, ViPBoolean currentAutorangeMode, ViUInt16 channel);

		/*========================================================================*//**
		\defgroup   TLPM_AUTORANGE_CURRENT_FLAGS_x  Auto Current status flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_AUTORANGE_CURRENT_OFF  (0)
		#define TLPM_AUTORANGE_CURRENT_ON   (1)
		/**@}*/  /* TLPM_AUTORANGE_CURRENT_FLAGS_x */ 
		
		ViStatus _VI_FUNC TLPMX_setCurrentRange (ViSession vi, ViReal64 current_to_Measure, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getCurrentRange (ViSession vi, ViInt16 attribute, ViPReal64 currentValue, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getCurrentRanges (ViSession instr, ViReal64 currentValues[], ViPUInt16 rangeCount, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setCurrentRangeSearch (ViSession instr, ViUInt16 channel);		
		ViStatus _VI_FUNC TLPMX_setCurrentRef (ViSession vi, ViReal64 currentReferenceValue, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getCurrentRef (ViSession vi, ViInt16 attribute, ViPReal64 currentReferenceValue, ViUInt16 channel);
		
		ViStatus _VI_FUNC TLPMX_setCurrentRefState (ViSession vi, ViBoolean currentReferenceState, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getCurrentRefState (ViSession vi, ViPBoolean currentReferenceState, ViUInt16 channel);

		/*========================================================================*//**
		\defgroup   TLPM_CURRENT_REFERENCE_FLAGS_x  Current reference status flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_CURRENT_REF_OFF  (0)
		#define TLPM_CURRENT_REF_ON   (1)  
		/**@}*/  /* TLPM_CURRENT_REFERENCE_FLAGS_x */ 
		
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_CURRENT_MEASUREMENT_x */ 
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_ENERGY_MEASUREMENT_x Measure Configure Energy Measurement Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles energy measurement related items of the instrument.
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPMX_setEnergyRange (ViSession vi, ViReal64 energyToMeasure, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getEnergyRange (ViSession vi, ViInt16 attribute, ViPReal64 energyValue, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_setEnergyRef (ViSession vi, ViReal64 energyReferenceValue, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getEnergyRef (ViSession vi, ViInt16 attribute, ViPReal64 energyReferenceValue, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_setEnergyRefState (ViSession vi, ViBoolean energyReferenceState, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getEnergyRefState (ViSession vi, ViPBoolean energyReferenceState, ViUInt16 channel);

		/*========================================================================*//**
		\defgroup   TLPM_ENERGY_REFERENCE_FLAGS_x  Energy reference status flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_ENERGY_REF_OFF (0)
		#define TLPM_ENERGY_REF_ON  (1)
		/**@}*/  /* TLPM_ENERGY_REFERENCE_FLAGS_x */
		
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_ENERGY_MEASUREMENT_x */  
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_FREQUENCY_MEASUREMENT_x Measure Configure Frequency Measurement Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions reads the frequency measurement range from the instrument.
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPMX_getFreqRange (ViSession vi, ViPReal64 lowerFrequency, ViPReal64 upperFrequency, ViUInt16 channel); 		
		
		/*========================================================================*//**
		\defgroup   TLPM_FREQ_MODE_FLAGS_x  Freq mode flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_FREQ_MODE_CW  	(0)
		#define TLPM_FREQ_MODE_PEAK	(1)
		/**@}*/  /* TLPM_AUTO_RANGE_FLAGS_x */ 		
		
		ViStatus _VI_FUNC TLPMX_setFreqMode (ViSession vi, ViUInt16 frequencyMode, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getFreqMode (ViSession vi, ViPUInt16 frequencyMode, ViUInt16 channel);
		
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_FREQUENCY_MEASUREMENT_x */ 
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_POWER_MEASUREMENT_x Measure Configure Power Measurement Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles power measurement related items of the instrument.
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPMX_setPowerAutoRange (ViSession vi, ViBoolean powerAutorangeMode, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getPowerAutorange (ViSession vi, ViPBoolean powerAutorangeMode, ViUInt16 channel);

		/*========================================================================*//**
		\defgroup   TLPM_AUTO_RANGE_FLAGS_x  Auto range mode flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_AUTORANGE_POWER_OFF  (0)
		#define TLPM_AUTORANGE_POWER_ON   (1)
		/**@}*/  /* TLPM_AUTO_RANGE_FLAGS_x */   
		
		ViStatus _VI_FUNC TLPMX_setPowerRange (ViSession vi, ViReal64 power_to_Measure, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getPowerRange (ViSession vi, ViInt16 attribute, ViPReal64 powerValue, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_setPowerRef (ViSession vi, ViReal64 powerReferenceValue, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getPowerRef (ViSession vi, ViInt16 attribute, ViPReal64 powerReferenceValue, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_setPowerRefState (ViSession vi, ViBoolean powerReferenceState, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getPowerRefState (ViSession vi, ViPBoolean powerReferenceState, ViUInt16 channel);

		/*========================================================================*//**
		\defgroup   TLPM_POWER_REFERENCE_FLAGS_x  Power reference status flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_POWER_REF_OFF  (0)
		#define TLPM_POWER_REF_ON   (1)
		/**@}*/  /* TLPM_POWER_REFERENCE_FLAGS_x */ 

		ViStatus _VI_FUNC TLPMX_setPowerUnit (ViSession vi, ViInt16 powerUnit, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getPowerUnit (ViSession vi, ViPInt16 powerUnit, ViUInt16 channel);

		/*========================================================================*//**
		\defgroup   TLPM_POWER_UNIT_x  Power unit
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_POWER_UNIT_WATT   (0)
		#define TLPM_POWER_UNIT_DBM    (1)
		/**@}*/  /* TLPM_POWER_UNIT_x */ 
		
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_POWER_MEASUREMENT_x */ 
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_USER_POWER_CALIBRATION_x Measure Configure User Power Calibration  Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles user power calibtation related items of the instrument.
		@{
		*//*=========================================================================*/
		
		/*========================================================================*//**
		\defgroup   TLPM_SENSOR_POSISION_x  Position of the sensor switch of a Thorlabs S130C
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define SENSOR_SWITCH_POS_1  (1)
		#define SENSOR_SWITCH_POS_2  (2)
		/**@}*/  /* TLPM_SENSOR_POSISION_x */ 
		
		ViStatus _VI_FUNC TLPMX_getPowerCalibrationPointsInformation (ViSession vi, ViUInt16 index, ViChar serialNumber[], ViChar calibrationDate[], ViPUInt16 calibrationPointsCount, ViChar author[], ViPUInt16 sensorPosition, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_getPowerCalibrationPointsState (ViSession vi, ViUInt16 index,ViPBoolean state, ViUInt16 channel); 
		ViStatus _VI_FUNC TLPMX_setPowerCalibrationPointsState (ViSession vi, ViUInt16 index, ViBoolean state, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_getPowerCalibrationPoints (ViSession vi, ViUInt16 index, ViUInt16 pointCounts, ViReal64 wavelengths[], ViReal64 powerCorrectionFactors[], ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setPowerCalibrationPoints (ViSession vi, ViUInt16 index, ViUInt16 pointCounts, ViReal64 wavelengths[], ViReal64 powerCorrectionFactors[], ViChar author[], ViUInt16 sensorPosition, ViUInt16 channel);
		
		ViStatus _VI_FUNC TLPMX_reinitSensor (ViSession vi, ViUInt16 channel);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_USER_POWER_CALIBRATION_x */ 
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_VOLTAGE_MEASUREMENT_x Measure Configure Voltage Measurement Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles voltage measurement related items of the instrument. 
		\details	This set of functions is only useable with sensor types that produce an electrical voltage as measurement value (Thermopile sensors and pyroelectric sensors).
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPMX_setVoltageAutoRange (ViSession vi, ViBoolean voltageAutorangeMode, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getVoltageAutorange (ViSession vi, ViPBoolean voltageAutorangeMode, ViUInt16 channel);

		/*========================================================================*//**
		\defgroup   TLPM_VOLTAGE_AUTO_RANGE_STATE_x  Voltage Auto Range status
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_AUTORANGE_VOLTAGE_OFF  (0)
		#define TLPM_AUTORANGE_VOLTAGE_ON   (1)
		/**@}*/  /* TLPM_VOLTAGE_AUTO_RANGE_STATE_x */ 

		ViStatus _VI_FUNC TLPMX_setVoltageRange (ViSession vi, ViReal64 voltage_to_Measure, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getVoltageRange (ViSession vi, ViInt16 attribute, ViPReal64 voltageValue, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getVoltageRanges (ViSession vi, ViReal64 voltageValues[], ViPUInt16 rangeCount, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setVoltageRangeSearch (ViSession vi, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setVoltageRef (ViSession vi, ViReal64 voltageReferenceValue, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getVoltageRef (ViSession vi, ViInt16 attribute, ViPReal64 voltageReferenceValue, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_setVoltageRefState (ViSession vi, ViBoolean voltageReferenceState, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getVoltageRefState (ViSession vi, ViPBoolean voltageReferenceState, ViUInt16 channel);

		/*========================================================================*//**
		\defgroup   TLPM_VOLTAGE_REFERENCE_STATE_x  Voltage Reference status
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_VOLTAGE_REF_OFF  (0)
		#define TLPM_VOLTAGE_REF_ON   (1)  
		/**@}*/  /* TLPM_VOLTAGE_REFERENCE_STATE_x */ 
		
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_VOLTAGE_MEASUREMENT_x */  
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_PEAK_DETECTOR_x Measure Configure Peak Detector Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the peak detector threshold of the instrument.
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPMX_setPeakThreshold (ViSession vi, ViReal64 peakThreshold, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getPeakThreshold (ViSession vi, ViInt16 attribute, ViPReal64 peakThreshold, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_startPeakDetector (ViSession vi, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_isPeakDetectorRunning (ViSession vi, ViPBoolean isRunning, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setPeakFilter(ViSession vi, ViInt16 filter, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getPeakFilter(ViSession vi, ViPInt16 filter, ViUInt16 channel);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_PEAK_DETECTOR_x */ 
		
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_EXTERNAL_TEMPERATURE_SENSOR_x Measure Configure External Temperature Sensor Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the external temperature sensor connected to the instrument.
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPMX_setExtNtcParameter (ViSession vi, ViReal64 r0Coefficient, ViReal64 betaCoefficient, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_getExtNtcParameter (ViSession vi, ViInt16 attribute, ViPReal64 r0Coefficient, ViPReal64 betaCoefficient, ViUInt16 channel);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_EXTERNAL_TEMPERATURE_SENSOR_x */ 
		
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_FILTER_POSITION_x Measure Configure Filter Position Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the filter position detection
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPMX_setFilterPosition (ViSession vi, ViBoolean filterPosition);  
		ViStatus _VI_FUNC TLPMX_getFilterPosition (ViSession vi, ViPBoolean filterPosition);  
		ViStatus _VI_FUNC TLPMX_setFilterAutoMode (ViSession vi, ViBoolean filterAutoPositionDetection);  
		ViStatus _VI_FUNC TLPMX_getFilterAutoMode (ViSession vi, ViPBoolean filterAutoPositionDetection);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_FILTER_POSITION_x */  
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_ANALOG_OUTPUT_x Measure Configure Filter Position Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the filter position detection
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPMX_getAnalogOutputSlopeRange (ViSession vi, ViPReal64 minSlope, ViPReal64 maxSlope, ViUInt16 channel);  
		ViStatus _VI_FUNC TLPMX_setAnalogOutputSlope (ViSession vi, ViReal64 slope, ViUInt16 channel);		 
		ViStatus _VI_FUNC TLPMX_getAnalogOutputSlope (ViSession vi, ViInt16 attribute, ViPReal64 slope, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_getAnalogOutputVoltageRange (ViSession vi, ViPReal64 minVoltage, ViPReal64 maxVoltage, ViUInt16 channel); 
		ViStatus _VI_FUNC TLPMX_getAnalogOutputVoltage (ViSession vi, ViInt16 attribute,  ViPReal64 voltage, ViUInt16 channel);
		
		ViStatus _VI_FUNC TLPMX_getAnalogOutputGainRange (ViSession vi, ViPInt16 gainRangeIndex, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setAnalogOutputGainRange (ViSession vi, ViInt16 gainRangeIndex, ViUInt16 channel);
		
		/*========================================================================*//**
		\defgroup   TLPM_ANALOG_ROUTES_x  Analog Routes definitions
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_ANALOG_ROUTE_PUR  (0)
		#define TLPM_ANALOG_ROUTE_CBA  (1)
		#define TLPM_ANALOG_ROUTE_CMA  (2)
		#define TLPM_ANALOG_ROUTE_GEN  (3)
		/**@}*/  /* TLPM_VOLTAGE_AUTO_RANGE_STATE_x */ 
		ViStatus _VI_FUNC TLPMX_getAnalogOutputRoute (ViSession vi, ViChar routeName[], ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setAnalogOutputRoute (ViSession vi, ViUInt16 routeStrategy, ViUInt16 channel);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_ANALOG_OUTPUT_x */
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_POSITION_ANALOG_OUTPUT_x Measure Configure Position Analog Output
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the analog output for the position
		@{
		*//*=========================================================================*/	
		ViStatus _VI_FUNC TLPMX_getPositionAnalogOutputSlopeRange (ViSession vi, ViPReal64 minSlope, ViPReal64 maxSlope, ViUInt16 channel);	  
		ViStatus _VI_FUNC TLPMX_setPositionAnalogOutputSlope (ViSession vi, ViReal64 slope, ViUInt16 channel);   
		ViStatus _VI_FUNC TLPMX_getPositionAnalogOutputSlope (ViSession vi, ViInt16 attribute, ViPReal64 slope, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_getPositionAnalogOutputVoltageRange (ViSession vi, ViPReal64 minVoltage, ViPReal64 maxVoltage, ViUInt16 channel);  
		ViStatus _VI_FUNC TLPMX_getPositionAnalogOutputVoltage (ViSession vi, ViInt16 attribute, ViPReal64 voltageX, ViPReal64 voltageY, ViUInt16 channel);

		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_POSITION_ANALOG_OUTPUT_x */  
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_MEASUREMENT_PIN_OUTPUT_x Measure Configure Position Analog Output
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the analog output for the position
		@{
		*//*=========================================================================*/	
		ViStatus _VI_FUNC TLPMX_getMeasPinMode (ViSession vi, ViPBoolean state, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_getMeasPinPowerLevel (ViSession vi, ViPReal64 level, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setMeasPinPowerLevel (ViSession vi, ViReal64 level, ViUInt16 channel);

		ViStatus _VI_FUNC TLPMX_getMeasPinEnergyLevel (ViSession vi, ViPReal64 level, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setMeasPinEnergyLevel (ViSession vi, ViReal64 level, ViUInt16 channel);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_MEASUREMENT_PIN_OUTPUT_x */  
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_PULSE_x Measure Configure Pulse
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the settings for the pulse measurements
		@{
		*//*=========================================================================*/	
		ViStatus _VI_FUNC TLPMX_setNegativePulseWidth (ViSession vi, ViReal64 pulseDuration, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setPositivePulseWidth (ViSession vi, ViReal64 pulseDuration, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setNegativeDutyCycle (ViSession vi, ViReal64 dutyCycle, ViUInt16 channel);
		ViStatus _VI_FUNC TLPMX_setPositiveDutyCycle (ViSession vi, ViReal64 dutyCycle, ViUInt16 channel);

		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_PULSE_x */  
		
	/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_x */  
	
	/*========================================================================*//**
	\defgroup   TLPM_METHODS_MEASURE_READ_x Measure Read Functions
	\ingroup    TLPM_METHODS_MEASURE_x
	\brief      The Read class contains functions to read measurement results from the instrument.
	@{
	*//*=========================================================================*/ 
	ViStatus _VI_FUNC TLPMX_measCurrent (ViSession vi, ViPReal64 current, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measVoltage (ViSession vi, ViPReal64 voltage, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measPower (ViSession vi, ViPReal64 power, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measEnergy (ViSession vi, ViPReal64 energy, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measFreq (ViSession vi, ViPReal64 frequency, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measPowerDens (ViSession vi, ViPReal64 powerDensity, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measEnergyDens (ViSession vi, ViPReal64 energyDensity, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measAuxAD0 (ViSession vi, ViPReal64 voltage, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measAuxAD1 (ViSession vi, ViPReal64 voltage, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measEmmHumidity (ViSession vi, ViPReal64 humidity, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measEmmTemperature (ViSession vi, ViPReal64 temperature, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measExtNtcTemperature (ViSession vi, ViPReal64 temperature, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measExtNtcResistance (ViSession vi, ViPReal64 resistance, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measHeadResistance (ViSession vi, ViPReal64 frequency, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measHeadTemperature (ViSession vi, ViPReal64 frequency, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_meas4QPositions (ViSession vi, ViPReal64 xPosition, ViPReal64 yPosition, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_meas4QVoltages (ViSession vi, ViPReal64 voltage1, ViPReal64 voltage2, ViPReal64 voltage3, ViPReal64 voltage4, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measNegPulseWidth (ViSession vi, ViPReal64 negativePulseWidth, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measPosPulseWidth (ViSession vi, ViPReal64 positivePulseWidth, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measNegDutyCycle (ViSession vi, ViPReal64 negativeDutyCycle, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measPosDutyCycle (ViSession vi, ViPReal64 positiveDutyCycle, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measPowerMeasurementSequence 				(ViSession vi, ViUInt32 baseTime, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measPowerMeasurementSequenceHWTrigger 		(ViSession vi, ViUInt32 baseTime, ViUInt32 hPos, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measureCurrentMeasurementSequence 			(ViSession vi, ViUInt32 baseTime, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_measureCurrentMeasurementSequenceHWTrigger 	(ViSession vi, ViUInt32 baseTime, ViUInt32 hPos, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_getFetchState (ViSession vi, ViPBoolean state, ViUInt16 channel);
	/**@}*/  /* TLPM_METHODS_MEASURE_READ_x */ 
	
	
	/*========================================================================*//**
	\defgroup   TLPM_METHODS_ARRAY_MEASUREMENTS_x Arrey Measurements Functions
	\ingroup    TLPM_METHODS_MEASURE_x
	\brief      The Read class contains functions to read measurement results from the instrument.
	@{
	*//*=========================================================================*/ 
	ViStatus _VI_FUNC TLPMX_resetFastArrayMeasurement 			(ViSession vi, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_confPowerFastArrayMeasurement 		(ViSession vi, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_confCurrentFastArrayMeasurement 	(ViSession vi, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_confVoltageFastArrayMeasurement 	(ViSession vi, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_confPDensityFastArrayMeasurement 	(ViSession vi, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_confEnergyFastArrayMeasurement 		(ViSession vi, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_confEDensityFastArrayMeasurement 	(ViSession vi, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_getNextFastArrayMeasurement 		(ViSession vi, ViPUInt16 count, ViUInt32 timestamps[], ViReal32 values[], ViReal32 values2[], ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_getFastMaxSamplerate 				(ViSession vi, ViPUInt32 pVal, ViUInt16 channel);
	
	ViStatus _VI_FUNC TLPMX_confPowerMeasurementSequence 			(ViSession vi, ViUInt32 baseTime, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_confPowerMeasurementSequenceHWTrigger 	(ViSession vi, ViUInt16 trigSrc, ViUInt32 baseTime, ViUInt32 hPos, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_confCurrentMeasurementSequence 			(ViSession vi, ViUInt32 baseTime, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_confCurrentMeasurementSequenceHWTrigger (ViSession vi, ViUInt16 trigSrc, ViUInt32 baseTime, ViUInt32 hPos, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_startMeasurementSequence(ViSession vi, ViUInt32 autoTriggerDelay, ViPBoolean triggerForced, ViUInt16 channel);

	ViStatus _VI_FUNC TLPMX_getMeasurementSequence(ViSession vi, ViUInt32 baseTime, ViReal32 timeStamps[], ViReal32 values[], ViReal32 values2[], ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_getMeasurementSequenceHWTrigger(ViSession vi, ViUInt32 baseTime, ViReal32 timeStamps[], ViReal32 values[], ViReal32 values2[], ViUInt16 channel);
	
	ViStatus _VI_FUNC TLPMX_confBurstArrayMeasurementChannel (ViSession vi, ViUInt16 channel);
	ViStatus _VI_FUNC TLPMX_confBurstArrayMeasPowerTrigger (ViSession vi, ViUInt32 initDelay, ViUInt32 burstCount, ViUInt32 averaging);
	ViStatus _VI_FUNC TLPMX_confBurstArrayMeasCurrentTrigger (ViSession vi, ViUInt32 initDelay, ViUInt32 burstCount, ViUInt32 averaging);
	ViStatus _VI_FUNC TLPMX_startBurstArrayMeasurement (ViSession vi);
	ViStatus _VI_FUNC TLPMX_getBurstArraySamplesCount (ViSession vi, ViPUInt32 samplesCount);
	ViStatus _VI_FUNC TLPMX_getBurstArraySamples (ViSession vi, ViUInt32 startIndex, ViUInt32 sampleCount, ViReal32 timeStamps[], ViReal32 values[], ViReal32 values2[]);


/**@}*/  /* TLPM_METHODS_MEASURE_READ_x */
	
/**@}*/  /* TLPM_METHODS_MEASURE_x */  

/*========================================================================*//**
\defgroup   TLPM_METHODS_DIGITAL_IO_x Digital IO Functions
\ingroup    TLPM_METHODS_x
\brief      The Digital I/O class groups all functions related to the instrument's digital I/O connector.
\detail		These functions are only available on PM200 and PM400.
@{
*//*=========================================================================*/ 
/*========================================================================*//**
\defgroup   TLPM_IODIR_DIRECTION_x  Digital IO direction
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define TLPM_IODIR_INP    (VI_OFF)
#define TLPM_IODIR_OUTP   (VI_ON)  
/**@}*/  /* TLPM_IODIR_DIRECTION_x */ 

ViStatus _VI_FUNC TLPMX_setDigIoDirection (ViSession vi, ViBoolean IO0, ViBoolean IO1, ViBoolean IO2, ViBoolean IO3);
ViStatus _VI_FUNC TLPMX_getDigIoDirection (ViSession vi, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);

/*========================================================================*//**
\defgroup   TLPM_IODIR_STATE_x  Digital IO status
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define TLPM_IOLVL_LOW   (VI_OFF)
#define TLPM_IOLVL_HIGH  (VI_ON)
/**@}*/  /* TLPM_IODIR_STATE_x */ 

ViStatus _VI_FUNC TLPMX_setDigIoOutput (ViSession vi, ViBoolean IO0, ViBoolean IO1, ViBoolean IO2, ViBoolean IO3);
ViStatus _VI_FUNC TLPMX_getDigIoOutput (ViSession vi, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);

ViStatus _VI_FUNC TLPMX_getDigIoPort (ViSession vi, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);

/**@}*/  /* TLPM_METHODS_DIGITAL_IO_x */  

/*========================================================================*//**
\defgroup   TLPM_METHODS_DIGITAL_IO_PIN_x  Digital IO direction
\ingroup    TLPM_MACROS_x
\brief      The Digital I/O class groups all functions related to the instrument's digital I/O connector.
\detail		These functions are only available on PM200 and PM400.
@{
*//*=========================================================================*/
/*========================================================================*//**
\defgroup   TLPM_IODIR_MODE_x  Digital IO mode
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define DIGITAL_IO_CONFIG_INPUT 	 (0)
#define DIGITAL_IO_CONFIG_OUTPUT 	 (1)
#define DIGITAL_IO_CONFIG_INPUT_ALT  (2)
#define DIGITAL_IO_CONFIG_OUTPUT_ALT (3)
/**@}*/  /* TLPM_IODIR_MODE_x */ 

ViStatus _VI_FUNC TLPMX_setDigIoPinMode (ViSession vi, ViInt16 pinNumber, ViUInt16 pinMode);
ViStatus _VI_FUNC TLPMX_getDigIoPinMode (ViSession vi, ViInt16 pinNumber, ViPUInt16 pinMode);

ViStatus _VI_FUNC TLPMX_setDigIoOutput (ViSession vi, ViBoolean IO0, ViBoolean IO1, ViBoolean IO2, ViBoolean IO3);
ViStatus _VI_FUNC TLPMX_getDigIoOutput (ViSession vi, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);

ViStatus _VI_FUNC TLPMX_getDigIoPinInput (ViSession vi, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);
/**@}*/  /* TLPM_METHODS_DIGITAL_IO_PIN_x */ 

/*========================================================================*//**
\defgroup   TLPM_CONTROLS_x  Control Functions
\ingroup    TLPM_METHODS_x
\brief      Functions to control the speed of the fans, Shutter and Interlocks.
@{
*//*=========================================================================*/ 
ViStatus _VI_FUNC TLPMX_getShutterInterlock (ViSession vi, ViPBoolean interlockState);
ViStatus _VI_FUNC TLPMX_setShutterPosition (ViSession vi, ViBoolean position);
ViStatus _VI_FUNC TLPMX_getShutterPosition (ViSession vi, ViPBoolean position);

ViStatus _VI_FUNC TLPMX_getFanState (ViSession vi, ViPBoolean isRunning, ViUInt16 channel);
/*========================================================================*//**
\defgroup   TLPM_FAN_MODE_x  Fan Control Mode
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define FAN_OPER_OFF 	     (0)
#define FAN_OPER_FULL 	     (1)
#define FAN_OPER_OPEN_LOOP   (2)
#define FAN_OPER_CLOSED_LOOP (3)
#define FAN_OPER_TEMPER_CTRL (4)
/**@}*/  /* TLPM_FAN_MODE_x */ 
ViStatus _VI_FUNC TLPMX_setFanMode (ViSession vi, ViUInt16 mode, ViUInt16 channel);
ViStatus _VI_FUNC TLPMX_getFanMode (ViSession vi, ViPUInt16 mode, ViUInt16 channel);
ViStatus _VI_FUNC TLPMX_setFanVoltage (ViSession vi,ViReal64 voltage, ViUInt16 channel);
ViStatus _VI_FUNC TLPMX_getFanVoltage (ViSession vi,ViPReal64 voltage, ViUInt16 channel);
ViStatus _VI_FUNC TLPMX_setFanRpm (ViSession vi, ViReal64 maxRPM, ViReal64 targetRPM, ViUInt16 channel);
ViStatus _VI_FUNC TLPMX_getFanRpm (ViSession vi, ViPReal64 maxRPM, ViPReal64 targetRPM, ViUInt16 channel);
ViStatus _VI_FUNC TLPMX_getActFanRpm (ViSession vi, ViPReal64 RPM, ViUInt16 channel);
/*========================================================================*//**
\defgroup   TLPM_FAN_TEMPERATUR CONTROL_MODE_x  Fan Temperature Control Mode
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define FAN_TEMPER_SRC_HEAD 	     (0)
#define FAN_TEMPER_SRC_EXT_NTC 	     (1)
/**@}*/  /*   */ 
ViStatus _VI_FUNC TLPMX_setFanTemperatureSource (ViSession vi, ViUInt16 source, ViUInt16 channel);
ViStatus _VI_FUNC TLPMX_getFanTemperatureSource (ViSession vi, ViPUInt16 source, ViUInt16 channel);
ViStatus _VI_FUNC TLPMX_setFanAdjustParameters (ViSession vi,
                                                ViReal64 voltageMin,
                                                ViReal64 voltageMax,
                                                ViReal64 temperatureMin,
                                                ViReal64 temperatureMax,
                                                ViUInt16 channel);
ViStatus _VI_FUNC TLPMX_getFanAdjustParameters (ViSession vi,
                                                ViPReal64 voltageMin,
                                                ViPReal64 voltageMax,
                                                ViPReal64 temperatureMin,
                                                ViPReal64 temperatureMax,
                                                ViUInt16 channel);
/**@}*/  /* TLPM_FAN_x */ 

/*========================================================================*//**
\defgroup   TLPM_METHODS_UTILITY_x Utility Functions
\ingroup    TLPM_METHODS_x
\brief      This class of functions provides utility and lower level functions to communicate with the instrument.
@{
*//*=========================================================================*/ 
ViStatus _VI_FUNC TLPMX_errorMessage (ViSession vi, ViStatus statusCode, ViChar _VI_FAR description[]); 
ViStatus _VI_FUNC TLPMX_errorQuery (ViSession vi, ViPInt32 errorNumber, ViChar _VI_FAR errorMessage[]); 
ViStatus _VI_FUNC TLPMX_errorQueryMode (ViSession vi, ViBoolean mode);   
ViStatus _VI_FUNC TLPMX_errorCount (ViSession instrumentHandle, ViPUInt32 count);
ViStatus _VI_FUNC TLPMX_reset (ViSession vi);  
ViStatus _VI_FUNC TLPMX_selfTest (ViSession vi, ViPInt16 selfTestResult, ViChar _VI_FAR description[]);   
ViStatus _VI_FUNC TLPMX_revisionQuery (ViSession vi, ViChar _VI_FAR instrumentDriverRevision[], ViChar _VI_FAR firmwareRevision[]);  
ViStatus _VI_FUNC TLPMX_identificationQuery (ViSession vi, ViChar _VI_FAR manufacturerName[], ViChar _VI_FAR deviceName[], ViChar _VI_FAR serialNumber[], ViChar _VI_FAR firmwareRevision[]);
ViStatus _VI_FUNC TLPMX_getCalibrationMsg (ViSession vi, ViChar _VI_FAR message[], ViUInt16 channel);
ViStatus _VI_FUNC TLPMX_setDisplayName (ViSession vi, ViChar _VI_FAR name[]);
ViStatus _VI_FUNC TLPMX_getDisplayName (ViSession vi, ViChar _VI_FAR name[]);
ViStatus _VI_FUNC TLPMX_getChannels (ViSession vi, ViPUInt16 channelCount);
ViStatus _VI_FUNC TLPMX_getSensorInfo (ViSession vi, ViChar _VI_FAR name[], ViChar _VI_FAR snr[], ViChar _VI_FAR message[], ViPInt16 pType, ViPInt16 pStype, ViPInt16 pFlags, ViUInt16 channel);

/*========================================================================*//**
\defgroup   TLPM_SENSOR_TYPE_FLAGS_x  Sensor type flags
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
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

#define TLPM_SENS_FLAG_IS_POWER      0x0001 // Power sensor
#define TLPM_SENS_FLAG_IS_ENERGY     0x0002 // Energy sensor
#define TLPM_SENS_FLAG_IS_RESP_SET   0x0010 // Responsivity settable
#define TLPM_SENS_FLAG_IS_WAVEL_SET  0x0020 // Wavelength settable
#define TLPM_SENS_FLAG_IS_TAU_SET    0x0040 // Time constant tau settable
#define TLPM_SENS_FLAG_HAS_TEMP      0x0100 // Temperature sensor included
/**@}*/  /* TLPM_SENSOR_TYPE_FLAGS_x */

	/*========================================================================*//**
	\defgroup   TLPM_METHODS_UTILITY_RAW_IO_x Utility Raw IOFunctions
	\ingroup    TLPM_METHODS_UTILITY_x
	\brief      The Raw I/O class groups all the functions for direct instrument communication.
	@{
	*//*=========================================================================*/ 
	ViStatus _VI_FUNC TLPMX_writeRaw (ViSession vi, ViString command); 
	ViStatus _VI_FUNC TLPMX_readRaw (ViSession vi, ViChar _VI_FAR buffer[], ViUInt32 size, ViPUInt32 returnCount);
	/**@}*/  /* TLPM_METHODS_UTILITY_RAW_IO_x */  
	
	/*========================================================================*//**
	\defgroup   TLPM_METHODS_UTILITY_TIMEOUT_x Utility Timeout Functions
	\ingroup    TLPM_METHODS_UTILITY_x
	\brief      The Timeout class groups functions to set the communication timeouts for the USB and serial interfaces.
	@{
	*//*=========================================================================*/ 
	ViStatus _VI_FUNC TLPMX_setTimeoutValue (ViSession vi, ViUInt32  value);
	ViStatus _VI_FUNC TLPMX_getTimeoutValue (ViSession vi, ViPUInt32 value); 
	/**@}*/  /* TLPM_METHODS_UTILITY_TIMEOUT_x */ 

/**@}*/  /* TLPM_METHODS_UTILITY_x */ 
	
/*========================================================================*//**
\defgroup   TLPM_METHODS_ETHERNET_INTERFACE_x Attributes Functions
\ingroup    TLPM_METHODS_x
\brief      This class of functions provides functions to change the baudrate for the serial communication in the instrument and on PC side.
@{
*//*=========================================================================*/ 
ViStatus _VI_FUNC TLPMX_setIPAddress (ViSession vi, ViChar IPAddress[]);
ViStatus _VI_FUNC TLPMX_getIPAddress (ViSession vi, ViChar IPAddress[]);
ViStatus _VI_FUNC TLPMX_setIPMask (ViSession vi, ViChar IPMask[]);
ViStatus _VI_FUNC TLPMX_getIPMask (ViSession vi, ViChar IPMask[]);
ViStatus _VI_FUNC TLPMX_getMACAddress (ViSession vi, ViChar MACAddress[]);
ViStatus _VI_FUNC TLPMX_setDHCP (ViSession vi, ViChar DHCP[]);
ViStatus _VI_FUNC TLPMX_getDHCP (ViSession vi, ViChar DHCP[]);
ViStatus _VI_FUNC TLPMX_setHostname (ViSession vi, ViChar hostname[]);
ViStatus _VI_FUNC TLPMX_getHostname (ViSession vi, ViChar hostname[]);
ViStatus _VI_FUNC TLPMX_setWebPort (ViSession vi, ViUInt32 port);
ViStatus _VI_FUNC TLPMX_getWebPort (ViSession vi, ViPUInt32 port);
ViStatus _VI_FUNC TLPMX_setSCPIPort (ViSession vi, ViUInt32 port);
ViStatus _VI_FUNC TLPMX_getSCPIPort (ViSession vi, ViPUInt32 port);
ViStatus _VI_FUNC TLPMX_setDFUPort (ViSession vi, ViUInt32 port);
ViStatus _VI_FUNC TLPMX_getDFUPort (ViSession vi, ViPUInt32 port);
/**@}*/  /* TLPM_METHODS_ETHERNET_INTERFACE_x */   

/*========================================================================*//**
\defgroup   TLPM_METHODS_SERIAL_INTERFACE_x Attributes Functions
\ingroup    TLPM_METHODS_x
\brief      This class of functions provides functions to change the baudrate for the serial communication in the instrument and on PC side.
@{
*//*=========================================================================*/ 
ViStatus _VI_FUNC TLPMX_setDeviceBaudrate (ViSession vi, ViUInt32 baudrate);  
ViStatus _VI_FUNC TLPMX_getDeviceBaudrate (ViSession vi, ViPUInt32 baudrate);

ViStatus _VI_FUNC TLPMX_setDriverBaudrate (ViSession vi, ViUInt32 baudrate);  
ViStatus _VI_FUNC TLPMX_getDriverBaudrate (ViSession vi, ViPUInt32 baudrate);
/**@}*/  /* TLPM_METHODS_SERIAL_INTERFACE_x */   

/**@}*/  /* TLPM_METHODS_x */	


#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif

#endif   /* _TLPM_DRIVER_HEADER_ */

/*- The End -----------------------------------------------------------------*/
