#ifndef USERLOGIN_H_INCLUDED
#define USERLOGIN_H_INCLUDED
#define USER_NUM 50
#include <string.h>
#include<iostream>
#include <fstream>

using namespace std;
//定义用户权限
class User
{
public:
    //用户
    string name;
    string password;
    //权限
    //值为1，则有该权限，值为0，则无该权限
    int access_insert;
    int access_select;
    int access_delete;
    int access_update;
    //Access user_access;
    User()
    {
        access_insert=0;
        access_select=0;
        access_delete=0;
        access_update=0;
    }
    User(string _name ,string _password)
    {
        name=_name;
        password=_password;
        access_insert=0;
        access_select=0;
        access_delete=0;
        access_update=0;
    }


} ;

int login(User *&u,string name ,string password,int &count1)
{
    int ok=-1;
    ifstream fin;
    fin.open("user.txt",ios_base::in);
    if(fin.fail())
    {
        cout<<"打开文件失败"<<endl;
        return ok;
    }
    User user;
    count1=0;
    int count2=0;
    while(fin>>user.name>>user.password>>user.access_insert>>user.access_update>>user.access_select>>user.access_delete)
    {
        if(user.name==name)
        {
            if(user.password==password&&user.name=="admin")
            {
                cout<<"超级管理员登陆成功！"<<endl;

                ok=count1;
            }
            else if(user.password==password&&user.name!="admin")
            {
                cout<<"普通用户登陆成功！"<<endl;
                ok=count1;

            }
            else
            {
                cout<<"密码错误！"<<endl;
            }
        }
        else
        {
            count2++;
        }
        u[count1].name=user.name;
        u[count1].password=user.password;
        u[count1].access_delete=user.access_delete;
        u[count1].access_insert=user.access_insert;
        u[count1].access_select=user.access_select;
        u[count1].access_update=user.access_update;
        count1++;
    }
    if(count2==count1)
    {
        cout<<"该用户不存在！"<<endl;

    }
    return ok;

}
#endif // USERLOGIN_H_INCLUDED
