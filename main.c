#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int learn=10;
char menu(void);
int main()
{
    printf("Welcome to CET4\\6 Learning Program!\n");
    //�Ի��� ѯ�ʵ���ÿ�ռƻ�
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
 //��ʼ����

    //bianli(words_base);

    char menuChioce;
    while((menuChioce=menu()) != 'Q')
    {
        switch(menuChioce)
        {
        case 'A':
            printf("��ʼѧϰ\n");
            LearnWordProc(sentencebase,words_base,portTargetword);
            //
            break;
        case 'B':
            printf("���\n");
            //
            break;
        case 'C':
            printf("�Զ���\n");
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
    printf("A.ѧϰ                   B.���\n");
    printf("C.�Զ���                Q.�˳�\n");
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
