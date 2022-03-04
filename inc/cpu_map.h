/*
  cpu_map.h - CPU and pin mapping configuration file
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* The cpu_map.h files serve as a central pin mapping selection file for different
   processor types or alternative pin layouts. This version of Grbl officially supports
   only the Arduino Mega328p. */


#ifndef cpu_map_h
#define cpu_map_h




  // Define serial port pins and interrupt vectors.


#ifdef CPU_MAP_STM32F103

  // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define STEP_PORT       GPIOA
#define RCC_STEP_PORT   RCC_APB2Periph_GPIOA
#define X_STEP_BIT      0  
#define Y_STEP_BIT      1  
#define Z_STEP_BIT      2
#define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits

  // Define step direction output pins. NOTE: All direction pins must be on the same port.
#define DIRECTION_PORT      GPIOA
#define RCC_DIRECTION_PORT   RCC_APB2Periph_GPIOA
#define X_DIRECTION_BIT   3  
#define Y_DIRECTION_BIT   4  
#define Z_DIRECTION_BIT   5
#define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits

  // Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLE_PORT   GPIOA
#define RCC_STEPPERS_DISABLE_PORT RCC_APB2Periph_GPIOA
#define STEPPERS_DISABLE_BIT    6  
#define STEPPERS_DISABLE_MASK   (1<<STEPPERS_DISABLE_BIT)
#define SetStepperDisableBit() GPIO_SetBits(STEPPERS_DISABLE_PORT,STEPPERS_DISABLE_MASK)
#define ResetStepperDisableBit() GPIO_ResetBits(STEPPERS_DISABLE_PORT,STEPPERS_DISABLE_MASK)


  // Define homing/hard limit switch input pins and limit interrupt vectors. 
  // NOTE: All limit bit pins must be on the same port
#define LIMIT_PIN        GPIOB
#define LIMIT_PORT       GPIOB
#define RCC_LIMIT_PORT   RCC_APB2Periph_GPIOB
#define GPIO_LIMIT_PORT  GPIO_PortSourceGPIOB
#define X_LIMIT_BIT      10  
#define Y_LIMIT_BIT      11  
#define Z_LIMIT_BIT      12  

#define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits

  // Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_PORT   GPIOB
#define RCC_SPINDLE_ENABLE_PORT RCC_APB2Periph_GPIOB
#define SPINDLE_ENABLE_BIT    13  // 
#ifndef USE_SPINDLE_DIR_AS_ENABLE_PIN
#define SPINDLE_DIRECTION_DDR   GPIOB
#define SPINDLE_DIRECTION_PORT  GPIOB
#define SPINDLE_DIRECTION_BIT   14  // 
#endif
#define SetSpindleEnablebit()       GPIO_WriteBit(SPINDLE_ENABLE_PORT, 1 << SPINDLE_ENABLE_BIT, Bit_SET)
#define ResetSpindleEnablebit()     GPIO_WriteBit(SPINDLE_ENABLE_PORT, 1 << SPINDLE_ENABLE_BIT, Bit_RESET)
#define SetSpindleDirectionBit()    GPIO_WriteBit(SPINDLE_DIRECTION_PORT, 1 << SPINDLE_DIRECTION_BIT,Bit_SET)
#define ResetSpindleDirectionBit()  GPIO_WriteBit(SPINDLE_DIRECTION_PORT, 1 << SPINDLE_DIRECTION_BIT,Bit_RESET)


  // Define flood and mist coolant enable output pins.
  // a later date if flash and memory space allows.
#define COOLANT_FLOOD_PORT            GPIOB
#define RCC_COOLANT_FLOOD_PORT        RCC_APB2Periph_GPIOB
#define COOLANT_FLOOD_BIT             3  
#define COOLANT_MIST_PORT             GPIOB
#define RCC_COOLANT_MIST_PORT         RCC_APB2Periph_GPIOB
#define COOLANT_MIST_BIT              4 

  // Define user-control controls (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define CONTROL_PIN_PORT              GPIOB
#define CONTROL_PORT                  GPIOB
#define RCC_CONTROL_PORT              RCC_APB2Periph_GPIOB
#define GPIO_CONTROL_PORT             GPIO_PortSourceGPIOB
#define CONTROL_RESET_BIT             5  
#define CONTROL_FEED_HOLD_BIT         6  
#define CONTROL_CYCLE_START_BIT       7  
#define CONTROL_SAFETY_DOOR_BIT       8  
#define CONTROL_MASK                 ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))

  // Define probe switch input pin.
#define PROBE_PORT                    GPIOA
#define RCC_PROBE_PORT                RCC_APB2Periph_GPIOA
#define PROBE_BIT                     15 
#define PROBE_MASK                    (1<<PROBE_BIT)

  // Start of PWM & Stepper Enabled Spindle
#ifdef VARIABLE_SPINDLE

  // NOTE: On the 328p, these must be the same as the SPINDLE_ENABLE settings.
#define SPINDLE_PWM_FREQUENCY       10000                   // KHz
#define SPINDLE_PWM_DDR	            GPIOA
#define SPINDLE_PWM_PORT            GPIOA
#define RCC_SPINDLE_PWM_PORT        RCC_APB2Periph_GPIOA
#define SPINDLE_PWM_BIT	            8    
#endif // End of VARIABLE_SPINDLE
#define SPINDLE_PWM_MAX_VALUE       (1000000 / SPINDLE_PWM_FREQUENCY)
#ifndef SPINDLE_PWM_MIN_VALUE
#define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
#endif
#define SPINDLE_PWM_OFF_VALUE     0
#define SPINDLE_PWM_RANGE         (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)

  //  Port A                                         Port B
  //   0      X_STEP_BIT                             
  //   1      Y_STEP_BIT                            
  //   2      Z_STEP_BIT                               
  //   3      X_DIRECTION_BIT                       COOLANT_FLOOD_BIT
  //   4      Y_DIRECTION_BIT                       COOLANT_MIST_BIT
  //   5      Z_DIRECTION_BIT                       CONTROL_RESET_BIT
  //   6      STEPPERS_DISABLE_BIT                  CONTROL_FEED_HOLD_BIT    
  //   7                                            CONTROL_CYCLE_START_BIT
  //   8      SPINDLE_PWM_BIT                       CONTROL_SAFETY_DOOR_BIT    
  //   9                             
  //   10                                            X_LIMIT_BIT
  //   11                                            Y_LIMIT_BIT
  //   12                                            Z_LIMIT_BIT
  //   13 14 SWD																		SPINDLE_ENABLE_BIT
//     14																						SPINDLE_DIRECTION_BIT
  //   15     PROBE_BIT					

#endif

#ifdef ABC_AXIS_EXAMPLE

  // Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define STEP_PORT       GPIOA
#define RCC_STEP_PORT   RCC_APB2Periph_GPIOA
#ifdef ABC_AXIS
#define C_STEP_BIT      13
#endif
#if defined(AB_AXIS) || defined(ABC_AXIS)
#define B_STEP_BIT      11
#endif
#define X_STEP_BIT      0
#define Y_STEP_BIT      1
#define Z_STEP_BIT      2
#if defined(AA_AXIS) || defined(AB_AXIS) || defined(ABC_AXIS)
#define A_STEP_BIT      3
#endif
#ifdef AA_AXIS
#define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)|(1<<A_STEP_BIT)) // All step bits
#elif defined(AB_AXIS)
#define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)|(1<<A_STEP_BIT)|(1<<B_STEP_BIT)) // All step bits
#elif defined(ABC_AXIS)
#define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)|(1<<A_STEP_BIT)|(1<<B_STEP_BIT)|(1<<C_STEP_BIT)) // All step bits
#else
#define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits
#endif

  // Define step direction output pins. NOTE: All direction pins must be on the same port.
#define DIRECTION_PORT      GPIOA
#define RCC_DIRECTION_PORT   RCC_APB2Periph_GPIOA
#ifdef ABC_AXIS
#define C_DIRECTION_BIT   14
#endif
#if defined(AB_AXIS) || defined(ABC_AXIS)
#define B_DIRECTION_BIT   12
#endif
#define X_DIRECTION_BIT   4
#define Y_DIRECTION_BIT   5
#define Z_DIRECTION_BIT   6
#if defined(AA_AXIS) || defined(AB_AXIS) || defined(ABC_AXIS)
#define A_DIRECTION_BIT   7
#endif
#ifdef AA_AXIS
#define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)|(1<<A_DIRECTION_BIT)) // All direction bits
#elif defined(AB_AXIS)
#define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)|(1<<A_DIRECTION_BIT)|(1<<B_DIRECTION_BIT)) // All direction bits
#elif defined(ABC_AXIS)
#define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)|(1<<A_DIRECTION_BIT)|(1<<B_DIRECTION_BIT)|(1<<C_DIRECTION_BIT)) // All direction bits
#else
#define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits
#endif

  // Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLE_PORT   GPIOA
#define RCC_STEPPERS_DISABLE_PORT RCC_APB2Periph_GPIOA
#define STEPPERS_DISABLE_BIT    15
#define STEPPERS_DISABLE_MASK   (1<<STEPPERS_DISABLE_BIT)
#define SetStepperDisableBit() GPIO_SetBits(STEPPERS_DISABLE_PORT,STEPPERS_DISABLE_MASK)
#define ResetStepperDisableBit() GPIO_ResetBits(STEPPERS_DISABLE_PORT,STEPPERS_DISABLE_MASK)


  // Define homing/hard limit switch input pins and limit interrupt vectors.
  // NOTE: All limit bit pins must be on the same port
#define LIMIT_PIN        GPIOB
#define LIMIT_PORT       GPIOB
#define RCC_LIMIT_PORT   RCC_APB2Periph_GPIOB
#define GPIO_LIMIT_PORT  GPIO_PortSourceGPIOB
#ifdef ABC_AXIS
#define C_LIMIT_BIT      10
#endif
#if defined(AB_AXIS) || defined(ABC_AXIS)
#define B_LIMIT_BIT      11
#endif
#define X_LIMIT_BIT      12
#define Y_LIMIT_BIT      13
#define Z_LIMIT_BIT      14
#if defined(AA_AXIS) || defined(AB_AXIS) || defined(ABC_AXIS)
#define A_LIMIT_BIT      15
#endif
#ifdef AA_AXIS
#define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)|(1<<A_LIMIT_BIT)) // All limit bits
#elif defined(AB_AXIS)
#define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)|(1<<A_LIMIT_BIT)|(1<<B_LIMIT_BIT)) // All limit bits
#elif defined(ABC_AXIS)
#define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)|(1<<A_LIMIT_BIT)|(1<<B_LIMIT_BIT)|(1<<C_LIMIT_BIT)) // All limit bits
#else
#define LIMIT_MASK       ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits
#endif

  // Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_PORT   GPIOB
#define RCC_SPINDLE_ENABLE_PORT RCC_APB2Periph_GPIOB
#define SPINDLE_ENABLE_BIT    1  //
#ifndef USE_SPINDLE_DIR_AS_ENABLE_PIN
#define SPINDLE_DIRECTION_DDR   GPIOB
#define SPINDLE_DIRECTION_PORT  GPIOB
#define SPINDLE_DIRECTION_BIT   0  //
#endif
#define SetSpindleEnablebit()       GPIO_WriteBit(SPINDLE_ENABLE_PORT, 1 << SPINDLE_ENABLE_BIT, Bit_SET)
#define ResetSpindleEnablebit()     GPIO_WriteBit(SPINDLE_ENABLE_PORT, 1 << SPINDLE_ENABLE_BIT, Bit_RESET)
#define SetSpindleDirectionBit()    GPIO_WriteBit(SPINDLE_DIRECTION_PORT, 1 << SPINDLE_DIRECTION_BIT,Bit_SET)
#define ResetSpindleDirectionBit()  GPIO_WriteBit(SPINDLE_DIRECTION_PORT, 1 << SPINDLE_DIRECTION_BIT,Bit_RESET)


  // Define flood and mist coolant enable output pins.
  // a later date if flash and memory space allows.
#define COOLANT_FLOOD_PORT            GPIOB
#define RCC_COOLANT_FLOOD_PORT        RCC_APB2Periph_GPIOB
#define COOLANT_FLOOD_BIT             4
#define COOLANT_MIST_PORT             GPIOB
#define RCC_COOLANT_MIST_PORT         RCC_APB2Periph_GPIOB
#define COOLANT_MIST_BIT              3

  // Define user-control controls (cycle start, reset, feed hold) input pins.
  // NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define CONTROL_PIN_PORT              GPIOB
#define CONTROL_PORT                  GPIOB
#define RCC_CONTROL_PORT              RCC_APB2Periph_GPIOB
#define GPIO_CONTROL_PORT             GPIO_PortSourceGPIOB
#define CONTROL_RESET_BIT             5
#define CONTROL_FEED_HOLD_BIT         6
#define CONTROL_CYCLE_START_BIT       7
#define CONTROL_SAFETY_DOOR_BIT       8
#define CONTROL_MASK                 ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))

  // Define probe switch input pin.
#define PROBE_PORT                    GPIOB
#define RCC_PROBE_PORT                RCC_APB2Periph_GPIOB
#define PROBE_BIT                     9
#define PROBE_MASK                    (1<<PROBE_BIT)

  // Start of PWM & Stepper Enabled Spindle
#ifdef VARIABLE_SPINDLE

  // NOTE: On the 328p, these must be the same as the SPINDLE_ENABLE settings.
#define SPINDLE_PWM_FREQUENCY       10000                   // KHz
#define SPINDLE_PWM_DDR	            GPIOA
#define SPINDLE_PWM_PORT            GPIOA
#define RCC_SPINDLE_PWM_PORT        RCC_APB2Periph_GPIOA
#define SPINDLE_PWM_BIT	            8
#endif // End of VARIABLE_SPINDLE
#define SPINDLE_PWM_MAX_VALUE       (1000000 / SPINDLE_PWM_FREQUENCY)
#ifndef SPINDLE_PWM_MIN_VALUE
#define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
#endif
#define SPINDLE_PWM_OFF_VALUE     0
#define SPINDLE_PWM_RANGE         (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)

  //	Port A                    						Port B
  //	0  X_STEP_BIT									SPINDLE_DIRECTION_BIT
  //	1  Y_STEP_BIT									SPINDLE_ENABLE_BIT
  //	2  Z_STEP_BIT									unconnected
  //	3  A_STEP_BIT									COOLANT_MIST_BIT
  //	4  X_DIRECTION_BIT								COOLANT_FLOOD_BIT
  //	5  Y_DIRECTION_BIT								CONTROL_RESET_BIT
  //	6  Z_DIRECTION_BIT								CONTROL_FEED_HOLD_BIT
  //	7  A_DIRECTION_BIT								CONTROL_CYCLE_START_BIT
  //	8  SPINDLE_PWM_BIT								CONTROL_SAFETY_DOOR_BIT
  //	9  reserved for UART1 or B_STEP_BIT				PROBE
  //	10 reserved for UART1 or B_DIRECTION_BIT		reserved for UART3 or C_LIMIT_BIT
  //	11 usb											reserved for UART3 or B_LIMIT_BIT
  //	12 usb											X_LIMIT_BIT
  //	13 swd, possible to use for	C_STEP_BIT			Y_LIMIT_BIT
  //	14 swd, possible to use for	C_DIRECTION_BIT		Z_LIMIT_BIT
  //	15 STEPPERS_DISABLE_BIT							A_LIMIT_BIT

#endif

/*
#ifdef CPU_MAP_CUSTOM_PROC
  // For a custom pin map or different processor, copy and edit one of the available cpu
  // map files and modify it to your needs. Make sure the defined name is also changed in
  // the config.h file.
#endif
*/

#endif
