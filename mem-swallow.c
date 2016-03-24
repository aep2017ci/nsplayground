#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i;
    char *p;
    printf(">>>>>>>>>>>>>>>>> BEGIN\n\n");
    const int one_mb = 1 << 20;

    for (i=0; i<50; ++i) {
      p = (char *) malloc(one_mb);
      if (p != NULL) {
        printf("Acquired: %d MB\n", i+1);
      } else {
        printf("Allocation failure\n");
      }
    }

    printf(">>>>>>>>>>>>>>>>>>> DONE\n");
    return 0;
}
