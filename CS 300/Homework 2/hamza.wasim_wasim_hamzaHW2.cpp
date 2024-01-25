//
//  main.cpp
//  CS 300 Homework 2
//
//  Created by Hamza Wasim on 11/11/2023.
//Student ID :00030456



#include <iostream>
using namespace std;
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>
#include <map>

struct DocumentItem {
    string documentName;
    int count;
};

struct WordItem {
    string word;
    list<DocumentItem> documentList;
    
    bool operator<(const WordItem& other) const {
        return word < other.word;
    }

    bool operator>(const WordItem& other) const {
        return word > other.word;
    }
};





template <typename T>
class AVLNode{
public:
    T item;
    int height;
    AVLNode *left;
    AVLNode *right;
    
    AVLNode(T k) : item(k),height(1),left(nullptr),right(nullptr) {};
    
};

template<typename T>
AVLNode<T>* minValueNode(AVLNode<T>* node) {
    AVLNode<T>* c = node;
    while (c->left != nullptr)
        c = c->left;
    return c;
}

template<typename T>
class AVLTree{
private:
    AVLNode<T>* root;
    
    AVLNode<T>* deleteNode(AVLNode<T>* root, T key) {
           if (root == nullptr)
               return root;

           if (key < root->item)
               root->left = deleteNode(root->left, key);
           else if (key > root->item)
               root->right = deleteNode(root->right, key);
           else {
               if ((root->left == nullptr) || (root->right == nullptr)) {
                   AVLNode<T>* temp = root->left ? root->left : root->right;
                   if (temp == nullptr) {
                       temp = root;
                       root = nullptr;
                   } else {
                       *root = *temp;
                   }
                   delete temp;
               } else {
                   AVLNode<T>* temp = minValueNode(root->right);
                   root->item = temp->item;
                   root->right = deleteNode(root->right, temp->item);
               }
           }

           if (root == nullptr)
               return root;

           root->height = 1 + max(Get_height(root->left), Get_height(root->right));
           int balance = Check_Balance(root);

           // Balancing the tree
           // Left Left Case
           if (balance > 1 && Check_Balance(root->left) >= 0)
               return right(root);
           // Left Right Case
           if (balance > 1 && Check_Balance(root->left) < 0) {
               root->left = left(root->left);
               return right(root);
           }
           // Right Right Case
           if (balance < -1 && Check_Balance(root->right) <= 0)
               return left(root);
           // Right Left Case
           if (balance < -1 && Check_Balance(root->right) > 0) {
               root->right = right(root->right);
               return left(root);
           }
           return root;
       }
    
    AVLNode<T>* right(AVLNode<T>* y){
        AVLNode<T> *x = y->left;
        AVLNode<T> *z = x->right;
        x->right = y;
        y->left = z;
        
//        function to update height
        y->height = max(Get_height(y->left), Get_height(y->right)) + 1;
        x->height = max(Get_height(x->left), Get_height(x->right)) + 1;

        return x;

    }
    //for rotation
    AVLNode<T>* left(AVLNode<T>* x) {
        AVLNode<T>* y = x->right;
        AVLNode<T>* z = y->left;
        y->left = x;
        x->right = z;
        
        x->height = max(Get_height(x->left), Get_height(x->right)) + 1;
        y->height = max(Get_height(y->left), Get_height(y->right)) + 1;
        return y;

    }
//getting height
    int Get_height(AVLNode<T>* x){
        if(x == nullptr){
            return 0;
        }
        else{
            return x->height;
        }
    }
    
    // checking for balance
    int Check_Balance(AVLNode<T>* x){
        if(x == nullptr){
            return 0;
        }
        else{
            return Get_height(x->left) - Get_height(x->right);
        }
    }
    
    // Insert function
    AVLNode<T>* insert(AVLNode<T>* node, T key, const string& docuu) {
        //  BST insertion
        if (node == nullptr) {
            key.documentList.push_back(DocumentItem{docuu, 1}); // Add document with count 1
            return new AVLNode<T>(key);
        }

        if (key.word < node->item.word)
            node->left = insert(node->left, key, docuu);
        else if (key.word > node->item.word)
            node->right = insert(node->right, key, docuu);
        else {
            // word already exists
            auto& docList = node->item.documentList;
            auto it = find_if(docList.begin(), docList.end(), [&docuu](const DocumentItem& item) {
                return item.documentName == docuu;
            });

            if (it != docList.end()) {
                // document already exists
                it->count++;
            } else {
                // new document
                docList.push_back(DocumentItem{docuu, 1});
            }
            return node; // Returning the node
        }

        // update height
        node->height = 1 + max(Get_height(node->left), Get_height(node->right));

        // Get  balance factor
        int balance = Check_Balance(node);

        // if this node becomes unbalanced, then there are 4 cases.

        // Left Left Case
        if (balance > 1 && key < node->left->item)
            return right(node);

        // Right Right Case
        if (balance < -1 && key > node->right->item)
            return left(node);

        // Left Right Case
        if (balance > 1 && key > node->left->item) {
            node->left = left(node->left);
            return right(node);
        }

        // Right Left Case
        if (balance < -1 && key < node->right->item) {
            node->right = right(node->right);
            return left(node);
        }

        // return the node pointer
        return node;
    }

    void inOrder(AVLNode<T>* root) {
        if (root != nullptr) {
            inOrder(root->left);
            cout << root->item << " ";
            inOrder(root->right);
        }
    }
    
    // search function
    AVLNode<T>* search(AVLNode<T>* root, const string& word) {
        if (root == nullptr || root->item.word == word)
            return root;

        if (root->item.word < word)
            return search(root->right, word);

        return search(root->left, word);
    }


    
    
    
public:
    

    AVLTree() : root(nullptr) {}

    void insert(WordItem key, const string& documentName) {
        root = insert(root, key, documentName);
    }
    
    void displayInOrder() {
        inOrder(root);
        cout << endl;
    }
    
    void remove(T key) {
        root = deleteNode(root, key);
    }
    
    

    
    list<DocumentItem> search(const string& word) {
        AVLNode<T>* result = search(root, word);
        if (result == nullptr) {
            return list<DocumentItem>(); // Return empty list
        }
        return result->item.documentList;
    }
    
    
    
    
};

void preprocessFile(const string& filename, AVLTree<WordItem>& tree) {
    ifstream file(filename);
    string wordsss;
    while (file >> wordsss) {
        transform(wordsss.begin(), wordsss.end(), wordsss.begin(), ::tolower);
        wordsss.erase(remove_if(wordsss.begin(), wordsss.end(), [](char c) { return !isalpha(c); }), wordsss.end());
        if (!wordsss.empty()) {
            WordItem wordItem;
            wordItem.word = wordsss;
            tree.insert(wordItem, filename); // Changed insert
//            cout << "Inserted word: " << word << " from file: " << filename << endl;
        }
    }
}







    int main() {
        int num;
        cout << "Enter number of input files: ";
        cin >> num;
        cin.ignore();
        
        AVLTree<WordItem> myTree;

        for (int i = 0; i < num; i++) {
            string filename;
            cout << "Enter " << (i + 1) << ". file name: ";
            getline(cin, filename);
            preprocessFile(filename, myTree);
        }
        cout<<endl;

        while (true) {
            string query;
            cout << "Enter queried words in one line: ";
            getline(cin, query);
            if (query == "ENDOFINPUT") break;
            
            if (query.substr(0, 6) == "REMOVE") {
                string wordToRemove = query.substr(7);
                transform(wordToRemove.begin(), wordToRemove.end(), wordToRemove.begin(), ::tolower);
                WordItem itemToRemove;
                itemToRemove.word = wordToRemove;
                myTree.remove(itemToRemove);
                cout << wordToRemove << " has been REMOVED" << endl<<endl;
                continue;
            }
            
      
            
            stringstream ss(query);
            string word;
            map<string, map<string, int>> wordDocuments;
            vector<string> queriedWords;
            bool allWordsFound = true;
            
            while (ss >> word) {
                transform(word.begin(), word.end(), word.begin(), ::tolower);
                word.erase(remove_if(word.begin(), word.end(), [](char c) { return !isalpha(c); }), word.end());
                if (!word.empty()) {
                    queriedWords.push_back(word);
                    auto docs = myTree.search(word);
                    if (docs.empty()) {
                        allWordsFound = false;
                        break; // Break if any word is not found
                    }
                    for (auto& doc : docs) {
                        wordDocuments[word][doc.documentName] += doc.count;
                    }
                }
            }
            
            if (!allWordsFound || queriedWords.empty()) {
                cout << "No document contains the given query" << endl<<endl;
                continue;
            }
            
            map<string, map<string, int>> documentWords;
            

            
            
            
            // display results
            
            for (const auto& word : queriedWords) {
                auto docs = myTree.search(word);
                for (const auto& doc : docs) {
                    documentWords[doc.documentName][word] += doc.count;
                }
            }
            
            for (const auto& docEntry : documentWords) {
                bool allWordsPresent = true;
                for (const auto& queriedWord : queriedWords) {
                    if (docEntry.second.find(queriedWord) == docEntry.second.end()) {
                        allWordsPresent = false;
                        break;
                    }
                }
                
                if (allWordsPresent) {
                    cout << "in Document " << docEntry.first << ", ";
                    bool firstWord = true;
                    for (const auto& queriedWord : queriedWords) {
                        auto wordCountIt = docEntry.second.find(queriedWord);
                        if (wordCountIt != docEntry.second.end()) {
                            if (!firstWord) {
                                cout << ", ";
                            }
                            cout << wordCountIt->first << " found " << wordCountIt->second << " times";
                            firstWord = false;
                        }
                    }
                    cout << "." << endl;
                }
            }
            documentWords.clear();
            cout << endl; // for matching with the result.txt output
            
            
        }
        
        return 0;
    }

    
  









