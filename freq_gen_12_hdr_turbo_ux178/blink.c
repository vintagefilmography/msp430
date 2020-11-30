/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP430G2xx1 Demo - Timer_A, Toggle P1.0, CCR0 Cont. Mode ISR, DCO SMCLK
//
//  Description: Toggle P1.0 using software and TA_0 ISR. Toggles every
//  50000 SMCLK cycles. SMCLK provides clock source for TACLK.
//  During the TA_0 ISR, P1.0 is toggled and 50000 clock cycles are added to
//  CCR0. TA_0 ISR is triggered every 50000 cycles. CPU is normally off and
//  used only during TA_ISR.
//  ACLK = n/a, MCLK = SMCLK = TACLK = default DCO
//
//           MSP430G2xx1
//         ---------------
//     /|\|            XIN|-
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//
//  D. Dang
//  Texas Instruments Inc.
//  October 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

#include <msp430.h>
unsigned int volatile counter = 0;   // main counter
unsigned int volatile cap_counter = 0;   // capstan counter
unsigned int volatile enable_cap;  // enable capstan in slow mode
unsigned int volatile toggle = 1;
unsigned int volatile frame_count = 0;
unsigned int volatile frame_count_toggle = 0;
unsigned int volatile keep_stepper_off = 0;
unsigned int volatile start_counter = 0;
unsigned long volatile alert_counter = 0;
unsigned int volatile cap_delay = 0;

int main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P1DIR |= 0x1b;                            // P1.0 P1.1 P1.8 output
  P2DIR &= ~BIT6;
  P2DIR |= BIT7;
  P1SEL = 0;
  P2SEL = 0;
  CCTL0 = CCIE;                             // CCR0 interrupt enabled
  CCR0 = 50000;
  TACTL = TASSEL_2 + MC_2;                  // SMCLK, contmode
  P1OUT = P1OUT & 0xFD;                     // Turn off TKM
  P1OUT = P1OUT & 0xEF;                     // Turn capstan motor off
  P1OUT = P1OUT | 0x08;                     // Turn stepper on
  P1REN = 0;

  // Set clock to 4MHz
  BCSCTL1 &= ~(BIT2);                 // set to DCO(11,3)
  BCSCTL1 |= (BIT3 + BIT1 + BIT0);
  DCOCTL &= ~BIT7;
  DCOCTL |= BIT5 + BIT6;

  __bis_SR_register(LPM0_bits + GIE);       // Enter LPM0 w/ interrupt
}

// Timer A0 interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMERA0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMERA0_VECTOR))) Timer_A (void)
#else
#error Compiler not supported!
#endif
{
  P1OUT ^= 0x01;    // Toggle P1.0  --- Step clock


  if(P1IN & BIT5)       //speed1 check
  {
      CCR0 += 84*4;       // 1 seconds per frame 76*4
      //enable_cap = 0;   // cannot run capstan in fast mode
      if(counter == 100)
        {
            P1OUT = P1OUT | 0x02;
        }
      if(counter == 750)
      {
          P1OUT = P1OUT & 0xFD;
      }
      if(counter == 4500)     // Turn cam trigger on 3800
      {
          P2OUT = P2OUT | 0x80;
      }
      if(counter == 4550)     // Turn cam trigger off 3810
      {
          P2OUT = P2OUT & 0x7F;
      }
  }

  else
  {

      CCR0 += 220*4;      // 2 seconds per frame  170 for 2sec 340 for 4 seconds
       if(counter == 100)
         {
             P1OUT = P1OUT | 0x02;
         }
       if((counter == 300)&&(frame_count > 1800))
       {
           P1OUT = P1OUT & 0xFD;
       }
       if((counter == 500)&&(frame_count <= 1800))
       {
           P1OUT = P1OUT & 0xFD;
       }

       // Triggers
       if(counter == 4500)         // First camera sync 4500
       {
           P2OUT = P2OUT | 0x80;
       }
       if(counter == 4508)
       {
           P2OUT = P2OUT & 0x7F;
       }

       if(counter == 5800)         // Second camera sync 6500
       {
           P2OUT = P2OUT | 0x80;
       }
       if(counter == 5808)
       {
           P2OUT = P2OUT & 0x7F;
       }

       if(counter == 7100)         // Third camera sync was 9700
       {
           P2OUT = P2OUT | 0x80;
       }
       if(counter == 7108)
       {
           P2OUT = P2OUT & 0x7F;
       }

       if(counter == 8400)         // Forth camera sync 11700
       {
           P2OUT = P2OUT | 0x80;
       }
       if(counter == 8408)
       {
           P2OUT = P2OUT & 0x7F;
       }

  }
      // Frame counter
      if((P1IN & BIT2)&&(P1IN & BIT7))       // Frame Sync and on/off check
      {
          if(frame_count_toggle == 0)
          {
              frame_count++;
              frame_count_toggle = 1;       // Additional delay at start of sync for cam exposure
          }
      }
      else
      {
          frame_count_toggle = 0;
      }


//=============================CAPSTAN
      if(P1IN & BIT6)                           // Activate capstan only if rewind is on
      {
           if((P2IN & BIT6) && (toggle == 0))   //capstan activity check
           {
               cap_counter = 0;
               toggle = 1;
           }
           else if(((P2IN & BIT6) == 0)&&(toggle == 1)) //activity toggle check
           {
               cap_counter = 0;
               toggle = 0;

           }
           else
           {
               cap_counter++;   // increment capstan counter
           }

           if(cap_counter > 30000)   // capstan active interval
               {
               //P1OUT = P1OUT | 0x10;  // Turn capstan motor on if takeup sw is on
               P1OUT = P1OUT & 0xF7;  // Turn stepper off
               keep_stepper_off = 1;
               cap_counter = 30100;    // latch counter so it does not roll over
               alert_counter++;        // used in stuck mode to run duty cycle
               if(alert_counter>>2 == 15000)     //film stuck for 10 seconds then capstan/alert on for 2 seconds
               {
                   P1OUT = P1OUT | 0x10;     //Turn capstan motor on
               }
               if(alert_counter>>2 > (15000 + 3000))     // and after 2 second capstan/alert turn it off for another 10 seconds
               {
                   P1OUT = P1OUT & 0xEF;  // Turn capstan motor off
                   alert_counter = 0;     // reset alert counter to start 10 second off interval -- cool down
               }
           }
           else
           {
              cap_delay++;
              if(cap_delay > 500)
              {
                  cap_delay = 0;
                  P1OUT = P1OUT & 0xEF;  // Turn capstan motor off
                  keep_stepper_off = 0;
                  alert_counter = 0;
              }
           }

     }
//======================================= END OF CAPSTAN

      if(P1IN & BIT2)       // Reset counter if Frame Sync
      {
          counter = 0;
          start_counter = 1;
      }
      else
      {
          if(start_counter == 1)
                 counter++;
      }


      if(P1IN & BIT7)       // On Off control
      {
          if(keep_stepper_off == 0)
              P1OUT = P1OUT | 0x08;     //ON
      }
      else
      {
          P1OUT = P1OUT & 0xf7;     //OFF
          counter = 0;
          start_counter = 0;
          cap_counter = 0;
          cap_delay = 0;
          alert_counter = 0;
          if (P1IN & BIT6)     //Turn takeup on (rewind)
          {
              P1OUT = P1OUT | 0x02;
          }
          else
          {
              P1OUT = P1OUT & 0xFD;
          }
          P1OUT = P1OUT & 0xEF;  // Turn capstan motor off
          keep_stepper_off = 0;
      }

}
