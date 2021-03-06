/*
 *   KONNEX/EIB-Protocol-Stack.
 *
 *  (C) 2007-2012 by Christoph Schueler <github.com/Christoph2,
 *                                       cpu12.gems@googlemail.com>
 *
 *   All Rights Reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */
#if !defined(__KNX_LAYER_APPLICATION_H)
#define __KNX_LAYER_APPLICATION_H

/*
**
**  Declarations common to the group-oriented and the managment parts of the application layer.
**
*/
#include "knx_alg.h"

#include "knx_messaging.h"
#include "KNXConv.h"
#include "knx_address.h"
#include "knx_layer_transport.h"
#include "knx_ios.h"
#include "knx_lsm.h"
#include "knx_apci.h"
#include "Appl.h"

#if defined(__cplusplus)
extern "C"
{
#endif  /* __cplusplus */

/*
** Global variables.
*/
extern const uint8  KNX_OBJ_LEN_TAB[];
extern const uint8  APP_CommObjTab[];
extern uint8        DEV_Device_Control;
extern uint8        DEV_Current_Accesslevel;
extern uint8        DEV_SystemState;

/*
** Global function-like macros.
*/
#define KnxAL_GetAPDUShortData(pmsg, nbits)         ((uint8)(pmsg)->apci & (uint8)KNX_AL_SHORT_DATA_MASK[(nbits) - (uint8)1])
#define KnxAL_SetAPDUShortData(pmsg, data, nbits)   ((pmsg)->apci =      \
                                                         ((pmsg)->apci & \
                                                          ~(uint8)0x3f) | ((data) & KNX_AL_SHORT_DATA_MASK[(nbits) - (uint8)1])

#if KSTACK_MEMORY_MAPPING == STD_ON
FUNC(void, KSTACK_CODE)     DEV_SetVerifyMode(boolean on);
FUNC(void, KSTACK_CODE)     DEV_ChkOwnPhysAddrRcvd(boolean on);
FUNC(void, KSTACK_CODE)     DEV_PhysAddrWriteEnable(boolean on);
FUNC(void, KSTACK_CODE)     KnxALM_Task(void);
FUNC(void, KSTACK_CODE)     KnxALG_PollCycle(void);
FUNC(uint8, KSTACK_CODE)    KnxAL_GetAPCIType(const KNX_StandardFrameRefType pmsg);
FUNC(void, KSTACK_CODE)     KnxAL_GetAPDUData(const KNX_StandardFrameRefType pmsg, uint8 offset,
                                              P2VAR(uint8, AUTOMATIC, KSTACK_APPL_DATA) data
                                              uint8 len
                                              );
FUNC(void, KSTACK_CODE)     KnxAL_SetAPDUData(const KNX_StandardFrameRefType pmsg, uint8 offset,
                                              P2VAR(uint8, AUTOMATIC, KSTACK_APPL_DATA) data
                                              uint8 len
                                              );
FUNC(uint8, KSTACK_CODE)    KnxAL_GetAPDUDataByte(const KNX_StandardFrameRefType pmsg, uint8 offset);
FUNC(void, KSTACK_CODE)     KnxAL_SetAPDUDataByte(const KNX_StandardFrameRefType pmsg, uint8 offset, uint8 value);
#else
void    DEV_SetVerifyMode(boolean on);
void    DEV_ChkOwnPhysAddrRcvd(boolean on);
void    DEV_PhysAddrWriteEnable(boolean on);
void    KnxALM_Task(void);
void    KnxALG_PollCycle(void);
uint8   KnxAL_GetAPCIType(const KNX_StandardFrameRefType pmsg);
void    KnxAL_GetAPDUData(const KNX_StandardFrameRefType pmsg, uint8 offset, uint8 * data, uint8 len);
void    KnxAL_SetAPDUData(const KNX_StandardFrameRefType pmsg, uint8 offset, uint8 * data, uint8 len);
uint8   KnxAL_GetAPDUDataByte(const KNX_StandardFrameRefType pmsg, uint8 offset);
void    KnxAL_SetAPDUDataByte(const KNX_StandardFrameRefType pmsg, uint8 offset, const uint8 value);


#endif /* KSTACK_MEMORY_MAPPING */

/*
**  Application-Layer-Services.
*/

#if KSTACK_MEMORY_MAPPING == STD_ON
/* Broadcast-Services. */
FUNC(void, KSTACK_CODE) A_IndividualAddress_Read_Res(KnxMSG_BufferPtr pBuffer, Knx_AddressType source);
FUNC(void, KSTACK_CODE) A_IndividualAddress_Read_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source);
FUNC(void, KSTACK_CODE) A_IndividualAddress_Write_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                      Knx_AddressType newaddress
                                                      );

FUNC(void, KSTACK_CODE) A_IndividualAddressSerialNumber_Read_Res(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                                 Knx_SerialNumberType serial_number, Knx_AddressType domain_addr
                                                                 );
FUNC(void, KSTACK_CODE) A_IndividualAddressSerialNumber_Read_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                                 Knx_SerialNumberType serial_number
                                                                 );
FUNC(void, KSTACK_CODE) A_IndividualAddressSerialNumber_Write_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                                  Knx_SerialNumberType serial_number, Knx_AddressType new_addr
                                                                  );

FUNC(void, KSTACK_CODE) A_ServiceInformation_Indication_Write_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                                  uint8 info
                                                                  );

FUNC(void, KSTACK_CODE) A_DomainAddress_Read_Res(KnxMSG_BufferPtr pBuffer, Knx_AddressType source);
FUNC(void, KSTACK_CODE) A_DomainAddress_Read_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source);
FUNC(void, KSTACK_CODE) A_DomainAddress_Write_req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                  Knx_AddressType domain_ddress
                                                  );
FUNC(void, KSTACK_CODE) A_DomainAddressSelective_Read_req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                          Knx_AddressType domain_ddress, Knx_AddressType start_address, uint8 range
                                                          );

FUNC(void, KSTACK_CODE) A_PropertyValue_Read_Res(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                 Knx_AddressType dest, uint8 obj_index, uint8 prop_id, uint8 nr_of_elem,
                                                 uint16 start_index,
                                                 P2VAR(uint8, AUTOMATIC,
                                                       KSTACK_APPL_DATA) data
                                                 );
FUNC(void, KSTACK_CODE) A_PropertyValue_Read_Res_NoData(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                        Knx_AddressType dest, uint8 obj_index, uint8 prop_id, uint8 nr_of_elem,
                                                        uint16 start_index
                                                        );
FUNC(void, KSTACK_CODE) A_PropertyValue_Read_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                 Knx_AddressType dest,  uint8 obj_index, uint8 prop_id, uint8 nr_of_elem,
                                                 uint16 start_index
                                                 );

/* todo: Prop_Write!!! */

FUNC(void, KSTACK_CODE) A_PropertyDescription_Read_Res(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                       Knx_AddressType dest,  uint8 obj_index, uint8 prop_id, uint8 prop_index,
                                                       uint8 type, uint16 nr_of_elem,
                                                       uint8 access
                                                       );
FUNC(void, KSTACK_CODE) A_PropertyDescription_Read_Res_NoData(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                              Knx_AddressType dest, uint8 obj_index, uint8 prop_id,
                                                              uint8 prop_index
                                                              );
FUNC(void, KSTACK_CODE) A_PropertyDescription_Read_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                                       Knx_AddressType dest, uint8 obj_index, uint8 prop_id, uint8 prop_index
                                                       );
#else
/* Broadcast-Services. */
void    A_IndividualAddress_Read_Res(KnxMSG_BufferPtr pBuffer, Knx_AddressType source);
void    A_IndividualAddress_Read_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source);
void    A_IndividualAddress_Write_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                      Knx_AddressType newaddress
                                      );

void A_IndividualAddressSerialNumber_Read_Res(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                              Knx_SerialNumberType serial_number, Knx_AddressType domain_addr
                                              );
void A_IndividualAddressSerialNumber_Read_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                              Knx_SerialNumberType serial_number
                                              );
void A_IndividualAddressSerialNumber_Write_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                               Knx_SerialNumberType serial_number, Knx_AddressType new_addr
                                               );

void A_ServiceInformation_Indication_Write_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source, uint8 info);

void    A_DomainAddress_Read_Res(KnxMSG_BufferPtr pBuffer, Knx_AddressType source);
void    A_DomainAddress_Read_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source);
void    A_DomainAddress_Write_req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source, Knx_AddressType domain_ddress);
void    A_DomainAddressSelective_Read_req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                          Knx_AddressType domain_ddress, Knx_AddressType start_address, uint8 range
                                          );

void A_PropertyValue_Read_Res(KnxMSG_BufferPtr pBuffer, Knx_AddressType source, Knx_AddressType dest,
                              uint8 obj_index, uint8 prop_id, uint8 nr_of_elem, uint16 start_index, uint8 * data
                              );
void A_PropertyValue_Read_Res_NoData(KnxMSG_BufferPtr pBuffer, Knx_AddressType source, Knx_AddressType dest,
                                     uint8 obj_index, uint8 prop_id, uint8 nr_of_elem, uint16 start_index
                                     );
void A_PropertyValue_Read_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source, Knx_AddressType dest,
                              uint8 obj_index, uint8 prop_id, uint8 nr_of_elem, uint16 start_index
                              );


/* todo: Prop_Write!!! */

void A_PropertyDescription_Read_Res(KnxMSG_BufferPtr pBuffer, Knx_AddressType source, Knx_AddressType dest,
                                    uint8 obj_index, uint8 prop_id, uint8 prop_index, uint8 type, uint16 nr_of_elem, uint8 access
                                    );
void A_PropertyDescription_Read_Res_NoData(KnxMSG_BufferPtr pBuffer, Knx_AddressType source,
                                           Knx_AddressType dest, uint8 obj_index, uint8 prop_id, uint8 prop_index
                                           );
void A_PropertyDescription_Read_Req(KnxMSG_BufferPtr pBuffer, Knx_AddressType source, Knx_AddressType dest,
                                    uint8 obj_index, uint8 prop_id, uint8 prop_index
                                    );


#endif /* KSTACK_MEMORY_MAPPING */

#if defined(__cplusplus)
}
#endif  /* __cplusplus */

#endif  /* __KNX_LAYER_APPLICATION_H */

