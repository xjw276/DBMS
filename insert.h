#ifndef INSERT_H_INCLUDED
#define INSERT_H_INCLUDED

void insert_table(char *sentence, Table *&t,int t_num)
{
    //语句格式检查
    int j=0;//用于找(所在的位置,是(的下标
    int j1=0;
    int j2=0;
    if(sentence[strlen(sentence)-1]!=';'||sentence[strlen(sentence)-2]!=')')
    {
        cout<<"插入语句格式出错，请重新输入111"<<endl;
        return;
    }
    else
    {
        sentence[strlen(sentence)-2]='\0';
    }
    for(int i=strlen(sentence)-3; i>0; i--)
    {
        if(sentence[i]=='('||sentence[i]==')'||sentence[i]==' '||(sentence[i]<='z'&&sentence[i]>='a')||(sentence[i]<='Z'&&sentence[i]>='A')||sentence[i]==','||(sentence[i]<='9'&&sentence[i]>='0'))
        {
            if(sentence[i]=='('&&j==0)
            {
                j=i;
                sentence[i]=' ';
            }
            else if(sentence[i]==')'&&j!=0)
            {
                j1=i;
                sentence[i]=' ';
            }
            if(sentence[i]=='('&&j1!=0)
            {
                j2=i;
                sentence[i]=' ';
                break;
            }
        }
        else
        {
            cout<<i<<"插入语句格式出错，请重新输入2222"<<endl;

            return;
        }
    }
    for(int i=strlen(sentence)-3; i>j; i--)
    {
        if(sentence[j-1]==' ')
        {
            cout<<"索引语句格式出错，请重新输入3333222"<<endl;
            return;
        }
        if((sentence[i]<='z'&&sentence[i]>='a')||(sentence[i]<='Z'&&sentence[i]>='A')||sentence[i]==','||(sentence[i]<='9'&&sentence[i]>='0'))
        {
            continue;
        }
        else
        {
            cout<<"索引语句格式出错，请重新输入3333"<<endl;
            return;
        }

    }
    for(int i=0; i<j2; i++)
    {
        if(sentence[i]=='(')
        {
            cout<<"索引语句格式出错，请重新输入4444"<<endl;
            return;
        }
    }

    int tt=-1;//记录插入的表的下标
    int count=0;//记录遍历了几个表
    string tmp;
    istringstream ss(sentence);
    ss>>tmp;//insert
    ss>>tmp;//into
    ss>>tmp;//table_name
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
    if(j2!=0)
    {
        ss>>tmp;
        char *tmp1=(char*)tmp.c_str();
        int co[100];
        int count=0;
        for(int i=0; i<strlen(tmp1); i++)
        {
            if(tmp1[i]==',')
            {
                count++;
            }
        }
        count++;
        string tokenPtr=strtok(tmp1,",");

        for(int i=0; i<count-1; i++)
        {
            for(int j=0; j<t[tt].attribute_num; j++)
            {
                if(tokenPtr==t[tt].attribute_name[j])
                {
                    co[i]=j;
                }

            }
            tokenPtr=strtok(NULL,",");
        }

        for(int j=0; j<t[tt].attribute_num; j++)
        {
            if(tokenPtr==t[tt].attribute_name[j])
                co[count]=j;
        }
        ss>>tmp;//value
        ss>>tmp;
        char *tmp2=(char*)tmp.c_str();
        string token=strtok(tmp2,",");

        for(int i=0; i<count-1; i++)
        {
            t[tt].table_data[t[tt].tuple_num][co[i]]=token;
            token=strtok(NULL,",");
        }
        t[tt].table_data[t[tt].tuple_num][co[count]]=token;

    }
    else
    {
        ss>>tmp;//value
        ss>>tmp;
        char *ttmp=(char*)tmp.c_str();
        string tokenPtr=strtok(ttmp,",");
        for(int i=0; i<t[tt].attribute_num-1; i++)
        {
            //cout<<tokenPtr<<endl;
            t[tt].table_data[t[tt].tuple_num][i]=tokenPtr;
            tokenPtr=strtok(NULL,",");
        }
        //cout<<tokenPtr<<endl;
        t[tt].table_data[t[tt].tuple_num][t[tt].attribute_num-1]=tokenPtr;
    }
    t[tt].tuple_num++;


    cout<<"插入成功！"<<endl;

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
        outfile<<"char类型的长度"<<t[z].attribute_length<<endl;

        for(int i=0; i<100; i++)
        {
            outfile<<"primary_key"<< t[z].prikey[i]<<" ";
        }
        outfile<<endl;
         for(int i=0; i<100; i++)
        {
        outfile<<"foreign_key"<<t[z].forkey[i]<<" ";
        }
        outfile<<endl;
        for(int i=0; i<100; i++)
        {
            outfile<<"unique_key"<<t[z].unikey[i]<<" ";
        }
        outfile<<endl;
        for(int i=0; i<100; i++)
        {
            outfile<<"not_null_key"<<t[z].notnull[i]<<" ";
        }
        outfile<<endl;
        for(int i=0; i<100; i++)
        {
            outfile<<"foreign_table"<<t[z].foreigntable[i]<<" ";
        }
        outfile<<endl;
        for(int i=0; i<100; i++)
        {
            outfile<<"foreign_table_key"<<t[z].foreign[i]<<" ";
        }
        outfile<<endl;
    }
    outfile.close();

}

#endif // INSERT_H_INCLUDED
