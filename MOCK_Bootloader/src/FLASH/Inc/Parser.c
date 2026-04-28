/*
 * Parser.c
 *
 *  Created on: Dec 28, 2025
 *      Author: BO
 */

#include "Parser.h"

#include <stdint.h>
/*******************************************************************************
 * Macros
 ******************************************************************************/


 /****************************************************************************
  * STATIC VARIABLE 
  ****************************************************************************/


/****************************************************************************
 * PROTOTYPE 
 ****************************************************************************/
static uint8_t hextobyte (const char *sent);

/***************************************************************************
 * IMPLEMENT 
 ***************************************************************************/

static uint8_t hextobyte(const char *s)
{
    uint8_t v = 0;
    for (uint8_t i = 0; i < 2; i++)
    {
        v <<= 4;
        char c = s[i];
        if (c >= '0' && c <= '9')       v |= (c - '0');
        else if (c >= 'A' && c <= 'F')  v |= (c - 'A' + 10);
    }
    return v;
}

ParserResult_t Srec_ParseLine(const char *line, BootPhraseStruct *rec)
{
    if (line[0] != 'S')
        return PARSER_INVALID;

    char type = line[1];
    uint8_t addr_len = 0;

    rec->TypeChar = type;
    rec->ByteCount = hextobyte(&line[2]);

    switch (type)
    {
    case '1': addr_len = 2; break;
    case '2': addr_len = 3; break;
    case '3': addr_len = 4; break;

    case '7':
    case '8':
    case '9':
        return PARSER_EOF;

    default:
        return PARSER_INVALID;
    }

    /* Parse address */
    rec->Address = 0;
    uint8_t idx = 4;
    for (uint8_t i = 0; i < addr_len; i++)
    {
        rec->Address <<= 8;
        rec->Address |= hextobyte(&line[idx]);
        idx += 2;
    }

    rec->DataLen = rec->ByteCount - addr_len - 1;

    for (uint8_t i = 0; i < rec->DataLen; i++)
    {
        rec->Data[i] = hextobyte(&line[idx]);
        idx += 2;
    }

    rec->Checksum = hextobyte(&line[idx]);

    /* ---- Checksum verify ---- */
    uint32_t sum = rec->ByteCount;

    for (uint8_t i = 0; i < addr_len; i++)
        sum += (rec->Address >> ((addr_len - 1 - i) * 8)) & 0xFF;

    for (uint8_t i = 0; i < rec->DataLen; i++)
        sum += rec->Data[i];

    sum = (~sum) & 0xFF;

    if (sum != rec->Checksum)
    {
        rec->Valid = 0;
        return PARSER_INVALID;
    }

    rec->Valid = 1;
    return PARSER_OK;
}
