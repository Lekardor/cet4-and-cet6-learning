#include "head.h"
#include <stdio.h>
#include <stdlib.h>
/*#define morethan 1
#define lessthan -1
#define equal 0

#define LH 1//左高
#define EH 0//等高
#define RH -1//右高

#define Boolean int
#define true 1
#define false 0

typedef struct BSTNode
{
    word wordnord;
    int bf;   //节点的平衡因子
    struct BSTNode *lchild,*rchild;//左右孩子指针
}BSTNode, *BSTree;*/

void R_Rotate(BSTree p)  //右旋转
{
    BSTree lc;
    lc=p->lchild;
    p->lchild=lc->rchild;
    lc->rchild=p;
    p=lc;
}

void L_Rotate(BSTree p)  //左旋转
{
    BSTree rc;
    rc=p->rchild;
    p->rchild=rc->lchild;
    rc->lchild=p;
    p=rc;
}

void LeftBalance(BSTree t)//左平衡
{
    BSTree lc;
    BSTree rd;
    lc=t->lchild;
    switch(lc->bf)
    {
    case LH:
        t->bf=lc->bf=EH;
        R_Rotate(t);
        break;
    case RH:
        rd=lc->rchild;
        switch(rd->bf)
        {
        case LH:
            t->bf=RH;
            lc->bf=EH;
            break;
        case EH:
            t->bf=lc->bf=EH;
            break;
        case RH:
            t->bf=EH;
            lc->bf=LH;
            break;
        }
        rd->bf =EH;
        L_Rotate(t->lchild);
        R_Rotate(t);
        break;
    }
}

void RightBalance(BSTree t)//右平衡
{
    BSTree rc;
    BSTree ld;
    rc=t->rchild;
    switch(rc->bf)
    {
    case RH:
        t->bf=rc->bf=EH;
        L_Rotate(t);
        break;
    case LH:
        ld=rc->lchild;
        switch(ld->bf)
        {
        case LH:
            t->bf=EH;
            rc->bf=RH;
            break;
        case EH:
            t->bf=rc->bf=EH;
            break;
        case RH:
            t->bf=LH;
            rc->bf=EH;
            break;
        }
        ld->bf =EH;
        R_Rotate(t->rchild);
        L_Rotate(t);
        break;
    }
}

int wordcomparing(char* a,char* b)//比较两个单词大小
{
    int i=0;
    while(a[i]!='\0'&&b[i]!='\0')//依次比较各个字母大小
    {
        if(a[i]>b[i])
            {
                return morethan;
            }
        if(a[i]<b[i])
            {
                return lessthan;
            }
        else
            {
                i++;
            }
    }
    if(strlen(a)>strlen(b))
    {
        return morethan;
    }
    if(strlen(a)<strlen(b))
    {
        return lessthan;
    }
    else
    {
        return equal;
    }
}

int InsertAVL(BSTree* t,word a, Boolean *taller)//平衡二叉树的插入操作
{
    word b;
    if(!*t)//插入新节点
    {
        *t=(BSTree)malloc(sizeof(BSTNode));
        (*t)->wordnord=a;
        (*t)->lchild=(*t)->rchild=NULL;
        (*t)->bf=EH;
        *taller=true;
    }
    else
    {
        if(wordcomparing((*t)->wordnord.word_info,a.word_info)==equal)
        {
            *taller=false;
            return 0;
        }
        if(wordcomparing((*t)->wordnord.word_info,a.word_info)==morethan)
        {
            if(!InsertAVL(&((*t)->lchild),a,taller))
            {
                return 0;
            }
            if(*taller)
            {
                switch((*t)->bf)
                {
                case LH:
                    LeftBalance((*t));
                    *taller=false;
                    break;
                case EH:
                    (*t)->bf=LH;
                    *taller=true;
                    break;
                case RH:
                    (*t)->bf=EH;
                    *taller=false;
                    break;
                }
            }

        }
        else
        {
           if(!InsertAVL(&((*t)->rchild),a,taller))
           {
               return 0;
           }
           if(*taller)
            {
                switch((*t)->bf)
                {
                case LH:
                    (*t)->bf=EH;
                    *taller=false;
                    break;
                case EH:
                    (*t)->bf=RH;
                    *taller=true;
                    break;
                case RH:
                    RightBalance((*t));
                    *taller=false;
                    break;
                }
            }
        }
    }
    b=(*t)->wordnord;
    return 1;
}

BSTree buildBSTree(wordsline line)//一个AVL树建立
{
    BSTree t;
    t=NULL;
    wordsline copy;
    Boolean *taller=(Boolean*)malloc(sizeof(Boolean));
    *taller=1;
    copy = line;
    word a;
    do
    {
        copy=copy->nextword;
        InsertAVL(&t,*copy,taller);
        a=*copy;
    }while(copy->nextword!=NULL);
   // word a=t->wordnord;
    free(taller);
    return t;
}

BSTree* buildallTree(wordsline wordbase[],int n)
{
    int i;
    BSTree *alltree=(BSTree*)malloc(26*sizeof(BSTree));
    for(i=0;i<n;i++)
    {
        alltree[i]=buildBSTree(wordbase[i]);
    }
    //word a=alltree[0]->wordnord;
    //printf("%d",alltree[0]->wordnord.word_type);
    return alltree;
}
BSTree wordsearch(BSTree t,char* a)//单词搜索
{
    if(wordcomparing((t->wordnord).word_info,a)==equal)
    {
        return t;
    }
    if(wordcomparing(t->wordnord.word_info,a)==morethan)
    {
        return wordsearch(t->lchild,a);
    }
    else
    {
        return wordsearch(t->rchild,a);
    }
}

BSTree choosetree(char* a,BSTree alltree[],int n)
{
 //   printf("c",alltree[0]->wordnord.word_info[0]);
    int i;
    BSTree result = (BSTree)malloc(sizeof(BSTNode));
    for(i=0;i<n;i++)
    {
        if(a[0]==(alltree[i]->wordnord).word_info[0])
        {
            result=wordsearch(alltree[i],a);
            return result;

        }
    }
    free(result);
    return NULL;
}

