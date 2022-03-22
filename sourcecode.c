#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tail -1
#define error -1

typedef enum{false,true} bool;
typedef int ElemType;
typedef int Location;

typedef LinkNode{
    ElemType Data;
    LinkNode* next;
}LinkNode;

typedef struct List{
    LinkNode *Head, *Tail;
    bool isEmpty;
}LinkList;

//初始化链表，返回一个规范空链表
LinkList lsetup(){
    LinkList* _l = (LinkList*)malloc(sizeof(struct List));
    _l->Head = _l->Tail = NULL;
    _l->isEmpty = true;
    return *_l;
}

//初始化节点，返回一个规范空节点
LinkNode* nsetup(){
    LinkNode* p = (LinkNode*)malloc(sizeof(LinkNode));
    p->Data = -1;
    p->next = NULL;
    return p;
}

//检查链表
void check(LinkList* l){
    LinkNode *p = l->Head;
    if(!p){
        l->isEmpty = true;
        return;
    }
    else
        l->isEmpty = false;
    while(p->next)
        p = p->next;
    l->Tail = p;
    return;
}

//格式化链表
void destory(LinkList* l){
    if(l->isEmpty){
        printf("There is nothing to do...\n");
        return;
    }
    LinkNode* p[2];
    int n = 0;
    p[0] = l->Head->next;
    p[1] = l->Head;
    while(p[n%2]){
        p[(n+1)%2] = p[n%2]->next;
        memset(p[n%2],0,sizeof(LinkNode));
        n ++;
    }
    memset(l->Head,0,sizeof(LinkNode));
    check(l);
    return;
}

//复制链表
LinkList copy(const LinkList l){
    LinkList rl = lsetup();
    if(l.isEmpty)
        return rl;
    LinkNode *op = l.Head, *rp = NULL;
    rl.Head = nsetup();
    rl.Head->Data = l.Head->Data;
    rp = rl.Head;
    while(op->next){
        rp->next = nsetup();
        rp = rp->next;
        op = op->next;
        rp->Data = op->Data;
    }
    check(&rl);
    return rl;
}

//返回某个元素的数据 *_loc 为下标*
ElemType read(const LinkList l, Location _loc){
    LinkNode *p = l.Head;
    while(_loc--){
        if(p->next)
            p = p->next;
        else{
            printf("Error! The location is wrongful!\n");
            return error;
        }
    }
    return p->Data;
}

//返回链表元素个数
int num(const LinkList l){
    if(l.isEmpty)
        return 0;
    LinkNode *p = l.Head;
    int n = 0;
    while(p){
        p = p->next;
        n ++;
    }
    return n;
}

//往链表中插入元素 *_loc 为下标*
void insert(LinkList* l, Location _loc, const ElemType _data){
    LinkNode *p = NULL;
    if(_loc == 0 || (_loc < 0 && l->isEmpty)){
        p = nsetup();
        p->Data = _data;
        p->next = l->Head;
        l->Head = p;
        check(l);
        return;
    }
    else if(_loc < 0){    
        p = nsetup();
        p->Data = _data;
        p->next = NULL;
        l->Tail->next = p;
        check(l);
        return;
    }
    else{
        p = l->Head;
        while(--_loc){
            if(p)
                p = p->next;
            else{
                printf("Error! The location is wrongful!\n");
                return;
            }
        }
        LinkNode* temp = nsetup();
        temp->Data = _data;
        temp->next = p->next;
        p->next = temp;
        check(l);
        return;
    }
}

//往链表中删除元素 *_loc 为下标*
void pop(LinkList* l, Location _loc){
    LinkNode* p = NULL;
    if(l->isEmpty){
        printf("Error! There is nothing in this link!\n");
        return;
    }
    else if(_loc < 0){
        p = l->Head;
        while(p->next != l->Tail)
            p = p->next;
        memset(p->next,0,sizeof(LinkNode));
        l->Tail = p;
        check(l);
        return;
    }
    else{
        p = l->Head;
        while(--_loc){
            if(p->next)
                p = p->next;
            else{
                printf("Error! The location is wrongful!\n");
                return;
            }
        }
        LinkNode* temp = p->next->next;
        memset(p->next,0,sizeof(LinkNode));
        p->next = p->next->next;
        check(l);
        return;
    }
}

//用户初始化链表（若原链表非空则会格式化原链表）输入负数停止
void create(LinkList* l){
    if(!l->isEmpty){
        printf("Warning! The link is not empty!\nThe original data will be destoryed!\n");
        destory(l);
    }
    ElemType _data;
    LinkNode* p = NULL;
    while(scanf("%d",&_data) != EOF){
        if(_data < 0)
            break;
        if(!p){
            l->Head = nsetup();
            l->Head->Data = _data;
            p = l->Head;
        }
        else{
            p->next = nsetup();
            p->next->Data = _data;
            p = p->next;
        }
    }
    check(l);
    return;
}

//顺序输出链表元素
void lout(const LinkList l){
    if(l.isEmpty){
        printf("NULL\n");
        return;
    }
    LinkNode* p = l.Head;
    while(p){
        if(p == l.Head)
            printf("%d",p->Data);
        else
            printf(", %d",p->Data);
        p = p->next;
    }
    printf("\n");
    return;
}

//返回反转的链表
LinkList usdown(const LinkList l){
    if(l.isEmpty)
        return lsetup();
    LinkList _l = copy(l), rl = lsetup();
    int n = num(_l);
    ElemType *_data = (ElemType*)malloc(sizeof(ElemType[n]));
    LinkNode *op = _l.Head, *rp = NULL;
    for(int i = 0; i < n; i ++){
        _data[i] = op->Data;
        op = op->next;
    }
    for(int i = n-1; i >= 0; i --){
        if(!rp){
            rl.Head = nsetup();
            rl.Head->Data = _data[i];
            rp = rl.Head;
        }
        else{
            rp->next = nsetup();
            rp = rp->next;
            rp->Data = _data[i];
        }
    }
    check(&rl);
    return rl;
}

LinkList connect(const LinkList _l1, const LinkList _l2){
    LinkList l1 = copy(_l1), l2 = copy(_l2);
    l1.Tail->next = l2.Head;
    check(&l1);
    return l1;
}

#if 1

int main(){
    LinkList l = lsetup(), l2 = lsetup();
    for(ElemType i = 0; i < 10; i ++)
        insert(&l,tail,i);
    for(ElemType i = 10; i < 20; i ++)
        insert(&l2,tail,i);
    lout(l);
    lout(l2);
    LinkList l3 = connect(l,l2);
    lout(l);
    lout(l2);
    lout(l3);
    destory(&l3);
    lout(l3);
    return 1;
}

#else

int main(){
    LinkList l = lsetup();
    for(ElemType i = 0; i < 10; i ++)
        insert(&l,tail,i);
    LinkList l2 = copy(l);
    lout(l2);
    return 1;
}

#endif