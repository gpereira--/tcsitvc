/*
** ###################################################################
**     This code is generated by the Device Initialization Tool.
**     It is overwritten during code generation.
**     USER MODIFICATION ARE PRESERVED ONLY INSIDE EXPLICITLY MARKED SECTIONS.
**
**     Project   : ELE3000_v0_4
**     Processor : MC9S12XDP512BMPV
**     Version   : Component 02.003, Driver 01.05, CPU db: 2.87.229
**     Datasheet : MC9S12XDP512RMV2 Rev. 2.18 May 2008
**     Date/Time : 2012-06-05, 20:48
**     Abstract  :
**         This module contains device initialization code 
**         for selected on-chip peripherals.
**     Contents  :
**         Function "MCU_init" initializes selected peripherals
**
**     Copyright : 1997 - 2010 Freescale Semiconductor, Inc. All Rights Reserved.
**     
**     http      : www.freescale.com
**     mail      : support@freescale.com
** ###################################################################
*/

#ifndef __ELE3000_v0_4_H
#define __ELE3000_v0_4_H 1

/* Include shared modules, which are used for whole project */


/* User declarations and definitions */
/*   Code, declarations and definitions here will be preserved during code generation */
/* End of user declarations and definitions */
#pragma CODE_SEG DEFAULT

extern void MCU_init(void);
/*
** ===================================================================
**     Method      :  MCU_init (component MC9S12XDP512_112)
**
**     Description :
**         Device initialization code for selected peripherals.
** ===================================================================
*/



/*lint -save  -e765 Disable MISRA rule (8.10) checking. */
#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isr_default(void);
/*
** ===================================================================
**     Interrupt handler : isr_default
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVcan2tx(void);
/*
** ===================================================================
**     Interrupt handler : isrVcan2tx
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVcan2rx(void);
/*
** ===================================================================
**     Interrupt handler : isrVcan2rx
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVcan2err(void);
/*
** ===================================================================
**     Interrupt handler : isrVcan2err
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVcan2wkup(void);
/*
** ===================================================================
**     Interrupt handler : isrVcan2wkup
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVcan1tx(void);
/*
** ===================================================================
**     Interrupt handler : isrVcan1tx
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVcan1rx(void);
/*
** ===================================================================
**     Interrupt handler : isrVcan1rx
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVcan1err(void);
/*
** ===================================================================
**     Interrupt handler : isrVcan1err
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVcan1wkup(void);
/*
** ===================================================================
**     Interrupt handler : isrVcan1wkup
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVcan0tx(void);
/*
** ===================================================================
**     Interrupt handler : isrVcan0tx
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVcan0rx(void);
/*
** ===================================================================
**     Interrupt handler : isrVcan0rx
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVcan0err(void);
/*
** ===================================================================
**     Interrupt handler : isrVcan0err
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVcan0wkup(void);
/*
** ===================================================================
**     Interrupt handler : isrVcan0wkup
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrViic0(void);
/*
** ===================================================================
**     Interrupt handler : isrViic0
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void IsrPortH(void);
/*
** ===================================================================
**     Interrupt handler : IsrPortH
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void IsrAtd0(void);
/*
** ===================================================================
**     Interrupt handler : IsrAtd0
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void isrVspi0(void);
/*
** ===================================================================
**     Interrupt handler : isrVspi0
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void IsrRti(void);
/*
** ===================================================================
**     Interrupt handler : IsrRti
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void IsrCop(void);
/*
** ===================================================================
**     Interrupt handler : IsrCop
**
**     Description :
**         User interrupt service routine. 
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma CODE_SEG DEFAULT



/*lint -restore Enable MISRA rule (8.10) checking. */



/* END ELE3000_v0_4 */

#endif
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.02 [04.44]
**     for the Freescale HCS12X series of microcontrollers.
**
** ###################################################################
*/
