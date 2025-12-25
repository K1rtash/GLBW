#include <GLBW/glbw.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int windowmode = 3;
    int vsync = 0;
    int resizable = 0;
    int msaa = 0;

    for(int i = 1; i < argc; i++) printf("%s\n", argv[i]);
    if (argc > 1) sscanf(argv[1], "%d", &windowmode); 
    if (argc > 2) sscanf(argv[2], "%d", &vsync); 
    if (argc > 3) sscanf(argv[3], "%d", &resizable);
    if (argc > 4) sscanf(argv[3], "%d", &msaa);

    GLBW_Init();

    //GLBW_CreateWindow("Hello GLBW", 800, 600);
    GLBW_CreateWindowWithArgs("Hello glbw", 800, 600, windowmode, vsync, resizable, msaa);

    while(GLBW_UpdateWindow()) {
    }

    return 0;    
}