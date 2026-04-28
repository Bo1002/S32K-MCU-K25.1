/*
 * Parser.h
 *
 *  Created on: Dec 28, 2025
 *      Author: BO
 */

#ifndef PARSER_PARSER_H_
#define PARSER_PARSER_H_

#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define MAX_DATA_REC        (64U)     /* Max data bytes per record */
#define MAX_PHSIZE_BP       (256U)    /* Flash phrase buffer size */
#define TIMEOUT_VALUE       (5U)

/*******************************************************************************
 * Structures
 ******************************************************************************/
typedef enum
{
    PARSER_OK = 0,
    PARSER_INVALID,
    PARSER_EOF
} ParserResult_t;


typedef struct
{
    char     TypeChar;                /* '0'...'9' */
    uint8_t  ByteCount;               /* count = addr + data + checksum */
    uint32_t Address;                 /* 2, 3, or 4 bytes depending on type */
    uint8_t  Data[MAX_DATA_REC];      /* payload data */
    uint8_t  DataLen;                 /* data length */
    uint8_t  Checksum;                /* checksum byte */
    uint8_t  Valid;
} BootPhraseStruct;

/*******************************************************************************
 * API
 ******************************************************************************/
uint8_t Srec_ParseLine(const char *line, BootPhraseStruct *rec);

#ifdef __cplusplus
}
#endif


#endif /* PARSER_PARSER_H_ */
