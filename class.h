#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED
using namespace std;

class Table
{
public:
    string table_name;    //����
    int attribute_num;    //���Ը���
    string attribute_name[100];      //������
    string attribute_type[100];//��������
    int attribute_length;//�������ͳ���
    //��������

    int tuple_num;        //Ԫ��ĸ���
    string table_data[100][100];		        //��ά��,����������Ǽ�¼��ֵ

    int prikey[100];//�������������λ�õ��±�
    int forkey[100];
    int unikey[100];
    int notnull[100];
    string foreigntable[100];//��������ӵı�
    string foreign[100];//��������ӱ�ļ�
    Table()
    {
        table_name="";
        attribute_length=0;
        for(int i=0; i<100; i++)
        {
            attribute_name[i]="";
            attribute_type[i]="";
            prikey[i]=-1;
            forkey[i]=-1;
            unikey[i]=-1;
            notnull[i]=-1;
            foreigntable[i]="";
            foreign[i]="";
             for(int j=0;j<100;j++){
                 table_data[i][j]="";
            }
        }
        attribute_num=0;
        tuple_num=0;        //Ԫ��ĸ���
    }
};

class View
{
public:
   // string proname[100];	//�ɼ�������
    string sql;
    string tname;		//��Ӧ�ı���
    string vname;		//��ͼ��
  //  int  pro_num;
    View()
    {
        for(int i=0;i<100;i++){
            ;
        }
        sql="";
        tname="";
        vname="";
       // pro_num=0;

    }
};	//��ͼ����ͼ��Ӧһ����һ������Զ�Ӧ�����ͼ
class Index
{
public:
    string iname[100];		//һ��������Ӧһ����
	string key_pro[100];                //��yin����
	int  key_;                    ///������Ӧ�±�
	string  from_table[100];     ///��һ���������
    int  index_num;
	string key[100];	         ///�ź���֮�����������
	int  key_ind[100];           ///�ź���֮��������±��Ӧԭ���е��±�
	Index(){
	}
};
#endif // CLASS_H_INCLUDED
