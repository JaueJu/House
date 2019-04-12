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
 
 
class Node { // �ڵ���
public:
    // �����ӣ� �ýڵ�Ĭ�ϵĽ���������Ϊ���ַ��� ���ǵ��ʵĽ���
    Node() { mContent = ' '; mMarker = false; count=0;}
    // ��������
    ~Node() {}
    // ��������ڵ������
    char content() { return mContent; }
    // ��������ڵ������
    void setContent(char c) { mContent = c; }
   // ����ڵ��Ƿ���������ʵĽ�����־ 
    bool wordMarker() { return mMarker; }
    
	long wordcount(){return count;}
    // ���õ�ǰ�Ľڵ�Ϊ���ʽ�����־
    void setWordMarker() { mMarker = true; count++;}
    // �����ַ�c, �ҵ�����ַ���Ӧ��ǰ�ڵ�ĵĺ��ӽڵ�
    Node* findChild(char c);
    // ��һ���ڵ���Ϊ��ǰ�ڵ�ĺ��ӽڵ㣬 append��
    void appendChild(Node* child) { mChildren.push_back(child); }
    // �Żص�ǰ�ڵ�����к��ӽڵ�
    vector<Node*> children() { return mChildren; }
 
private:
    char mContent; // �ڵ���ַ�
    long count;    //
    bool mMarker; // �ýڵ��Ƿ�Ϊ���ʵĽ���λ��
    vector<Node*> mChildren; // �ýڵ�ĺ��ӣ� ��vector of nodes(Ϊ����ڵ�ĺ���)
};
 
// �ֵ�������
class Trie {
public:
    Trie();
    ~Trie();
    // ���һ�����ʵ����ӽڵ�
    void addWord(string s);
    //�����ַ�s�� ���ҵ�ǰ���ӵ������Ƿ����������
    long searchWord(string s);
    // �������ʣ� ɾ����ǰ�ֵ����е��������
    void deleteWord(string s);
	
	long findline(){return max_num;};
private:
    // �ֵ����ĸ��ڵ�
    Node* root;
    static long max_num;
};
 
Node* Node::findChild(char c)
{
    // ��鵱ǰ�ڵ�ĺ��ӽڵ��Ƿ����ַ�c�� ���У� �򷵻�����ڵ�
    for ( int i = 0; i < mChildren.size(); i++ )
    {
        Node* tmp = mChildren.at(i);
        if ( tmp->content() == c )
        {
            return tmp;
        }
    }
    // �ڵ�ǰ�ڵ�ĺ��Ӻ�����û�ҵ��� ����NULL
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
     //������ַ�Ϊ���ַ��� ֱ�Ӱѵ�ǰ�ģ����ڵ㣩����Ϊ
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
            // �ҵ�������ڵ��λ��
            current = child;
        }
        else
        {
            // û���ҵ����� �򴴽�
			
            Node* tmp = new Node();
            tmp->setContent(s[i]);
            // ������ڵ�����Ϊ���ӽڵ�
            current->appendChild(tmp);
            current = tmp;
        }
        // ���һ���ַ���������ĵ��ʽ�����־
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
	sum_data=deal_data(trie);//����Trie 

	ifstream infile2("dealt_data.txt",ios::in);
	
	
	bool e_flag=true;
	int i,j;
	long num_word=0;
	string m_word;
	
	num_word=trie->findline();//�õ��ܹ��ĵ����� 
	vector<words> n_word(num_word);//����ͳ��ÿ�൥�ʵ����� 
	infile2>>m_word;
	n_word[0].m_char=m_word;
	n_word[0].m_num=trie->searchWord(m_word);

	
	cout<<"num_word    "<<num_word<<endl;
	

	i=0; 
	while(infile2>>m_word) {
      	for(j=0;j<=i;j++)
		{
			if((n_word[j].m_char==m_word)){		//���һ�������			
				e_flag=false;
				break;
			}
		}
		if(e_flag){
				i++;//����µĵ��� 
				n_word[i].m_char=m_word;
				n_word[i].m_num=trie->searchWord(m_word);
		}
		
		e_flag=true;
 		if(i==(num_word-1))
 			break;
    }

  
    infile2.close();
	
	//�Խṹ������ 
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

