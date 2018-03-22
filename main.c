#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int learn=10;
char menu(void);
int main()
{
    printf("Welcome to CET4\\6 Learning Program!\n");
    //对话框 询问单词每日计划
    //
    word portTargetword[LearnWordNum+1];

    sentence* sentencebase = (sentence*)malloc(MAX_SENTENCE*sizeof(sentence));
    CreateSentence_base(sentencebase,MAX_SENTENCE);
    wordsline *words_base = (wordsline*)malloc(26*sizeof(wordsline));
    int i;
    for(i=0;i<26;i++)
    {
        words_base[i]=(wordsline)malloc(sizeof(word));
    }
    CreateWordBase(words_base);


    BSTree* AVLTree=buildallTree(words_base,26);

    chooseWordInBase(words_base,portTargetword);
 //开始运行

    //bianli(words_base);

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

//void bianli(wordsline a_to_z[])
//{
//    int vol;
//    wordsline ptr;
//    for(vol = 0;vol < 26;vol++)
//    {
//        ptr = a_to_z[vol];
//        while(ptr->nextword!= NULL)
//        {
//            printf("%s   %s\n",ptr->nextword->word_info,ptr->nextword->word_meaning);
//            ptr=ptr->nextword;
//        }
//    }
//
//}
