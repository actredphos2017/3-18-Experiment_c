#include <stdio.h>
#include "head/link.h"

#if 0

int main(){
    LinkList l = lsetup();
    for(ElemType i = 0; i < 10; i ++)
        insert(&l,tail,i);
    lout(connect(l,usdown(l)));
    return 1;
}

#else

int main(){
    LinkList l = lsetup();
    create(&l);
    lout(l);
    printf("%d\n",num(l));
    Location loc;
    ElemType data;
    scanf("%d%d",&loc,&data);
    insert(&l,loc,data);
    lout(l);
    return 1;
}

#endif