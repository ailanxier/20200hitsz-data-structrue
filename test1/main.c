
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int ClassID;
    int StuID;
    int Grade;
    struct node *next;
}StudentLinkedListNode;

/** ��ӡ�����ڵ� */
void printLinkedListNode(StudentLinkedListNode * node){
    printf("{name:%d, ID:%d, Grade:%d}",node->ClassID, node->StuID, node->Grade);
    if(node->next!=NULL){
        printf("->");
    }else{
        printf("\n");
    }
}

/** ����ñ�ĳɼ���� */
void outputStudentLinkedList(StudentLinkedListNode* head){
    //���ڵ����ڵ�����ĺ���printLinkedListNode���ṩ
    //����Ƿ�Ϊ�ձ�
    if(head == NULL||head->next == NULL){
        printf("��ǰΪ�ձ�������������");
        return;
	}
	StudentLinkedListNode * nowNode = head->next;
	//��nowNode��Ϊ��ʱ���������Ԫ��ֵ������,ֱ������ĩβ
	while(nowNode != NULL){
        printLinkedListNode(nowNode);
        nowNode = nowNode->next;
	}
}

/** �½�һ������node�����ص�ַ */
StudentLinkedListNode* studentLinkedListCreate( int class_id,int student_id,int grade) {
    //tips:malloc��ʱ��ǵ�Ϊת��Ϊ�ṹ��ָ��
	//TODO
	StudentLinkedListNode * newStudentNode = (StudentLinkedListNode *)malloc(sizeof(StudentLinkedListNode));
	//����Ƿ�����ɹ�
	if(newStudentNode == NULL){
        printf("�ڴ治��");
        exit(0);
	}
	newStudentNode->ClassID = class_id;
	newStudentNode->Grade = grade;
	newStudentNode->StuID = student_id;
	newStudentNode->next = NULL;
	return newStudentNode;//�����½ڵ��ַ
}

/** copyһ�����е�node */
StudentLinkedListNode* studentLinkedListCopy(StudentLinkedListNode* src){
    StudentLinkedListNode* tempNode = studentLinkedListCreate(src->ClassID,src->StuID,src->Grade);
    return tempNode;
}

/** ���ս������ѧ���ĳɼ����,����������ͷָ�� */
StudentLinkedListNode* studentLinkedListAdd(StudentLinkedListNode* head, StudentLinkedListNode* node) {
    //�ȼ���ͷ�ڵ��Ƿ�Ϊ��
    if(head == NULL){
        head = (StudentLinkedListNode *)malloc(sizeof(StudentLinkedListNode));
        if(head == NULL){
            printf("�ڴ治��");
            exit(0);
        }
    }
    //�ټ���Ƿ��ǿձ�
    if(head->next == NULL){
        head->next = node;
        node->next = NULL;
    }
    else{
        StudentLinkedListNode * nowNode = head->next;//ָ��ǰ�ڵ�
        StudentLinkedListNode * priorNode = head;//������ǰ�ڵ���һ���ڵ�
        if(node->Grade > nowNode->Grade){//���������½ڵ�ɼ��Ѿ����ڵ�ǰ�ǰ�ĳɼ�����Ҫ�޸�head->next��ָ��
            head->next = node;
            node->next = nowNode;
        }
        else{
            //nowNode�����ҵ���һ����С��node�ɼ�ֵ�Ľڵ�
            while(node->Grade < nowNode->Grade){
                priorNode = nowNode;
                nowNode = nowNode->next;
                 //�����ǰ�������нڵ�ɼ�����nodeС���˳�
                if(nowNode == NULL)
                   break;
            }
            //��ʱnode����nowNode�ɼ�ֵС����priorNodeС�������м�
            priorNode->next = node;
            node->next = nowNode;
        }
    }
    return head;
}

/** ����ѧ������ĳ��ѧ���ĳɼ���� ���û��,��printf("this class  has no such student as id=%d",id)�� */
void searchByID(StudentLinkedListNode * head ,int id){
    //�ð༶�ɼ���Ϊ�ձ�,ֱ�����
    if(head == NULL||head->next == NULL){
        printf("this class has no such student as id=%d",id);
        return;
    }
    StudentLinkedListNode * nowNode = head->next;
    //��nowNode��Ϊ��ʱ���Ƚ�����ѧ��
    while(nowNode != NULL){
        if(nowNode->StuID == id){
            printf("�༶��%d  ѧ�ţ�%d  �ɼ���%d\n",nowNode->ClassID,id,nowNode->Grade);
            return;
        }
        nowNode = nowNode->next;
    }
    //û����while��return,û���ҵ���ѧ������Ϣ
    printf("this class  has no such student as id=%d",id);
}

/** ����ѧ��ɾ��ĳ��ѧ���ĳɼ���� ���û��,��printf("this class has no such student as id=%d",id);*/
StudentLinkedListNode* deleteByID(StudentLinkedListNode* head,int id){
    //�ð༶�ɼ���Ϊ�ձ�,ֱ�����
    if(head == NULL||head->next == NULL){
        printf("this class has no such student as id=%d",id);
        return head;
    }
    StudentLinkedListNode * nowNode = head->next;
    StudentLinkedListNode * priorNode = head;
    //��nowNode��Ϊ��ʱ���Ƚ�����ѧ��
    while(nowNode != NULL){
        if(nowNode->StuID == id){
            //��nowNode��һ���ڵ�ָ��nowNode�¸��ڵ㣬Ȼ�����ͷ�nowNode
            priorNode->next = nowNode->next;
            free(nowNode);
            printf("the student id=%d is deleted",id);
            return head;
        }
        //priorNode���浱ǰ�ڵ㣬nowNode����
        priorNode = nowNode;
        nowNode = nowNode->next;
    }
    //û����while��return,û���ҵ���ѧ������Ϣ
    printf("this class  has no such student as id=%d",id);
    return head;
}

/** �ϲ������༶�ĳɼ�����������±�ͷָ��*/
StudentLinkedListNode* mergeLinkedList(StudentLinkedListNode * heads[]){
    //tips:��Ϊ����Ķ���ָ��,Ϊ�˷�ֹ��ֹ�����Ӱ����ԭ��������Ĵ洢,
    //������node��ֵ��ʱ������������ṩ��studentLinkedListCopy����
    //�� node->next = temp_node ��Ϊ node->next = studentLinkedListCopy(temp_node)

    StudentLinkedListNode * nowNode_0 ;//ָ��0��ڵ��ָ��
	StudentLinkedListNode * nowNode_1 ;//ָ��1��ڵ��ָ��
	//����Ƿ�Ϊ�ձ�
	if(heads[0] == NULL) nowNode_0 = NULL;//�ձ���ָ��Ϊ�գ���while�л��Զ�����
	else nowNode_0 = heads[0]->next;//����ָ���һ���ڵ�
	if(heads[1] == NULL) nowNode_1 = NULL;
	else nowNode_1 = heads[1]->next;
	//�������ͷָ��
	StudentLinkedListNode * newHead = (StudentLinkedListNode *)malloc(sizeof(StudentLinkedListNode));
	//����Ҫ���������Ľڵ��Ƿ�����ɹ�
	if(newHead == NULL){
        printf("�ڴ治��");
        exit(0);
	}
	//����������Ľڵ�
	StudentLinkedListNode * newNode = newHead;
	while(nowNode_0 != NULL && nowNode_1 != NULL){
        //newNodeָ��ɼ��ϴ�ڵ�ĸ��ƽڵ�
        if(nowNode_0->Grade >= nowNode_1->Grade) {
             newNode->next = studentLinkedListCopy(nowNode_0);
             nowNode_0 = nowNode_0->next;
        }else{
            newNode->next = studentLinkedListCopy(nowNode_1);
            nowNode_1 = nowNode_1->next;
        }
        newNode = newNode->next;
	}
	//���ڻ��еĲ���ֱ����ӽ��������У�����ԭ��Ľ����ԣ��±�һ���ǽ����
	while(nowNode_0 != NULL){
        newNode->next = studentLinkedListCopy(nowNode_0);
        nowNode_0 = nowNode_0->next;
        newNode = newNode->next;
	}
	while(nowNode_1 != NULL){
        newNode->next = studentLinkedListCopy(nowNode_1);
        nowNode_1 = nowNode_1->next;
        newNode = newNode->next;
	}
	newNode->next = NULL;
	//�����������ͷָ��
    return newHead;
}

/**����ת�������±�ͷָ��*/
StudentLinkedListNode* reverseLinkedList(StudentLinkedListNode * head){
    //����Ƿ�Ϊ�ձ�,����ֻ��һ��Ԫ�أ�ֱ�ӷ���ԭͷ��㣬���÷�ת
    if(head == NULL || head->next == NULL || head->next->next == NULL)
        return head;
    StudentLinkedListNode * nowNode = head->next;
    StudentLinkedListNode * newHead = (StudentLinkedListNode * )malloc(sizeof(StudentLinkedListNode));
    //����Ƿ�����ɹ�
    if(newHead == NULL){
        printf("�ڴ治��");
        exit(0);
    }
    //newNodeΪ�������е��½ڵ㣬��������������
    StudentLinkedListNode * newNode = NULL;
    while(nowNode != NULL){
        //temp����nowNode�ı��ݣ�����ָ��newNodeָ��ĵ�ַ��newNode��ָ����
        StudentLinkedListNode * temp = studentLinkedListCopy(nowNode);
        temp->next = newNode;
        newNode = temp;
        nowNode = nowNode->next;
    }
    //��������ͷָ��nextָ��newNode
    newHead->next = newNode;
    return newHead;
}

/**��������ȷ���Ƿ����ظ���ѧ��*/
_Bool isExistStudentId(StudentLinkedListNode * head, int id){
    //�ձ�ֱ�ӷ���û���ظ�ѧ��
    if(head == NULL|| head->next == NULL) return 0;
    StudentLinkedListNode * nowNode = head->next;
    while(nowNode != NULL){
        if(nowNode->StuID == id) return 1;
        nowNode = nowNode->next;
    }
    return 0;
}

int main(){
        system("color 7d");//������ڱ�ɫ
        StudentLinkedListNode* Class[2]={NULL};
        StudentLinkedListNode* All=NULL;
		StudentLinkedListNode* reAll=NULL;
        printf("1.insert 2.search by StuID 3.delete by StuID  4.merge 5.reverse 6.output 7.exit  \n");

        int option;
        int dataRow;
        int tempClass;
        int tempStuId;
        int tempGrade;
        StudentLinkedListNode *tempNode;//��������ѧ����Ϣ�Ľڵ�
        while (scanf("%d", &option) != EOF) {
            fflush(stdin);//��ֹ�������
            switch (option) {
                case 1:
                    //������Ϣ
                    printf("How many rows of data do you need to input?\n");
                    //һ����һ��ѧ������Ϣ
                    while(scanf("%d",&dataRow)!=1){
                        printf("�������Ϣ�к��Ƿ��ַ������������ʽ�����������룺\n");
                        fflush(stdin);
                    }
                    //��ʾ�����dataRow����1�У����Ϸ�
                    if(dataRow <= 0){
                        printf("���������������������1");
                        break;
                    }
                    fflush(stdin);//���������������
                    printf("input the %d row data format as:class_id,student_id,grade\n",dataRow);
                    while (dataRow!=0){
                        //����������쳣�����Ƿ��ַ�
                        while(scanf("%d,%d,%d", &tempClass,&tempStuId, &tempGrade)!=3){
                            printf("�������Ϣ�к��Ƿ��ַ������������ʽ�����������룺\n");
                            fflush(stdin);
                        }
                        //��������༶��Ϊ1��2�����Ƴɼ����ܵ���0�֣�����ѧ�Ų���Ϊ����
                        if(tempClass != 0 && tempClass != 1){
                            printf("����༶����Ϊ0��1,���������룺\n");
                            continue;
                        }
                        if(tempGrade < 0){
                            printf("����ĳɼ�����0�֣����Ϸ�,���������룺\n");
                            continue;
                        }
                        if(tempStuId < 0){
                            printf("�����ѧ�Ų���С��0�����������룺\n");
                            continue;
                        }
                        if(isExistStudentId(Class[tempClass],tempStuId)){
                            printf("ѧ��Ϊ%d��ѧ����Ϣ�Ѵ��ڣ����������룺\n",tempStuId);
                            continue;
                        }
                        //�Ӹ��ж�ѧ���ظ�
                        tempNode = studentLinkedListCreate(tempClass, tempStuId, tempGrade);
                        Class[tempClass]=studentLinkedListAdd(Class[tempClass], tempNode);
                        dataRow--;
                    }
                    break;
                case 2:
                    //����ѧ������ĳ��ѧ���ĳɼ����
                    printf("input the data format as: ClassID, StuID\n");
                    //����������쳣�����Ƿ��ַ�
                    while(scanf("%d,%d,%d", &tempClass,&tempStuId)!=2){
                        printf("�������Ϣ�к��Ƿ��ַ������������ʽ�����������룺\n");
                        fflush(stdin);
                    }
                    //�������İ༶��ѧ���Ƿ����Ҫ��,����༶��Ϊ1��0��ѧ��С��0��ֱ�����δ�ҵ�
                    if((tempClass != 0 && tempClass != 1)||tempStuId < 0 ){
                        printf("this class has no such student as id=%d",tempStuId);
                        break;
                    }
                    searchByID(Class[tempClass],tempStuId);
                    break;
                case 3:
                    //����ѧ��ɾ��ĳ��ѧ������Ϣ
                    printf("input the data format as: ClassID, StuID\n");
                    //����������쳣�����Ƿ��ַ�
                    while(scanf("%d,%d,%d", &tempClass,&tempStuId)!=2){
                        printf("�������Ϣ�к��Ƿ��ַ������������ʽ���������룺\n");
                        fflush(stdin);
                    }
                    //�������İ༶��ѧ���Ƿ����Ҫ��,����༶��Ϊ1��0��ѧ��С��0��ֱ�����δ�ҵ�
                    if((tempClass != 0 && tempClass != 1)||tempStuId < 0){
                        printf("this class has no such student as id=%d",tempStuId);
                        break;
                    }
                    Class[tempClass]=deleteByID(Class[tempClass], tempStuId);
                    break;
                case 4:
                    //�ϲ�����
                    All=mergeLinkedList(Class);
                    outputStudentLinkedList(All);
                    break;
                case 5:
                    //��ת����
                    reAll=reverseLinkedList(All);
                    outputStudentLinkedList(reAll);
                    break;
                case 6:
                    //�������
                    printf("Class 0:\n");
                    outputStudentLinkedList(Class[0]);
                    printf("\nClass 1:\n");
                    outputStudentLinkedList(Class[1]);
                    break;
                case 7:
                    //����ѭ�����˳�����
                    exit(0);
                default:
                    //����ָ�����ʾ
                    printf("ָ��ֻ��Ϊ1-6֮���ĳ������ֵ.\n");
                    break;
            }
            fflush(stdin);//�������
            printf("\n###################################\n");
            printf("1.insert 2.search by studentID 3.delete by studentID 4.merge 5. reverse 6.output 7.exit \n");
    }
    return 0;
}
