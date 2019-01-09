#include <stdio.h>
#include <utils.h>

int main(int argc, char **argv)
{
    vector_t v =  point_to_screen(-1,1,600,600);   
   
    printf("%f", v.x);    
 
}
