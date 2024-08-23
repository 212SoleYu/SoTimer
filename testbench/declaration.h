/*
 * This file declare all the macros used in all testbenches
 */

#ifndef DECLARATION_H
#define DECLARATION_H

#include <Modules/driver_include.h>
#include <stdint.h>

/****************************************BITCOUNT****************************************************/

#define BITCOUNT_SEED               4L
#define BITCOUNT_ITER               128
#define BITCOUNT_CHARBIT            8

extern const uint8_t bc_bits[256];



/*******************************************CRC32****************************************************/

#define CRC_LENGTH          (1024)
#define CRC_INIT            (0xFFFF)

extern const uint16_t CRC_Input[CRC_LENGTH];


/*******************************************DIJ**************************************************/


typedef struct {
    uint16_t dist;
    uint16_t prev;
} dijkstra_node_t;

typedef struct {
    uint16_t node;
    uint16_t dist;
    uint16_t prev;
} dijkstra_queue_t;

#define DIJKSTRA_NNODES             25
#define DIJKSTRA_QSIZE              4 * DIJKSTRA_NNODES
#define DIJKSTRA_INFINITY           0xFFFF
#define DIJKSTRA_UNDEFINED          0xFFF


extern const uint8_t adj_matrix[DIJKSTRA_NNODES][DIJKSTRA_NNODES];




/*******************************************QSORT****************************************************/

#define SORT_LENGTH  1000

extern const uint16_t raw[SORT_LENGTH];



/*******************************************RSA******************************************************/

extern const uint16_t rsa_msg[38];

extern const uint16_t p;
extern const uint16_t q;

#define RSA_MSGLENGTH    (30)


/*******************************************CRC32****************************************************/








/*******************************************CRC32****************************************************/




#endif
