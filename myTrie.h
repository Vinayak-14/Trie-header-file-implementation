#include <string.h>
#include <vector>
using namespace std;

const int ALPHABET_SIZE = 26;

class TrieNode
{
public:
  char data;
  TrieNode *children[ALPHABET_SIZE];
  bool isTerminal;
  TrieNode(char x)
  {
    data = x;
    for (int i = 0; i < 26; i++)
      children[i] = NULL;
    isTerminal = false;
  }
};

class myTrie
{
  TrieNode *root;
  int count;

public:
  myTrie()
  {
    root = new TrieNode('\0');
    count = 0;
  }

  // O(n) -> n = word size
  void insert(string word)
  {
    TrieNode *node = root;
    for (auto ch : word)
    {
      int index = ch - 'a';
      if (node->children[index])
        node = node->children[index];
      else
      {
        TrieNode *newNode = new TrieNode(ch);
        node->children[index] = newNode;
        node = newNode;
      }
    }
    if (node->isTerminal == false)
      count++;
    node->isTerminal = true;
  }

  // O(n) -> n = word size
  bool isPresent(string word)
  {
    TrieNode *node = root;
    for (auto ch : word)
    {
      int index = ch - 'a';
      if (node->children[index])
        node = node->children[index];
      else
        return false;
    }
    return node->isTerminal;
  }

  // O(n) -> n = word size
  // return false if word is not found
  bool erase(string word)
  {
    TrieNode *node = root;
    for (auto ch : word)
    {
      int index = ch - 'a';
      if (node->children[index])
        node = node->children[index];
      else
        return false;
    }
    if (node->isTerminal == false)
      return false;
    node->isTerminal = false;
    count--;
    return true;
  }

  // O(1)
  int size()
  {
    return count;
  }

  // O(W*L) , where W is the number of words, and L is an average length of the word
  // to find all the words with prefix str
  vector<string> autocomplete(string str)
  {
    vector<string> ans;
    TrieNode *node = root;
    for (auto ch : str)
    {
      int index = ch - 'a';
      if (node->children[index])
        node = node->children[index];
      else
        return ans;
    }

    vector<string> temp = display(node);
    for (auto it : temp)
      ans.push_back(str + it);
    return ans;
  }

  // display the trie from the given node
  vector<string> display(TrieNode *node)
  {
    string s = "";
    vector<string> temp;
    display(node, s, temp);
    return temp;
  }

  // display function for user to display the trie
  vector<string> display()
  {
    string s = "";
    vector<string> temp;
    display(root, s, temp);
    return temp;
  }

  // O(W*L) , where W is the number of words, and L is an average length of the word
  // main algorithm of display function
  void display(TrieNode *node, string &s, vector<string> &temp)
  {
    if (node->isTerminal)
      temp.push_back(s);
    for (int i = 0; i < 26; i++)
    {
      if (node->children[i])
      {
        s += (i + 'a');
        display(node->children[i], s, temp);
        s.pop_back();
      }
    }
  }

  // O(W*L) , where W is the number of words in the small size trie, and L is an average length of the word
  // merge 2 tries
  myTrie *merge(myTrie *a, myTrie *b)
  {
    if (a->size() < b->size())
    {
      vector<string> dict = a->display();
      for (auto it : dict)
      {
        b->insert(it);
      }
      return b;
    }
    else
    {
      vector<string> dict = b->display();
      for (auto it : dict)
      {
        a->insert(it);
      }
    }
    return a;
  }

  // return "-1" if the word not found
  //  helper function of trie
  int position(string str)
  {
    int ans = 0;
    string s;
    bool found = position(root, str, s, ans);
    if (found == false)
      return -1;
    return ans;
  }

  // O(W*L) , where W is the number of words, and L is an average length of the word
  // to find the index of the word in the trie
  // return false if the word not found
  bool position(TrieNode *node, string &str, string &s, int &ans)
  {
    if (str == s)
      return true;
    if (node->isTerminal)
      ans++;
    for (int i = 0; i < 26; i++)
    {
      if (node->children[i])
      {
        s += (i + 'a');
        bool found = position(node->children[i], str, s, ans);
        if (found == true)
          return true;
        s.pop_back();
      }
    }
    return false;
  }
};
