#include <stdio.h>

void ss(char *s, char t) {

while (*s) {

if (*s = t)

*s = t - 'a' + 'A';

s++;

}

}

int main() {

char s[100] = "abc", c = 'd';

ss(s, c);

printf("%s\n", s);

return 0;

}