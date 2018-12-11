#include <bits/stdc++.h>
#include "userlogin.h"
#include "class.h"
#include "create.h"
#include "insert.h"
#include "update.h"
#include "delete.h"
#include "select.h"
#include "grant.h"
#include "revoke.h"
#include "help.h"
using namespace std;

int main()
{
    string name;
    string password;
    cout << "�������û�����   ";
    User *user = new User[20]();
    int ok;
    int Count = 0;
    while(cin >> name)
    {

        cout << "���������룺   ";
        cin >> password;
        ok = login(user,name,password,Count);
        if(ok != -1)
        {
            break;
        }
        cout << "�������û�����   ";
    }
    cout << endl;

    //  cout<<Count;
    Table  *t = new Table[100]();
    Index *in = new Index[100]();
    View  *vi = new View[100]();
    int t_num = 0;
    int i_num = 0;
    int v_num = 0;
    ifstream fin;
    fin.open("table.txt",ios_base::in);
    if(fin.fail())
    {
        cout<<"���ļ�ʧ��"<<endl;
    }
    int q=0;
    while(fin>>t[q].table_name>>t[q].attribute_num>>t[q].tuple_num)
    {
        //  cout<<t[q].table_name<<endl;
        for(int i=0; i<t[q].attribute_num; i++)
        {
            fin>>t[q].attribute_name[i];
        }
        for(int j=0; j<t[q].tuple_num; j++)
        {

            for(int i=0; i<t[q].attribute_num; i++)
            {
                fin>>t[q].table_data[j][i];
            }
        }
        string r;
        fin>>r>>t[q].attribute_length;

        for(int i=0; i<100; i++)
        {
            fin>>r>>t[q].prikey[i];
        }
        for(int i=0; i<100; i++)
        {
            fin>>r>>t[q].forkey[i];
        }
        for(int i=0; i<100; i++)
        {
            fin>>r>>t[q].unikey[i];
        }
        for(int i=0; i<100; i++)
        {
            fin>>r>>t[q].notnull[i];
        }
        for(int i=0; i<100; i++)
        {
            fin>>r>>t[q].foreigntable[i];
        }
        for(int i=0; i<100; i++)
        {
            fin>>r>>t[q].foreign[i];
        }
        q++;
    }
    t_num=q;

    if(ok==0)
    {
        cout<<"��ӭ��������Ա�û���"<<endl;
        cout<<"������sql��䣺"<<endl;
        char sql[1000];
//        ifstream fin;
//        fin.open("����.txt",ios_base::in);
//        if(fin.fail())
//        {
//            cout<<"���ļ�ʧ��"<<endl;
//        }
//        while(fin.getline(sql,sizeof(sql)))
        while(1)
        {
            gets(sql);
            string tmp;
            istringstream split_sql(sql);
            split_sql >> tmp;
            if(tmp == "create"||tmp == "CREATE")
            {
                split_sql>>tmp;
                if(tmp == "table" || tmp == "TABLE")
                    create_table(sql,t,t_num);
                else if(tmp == "view" || tmp == "VIEW"){
                    create_view(sql,t,t_num,vi,v_num);
                }
                else{
                    cout << "create��������������������" << endl;
                    continue;
                }
            }
            else if(tmp == "insert"||tmp == "INSERT")
            {
                insert_table(sql,t,t_num);
            }
            else if(tmp=="update"||tmp=="UPDATE")
            {
                update_table(sql,t,t_num);
            }
            else if(tmp=="delete"||tmp=="DELETE")
            {
                delete_table(sql,t,t_num);
            }
            else if(tmp=="grant"||tmp=="GRANT")
            {
                grant_access(sql,t,t_num,ok,user,Count);
            }
            else if(tmp=="revoke"||tmp=="REVOKE")
            {
                grant_access(sql,t,t_num,ok,user,Count);
            }
            else if(tmp=="help"||tmp=="HELP"){
                help(sql,t,t_num,in,i_num,vi,v_num);
            }
            else if(tmp=="select"||tmp=="SELECT"){
                 select_table(sql,t,t_num,0);
            }
            else
                cout << "sql��������������������" << endl;
        }

    }
    else
    {
        cout<<"���Ĳ���Ȩ���У�";
        ifstream fi;
        fi.open("user.txt",ios_base::in);
        if(fi.fail())
        {
            cout<<"���ļ�ʧ��"<<endl;
        }
        User u;
        while(fi>>u.name>>u.password>>u.access_insert>>u.access_update>>u.access_select>>u.access_delete)
        {
            if(u.name==user[ok].name)
            {
                if(u.access_insert==1)
                    cout<<"  ����";
                if(u.access_select==1)
                    cout<<"  ��ѯ";
                if(u.access_update==1)
                    cout<<"  ����";
                if(u.access_delete==1)
                    cout<<"  ɾ��";
            }
        }
        fi.close();
        cout<<endl;


        cout<<"������sql��䣺"<<endl;
        char sql[1024]= {0};
        while(1)
        {
            gets(sql);
            string tmp;
            istringstream split_sql(sql);
            split_sql>>tmp;

            if(tmp=="create"||tmp=="CREATE")
            {
                cout<<"��û��create��Ȩ�ޡ�"<<endl;
            }
            else if(tmp=="insert"||tmp=="INSERT")
            {
                if(user[ok].access_insert==1)
                    insert_table(sql,t,t_num);
                else
                    cout<<"��û��insert��Ȩ�ޡ�"<<endl;
            }
            else if(tmp=="update"||tmp=="UPDATE")
            {
                if(user[ok].access_update==1)
                    update_table(sql,t,t_num);
                else
                    cout<<"��û��update��Ȩ�ޡ�"<<endl;

            }
            else if(tmp=="delete"||tmp=="DELETE")
            {
                if(user[ok].access_delete==1)
                    delete_table(sql,t,t_num);
                else
                    cout<<"��û��delete��Ȩ�ޡ�"<<endl;
            }
            else if(tmp=="grant"||tmp=="GRANT")
            {
                cout<<"��û��grant��Ȩ�ޡ�"<<endl;
            }
            else if(tmp=="revoke"||tmp=="REVOKE")
            {
                cout<<"��û��revoke��Ȩ�ޡ�"<<endl;
            }
        }
    }
    return 0;
}
