#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

int main() {
    int gd = DETECT, gm;
    int xc, yc, r; // Center coord, radius
    int x = 0, y; // plotting points;
    int P; // decision parameter
    int c1, c2; // Decision parameter increments

    printf("Enter coordinate (xc, yc): ");
    scanf("%d %d", &xc, &yc);
    printf("Enter radius: ");
    scanf("%d", &r);
    y = r;

    P = 3 - 2*r; // Initalise decision parameter
    
    initgraph(&gd, &gm, "");
    while (x <= y) {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, LIGHTGRAY);
        putpixel(xc - x, yc - y, LIGHTRED);
        putpixel(xc + x, yc - y, RED);
        putpixel(xc + y, yc + x, LIGHTBLUE);
        putpixel(xc - y, yc + x, GREEN);
        putpixel(xc - y, yc - x, LIGHTGREEN);
        putpixel(xc + y, yc - x, BLUE);

        x++;
        if (P < 0) {
            P = P + 4*x + 6;
        } else {
            y--;
            P = P + 4*(x-y) + 10;
        }
        delay(150);
    }
    getch();
    closegraph(0);
    return 0;
}