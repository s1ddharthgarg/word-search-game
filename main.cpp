#include<bits/stdc++.h>
using namespace std;

class trienode
{
public:
    char data;
    trienode **children;
    bool isterminal;
    trienode(char d)
    {
        this->data=d;
        children =new trienode*[26];
        for(int i=0; i<26; i++)
        {
            children[i]=NULL;
        }
        this->isterminal=false;
    }
};

class trie
{
public:
    trienode *root;
    trie()
    {
        root=new trienode('\0');
    }
    void insertword(trienode *root,string word)
    {
        if(word.size()==0)
        {
            root->isterminal=true;
            return;
        }
        int index=word[0]-'A';
        trienode *child;
        if(root->children[index]!=NULL)
        {
            child=root->children[index];
        }
        else
        {
            child=new trienode(word[0]);
            root->children[index]=child;
        }
        return insertword(child,word.substr(1));
    }

    void insertword(string word)
    {
        return insertword(root,word);
    }

    bool searchword(trienode *root,string word)
    {
        if(word.size()==0)
        {
            if(root->isterminal==true)
            {
                return true;
            }
            return false;
        }
        int index=word[0]-'A';
        trienode *child;
        if(root->children[index]!=NULL)
        {
            child=root->children[index];
        }
        else
        {
            return false;
        }
        return searchword(child,word.substr(1));
    }

    bool searchword(string word)
    {
        return searchword(root,word);
    }

    void removeword(trienode *root,string word)
    {
        if(word.size()==0)
        {
            root->isterminal=false;
            return;
        }
        int index=word[0]-'A';
        trienode *child;
        if(root->children[index]!=NULL)
        {
            child=root->children[index];
        }
        else
        {
            return;
        }
        return removeword(child,word.substr(1));
        if(child->isterminal==false)
        {
            for(int i=0; i<26; i++)
            {
                if(child->children[i]!=NULL)
                {
                    return;
                }
            }
            delete child;
            root->children[index]=NULL;
        }
    }
    void removeword(string word)
    {
        return removeword(root,word);
    }

    void wordLook(vector<vector<char>> &v, int n, int m, int i, int j, int yInc, int xInc, trienode *root, string direction, string tmp, const int& startX, const int& startY)
    {
        if(root->isterminal)
        {
            cout<<setw(15)<<tmp<<"\t\t\t"<<startX<<","<<startY<<"\t\t"<<direction<<endl;
        }
        i += yInc;
        j += xInc;
        if(i>=0 && i<n && j>=0 && j<m){
            int index = v[i][j]-'A';
            tmp.push_back(v[i][j]);
            if(root->children[index] != NULL){
                wordLook(v, n, m, i, j, yInc, xInc, root->children[index], direction, tmp, startX, startY);
            }
        }
    }

    void wordSearch(vector<vector<char>> &v, int n, int m)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
            {
                int index = v[i][j]-'A';
                if(root->children[index] != NULL)
                {
                    string tmp;
                    tmp.push_back(v[i][j]);
                    //Left Direction
                    wordLook(v, n, m, i, j,  -1, 0, root->children[index], "Up", tmp, i, j);
                    //Right Direction
                    wordLook(v, n, m, i, j, 1, 0, root->children[index], "Down", tmp, i, j);
                    //Up Direction
                    wordLook(v, n, m, i, j, 0, -1, root->children[index], "Left", tmp, i, j);
                    //Down Direction
                    wordLook(v, n, m, i, j, 0, 1, root->children[index], "Right", tmp, i, j);
                    //Left-Up Direction
                    wordLook(v, n, m, i, j, -1, -1, root->children[index], "Left-Up", tmp, i, j);
                    //Right-Up Direction
                    wordLook(v, n, m, i, j, 1, -1, root->children[index], "Left-Down", tmp, i,j);
                    //Left-Down Direction
                    wordLook(v, n, m, i, j, -1, 1, root->children[index], "Right-Up", tmp, i, j);
                    //Right-Down Direction
                    wordLook(v, n, m, i, j, 1, 1, root->children[index], "Right-Down", tmp, i, j);
                }
            }
        }
    }
};


int main()
{
    fstream file;
    string word, q, filename;
    file.open("dictionary.txt");
    //Inserting all words from file into trie
    trie t;
    while (file >> word)
    {
        t.insertword(word);
    }
    file.close();
    int n, m;
    cout<<"Enter Puzzle matrix: ";
    cin>>n>>m;
    vector<vector<char>>v;
    for(int i=0; i<n; i++)
    {
        char ch;
        vector<char>tmp;
        for(int j=0; j<m; j++)
        {
            cin>>ch;
            tmp.push_back(ch);
        }
        v.push_back(tmp);
    }
    cout<<"_______________________________________________________________\n";
    cout<<"\tWord\t\t     Co-ordinates\tDirection\n";
    cout<<"_______________________________________________________________\n";
    t.wordSearch(v, n, m);
    return 0;
}
