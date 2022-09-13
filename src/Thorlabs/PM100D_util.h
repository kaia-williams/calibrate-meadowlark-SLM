//==============================================================================
//
// Title:      PM100D_util.h
// Purpose:    A short description of the interface.
//
// Created on: 30.06.2016 at 15:57:46 by tempinstall.
// Copyright:  . All Rights Reserved.
//
//==============================================================================

#ifndef __PM100D_util_H__
#define __PM100D_util_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

#include "visa.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

/*------------------------------------------------------------------------*//**
\brief   Check if an USB device is supported by this driver.
\param[in] vid USB vendor id
\param[in] pid USB product id
\return  VI_SUCCESS if the device is supported. VI_ERROR_FAIL_ID_QUERY if the 
         device is not supported.
*//*-------------------------------------------------------------------------*/
ViStatus util_checkUsbId(ViUInt16 vid, ViUInt16 pid);

#ifdef __cplusplus
    }
#endif

#endif  /* ndef __PM100D_util_H__ */
