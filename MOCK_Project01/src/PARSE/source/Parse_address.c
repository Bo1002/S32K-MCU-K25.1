/**
 * @file   Parse_addres.c
 * @author your name (you@domain.com)
 * @brief   Implementation of Motorola S-Record parser.
 * @details Converts ASCII S-Record line into binary address/data and verifies
 *          checksum integrity according to Motorola specification.
 * @version 0.1
 * @date 2025-10-22
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../include/Parse_address.h"
#include <stddef.h>   /* for NULL */
#include <string.h>   /* for strlen */

/*******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/
static int32_t Srec_HexCharToVal(char c);
static int32_t Srec_HexByteToVal(const char *p_hex);

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static int32_t Srec_HexCharToVal(char c)
{
    if ((c >= '0') && (c <= '9')) return (int32_t)(c - '0');
    if ((c >= 'A') && (c <= 'F')) return (int32_t)(10 + (c - 'A'));
    if ((c >= 'a') && (c <= 'f')) return (int32_t)(10 + (c - 'a'));
    return -1; /* Invalid */
}

static int32_t Srec_HexByteToVal(const char *p_hex)
{
    int32_t hi = Srec_HexCharToVal(p_hex[0]);
    int32_t lo = Srec_HexCharToVal(p_hex[1]);
    if ((hi < 0) || (lo < 0)) return -1;
    return (hi << 4) | lo;
}

/*******************************************************************************
 * Public Function Definitions
 ******************************************************************************/
bool Srec_ParseLine(const char *line, SREC_Record *rec)
{
    if ((line == NULL) || (rec == NULL)) return false;
    if (line[0] != 'S') return false;

    /* Determine record type */
    switch (line[1])
    {
        case '0': rec->record_type = SREC_TYPE_S0; break;
        case '1': rec->record_type = SREC_TYPE_S1; break;
        case '2': rec->record_type = SREC_TYPE_S2; break;
        case '3': rec->record_type = SREC_TYPE_S3; break;
        case '5': rec->record_type = SREC_TYPE_S5; break;
        case '7': rec->record_type = SREC_TYPE_S7; break;
        case '8': rec->record_type = SREC_TYPE_S8; break;
        case '9': rec->record_type = SREC_TYPE_S9; break;
        default:  rec->record_type = SREC_TYPE_UNKNOWN; return false;
    }

    /* Byte count (2 hex chars after 'Sx') */
    int32_t tmp = Srec_HexByteToVal(&line[2]);
    if (tmp < 0) return false;
    uint8_t byte_count = (uint8_t)tmp;

    /* Address length based on record type */
    uint8_t addr_len_bytes = 0U;
    switch (rec->record_type)
    {
        case SREC_TYPE_S1:
        case SREC_TYPE_S5:
        case SREC_TYPE_S9: addr_len_bytes = 2U; break;
        case SREC_TYPE_S2:
        case SREC_TYPE_S8: addr_len_bytes = 3U; break;
        case SREC_TYPE_S3:
        case SREC_TYPE_S7: addr_len_bytes = 4U; break;
        default: addr_len_bytes = 2U; break;
    }

    /* Parse address */
    rec->address = 0U;
    uint8_t offset = 4U;
    for (uint8_t i = 0U; i < addr_len_bytes; i++)
    {
        tmp = Srec_HexByteToVal(&line[offset]);
        if (tmp < 0) return false;
        rec->address = (rec->address << 8U) | (uint8_t)tmp;
        offset += 2U;
    }

    /* Data length = total count − addr bytes − checksum(1) */
    int32_t data_len = (int32_t)byte_count - (int32_t)addr_len_bytes - 1;
    if ((data_len < 0) || (data_len > SREC_MAX_DATA_LEN)) return false;
    rec->data_length = (uint8_t)data_len;

    /* Parse data bytes */
    for (int i = 0; i < data_len; i++)
    {
        tmp = Srec_HexByteToVal(&line[offset]);
        if (tmp < 0) return false;
        rec->data[i] = (uint8_t)tmp;
        offset += 2U;
    }

    /* Parse checksum */
    tmp = Srec_HexByteToVal(&line[offset]);
    if (tmp < 0) return false;
    uint8_t checksum = (uint8_t)tmp;

    /* Verify checksum (sum of all bytes except checksum should + checksum = 0xFF) */
    uint32_t sum = 0U;
    for (uint8_t i = 0; i < (byte_count - 1U); i++)
    {
        tmp = Srec_HexByteToVal(&line[2 + (i * 2)]);
        if (tmp < 0) return false;
        sum += (uint32_t)tmp;
    }

    uint8_t calc_checksum = (uint8_t)(0xFFU - (sum & 0xFFU));
    rec->checksum_ok = (calc_checksum == checksum);

    return rec->checksum_ok;
}

/*******************************************************************************
 * End of File
 ******************************************************************************/





