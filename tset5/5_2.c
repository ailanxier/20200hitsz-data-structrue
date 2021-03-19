#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MININTEGER 0

#define MAX(a,b) ((a>b) ? a : b)
int bucket[100];//18��65��Ͱ
//�������ܣ����ؿ��Ա���������������ֵ
int maximumGap(){
    int maxGap = -1;//�����
    int last = 0;//���ڵ���һ������
    for(int i = 18;i <= 65;i++){
        if(bucket[i]&&last != 0) maxGap = MAX(maxGap,i-last),last = i;
        else if(bucket[i]&&last == 0 ) last = i;//��һ������
    }
    return maxGap;
}
int main()
{
    int numsSize;  //���Ա����
    int count = 0; //�����������
    int maxdiff;   //���������������ֵ
    freopen("5_2_input.in", "r", stdin);

    while(scanf("%d",&numsSize)!=EOF){
        memset(bucket,0,sizeof(bucket));
        count++;
        int nums[numsSize];  //���Ա��������
        for(int i = 0;i < numsSize;i++){
            scanf("%d",&nums[i]);
            //����涨��18-65֮��
            if(nums[i]>65||nums[i]<18){
                printf("���䲻��18�굽65��֮��");
                exit(0);
            }
            bucket[nums[i]] = 1;//���������¼��Ͱ��
        }
        printf("======Case %d======\n",count);
        maxdiff = maximumGap();
        printf("%d\n", maxdiff);

    }
    fclose(stdin);

    return 0;
}
