#include "includes/base64.h"
#include <stdio.h>
#include <string.h>

int main() {
  int mode;
  printf("For encoding(0) or decoding(1): ");
  scanf("%d", &mode);
  if (mode == 0) {
    char input[999];
    printf("Please input the string to encode: ");
    scanf("%s", input);
    char *encoded = base64_encoder(input, strlen(input));

    printf("Encode: %s\n", encoded);
  } else if (mode == 1) {
    printf("Wait a minute...\n");
  } else {
    printf("fuck off\n");
  }
  return 0;
}
