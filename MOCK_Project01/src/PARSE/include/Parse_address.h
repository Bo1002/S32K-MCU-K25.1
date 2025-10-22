/**
 * @file    Parse_address.h
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
#ifndef PARSE_ADDRESS_H
#define PARSE_ADDRESS_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * Macros
 ******************************************************************************/
#define SREC_MAX_DATA_LEN   (64U)   /* Maximum number of data bytes per record */

/*******************************************************************************
 * Enumerations
 ******************************************************************************/
/**
 * @brief Motorola S-Record type identifiers.
 */
typedef enum
{
    SREC_TYPE_UNKNOWN = 0U,
    SREC_TYPE_S0,
    SREC_TYPE_S1,
    SREC_TYPE_S2,
    SREC_TYPE_S3,
    SREC_TYPE_S5,
    SREC_TYPE_S7,
    SREC_TYPE_S8,
    SREC_TYPE_S9
} SREC_Type;

/*******************************************************************************
 * Structures
 ******************************************************************************/
/**
 * @brief Structure representing a parsed S-Record line.
 */
typedef struct
{
    SREC_Type record_type;                /**< Type of S-Record (S1, S2, S3, etc.)  */
    uint32_t  address;                    /**< Start address extracted from record  */
    uint8_t   data[SREC_MAX_DATA_LEN];    /**< Data bytes of this record            */
    uint8_t   data_length;                /**< Number of valid bytes in data[]      */
    bool      checksum_ok;                /**< True if checksum matches             */
} SREC_Record;

/*******************************************************************************
 * API Prototypes
 ******************************************************************************/

/**
 * @brief Parse a single Motorola S-Record line.
 *
 * @param line  Pointer to null-terminated S-Record string (e.g. "S1137AF00A0A...").
 * @param rec   Pointer to SREC_Record structure to receive parsed data.
 *
 * @return true  if record is valid and checksum passes.
 * @return false if record is invalid (syntax or checksum error).
 */
bool Srec_ParseLine(const char *line, SREC_Record *rec);

#ifdef __cplusplus
}
#endif



/*******************************************************************************
 * End of File
 ******************************************************************************/

#endif /* PARSE_INCLUDE_PARSE_ADDRESS_H_ */
