#include "../includes/base64.h"
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

    out[j++] = base64_table[(n >> 18) & 0x3F];
    out[j++] = base64_table[(n >> 12) & 0x3F];

    if (padding > 1)
      out[j++] = base64_table[(n >> 6) & 0x3F];
    else
      out[j++] = '=';

    if (padding > 2)
      out[j++] = base64_table[n & 0x3F];
    else
      out[j++] = '=';
  }

  out[out_len] = '\0';
  return out;
}

char *base64_decoder(const char *data, size_t len) {
  if (len % 4 != 0)
    return NULL;

  size_t out_len = len * 3 / 4;
  if (data[len - 1] == '=')
    out_len--;
  if (data[len - 2] == '=')
    out_len--;

  char *out = malloc(out_len + 1);
  unsigned now = 0;
  if (!out)
    return NULL;

  unsigned buffer = 0;
  unsigned buf_size = 0;
  for (size_t i = 0; i < len; i++) {
    if (data[i] == '=')
      break;
    for (size_t j = 0; j < 64; j++) {
      if (data[i] == base64_table[j]) {
        buffer = (buffer << 6) + j;
        buf_size += 6;
      }
      if (buf_size >= 8) {
        out[now++] = (char)(buffer >> (buf_size - 8));
        buf_size -= 8;
      }
    }
  }
  out[out_len] = '\0';
  return out;
}
