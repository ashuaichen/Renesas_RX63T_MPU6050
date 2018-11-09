/************************************************************************
*
* Device     : RX/RX600/RX63T
*
* File Name  : vect.h
*
* Abstract   : Definition of Vector.
*
* History    : 1.00  (2012-06-12)  [Hardware Manual Revision : 1.00]
*            : 2.00  (2013-02-17)  [Hardware Manual Revision : 2.00]
*
* NOTE       : THIS IS A TYPICAL EXAMPLE.
*
* Copyright (C) 2013 (2012) Renesas Electronics Corporation. and
* Renesas Solutions Corp. All rights reserved.
*
************************************************************************/

// Exception(Supervisor Instruction)
#pragma interrupt (Excep_SuperVisorInst)
void Excep_SuperVisorInst(void);

// Exception(Access Instruction)
void Excep_AccessInst(void);

// Exception(Undefined Instruction)
#pragma interrupt (Excep_UndefinedInst)
void Excep_UndefinedInst(void);

// Exception(Floating Point)
#pragma interrupt (Excep_FloatingPoint)
void Excep_FloatingPoint(void);

// NMI
#pragma interrupt (NonMaskableInterrupt)
void NonMaskableInterrupt(void);

// Dummy
#pragma interrupt (Dummy)
void Dummy(void);

// BRK
#pragma interrupt (Excep_BRK(vect=0))
void Excep_BRK(void);

// vector  1 reserved
// vector  2 reserved
// vector  3 reserved
// vector  4 reserved
// vector  5 reserved
// vector  6 reserved
// vector  7 reserved
// vector  8 reserved
// vector  9 reserved
// vector 10 reserved
// vector 11 reserved
// vector 12 reserved
// vector 13 reserved
// vector 14 reserved
// vector 15 reserved

// BSC BUSERR
#pragma interrupt (Excep_BSC_BUSERR(vect=16))
void Excep_BSC_BUSERR(void);

// FCU FIFERR
#pragma interrupt (Excep_FCU_FIFERR(vect=21))
void Excep_FCU_FIFERR(void);

// FCU FRDYI
#pragma interrupt (Excep_FCU_FRDYI(vect=23))
void Excep_FCU_FRDYI(void);

// ICU SWINT
#pragma interrupt (Excep_ICU_SWINT(vect=27))
void Excep_ICU_SWINT(void);

// CMT0 CMI0
#pragma interrupt (Excep_CMT0_CMI0(vect=28))
void Excep_CMT0_CMI0(void);

// CMT1 CMI1
#pragma interrupt (Excep_CMT1_CMI1(vect=29))
void Excep_CMT1_CMI1(void);

// CMT2 CMI2
#pragma interrupt (Excep_CMT2_CMI2(vect=30))
void Excep_CMT2_CMI2(void);

// CMT3 CMI3
#pragma interrupt (Excep_CMT3_CMI3(vect=31))
void Excep_CMT3_CMI3(void);

// USB0 D0FIFO0
#pragma interrupt (Excep_USB0_D0FIFO0(vect=33))
void Excep_USB0_D0FIFO0(void);

// USB0 D1FIFO0
#pragma interrupt (Excep_USB0_D1FIFO0(vect=34))
void Excep_USB0_D1FIFO0(void);

// USB0 USBI0
#pragma interrupt (Excep_USB0_USBI0(vect=35))
void Excep_USB0_USBI0(void);

// CAC FERRF
#pragma interrupt (Excep_CAC_FERRF(vect=36))
void Excep_CAC_FERRF(void);

// CAC MENDF
#pragma interrupt (Excep_CAC_MENDF(vect=37))
void Excep_CAC_MENDF(void);

// CAC OVFF
#pragma interrupt (Excep_CAC_OVFF(vect=38))
void Excep_CAC_OVFF(void);

// RSPI0 SPRI0
#pragma interrupt (Excep_RSPI0_SPRI0(vect=39))
void Excep_RSPI0_SPRI0(void);

// RSPI0 SPTI0
#pragma interrupt (Excep_RSPI0_SPTI0(vect=40))
void Excep_RSPI0_SPTI0(void);

// RSPI0 SPII0
#pragma interrupt (Excep_RSPI0_SPII0(vect=41))
void Excep_RSPI0_SPII0(void);

// RSPI1 SPRI1
#pragma interrupt (Excep_RSPI1_SPRI1(vect=42))
void Excep_RSPI1_SPRI1(void);

// RSPI1 SPTI1
#pragma interrupt (Excep_RSPI1_SPTI1(vect=43))
void Excep_RSPI1_SPTI1(void);

// RSPI1 SPII1
#pragma interrupt (Excep_RSPI1_SPII1(vect=44))
void Excep_RSPI1_SPII1(void);

// CAN1 RXF1
#pragma interrupt (Excep_CAN1_RXF1(vect=45))
void Excep_CAN1_RXF1(void);

// CAN1 TXF1
#pragma interrupt (Excep_CAN1_TXF1(vect=46))
void Excep_CAN1_TXF1(void);

// CAN1 RXM1
#pragma interrupt (Excep_CAN1_RXM1(vect=47))
void Excep_CAN1_RXM1(void);

// CAN1 TXM1
#pragma interrupt (Excep_CAN1_TXM1(vect=48))
void Excep_CAN1_TXM1(void);

// GPT7 GTCIA7
#pragma interrupt (Excep_GPT7_GTCIA7(vect=49))
void Excep_GPT7_GTCIA7(void);

// GPT7 GTCIB7
#pragma interrupt (Excep_GPT7_GTCIB7(vect=50))
void Excep_GPT7_GTCIB7(void);

// GPT7 GTCIC7
#pragma interrupt (Excep_GPT7_GTCIC7(vect=51))
void Excep_GPT7_GTCIC7(void);

// GPT7 GTCIE7
#pragma interrupt (Excep_GPT7_GTCIE7(vect=52))
void Excep_GPT7_GTCIE7(void);

// GPT7 GTCIV7
#pragma interrupt (Excep_GPT7_GTCIV7(vect=53))
void Excep_GPT7_GTCIV7(void);

// CMP CMP4
#pragma interrupt (Excep_CMP_CMP4(vect=54))
void Excep_CMP_CMP4(void);

// CMP CMP5
#pragma interrupt (Excep_CMP_CMP5(vect=55))
void Excep_CMP_CMP5(void);

// CMP CMP6
#pragma interrupt (Excep_CMP_CMP6(vect=56))
void Excep_CMP_CMP6(void);

// DOC DOPCF
#pragma interrupt (Excep_DOC_DOPCF(vect=57))
void Excep_DOC_DOPCF(void);

// ICU IRQ0
#pragma interrupt (Excep_ICU_IRQ0(vect=64))
void Excep_ICU_IRQ0(void);

// ICU IRQ1
#pragma interrupt (Excep_ICU_IRQ1(vect=65))
void Excep_ICU_IRQ1(void);

// ICU IRQ2
#pragma interrupt (Excep_ICU_IRQ2(vect=66))
void Excep_ICU_IRQ2(void);

// ICU IRQ3
#pragma interrupt (Excep_ICU_IRQ3(vect=67))
void Excep_ICU_IRQ3(void);

// ICU IRQ4
#pragma interrupt (Excep_ICU_IRQ4(vect=68))
void Excep_ICU_IRQ4(void);

// ICU IRQ5
#pragma interrupt (Excep_ICU_IRQ5(vect=69))
void Excep_ICU_IRQ5(void);

// ICU IRQ6
#pragma interrupt (Excep_ICU_IRQ6(vect=70))
void Excep_ICU_IRQ6(void);

// ICU IRQ7
#pragma interrupt (Excep_ICU_IRQ7(vect=71))
void Excep_ICU_IRQ7(void);

// USB USBR0
#pragma interrupt (Excep_USB_USBR0(vect=90))
void Excep_USB_USBR0(void);

// AD ADI0
#pragma interrupt (Excep_AD_ADI0(vect=98))
void Excep_AD_ADI0(void);

// S12AD S12ADI
#pragma interrupt (Excep_S12AD_S12ADI(vect=102))
void Excep_S12AD_S12ADI(void);

// S12AD S12GBADI
#pragma interrupt (Excep_S12AD_S12GBADI(vect=103))
void Excep_S12AD_S12GBADI(void);

// S12AD1 S12ADI1
#pragma interrupt (Excep_S12AD1_S12ADI1(vect=104))
void Excep_S12AD1_S12ADI1(void);

// S12AD1 S12GBADI1
#pragma interrupt (Excep_S12AD1_S12GBADI1(vect=105))
void Excep_S12AD1_S12GBADI1(void);

// ICU GROUP0
#pragma interrupt (Excep_ICU_GROUP0(vect=106))
void Excep_ICU_GROUP0(void);

// ICU GROUP12
#pragma interrupt (Excep_ICU_GROUP12(vect=114))
void Excep_ICU_GROUP12(void);

// SCI12 SCIX0
#pragma interrupt (Excep_SCI12_SCIX0(vect=122))
void Excep_SCI12_SCIX0(void);

// SCI12 SCIX1
#pragma interrupt (Excep_SCI12_SCIX1(vect=123))
void Excep_SCI12_SCIX1(void);

// SCI12 SCIX2
#pragma interrupt (Excep_SCI12_SCIX2(vect=124))
void Excep_SCI12_SCIX2(void);

// SCI12 SCIX3
#pragma interrupt (Excep_SCI12_SCIX3(vect=125))
void Excep_SCI12_SCIX3(void);

// MTU0 TGIA0
#pragma interrupt (Excep_MTU0_TGIA0(vect=126))
void Excep_MTU0_TGIA0(void);

// MTU0 TGIB0
#pragma interrupt (Excep_MTU0_TGIB0(vect=127))
void Excep_MTU0_TGIB0(void);

// MTU0 TGIC0
#pragma interrupt (Excep_MTU0_TGIC0(vect=128))
void Excep_MTU0_TGIC0(void);

// MTU0 TGID0
#pragma interrupt (Excep_MTU0_TGID0(vect=129))
void Excep_MTU0_TGID0(void);

// MTU0 TCIV0
#pragma interrupt (Excep_MTU0_TCIV0(vect=130))
void Excep_MTU0_TCIV0(void);

// MTU0 TGIE0
#pragma interrupt (Excep_MTU0_TGIE0(vect=131))
void Excep_MTU0_TGIE0(void);

// MTU0 TGIF0
#pragma interrupt (Excep_MTU0_TGIF0(vect=132))
void Excep_MTU0_TGIF0(void);

// MTU1 TGIA1
#pragma interrupt (Excep_MTU1_TGIA1(vect=133))
void Excep_MTU1_TGIA1(void);

// MTU1 TGIB1
#pragma interrupt (Excep_MTU1_TGIB1(vect=134))
void Excep_MTU1_TGIB1(void);

// MTU1 TCIV1
#pragma interrupt (Excep_MTU1_TCIV1(vect=135))
void Excep_MTU1_TCIV1(void);

// MTU1 TCIU1
#pragma interrupt (Excep_MTU1_TCIU1(vect=136))
void Excep_MTU1_TCIU1(void);

// MTU2 TGIA2
#pragma interrupt (Excep_MTU2_TGIA2(vect=137))
void Excep_MTU2_TGIA2(void);

// MTU2 TGIB2
#pragma interrupt (Excep_MTU2_TGIB2(vect=138))
void Excep_MTU2_TGIB2(void);

// MTU2 TCIV2
#pragma interrupt (Excep_MTU2_TCIV2(vect=139))
void Excep_MTU2_TCIV2(void);

// MTU2 TCIU2
#pragma interrupt (Excep_MTU2_TCIU2(vect=140))
void Excep_MTU2_TCIU2(void);

// MTU3 TGIA3
#pragma interrupt (Excep_MTU3_TGIA3(vect=141))
void Excep_MTU3_TGIA3(void);

// MTU3 TGIB3
#pragma interrupt (Excep_MTU3_TGIB3(vect=142))
void Excep_MTU3_TGIB3(void);

// MTU3 TGIC3
#pragma interrupt (Excep_MTU3_TGIC3(vect=143))
void Excep_MTU3_TGIC3(void);

// MTU3 TGID3
#pragma interrupt (Excep_MTU3_TGID3(vect=144))
void Excep_MTU3_TGID3(void);

// MTU3 TCIV3
#pragma interrupt (Excep_MTU3_TCIV3(vect=145))
void Excep_MTU3_TCIV3(void);

// MTU4 TGIA4
#pragma interrupt (Excep_MTU4_TGIA4(vect=146))
void Excep_MTU4_TGIA4(void);

// MTU4 TGIB4
#pragma interrupt (Excep_MTU4_TGIB4(vect=147))
void Excep_MTU4_TGIB4(void);

// MTU4 TGIC4
#pragma interrupt (Excep_MTU4_TGIC4(vect=148))
void Excep_MTU4_TGIC4(void);

// MTU4 TGID4
#pragma interrupt (Excep_MTU4_TGID4(vect=149))
void Excep_MTU4_TGID4(void);

// MTU4 TCIV4
#pragma interrupt (Excep_MTU4_TCIV4(vect=150))
void Excep_MTU4_TCIV4(void);

// MTU5 TGIU5
#pragma interrupt (Excep_MTU5_TGIU5(vect=151))
void Excep_MTU5_TGIU5(void);

// MTU5 TGIV5
#pragma interrupt (Excep_MTU5_TGIV5(vect=152))
void Excep_MTU5_TGIV5(void);

// MTU5 TGIW5
#pragma interrupt (Excep_MTU5_TGIW5(vect=153))
void Excep_MTU5_TGIW5(void);

// MTU6 TGIA6
#pragma interrupt (Excep_MTU6_TGIA6(vect=154))
void Excep_MTU6_TGIA6(void);

// MTU6 TGIB6
#pragma interrupt (Excep_MTU6_TGIB6(vect=155))
void Excep_MTU6_TGIB6(void);

// MTU6 TGIC6
#pragma interrupt (Excep_MTU6_TGIC6(vect=156))
void Excep_MTU6_TGIC6(void);

// MTU6 TGID6
#pragma interrupt (Excep_MTU6_TGID6(vect=157))
void Excep_MTU6_TGID6(void);

// MTU6 TCIV6
#pragma interrupt (Excep_MTU6_TCIV6(vect=158))
void Excep_MTU6_TCIV6(void);

// MTU7 TGIA7
#pragma interrupt (Excep_MTU7_TGIA7(vect=161))
void Excep_MTU7_TGIA7(void);

// MTU7 TGIB7
#pragma interrupt (Excep_MTU7_TGIB7(vect=162))
void Excep_MTU7_TGIB7(void);

// MTU7 TGIC7
#pragma interrupt (Excep_MTU7_TGIC7(vect=163))
void Excep_MTU7_TGIC7(void);

// MTU7 TGID7
#pragma interrupt (Excep_MTU7_TGID7(vect=164))
void Excep_MTU7_TGID7(void);

// MTU7 TCIV7
#pragma interrupt (Excep_MTU7_TCIV7(vect=165))
void Excep_MTU7_TCIV7(void);

// POE OEI1
#pragma interrupt (Excep_POE_OEI1(vect=166))
void Excep_POE_OEI1(void);

// POE OEI2
#pragma interrupt (Excep_POE_OEI2(vect=167))
void Excep_POE_OEI2(void);

// POE OEI3
#pragma interrupt (Excep_POE_OEI3(vect=168))
void Excep_POE_OEI3(void);

// POE OEI4
#pragma interrupt (Excep_POE_OEI4(vect=169))
void Excep_POE_OEI4(void);

// POE OEI5
#pragma interrupt (Excep_POE_OEI5(vect=170))
void Excep_POE_OEI5(void);

// CMP CMP0
#pragma interrupt (Excep_CMP_CMP0(vect=171))
void Excep_CMP_CMP0(void);

// CMP CMP1
#pragma interrupt (Excep_CMP_CMP1(vect=172))
void Excep_CMP_CMP1(void);

// CMP CMP2
#pragma interrupt (Excep_CMP_CMP2(vect=173))
void Excep_CMP_CMP2(void);

// GPT4 GTCIA4
#pragma interrupt (Excep_GPT4_GTCIA4(vect=174))
void Excep_GPT4_GTCIA4(void);

// GPT4 GTCIB4
#pragma interrupt (Excep_GPT4_GTCIB4(vect=175))
void Excep_GPT4_GTCIB4(void);

// GPT4 GTCIC4
#pragma interrupt (Excep_GPT4_GTCIC4(vect=176))
void Excep_GPT4_GTCIC4(void);

// GPT4 GTCIE4
#pragma interrupt (Excep_GPT4_GTCIE4(vect=177))
void Excep_GPT4_GTCIE4(void);

// GPT4 GTCIV4
#pragma interrupt (Excep_GPT4_GTCIV4(vect=178))
void Excep_GPT4_GTCIV4(void);

// GPT4 LOCOI4
#pragma interrupt (Excep_GPT4_LOCOI4(vect=179))
void Excep_GPT4_LOCOI4(void);

// GPT5 GTCIA5
#pragma interrupt (Excep_GPT5_GTCIA5(vect=180))
void Excep_GPT5_GTCIA5(void);

// GPT5 GTCIB5
#pragma interrupt (Excep_GPT5_GTCIB5(vect=181))
void Excep_GPT5_GTCIB5(void);

// GPT5 GTCIC5
#pragma interrupt (Excep_GPT5_GTCIC5(vect=182))
void Excep_GPT5_GTCIC5(void);

// GPT5 GTCIE5
#pragma interrupt (Excep_GPT5_GTCIE5(vect=183))
void Excep_GPT5_GTCIE5(void);

// GPT5 GTCIV5
#pragma interrupt (Excep_GPT5_GTCIV5(vect=184))
void Excep_GPT5_GTCIV5(void);

// GPT6 GTCIA6
#pragma interrupt (Excep_GPT6_GTCIA6(vect=185))
void Excep_GPT6_GTCIA6(void);

// GPT6 GTCIB6
#pragma interrupt (Excep_GPT6_GTCIB6(vect=186))
void Excep_GPT6_GTCIB6(void);

// GPT6 GTCIC6
#pragma interrupt (Excep_GPT6_GTCIC6(vect=187))
void Excep_GPT6_GTCIC6(void);

// GPT6 GTCIE6
#pragma interrupt (Excep_GPT6_GTCIE6(vect=188))
void Excep_GPT6_GTCIE6(void);

// GPT6 GTCIV6
#pragma interrupt (Excep_GPT6_GTCIV6(vect=189))
void Excep_GPT6_GTCIV6(void);

// RIIC1 EEI1
#pragma interrupt (Excep_RIIC1_EEI1(vect=190))
void Excep_RIIC1_EEI1(void);

// RIIC1 RXI1
#pragma interrupt (Excep_RIIC1_RXI1(vect=191))
void Excep_RIIC1_RXI1(void);

// RIIC1 TXI1
#pragma interrupt (Excep_RIIC1_TXI1(vect=192))
void Excep_RIIC1_TXI1(void);

// RIIC1 TEI1
#pragma interrupt (Excep_RIIC1_TEI1(vect=193))
void Excep_RIIC1_TEI1(void);

// RIIC0 EEI0
#pragma interrupt (Excep_RIIC0_EEI0(vect=194))
void Excep_RIIC0_EEI0(void);

// RIIC0 RXI0
#pragma interrupt (Excep_RIIC0_RXI0(vect=195))
void Excep_RIIC0_RXI0(void);

// RIIC0 TXI0
#pragma interrupt (Excep_RIIC0_TXI0(vect=196))
void Excep_RIIC0_TXI0(void);

// RIIC0 TEI0
#pragma interrupt (Excep_RIIC0_TEI0(vect=197))
void Excep_RIIC0_TEI0(void);

// DMAC DMAC0I
#pragma interrupt (Excep_DMAC_DMAC0I(vect=198))
void Excep_DMAC_DMAC0I(void);

// DMAC DMAC1I
#pragma interrupt (Excep_DMAC_DMAC1I(vect=199))
void Excep_DMAC_DMAC1I(void);

// DMAC DMAC2I
#pragma interrupt (Excep_DMAC_DMAC2I(vect=200))
void Excep_DMAC_DMAC2I(void);

// DMAC DMAC3I
#pragma interrupt (Excep_DMAC_DMAC3I(vect=201))
void Excep_DMAC_DMAC3I(void);

// SCI0 RXI0
#pragma interrupt (Excep_SCI0_RXI0(vect=214))
void Excep_SCI0_RXI0(void);

// SCI0 TXI0
#pragma interrupt (Excep_SCI0_TXI0(vect=215))
void Excep_SCI0_TXI0(void);

// SCI0 TEI0
#pragma interrupt (Excep_SCI0_TEI0(vect=216))
void Excep_SCI0_TEI0(void);

// SCI1 RXI1
#pragma interrupt (Excep_SCI1_RXI1(vect=217))
void Excep_SCI1_RXI1(void);

// SCI1 TXI1
#pragma interrupt (Excep_SCI1_TXI1(vect=218))
void Excep_SCI1_TXI1(void);

// SCI1 TEI1
#pragma interrupt (Excep_SCI1_TEI1(vect=219))
void Excep_SCI1_TEI1(void);

// SCI2 RXI2
#pragma interrupt (Excep_SCI2_RXI2(vect=220))
void Excep_SCI2_RXI2(void);

// SCI2 TXI2
#pragma interrupt (Excep_SCI2_TXI2(vect=221))
void Excep_SCI2_TXI2(void);

// SCI2 TEI2
#pragma interrupt (Excep_SCI2_TEI2(vect=222))
void Excep_SCI2_TEI2(void);

// SCI3 RXI3
#pragma interrupt (Excep_SCI3_RXI3(vect=223))
void Excep_SCI3_RXI3(void);

// SCI3 TXI3
#pragma interrupt (Excep_SCI3_TXI3(vect=224))
void Excep_SCI3_TXI3(void);

// SCI3 TEI3
#pragma interrupt (Excep_SCI3_TEI3(vect=225))
void Excep_SCI3_TEI3(void);

// GPT0 GTCIA0
#pragma interrupt (Excep_GPT0_GTCIA0(vect=226))
void Excep_GPT0_GTCIA0(void);

// GPT0 GTCIB0
#pragma interrupt (Excep_GPT0_GTCIB0(vect=227))
void Excep_GPT0_GTCIB0(void);

// GPT0 GTCIC0
#pragma interrupt (Excep_GPT0_GTCIC0(vect=228))
void Excep_GPT0_GTCIC0(void);

// GPT0 GTCIE0
#pragma interrupt (Excep_GPT0_GTCIE0(vect=229))
void Excep_GPT0_GTCIE0(void);

// GPT0 GTCIV0
#pragma interrupt (Excep_GPT0_GTCIV0(vect=230))
void Excep_GPT0_GTCIV0(void);

// GPT0 LOCOI0
#pragma interrupt (Excep_GPT0_LOCOI0(vect=231))
void Excep_GPT0_LOCOI0(void);

// GPT1 GTCIA1
#pragma interrupt (Excep_GPT1_GTCIA1(vect=232))
void Excep_GPT1_GTCIA1(void);

// GPT1 GTCIB1
#pragma interrupt (Excep_GPT1_GTCIB1(vect=233))
void Excep_GPT1_GTCIB1(void);

// GPT1 GTCIC1
#pragma interrupt (Excep_GPT1_GTCIC1(vect=234))
void Excep_GPT1_GTCIC1(void);

// GPT1 GTCIE1
#pragma interrupt (Excep_GPT1_GTCIE1(vect=235))
void Excep_GPT1_GTCIE1(void);

// GPT1 GTCIV1
#pragma interrupt (Excep_GPT1_GTCIV1(vect=236))
void Excep_GPT1_GTCIV1(void);

// GPT2 GTCIA2
#pragma interrupt (Excep_GPT2_GTCIA2(vect=238))
void Excep_GPT2_GTCIA2(void);

// GPT2 GTCIB2
#pragma interrupt (Excep_GPT2_GTCIB2(vect=239))
void Excep_GPT2_GTCIB2(void);

// GPT2 GTCIC2
#pragma interrupt (Excep_GPT2_GTCIC2(vect=240))
void Excep_GPT2_GTCIC2(void);

// GPT2 GTCIE2
#pragma interrupt (Excep_GPT2_GTCIE2(vect=241))
void Excep_GPT2_GTCIE2(void);

// GPT2 GTCIV2
#pragma interrupt (Excep_GPT2_GTCIV2(vect=242))
void Excep_GPT2_GTCIV2(void);

// GPT3 GTCIA3
#pragma interrupt (Excep_GPT3_GTCIA3(vect=244))
void Excep_GPT3_GTCIA3(void);

// GPT3 GTCIB3
#pragma interrupt (Excep_GPT3_GTCIB3(vect=245))
void Excep_GPT3_GTCIB3(void);

// GPT3 GTCIC3
#pragma interrupt (Excep_GPT3_GTCIC3(vect=246))
void Excep_GPT3_GTCIC3(void);

// GPT3 GTCIE3
#pragma interrupt (Excep_GPT3_GTCIE3(vect=247))
void Excep_GPT3_GTCIE3(void);

// GPT3 GTCIV3
#pragma interrupt (Excep_GPT3_GTCIV3(vect=248))
void Excep_GPT3_GTCIV3(void);

// SCI12 RXI12
#pragma interrupt (Excep_SCI12_RXI12(vect=250))
void Excep_SCI12_RXI12(void);

// SCI12 TXI12
#pragma interrupt (Excep_SCI12_TXI12(vect=251))
void Excep_SCI12_TXI12(void);

// SCI12 TEI12
#pragma interrupt (Excep_SCI12_TEI12(vect=252))
void Excep_SCI12_TEI12(void);

//;<<VECTOR DATA START (POWER ON RESET)>>
//;Power On Reset PC
extern void PowerON_Reset_PC(void);                                                                                                                
//;<<VECTOR DATA END (POWER ON RESET)>>

