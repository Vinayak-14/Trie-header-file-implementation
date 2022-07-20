#include <iostream>
#include "myTrie.h"
using namespace std;

int main()
{
  // declaring 2 tries objects
  myTrie *obj1 = new myTrie();
  myTrie *obj2 = new myTrie();

  // inserting words in trie 1
  obj1->insert("cat");
  obj1->insert("cats");
  obj1->insert("caterpillar");
  obj1->insert("dog");
  obj1->insert("duck");
  obj1->insert("horse");
  obj1->insert("dogs");

  // displaying trie 1
  vector<string> output = obj1->display();
  for (auto it : output)
    cout << it << " ";
  cout << endl;

  // inserting words in trie 2
  obj2->insert("kitten");
  obj2->insert("lion");
  obj2->insert("cheetah");
  obj2->insert("frog");

  // merging trie 1 and trie 2 into trie 1
  obj1 = obj1->merge(obj1, obj2);

  // displaying trie 1 after merging trie 1 and trie 2
  vector<string> output1 = obj1->display();
  for (auto it : output1)
    cout << it << " ";
  cout << endl;

  // checking the presence of words
  cout << obj1->isPresent("catty") << endl;
  cout << obj1->isPresent("cat") << endl;

  // checking presence and checking presence again after deleting the word
  cout << obj1->isPresent("horse") << endl;
  cout << obj1->erase("horse") << endl;
  cout << obj1->isPresent("horse") << endl;

  // getting all words in which prefix is "ca"
  vector<string> output2 = obj1->autocomplete("ca");
  for (auto it : output2)
    cout << it << " ";
  cout << endl;

  // getting all words in which prefix is "dog"
  vector<string> output3 = obj1->autocomplete("dog");
  for (auto it : output3)
    cout << it << " ";
  cout << endl;

  // printing the size of trie (no of words in the trie)
  cout << obj1->size() << endl;

  // displaying trie 1 since horse is deleted now
  vector<string> output4 = obj1->display();
  for (auto it : output4)
    cout << it << " ";
  cout << endl;

  // printing the position of words in dictionary order
  cout << obj1->position("cat") << endl;
  cout << obj1->position("dog") << endl;
  cout << obj1->position("lion") << endl;
}
