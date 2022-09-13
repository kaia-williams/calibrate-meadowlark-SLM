//==============================================================================
//
// Title:      PM100D_rsrc.h
// Purpose:    Instrument driver resource information.
//
// Created on: 30.06.2016 at 13:51:29
// Copyright:  . All Rights Reserved.
//
//==============================================================================

#ifndef __PM100D_rsrc_H__
#define __PM100D_rsrc_H__

#ifdef __cplusplus
    extern "C" {
#endif

//==============================================================================
// Include files

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// External variables

//==============================================================================
// Global functions

/*------------------------------------------------------------------------*//**
\brief   Initializes the instrument driver resource module.
\details Call this once in DllMain().
\return  Error code. (See \ref VI_ERROR_x)
*//*-------------------------------------------------------------------------*/
ViStatus rsrc_init(void);

/*------------------------------------------------------------------------*//**
\brief   Cleanup the instrument driver resource module.
\details Removes the data from memory. Call this once in DllMain().
\return  Error code. (See \ref VI_ERROR_x)
*//*-------------------------------------------------------------------------*/
ViStatus rsrc_cleanup(void);
   
ViStatus rsrc_findRsrc(ViUInt32 *devCnt);
ViStatus rsrc_getRsrcName(ViUInt32 index, ViChar rsrcName[]);
ViStatus rsrc_getRsrcInfo(ViUInt32 index, ViChar modelName[], ViChar serialNumber[], ViChar manufacturer[], ViPBoolean deviceAvailable);

#ifdef __cplusplus
    }
#endif


#endif  /* ndef __PM100D_rsrc_H__ */
