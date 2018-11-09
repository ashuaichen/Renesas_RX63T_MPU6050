/************************************************************************
*
* Device     : RX/RX600/RX63T
*
* File Name  : intprg.c
*
* Abstract   : Interrupt Program.
*
* History    : 1.00  (2012-06-12)  [Hardware Manual Revision : 1.00]
*            : 2.00  (2013-02-17)  [Hardware Manual Revision : 2.00]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2013 (2012) Renesas Electronics Corporation and
* Renesas Solutions Corp. All rights reserved.
*
************************************************************************/

#include <machine.h>
#include "vect.h"
#include <riic.h>
#pragma section IntPRG

// Exception(Supervisor Instruction)
void Excep_SuperVisorInst(void){/* brk(); */}

// Exception(Access Instruction)
void Excep_AccessInst(void){/* brk(); */}

// Exception(Undefined Instruction)
void Excep_UndefinedInst(void){/* brk(); */}

// Exception(Floating Point)
void Excep_FloatingPoint(void){/* brk(); */}

// NMI
void NonMaskableInterrupt(void){/* brk(); */}

// Dummy
void Dummy(void){/* brk(); */}

// BRK
void Excep_BRK(void){ wait(); }

// BSC BUSERR
void Excep_BSC_BUSERR(void){ }

// FCU FIFERR
void Excep_FCU_FIFERR(void){ }

// FCU FRDYI
void Excep_FCU_FRDYI(void){ }

// ICU SWINT
void Excep_ICU_SWINT(void){ }

// CMT0 CMI0
void Excep_CMT0_CMI0(void){ }

// CMT1 CMI1
void Excep_CMT1_CMI1(void){ }

// CMT2 CMI2
void Excep_CMT2_CMI2(void){ }

// CMT3 CMI3
void Excep_CMT3_CMI3(void){ }

// USB0 D0FIFO0
void Excep_USB0_D0FIFO0(void){ }

// USB0 D1FIFO0
void Excep_USB0_D1FIFO0(void){ }

// USB0 USBI0
void Excep_USB0_USBI0(void){ }

// CAC FERRF
void Excep_CAC_FERRF(void){ }

// CAC MENDF
void Excep_CAC_MENDF(void){ }

// CAC OVFF
void Excep_CAC_OVFF(void){ }

// RSPI0 SPRI0
void Excep_RSPI0_SPRI0(void){ }

// RSPI0 SPTI0
void Excep_RSPI0_SPTI0(void){ }

// RSPI0 SPII0
void Excep_RSPI0_SPII0(void){ }

// RSPI1 SPRI1
void Excep_RSPI1_SPRI1(void){ }

// RSPI1 SPTI1
void Excep_RSPI1_SPTI1(void){ }

// RSPI1 SPII1
void Excep_RSPI1_SPII1(void){ }

// CAN1 RXF1
void Excep_CAN1_RXF1(void){ }

// CAN1 TXF1
void Excep_CAN1_TXF1(void){ }

// CAN1 RXM1
void Excep_CAN1_RXM1(void){ }

// CAN1 TXM1
void Excep_CAN1_TXM1(void){ }

// GPT7 GTCIA7
void Excep_GPT7_GTCIA7(void){ }

// GPT7 GTCIB7
void Excep_GPT7_GTCIB7(void){ }

// GPT7 GTCIC7
void Excep_GPT7_GTCIC7(void){ }

// GPT7 GTCIE7
void Excep_GPT7_GTCIE7(void){ }

// GPT7 GTCIV7
void Excep_GPT7_GTCIV7(void){ }

// CMP CMP4
void Excep_CMP_CMP4(void){ }

// CMP CMP5
void Excep_CMP_CMP5(void){ }

// CMP CMP6
void Excep_CMP_CMP6(void){ }

// DOC DOPCF
void Excep_DOC_DOPCF(void){ }

// ICU IRQ0
void Excep_ICU_IRQ0(void){ }

// ICU IRQ1
void Excep_ICU_IRQ1(void){ }

// ICU IRQ2
void Excep_ICU_IRQ2(void){ }

// ICU IRQ3
void Excep_ICU_IRQ3(void){ }

// ICU IRQ4
void Excep_ICU_IRQ4(void){ }

// ICU IRQ5
void Excep_ICU_IRQ5(void){ }

// ICU IRQ6
void Excep_ICU_IRQ6(void){ }

// ICU IRQ7
void Excep_ICU_IRQ7(void){ }

// USB USBR0
void Excep_USB_USBR0(void){ }

// AD ADI0
void Excep_AD_ADI0(void){ }

// S12AD S12ADI
void Excep_S12AD_S12ADI(void){ }

// S12AD S12GBADI
void Excep_S12AD_S12GBADI(void){ }

// S12AD1 S12ADI1
void Excep_S12AD1_S12ADI1(void){ }

// S12AD1 S12GBADI1
void Excep_S12AD1_S12GBADI1(void){ }

// ICU GROUP0
void Excep_ICU_GROUP0(void){ }

// ICU GROUP12
void Excep_ICU_GROUP12(void){ }

// SCI12 SCIX0
void Excep_SCI12_SCIX0(void){ }

// SCI12 SCIX1
void Excep_SCI12_SCIX1(void){ }

// SCI12 SCIX2
void Excep_SCI12_SCIX2(void){ }

// SCI12 SCIX3
void Excep_SCI12_SCIX3(void){ }

// MTU0 TGIA0
void Excep_MTU0_TGIA0(void){ }

// MTU0 TGIB0
void Excep_MTU0_TGIB0(void){ }

// MTU0 TGIC0
void Excep_MTU0_TGIC0(void){ }

// MTU0 TGID0
void Excep_MTU0_TGID0(void){ }

// MTU0 TCIV0
void Excep_MTU0_TCIV0(void){ }

// MTU0 TGIE0
void Excep_MTU0_TGIE0(void){ }

// MTU0 TGIF0
void Excep_MTU0_TGIF0(void){ }

// MTU1 TGIA1
void Excep_MTU1_TGIA1(void){ }

// MTU1 TGIB1
void Excep_MTU1_TGIB1(void){ }

// MTU1 TCIV1
void Excep_MTU1_TCIV1(void){ }

// MTU1 TCIU1
void Excep_MTU1_TCIU1(void){ }

// MTU2 TGIA2
void Excep_MTU2_TGIA2(void){ }

// MTU2 TGIB2
void Excep_MTU2_TGIB2(void){ }

// MTU2 TCIV2
void Excep_MTU2_TCIV2(void){ }

// MTU2 TCIU2
void Excep_MTU2_TCIU2(void){ }

// MTU3 TGIA3
void Excep_MTU3_TGIA3(void){ }

// MTU3 TGIB3
void Excep_MTU3_TGIB3(void){ }

// MTU3 TGIC3
void Excep_MTU3_TGIC3(void){ }

// MTU3 TGID3
void Excep_MTU3_TGID3(void){ }

// MTU3 TCIV3
void Excep_MTU3_TCIV3(void){ }

// MTU4 TGIA4
void Excep_MTU4_TGIA4(void){ }

// MTU4 TGIB4
void Excep_MTU4_TGIB4(void){ }

// MTU4 TGIC4
void Excep_MTU4_TGIC4(void){ }

// MTU4 TGID4
void Excep_MTU4_TGID4(void){ }

// MTU4 TCIV4
void Excep_MTU4_TCIV4(void){ }

// MTU5 TGIU5
void Excep_MTU5_TGIU5(void){ }

// MTU5 TGIV5
void Excep_MTU5_TGIV5(void){ }

// MTU5 TGIW5
void Excep_MTU5_TGIW5(void){ }

// MTU6 TGIA6
void Excep_MTU6_TGIA6(void){ }

// MTU6 TGIB6
void Excep_MTU6_TGIB6(void){ }

// MTU6 TGIC6
void Excep_MTU6_TGIC6(void){ }

// MTU6 TGID6
void Excep_MTU6_TGID6(void){ }

// MTU6 TCIV6
void Excep_MTU6_TCIV6(void){ }

// MTU7 TGIA7
void Excep_MTU7_TGIA7(void){ }

// MTU7 TGIB7
void Excep_MTU7_TGIB7(void){ }

// MTU7 TGIC7
void Excep_MTU7_TGIC7(void){ }

// MTU7 TGID7
void Excep_MTU7_TGID7(void){ }

// MTU7 TCIV7
void Excep_MTU7_TCIV7(void){ }

// POE OEI1
void Excep_POE_OEI1(void){ }

// POE OEI2
void Excep_POE_OEI2(void){ }

// POE OEI3
void Excep_POE_OEI3(void){ }

// POE OEI4
void Excep_POE_OEI4(void){ }

// POE OEI5
void Excep_POE_OEI5(void){ }

// CMP CMP0
void Excep_CMP_CMP0(void){ }

// CMP CMP1
void Excep_CMP_CMP1(void){ }

// CMP CMP2
void Excep_CMP_CMP2(void){ }

// GPT4 GTCIA4
void Excep_GPT4_GTCIA4(void){ }

// GPT4 GTCIB4
void Excep_GPT4_GTCIB4(void){ }

// GPT4 GTCIC4
void Excep_GPT4_GTCIC4(void){ }

// GPT4 GTCIE4
void Excep_GPT4_GTCIE4(void){ }

// GPT4 GTCIV4
void Excep_GPT4_GTCIV4(void){ }

// GPT4 LOCOI4
void Excep_GPT4_LOCOI4(void){ }

// GPT5 GTCIA5
void Excep_GPT5_GTCIA5(void){ }

// GPT5 GTCIB5
void Excep_GPT5_GTCIB5(void){ }

// GPT5 GTCIC5
void Excep_GPT5_GTCIC5(void){ }

// GPT5 GTCIE5
void Excep_GPT5_GTCIE5(void){ }

// GPT5 GTCIV5
void Excep_GPT5_GTCIV5(void){ }

// GPT6 GTCIA6
void Excep_GPT6_GTCIA6(void){ }

// GPT6 GTCIB6
void Excep_GPT6_GTCIB6(void){ }

// GPT6 GTCIC6
void Excep_GPT6_GTCIC6(void){ }

// GPT6 GTCIE6
void Excep_GPT6_GTCIE6(void){ }

// GPT6 GTCIV6
void Excep_GPT6_GTCIV6(void){ }

// RIIC1 EEI1
void Excep_RIIC1_EEI1(void){IIC_EEI_Int(); }

// RIIC1 RXI1
void Excep_RIIC1_RXI1(void){ IIC_RXI_Int(); }

// RIIC1 TXI1
void Excep_RIIC1_TXI1(void){ IIC_TXI_Int(); }

// RIIC1 TEI1
void Excep_RIIC1_TEI1(void){ IIC_TEI_Int(); }

// RIIC0 EEI0
void Excep_RIIC0_EEI0(void){ }

// RIIC0 RXI0
void Excep_RIIC0_RXI0(void){ }

// RIIC0 TXI0
void Excep_RIIC0_TXI0(void){ }

// RIIC0 TEI0
void Excep_RIIC0_TEI0(void){ }

// DMAC DMAC0I
void Excep_DMAC_DMAC0I(void){ }

// DMAC DMAC1I
void Excep_DMAC_DMAC1I(void){ }

// DMAC DMAC2I
void Excep_DMAC_DMAC2I(void){ }

// DMAC DMAC3I
void Excep_DMAC_DMAC3I(void){ }

// SCI0 RXI0
void Excep_SCI0_RXI0(void){ }

// SCI0 TXI0
void Excep_SCI0_TXI0(void){ }

// SCI0 TEI0
void Excep_SCI0_TEI0(void){ }

// SCI1 RXI1
void Excep_SCI1_RXI1(void){ }

// SCI1 TXI1
void Excep_SCI1_TXI1(void){ }

// SCI1 TEI1
void Excep_SCI1_TEI1(void){ }

// SCI2 RXI2
void Excep_SCI2_RXI2(void){ }

// SCI2 TXI2
void Excep_SCI2_TXI2(void){ }

// SCI2 TEI2
void Excep_SCI2_TEI2(void){ }

// SCI3 RXI3
void Excep_SCI3_RXI3(void){ }

// SCI3 TXI3
void Excep_SCI3_TXI3(void){ }

// SCI3 TEI3
void Excep_SCI3_TEI3(void){ }

// GPT0 GTCIA0
void Excep_GPT0_GTCIA0(void){ }

// GPT0 GTCIB0
void Excep_GPT0_GTCIB0(void){ }

// GPT0 GTCIC0
void Excep_GPT0_GTCIC0(void){ }

// GPT0 GTCIE0
void Excep_GPT0_GTCIE0(void){ }

// GPT0 GTCIV0
void Excep_GPT0_GTCIV0(void){ }

// GPT0 LOCOI0
void Excep_GPT0_LOCOI0(void){ }

// GPT1 GTCIA1
void Excep_GPT1_GTCIA1(void){ }

// GPT1 GTCIB1
void Excep_GPT1_GTCIB1(void){ }

// GPT1 GTCIC1
void Excep_GPT1_GTCIC1(void){ }

// GPT1 GTCIE1
void Excep_GPT1_GTCIE1(void){ }

// GPT1 GTCIV1
void Excep_GPT1_GTCIV1(void){ }

// GPT2 GTCIA2
void Excep_GPT2_GTCIA2(void){ }

// GPT2 GTCIB2
void Excep_GPT2_GTCIB2(void){ }

// GPT2 GTCIC2
void Excep_GPT2_GTCIC2(void){ }

// GPT2 GTCIE2
void Excep_GPT2_GTCIE2(void){ }

// GPT2 GTCIV2
void Excep_GPT2_GTCIV2(void){ }

// GPT3 GTCIA3
void Excep_GPT3_GTCIA3(void){ }

// GPT3 GTCIB3
void Excep_GPT3_GTCIB3(void){ }

// GPT3 GTCIC3
void Excep_GPT3_GTCIC3(void){ }

// GPT3 GTCIE3
void Excep_GPT3_GTCIE3(void){ }

// GPT3 GTCIV3
void Excep_GPT3_GTCIV3(void){ }

// SCI12 RXI12
void Excep_SCI12_RXI12(void){ }

// SCI12 TXI12
void Excep_SCI12_TXI12(void){ }

// SCI12 TEI12
void Excep_SCI12_TEI12(void){ }

