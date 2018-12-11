#ifndef DELETE_H_INCLUDED
#define DELETE_H_INCLUDED

///delete from st where sno='02';
///delete from stt;
void delete_table(char* sql,Table *&t,int t_num)
{
    string tmp;
    istringstream ss(sql);
    ss>>tmp;//delete
    ss>>tmp;//from
    ss>>tmp;
    int tt=0;//用来标记更新表所在的位置下标
    int count=0;
    int situation=0;
    if(tmp[tmp.length()-1]==';')
    {
        tmp=tmp.substr(0,tmp.length()-1);
        situation=1;
    }
    //cout<<tmp<<endl;
    for(int i=0; i<t_num; i++)
    {
        if(t[i].table_name==tmp)
        {
            tt=i;
            break;
        }
        else
        {
            count++;
        }
    }
    if(count==t_num)
    {
        cout<<"该表不存在，请检查后重新输入。"<<endl;
        return;
    }

    if(situation==1)
    {
        for(int i=0; i<t[tt].tuple_num; i++)
        {
            for(int j=0; j<t[tt].attribute_num; j++)
            {
                t[tt].table_data[i][j]="";
            }
        }
        cout<<"ok"<<endl;
    }
    ///delete from st where sno='02' and sname="tom";
    ///delete from st where sno='02' or sno="01";
    ///delete from st where between sno='02' and sno="01";
    ///delete from st where sno in(select sno from st where sno="10");
    else
    {
        ss>>tmp;
        if(tmp!="where"&&tmp!="WHERE")
        {
            cout<<"WHERE或where拼写错误，请检查后重新输入。"<<endl;
            return;
        }
        ss>>tmp;
        int And=0;
        int Or=0;
        int q=0;
        int y=-1;
        string delete_data[3];

        while(tmp[tmp.length()-1]!=';') //sno='02';
        {
            // cout<<"测试"<<endl;
            if(tmp=="and")
            {
                And=1;
                ss>>tmp;
                continue;
            }
            else if(tmp=="or")
            {
                Or=1;
                ss>>tmp;
                continue;
            }
            else
            {
                int z=0;//标记是否为int类型
                char *tmp1=(char*)tmp.c_str();
                string token=strtok(tmp1,"=");

                for(int i=0; i<t[tt].attribute_num; i++)
                {
                    if(t[tt].attribute_name[i]==token)
                    {
                        if(t[tt].attribute_type[i]=="int")
                            z=1;
                        y=i;
                        break;
                    }
                }
                if(y==-1)
                {
                    cout<<"删除条件中的属性不存在，请检查后重新输入。"<<endl;
                    return;
                }

                token=strtok(NULL,"=");
                if(token[0]=='\''&&z!=0)
                {
                    cout<<"删除的属性数据类型错误，不应加单引号，请检查后重新输入。"<<endl;
                    return;
                }
                if(token[0]!='\''&&z==0)
                {
                    cout<<"删除的属性数据类型错误，应加单引号，请检查后重新输入。"<<endl;
                    return;
                }
                if(z==0)
                {
                    if(tmp[tmp.length()-1]==';')
                    {
                        token=token.substr(1,token.length()-3);
                    }
                    else
                        token=token.substr(1,token.length()-2);
                }

                delete_data[q]=token;
                q++;
                ss>>tmp;
            }
        }
        int n=-1;
        count=0;
        string g[10];
        int h=0;
        for(int i=0; i<t[tt].tuple_num; i++)
        {
            for(int p=0; p<q; p++)
            {

                if(t[tt].table_data[i][y]==delete_data[p])
                {
                    g[h]=i;
                    h++;
                }
            }
        }
        if(h==0)
        {
            cout<<"删除的数据不存在，请检查后重新输入。"<<endl;
            return;
        }
        int m=-1;
        for(int i=0; i<t[tt].tuple_num; i++)
        {
            for(int j=0; j<t[tt].attribute_num; j++)
            {
                if(And==1)
                {
                    if(t[tt].table_data[i][j]==g[0]&&t[tt].table_data[i][j]==g[1])
                    {
                        t[tt].table_data[i][j]="";
                        n=i;
                    }

                }
                else if(Or==1)
                {
                    if(t[tt].table_data[i][j]==g[0])
                    {
                        t[tt].table_data[i][j]="";
                        n=i;
                    }
                    if(t[tt].table_data[i][j]==g[1])
                    {
                        t[tt].table_data[i][j]="";
                        m=i;
                    }
                }
                else
                {
                    if(t[tt].table_data[i][j]==g[0])
                    {
                        t[tt].table_data[i][j]="";
                        n=i;
                    }
                }
                //t[tt].table_data[i][j]=t[tt].table_data[i+1][j];
            }
            // t[tt].tuple_num--;
            break;
        }
        for(int i=n; i<t[tt].tuple_num; i++)
        {
            for(int j=0; j<t[tt].attribute_num; j++)
            {
                t[tt].table_data[i][j]=t[tt].table_data[i+1][j];
            }
        }
        if(m>-1)
        {
            for(int i=m; i<t[tt].tuple_num; i++)
            {
                for(int j=0; j<t[tt].attribute_num; j++)
                {
                    t[tt].table_data[i][j]=t[tt].table_data[i+1][j];
                }
            }

        }
        t[tt].tuple_num--;

        cout<<"删除成功！"<<endl;
    }

}
#endif // DELETE_H_INCLUDED
