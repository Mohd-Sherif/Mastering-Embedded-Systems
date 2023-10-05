/*
 * Platform_Types.h
 *
 *  Created on: Oct 5, 2023
 *      Author: Mohamed Sherif
 */
#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * Type definitions - general
 *
 * The platform type files for all platforms could contain the following symbols:
 */
#define CPU_TYPE_8		8
#define CPU_TYPE_16		16
#define CPU_TYPE_32		32
#define CPU_TYPE_64		64
#define MSB_FIRST		0
#define LSB_FIRST		1
#define HIGH_BYTE_FIRST	0
#define LOW_BYTE_FIRST	1

#ifndef _Bool
#define _Bool unsigned char
#endif

#define CPU_Type              CPU_TYPE_32
#define CPU_BIT_ORDER         MSB_FIRST
#define CPU_BYTE_ORDER        HIGH_BYTE_FIRST

#ifndef FALSE
#define FALSE         (boolean)false
#endif
#ifndef TRUE
#define TRUE          (boolean)true
#endif

typedef _Bool         boolean;
typedef int8_t        sint8;
typedef uint8_t       uint8;
typedef char          char_t;
typedef int16_t       sint16;
typedef uint16_t      uint16;
typedef int32_t       sint32;
typedef uint32_t      uint32;
typedef int64_t       sint64;
typedef uint64_t      uint64;

typedef volatile int8_t		vint8_t;
typedef volatile uint8_t	vuint8_t;

typedef volatile int16_t	vint16_t;
typedef volatile uint16_t	vuint16_t;

typedef volatile int32_t	vint32_t;
typedef volatile uint32_t	vuint32_t;

typedef volatile int64_t	vint64_t;
typedef volatile uint64_t	vuint64_t;

#endif /* PLATFORM_TYPES_H_ */
