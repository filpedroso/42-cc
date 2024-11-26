#include <stdio.h>

int main(void)
{
    char c = 'A';
    char *str = "Hello, World!";
    void *ptr = &c;
    int d = 42;
    unsigned int u = 3000000000U; // Large unsigned value
    int x = 255;

    printf("Testing '-' flag:\n");
    printf("Argument: '%%-5c', '%c' -> ", c);
    printf("|%-5c|\n", c);
    printf("Argument: '%%-10s', \"%s\" -> ", str);
    printf("|%-10s|\n", str);
    printf("Argument: '%%-10d', %d -> ", d);
    printf("|%-10d|\n", d);

    printf("\nTesting '.' flag (precision):\n");
    printf("Argument: '%%.0d', %d -> ", d);
    printf("|%.0d|\n", d);
    printf("Argument: '%%.5d', %d -> ", d);
    printf("|%.5d|\n", d);
    printf("Argument: '%%.5s', \"%s\" -> ", str);
    printf("|%.5s|\n", str);
    printf("Argument: '%%.s', \"%s\" -> ", str);
    printf("|%.s|\n", str);
    printf("Argument: '%%.3x', %d -> ", x);
    printf("|%.3x|\n", x);

    printf("\nTesting '0' flag (zero padding):\n");
    printf("Argument: '%%05d', %d -> ", d);
    printf("|%05d|\n", d);
    printf("Argument: '%%05x', %x -> ", x);
    printf("|%05x|\n", x);
    printf("Argument: '%%05s', \"%s\" -> ", str); // Ignored for strings
    printf("|%05s|\n", str);

    printf("\nTesting combinations of flags:\n");
    printf("Argument: '%%-05d', %d -> ", d); // '-' overrides '0'
    printf("|%-05d|\n", d);
    printf("Argument: '%%-.5d', %d -> ", d); // Precision overrides '0'
    printf("|%-.5d|\n", d);

    printf("\nTesting special values:\n");
    printf("Argument: '%%p', pointer -> ");
    printf("|%p|\n", ptr);
    printf("Argument: '%%x', 0 -> ");
    printf("|%x|\n", 0);
    printf("Argument: '%%.x', 0 -> ");
    printf("|%.x|\n", 0);
    printf("Argument: '%%X', 255 -> ");
    printf("|%X|\n", 255);

    printf("\nTesting unsigned values:\n");
    printf("Argument: '%%u', %u -> ", u);
    printf("|%u|\n", u);
    printf("Argument: '%%.5u', %u -> ", u);
    printf("|%.5u|\n", u);
    printf("Argument: '%%05u', %u -> ", u);
    printf("|%05u|\n", u);

    printf("\nTesting invalid or uncommon uses:\n");
    printf("Argument: '%%-.0d', %d -> ", d); // Precision overrides width
    printf("|%-.0d|\n", d);
    printf("Argument: '%%.10s', NULL -> ");
    printf("|%.10s|\n", NULL); // `NULL` string handling
    printf("Argument: '%%d', 0 -> ");
    printf("|%d|\n", 0);

    return 0;
}
