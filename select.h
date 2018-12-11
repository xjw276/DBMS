#ifndef SELECT_H_INCLUDED
#define SELECT_H_INCLUDED

///"select * from st;";
///"select sname from st where sno='11';";
///select sname,sno from st;
/// select sno,score from st,grade where st.sno=grade.sno;
/// select count(sno) from st group by class having count(sno)>1;
///select * from st where sno='02' order by sno desc;
void join_query(string sql,Table *&t,int t_num,Table &t1)
{
    char *tmp=(char*)sql.c_str();
    string table1;
    string table2;
    string att1;
    string att2;
    int  a1;
    int a2;
    string token=strtok(tmp,".");
    table1=token;
    token=strtok(NULL,"=");
    att1=token;
    token=strtok(NULL,".");
    table2=token;
    token=strtok(NULL,".");
    att2=token;
    if(att1==att2)
    {
        cout<<"属性连接错误。"<<endl;
        return;
    }
//    for(int i=0; i<t_num; i++)
//    {
//         if(t[i].table_name==table1){
//            t[i].foreigntable
//         }
//
//    }
    int len=-1;
    for(int i=0; i<t_num; i++)
    {
        if(t[i].table_name==table1)
        {
            for(int j=0; j<t[i].attribute_num; j++)
            {
                if(t[i].attribute_name[j]==att1)
                {
                    a1=j;
                }
                t1.attribute_name[j]=t[i].attribute_name[j];
                for(int z=0; z<t[i].tuple_num; z++)
                {
                    t1.table_data[z][j]=t[i].table_data[z][j];
                }
            }

            t1.attribute_num=t[i].attribute_num;
            t1.tuple_num=t[i].tuple_num;
            len=t[i].attribute_num;
        }
        if(t[i].table_name==table2)
        {
            for(int j=0; j<t[i].attribute_num; j++)
            {
                if(t[i].attribute_name[j]==att1)
                {
                    a2=j;
                }
                t1.attribute_name[t1.attribute_num+j]=t[i].attribute_name[j];
                for(int x=0; x<t1.tuple_num; x++)
                {
                    for(int z=0; z<t[i].tuple_num; z++)
                    {
                        if(t[i].table_data[z][a2]==t1.table_data[x][a1])
                        {
                            t1.table_data[x][t1.attribute_num+j]=t[i].table_data[z][j];
                        }
                    }
                }
            }
            t1.attribute_num+=t[i].attribute_num;
        }
    }
    for(int i=a2+len; i<t1.attribute_num; i++)
    {
        for(int j=0; j<t1.tuple_num; j++)
        {
            t1.table_data[j][i]=t1.table_data[j][i+1];
        }
    }

    t1.attribute_num--;


}
void select_print(Table *t,int z,int sit,string *select_att,string s,string value)
{
    if(sit==1)
    {
        for(int i=0; i<t[z].attribute_num; i++)
        {
            cout<<t[z].attribute_name[i]<<"   ";
        }
        cout<<endl;
        for(int i=0; i<t[z].tuple_num; i++)
        {
            for(int j=0; j<t[z].attribute_num; j++)
            {
                if(s!="")
                {
                    if(t[z].attribute_name[j]==s&&t[z].table_data[i][j]==value)
                    {
                        cout<<t[z].table_data[i][j]<<"   ";
                    }
                }
                else
                {
                    cout<<t[z].table_data[i][j]<<"   ";
                }

            }
            cout<<endl;
        }
    }
    else
    {
        int len=sizeof( select_att ) / sizeof( select_att[0] );
        for(int i=0; i<=len; i++)
        {
            cout<<select_att[i]<<"   ";
        }
        cout<<endl;

        int m=-1;
        for(int n=0; n<t[z].tuple_num; n++)
        {
            for(int j=0; j<t[z].attribute_num; j++)
            {
                if(s!="")
                {
                    if(t[z].attribute_name[j]==s&&t[z].table_data[n][j]==value)
                    {
                        m=n;
                    }
                }
                else
                {
                    m=n;
                }

                for(int i=0; i<len; i++)
                {
                    if(select_att[i]==t[z].attribute_name[j])
                    {
                        if(t[z].table_data[m][j]!="")
                            cout<<t[z].table_data[m][j]<<"   ";
                    }
                }
            }
            if(m!=-1)
            {
                cout<<endl;
            }
        }
        if(m==-1)
        {
            cout<<"没有符合条件的结果。"<<endl;
            return;
        }
        cout<<endl;
    }
}
void view_select_print(Table *t,int z,int sit,string *select_att,string s,string value)
{
    ofstream outfile;
    outfile.open("view.txt");
    if(!outfile)
    {
        cerr<<"open error!"<<endl;
        exit(1);
    }

    if(sit==1)
    {

        for(int i=0; i<t[z].attribute_num; i++)
        {
            outfile<<t[z].attribute_name[i]<<"   ";
        }
        outfile<<endl;
        for(int i=0; i<t[z].tuple_num; i++)
        {
            for(int j=0; j<t[z].attribute_num; j++)
            {
                if(s!="")
                {
                    if(t[z].attribute_name[j]==s&&t[z].table_data[i][j]==value)
                    {
                        outfile<<t[z].table_data[i][j]<<"   ";
                    }
                }
                else
                {
                    outfile<<t[z].table_data[i][j]<<"   ";
                }

            }
            outfile<<endl;
        }
    }
    else
    {
        int len=sizeof( select_att ) / sizeof( select_att[0] );
        for(int i=0; i<=len; i++)
        {
            outfile<<select_att[i]<<"   ";
        }
        outfile<<endl;

        int m=-1;
        for(int n=0; n<t[z].tuple_num; n++)
        {
            for(int j=0; j<t[z].attribute_num; j++)
            {
                if(s!="")
                {
                    if(t[z].attribute_name[j]==s&&t[z].table_data[n][j]==value)
                    {
                        m=n;
                    }
                }
                else
                {
                    m=n;
                }

                for(int i=0; i<len; i++)
                {
                    if(select_att[i]==t[z].attribute_name[j])
                    {
                        if(t[z].table_data[m][j]!="")
                            outfile<<t[z].table_data[m][j]<<"   ";
                    }
                }
            }
            if(m!=-1)
            {
                outfile<<endl;
            }
        }
        if(m==-1)
        {
            cout<<"没有符合条件的结果。"<<endl;
            return;
        }
        outfile<<endl;
    }
    outfile.close();
}
int find_table(Table *t,int t_num,string *tt,int mCount)
{
    int p=-1;
    for(int i=0; i<t_num; i++)
    {
        if(t[i].table_name==tt[mCount])
        {
            p=i;
            break;
        }
    }
    return p;
}
void select_table(char *sql,Table *&t,int t_num,int if_view)
{

    string tmp;
    istringstream ss(sql);
    ss>>tmp;//select
    ss>>tmp;//sname 查询的属性
    //  int select_att[100];//记录查询属性的下标
    int sit=0;//sit如果为1，则表示查找的是全部属性
    string select_att[100];
    if(tmp=="*")
    {
        sit=1;
    }
    else
    {
        //查找string中是否有，有的话，就分开，没有的话，就遍历，记录下下标。
        int nCount = count(tmp.begin(), tmp.end(), ',');
        if(nCount==0)
        {
            select_att[0]=tmp;
        }
        else
        {
            char *tmp1=(char*)tmp.c_str();
            string token=strtok(tmp1,",");
            for(int i=0; i<nCount; i++)
            {
                select_att[i]=token;
                token=strtok(NULL,",");
            }
            select_att[nCount]=token;
        }
    }

    ss>>tmp;//from
    if(tmp!="FROM"&&tmp!="from")
    {
        cout<<"from或者FROM输入错误，请检查后重新输入。"<<endl;
        return;
    }
    //st;\st,grade\st
    ss>>tmp;
    int mCount= count(tmp.begin(), tmp.end(), ',');
    string tt[100];//记录表名
    int w;//用来标记查询表所在的位置下标
    int ww[100];//得到各表的下标
    if(tmp[tmp.length()-1]==';'&&mCount==0)
    {
        tmp=tmp.substr(0,tmp.length()-1);
        int c=0;
        tt[0]=tmp;
        cout<<tt[0]<<endl;
        w=find_table(t,t_num,tt,0);
        if(w==-1)
        {
            cout<<"该表不存在，请检查后重新输入。"<<endl;
            return;
        }
        if(if_view==0)
        {
            select_print(t,w,sit,select_att,"","");
        }
        else if(if_view==1)
        {
            view_select_print(t,w,sit,select_att,"","");
        }

        return;

    }
    else if(mCount!=0)
    {
        char *tmp2=(char*)tmp.c_str();
        string tokenptr=strtok(tmp2,",");
        for(int i=0; i<mCount; i++)
        {
            tt[i]=tokenptr;
            tokenptr=strtok(NULL,",");
        }
        tt[mCount]=tokenptr;

        for(int i=0; i<=mCount; i++)
        {
            ww[i]=find_table(t,t_num,tt,i);
            if(ww[i]==-1)
            {
                cout<<"该表不存在，请检查后重新输入。"<<endl;
                return;
            }
        }
    }
    else
    {
        tt[0]=tmp;
        w=find_table(t,t_num,tt,0);
        if(w==-1)
        {
            cout<<"该表不存在，请检查后重新输入。"<<endl;
            return;
        }
    }
//以上得到了查找表的位置
//where\group\order
    ss>>tmp;
    if(tmp=="where"||tmp=="WHERE")
    {
        // sno='11';
        ss>>tmp;
//调用连接查询函数 st.sno=grade.sno
        if(count(tmp.begin(),tmp.end(),'.')!=0)
        {
            Table *t1=new Table[4]();
            if(tmp[tmp.length()-1]==';')
            {
                tmp=tmp.substr(0,tmp.length()-2);

                join_query(tmp,t,t_num,t1[0]);

                if(if_view==0)
                {
                    select_print(t1,0,sit,select_att,"","");
                }
                else if(if_view==1)
                {
                    view_select_print(t1,0,sit,select_att,"","");
                }
                return;
            }
            else
            {
                join_query(tmp,t,t_num,t1[0]);
            }
        }
        int y=-1;//记录条件中属性的位置下标
        int z=0;//标记属性类型是否为int
        char *tmp3=(char*)tmp.c_str();
        string tokenp=strtok(tmp3,"=");
        for(int i=0; i<t[w].attribute_num; i++)
        {
            if(t[w].attribute_name[i]==tokenp)
            {
                if(t[w].attribute_type[i]=="int")
                    z=1;
                y=i;
                break;
            }
        }
        if(y==-1)
        {
            cout<<"更新条件中的属性不存在，请检查后重新输入。"<<endl;
            return;
        }
        tokenp=strtok(NULL,"=");
        if(tokenp[0]=='\''&&z!=0)
        {
            cout<<"查询条件的属性数据类型错误，不应加单引号，请检查后重新输入。"<<endl;
            return;
        }
        if(tokenp[0]!='\''&&z==0)
        {
            cout<<"查询条件的属性数据类型错误，应加单引号，请检查后重新输入。"<<endl;
            return;
        }
        if(z==0)
        {
            if(tokenp[tokenp.length()-1]==';')
            {
                tokenp=tokenp.substr(1,tokenp.length()-3);
                string old_data;
                old_data=tokenp;
                if(if_view==0)
                {
                    select_print(t,w,sit,select_att,t[w].attribute_name[y],old_data);
                }
                else if(if_view==1)
                {
                    select_print(t,w,sit,select_att,t[w].attribute_name[y],old_data);
                }
                return;
            }
            else
            {
                tokenp=tokenp.substr(1,tokenp.length()-2);
            }
        }
        string data="";
        data=tokenp;
        if(if_view==0)
        {
            select_print(t,w,sit,select_att,t[w].attribute_name[y],data);
        }
        else if(if_view==1)
        {
            select_print(t,w,sit,select_att,t[w].attribute_name[y],data);
        }
        return;
    }
    else if(tmp=="order"||tmp=="ORDER")
    {
        ss>>tmp;//by
        ss>>tmp;//sno
        int stand=-1;
        Table *t2=new Table[2]();
        for(int j=0; j<t[w].attribute_num; j++)
        {
            t2[0].attribute_name[j]=t[w].attribute_name[j];
            if(tmp==t[w].attribute_name[j])
            {
                stand=j;
            }
            for(int i=0; i<t[w].tuple_num; i++)
            {
                t2[0].table_data[i][j]=t[w].table_data[i][j];
            }
        }
        t2[0].attribute_num=t[w].attribute_num;
        t2[0].tuple_num=t[w].tuple_num;
        ss>>tmp;//desc;\asc;
        string temp;
        int ss[100];
        int temp1;

        for(int i=0; i<t[w].tuple_num; i++)
        {
            ss[i]=i;
        }
        if(tmp=="desc;"||tmp=="DESC;")
        {
            for(int i=0; i<t[w].tuple_num; i++)
            {
                for(int j=i+1; j<t[w].tuple_num; j++)
                {
                    if (t2[0].table_data[i][stand] < t2[0].table_data[j][stand])
                    {
                        temp = t2[0].table_data[i][stand];
                        t2[0].table_data[i][stand] = t2[0].table_data[j][stand];
                        t2[0].table_data[j][stand] = temp;

                        temp1=ss[i];
                        ss[i]=ss[j];
                        ss[j]=temp1;
                    }
                }
            }

        }
        else if(tmp=="asc;"||tmp=="ASC;")
        {
            for(int i=0; i<t[w].tuple_num; i++)
            {
                for(int j=i+1; j<t[w].tuple_num; j++)
                {
                    if (t2[0].table_data[i][stand] > t2[0].table_data[j][stand])
                    {
                        temp = t2[0].table_data[i][stand];
                        t2[0].table_data[i][stand] = t2[0].table_data[j][stand];
                        t2[0].table_data[j][stand] = temp;

                        temp1=ss[i];
                        ss[i]=ss[j];
                        ss[j]=temp1;
                    }
                }
            }

        }
        for(int j=0; j<t[w].attribute_num; j++)
        {
            for(int i=0; i<t[w].tuple_num; i++)
            {
                int y=ss[i];
                t2[0].table_data[i][j]=t[w].table_data[y][j];
            }
        }
        if(if_view==0)
        select_print(t2,0,sit,select_att,"","");
        else if(if_view==1){
                 select_print(t2,0,sit,select_att,"","");
        }
        return;
    }
    else if(tmp=="group"||tmp=="GROUP")
    {

    }
    else
    {

    }








}








#endif // SELECT_H_INCLUDED
