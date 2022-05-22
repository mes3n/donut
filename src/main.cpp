#include <stdio.h>   // printf
#include <math.h>    // half the code
#include <string.h>  // memset
#include <unistd.h>  // sleep


                        int main(){float R=7;
                float r=2.5;float rx=0.5;float ry=
              0;float rz=0;int g[400];int i,j;printf(
           "\033[2J");while(true){memset(g,0,1600);float
          cx,sx,cy,sy,cz,sz;cx=cos(rx);sx=sin(rx);cy=cos(ry
         );sy=sin(ry);cz=cos(rz);   sz=sin(rz);for(i=0;i<48;
       i++){float ca,sa;ca=cos        (M_PI*i/24);sa=sin(M_PI*
       i/24);for(j=0;j<24;j++          ){int a,b,c,ii;float ct,
      st,x,y,z;ct=cos(M_PI*j/           12);st=sin(M_PI*j/12);
      x=(R+r*ct)*ca;y=(R+r*             ct)*sa;z=r*st;a=x*cy*cz
      +y*(sx*sy*cz-cx*sz)+z            *(cx*sy*cz+sx*sz)+R+r;b=
      x*cy*sz+y*(sx*sy*sz+cx          *cz)+z*(cx*sy*sz-sx*cz)+R
       +r;c=-(x*sy)+y*sx*cy+z*      cx*cy+R+r;ii=b*20+a;g[ii]=
         g[ii]>c?g[ii]:c;}}int x, y;for(y=0;y<20;y++){for(x=
           0;x<20; x++){printf("\033[%d;%dH%c",y+6,2*(x+6),
            " .,-~:;!*+#$@"[g[y*20+x]>12?12:g[y*20+x]]);
                }}rx+=0;ry+=0.01;rz+=0;usleep(10000);
                      /*--*/}return 0;}/*--*/
                            // Good Bye
 
