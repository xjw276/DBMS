#ifndef GRANT_H_INCLUDED
#define GRANT_H_INCLUDED


/// grant select on st to zly;

/// revoke select on st from zly;

void grant_access(char *sql,Table *t,int t_num,int ok,User *&user,int u_num)
{
    if(ok==0)
    {
        string tmp;
        istringstream ss(sql);
        ss>>tmp;//grant
        ss>>tmp;//操作
        string oper=tmp;
            ss>>tmp;//on
            ss>>tmp;//表名
            int n=-1;
            for(int i=0;i<t_num;i++){
                if(tmp==t[i].table_name){
                    n=i;
                }
            }
            if(n==-1){
                cout<<"没有授予权限的表。"<<endl;
                return;
            }
            ss>>tmp;
            ss>>tmp;//zly;
            tmp=tmp.substr(0,tmp.length()-1);

            int x=-1;
            for(int i=0;i<u_num;i++){
                if(user[i].name==tmp){
                   x=i;
                }
            }
            if(x==-1){

                cout<<"该用户不存在。"<<endl;
                return;
            }
            //赋予用户权限

        if(oper=="select"||oper=="SELECT"){
            user[x].access_select=1;
        }
        else if(oper=="update"||oper=="UPDATE"){
            user[x].access_update=1;
        }
        else if(oper=="insert"||oper=="INSERT"){
            user[x].access_insert=1;
        }
        else if(oper=="delete"||oper=="DELETE")
        {
            user[x].access_delete=1;
        }
        else{
            cout<<"您授权的操作的无效的。"<<endl;
        }

       // ifstream fin;
        //fin.open("u.txt",ios_base::in);


    }
    else
    {
        cout<<"不是管理员，不能进行授权。"<<endl;
        return;

    }
     cout<<"授权成功。"<<endl;
         ofstream outfile;
    outfile.open("user.txt");
    if(!outfile)
    {
        cerr<<"open error!"<<endl;
        exit(1);
    }
    for(int z=0; z<u_num; z++)
    {
        outfile<<user[z].name<<" "<<user[z].password<<" "<<user[z].access_insert<<" "<<user[z].access_update<<" "<<user[z].access_select<<" "<<user[z].access_delete<<endl;

    }
    outfile.close();
}




#endif // GRANT_H_INCLUDED
