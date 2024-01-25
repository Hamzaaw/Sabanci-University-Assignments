#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};



string toUpperCase(const string& input) {
    string output = input;
    transform(output.begin(), output.end(), output.begin(),
              [](unsigned char c){ return toupper(c); });
    return output;
}

unsigned int hashhFunction1(const string& s) {
    unsigned int hashValue = 0;
    for (char c : s) {
        hashValue = hashValue * 31 + c;
    }
    return hashValue;
}//hash function if needed



struct DocumentItem {
    string documentName;
    int count = 0;
};

unsigned int anotherHashFunction(const string& s) {
    unsigned int hashValue = 0;
    for (char c : s) {
        hashValue = (hashValue << 5) | (hashValue >> 27); // Rotate the current bits of hashValue
        hashValue += static_cast<unsigned int>(c); // Add the character value
    }
    return hashValue;
}//hash function if needed might be better



struct WordItem {
    string word = "";
    vector<DocumentItem> documentList;

    WordItem() = default;
    WordItem(string neww, string document_name) : word(std::move(neww)), documentList{{document_name, 1}} {}
    explicit WordItem(int) : word("-1") {}
    
    friend bool operator == (const WordItem& left, const WordItem& right) { return left.word == right.word; }
    friend bool operator != (const WordItem& left, const WordItem& right) { return left.word != right.word; }
    friend bool operator < (const WordItem& left, const WordItem& right) { return left.word < right.word; }
    friend bool operator > (const WordItem& left, const WordItem& right) { return left.word > right.word; }
    friend bool operator <= (const WordItem& left, const WordItem& right) { return left.word <= right.word; }
    friend bool operator >= (const WordItem& left, const WordItem& right) { return left.word >= right.word; }
};

template <class T>
class HashTbl {
public:
    enum change {
        ON,
        Zero,
        Remove
    };

private:
    //enter use enum
    

    
struct rate {
        T elem;
        change info;

        rate(const T& e = T(), change i = Zero) : elem(e), info(i) {}
    };

    vector<rate> arr;
    int count;

public:
    HashTbl(int size) : arr(nextPrime(size)), count(0) {}

    bool insert(T& x) {
        int pos = XOX(x);
        if (arr[pos].info == ON) return false;
        arr[pos] = rate(x, ON);
        if (++count > arr.size() / 1.25) hashing();
        return true;
    }

    void remove(T& x) {
        int pos = XOX(x);
        if (arr[pos].info == ON) {
            arr[pos].info = Remove;
            --count;
        }
    }

    int check(T& x) {
        int pos = XOX(x);
        return arr[pos].info == ON ? pos : -1;
    }

    T& finder(T& x) { return arr[XOX(x)].elem; }

    void print() {
        cout << "After preprocessing, the unique word count is " << count << ". Current load ratio is " << double(count) / arr.size() << endl;
    }

private:
    bool isssPrime(int n) {
        if (n <= 1) return false;
        if (n == 2) return true;  // 2 is a prime number
        if (n % 2 == 0) return false;

        // Check
        for (int i = 3; i <= sqrt(n); i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }
    
    bool isPrime(int n) {
        if (n == 2) return true;
        for (int i = 2; i < n; i++) {
            if (n % i == 0) return false;
        }
        return true;
    }

    int nextPrime(int n) {
        if (n % 2 == 0) ++n;
        while (!isPrime(n)) n += 2;
        return n;
    }

    int hashFunc(WordItem& input) {
        int hashVal = 0;
        string key = input.word;
        for (char ch : key) hashVal = 37 * hashVal + ch;
        hashVal %= arr.size();
        if (hashVal < 0) hashVal += arr.size();
        return hashVal;
    }

    int XOX(T& x) {
        int pos = hashFunc(x);
        int collisionNum = 0;
        while (arr[pos].info != Zero && arr[pos].elem != x) {
            pos += 2 * ++collisionNum - 1;
            if (pos >= arr.size()) pos -= arr.size();
        }
        return pos;
    }

    void hashing() {
        vector<rate> oldArr = arr;
        arr.resize(nextPrime(2 * oldArr.size()));
        for (auto& entry : arr) entry.info = Zero;
        count = 0;
        for (auto& entry : oldArr)
            if (entry.info == ON) insert(entry.elem);
        cout << "rehashed...\nprevious table size:" << oldArr.size() << ", new table size: " << arr.size() << ", current unique word count: " << count << ", current load factor: " << double(count) / arr.size() << endl;
    }
};


unsigned long hash_2(const string& str) {
    unsigned long hash = 5381;
    int c;

    for (size_t i = 0; i < str.length(); i++) {
        c = static_cast<int>(str[i]);
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}


template <class Comparable>
class BinarySearchTree {
private:
    struct BinaryNode {
        Comparable data;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Comparable& theData, BinaryNode* lt = nullptr, BinaryNode* rt = nullptr)
            : data(theData), left(lt), right(rt) {}
    };

    BinaryNode* root;
    Comparable ITEM_NOT_FOUND;

    Comparable& elementAt(BinaryNode* position) {
        return position ? position->data : ITEM_NOT_FOUND;
    }

    BinaryNode* find(const Comparable& x, BinaryNode* t) {
        if (!t) return nullptr;
        if (x < t->data) return find(x, t->left);
        if (x > t->data) return find(x, t->right);
        return t;
    }

    BinaryNode* findMin(BinaryNode* t) const {
        return t ? (t->left ? minimum(t->left) : t) : nullptr;
    }

    BinaryNode* findMax(BinaryNode* t) const {
        return t ? (t->right ? Maximum(t->right) : t) : nullptr;
    }

    void insert(const Comparable& x, BinaryNode*& t) {
        if (!t) t = new BinaryNode(x);
        else if (x < t->data) insert(x, t->left);
        else if (x > t->data) insert(x, t->right);
    }

    void remove(const Comparable& x, BinaryNode*& t) {
        if (!t) return;
        if (x < t->data) remove(x, t->left);
        else if (x > t->data) remove(x, t->right);
        else if (t->left && t->right) {
            t->data = minimum(t->right)->data;
            remove(t->data, t->right);
        } else {
            BinaryNode* deletesoon = t;
            t = (t->left) ? t->left : t->right;
            delete deletesoon;
        }
    }

    void makeEmpty(BinaryNode*& t) {
        if (t) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullptr;
        }
    }

    void PrintFunc(BinaryNode* t) const {
        if (t) {
            PrintFunc(t->left);
            std::cout << t->data << std::endl;
            PrintFunc(t->right);
        }
    }

    BinaryNode* clone(BinaryNode* t) const {
        return t ? new BinaryNode(t->data, clone(t->left), clone(t->right)) : nullptr;
    }

public:
    BinarySearchTree(const Comparable& notFound) : ITEM_NOT_FOUND(notFound), root(nullptr) {}

    Comparable& find(const Comparable& x) {
        return elementAt(find(x, root));
    }

    const Comparable& minimum() const {
        return elementAt(minimum(root));
    }

    const Comparable& Maximum() const {
        return elementAt(Maximum(root));
    }

    void insert(const Comparable& x) {
        insert(x, root);
    }

    void remove(const Comparable& x) {
        remove(x, root);
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    bool isEmpty() const {
        return !root;
    }

    void printTree() const {
        PrintFunc(root);
    }

    const BinarySearchTree<Comparable>& operator=(const BinarySearchTree& rhs) {
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }

    ~BinarySearchTree() {
        makeEmpty();
    }
};






void clean(string& domain) {
    for (char& character : domain) {
        character = isalpha(character) ? tolower(character) : ' ';
    }
}



int findIndex(vector<string>& strList, string searchTerm) {
    auto it = find(strList.begin(), strList.end(), searchTerm);
    return (it != strList.end()) ? distance(strList.begin(), it) : -1;
}




bool isDocumentInList(const vector<DocumentItem>& docList, const string& docName) {
    return any_of(docList.begin(), docList.end(), [&docName](const DocumentItem& item) {
        return item.documentName == docName;
    });
}





bool isAllTrue(vector<bool>& list) {
    bool rap = true;
    for (int i = 0; i < list.size(); i++)
    {
        if (list[i] == false) {
            rap = false;
        }
    }
    return rap;
}

void queryKing(string query, int& fileNumber, BinarySearchTree<WordItem>& BST, vector<string>& fileNames, int h, int o) {
    clean(query);
    istringstream ss(query);
    string qWord;

    vector<string> qWords;
    vector<vector<bool>> zart2;

    while (ss >> qWord) {
        qWords.push_back(qWord);

        vector<bool> zart(fileNumber, true);
        WordItem& tempItemHASH = BST.find(WordItem(qWord, "query"));

        for (int i = 0; i < zart.size(); i++)
            zart[i] = isDocumentInList(tempItemHASH.documentList, fileNames[i]);

        zart2.push_back(zart);
    }

    bool hic = false;

    for (int kk = 0; kk < fileNumber; kk++) {
        vector<bool> bools(zart2.size(), true);

        for (int i = 0; i < zart2.size(); i++)
            bools[i] = zart2[i][kk];

        if (isAllTrue(bools) && h == o - 1) {
            hic = true;
            cout << "in Document " << fileNames[kk];

            for (const auto& word : qWords) {
                WordItem& tempItemHASH = BST.find(WordItem(word, "query"));
                int wCount = 0;

                for (const auto& doc : tempItemHASH.documentList)
                    if (doc.documentName == fileNames[kk])
                        wCount = doc.count;

                cout << ", " << word << " found " << wCount << " times";
            }

            cout << "." << endl;
        }
    }

    if (!hic && h == o - 1)
        cout << "No document contains the given query" << endl;
}

void queryQueen(string& query, int& numOfFiles, HashTbl<WordItem>& hashTable, vector<string>& fileNames, int h, int o) {
    clean(query);
    istringstream queryStream(query);
    string queryWord;

    vector<string> queryWords;
    vector<vector<bool>> documentMatches;

    bool isMatchFound = false;

    while (queryStream >> queryWord) {
        queryWords.push_back(queryWord);

        vector<bool> matches(numOfFiles, true);

        WordItem newItem(queryWord, "query");
        WordItem& tempItemHash = hashTable.finder(newItem);

        for (int i = 0; i < matches.size(); i++)
        {
            if (!isDocumentInList(tempItemHash.documentList, fileNames[i])) {
                matches[i] = false;
            }
        }

        documentMatches.push_back(matches);
    }

    for (int i = 0; i < numOfFiles; i++) {

        vector<bool> bools(queryWords.size(), true);

        for (int j = 0; j < documentMatches.size(); j++)
        {
            if (!documentMatches[j][i]) {
                bools[j] = false;
            }
        }

        if (isAllTrue(bools) && h == o - 1) {
            isMatchFound = true;

            cout << "in Document " << fileNames[i];

            for (const auto& word : queryWords)
            {
                WordItem newItem(word, "query");
                WordItem& tempItemHash = hashTable.finder(newItem);
                int wordCount = 0;

                for (const auto& doc : tempItemHash.documentList)
                {
                    if (doc.documentName == fileNames[i]) {
                        wordCount = doc.count;
                    }
                }

                cout << ", " << word << " found " << wordCount << " times";
            }

            cout << "." << endl;
        }
    }

    if (!isMatchFound && h == o - 1) {
        cout << "No document contains the given query" << endl;
    }
}





string ToUpperagain(const string& input) {
    string output = input;

    transform(output.begin(), output.end(), output.begin(),
              [](unsigned char c){ return tolower(c); });

    string temp = output;

    transform(output.begin(), output.end(), output.begin(),
              [](unsigned char c){ return toupper(c); });

    if (output != temp) {
        cout << "Strings are not the same after conversion." << endl;
    }

    return output;
}



    int main() {
        int numFiles;
        cout << "Enter number of input files: ";
        cin >> numFiles;

        vector<string> fileNames(numFiles);
        for (int i = 0; i < numFiles; i++) {
            cout << "Enter " << i+1 << ". file name: ";
            cin >> fileNames[i];
        }

        const WordItem notFound(-1);
        BinarySearchTree<WordItem> bst(notFound);
        HashTbl<WordItem> hash(50);

        for (int i = 0; i < numFiles; i++) {
            ifstream input(fileNames[i]);
            string line;
            while (getline(input, line)) {
                clean(line);
                istringstream ss(line);
                string word;
                while (ss >> word) {
                    WordItem nayaa(word, fileNames[i]);
                    if (bst.find(nayaa) == notFound) {
                        bst.insert(nayaa);
                    } else {
                        WordItem& tempItemBST = bst.find(nayaa);
                        bool docExists = false;
                        for (auto& doc : tempItemBST.documentList) {
                            if (doc.documentName == fileNames[i]) {
                                docExists = true;
                                doc.count++;
                            }
                        }
                        if (!docExists) {
                            DocumentItem newDoc;
                            newDoc.documentName = fileNames[i];
                            newDoc.count = 1;
                            tempItemBST.documentList.push_back(newDoc);
                        }
                    }

                    if (hash.check(nayaa) == -1) {
                        hash.insert(nayaa);
                    } else {
                        WordItem& tempo = hash.finder(nayaa);
                        bool nurse = false;
                        for (auto& doc : tempo.documentList) {
                            if (doc.documentName == fileNames[i]) {
                                nurse = true;
                                doc.count++;
                            }
                        }
                        if (!nurse) {
                            DocumentItem doctor;
                            doctor.documentName = fileNames[i];
                            doctor.count = 1;
                            tempo.documentList.push_back(doctor);
                        }
                    }
                }
            }
            input.close();
        }

        cout << endl;
        hash.print();

        string query;
        cout << "Enter queried words in one line: ";
        cin.clear();
        cin.ignore();
        getline(cin, query);

        int k = 20;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < k; i++)
            queryKing(query, numFiles, bst, fileNames, i, k);
        auto bstTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);

        start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < k; i++)
            queryQueen(query, numFiles, hash, fileNames, i, k);
        auto htTime = std::chrono::duration_cast<std::chrono::nanoseconds>
            (std::chrono::high_resolution_clock::now() - start);

        cout << "\nTime: " << bstTime.count() / k << "\n";
        cout << "\nTime: " << htTime.count() / k << "\n";
        cout << "Speed Up: " << (double)bstTime.count() / htTime.count() << endl;

        return 0;
    }
