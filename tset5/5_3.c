#include<stdio.h>
#include <stdlib.h>
//�������ֵ
int max(int n1,int n2){
    return n1>n2?n1:n2;
}
//������Сֵ
int min(int n1,int n2){
    return n1>n2?n2:n1;
}
//����
void swap(int *n1,int *n2){
    int tem = *n1;
    *n1 = *n2;
    *n2 = tem;
}
/** �������� */
void sort(int * arr, int l,int r){
    int mid = arr[(l+r)/2];//��Ԫ
    int i = l,j = r;//����ԭ������˵���Ҷ˵�
    while(i <= j){
        while(arr[i]<mid) i++;
        while(mid<arr[j]) j--;
        if(i <= j){
            swap(arr+i,arr+j);
            i++,j--;
        }
    }
    if(j>l)  sort(arr,l,j);//�ݹ�����
    if(i<r) sort(arr,i,r);
}

//ʵ�ֺ������ܣ��������ٵ��ʵ�Ա������
int getMinNum(const int *array, int n){
    int peopleNum=n;//�ʵ�Ա����,��ʼ��Ϊ�ش���˵�����
    int sameAns = array[1];//��ͬ�ش��ֵ
    int sameCount = 0;//��ͬ�ش�ļ���
    for(int i  =2;i <= n;i++){
        //�ش���ǰһλ��ͬ
        if(array[i] == sameAns){
            sameCount++;//��ͬ�ش�����һ
            if(sameCount == sameAns) sameCount = -1;//����ճ�һ�飬�ͽ�������Ϊ-1
        }
        else {
            //����ش���ͬ������һλ�ش�û�дճ�һ��
            if(sameCount != -1) peopleNum+=sameAns-sameCount;
            sameAns = array[i];
            sameCount = 0;
        }
    }
    //����ĩβ�����������һ����û�дճ�һ�飬�ͼ���
    if(sameCount != -1) peopleNum+=sameAns-sameCount;
    return peopleNum;
}

int main(){

    int n,caseNum = 0;//����ش���ʵ�Ա��Ŀ
    //�ļ��������
    freopen("5_3_input.in", "r", stdin);
    while(scanf("%d",&n)!=EOF){
        printf("======Case %d======\n",++caseNum);
        int array[n+1];
        for(int i=1;i<=n;i++)  scanf("%d",&array[i]);
        sort(array,1,n);
        printf("There are at least %d postmen.\n", getMinNum(array, n));
    }
    fclose(stdin);
    return 0;
}
