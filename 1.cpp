#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
typedef int datatype;
typedef struct node{
    int data;
    struct node *next;
}linklist;

//形成链表
linklist *create()
{
    linklist *L,*p,*r;
    L=(linklist*)malloc(sizeof(linklist));
    L->next=NULL;
    r = L;
    int x;
    scanf("%d",&x);
    while(x != -1)
    {   
        p = (linklist*)malloc(sizeof(linklist));
        p->data = x;
        r->next = p;
        r = p;
        scanf("%d",&x);
    }
    r->next = NULL;
    return L; 
}

//预处理函数(排序以及去除重复项)
void sort(linklist*L){
    linklist *p=L->next,*pre;
    linklist *r=p->next;
    p->next=NULL;
    p=r;
    while(p!=NULL){
        r=p->next;
        pre=L;
        while(pre->next!=NULL&&pre->next->data<p->data){
            pre=pre->next;            
        }
        p->next=pre->next;
        pre->next=p;
        p=r;
    }//排序
    
    pre=L;
    p=pre->next;
    r=NULL;
    while(p!=NULL){
        if (pre->data==p->data){
            r=p;
            p=p->next;
            pre->next=p;
        }
        else{
            pre=p;
            p=p->next;
        }
   }//删除重复项
}

//输出函数
void print(linklist*L)
{
    linklist *p;
    p = L->next;
    while(p->next != NULL){
        printf("%d ",p->data);
        p = p->next;
    }
    printf("%d\n",p->data);
}


//求交集
linklist* insec(linklist *A, linklist * B){

    if(A->next==NULL || B->next == NULL){
        return NULL;
    }//特殊情况

    linklist *L,*a,*b,*r,*q;
    L = (linklist*)malloc(sizeof(linklist));
    L->next=NULL;
    r=L;

    a=A->next;
    b=B->next;

    while(a!=NULL && b!=NULL){
        if (a->data==b->data){
            q = (linklist*)malloc(sizeof(linklist));
            q->data=a->data;
            r->next = q;
            r=r->next;
            a=a->next;
            b=b->next;
        }
        else if (a->data < b->data){
            a=a->next;
        }
        else{
            b=b->next;
        }
        
    }
    r->next=NULL;

    return L;
}

//求并集运算
linklist* Union(linklist* A,linklist* B){

    if(A->next==NULL && B->next==NULL){
        return A;
    }
    if(A->next!=NULL && B->next==NULL){
        return A;
    }
    if(A->next==NULL && B->next!=NULL){
        return B;
    }//三种特殊状况

    linklist*L,*p,*r,*q;
    L = (linklist*)malloc(sizeof(linklist));
    L->next=NULL;
    r=L;
    
    p=A->next;

    while(p!=NULL){
        q = (linklist*)malloc(sizeof(linklist));
        q->data=p->data;
        r->next=q;
        r=r->next;
        p=p->next;
    }
    
    p=B->next;
    while(p!=NULL){
        q = (linklist*)malloc(sizeof(linklist));
        q->data=p->data;
        r->next=q;
        r=r->next;
        p=p->next;
    }

    r->next=NULL;
    sort(L);
    return L;
}//将两个集合合并，并利用sort函数使形式规范

//求集合差
linklist* minus(linklist*A,linklist*B){
    linklist *L,*a,*b,*r,*q;
    L = (linklist*)malloc(sizeof(linklist));
    L->next=NULL;
    r=L;

    a=A->next;
    b=insec(A,B)->next;

    while(a!=NULL){
        q = (linklist*)malloc(sizeof(linklist));
        q->data=a->data;
        r->next=q;
        r=r->next;
        a=a->next;
    }
    r->next = NULL;

    r=L;
    q=L->next;
    while(r!=NULL && b!=NULL){
        if (q->data==b->data){    
            q=q->next;
            r->next=q;
            b=b->next;
        }
        else if (q->data < b->data){
            r=r->next;
            q=q->next;
        }
        else{
            b=b->next;
        }
        
    }

    return L;
}

int main(){

    puts("请输入集合A");
    linklist *A=create();
    puts("请输入集合B");
    linklist *B=create();
    
    //集合预处理

    sort(A);
    sort(B);
    puts("两集合为：");
    print(A);
    print(B);

    //以下输出

    printf("set1∪set2＝");
    print(Union(A,B));
    printf("set1∩set2＝");
    print(insec(A,B));
    printf("set1-set2＝");
    print(minus(A,B));

    system("pause");
    return 0;
}