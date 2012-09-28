#include <hidef.h>      /* common defines and macros */
#include "derivative.h"      /* derivative-specific definitions */
#include "MCUinit.h"

typedef unsigned char   uint8;
typedef unsigned int    uint16;
typedef unsigned long   uint32;


//Leds
#define LED_ET_LUM_FREINS       PORTA_PA0
#define LED_ACCEL               PORTA_PA1
#define LED_VSYNC               PORTA_PA3
#define LED_ERR                 PORTA_PA4
#define LED_ACCEL_ERR           PORTA_PA7

//Ready to drive
#define READY_TO_DRIVE_IN       PORTE_PE0       //Fil blanc + pull-down
#define READY_TO_DRIVE_OUT      PTH_PTH0        //Fil noir
// #define RTDS_DURATION           8000            //nombre de p�riodes de 250 us
// #define RTDS_PERIOD_ON             2000             //nombre de p�riodes de 250 us avant le toggle du son
// #define RTDS_PERIOD_OFF             500             //nombre de p�riodes de 250 us avant le toggle du son
#define RTDS_DURATION_01           4000
#define RTDS_DURATION_02           1000
#define RTDS_DURATION_03           7000 


//Dac
#define DAC_CS_N    PTS_PTS7
#define DAC_LDAC  PORTK_PK2

//op-amps
#define OPAMP_EN    PORTK_PK1

//TODO: ajustements offset et plage sur freins
//TODO: d�terminer les offset au d�but du programme?

//Ajustements
#define ACCEL1_OFFSET            125 // 24
#define ACCEL2_OFFSET            21 //-90 //137
#define BRAKES_OFFSET            510

//Limites acceleration et freins 
#define HIGH_ACCEL_DIFF         130         //100 correspond � 10%
#define LOW_ACCEL_DIFF          50
#define INACTIV_ACCEL_THRES     100        //Correspond � 50 pour chaque potentiom�tre donc 5%
#define ACTIV_ACCEL_THRES       50
#define ACTIV_ACCEL_BRAKE_THRES 400         //Correspond � 200 pour chaque potentiom�tre donc 20%
#define INACTIV_FREINS_THRES    10
#define ACTIV_FREINS_THRES      20


uint16 freins = 0;
uint16 accel = 0;                       //accel est la somme des deux accel. Il est sur 11 bits
uint16 accel1 = 0;
uint16 accel2 = 1024;

//test
volatile uint16 gAccelDiffTmp = 0;
volatile uint16 gAccel2Inv = 0;
volatile uint16 gAccel2Adj = 0;
volatile uint16 gAccel1Adj = 0;
volatile uint16 gFreinsAdj = 0;
//test

volatile uint16 yo = 0;

void MCU_init(void);
void SpiSend(unsigned int data);

void main(void) {
  
    
    MCU_init();
    PORTA = 0x00;
    OPAMP_EN = 1;

  for(;;) {
    yo++;
    /* _FEED_COP(); by default, COP is disabled with device init. When enabling, also reset the watchdog. */
  
    //LED_ERR = 0;      // Aide pour le debug: enl�ve l'erreur pour le watchdog timer
    
    //MAT:  c'est �trange on dirait qu'on ne vient jamais dans le main...
    //      les interrupts RTI sont peut-�tre trop fr�quentes � 4 kHz
  }
}

void SafetyCheck(void)
{
	uint16 accelDiff, tmpAccel = 0;
   uint16 accel1Adj, accel2Adj, freinsAdj;
    static uint8 accErr = 0;
    static uint8 accDiffErr = 0;
       
    if(accel1 > ACCEL1_OFFSET) {
      accel1Adj = accel1 - ACCEL1_OFFSET;
      accel1Adj = (38*accel1Adj)>>5;         //redimensionnement de l'acc�l�ration car
      if(accel1Adj > 1023)                   //la valeur maximale lue est de 844. Don c
         accel1Adj = 1023;                   //1024/844 = 1.21 = 39/32               
    } else {
      accel1Adj = 0;
    }
    
    accel2Adj = 1024 - accel2;               //les potentiom�tres sont branch�s � l'inverse
    
    //tmp
    gAccel2Inv = accel2Adj;
    //tmp
    
    if(accel2Adj > ACCEL2_OFFSET) {          //pour augmenter s�curit�.
      accel2Adj -= ACCEL2_OFFSET;
      accel2Adj = (42*accel2Adj)>>5;         //redimensionnement de l'acc�l�ration car
      if(accel2Adj > 1023)                   //la valeur maximale lue est de 696. Donc
         accel2Adj = 1023;                   // 1024/752 = 1.36 = 44/32
    } else {
      accel2Adj = 0;
    }
      
    if(freins > BRAKES_OFFSET)
      freinsAdj = freins - BRAKES_OFFSET;    
    else 
      freinsAdj = 0;
      
      
    //Les deux potentiom�tres d'acc�l�ration sont en redondance
    //On d�termine leur diff�rence pour s'assurer d'une bonne lecture
    //Hyst�r�sis :  diff�rence trop grande si sup�rieure � 10%
    //              on annule l'erreur si la diff�rence descend sous 5%
    if(accel1Adj > accel2Adj)
        accelDiff = accel1Adj - accel2Adj;
    else
        accelDiff = accel2Adj - accel1Adj;         
   
   //test
   gAccelDiffTmp = accelDiff;
   gAccel1Adj = accel1Adj;
   gAccel2Adj = accel2Adj;
   gFreinsAdj = freinsAdj;
   //test
   
	if (accelDiff > HIGH_ACCEL_DIFF)
        accDiffErr = 1;
	else if(accelDiff < LOW_ACCEL_DIFF)
        accDiffErr = 0;
	
    tmpAccel = accel1Adj + accel2Adj;
	
    //Hyst�r�sis sur les freins.
    //Actifs si sup�rieur � 10%. Inactif si inf�rieur � 5%.
	if(freinsAdj > ACTIV_FREINS_THRES)
	{
		//Freins actionn�s
		LED_ET_LUM_FREINS = 1;
		
        
        //Hyst�r�sis sur la d�tection d'une erreur d'acc�l�ration
        //Si accel > 20% alors erreur et si accel < 5% on enl�ve
        //l'erreur
		if(tmpAccel > ACTIV_ACCEL_BRAKE_THRES)
			accErr = 1;         //Acc�l�rateur enfonc� en m�me temps que les freins !!!
		else if(tmpAccel < INACTIV_ACCEL_THRES)
			accErr = 0;         //Acc�l�rateur rel�ch�
        
		//LED_VSYNC = 0;
	}
	else if(freinsAdj < INACTIV_FREINS_THRES)
	{
		//Freins rel�ch�s
		LED_ET_LUM_FREINS = 0;
		
        //Il faut rel�cher les freins ET l'acc�l�ration lorsqu'il y a eu une erreur
        //d'acc�l�ration
        if (tmpAccel < INACTIV_ACCEL_THRES)  
            accErr = 0;         //Acc�l�rateur rel�ch�

		//LED_VSYNC = (accel < 40);   //Vsync: pour synchroniser la vitesse
	}
	
    
    //On coupe l'acc�l�ration si on freine en m�me temps ou
    //qu'il y a un �cart trop grand entre les valeurs des 2 potentiom�tres

    if(accErr || accDiffErr) {
        accel = 0;
        LED_ACCEL_ERR = 1;  
    } else {
        accel = tmpAccel;
        LED_ACCEL_ERR = 0;
    }
    
    
	LED_ACCEL = (accel > ACTIV_ACCEL_THRES);    //On acc�l�re quand on acc�l�re � plus que 5%
	
	//OPAMP_EN &= (accel != 0);   //On d�sactive la sortie des amplis op quand on n'acc�l�re pas
	
}

void SpiSend(uint16 data)         //On doit envoyer deux mots de 16 bits, donc voici le hack pour le SPI
{
	// LDAC = 1
	DAC_LDAC = 1;
	
	//Send MSB DAC_A
	DAC_CS_N = 0;
//	SPI0SR_SPIF = 1;
	SPI0DR = 0x10 | (data >> 7);
	
	//Wait
//	while(!SPI0SR_SPIF);
	while(!SPI0SR_SPTEF);	
	
	//Send LSB DAC_A
//	SPI0SR_SPIF = 1;
	SPI0DR = data << 1;
		
	//Wait
//	while(!SPI0SR_SPIF);
	while(!SPI0SR_SPTEF);	
	
	
	
	//Send MSB DAC_B
//	SPI0SR_SPIF = 1;
	SPI0DR = 0x90 | (data >> 7);
	
	//Wait
//	while(!SPI0SR_SPIF);
	while(!SPI0SR_SPTEF);
	
	DAC_CS_N = 1;
	DAC_CS_N = 0;
	
	//Send LSB DAC_B
//	SPI0SR_SPIF = 1;
	SPI0DR = data << 1;
  	
	//Wait
//	while(!SPI0SR_SPIF);
	while(!SPI0SR_SPTEF);
	SPI0DR = 0;
	while(!SPI0SR_SPTEF);	
	DAC_CS_N = 1;

	
	// LDAC = 0
	DAC_LDAC = 0;
	
	//Enable OpAmps
	//OPAMP_EN = (data != 0);
}

void emitReadyToDriveSound(void)
{
    // static uint16 intCount = 0;
    // static uint16 periodCount = 0;
    static uint16 soundPeriodCount = 0;
    static uint16 soundTotTimeCount = 0;
    static uint16 rtdHistory = 0;
    static uint8 rtdActive = 0;
    static uint8 emittingSound = 0;
    static uint8 soundDone = 0;
    uint16 curRtd;
    uint8 tmp = 0;
                    
    //On d�termine l'�tat de l'entr�e ready-to-drive (rtd).
    //On attend d'avoir re�u 16 valeurs (4 ms @ 4 kHz) identiques avant de
    //consid�rer un changement de la variable interne (debouncing).
    curRtd = (uint16) READY_TO_DRIVE_IN;
    rtdHistory = rtdHistory<<1;
    rtdHistory = rtdHistory | (curRtd & 0x1);
    
   
    if((rtdHistory & 0xFFFF) == 0xFFFF)      //On assume la logique normale, i.e. 1 = RTDS ON
        rtdActive = 1;
    else if(rtdHistory == 0)
        rtdActive = 0;        
    
//temp
   // if(gFreinsAdj > 20)
      // rtdActive = 1;
   // else
      // rtdActive = 0;
//temp

    
    // if(rtdActive) {
        // if(intCount < RTDS_DURATION) {    //8000 pour une dur�e 2 secondes avec un interrupt � 4 kHz
            // READY_TO_DRIVE_OUT = 1;
            // intCount++;
        // } else {
            // READY_TO_DRIVE_OUT = 0;
        // }
    // } else {
        // READY_TO_DRIVE_OUT = 0;
        // intCount = 0;
    // }

    
    // if(emittingSound) {
       // soundPeriodCount++;
       // soundTotTimeCount++;
       // if(soundTotTimeCount < RTDS_DURATION) {
         // if(soundPeriodCount >= RTDS_PERIOD_ON && READY_TO_DRIVE_OUT) {    //Fin on time
            // soundPeriodCount = 0;
            // READY_TO_DRIVE_OUT = 0;
         // } else if (soundPeriodCount >= RTDS_PERIOD_OFF && !READY_TO_DRIVE_OUT) {  //Fin off time
            // soundPeriodCount = 0;
            // READY_TO_DRIVE_OUT = 1;
         // }
       // } else {      //Son a joue au complet
         // emittingSound = 0;
         // soundDone = 1;
         // soundPeriodCount = 0;
         // soundTotTimeCount = 0;
         // READY_TO_DRIVE_OUT  = 0;
       // }
    // } else if(!rtdActive) {
       // soundDone = 0;
    // } else if(rtdActive  && !soundDone) {
       // emittingSound = 1;
    // }
     
     
    if(emittingSound) {
       soundTotTimeCount++;
       if(soundTotTimeCount < RTDS_DURATION_01) {
           READY_TO_DRIVE_OUT = 1;
       } else if(soundTotTimeCount < RTDS_DURATION_02) {
           READY_TO_DRIVE_OUT = 0;
       } else if(soundTotTimeCount < RTDS_DURATION_03) {
           READY_TO_DRIVE_OUT = 1;       
       } else {      //Son a joue au complet
           emittingSound = 0;
           soundDone = 1;
           soundTotTimeCount = 0;
           READY_TO_DRIVE_OUT  = 0;
       }
    } else if(!rtdActive) {
       soundDone = 0;
    } else if(rtdActive  && !soundDone) {
       emittingSound = 1;
    }
    
}

#pragma CODE_SEG __SHORT_SEG NON_BANKED
__interrupt void IsrCop(void) {
 
  LED_ERR = 1;
  SpiSend(0);       //Send accel=0 to DAC
}
#pragma CODE_SEG DEFAULT