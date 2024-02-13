#include <stdint.h>
#include <stdlib.h>

char *base64_encoder(const char *data, size_t len);

char *base64_decoder(const char *data, size_t len);

#include <stdlib.h>
static const char *encoding =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
