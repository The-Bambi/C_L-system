#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "turtle.c"

#define IGNORE "XY"
#define ABS(X) ((X)>0 ? (X) : (-(X)))


typedef struct node {
    double x, y, heading;
    struct node *prev;
} node;

node *head = NULL;

void push(double x, double y, double heading) {

    node *n = malloc(sizeof(node));
    if (n == NULL) {
        printf("Something's wrong with memory...");
        return;
    }
    n->x = x;
    n->y = y;
    n->heading = heading;
    n->prev = head;
    head = n;
}

int isEmpty() {
    if (head == NULL) return 1;
    return 0;
}

node *pop() {
    node *rtrn = head;
    head = head->prev;
    return rtrn;
}

//l_system
typedef struct {
    char in;
    char out[32];
}rule;

char *l_system(int iters_total, rule a, rule b, char *start, char *end, int save_to_file) {
    long expected = strlen(start);
    long buff_size = 32768;
    long i;
    FILE *f;

    if (save_to_file) {
        f = fopen("output.txt","w");
        fputs(start,f);
        putc('\n',f);
    }
    
    for (int iters = 0; iters < iters_total; iters++) {
        i = 0;
        do {
            char current_char = start[i++];
            
            if (current_char == a.in) {

                expected += strlen(a.out)-1;
                if (expected > buff_size) {
                    buff_size *= 2;
                    start = realloc(start, buff_size);
                    end = realloc(end, buff_size);
                }

                strcat(end,a.out);
            }
            
            else if (current_char == b.in) {

                expected += strlen(b.out)-1;
                if (expected > buff_size) {
                    buff_size *= 2;
                    start = realloc(start, buff_size);
                    end = realloc(end, buff_size);
                }

                strcat(end,b.out);
            }

            else {
                end[strlen(end)] = current_char;
                expected++;
            }
        } while (start[i] != '\0');

        memset(start,0,strlen(start));
        strcpy(start,end);
        memset(end,0,strlen(end));

        if (start == NULL || end == NULL) {
            printf("Something's wrong with memory...");
            exit(1);
        }
        fputs(start,f);
        putc('\n',f);
    }
    fclose(f);
    free(end);
    return start;

}


int main() {

    printf("Dostepne opcje:\n0. Ciag Fibbonaciego (bez rysowania, tylko zapis do pliku)\n1. Trojkat Sierpinskiego\n2. Trojkat Sierpinskiego - 'Arrowhead curve'\n3. Dywan Sierpinskiego\n4. Kwadratowy Sierpinski\n5. Wzrost krysztalu\n6. Platek sniegu Kocha\n7. Platek sniegu - wariacja\n8. Pierscienie\n9. Roslina 1.0\n10. Roslina 2.0\n11. Roslina 3.0\n12. Roslina 4.0\n13. Krzywa Levy'ego\n14. Krzywa Peano\n15. Krzywa Kocha\n16. Wyspa Kocha\n17. Plansza kwadratow\n");
    
    int line_length = 7;
    float MODIFIER = 0.95;
    int type, iterations;

    printf("Numer: ");
    scanf("%d",&type);
    printf("Stopien zlozonosci (zalecam nie wychodzic poza 5-6 ze wzgledu na czas...): ");
    scanf("%d",&iterations);
    int turtle_start_x, turtle_start_y, turtle_start_heading, turn_angle;

    rule a;
    rule b;

    char *start = malloc(sizeof(char)*32768);
    char *end = malloc(sizeof(char)*32768);

    if (start == NULL || end == NULL) {
        printf("Something's wrong with memory...");
        exit(1);
    }

    switch (type) { //setting up initial conditions for l-system to evolve and to set turtle
        case 0:

            strcpy(start,"A");
            a.in = 'A';
            strcpy(a.out,"AB");
            b.in = 'B';
            strcpy(b.out, "A");
            break;

        case 1:

            strcpy(start,"F-G-G");
            a.in = 'F';
            strcpy(a.out,"F-G+F+G-F");
            b.in = 'G';
            strcpy(b.out, "GG");

            turtle_start_heading = 120;
            turn_angle = 120;

            break;
        
        case 2:

            strcpy(start,"A");
            a.in = 'A';
            strcpy(a.out,"B-A-B");
            b.in = 'B';
            strcpy(b.out, "A+B+A");

            turtle_start_heading = 30;
            turn_angle = 60;

            break;

        case 3:

            strcpy(start,"F");
            a.in = 'F';
            strcpy(a.out,"F+F-F-F-UGD+F+F+F-F");
            b.in = 'G';
            strcpy(b.out, "GGG");

            turtle_start_heading = 90;
            turn_angle = 90;
     
            break;

        case 4:

            strcpy(start,"F+GF+F+GF");
            a.in = 'G';
            strcpy(a.out,"GF-F+F-GF+F+GF-F+F-G");
            b.in = '0';
            strcpy(b.out, "0");

            turtle_start_heading = 90;
            turn_angle = 90;
     
            break;

        case 5:

            strcpy(start,"F+F+F+F");
            a.in = 'F';
            strcpy(a.out,"FF+F++F+F");
            b.in = '0';
            strcpy(b.out, "0");

            turtle_start_heading = 90;
            turn_angle = 90;
     
            break;

        case 6:

            strcpy(start,"F++F++F");
            a.in = 'F';
            strcpy(a.out,"F-F++F-F");
            b.in = '0';
            strcpy(b.out, "0");

            turtle_start_heading = 90;
            turn_angle = 60;
     
            break;

        case 7:

            strcpy(start,"X+X+X+X+X+X+X+X");
            a.in = 'X';
            strcpy(a.out,"X+YF++YF-FX--FXFX-YF+X");
            b.in = 'Y';
            strcpy(b.out, "-FX+YFYF++YF+FX--FX-YF");

            turtle_start_heading = 90;
            turn_angle = 45;
     
            break;


        case 8:

            strcpy(start,"F+F+F+F");
            a.in = 'F';
            strcpy(a.out,"FF+F+F+F+F+F-F");
            b.in = '0';
            strcpy(b.out, "0");

            turtle_start_heading = 90;
            turn_angle = 90;
     
            break;

        case 9:

            strcpy(start,"F");
            a.in = 'F';
            strcpy(a.out,"FF+[+F-F-F]-[-F+F+F]");
            b.in = '0';
            strcpy(b.out, "0");

            turtle_start_heading = 90;
            turn_angle = 22;
     
            break;

        case 10:

            strcpy(start,"X");
            a.in = 'X';
            strcpy(a.out,"F+[[X]-X]-F[-FX]+X");
            b.in = 'F';
            strcpy(b.out, "FF");

            turtle_start_heading = 90;
            turn_angle = 25;
     
            break;

        case 11:

            strcpy(start,"X");
            a.in = 'X';
            strcpy(a.out,"F[+FX]FX[-FX]");
            b.in = 'F';
            strcpy(b.out, "FF");

            turtle_start_heading = 90;
            turn_angle = 25;
     
            break;

        case 12:

            strcpy(start,"F");
            a.in = 'F';
            strcpy(a.out,"F[+FF][-FF]F[-F][+F]F");
            b.in = '0';
            strcpy(b.out, "0");

            turtle_start_x = 0;
            turtle_start_y = -8191;
            turtle_start_heading = 90;
            turn_angle = 36;

            break;

        case 13:

            strcpy(start,"F++F++F++F");
            a.in = 'F';
            strcpy(a.out,"-F++F-");
            b.in = '0';
            strcpy(b.out, "0");

            turtle_start_heading = 90;
            turn_angle = 45;
     
            break;

        case 14:

            strcpy(start,"X");
            a.in = 'X';
            strcpy(a.out,"XFYFX+F+YFXFY-F-XFYFX");
            b.in = 'Y';
            strcpy(b.out, "YFXFY-F-XFYFX+F+YFXFY");

            turtle_start_heading = 90;
            turn_angle = 90;
     
            break;

        case 15:

            strcpy(start,"F");
            a.in = 'F';
            strcpy(a.out,"F-F++F-F");
            b.in = '0';
            strcpy(b.out, "00");

            turtle_start_heading = 0;
            turn_angle = 60;
     
            break;

        case 16:

            strcpy(start,"F+F+F+F");
            a.in = 'F';
            strcpy(a.out,"F+F-F-FFF+F+F-F");
            b.in = '0';
            strcpy(b.out, "00");

            turtle_start_heading = 90;
            turn_angle = 90;
     
            break;

        case 17:

            strcpy(start,"F+F+F+F");
            a.in = 'F';
            strcpy(a.out,"FF+F+F+F+FF");
            b.in = '0';
            strcpy(b.out, "00");

            turtle_start_heading = 90;
            turn_angle = 90;
     
            break;

        default: 
            printf("ERROR, Prosze wybrac numer 0-13!\n");
            exit(0);
    }

    char *l = l_system(iterations,a,b,start,end,1);


    //estimate size:
    turtle_init(16, 16);
    turtle_pen_up();
    turtle_set_heading(turtle_start_heading);

    node *pos;

    long maxx = LONG_MIN;
    long maxy = LONG_MIN;
    long minx = LONG_MAX;
    long miny = LONG_MAX;
    
    for (long index = 0; index<strlen(l); index++) {
        char letter = l[index];
        switch (letter) {
            case 'U':
                break;
            case 'D':
                break;
            case '[':
                push(turtle_get_x(),turtle_get_y(),turtle_get_heading());
                break;
            case ']':
                pos = pop();
                turtle_pen_up();
                turtle_goto(pos->x,pos->y);
                turtle_set_heading(pos->heading);
                turtle_pen_down();
                break;
            case '+':
                turtle_turn_right(turn_angle);
                break;
            case '-':
                turtle_turn_left(turn_angle);
                break;
            default:
                if (strchr(IGNORE,letter) != NULL) break;
                turtle_calculate_forward(line_length*pow(MODIFIER,iterations));
                break;
        }

        if (turtle_get_x() > maxx) maxx = turtle_get_x();
        if (turtle_get_x() < minx) minx = turtle_get_x();
        if (turtle_get_y() > maxy) maxy = turtle_get_y();
        if (turtle_get_y() < miny) miny = turtle_get_y();
    }
    
    long width = maxx - minx;
    long height = maxy - miny;

    turtle_reset();
    //drawing!
    turtle_init(width, height); //tutaj wpisz obliczony width i height
    turtle_pen_up();

    turtle_goto(-width/2+ABS(minx),-height/2+ABS(miny));
    turtle_set_heading(turtle_start_heading);

    turtle_pen_down();
    
    for (long index = 0; index<strlen(l); index++) {
        char letter = l[index];
        switch (letter) {
            case 'U':
                turtle_pen_up();
                break;
            case 'D':
                turtle_pen_down();
                break;
            case '[':
                push(turtle_get_x(),turtle_get_y(),turtle_get_heading());
                break;
            case ']':
                pos = pop();
                turtle_pen_up();
                turtle_goto(pos->x,pos->y);
                turtle_set_heading(pos->heading);
                turtle_pen_down();
                break;
            case '+':
                turtle_turn_right(turn_angle);
                break;
            case '-':
                turtle_turn_left(turn_angle);
                break;
            default:
                if (strchr(IGNORE,letter) != NULL) break;
                turtle_forward(line_length*pow(MODIFIER,iterations));
                break;
        }
    }


    free(start);
    turtle_save_bmp("output.bmp");
    //by Krystian Figiel
}