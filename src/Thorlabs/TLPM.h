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

// find any PM100/PM160/PM200 with USB interface
#define PMxxx_FIND_PATTERN            "USB?*INSTR{VI_ATTR_MANF_ID==0x1313 && (VI_ATTR_MODEL_CODE==0x8070 || VI_ATTR_MODEL_CODE==0x8078 || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8071 || VI_ATTR_MODEL_CODE==0x8079 || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8072 || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8073 || VI_ATTR_MODEL_CODE==0x807B || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8074 || VI_ATTR_MODEL_CODE==0x807C || " \
                                                                             "VI_ATTR_MODEL_CODE==0x8075 || VI_ATTR_MODEL_CODE==0x807D || " \
																			 "VI_ATTR_MODEL_CODE==0x8076 || VI_ATTR_MODEL_CODE==0x807E || " \
																			 "VI_ATTR_MODEL_CODE==0x8077 || VI_ATTR_MODEL_CODE==0x807F || " \
																			 "VI_ATTR_MODEL_CODE==0x807A || " \
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
ViStatus _VI_FUNC TLPM_init (ViRsrc resourceName, ViBoolean IDQuery, ViBoolean resetDevice, ViPSession vi); 
ViStatus _VI_FUNC TLPM_close (ViSession vi);   

/*========================================================================*//**
\defgroup   TLPM_METHODS_RM_x Resource Manager TLVISA library functions
\ingroup    TLPM_METHODS_x
\brief      Functions provided by TLVISA library for managing resources, e.g. finding resources.
@{
*//*=========================================================================*/
ViStatus _VI_FUNC TLPM_findRsrc (ViSession vi, ViPUInt32 resourceCount);
ViStatus _VI_FUNC TLPM_getRsrcName (ViSession vi, ViUInt32 index, ViChar resourceName[]);
ViStatus _VI_FUNC TLPM_getRsrcInfo (ViSession vi, ViUInt32 index, ViChar modelName[], ViChar serialNumber[], ViChar manufacturer[], ViPBoolean deviceAvailable);
/**@}*/  /* TLPM_METHODS_RM_x */

/*========================================================================*//**
\defgroup   TLPM_STATUS_REGISTER_x Resource Manager TLVISA library functions
\ingroup    TLPM_METHODS_x
\brief      Functions provided by TLVISA library for managing the status flags
@{
*//*=========================================================================*/
ViStatus _VI_FUNC TLPM_writeRegister (ViSession vi, ViInt16 reg, ViInt16 value);
ViStatus _VI_FUNC TLPM_readRegister (ViSession vi, ViInt16 reg, ViPInt16 value);
ViStatus _VI_FUNC TLPM_presetRegister (ViSession vi);

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
	ViStatus _VI_FUNC TLPM_setTime (ViSession vi, ViInt16  year, ViInt16  month, ViInt16  day, ViInt16  hour, ViInt16 minute, ViInt16  second);
	ViStatus _VI_FUNC TLPM_getTime (ViSession vi, ViPInt16 year, ViPInt16 month, ViPInt16 day, ViPInt16 hour, ViPInt16 minute, ViPInt16 second);
	/**@}*/  /* TLPM_METHODS_SYSTEM_DATE_TIME_x */  

	/*========================================================================*//**
	\defgroup   TLPM_METHODS_SYSTEM_LINE_FREQUENCY_x System Line Frequency Functions
	\ingroup    TLPM_METHODS_SYSTEM_x
	\brief      Line frequency setup.
	@{
	*//*=========================================================================*/
	ViStatus _VI_FUNC TLPM_setLineFrequency (ViSession vi, ViInt16  lineFrequency);
	ViStatus _VI_FUNC TLPM_getLineFrequency (ViSession vi, ViPInt16 lineFrequency);

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
	ViStatus _VI_FUNC TLPM_getBatteryVoltage (ViSession vi, ViPReal64 voltage);   
	/**@}*/  /* TLPM_METHODS_SYSTEM_BATTERY_x */  

	/*========================================================================*//**
	\defgroup   TLPM_METHODS_SYSTEM_DISPLAY_x System Display Functions
	\ingroup    TLPM_METHODS_SYSTEM_x
	\brief      The Display class groups functions for display control.
	@{
	*//*=========================================================================*/
	ViStatus _VI_FUNC TLPM_setDispBrightness (ViSession vi, ViReal64 val);
	ViStatus _VI_FUNC TLPM_getDispBrightness (ViSession vi, ViPReal64 pVal);

	ViStatus _VI_FUNC TLPM_setDispContrast (ViSession vi, ViReal64 val);
	ViStatus _VI_FUNC TLPM_getDispContrast (ViSession vi, ViPReal64 pVal);
	/**@}*/  /* TLPM_METHODS_SYSTEM_DISPLAY_x */ 

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
		ViStatus _VI_FUNC TLPM_setInputFilterState (ViSession vi, ViBoolean inputFilterState);
		ViStatus _VI_FUNC TLPM_getInputFilterState (ViSession vi, ViPBoolean inputFilterState);
			/*========================================================================*//**
			\defgroup   TLPM_INPUT_FILTER_FLAGS_x  Input Filter Flags
			\ingroup    TLPM_MACROS_x
			@{
			*//*=========================================================================*/
			#define TLPM_INPUT_FILTER_STATE_OFF  (0)
			#define TLPM_INPUT_FILTER_STATE_ON   (1)
			/**@}*/  /* TLPM_INPUT_FILTER_FLAGS_x */ 

		ViStatus _VI_FUNC TLPM_setAccelState (ViSession vi, ViBoolean accelState);
		ViStatus _VI_FUNC TLPM_getAccelState (ViSession vi, ViPBoolean accelState);

			/*========================================================================*//**
			\defgroup   TLPM_INPUT_ACCELERATION_STATES_x  Input Accelerateion Flags
			\ingroup    TLPM_MACROS_x
			@{
				*//*=========================================================================*/
			#define TLPM_ACCELERATION_STATE_OFF  (0)
			#define TLPM_ACCELERATION_STATE_ON   (1)
			/**@}*/  /* TLPM_INPUT_ACCELERATION_STATES_x */  

		ViStatus _VI_FUNC TLPM_setAccelMode (ViSession vi, ViBoolean accelMode);
		ViStatus _VI_FUNC TLPM_getAccelMode (ViSession vi, ViPBoolean accelMode);
		
			/*========================================================================*//**
			\defgroup   TLPM_INPUT_ACCELERATION_MODES_x  Input Filter Flags
			\ingroup    TLPM_MACROS_x
			@{
			*//*=========================================================================*/  
			#define TLPM_ACCELERATION_MANUAL     (0)
			#define TLPM_ACCELERATION_AUTO       (1)
			/**@}*/  /* TLPM_INPUT_ACCELERATION_MODES_x */   


		ViStatus _VI_FUNC TLPM_setAccelTau (ViSession vi, ViReal64 accelTau);
		ViStatus _VI_FUNC TLPM_getAccelTau (ViSession vi, ViInt16 attribute, ViPReal64 accelTau);

		ViStatus _VI_FUNC TLPM_setInputAdapterType (ViSession vi, ViInt16 type);
		ViStatus _VI_FUNC TLPM_getInputAdapterType (ViSession vi, ViPInt16 type);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_INPUT_x */  
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_AVERAGE_x Measure Configure Average Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the measurement averaging of the instrument.
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPM_setAvgTime (ViSession vi, ViReal64 avgTime);
		ViStatus _VI_FUNC TLPM_getAvgTime (ViSession vi, ViInt16 attribute, ViPReal64 avgTime);

		ViStatus _VI_FUNC TLPM_setAvgCnt (ViSession vi, ViInt16 averageCount);
		ViStatus _VI_FUNC TLPM_getAvgCnt (ViSession vi, ViPInt16 averageCount);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_AVERAGE_x */ 
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_CORRECTION_x Measure Configure Correction Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the input corrections of the instrument.
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPM_setAttenuation (ViSession vi, ViReal64 attenuation);
		ViStatus _VI_FUNC TLPM_getAttenuation (ViSession vi, ViInt16 attribute, ViPReal64 attenuation);
		
		ViStatus _VI_FUNC TLPM_startDarkAdjust (ViSession vi);
		ViStatus _VI_FUNC TLPM_cancelDarkAdjust (ViSession vi);
		ViStatus _VI_FUNC TLPM_getDarkAdjustState (ViSession vi, ViPInt16 state);
		ViStatus _VI_FUNC TLPM_getDarkOffset (ViSession vi, ViPReal64 darkOffset);

		/*========================================================================*//**
		\defgroup   TLPM_STAT_DARK_ADJUST_FLAGS_x  Dark adjustment status flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_STAT_DARK_ADJUST_FINISHED  (0)
		#define TLPM_STAT_DARK_ADJUST_RUNNING   (1)
		/**@}*/  /* TLPM_STAT_DARK_ADJUST_FLAGS_x */ 
		
		ViStatus _VI_FUNC TLPM_setBeamDia (ViSession vi, ViReal64 beamDiameter);
		ViStatus _VI_FUNC TLPM_getBeamDia (ViSession vi, ViInt16 attribute, ViPReal64 beamDiameter);
		
		ViStatus _VI_FUNC TLPM_setWavelength (ViSession vi, ViReal64 wavelength);
		ViStatus _VI_FUNC TLPM_getWavelength (ViSession vi, ViInt16 attribute, ViPReal64 wavelength);

		ViStatus _VI_FUNC TLPM_setPhotodiodeResponsivity (ViSession vi, ViReal64 response);
		ViStatus _VI_FUNC TLPM_getPhotodiodeResponsivity (ViSession vi, ViInt16 attribute, ViPReal64 responsivity);
		
		ViStatus _VI_FUNC TLPM_setThermopileResponsivity (ViSession vi, ViReal64 response);
		ViStatus _VI_FUNC TLPM_getThermopileResponsivity (ViSession vi, ViInt16 attribute, ViPReal64 responsivity);

		ViStatus _VI_FUNC TLPM_setPyrosensorResponsivity (ViSession vi, ViReal64 response);
		ViStatus _VI_FUNC TLPM_getPyrosensorResponsivity (ViSession vi, ViInt16 attribute, ViPReal64 responsivity);

		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_CORRECTION_x */    
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_CURRENT_MEASUREMENT_x Measure Configure Current Measurement Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles current measurement related items of the instrument. 
		\details	This set of functions is only useable with sensor types that produce an electrical current as measurement value (Photodiodes).
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPM_setCurrentAutoRange (ViSession vi, ViBoolean currentAutorangeMode);
		ViStatus _VI_FUNC TLPM_getCurrentAutorange (ViSession vi, ViPBoolean currentAutorangeMode);

		/*========================================================================*//**
		\defgroup   TLPM_AUTORANGE_CURRENT_FLAGS_x  Auto Current status flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_AUTORANGE_CURRENT_OFF  (0)
		#define TLPM_AUTORANGE_CURRENT_ON   (1)
		/**@}*/  /* TLPM_AUTORANGE_CURRENT_FLAGS_x */ 
		
		ViStatus _VI_FUNC TLPM_setCurrentRange (ViSession vi, ViReal64 current_to_Measure);
		ViStatus _VI_FUNC TLPM_getCurrentRange (ViSession vi, ViInt16 attribute, ViPReal64 currentValue);
		ViStatus _VI_FUNC TLPM_getCurrentRanges (ViSession instr, ViReal64 currentValues[], ViPUInt16 rangeCount);
		
		ViStatus _VI_FUNC TLPM_setCurrentRef (ViSession vi, ViReal64 currentReferenceValue);
		ViStatus _VI_FUNC TLPM_getCurrentRef (ViSession vi, ViInt16 attribute, ViPReal64 currentReferenceValue);
		
		ViStatus _VI_FUNC TLPM_setCurrentRefState (ViSession vi, ViBoolean currentReferenceState);
		ViStatus _VI_FUNC TLPM_getCurrentRefState (ViSession vi, ViPBoolean currentReferenceState);

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
		ViStatus _VI_FUNC TLPM_setEnergyRange (ViSession vi, ViReal64 energyToMeasure);
		ViStatus _VI_FUNC TLPM_getEnergyRange (ViSession vi, ViInt16 attribute, ViPReal64 energyValue);

		ViStatus _VI_FUNC TLPM_setEnergyRef (ViSession vi, ViReal64 energyReferenceValue);
		ViStatus _VI_FUNC TLPM_getEnergyRef (ViSession vi, ViInt16 attribute, ViPReal64 energyReferenceValue);

		ViStatus _VI_FUNC TLPM_setEnergyRefState (ViSession vi, ViBoolean energyReferenceState);
		ViStatus _VI_FUNC TLPM_getEnergyRefState (ViSession vi, ViPBoolean energyReferenceState);

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
		ViStatus _VI_FUNC TLPM_getFreqRange (ViSession vi, ViPReal64 lowerFrequency, ViPReal64 upperFrequency); 		
		
		/*========================================================================*//**
		\defgroup   TLPM_FREQ_MODE_FLAGS_x  Freq mode flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_FREQ_MODE_CW  	(0)
		#define TLPM_FREQ_MODE_PEAK	(1)
		/**@}*/  /* TLPM_AUTO_RANGE_FLAGS_x */ 		
		
		ViStatus _VI_FUNC TLPM_setFreqMode (ViSession vi, ViUInt16 frequencyMode);
		ViStatus _VI_FUNC TLPM_getFreqMode (ViSession vi, ViPUInt16 frequencyMode);
		
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_FREQUENCY_MEASUREMENT_x */ 
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_POWER_MEASUREMENT_x Measure Configure Power Measurement Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles power measurement related items of the instrument.
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPM_setPowerAutoRange (ViSession vi, ViBoolean powerAutorangeMode);
		ViStatus _VI_FUNC TLPM_getPowerAutorange (ViSession vi, ViPBoolean powerAutorangeMode);

		/*========================================================================*//**
		\defgroup   TLPM_AUTO_RANGE_FLAGS_x  Auto range mode flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_AUTORANGE_POWER_OFF  (0)
		#define TLPM_AUTORANGE_POWER_ON   (1)
		/**@}*/  /* TLPM_AUTO_RANGE_FLAGS_x */   
		
		ViStatus _VI_FUNC TLPM_setPowerRange (ViSession vi, ViReal64 power_to_Measure);
		ViStatus _VI_FUNC TLPM_getPowerRange (ViSession vi, ViInt16 attribute, ViPReal64 powerValue);

		ViStatus _VI_FUNC TLPM_setPowerRef (ViSession vi, ViReal64 powerReferenceValue);
		ViStatus _VI_FUNC TLPM_getPowerRef (ViSession vi, ViInt16 attribute, ViPReal64 powerReferenceValue);

		ViStatus _VI_FUNC TLPM_setPowerRefState (ViSession vi, ViBoolean powerReferenceState);
		ViStatus _VI_FUNC TLPM_getPowerRefState (ViSession vi, ViPBoolean powerReferenceState);

		/*========================================================================*//**
		\defgroup   TLPM_POWER_REFERENCE_FLAGS_x  Power reference status flags
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_POWER_REF_OFF  (0)
		#define TLPM_POWER_REF_ON   (1)
		/**@}*/  /* TLPM_POWER_REFERENCE_FLAGS_x */ 

		ViStatus _VI_FUNC TLPM_setPowerUnit (ViSession vi, ViInt16 powerUnit);
		ViStatus _VI_FUNC TLPM_getPowerUnit (ViSession vi, ViPInt16 powerUnit);

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
		
		ViStatus _VI_FUNC TLPM_getPowerCalibrationPointsInformation (ViSession vi, ViUInt16 index, ViChar serialNumber[], ViChar calibrationDate[], ViPUInt16 calibrationPointsCount, ViChar author[], ViPUInt16 sensorPosition);

		ViStatus _VI_FUNC TLPM_getPowerCalibrationPointsState (ViSession vi, ViUInt16 index,ViPBoolean state); 
		ViStatus _VI_FUNC TLPM_setPowerCalibrationPointsState (ViSession vi, ViUInt16 index, ViBoolean state);

		ViStatus _VI_FUNC TLPM_getPowerCalibrationPoints (ViSession vi, ViUInt16 index, ViUInt16 pointCounts, ViReal64 wavelengths[], ViReal64 powerCorrectionFactors[]);
		ViStatus _VI_FUNC TLPM_setPowerCalibrationPoints (ViSession vi, ViUInt16 index, ViUInt16 pointCounts, ViReal64 wavelengths[], ViReal64 powerCorrectionFactors[], ViChar author[], ViUInt16 sensorPosition);
		
		ViStatus _VI_FUNC TLPM_reinitSensor (ViSession vi);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_USER_POWER_CALIBRATION_x */ 
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_VOLTAGE_MEASUREMENT_x Measure Configure Voltage Measurement Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles voltage measurement related items of the instrument. 
		\details	This set of functions is only useable with sensor types that produce an electrical voltage as measurement value (Thermopile sensors and pyroelectric sensors).
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPM_setVoltageAutoRange (ViSession vi, ViBoolean voltageAutorangeMode);
		ViStatus _VI_FUNC TLPM_getVoltageAutorange (ViSession vi, ViPBoolean voltageAutorangeMode);

		/*========================================================================*//**
		\defgroup   TLPM_VOLTAGE_AUTO_RANGE_STATE_x  Voltage Auto Range status
		\ingroup    TLPM_MACROS_x
		@{
		*//*=========================================================================*/
		#define TLPM_AUTORANGE_VOLTAGE_OFF  (0)
		#define TLPM_AUTORANGE_VOLTAGE_ON   (1)
		/**@}*/  /* TLPM_VOLTAGE_AUTO_RANGE_STATE_x */ 

		ViStatus _VI_FUNC TLPM_setVoltageRange (ViSession vi, ViReal64 voltage_to_Measure);
		ViStatus _VI_FUNC TLPM_getVoltageRange (ViSession vi, ViInt16 attribute, ViPReal64 voltageValue);
		ViStatus _VI_FUNC TLPM_getVoltageRanges (ViSession vi, ViReal64 voltageValues[], ViPUInt16 rangeCount);

		ViStatus _VI_FUNC TLPM_setVoltageRef (ViSession vi, ViReal64 voltageReferenceValue);
		ViStatus _VI_FUNC TLPM_getVoltageRef (ViSession vi, ViInt16 attribute, ViPReal64 voltageReferenceValue);

		ViStatus _VI_FUNC TLPM_setVoltageRefState (ViSession vi, ViBoolean voltageReferenceState);
		ViStatus _VI_FUNC TLPM_getVoltageRefState (ViSession vi, ViPBoolean voltageReferenceState);

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
		ViStatus _VI_FUNC TLPM_setPeakThreshold (ViSession vi, ViReal64 peakThreshold);
		ViStatus _VI_FUNC TLPM_getPeakThreshold (ViSession vi, ViInt16 attribute, ViPReal64 peakThreshold);
		ViStatus _VI_FUNC TLPM_startPeakDetector (ViSession vi);
		ViStatus _VI_FUNC TLPM_isPeakDetectorRunning (ViSession vi, ViPBoolean isRunning);
		ViStatus _VI_FUNC TLPM_setPeakFilter(ViSession vi, ViInt16 filter);
		ViStatus _VI_FUNC TLPM_getPeakFilter(ViSession vi, ViPInt16 filter);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_PEAK_DETECTOR_x */ 
		
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_EXTERNAL_TEMPERATURE_SENSOR_x Measure Configure External Temperature Sensor Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the external temperature sensor connected to the instrument.
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPM_setExtNtcParameter (ViSession vi, ViReal64 r0Coefficient, ViReal64 betaCoefficient);
		ViStatus _VI_FUNC TLPM_getExtNtcParameter (ViSession vi, ViInt16 attribute, ViPReal64 r0Coefficient, ViPReal64 betaCoefficient);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_EXTERNAL_TEMPERATURE_SENSOR_x */ 
		
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_FILTER_POSITION_x Measure Configure Filter Position Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the filter position detection
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPM_setFilterPosition (ViSession vi, ViBoolean filterPosition);  
		ViStatus _VI_FUNC TLPM_getFilterPosition (ViSession vi, ViPBoolean filterPosition);  
		ViStatus _VI_FUNC TLPM_setFilterAutoMode (ViSession vi, ViBoolean filterAutoPositionDetection);  
		ViStatus _VI_FUNC TLPM_getFilterAutoMode (ViSession vi, ViPBoolean filterAutoPositionDetection);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_FILTER_POSITION_x */  
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_ANALOG_OUTPUT_x Measure Configure Filter Position Functions
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the filter position detection
		@{
		*//*=========================================================================*/
		ViStatus _VI_FUNC TLPM_getAnalogOutputSlopeRange (ViSession vi, ViPReal64 minSlope, ViPReal64 maxSlope);  
		ViStatus _VI_FUNC TLPM_setAnalogOutputSlope (ViSession vi, ViReal64 slope);		 
		ViStatus _VI_FUNC TLPM_getAnalogOutputSlope (ViSession vi, ViInt16 attribute, ViPReal64 slope);

		ViStatus _VI_FUNC TLPM_getAnalogOutputVoltageRange (ViSession vi, ViPReal64 minVoltage, ViPReal64 maxVoltage); 
		ViStatus _VI_FUNC TLPM_getAnalogOutputVoltage (ViSession vi, ViInt16 attribute,  ViPReal64 voltage);
		
		ViStatus _VI_FUNC TLPM_getAnalogOutputHub (ViSession vi, ViPReal64 voltage);
		ViStatus _VI_FUNC TLPM_setAnalogOutputHub (ViSession vi, ViReal64 voltage);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_ANALOG_OUTPUT_x */
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_POSITION_ANALOG_OUTPUT_x Measure Configure Position Analog Output
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the analog output for the position
		@{
		*//*=========================================================================*/	
		ViStatus _VI_FUNC TLPM_getPositionAnalogOutputSlopeRange (ViSession vi, ViPReal64 minSlope, ViPReal64 maxSlope);	  
		ViStatus _VI_FUNC TLPM_setPositionAnalogOutputSlope (ViSession vi, ViReal64 slope);   
		ViStatus _VI_FUNC TLPM_getPositionAnalogOutputSlope (ViSession vi, ViInt16 attribute, ViPReal64 slope);

		ViStatus _VI_FUNC TLPM_getPositionAnalogOutputVoltageRange (ViSession vi, ViPReal64 minVoltage, ViPReal64 maxVoltage);  
		ViStatus _VI_FUNC TLPM_getPositionAnalogOutputVoltage (ViSession vi, ViInt16 attribute, ViPReal64 voltageX, ViPReal64 voltageY);

		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_POSITION_ANALOG_OUTPUT_x */  
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_MEASUREMENT_PIN_OUTPUT_x Measure Configure Position Analog Output
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the analog output for the position
		@{
		*//*=========================================================================*/	
		ViStatus _VI_FUNC TLPM_getMeasPinMode (ViSession vi, ViPBoolean state);

		ViStatus _VI_FUNC TLPM_getMeasPinPowerLevel (ViSession vi, ViPReal64 level);
		ViStatus _VI_FUNC TLPM_setMeasPinPowerLevel (ViSession vi, ViReal64 level);

		ViStatus _VI_FUNC TLPM_getMeasPinEnergyLevel (ViSession vi, ViPReal64 level);
		ViStatus _VI_FUNC TLPM_setMeasPinEnergyLevel (ViSession vi, ViReal64 level);
		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_MEASUREMENT_PIN_OUTPUT_x */  
		
		/*========================================================================*//**
		\defgroup   TLPM_METHODS_MEASURE_CONFIGURE_PULSE_x Measure Configure Pulse
		\ingroup    TLPM_METHODS_MEASURE_CONFIGURE_x
		\brief      This class of functions handles the settings for the pulse measurements
		@{
		*//*=========================================================================*/	
		ViStatus _VI_FUNC TLPM_setNegativePulseWidth (ViSession vi, ViReal64 pulseDuration);
		ViStatus _VI_FUNC TLPM_setPositivePulseWidth (ViSession vi, ViReal64 pulseDuration);
		ViStatus _VI_FUNC TLPM_setNegativeDutyCycle (ViSession vi, ViReal64 dutyCycle);
		ViStatus _VI_FUNC TLPM_setPositiveDutyCycle (ViSession vi, ViReal64 dutyCycle);

		/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_PULSE_x */  
		
	/**@}*/  /* TLPM_METHODS_MEASURE_CONFIGURE_x */  
	
	/*========================================================================*//**
	\defgroup   TLPM_METHODS_MEASURE_READ_x Measure Read Functions
	\ingroup    TLPM_METHODS_MEASURE_x
	\brief      The Read class contains functions to read measurement results from the instrument.
	@{
	*//*=========================================================================*/ 
	ViStatus _VI_FUNC TLPM_measCurrent (ViSession vi, ViPReal64 current);
	ViStatus _VI_FUNC TLPM_measVoltage (ViSession vi, ViPReal64 voltage);
	ViStatus _VI_FUNC TLPM_measPower (ViSession vi, ViPReal64 power);
	ViStatus _VI_FUNC TLPM_measEnergy (ViSession vi, ViPReal64 energy);
	ViStatus _VI_FUNC TLPM_measFreq (ViSession vi, ViPReal64 frequency);
	ViStatus _VI_FUNC TLPM_measPowerDens (ViSession vi, ViPReal64 powerDensity);
	ViStatus _VI_FUNC TLPM_measEnergyDens (ViSession vi, ViPReal64 energyDensity);
	ViStatus _VI_FUNC TLPM_measAuxAD0 (ViSession vi, ViPReal64 voltage);
	ViStatus _VI_FUNC TLPM_measAuxAD1 (ViSession vi, ViPReal64 voltage);
	ViStatus _VI_FUNC TLPM_measEmmHumidity (ViSession vi, ViPReal64 humidity);
	ViStatus _VI_FUNC TLPM_measEmmTemperature (ViSession vi, ViPReal64 temperature);
	ViStatus _VI_FUNC TLPM_measExtNtcTemperature (ViSession vi, ViPReal64 temperature);
	ViStatus _VI_FUNC TLPM_measExtNtcResistance (ViSession vi, ViPReal64 resistance);
	ViStatus _VI_FUNC TLPM_meas4QPositions (ViSession vi, ViPReal64 xPosition, ViPReal64 yPosition);
	ViStatus _VI_FUNC TLPM_meas4QVoltages (ViSession vi, ViPReal64 voltage1, ViPReal64 voltage2, ViPReal64 voltage3, ViPReal64 voltage4);
	ViStatus _VI_FUNC TLPM_measNegPulseWidth (ViSession vi, ViPReal64 negativePulseWidth);
	ViStatus _VI_FUNC TLPM_measPosPulseWidth (ViSession vi, ViPReal64 positivePulseWidth);
	ViStatus _VI_FUNC TLPM_measNegDutyCycle (ViSession vi, ViPReal64 negativeDutyCycle);
	ViStatus _VI_FUNC TLPM_measPosDutyCycle (ViSession vi, ViPReal64 positiveDutyCycle);
	/**@}*/  /* TLPM_METHODS_MEASURE_READ_x */ 
	
	
	/*========================================================================*//**
	\defgroup   TLPM_METHODS_ARRAY_MEASUREMENTS_x Arrey Measurements Functions
	\ingroup    TLPM_METHODS_MEASURE_x
	\brief      The Read class contains functions to read measurement results from the instrument.
	@{

	*//*=========================================================================*/ 
	ViStatus _VI_FUNC TLPM_resetFastArrayMeasurement 		(ViSession vi);
	ViStatus _VI_FUNC TLPM_confPowerFastArrayMeasurement 	(ViSession vi);
	ViStatus _VI_FUNC TLPM_confCurrentFastArrayMeasurement 	(ViSession vi);
	ViStatus _VI_FUNC TLPM_confVoltageFastArrayMeasurement 	(ViSession vi);
	ViStatus _VI_FUNC TLPM_confPDensityFastArrayMeasurement (ViSession vi);
	ViStatus _VI_FUNC TLPM_confEnergyFastArrayMeasurement 	(ViSession vi);
	ViStatus _VI_FUNC TLPM_confEDensityFastArrayMeasurement (ViSession vi);
	ViStatus _VI_FUNC TLPM_getNextFastArrayMeasurement 		(ViSession vi, ViPUInt16 count, ViUInt32 timestamps[], ViReal32 values[]);
	ViStatus _VI_FUNC TLPM_getFastMaxSamplerate (ViSession vi, ViPUInt32 pVal);
	
	ViStatus _VI_FUNC TLPM_confPowerMeasurementSequence 			(ViSession vi, ViUInt32 baseTime);
	ViStatus _VI_FUNC TLPM_confPowerMeasurementSequenceHWTrigger 	(ViSession vi, ViUInt32 baseTime, ViUInt32 hPos);
	ViStatus _VI_FUNC TLPM_confCurrentMeasurementSequence 			(ViSession vi, ViUInt32 baseTime);
	ViStatus _VI_FUNC TLPM_confCurrentMeasurementSequenceHWTrigger 	(ViSession vi, ViUInt32 baseTime, ViUInt32 hPos);
	ViStatus _VI_FUNC TLPM_startMeasurementSequence(ViSession vi, ViUInt32 autoTriggerDelay, ViPBoolean triggerForced);

	ViStatus _VI_FUNC TLPM_getMeasurementSequence(ViSession vi, ViUInt32 baseTime, ViReal32 timeStamps[], ViReal32 values[]);
	ViStatus _VI_FUNC TLPM_getMeasurementSequenceHWTrigger(ViSession vi, ViUInt32 baseTime, ViReal32 timeStamps[], ViReal32 values[]);

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

ViStatus _VI_FUNC TLPM_setDigIoDirection (ViSession vi, ViBoolean IO0, ViBoolean IO1, ViBoolean IO2, ViBoolean IO3);
ViStatus _VI_FUNC TLPM_getDigIoDirection (ViSession vi, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);

/*========================================================================*//**
\defgroup   TLPM_IODIR_STATE_x  Digital IO status
\ingroup    TLPM_MACROS_x
@{
*//*=========================================================================*/
#define TLPM_IOLVL_LOW   (VI_OFF)
#define TLPM_IOLVL_HIGH  (VI_ON)
/**@}*/  /* TLPM_IODIR_STATE_x */ 

ViStatus _VI_FUNC TLPM_setDigIoOutput (ViSession vi, ViBoolean IO0, ViBoolean IO1, ViBoolean IO2, ViBoolean IO3);
ViStatus _VI_FUNC TLPM_getDigIoOutput (ViSession vi, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);

ViStatus _VI_FUNC TLPM_getDigIoPort (ViSession vi, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);

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

ViStatus _VI_FUNC TLPM_setDigIoPinMode (ViSession vi, ViInt16 pinNumber, ViUInt16 pinMode);
ViStatus _VI_FUNC TLPM_getDigIoPinMode (ViSession vi, ViInt16 pinNumber, ViPUInt16 pinMode);

ViStatus _VI_FUNC TLPM_setDigIoOutput (ViSession vi, ViBoolean IO0, ViBoolean IO1, ViBoolean IO2, ViBoolean IO3);
ViStatus _VI_FUNC TLPM_getDigIoOutput (ViSession vi, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);

ViStatus _VI_FUNC TLPM_getDigIoPinInput (ViSession vi, ViPBoolean IO0, ViPBoolean IO1, ViPBoolean IO2, ViPBoolean IO3);
/**@}*/  /* TLPM_METHODS_DIGITAL_IO_PIN_x */ 

/*========================================================================*//**
\defgroup   TLPM_METHODS_UTILITY_x Utility Functions
\ingroup    TLPM_METHODS_x
\brief      This class of functions provides utility and lower level functions to communicate with the instrument.
@{
*//*=========================================================================*/ 
ViStatus _VI_FUNC TLPM_errorMessage (ViSession vi, ViStatus statusCode, ViChar _VI_FAR description[]); 
ViStatus _VI_FUNC TLPM_errorQuery (ViSession vi, ViPInt32 errorNumber, ViChar _VI_FAR errorMessage[]); 
ViStatus _VI_FUNC TLPM_errorQueryMode (ViSession vi, ViBoolean mode);   
ViStatus _VI_FUNC TLPM_reset (ViSession vi);  
ViStatus _VI_FUNC TLPM_selfTest (ViSession vi, ViPInt16 selfTestResult, ViChar _VI_FAR description[]);   
ViStatus _VI_FUNC TLPM_revisionQuery (ViSession vi, ViChar _VI_FAR instrumentDriverRevision[], ViChar _VI_FAR firmwareRevision[]);  
ViStatus _VI_FUNC TLPM_identificationQuery (ViSession vi, ViChar _VI_FAR manufacturerName[], ViChar _VI_FAR deviceName[], ViChar _VI_FAR serialNumber[], ViChar _VI_FAR firmwareRevision[]);
ViStatus _VI_FUNC TLPM_getCalibrationMsg (ViSession vi, ViChar _VI_FAR message[]);
ViStatus _VI_FUNC TLPM_setDisplayName (ViSession vi, ViChar _VI_FAR name[]);
ViStatus _VI_FUNC TLPM_getDisplayName (ViSession vi, ViChar _VI_FAR name[]);

ViStatus _VI_FUNC TLPM_getSensorInfo (ViSession vi, ViChar _VI_FAR name[], ViChar _VI_FAR snr[], ViChar _VI_FAR message[], ViPInt16 pType, ViPInt16 pStype, ViPInt16 pFlags);

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
	ViStatus _VI_FUNC TLPM_writeRaw (ViSession vi, ViString command); 
	ViStatus _VI_FUNC TLPM_readRaw (ViSession vi, ViChar _VI_FAR buffer[], ViUInt32 size, ViPUInt32 returnCount);
	/**@}*/  /* TLPM_METHODS_UTILITY_RAW_IO_x */  
	
	/*========================================================================*//**
	\defgroup   TLPM_METHODS_UTILITY_TIMEOUT_x Utility Timeout Functions
	\ingroup    TLPM_METHODS_UTILITY_x
	\brief      The Timeout class groups functions to set the communication timeouts for the USB and serial interfaces.
	@{
	*//*=========================================================================*/ 
	ViStatus _VI_FUNC TLPM_setTimeoutValue (ViSession vi, ViUInt32  value);
	ViStatus _VI_FUNC TLPM_getTimeoutValue (ViSession vi, ViPUInt32 value); 
	/**@}*/  /* TLPM_METHODS_UTILITY_TIMEOUT_x */ 

/**@}*/  /* TLPM_METHODS_UTILITY_x */ 

/*========================================================================*//**
\defgroup   TLPM_METHODS_ATTRIBUTES_x Attributes Functions
\ingroup    TLPM_METHODS_x
\brief      This class of functions provides functions to change the baudrate for the serial communication in the instrument and on PC side.
@{
*//*=========================================================================*/ 
ViStatus _VI_FUNC TLPM_setDeviceBaudrate (ViSession vi, ViUInt32 baudrate);  
ViStatus _VI_FUNC TLPM_getDeviceBaudrate (ViSession vi, ViPUInt32 baudrate);

ViStatus _VI_FUNC TLPM_setDriverBaudrate (ViSession vi, ViUInt32 baudrate);  
ViStatus _VI_FUNC TLPM_getDriverBaudrate (ViSession vi, ViPUInt32 baudrate);
/**@}*/  /* TLPM_METHODS_ATTRIBUTES_x */   

/**@}*/  /* TLPM_METHODS_x */	


#if defined(__cplusplus) || defined(__cplusplus__)
}
#endif

#endif   /* _TLPM_DRIVER_HEADER_ */

/*- The End -----------------------------------------------------------------*/
