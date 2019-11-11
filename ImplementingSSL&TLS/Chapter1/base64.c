#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char *base64 = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// How the base64 algorithm works?
//  1) Analyse the input 3 bytes at a time
//  2) Uses 6-bits character encoding instead of 8-bits
//  3) So, for each 3 bytes (24 bits) from input, the algorithm returns 4 characters (24-bits/6-bits = 4 characters)
//  
//  Example: Input = 'ABC' 
//      A = 0x41 = 01000001
//      B = 0x42 = 01000010
//      C = 0x43 = 01000011
//
//  01000001 01000010 01000011  --------> (ABC)
//  
//  Separate the sequence into 6-bits chunks:
//  010000 010100 001001 000011
//   (16)   (20)    (9)   (3)   --------> (QUJD) 'base64 encoded'
//  |_________________________|
//   These numbers are indexes 
//    for the base64 variable
//         defined above.
//    (ex: base64[16] == 'Q')
//
void base64_encode(const unsigned char *input, int len, unsigned char *output) { 
    do { 
        // 'input[0] & 0xFC': Selects the last 6-bits from first byte. 
        // Ex: Character 'A' = 0x41 = 01000001 
        //                     0xFC = 11111100
        //
        //     01000001
        // &   11111100    "Here, the first two bits are reseted (base64 works with 6-bits chunks)"
        // -------------
        //     01000000    "Because we are avoiding the first two bits, we need to perform a two-bit right shift operator" 
        // >>2 
        // -------------
        //     00010000    --> (0x1 or 0d16) --> base64[16] = 'Q'  
        *output++ = base64[(input[0] & 0xFC) >> 2];

        // The input is analyzed 3-bytes at a time. If the last chunk has only one byte,
        // we need to perform a padding with two '=' character.
        if (len == 1) { 
            // 'input[0] & 0x03': Selects the first 2-bits of the byte. 
            // Ex: Character 'A' = 0x41 = 01000001 | '0x03' = 00000011
            //
            //     01000001
            // &   00000011    "Here, the last 6-bits  are reseted"
            // -------------
            //     00000001    "The first two-bits of the first byte, become the last two-bits of the next 6-bit chunk"
            // <<4             "So, we need to perform a 4-bit shift operator to left"
            // -------------
            //     00010000    --> (0x1 or 0d16) --> base64[16] == 'Q'  
            *output++ = base64[((input[0] & 0x03) << 4)];
            *output++ = '=';
            *output++ = '=';
            break;
        }

        // 'input[0] & 0x03': See the explanation above.
        // 'input[1] & 0xF0': Selects the last 4-bits of the second byte. 
        // Ex: Character 'B' = 0x42 = 01000010 | '0xF0' = 11110000
        //
        //     01000010
        // &   11110000    "Here, the first 4-bits  are reseted"
        // -------------
        //     01000000    "The last 4-bits of the second byte, become the first 4-bits of the current 6-bit chunk"
        // >>4             "So, we need to perform a 4-bit shift operator to right"
        // -------------
        //     00000100 
        // |   00010000    "Performs an OR operation to get a 6-bit chunk (first 2-bits of the first byte + last 4-bits of the second byte)"
        // -------------
        //     00010100    --> (0x14 or 0d20) --> base64[20] == 'U'
        *output++ = base64[((input[0] & 0x03) << 4) | ((input[1] & 0xF0) >> 4)];

        if (len == 2) { 
            *output++ = base64[((input[1] & 0x0F) << 2)];
            *output++ = '=';
            break;
        }

        // Same logic applied here.
        *output++ = base64[((input[1] & 0x0F) << 2) | ((input[2] & 0xC0) >> 6)];
        *output++ = base64[(input[2] & 0x3F)];
        input += 3;
    } while (len -= 3);

    *output + '\0';
}

int main(int argc, char* argv[]) { 
    size_t length;
    char* output;

    if (argc < 2) { 
        printf("Usage: ./base64 <string>\n");
        return 1;
    }

    length = strlen(argv[1]);
    output = malloc(sizeof(char) * length);

    base64_encode(argv[1], length, output);

    printf("Output: %s\n", output);

    return 0;
}
