#ifndef __LINK_H__
#define __LINK_H__

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define tail -1
#define error -1

//typedef enum{false,true} bool;
typedef char ElemType;
typedef int Location;

struct Node{
    ElemType Data;
    struct Node* next;
};
typedef struct Node LinkNode;

struct List{
    LinkNode *Head, *Tail;
    bool isEmpty;
};
typedef struct List LinkList;

//初始化链表，返回一个规范空链表
LinkList lsetup(){
    LinkList* _l = (LinkList*)malloc(sizeof(LinkList));
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
        free(p[n%2]);
        n ++;
    }
    memset(l->Head,0,sizeof(LinkNode));
    free(l->Head);
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

//局部复制链表
LinkList partcp(const LinkList l, Location loc1, Location loc2){
    loc1 = loc1<0?(num(l)-1):loc1;
    loc2 = loc2<0?(num(l)-1):loc2;
    if(loc1 > loc2){
        Location temp = loc1;
        loc1 = loc2;
        loc2 = temp;
    }
    if(loc2+1 > num(l)){
        printf("Error! The location is wrongful!\n");
        return lsetup();
    }
    LinkList _l = copy(l);
    LinkNode *p = _l.Head, *tp = NULL;
    while(loc2--)
        p = p->next;
    while(p->next){
        tp = p->next->next;
        memset(p->next,0,sizeof(LinkNode));
        free(p->next);
        p->next = tp;
        tp = NULL;
    }
    p = NULL;
    while(loc1--){
        tp = _l.Head->next;
        memset(_l.Head,0,sizeof(LinkNode));
        free(_l.Head);
        _l.Head = tp;
        tp = NULL;
    }
    return _l;
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
            if(p->next)
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
        free(p->next);
        l->Tail = p;
        check(l);
        return;
    }
    else{
        p = l->Head;
        while(--_loc){
            if(p->next->next)
                p = p->next;
            else{
                printf("Error! The location is wrongful!\n");
                return;
            }
        }
        LinkNode* temp = p->next->next;
        memset(p->next,0,sizeof(LinkNode));
        free(p->next);
        p->next = temp;
        check(l);
        return;
    }
}

//用户初始化链表（若原链表非空则会格式化原链表）输入'!'时停止
void create(LinkList* l){
    if(!l->isEmpty){
        printf("Warning! The link is not empty!\nThe original data will be destoryed!\n");
        destory(l);
    }
    ElemType _data;
    LinkNode* p = NULL;
    while(scanf("%c",&_data) != EOF){
        if(_data == ' ' || _data == '\n')
            continue;
        if(_data == '!')
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
            printf("%c",p->Data);
        else
            printf(", %c",p->Data);
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

//连接两条链表
LinkList connect(const LinkList _l1, const LinkList _l2){
    LinkList l1 = copy(_l1), l2 = copy(_l2);
    l1.Tail->next = l2.Head;
    check(&l1);
    return l1;
}

//返回局部反转的链表
LinkList partusdown(const LinkList l, Location loc1, Location loc2){
    int n = num(l);
    loc1 = loc1<0?(n-1):loc1;
    loc2 = loc2<0?(n-1):loc2;
    if(loc1 > loc2){
        Location temp = loc1;
        loc1 = loc2;
        loc2 = temp;
    }
    if(loc1 == 0 && loc2 == n-1)
        return usdown(l);
    else if(loc1 == 0)
        return connect(usdown(partcp(l,loc1,loc2)),partcp(l,loc2+1,tail));
    else if(loc2 == n-1)
        return connect(partcp(l,0,loc1-1),usdown(partcp(l,loc1,tail)));
    else
        return connect(connect(partcp(l,0,loc1-1),usdown(partcp(l,loc1,loc2))),partcp(l,loc2+1,tail));
}

//判断回文
bool palindrome(const LinkList _l){
    if(_l.isEmpty)
        return true;
    LinkList l = usdown(_l);
    LinkNode *op = _l.Head, *np = l.Head;
    while(op){
        if(op->Data == np->Data){
            op = op->next;
            np = np->next;
        }
        else
            return false;
    }
    return true;
}

#endif