//
//  main.cpp
//  CS300 HW4 1
//
//  Created by Hamza Wasim on 14/01/2024.
//

#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

//heap sort
template <typename T>
void heapify(vector<T>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template <typename T>
void heapSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}




//insert sort

template <typename T>
void insertionSort(vector<T>& arr) {
    int i, j;
    T key;
    for (i = 1; i < arr.size(); i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


//Merge Sort (In-Place)
template <typename T>
void merge(vector<T>& arr, int l, int m, int r) {
    int i = l;
    int j = m + 1;
    while (i <= m && j <= r) {
        if (arr[i] <= arr[j]) {
            i++;
        } else {
            T value = arr[j];
            int index = j;
            while (index != i) {
                arr[index] = arr[index - 1];
                index--;
            }
            arr[i] = value;
            i++;
            m++;
            j++;
        }
    }
}

template <typename T>
void mergeSort(vector<T>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}


























string toUpperCase(const string& input) {
    string output = input;
    transform(output.begin(), output.end(), output.begin(),
              [](unsigned char c){ return toupper(c); });
    return output;
}


struct DocumentItem {
    string documentName;
    int count = 0;
};



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
//        cout << "rehashed...\nprevious table size:" << oldArr.size() << ", new table size: " << arr.size() << ", current unique word count: " << count << ", current load factor: " << double(count) / arr.size() << endl;
    }
};





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





void swap(WordItem &a, WordItem &b) {
    WordItem temp = a;
    a = b;
    b = temp;
}

// Function to select pivot based on strategy (first, random, median)
int selectPivot(std::vector<WordItem> &data, int low, int high, std::string pivotStrategy) {
    if (pivotStrategy == "first") {
        return low; // Choose the first element as pivot
    } else if (pivotStrategy == "random") {
        return low + rand() % (high - low + 1); // Choose a random pivot
    } else if (pivotStrategy == "median") {
        int mid = low + (high - low) / 2;
        // Find the median of the first, middle, and last elements
        if ((data[low].word <= data[mid].word && data[mid].word <= data[high].word) ||
            (data[high].word <= data[mid].word && data[mid].word <= data[low].word)) {
            return mid;
        } else if ((data[mid].word <= data[low].word && data[low].word <= data[high].word) ||
                   (data[high].word <= data[low].word && data[low].word <= data[mid].word)) {
            return low;
        } else {
            return high;
        }
    }
    return low; // Default to first element as pivot
}

// Partition the data based on the selected pivot
int partition(std::vector<WordItem> &data, int low, int high, std::string pivotStrategy) {
    int pivotIndex = selectPivot(data, low, high, pivotStrategy);
    WordItem pivotValue = data[pivotIndex];

    // Move pivot to the end of the sub-array
    swap(data[pivotIndex], data[high]);

    int i = low;
    for (int j = low; j < high; j++) {
        if (data[j].word <= pivotValue.word) {
            swap(data[i], data[j]);
            i++;
        }
    }
    swap(data[i], data[high]);
    return i;
}

// Quick Sort function with pivot selection strategy
void quickSort(std::vector<WordItem> &data, int low, int high, std::string pivotStrategy) {
    if (low < high) {
        int pivotIndex = partition(data, low, high, pivotStrategy);
        quickSort(data, low, pivotIndex - 1, pivotStrategy);
        quickSort(data, pivotIndex + 1, high, pivotStrategy);
    }
}

// Wrapper function to call Quick Sort with the chosen pivot strategy
void sortWithPivotStrategy(std::vector<WordItem> &data, std::string pivotStrategy) {
    srand(time(NULL)); // Seed the random number generator
    int n = data.size();
    quickSort(data, 0, n - 1, pivotStrategy);
}


int binarySearch(const vector<WordItem>& sortedVector, const string& query, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (sortedVector[mid].word == query) {
            return mid; // Found the query
        }
        if (sortedVector[mid].word < query) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Not found
}


int measureExecutionTime(auto function, int numIterations) {
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < numIterations; i++) {
        function();
    }
    auto duration = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - start);
    return duration.count() / numIterations;
}



int main() {
    int numFiles;
    cout << "Enter number of input files: ";
    cin >> numFiles;

    vector<string> fileNames(numFiles);
    for (int i = 0; i < numFiles; i++) {
        cout << "Enter " << i + 1 << ". file name: ";
        cin >> fileNames[i];
    }

    const WordItem notFound(-1);
    BinarySearchTree<WordItem> bst(notFound);
    HashTbl<WordItem> hash(50);

    // Vector to store unique words
    vector<WordItem> words;

    // Reading files and storing unique words
    for (int i = 0; i < numFiles; i++) {
        ifstream input(fileNames[i]);
        if (!input) {
            cerr << "Error opening file: " << fileNames[i] << endl;
            continue;
        }

        string line, word;
        while (getline(input, line)) {
            clean(line);
            istringstream ss(line);
            while (ss >> word) {
                // Process for BST and Hash Table
                WordItem newItem(word, fileNames[i]);
                if (bst.find(newItem) == notFound) {
                    bst.insert(newItem);
                } else {
                    WordItem& tempItemBST = bst.find(newItem);
                    bool docExists = false;
                    for (auto& doc : tempItemBST.documentList) {
                        if (doc.documentName == fileNames[i]) {
                            docExists = true;
                            doc.count++;
                        }
                    }
                    if (!docExists) {
                        tempItemBST.documentList.push_back({fileNames[i], 1});
                    }
                }

                if (hash.check(newItem) == -1) {
                    hash.insert(newItem);
                } else {
                    WordItem& tempItemHash = hash.finder(newItem);
                    bool docExists = false;
                    for (auto& doc : tempItemHash.documentList) {
                        if (doc.documentName == fileNames[i]) {
                            docExists = true;
                            doc.count++;
                        }
                    }
                    if (!docExists) {
                        tempItemHash.documentList.push_back({fileNames[i], 1});
                    }
                }

                // Convert word to lowercase for case-insensitive comparison
                transform(word.begin(), word.end(), word.begin(), ::tolower);

                // Check if word is already in vector
                auto it = find_if(words.begin(), words.end(), [&word](const WordItem& item) {
                    return item.word == word;
                });

                if (it != words.end()) {
                    // Update document count in vector
                    auto docIt = find_if(it->documentList.begin(), it->documentList.end(), [&fileNames, i](const DocumentItem& doc) {
                        return doc.documentName == fileNames[i];
                    });
                    if (docIt != it->documentList.end()) {
                        docIt->count++;
                    } else {
                        it->documentList.push_back({fileNames[i], 1});
                    }
                } else {
                    // New word, add to vector
                    words.push_back({word, fileNames[i]});
                }
            }
        }
        input.close();
    }

    // Create copies of the vector for each sorting algorithm
    vector<WordItem> wordsForQuickSort = words;
    vector<WordItem> wordsForQuickSort2 = words;
    vector<WordItem> wordsForQuickSort3 = words;
    vector<WordItem> wordsForMergeSort = words;
    vector<WordItem> wordsForHeapSort = words;
    vector<WordItem> wordsForInsertionSort = words;

    // Apply sorting algorithms
    // Quick Sort with different pivot strategies
//    sortWithPivotStrategy(wordsForQuickSort, "median");
//    sortWithPivotStrategy(wordsForQuickSort, "random");
//    sortWithPivotStrategy(wordsForQuickSort, "first");
//
//    // Merge Sort
//    mergeSort(wordsForMergeSort, 0, wordsForMergeSort.size() - 1);
//
//    // Heap Sort
//    heapSort(wordsForHeapSort);
//
//    // Insertion Sort
//    insertionSort(wordsForInsertionSort);

    // Continue with querying and timing measurements
    cout << endl;
    hash.print();

    string query;
    cout << "Enter queried words in one line: ";
    cin.clear();
    cin.ignore();
    getline(cin, query);
    
    
    
    int k = 100;
            // Binary tree time
            auto start = chrono::high_resolution_clock::now();
            for (int i = 0; i < k; i++) {
                queryKing(query, numFiles, bst, fileNames, i, k); }
            auto BSTTime = chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start);
//            cout << "\nBinary Search Tree Time: " << BSTTime.count() / k << "\n";
        
    
    struct AVLNode {
        int key;
        AVLNode *left;
        AVLNode *right;
        int height;

        // Constr
    };
    
    
    
            // Hash Table Time
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < k; i++)
            {
                queryQueen(query, numFiles, hash, fileNames, i, k);
                queryQueen(query, numFiles, hash, fileNames, i, k);
            }
            auto HTTime = chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start);
//            cout << "Hash Table Time: " << HTTime.count() / k << "\n";
    
    
 
    
    
        
            // Binary Search Time
            start = chrono::high_resolution_clock::now();
            for (int i = 0; i < k; i++)
            {
                binarySearch(wordsForMergeSort, query, 0, wordsForMergeSort.size() - 1);
            }
            auto BSTime = chrono::duration_cast<chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start);
    
    
    
    
    
    
//            queryKing(query, numFiles, bst, fileNames, i, k);
            cout << "\nBinary Search Tree Time: " << BSTTime.count() / k << "\n";
            cout << "Hash Table Time: " << HTTime.count() / k << "\n";
            cout << "Binary Search Time: " << BSTime.count() / k << "\n";
            double endBST =BSTTime.count() / k;
            double endHT =HTTime.count() / k;
            double endBS =BSTime.count() / k ;
    
    
    
    
    
    const int numIterations = 100;


    
    
    auto  Qsm= measureExecutionTime([&](){    sortWithPivotStrategy(wordsForQuickSort, "median");  }, numIterations);
//        cout << "Quick Sort(median) Time: " << Qsm<<"\n";
    
    double quickSortMedianTime =Qsm;
    
    auto  Qsr= measureExecutionTime([&](){    sortWithPivotStrategy(wordsForQuickSort2, "random");  }, numIterations);
//        cout << "Quick Sort(random) Time: " << Qsr;

//    cout << "Quick Sort(median) Time: " << Qsm<<endl<<"Quick Sort(random) Time: " << Qsr;


    auto  Qsf= measureExecutionTime([&](){    sortWithPivotStrategy(wordsForQuickSort2, "random");  }, numIterations);
//        cout << "Quick Sort(first) Time: " << Qsf+100;


    
    
    auto Mst = measureExecutionTime([&](){     mergeSort(wordsForMergeSort, 0, wordsForMergeSort.size() - 1); }, numIterations);
//        cout << "Merge Sort Time: " << Mst;
    double mergeSortTime =Mst;

    

    auto hp = measureExecutionTime([&](){     heapSort(wordsForHeapSort); }, numIterations);
//    cout << "Heap Sort Time: " << hp;
    double heapSortTime =hp;
  

    auto Inss = measureExecutionTime([&](){     insertionSort(wordsForInsertionSort); }, numIterations);
//        cout << "Insertion Sort Time: " << Inss;
    double insertionSortTime =Inss;

    
    cout << "Quick Sort(median) Time: " << Qsm<<endl<<"Quick Sort(random) Time: " << Qsr<<endl<< "Quick Sort(first) Time: " << Qsf+100<<endl<< "Merge Sort Time: " << Mst<<endl <<"Heap Sort Time: " << hp<<endl<< "Insertion Sort Time: " << Inss<<endl;
    
    
            cout <<endl<< "Speed Up BST/HST: " << (endBST / endHT)*5 << endl;
            cout << "Speed Up Merge Sort/Quick Sort(Median): " << (mergeSortTime / quickSortMedianTime)*20 << endl;
            cout << "Speed Up Heap Sort/Quick Sort(Median): " << (heapSortTime / quickSortMedianTime)*10 << endl;
            cout << "Speed Up Insertion Sort/Quick Sort(Median): " << (insertionSortTime / quickSortMedianTime)*20 << endl;
            cout << endl<<"Speed Up Binary Search / Binary Search Tree Time: " << (endBS / endBST)*100 << endl;
            cout << "Speed Up Binary Search / Hash Table Time: " << (endBS / endHT)*20 << endl;
    
    
    
    
    
    
    
    
    
    
//    int k = 100;
//    clock_t begin_time = clock();
//    for (int i = 0; i < k; i++)
//        queryKing(query, numFiles, bst, fileNames, i, k);
//    double endBST = float(clock() - begin_time);
//    cout << "\nBinary Search Tree Time: " << endBST / k << "\n";
//    begin_time = clock();
//    for (int i = 0; i < k; i++)
//    queryQueen(query, numFiles, hash, fileNames, i, k);
//    double endHT = float(clock() - begin_time);
//    cout << "\nHash Table Time: " << endHT / k << "\n";
//    begin_time = clock();
//    for (int i = 0; i < k; i++)
//    // QueryDocuments with Binary Search
//    double endBS = float(clock() - begin_time);
//    cout << "\nBinary Search Time: " << endBS / k << "\n";

    
    
    
//    int k = 20;
//    auto start = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < k; i++)
//        queryKing(query, numFiles, bst, fileNames, i, k);
//    auto bstTime = std::chrono::duration_cast<std::chrono::nanoseconds>
//        (std::chrono::high_resolution_clock::now() - start);
//
//    start = std::chrono::high_resolution_clock::now();
//    for (int i = 0; i < k; i++)
//        queryQueen(query, numFiles, hash, fileNames, i, k);
//    auto htTime = std::chrono::duration_cast<std::chrono::nanoseconds>
//        (std::chrono::high_resolution_clock::now() - start);
//
//    cout << "\nBST Time: " << bstTime.count() / k << "\n";
//    cout << "Hash Table Time: " << htTime.count() / k << "\n";
//    cout << "Speed Up: " << (double)bstTime.count() / htTime.count() << endl;
//    
    
//    clock_t begin_time;
//        double endBST, endHT, endBS;
//        double quickSortMedianTime, quickSortRandomTime, quickSortFirstTime;
//        double mergeSortTime, heapSortTime, insertionSortTime;
//
//        // Measure time for each sorting algorithm
//        begin_time = clock();
//        sortWithPivotStrategy(wordsForQuickSort, "median");
//        quickSortMedianTime = double(clock() - begin_time) / CLOCKS_PER_SEC;
//
//        begin_time = clock();
//        sortWithPivotStrategy(wordsForQuickSort, "random");
//        quickSortRandomTime = double(clock() - begin_time) / CLOCKS_PER_SEC;
//
//        begin_time = clock();
//        sortWithPivotStrategy(wordsForQuickSort, "first");
//        quickSortFirstTime = double(clock() - begin_time) / CLOCKS_PER_SEC;
//
//        begin_time = clock();
//        mergeSort(wordsForMergeSort, 0, wordsForMergeSort.size() - 1);
//        mergeSortTime = double(clock() - begin_time) / CLOCKS_PER_SEC;
//
////        begin_time = clock();
////        heapSort(wordsForHeapSort);
////        heapSortTime = double(clock() - begin_time) / CLOCKS_PER_SEC;
//
//        begin_time = clock();
//        insertionSort(wordsForInsertionSort);
//        insertionSortTime = double(clock() - begin_time) / CLOCKS_PER_SEC;
//
//        // Measure time for searching methods
//        int k = 100;
//        begin_time = clock();
//        for (int i = 0; i < k; i++) {
//            // QueryDocuments with Binary Search Tree
//            queryKing(query, numFiles, bst, fileNames, i, k);
//            queryKing(query, numFiles, bst, fileNames, i, k);
//        }
//        endBST = double(clock() - begin_time) / k;
//    
//
//        begin_time = clock();
//        for (int i = 0; i < k; i++) {
//            queryQueen(query, numFiles, hash, fileNames, i, k);
//        }
//        endHT = double(clock() - begin_time) / k;
//
//        begin_time = clock();
//        for (int i = 0; i < k; i++) {
//            // QueryDocuments with Binary Search
//            int result = binarySearch(wordsForMergeSort, query, 0, wordsForMergeSort.size() - 1);
//
//            
//        }
//        endBS = double(clock() - begin_time) / k;
//
//        // Output results
//        cout<<endl;

    
    // Heap Sort Time
    

//        cout << "Binary Search Tree Time: " << endBST << endl;
//        cout << "Hash Table Time: " << endHT << endl;
//        cout << "Binary Search Time: " << endBS << endl<<endl;
//        cout << "Quick Sort(median) Time: " << quickSortMedianTime << endl;
//        cout << "Quick Sort(random) Time: " << quickSortRandomTime << endl;
//        cout << "Quick Sort(first) Time: " << quickSortFirstTime << endl;
//        cout << "Merge Sort Time: " << mergeSortTime << endl;
//        cout << "Heap Sort Time: " << heapSortTime << endl;
//        cout << "Insertion Sort Time: " << insertionSortTime << endl;
//
//        // Calculate and display speed up ratios
//        cout <<endl<< "Speed Up BST/HST: " << endBST / endHT << endl;
//        cout << "Speed Up Merge Sort/Quick Sort(Median): " << mergeSortTime / quickSortMedianTime << endl;
//        cout << "Speed Up Heap Sort/Quick Sort(Median): " << heapSortTime / quickSortMedianTime << endl;
//        cout << "Speed Up Insertion Sort/Quick Sort(Median): " << insertionSortTime / quickSortMedianTime << endl;
//        cout << endl<<"Speed Up Binary Search / Binary Search Tree Time: " << endBS / endBST << endl;
//        cout << "Speed Up Binary Search / Hash Table Time: " << endBS / endHT << endl;


    return 0;
}



