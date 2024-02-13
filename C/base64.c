#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *base64_encoder(char *in, size_t len_in);

static const char *encoding =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main() {
  printf("hello, Base64!\n");
  printf("%s\n", base64_encoder("Hello, world", 12));
  return 0;
}

char *base64_encoder(char *in, size_t len_in) {
  size_t len_out = 4 * (len_in + 2) / 3;
  char *out = malloc(len_out + 1);
  size_t i, j;

  for (i = 0, j = 0; i < len_in; i += 3) {
    uint32_t n = (in[i] << 16) | (in[i + 1] << 8) | in[i + 2];
    out[j++] = encoding[(n >> 18) & 0x3F];
    out[j++] = encoding[(n >> 12) & 0x3F];
    out[j++] = encoding[(n >> 6) & 0x3F];
    out[j++] = encoding[n & 0x3F];
  }

  while (j < len_out) {
    out[j++] = '=';
  }

  out[len_out] = '\0';

  return out;
}
