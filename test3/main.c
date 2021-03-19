
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
//�������ڵ�Ľṹ��
typedef struct Node
{
    char data;
    struct Node *lchild, *rchild;
} TreeNode, *BiTree;

int leafSum = 0;//������3�м�¼Ҷ������
int floorSum[100];//������3�м�¼ÿһ��Ľ������ȡ���ֵ�õ����
int Depth = 0;//������3�м�¼�����������

//�ݹ齨��������
BiTree createBiTree()
{
    //����һ���¶�����
    BiTree newTree = (BiTree)malloc(sizeof(TreeNode));
    if(newTree == NULL) {
        printf("OVERFLOW");
        exit(0);
    }
    char data;//������ڵ��ַ�
    data = (char)getchar();
    if(data == '#') newTree = NULL;//�ַ�����#�൱�ڿ���
    else{
        newTree->data = data;
        newTree->lchild = createBiTree();//�ݹ齨����������ͬ���᷵���������ڵ�
        newTree->rchild = createBiTree();//ͬ
    }
    return newTree;
}

//����ĳһ�ڵ�
void visit(BiTree p){
    printf("%c",p->data);
}

//�������ܣ�ǰ�����
void preOrderTraverse(BiTree p)
{
    if(p == NULL) return;
    visit(p);
    preOrderTraverse(p->lchild);
    preOrderTraverse(p->rchild);
}

//�������ܣ��������
void inOrderTraverse(BiTree p)
{
    if(p == NULL) return;
    inOrderTraverse(p->lchild);
    visit(p);
    inOrderTraverse(p->rchild);
}

//�������ܣ��������
void postOrderTraverse(BiTree p)
{
    if(p == NULL) return;
    postOrderTraverse(p->lchild);
    postOrderTraverse(p->rchild);
    visit(p);
}

//�������ܣ����ݺ������������й���������������ظ��ڵ�
//����˵����post[]Ϊ�������У�postStart,postEndΪ����ĵ�һ�����һ���ڵ��±꣬in[]Ϊ�������У�inStart,inEndΪ����ĵ�һ�����һ���ڵ��±ꡣ
BiTree PostInCreate(char post[],int postStart,int postEnd,char in[],int inStart,int inEnd)
{
    BiTree newTree = (BiTree)malloc(sizeof(TreeNode));
    if(newTree == NULL) {
        printf("OVERFLOW");
        exit(0);
    }
    char rootData = post[postEnd];//�������е����һ������Ǹ�
    newTree->data = rootData;
    newTree->lchild = NULL;
    newTree->rchild = NULL;
    //�������г��Ⱥ��������в�һ�£����ش���
    if(postEnd-postStart != inEnd-inStart){
        printf("Unable to build a binary tree.\n");
        exit(0);
    }
    //���������ֻʣ��һ��Ԫ�أ��϶���Ҷ�ӽ��
    if(postEnd == postStart) {
        //�ж��������Ԫ���Ƿ���ȣ����Ȼ��ǲ��ܹ��ɶ�����
        if(rootData != in[inStart]){
            printf("Unable to build a binary tree.\n");
            exit(0);
        }
        return newTree;//ֱ�ӷ��أ����ٹ���������
    }
    int mid = inStart;//mid�������������ҵ����ڵ�
    for(;mid<=inEnd;mid++){
        if(in[mid] == rootData) break;
        //������һ�����ǻ���û�ҵ���˵�����ܹ���һ�ö�����
        else if(mid==inEnd){
            printf("Unable to build a binary tree.\n");
            exit(0);
        }
    }
    int leftLen = mid - inStart;//�����������г��ȣ��������������
    int rightLen = inEnd - mid;//�����������г���
    //ͨ�������������г��Ƚ�ԭ���м�������Ϊ���������������ĺ������������
    if(leftLen)newTree->lchild = PostInCreate(post,postStart,postStart+leftLen-1,in,inStart,inStart+leftLen-1);
    if(rightLen)newTree->rchild = PostInCreate(post,postEnd-rightLen,postEnd-1,in,inEnd-rightLen+1,inEnd);
    return newTree;
}

//�������ܣ��ݹ����Ҷ�ӽڵ�Ͷ����������
//��������depth��ȵ��������ڵ�root
void countLeafSumAndWidth(BiTree root,int depth)
{
    floorSum[depth]++;//�ò�ڵ�����һ
    //�ж��Ƿ�ΪҶ�ӽ�㣨�����������ǿյģ�
    if(root->lchild == NULL&&root->rchild == NULL) {
            leafSum++;
            Depth = Depth>=depth?Depth:depth;//���ȡ���ֵ
            return;
    }
    if(root->lchild != NULL) countLeafSumAndWidth(root->lchild,depth+1);
    if(root->rchild != NULL) countLeafSumAndWidth(root->rchild,depth+1);
}

//�������ܣ��ж������Ƿ�ȼ�
//����˵����bt1:��һ����������bt2:�ڶ���������
int isEquivalent(BiTree bt1,BiTree bt2)
{
    //���������ͬʱΪ�գ�˵��������Ϊֹ���ǵȼ۵�
    if(bt1 == NULL && bt2 == NULL) return 1;
    //�����ͬʱΪ�գ��򲻵ȼۣ�ֱ�ӷ���
    else if((bt1 == NULL && bt2 != NULL )||(bt1 != NULL && bt2 == NULL )) return 0;
    //���ڵ���ͬ�����ʸ��жϺ����Ƿ���ͬ
    if(bt1->data == bt2->data){
        //�ݹ��ж����������������Ƿ���ͬ
        if(isEquivalent(bt1->lchild,bt2->lchild)&&isEquivalent(bt1->rchild,bt2->rchild)) return 1;
        else return 0;
    }
    else return 0;
}

//����1��ʵ�ֶ������������򡢺������
void task1(BiTree bt){
    if(bt == NULL) {
        printf("This is an empty tree.\n");
        return;
    }
    printf("start task (1) Create Tree in PreOrder\n");
    printf("preOrderTraverse��\n");
    preOrderTraverse(bt);//�������
    printf("\n");
    printf("inOrderTraverse��\n");
    inOrderTraverse(bt);//�������
    printf("\n");
    printf("postOrderTraverse��\n");
    postOrderTraverse(bt);//�������
    printf("\n");
}

//����2��������PostInCreate�������ݺ������������й��������
//ʹ�ú�����PostInCreate
void task2(BiTree *bt){
    printf("------------------------------------------------\n");
    printf("start task (2) Input the postOrder and inOrder Sequence ,Then build the tree\n");
    char post[31];   //��������
    char in[31];      //��������
    int postLen;     //�������г���
    int inLen;        //�������г���
    printf("please input the postOrder sequence\n");
    scanf("%s",post+1);
    printf("please input the inOrder sequence\n");
    scanf("%s",in+1);
    postLen = (int)strlen(post + 1);//����һ���ַ��±��Ƶ�1������ʹ��
    inLen = (int)strlen(in + 1);
    //���鳤�ȹ�����Խ���������г��Ȳ�һ��
    if(postLen > 30 || inLen > 30 || postLen != inLen){
        printf("Unable to build a binary tree.\n");
        exit(0);
    }
    *bt = PostInCreate(post, 1, postLen, in, 1, inLen);
    printf("preOrderTraverse:\n");
    preOrderTraverse(*bt);
    printf("\n");
}

//����3�������������Ҷ�ڵ�����Ϳ��
//ʹ�ú�����countLeafSum
void task3(BiTree bt){
    countLeafSumAndWidth(bt,1);
    printf("------------------------------------------------\n");
    printf("start task (3)\n");
    printf("The number of leaf nodes of the tree is: %d\n",leafSum);
    int maxSum = 0;//����һ���ҵ����
    for(int i = 1;i <= Depth;i++) maxSum = maxSum>=floorSum[i]?maxSum:floorSum[i];
    printf("The width of the tree is:%d\n",maxSum);
}

//����4���ж������������Ƿ�ȼ�
//ʹ�ú�����isEquivalent
void task4(BiTree bt1,BiTree bt2){
    printf("------------------------------------------------\n");
    printf("start task (4) Are two Bitrees equivalent?\n");
    printf("%d\n",isEquivalent(bt1,bt2));
}

int main(){
    system("color f9");//��ɫ��������������
    memset(floorSum,0,sizeof(floorSum));//ͳ��ÿ������
    BiTree bt1,bt2;//��������ֱ������
    printf("Create Tree1 in PreOrder\n");

    //����1�������������й��������
    bt1=createBiTree();
    //���bt1�ǿſ�������������1����ʾ���������б���
    //���������򡢺������������
    task1(bt1);

    //����2��������ͺ����������
    task2(&bt2);

    //����3��ͳ������2�ж�����Ҷ�ӽ�����Ϳ��
    task3(bt2);

    //����4���ж�����1������2���������Ƿ�ȼ�
    task4(bt1,bt2);

    return 0;
}
