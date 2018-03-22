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

BSTree R_Rotate(BSTree p)  //右旋转
{
    BSTree lc;
    lc=p->lchild;
    p->lchild=lc->rchild;
    lc->rchild=p;
    return lc;
}

BSTree L_Rotate(BSTree p)  //左旋转
{
    BSTree rc;
    rc=p->rchild;
    p->rchild=rc->lchild;
    rc->lchild=p;
    return rc;
}

BSTree LeftBalance(BSTree t)//左平衡
{
    BSTree lc;
    BSTree rd;
    lc=t->lchild;
    switch(lc->bf)
    {
    case LH:
        t->bf=lc->bf=EH;
        return R_Rotate(t);
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
        t->lchild=L_Rotate(t->lchild);
        return R_Rotate(t);
        break;
    }
}

BSTree RightBalance(BSTree t)//右平衡
{
    BSTree rc;
    BSTree ld;
    rc=t->rchild;
    switch(rc->bf)
    {
    case RH:
        t->bf=rc->bf=EH;
        return L_Rotate(t);
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
        t->rchild=R_Rotate(t->rchild);
        return L_Rotate(t);
        break;
    }
}

int wordcomparing(char* a,char* b)//比较两个单词大小
{
    int i=0;
    while('a'<=a[i]&&a[i]<='z'&&'a'<=b[i]&&b[i]<='z')//依次比较各个字母大小
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

    if('a'<=a[i]&&a[i]<='z')
    {
        return morethan;
    }
    if('a'<=b[i]&&b[i]<='z')
        return lessthan;
    else
        return equal;


}

BSTree InsertAVL(BSTree t,word a, Boolean *taller,Boolean *same)//平衡二叉树的插入操作
{
    //word b;
    //word c;
    //int e;
    //int f;
    //e=t->flag;
    BSTree lc;
    BSTree rc;
    if(t->flag==0)//插入新节点
    {
        t->wordnord=a;
        t->lchild=(BSTree)malloc(sizeof(BSTNode));
        t->lchild->flag=0;
        t->rchild=(BSTree)malloc(sizeof(BSTNode));
        t->rchild->flag=0;
        t->bf=EH;
        *taller=true;
        t->flag=1;
    }
    else
    {
        if(wordcomparing(t->wordnord.word_info,a.word_info)==equal)
        {
            *taller=false;
            *same=true;
            return t;

        }
        if(wordcomparing(t->wordnord.word_info,a.word_info)==morethan)
        {
            lc=InsertAVL(t->lchild,a,taller,same);
            if(*same==true)
            {
                return t;
            }
            t->lchild=lc;
            if(*taller)
            {
                switch(t->bf)
                {
                case LH:
                  t=LeftBalance(t);
                    *taller=false;
                    break;
                case EH:
                    t->bf=LH;
                    *taller=true;
                    break;
                case RH:
                    t->bf=EH;
                    *taller=false;
                    break;
                }
            }

        }
        else
        {
            rc=InsertAVL(t->rchild,a,taller,same);
           if(*same==true)
           {
               return t;
           }
           t->rchild=rc;
           if(*taller)
            {
                switch(t->bf)
                {
                case LH:
                    t->bf=EH;
                    *taller=false;
                    break;
                case EH:
                    t->bf=RH;
                    *taller=true;
                    break;
                case RH:
                    t=RightBalance(t);
                    *taller=false;
                    break;
                }
            }
        }
    }
    //b=t->rchild->wordnord;
    //c=t->lchild->wordnord;
    //e=t->rchild->flag;
    //f=t->lchild->flag;
    return t;
}

BSTree buildBSTree(wordsline line)//一个AVL树建立
{
    //int b;
    BSTree t;
    t=(BSTree)malloc(sizeof(BSTNode));
    t->flag=0;
    wordsline copy;
    Boolean *taller=(Boolean*)malloc(sizeof(Boolean));
    Boolean *same=(Boolean*)malloc(sizeof(Boolean));
    *same=false;
    *taller=1;
    copy = line;
    //word a;
    //word c;
    do
    {
        copy=copy->nextword;
        //c=*copy;
        t=InsertAVL(t,*copy,taller,same);
        //b=t->flag;
        //a=t->wordnord;
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
    //word b;
    if(t)
    {
        if(wordcomparing((t->wordnord).word_info,a)==equal)
        {
            //word b=t->wordnord;
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
    return NULL;
}

BSTree choosetree(char* a,BSTree alltree[],int n)
{
 //   printf("c",alltree[0]->wordnord.word_info[0]);
    int i;
    BSTree result = (BSTree)malloc(sizeof(BSTNode));
    for(i=0;i<n;i++)
    {
        if(a[0]=='a'+i)
        {
            result=wordsearch(alltree[i],a);
            return result;

        }
    }
    free(result);
    return NULL;
}

