#include <stdio.h>
#include "head/link.h"

#if 0

int main(){
    LinkList l = lsetup();
    for(ElemType i = 'a'; i < 'a'+10; i ++)
        insert(&l,tail,i);
    lout(connect(l,usdown(l)));
    return 0;
}

#elif 0

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
    return 0;
}

#elif 0

int main(){
    LinkList l = lsetup();
    create(&l);
    lout(l);
    if(palindrome(l))
        printf("This link is a palindrome!\n");
    else
        printf("This link is not a palindrome!\n");
    system("pause");
    return 0;
}

#else

int main(){
    LinkList l = lsetup();
    create(&l);
    lout(l);
    Location a, b;
    scanf("%d%d",&a,&b);
    LinkList l_ = partusdown(l,a,b);
    lout(l_);
    return 0;
}

#endif