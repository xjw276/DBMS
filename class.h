#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED
using namespace std;

class Table
{
public:
    string table_name;    //表名
    int attribute_num;    //属性个数
    string attribute_name[100];      //属性名
    string attribute_type[100];//属性类型
    int attribute_length;//属性类型长度
    //数据类型

    int tuple_num;        //元组的个数
    string table_data[100][100];		        //三维表,保存的内容是记录的值

    int prikey[100];//各标记属性所在位置的下标
    int forkey[100];
    int unikey[100];
    int notnull[100];
    string foreigntable[100];//外键所连接的表
    string foreign[100];//外键所连接表的键
    Table()
    {
        table_name="";
        attribute_length=0;
        for(int i=0; i<100; i++)
        {
            attribute_name[i]="";
            attribute_type[i]="";
            prikey[i]=-1;
            forkey[i]=-1;
            unikey[i]=-1;
            notnull[i]=-1;
            foreigntable[i]="";
            foreign[i]="";
             for(int j=0;j<100;j++){
                 table_data[i][j]="";
            }
        }
        attribute_num=0;
        tuple_num=0;        //元组的个数
    }
};

class View
{
public:
   // string proname[100];	//可见的属性
    string sql;
    string tname;		//对应的表名
    string vname;		//视图名
  //  int  pro_num;
    View()
    {
        for(int i=0;i<100;i++){
            ;
        }
        sql="";
        tname="";
        vname="";
       // pro_num=0;

    }
};	//视图，视图对应一个表，一个表可以对应多个视图
class Index
{
public:
    string iname[100];		//一个索引对应一个表
	string key_pro[100];                //索yin属性
	int  key_;                    ///索引对应下标
	string  from_table[100];     ///哪一个表的索引
    int  index_num;
	string key[100];	         ///排好序之后的索引属性
	int  key_ind[100];           ///排好序之后的索引下标对应原表中的下表。
	Index(){
	}
};
#endif // CLASS_H_INCLUDED
