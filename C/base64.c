#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *base64_encoder(const char *data, size_t len);

static const char *encoding =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main() {
  printf("Hello, world!\n");
  printf("%s\n", base64_encoder("Hello, world!", 13));
  return 0;
}

char *base64_encoder(const char *data, size_t len) {
  size_t out_len = (len + 2) / 3 * 4;
  char *out = malloc(out_len + 1);
  size_t i, j;

  for (i = 0, j = 0; i < len; i += 3) {
    uint32_t n = 0;
    int padding = 0;

    n |= ((unsigned char)data[i]) << 16;
    padding++;

    if (i + 1 < len) {
      n |= ((unsigned char)data[i + 1]) << 8;
      padding++;
    }

    if (i + 2 < len) {
      n |= ((unsigned char)data[i + 2]);
      padding++;
    }

    out[j++] = encoding[(n >> 18) & 0x3F];
    out[j++] = encoding[(n >> 12) & 0x3F];

    if (padding > 1)
      out[j++] = encoding[(n >> 6) & 0x3F];
    else
      out[j++] = '=';

    if (padding > 2)
      out[j++] = encoding[n & 0x3F];
    else
      out[j++] = '=';
  }

  out[out_len] = '\0';
  return out;
}
