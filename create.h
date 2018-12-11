#ifndef CREATE_H_INCLUDED
#define CREATE_H_INCLUDED
#include "select.h"
void create_table(char *sentence,Table *&t,int &t_num)
{
    ///�õ��������Ը�����ͨ���м����������������ж��м������ԣ���Ȼ���п��ܰ���������Լ����
    int len=strlen(sentence);
    for(int i=0; i<len; i++)
    {
        if(sentence[i]==',')
        {
            t[t_num].attribute_num++;
        }
    }
    t[t_num].attribute_num++;

    ///�������б�����һ�����ţ���Ϊһ�������У�������Լ�����У�ʹ��strtok����ȡ��䣩
    string attribute[100];
    string tokenPtr=strtok(sentence," ");
    tokenPtr=strtok(NULL," ");
    tokenPtr=strtok(NULL,"(");
    ///�����ظ��Լ��,�����Ƿ���ڡ��������������±������ڷ�����һ��
    for(int i=0; i<t_num; i++)
    {
        if(tokenPtr==t[i].table_name)
        {
            cout<<"�ñ��Ѵ��ڣ����ؽ���"<<endl;
            //exit(1);
            return;
        }
    }
    t[t_num].table_name=tokenPtr;	//�±����
    //table_name = atoi(tokenPtr);
    ///�õ������������������Ϣ���������б��С���������� ��ʽ����ȷ��
    int count=0;
    while(tokenPtr.size()!=0&&count<t[t_num].attribute_num)
    {

        tokenPtr=strtok(NULL,",");

        if(count== t[t_num].attribute_num-1)
        {
            int len1=tokenPtr.length();
            if(tokenPtr[len1-1]!=';'||(tokenPtr[len1-2]==')'&&tokenPtr[len1-3]=='(')||(tokenPtr[len1-2]==')'&&tokenPtr[len1-3]<'9'&&tokenPtr[len1-3]>'0')||(tokenPtr[len1-2]==')'&&tokenPtr[len1-3]<'Z'&&tokenPtr[len1-3]>'A'))
            {
                cout<<"�����ʽ����!"<<endl;
            }

            attribute[count]=tokenPtr.erase(len1-2);

        }
        else
            attribute[count]=tokenPtr;
        count++;
    }

    int p=0;//����Լ���Լ��ĸ���
    int f=0;
    int n=0;
    int u=0;
///���б�����ȡ�й���Ϣ
    for(int i=0; i<count; i++)
    {
        //���б��еķ����õķ����滻Ϊ�ո�
        for(int j=0; j<attribute[i].length(); j++)
        {
            if(attribute[i][j]=='(')
            {
                attribute[i][j]=' ';
            }
            if(attribute[i][j]==')')
            {
                attribute[i][j]=' ';
            }
        }
        // cout<<attribute[i]<<endl;
        istringstream ss(attribute[i]);
        string tmp;
        ss>>tmp;//ÿ�е�һ���ַ���

        if(tmp=="primary")
        {
            string mn;
            ss>>mn;
            ss>>mn;//������

            for(int j=0; j<i; j++)
            {
                if(t[t_num].attribute_name[j]==mn)
                {
                    t[t_num].prikey[p]=j;
                    p++;
                }
            }

            t[t_num].attribute_num--;//������
        }
        else if(tmp=="foreign")
        {
            string mn;
            ss>>mn;
            ss>>mn;//�����
            for(int j=0; j<i; j++)
            {
                if(t[t_num].attribute_name[j]==mn)
                {
                    t[t_num].forkey[f]=j;

                }
            }
            ss>>mn;
            ss>>mn;
            t[t_num].foreigntable[f]=mn;
            ss>>mn;
            t[t_num].foreign[f]=mn;
            t[t_num].attribute_num--;//������
            f++;
        }
        else
        {
            t[t_num].attribute_name[i]=tmp;
            string mn;
            ss>>mn;
            t[t_num].attribute_type[i]=mn;
            //cout<<t.attribute_name[i]<<"ÿ�е�һ���ַ���"<<t.attribute_type[i]<<endl;
            if(mn=="char")
            {
                ss>>mn;
                t[t_num].attribute_length=atoi(mn.c_str());
            }
            ss>>mn;
            if(mn=="")
            {
                continue;
            }
            else
            {
                if(mn=="primary")
                {
                    t[t_num].prikey[p++]=i;
                }

                if(mn=="not")
                {
                    string tt;
                    ss>>tt;
                    if(tt=="null")
                        t[t_num].notnull[n++]=i;
                }
                if(mn=="unique")
                    t[t_num].unikey[u++]=i;
            }
            //  cout<<t.prikey<<"zhu"<<t.notnull<<"kong"<<t.unikey<<"weiyi"<<endl;

        }

    }
    t_num++;
    cout<<t[t_num-1].table_name<<"�����ɹ���"<<endl;

    ofstream outfile;
    outfile.open("table.txt");
    if(!outfile)
    {
        cerr<<"open error!"<<endl;
        exit(1);
    }
    for(int z=0; z<t_num; z++)
    {
        outfile<<t[z].table_name<<" "<<t[z].attribute_num<<" "<<t[z].tuple_num<<endl;
        for(int i=0; i<t[z].attribute_num; i++)
        {
            outfile<<t[z].attribute_name[i]<<"   ";
        }
        outfile<<endl;
        for(int i=0; i<t[z].tuple_num; i++)
        {
            for(int j=0; j<t[z].attribute_num; j++)
            {
                outfile<<t[z].table_data[i][j]<<"   ";
            }
            outfile<<endl;
        }
        outfile<<endl;
    }
    outfile.close();
}

void create_index(char *sentence,Table *&t,int &t_num,Index *&in,int i_num)
{


    ofstream outfile;
    outfile.open("index.txt");
    if(!outfile)
    {
        cerr<<"open error!"<<endl;
        exit(1);
    }
    outfile.close();
}
///    create view stt as (select * from st);
void create_view(char *sentence,Table *&t,int &t_num,View *&vi,int v_num)
{

    istringstream ss(sentence);
    string tmp;
    ss>>tmp;//create
    ss>>tmp;//view
    ss>>tmp;//stt
    for(int i=0; i<v_num; i++)
    {
        if(tmp==vi[i].vname)
        {
            cout<<"����ͼ�Ѵ��ڣ����ؽ���ͼ��"<<endl;
            exit(1);
            return;
        }
    }
    vi[v_num].vname=tmp;
    ss>>tmp;//as
    ss>>tmp;
    while(tmp[tmp.length()-1]!=';'){
        vi[v_num].sql=vi[v_num].sql+" "+tmp;
        ss>>tmp;
    }
    ss>>tmp;
    vi[v_num].sql=vi[v_num].sql+" "+tmp;

    vi[v_num].sql=vi[v_num].sql.substr(2,vi[v_num].sql.length()-4);
    vi[v_num].sql=vi[v_num].sql+";";
    cout<<vi[v_num].sql<<endl;
    char *tmp1=(char*)vi[v_num].sql.c_str();
    select_table(tmp1,t,t_num,1);
    cout<<"��ͼ�����ɹ���"<<endl;

}
#endif // CREATE_H_INCLUDED
