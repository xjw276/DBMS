#ifndef CREATE_H_INCLUDED
#define CREATE_H_INCLUDED
#include "select.h"
void create_table(char *sentence,Table *&t,int &t_num)
{
    ///得到初步属性个数（通过有几个“，”来初步判断有几个属性，当然其中可能包含完整性约束）
    int len=strlen(sentence);
    for(int i=0; i<len; i++)
    {
        if(sentence[i]==',')
        {
            t[t_num].attribute_num++;
        }
    }
    t[t_num].attribute_num++;

    ///建立行列表，即读一个逗号，就为一个属性行，包含了约束等行（使用strtok来读取语句）
    string attribute[100];
    string tokenPtr=strtok(sentence," ");
    tokenPtr=strtok(NULL," ");
    tokenPtr=strtok(NULL,"(");
    ///表名重复性检查,看表是否存在。若不存在则建立新表，若存在返回上一步
    for(int i=0; i<t_num; i++)
    {
        if(tokenPtr==t[i].table_name)
        {
            cout<<"该表已存在，请重建表。"<<endl;
            //exit(1);
            return;
        }
    }
    t[t_num].table_name=tokenPtr;	//新表表名
    //table_name = atoi(tokenPtr);
    ///得到初步输入的属性行信息，并存入列表中。并检查输入 格式的正确性
    int count=0;
    while(tokenPtr.size()!=0&&count<t[t_num].attribute_num)
    {

        tokenPtr=strtok(NULL,",");

        if(count== t[t_num].attribute_num-1)
        {
            int len1=tokenPtr.length();
            if(tokenPtr[len1-1]!=';'||(tokenPtr[len1-2]==')'&&tokenPtr[len1-3]=='(')||(tokenPtr[len1-2]==')'&&tokenPtr[len1-3]<'9'&&tokenPtr[len1-3]>'0')||(tokenPtr[len1-2]==')'&&tokenPtr[len1-3]<'Z'&&tokenPtr[len1-3]>'A'))
            {
                cout<<"输入格式有误!"<<endl;
            }

            attribute[count]=tokenPtr.erase(len1-2);

        }
        else
            attribute[count]=tokenPtr;
        count++;
    }

    int p=0;//各个约束性键的个数
    int f=0;
    int n=0;
    int u=0;
///从列表中提取有关信息
    for(int i=0; i<count; i++)
    {
        //将列表中的非有用的符号替换为空格
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
        ss>>tmp;//每行第一个字符串

        if(tmp=="primary")
        {
            string mn;
            ss>>mn;
            ss>>mn;//主键名

            for(int j=0; j<i; j++)
            {
                if(t[t_num].attribute_name[j]==mn)
                {
                    t[t_num].prikey[p]=j;
                    p++;
                }
            }

            t[t_num].attribute_num--;//非属性
        }
        else if(tmp=="foreign")
        {
            string mn;
            ss>>mn;
            ss>>mn;//外键名
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
            t[t_num].attribute_num--;//非属性
            f++;
        }
        else
        {
            t[t_num].attribute_name[i]=tmp;
            string mn;
            ss>>mn;
            t[t_num].attribute_type[i]=mn;
            //cout<<t.attribute_name[i]<<"每行第一个字符串"<<t.attribute_type[i]<<endl;
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
    cout<<t[t_num-1].table_name<<"表创建成功！"<<endl;

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
            cout<<"该视图已存在，请重建视图。"<<endl;
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
    cout<<"视图创建成功。"<<endl;

}
#endif // CREATE_H_INCLUDED
