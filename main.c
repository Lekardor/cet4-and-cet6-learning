#include <stdio.h>
#include <stdlib.h>
#include "head.h"
int main()
{
    sentence* sentencebase = (sentence*)malloc(MAX_SENTENCE*sizeof(sentence));
    CreateSentence_base(sentencebase,MAX_SENTENCE);
    wordsline *words_base = (wordsline*)malloc(26*sizeof(wordsline));
    int i;
    for(i=0;i<26;i++)
    {
        words_base[i]=(wordsline)malloc(sizeof(word));
    }
    char a[7]="abandon";
    CreateWordBase(words_base);
    BSTree* AVLTree=buildallTree(words_base,26);
    //printf("%s",AVLTree[24]->rchild->wordnord.word_info);
    BSTree result=choosetree(a,AVLTree,26);
    if(result)
    {
        printf("%s",result->wordnord.word_meaning);
    }

    /*int choose;
    printf("Welcome to CET4andCET6 learning program!\n");
    do
    {
        printf("******************MENU********************\n");
        printf("1.search word\n");
        printf("2.learning\n");
        printf("3.setting\n");
        printf("4.check\n");
        printf("5.save and exit\n");
        printf("*******************************************\n");
        printf("please enter a choose:");
        scanf("%d",choose);
        switch(choose)*/


}
