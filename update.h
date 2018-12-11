#ifndef UPDATE_H_INCLUDED
#define UPDATE_H_INCLUDED

void update_table(char *sql,Table *&t,int t_num)
{

    string tmp;
    istringstream ss(sql);
    ss>>tmp;//update
    ss>>tmp;//st
    int tt=0;//������Ǹ��±����ڵ�λ���±�
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
        cout<<"�ñ����ڣ�������������롣"<<endl;
        return;
    }


    ss>>tmp;//set
    if(tmp=="set"||tmp=="SET")
    {
    }
    else
    {
        cout<<"SET��set��������������롣"<<endl;
        return;
    }


    ss>>tmp;//sno='00'
    int z=0;//����Ƿ�Ϊint����
    count=0;
    int x=-1;//��Ǹ��µ�����ֵ���ڵ�λ���±�
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
        cout<<"���µ����Բ����ڣ�������������롣"<<endl;
        return;
    }
    tokenPtr=strtok(NULL,"=");
    if(tokenPtr[0]=='\''&&z!=0)
    {
        cout<<"���µ������������ʹ��󣬲�Ӧ�ӵ����ţ�������������롣"<<endl;
        return;
    }
    if(tokenPtr[0]!='\''&&z==0)
    {
        cout<<"���µ������������ʹ���Ӧ�ӵ����ţ�������������롣"<<endl;
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
        cout<<"WHERE��whereƴд����������������롣"<<endl;
        return;
    }
    ss>>tmp;//sname='wr'
    int y=-1;//��¼���������Ե�λ���±�
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
        cout<<"���������е����Բ����ڣ�������������롣"<<endl;
        return;
    }
    token=strtok(NULL,"=");
    if(token[0]=='\''&&z!=0)
    {
        cout<<"���������������������ʹ��󣬲�Ӧ�ӵ����ţ�������������롣"<<endl;
        return;
    }
    if(token[0]!='\''&&z==0)
    {
        cout<<"���������������������ʹ���Ӧ�ӵ����ţ�������������롣"<<endl;
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
    cout<<"���³ɹ���"<<endl;

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
