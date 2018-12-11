#ifndef HELP_H_INCLUDED
#define HELP_H_INCLUDED

void help(char *sql,Table *t,int t_num,Index *in,int i_num,View *vi,int v_num)
{

    string tmp;
    istringstream ss(sql);
    ss>>tmp;//help
    ss>>tmp;//
    if(tmp=="table"||tmp=="TABLE")
    {
        ss>>tmp;
        int z=0;
        for(int i=0; i<t_num; i++)
        {
            if(t[i].table_name==tmp)
            {
                z=i;
            }
        }
        for(int i=0; i<t[z].attribute_num; i++)
        {
            cout<<t[z].attribute_name[i]<<"   ";
        }
        cout<<endl;
        for(int i=0; i<t[z].tuple_num; i++)
        {
            for(int j=0; j<t[z].attribute_num; j++)
            {
                cout<<t[z].table_data[i][j]<<"   ";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    else if(tmp=="index"||tmp=="INDEX")
    {
        ss>>tmp;

    }
    else if(tmp=="view"||tmp=="VIEW")
    {
        ss>>tmp;
        int p=-1;
        for(int i=0;i<v_num;i++){
            if(tmp==vi[i].vname){
                p=i;
            }
        }
        if(p==-1){
            cout<<"该视图不存在。"<<endl;
            return;
        }
        ifstream fin;
        fin.open("view.txt",ios_base::in);
        if(fin.fail())
        {
            cout<<"打开文件失败"<<endl;
        }
         char s[1024]= {0};
      while( fin.getline(s,sizeof(s))){

           cout<<s<<endl;
       }
       fin.close();

    }
    else if(tmp=="database"||tmp=="DATABASE")
    {
        cout<<"表"<<endl;
        for(int z=0; z<t_num; z++)
        {
            cout<<t[z].table_name<<endl;
            for(int i=0; i<t[z].attribute_num; i++)
            {
                cout<<t[z].attribute_name[i]<<"   ";
            }
            cout<<endl;
            for(int i=0; i<t[z].tuple_num; i++)
            {
                for(int j=0; j<t[z].attribute_num; j++)
                {
                    cout<<t[z].table_data[i][j]<<"   ";
                }
                cout<<endl;
            }
            cout<<endl;
        }

        cout<<"视图"<<endl;
        ifstream fin;
        fin.open("view.txt",ios_base::in);
        if(fin.fail())
        {
            cout<<"打开文件失败"<<endl;
        }
         char s[1024]= {0};
      while( fin.getline(s,sizeof(s))){

           cout<<s<<endl;
       }
       fin.close();
    }



}

#endif // HELP_H_INCLUDED
