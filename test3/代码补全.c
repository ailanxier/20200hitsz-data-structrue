
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int FLAG = 0;  //��ʶ�Ƿ����ɺ���������������

typedef struct Node
{
    char data;
    struct Node *lchild, *rchild;
} TreeNode, *BiTree; //�������ڵ�Ľṹ��

BiTree createBiTree()//����������
{
    char data;

    return bt;

}
void preOrderTraverse(BiTree p)//�������ܣ�ǰ�����
{
    return;

}
void inOrderTraverse(BiTree p)//�������ܣ��������
{
    return;

}
void postOrderTraverse(BiTree p)//�������ܣ��������
{
    return;

}
BiTree* PostInCreate(char post[],int s1,int e1,char in[],int s2,int e2)
{
//�������ܣ����ݺ������������й���������������ظ��ڵ�
//����˵����post[]Ϊ�������У�s1,e1Ϊ����ĵ�һ�����һ���ڵ��±꣬in[]Ϊ�������У�s2,e2Ϊ����ĵ�һ�����һ���ڵ��±ꡣ

    return NULL; //��ɾ��
}
int countLeafSum(BiTree root)
{
//�������ܣ�����Ҷ�ӽڵ���

    return 0; //��ɾ��
}
int countHeight(BiTree root)
{
//�������ܣ�����������ĸ߶�,�������ĸ߶��������������������нϸߵ�һ�������ĸ߶��ټ�1

    return 0;//��ɾ��
}
void getwidth(BiTree root,int *count,int counter)
{
//�������ܣ��õ�һ��������ÿ��Ľڵ���Ŀ��
//����˵����counter��¼����,����count��¼ÿһ��Ľڵ���

}
int isEquivalent(BiTree bt1,BiTree bt2)
{
   //�������ܣ��ж������Ƿ�ȼ�
    //����˵����bt1:��һ����������bt2:�ڶ���������

}
void task1(BiTree bt){
    //����1��ʵ�ֶ������������򡢺������
    printf("start task (1) Create Tree in PreOrder\n");
    printf("preOrderTraverse\n");
    preOrderTraverse(bt);
    printf("\n");
    printf("inOrderTraverse\n");
    inOrderTraverse(bt);
    printf("\n");
    printf("postOrderTraverse\n");
    postOrderTraverse(bt);
    printf("\n");
}

void task2(BiTree *bt){
    //����2��������PostInCreate�������ݺ������������й��������
    //ʹ�ú�����PostInCreate
    printf("start task (2) Input the postOrder and inOrder Sequence ,Then build the tree\n");
    char post[20];  //��������
    char in[20];    //��������
    int postlen;    //�������г���
    int inlen;      //�������г���
    printf("please input the postorder sequence\n");
    scanf("%s",post);
    printf("please input the inorder sequence\n");
    scanf("%s",in);
    //�����ƺ���




    printf("preOrderTraverse:\n");
    preOrderTraverse(*bt);
    printf("\n");

}

void task3(BiTree bt){
    //����3�������������Ҷ�ڵ�����Ϳ�ȡ���ע������������ĺ����ǳ���������ƣ��������и��õİ취�õ���ȣ��Լ������ɡ���
    //ʹ�ú�����countLeafSum��countHeight��getwidth
    printf("start task (3) ------------------------------\n");
    int height;     //���ĸ߶�
    int maxwidth=-1;     //���Ŀ�ȣ�Ԥ��Ϊ-1������ȣ�������ÿһ��ڵ��������ֵ��
    printf("The number of leaf nodes of the tree is:\n");
    printf("%d\n",countLeafSum(bt));
    //�����ƺ���



    printf("The widht of the tree is:\n");
    printf("%d\n",maxwidth);
}


void task4(BiTree bt1,BiTree bt2){
    //����4���ж������������Ƿ�ȼ�
    //ʹ�ú�����isEquivalent
    printf("start task (4) Are two Bitrees equivalent?\n");
    printf("%d\n",isEquivalent(bt1,bt2));

}
int main()
{
    BiTree bt1,bt2;
    printf("Create Tree1 in PreOrder\n");
    bt1=createBiTree();

    task1(bt1);
    task2(&bt2);
    task3(bt2);
    //task4(bt1,bt2);

    return 0;
}
