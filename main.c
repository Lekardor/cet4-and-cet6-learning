#include <stdio.h>
#include <stdlib.h>
#include "head.h"

char menu(void);
int main()
{
    word portTargetword[LearnWordNum+1];

    sentence* sentencebase = (sentence*)malloc(MAX_SENTENCE*sizeof(sentence));
    CreateSentence_base(sentencebase,MAX_SENTENCE);
    wordsline *words_base = (wordsline*)malloc(26*sizeof(wordsline));
    int i;
    for(i=0;i<26;i++)
    {
        words_base[i]=(wordsline)malloc(sizeof(word));
    }
    //char a[7]="deficit";
    CreateWordBase(words_base);
    BSTree* AVLTree=buildallTree(words_base,26);
    //BSTree result=choosetree(a,AVLTree,26);
    printf("%s",AVLTree[0]->rchild->wordnord.word_info);

    chooseWordInBase(words_base,portTargetword);
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
    //梁俊平 2018年3月21日19:39:02 修改
    printf("welcome to CET4\\6 learning program!\n");
    char menuChioce;
    while((menuChioce=menu()) != 'Q')
    {
        switch(menuChioce)
        {
        case 'A':
            printf("开始学习\n");
            LearnWordProc(sentencebase,words_base,portTargetword);
            //
            break;
        case 'B':
            printf("查词\n");
            //
            break;
        case 'C':
            printf("自定义\n");
            //
            break;
        default:
            printf("program error!\n");
            //
            break;
        }
    }
    printf("bye!");

    return 0;
}


char menu(void)
{
    int ch;

    printf("Enter the letter of your choice:\n");
    printf("*****************************************\n");
    printf("A.学习                   B.查词\n");
    printf("C.自定义                Q.退出\n");
    printf("*****************************************\n");

    ch = get_first();
    while ((ch < 'A' || ch > 'C') && ch != 'Q')
    {
        printf("Please respond with A,B,C or Q.\n");
        ch = get_first();
    }

    return ch;
}
