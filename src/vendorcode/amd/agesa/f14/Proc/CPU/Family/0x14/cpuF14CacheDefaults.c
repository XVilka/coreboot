/* $NoKeywords:$ */
/**
 * @file
 *
 * AMD Family_14 ROM Execution Cache Defaults
 *
 * Contains default values for ROM execution cache setup
 *
 * @xrefitem bom "File Content Label" "Release Content"
 * @e project:      AGESA
 * @e sub-project:  CPU/Family/0x14
 * @e \$Revision: 36376 $   @e \$Date: 2010-08-18 00:17:10 +0800 (Wed, 18 Aug 2010) $
 *
 */
/*
 *****************************************************************************
 *
 * Copyright (c) 2011, Advanced Micro Devices, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Advanced Micro Devices, Inc. nor the names of 
 *       its contributors may be used to endorse or promote products derived 
 *       from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ADVANCED MICRO DEVICES, INC. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * ***************************************************************************
 *
 */

/*----------------------------------------------------------------------------------------
 *                             M O D U L E S    U S E D
 *----------------------------------------------------------------------------------------
 */
#include "AGESA.h"
#include "cpuCacheInit.h"
#include "cpuFamilyTranslation.h"
#include "Filecode.h"
#define FILECODE PROC_CPU_FAMILY_0X14_CPUF14CACHEDEFAULTS_FILECODE

/*----------------------------------------------------------------------------------------
 *                   D E F I N I T I O N S    A N D    M A C R O S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *                  T Y P E D E F S     A N D     S T R U C T U R E S
 *----------------------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------------------
 *           P R O T O T Y P E S     O F     L O C A L     F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */

VOID
GetF14CacheInfo (
  IN       CPU_SPECIFIC_SERVICES *FamilySpecificServices,
     OUT   CONST VOID **CacheInfoPtr,
     OUT   UINT8 *NumberOfElements,
  IN       AMD_CONFIG_PARAMS *StdHeader
  );

/*----------------------------------------------------------------------------------------
 *                          E X P O R T E D    F U N C T I O N S
 *----------------------------------------------------------------------------------------
 */
#define BSP_STACK_SIZE            16384
#define CORE0_STACK_SIZE          16384
#define CORE1_STACK_SIZE          4096
#define MEM_TRAINING_BUFFER_SIZE  16384
#define VAR_MTRR_MASK             0x0000000FFFFFFFFF

#define HEAP_BASE_MASK            0x0000000FFFFFFFFF

#define SHARED_MEM_SIZE       0

CONST CACHE_INFO ROMDATA CpuF14CacheInfo =
{
  BSP_STACK_SIZE,
  CORE0_STACK_SIZE,
  CORE1_STACK_SIZE,
  MEM_TRAINING_BUFFER_SIZE,
  SHARED_MEM_SIZE,
  VAR_MTRR_MASK,
  VAR_MTRR_MASK,
  HEAP_BASE_MASK,
  InfiniteExe
};


/*---------------------------------------------------------------------------------------*/
/**
 *  Returns the family specific properties of the cache, and its usage.
 *
 *  @CpuServiceMethod{::F_CPU_GET_FAMILY_SPECIFIC_ARRAY}.
 *
 *  @param[in]   FamilySpecificServices   The current Family Specific Services.
 *  @param[out]  CacheInfoPtr             Points to the cache info properties on exit.
 *  @param[out]  NumberOfElements         Will be one to indicate one entry.
 *  @param[in]   StdHeader                Header for library and services.
 *
 */
VOID
GetF14CacheInfo (
  IN       CPU_SPECIFIC_SERVICES *FamilySpecificServices,
     OUT   CONST VOID **CacheInfoPtr,
     OUT   UINT8 *NumberOfElements,
  IN       AMD_CONFIG_PARAMS *StdHeader
  )
{
  *NumberOfElements = 1;
  *CacheInfoPtr = &CpuF14CacheInfo;
}

