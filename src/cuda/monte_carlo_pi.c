#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SAMPLES 100000000

int main() {
    int inside = 0;
    srand(time(NULL));

    for (int i = 0; i < NUM_SAMPLES; i++) {
        float x = (float)rand() / RAND_MAX;
        float y = (float)rand() / RAND_MAX;

        if (x*x + y*y <= 1.0f) inside++;
    }

    float pi = 4.0f * inside / NUM_SAMPLES;

    printf("Estimated value of π: %f\n", pi);
    printf("Samples used: %d\n", NUM_SAMPLES);
    printf("Points inside circle: %d\n", inside);

    return 0;
}
