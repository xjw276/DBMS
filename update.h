#ifndef UPDATE_H_INCLUDED
#define UPDATE_H_INCLUDED

void update_table(char *sql,Table *&t,int t_num)
{

    string tmp;
    istringstream ss(sql);
    ss>>tmp;//update
    ss>>tmp;//st
    int tt=0;//用来标记更新表所在的位置下标
    int count=0;
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


    ss>>tmp;//set
    if(tmp=="set"||tmp=="SET")
    {
    }
    else
    {
        cout<<"SET或set，请检查后重新输入。"<<endl;
        return;
    }


    ss>>tmp;//sno='00'
    int z=0;//标记是否为int类型
    count=0;
    int x=-1;//标记更新的属性值所在的位置下标
    char *tmp1=(char*)tmp.c_str();
    string tokenPtr=strtok(tmp1,"=");
    for(int i=0; i<t[tt].attribute_num; i++)
    {
        if(t[tt].attribute_name[i]==tokenPtr)
        {
            if(t[tt].attribute_type[i]=="int")
                z=1;
            x=i;
            break;
        }
        else
        {
            count++;
        }
    }
    if(count==t[tt].attribute_num)
    {
        cout<<"更新的属性不存在，请检查后重新输入。"<<endl;
        return;
    }
    tokenPtr=strtok(NULL,"=");
    if(tokenPtr[0]=='\''&&z!=0)
    {
        cout<<"更新的属性数据类型错误，不应加单引号，请检查后重新输入。"<<endl;
        return;
    }
    if(tokenPtr[0]!='\''&&z==0)
    {
        cout<<"更新的属性数据类型错误，应加单引号，请检查后重新输入。"<<endl;
        return;
    }
    if(z==0){
        tokenPtr=tokenPtr.substr(1,tokenPtr.length()-2);
    }
    string update_data;
    update_data=tokenPtr;
    z=0;


    ss>>tmp;//where
    if(tmp!="where"&&tmp!="WHERE")
    {
        cout<<"WHERE或where拼写错误，请检查后重新输入。"<<endl;
        return;
    }
    ss>>tmp;//sname='wr'
    int y=-1;//记录条件中属性的位置下标
    count=0;
    char *tmp2=(char*)tmp.c_str();
    string token=strtok(tmp2,"=");
    for(int i=0; i<t[tt].attribute_num; i++)
    {
        if(t[tt].attribute_name[i]==token)
        {
            if(t[tt].attribute_type[i]=="int")
                z=1;
            y=i;
            break;
        }
        else
        {
            count++;
        }
    }
    if(count==t[tt].attribute_num)
    {
        cout<<"更新条件中的属性不存在，请检查后重新输入。"<<endl;
        return;
    }
    token=strtok(NULL,"=");
    if(token[0]=='\''&&z!=0)
    {
        cout<<"更新条件的属性数据类型错误，不应加单引号，请检查后重新输入。"<<endl;
        return;
    }
    if(token[0]!='\''&&z==0)
    {
        cout<<"更新条件的属性数据类型错误，应加单引号，请检查后重新输入。"<<endl;
        return;
    }
    if(z==0){
        token=token.substr(1,token.length()-3);
    }
    string old_data;
    old_data=token;

    for(int i=0;i<t[tt].tuple_num;i++){
        if(t[tt].table_data[i][y]==old_data){
           t[tt].table_data[i][x]=update_data;
           break;
        }
    }
    cout<<"更新成功！"<<endl;

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


#endif // UPDATE_H_INCLUDED
