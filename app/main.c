#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

static int type=0;

char *decode_bencode(const char *bencoded_value)
{
    int length = strlen(bencoded_value);
    if (is_digit(bencoded_value[0]))
    {
        const char *colon_index = strchr(bencoded_value, ':');
        if (colon_index != NULL)
        {
            const char *start = colon_index + 1;
            char *decoded_str = (char *)malloc(length + 1);
            strncpy(decoded_str, start, length);
            decoded_str[length] = '\0';
            return decoded_str;
        }
        else
        {
            fprintf(stderr, "Invalid encoded value: %s\n", bencoded_value);
            exit(1);
        }
    }
    else if (bencoded_value[0] == 'i')
    {
        type=1;
        char *substring = (char *)malloc(length - 1);
        strncpy(substring, bencoded_value + 1, length - 1);
        substring[length-2] = '\0';
        return substring;
    }
    else
    {
        fprintf(stderr, "Only strings are supported at the moment\n");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: your_bittorrent.sh <command> <args>\n");
        return 1;
    }

    const char *command = argv[1];

    if (strcmp(command, "decode") == 0)
    {
        // You can use print statements as follows for debugging, they'll be visible when running tests.
        // printf("Logs from your program will appear here!\n");
        const char *encoded_str = argv[2];
        char *decoded_str = decode_bencode(encoded_str);
        switch (type){
            case 0:
                printf("\"%s\"\n", decoded_str);
                break;
            case 1:
                printf("%s\n", decoded_str);
                break;
            default:
                fprintf(stderr, "Unknown command: %s\n", command);
                return 1;
                break;
        }
    }
    else
    {
        fprintf(stderr, "Unknown command: %s\n", command);
        return 1;
    }

    return 0;
}
