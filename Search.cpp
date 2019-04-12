#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <algorithm>


using namespace std;
 
 
typedef struct  WORD{
	string  m_char;
	long m_num;
}words; 
 
 
class Node { // 节点类
public:
    // 建构子， 该节点默认的建构子内容为空字符， 不是单词的结束
    Node() { mContent = ' '; mMarker = false; count=0;}
    // 析构函数
    ~Node() {}
    // 返回这个节点的内容
    char content() { return mContent; }
    // 设置这个节点的内容
    void setContent(char c) { mContent = c; }
   // 这个节点是否是这个单词的结束标志 
    bool wordMarker() { return mMarker; }
    
	long wordcount(){return count;}
    // 设置当前的节点为单词结束标志
    void setWordMarker() { mMarker = true; count++;}
    // 给定字符c, 找到这个字符对应当前节点的的孩子节点
    Node* findChild(char c);
    // 将一个节点作为当前节点的孩子节点， append上
    void appendChild(Node* child) { mChildren.push_back(child); }
    // 放回当前节点的所有孩子节点
    vector<Node*> children() { return mChildren; }
 
private:
    char mContent; // 节点的字符
    long count;    //
    bool mMarker; // 该节点是否为单词的结束位置
    vector<Node*> mChildren; // 该节点的孩子， 是vector of nodes(为这个节点的孩子)
};
 
// 字典树的类
class Trie {
public:
    Trie();
    ~Trie();
    // 添加一个单词到孩子节点
    void addWord(string s);
    //给定字符s， 查找当前的子点数中是否有这个单词
    long searchWord(string s);
    // 给定单词， 删除当前字典树中的这个单词
    void deleteWord(string s);
	
	long findline(){return max_num;};
private:
    // 字典树的根节点
    Node* root;
    static long max_num;
};
 
Node* Node::findChild(char c)
{
    // 检查当前节点的孩子节点是否有字符c， 若有， 则返回这个节点
    for ( int i = 0; i < mChildren.size(); i++ )
    {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c )
        {
            return tmp;
        }
    }
    // 在当前节点的孩子孩子中没找到， 返回NULL
    return NULL;
}
 
 
 
 
long Trie:: max_num=0;
 
 
Trie::Trie()
{
    root = new Node();
}
 
Trie::~Trie()
{
    // Free memory
}
 
void Trie::addWord(string s)
{
	
	
    Node* current = root; 
     //插入的字符为空字符， 直接把当前的（根节点）设置为
    if ( s.length() == 0 )
    {
        current->setWordMarker(); // an empty word
        return;
    }
 
    for ( int i = 0; i < s.length(); i++ )
    {
        Node* child = current->findChild(s[i]);
        if ( child != NULL )
        {
            // 找到了这个节点的位置
            current = child;
        }
        else
        {
            // 没有找到到， 则创建
			
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            // 将这个节点设置为孩子节点
            current->appendChild(tmp);
            current = tmp;
        }
        // 最后一个字符设置这里的单词结束标志
        if ( i == s.length() - 1 )
		{ 	 if(current->wordcount()==0){
			  max_num++;
		    }
			current->setWordMarker();
		}
    }
}
 
 
long Trie::searchWord(string s)
{
    Node* current = root;
 
    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return 0;
            current = tmp;
        }
 
        if ( current->wordMarker() )
            return current->wordcount();
        else
            return 0;
    }
 
    return 0;
}


static long deal_data(Trie  *data_trie) {
    string word;
    char ch;
    long file_num=0;
    const char* filename="test.txt";
    ifstream infile(filename,ios_base::in);
    ofstream outfile("dealt_data.txt",ios_base::out);
    if(!infile) {
        cout<<"Open  file error!"<<endl;
        exit(1);
	}
    if(!outfile) {
        cout<<"Open dealt_data error!"<<endl;
        exit(1);
	}
    
    while(infile.get(ch)) {
        if((ch>=65&&ch<=90)||(ch>=97&&ch<=122)||(ch>=47&&ch<=56)){
        	;
		}
        else{
		    ch=' ';
		}
		outfile.put(ch);
    }
    infile.close();
    outfile.close();
    ifstream infile1("dealt_data.txt",ios::in);
    if(!infile1) {
        cout<<"open dealt_data error!"<<endl;
         exit(1);
    }
  
    while(infile1>>word) {
      
         data_trie->addWord(word);file_num++;
        // cout<<word<<endl;
    }
	infile1.close();
	
	return file_num;
  
} 

bool cmp(words a , words b)
{
	if (a.m_num > b.m_num )
	{
		return true;
	}

	return false ;

}

int main()
{
	Trie* trie = new Trie();
	long sum_data;
	sum_data=deal_data(trie);//建立Trie 

	ifstream infile2("dealt_data.txt",ios::in);
	
	
	bool e_flag=true;
	int i,j;
	long num_word=0;
	string m_word;
	
	num_word=trie->findline();//得到总共的单词数 
	vector<words> n_word(num_word);//定义统计每类单词的数组 
	infile2>>m_word;
	n_word[0].m_char=m_word;
	n_word[0].m_num=trie->searchWord(m_word);

	
	cout<<"num_word    "<<num_word<<endl;
	

	i=0; 
	while(infile2>>m_word) {
      	for(j=0;j<=i;j++)
		{
			if((n_word[j].m_char==m_word)){		//如果一样则不添加			
				e_flag=false;
				break;
			}
		}
		if(e_flag){
				i++;//添加新的单词 
				n_word[i].m_char=m_word;
				n_word[i].m_num=trie->searchWord(m_word);
		}
		
		e_flag=true;
 		if(i==(num_word-1))
 			break;
    }

  
    infile2.close();
	
	//对结构体排序 
	sort(n_word.begin(),n_word.end(),cmp);
	for(i=0;i<10;i++)
	{
		
		cout<<endl<<n_word[i].m_char<<"  "<<n_word[i].m_num <<endl;
		if(i==(num_word-1))
 			break;
	}
	
	
    delete trie;
	return 0;
}

