
/* 
* Copyright (C) 2009-2014 Texas Instruments Incorporated - http://www.ti.com/ 
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef __MEM_MAP_H__
#define __MEM_MAP_H__
/*FEE*/
#ifdef FEE_START_SEC_VAR_INIT_UNSPECIFIED
#pragma SET_DATA_SECTION("FEE_DATA_SECTION")
#undef FEE_START_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#pragma SET_DATA_SECTION()
#undef FEE_STOP_SEC_VAR_INIT_UNSPECIFIED
#endif

#ifdef FEE_START_SEC_CONST_UNSPECIFIED
#pragma SET_DATA_SECTION("FEE_CONST_SECTION")
#undef FEE_START_SEC_CONST_UNSPECIFIED
#endif

#ifdef FEE_STOP_SEC_CONST_UNSPECIFIED
#pragma SET_DATA_SECTION()
#undef FEE_STOP_SEC_CONST_UNSPECIFIED
#endif

#ifdef FEE_START_SEC_CODE
#pragma SET_CODE_SECTION("FEE_TEXT_SECTION")
#undef FEE_START_SEC_CODE
#endif

#ifdef FEE_STOP_SEC_CODE
#pragma SET_CODE_SECTION()
#undef FEE_STOP_SEC_CODE
#endif


#endif  /* __MEM_MAP_H__ */
