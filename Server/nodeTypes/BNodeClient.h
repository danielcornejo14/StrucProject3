#pragma once

#include <iostream>
#include <utility>

using namespace std;
// A BTreeClients node

class ClientData {
public:
    explicit ClientData(){
        this->name = "";
        this->email = "";
        this->phoneNumber = "";
        this->cityCode = "";
        this->amountSpent = 0;
        this->billingCount = 0;
    }

    explicit ClientData(string name, string cityCode, string phoneNumber, string email){
        this->name = name;
        this->email = email;
        this->phoneNumber = phoneNumber;
        this->cityCode = cityCode;
        this->amountSpent = 0;
        this->billingCount = 0;
    }

    const string &getName() const;

    void setName(const string &name);

    const string &getEmail() const;

    void setEmail(const string &email);

    const string &getPhoneNumber() const;

    void setPhoneNumber(const string &phoneNumber);

    const string &getCityCode() const;

    void setCityCode(const string &cityCode);

    float getAmountSpent() const;

    void setAmountSpent(float amountSpent);

    int getBillingCount() const;

    void setBillingCount(int billingCount);

    void incBillingCount();




private:
    string name;
    string email;
    string cityCode;
    string phoneNumber;
    float amountSpent;
    int billingCount;
};

float ClientData::getAmountSpent() const {
    return amountSpent;
}

void ClientData::setAmountSpent(float amountSpent) {
    ClientData::amountSpent = amountSpent;
}

int ClientData::getBillingCount() const {
    return billingCount;
}

void ClientData::setBillingCount(int billingCount) {
    ClientData::billingCount = billingCount;
}

const string &ClientData::getName() const {
    return name;
}

void ClientData::setName(const string &name) {
    ClientData::name = name;
}

const string &ClientData::getEmail() const {
    return email;
}

void ClientData::setEmail(const string &email) {
    ClientData::email = email;
}

const string &ClientData::getPhoneNumber() const {
    return phoneNumber;
}

void ClientData::setPhoneNumber(const string &phoneNumber) {
    ClientData::phoneNumber = phoneNumber;
}

const string &ClientData::getCityCode() const {
    return cityCode;
}

void ClientData::setCityCode(const string &cityCode) {
    ClientData::cityCode = cityCode;
}

class BTreeNode{
private:
    int *keys; // An array of keys
    int t;	 // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;	 // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
    ClientData *clientDataArray;




public:
    BTreeNode(int t1, bool leaf1); // Constructor

    // A function that returns the index of the first key that is greater
    // or equal to k
    int findKey(int k);

    // A utility function to insert a new key in the subtree rooted with
    // this node. The assumption is, the node must be non-full when this
    // function is called
    void insertNonFull(int k, ClientData clientData);

    // A utility function to split the child y of this node. i is index of y in
    // child array C[]. The Child y must be full when this function is called
    void splitChild(int i, BTreeNode *y);

    // A function to traverse all nodes in a subtree rooted with this node
    void traverse();

    // A wrapper function to remove the key k in subtree rooted with
    // this node.
    void remove(int k);

    // A function to remove the key present in idx-th position in
    // this node which is a leaf
    void removeFromLeaf(int idx);

    // A function to remove the key present in idx-th position in
    // this node which is a non-leaf node
    void removeFromNonLeaf(int idx);

    // A function to get the predecessor of the key- where the key
    // is present in the idx-th position in the node
    int getPred(int idx);
    ClientData getPredClient(int idx);

    // A function to get the successor of the key- where the key
    // is present in the idx-th position in the node
    int getSucc(int idx);
    ClientData getSuccClient(int idx);

    // A function to fill up the child node present in the idx-th
    // position in the C[] array if that child has less than t-1 keys
    void fill(int idx);

    // A function to borrow a key from the C[idx-1]-th node and place
    // it in C[idx]th node
    void borrowFromPrev(int idx);

    // A function to borrow a key from the C[idx+1]-th node and place it
    // in C[idx]th node
    void borrowFromNext(int idx);

    // A function to merge idx-th child of the node with (idx+1)th child of
    // the node
    void merge(int idx);

    // A function to search a key in the subtree rooted with this node.
    BTreeNode *search(int k); // returns NULL if k is not present.
    ClientData searchClient(int k);
    void getHighestBoughtValue(float &mostBoughtValue);
    void getMostBoughtValue(int &mostBoughtValue);
    void getLowestBoughtValue(float &leastBoughtValue);
    void getLeastBoughtValue(int &fewestBoughtValue);
    void generateMostExpensiveBill(float &highestBoughtValue, ofstream &outfile);
    void generateMostBilledClient(int &mostBoughtValue, ofstream &outfile);
    void generateLeastExpensiveBill(float &leastBoughtValue, ofstream &outfile);
    void generateLeastBilledClient(int &fewestBoughtValue, ofstream &outfile);
    void generateClients(ofstream &outfile);

// Make BTreeClients friend of this so that we can access private members of this
// class in BTreeClients functions
    friend class BTreeClients;
};

// Constructor for BTreeNode class
BTreeNode::BTreeNode(int t1, bool leaf1)
{
    // Copy the given minimum degree and leaf property
    t = t1;
    leaf = leaf1;

    // Allocate memory for maximum number of possible keys
    // and child pointers
    keys = new int[2*t-1];
    clientDataArray = new ClientData[2*t-1];
    C = new BTreeNode *[2*t];

    // Initialize the number of keys as 0
    n = 0;
}

// Function to traverse all nodes in a subtree rooted with this node
void BTreeNode::traverse()
{
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++){
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!leaf)
            C[i]->traverse();
        cout << " " << keys[i] <<"["<<clientDataArray[i].getName()<<","<<clientDataArray[i].getCityCode()<<","<<clientDataArray[i].getPhoneNumber()<<","<<clientDataArray[i].getEmail()<<","<<clientDataArray[i].getBillingCount()<<","<<clientDataArray[i].getAmountSpent()<<"]" << endl;
    }

    // Print the subtree rooted with last child
    if (!leaf)
        C[i]->traverse();
}

// Function to search key k in subtree rooted with this node
BTreeNode *BTreeNode::search(int k)
{
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // If the found key is equal to k, return this node
    if (keys[i] == k)
        return this;

    // If key is not found here and this is a leaf node
    if (leaf)
        return nullptr;

    // Go to the appropriate child
    return C[i]->search(k);
}

ClientData BTreeNode::searchClient(int k) {
    // Find the first key greater than or equal to k
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    // If the found key is equal to k, return this node
    if (keys[i] == k)
        return clientDataArray[i];

    // If key is not found here and this is a leaf node
    if (leaf){
        cout << "C MAMO" << endl;
        return ClientData("ERROR", "ERROR", "ERROR", "ERROR");
    }

    // Go to the appropriate child
    return C[i]->searchClient(k);
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTreeNode::insertNonFull(int k, ClientData clientData)
{
    // Initialize index as index of rightmost element
    int i = n-1;

    // If this is a leaf node
    if (leaf)
    {
        // The following loop does two things
        // a) Finds the location of new key to be inserted
        // b) Moves all greater keys to one place ahead
        while (i >= 0 && keys[i] > k)
        {
            clientDataArray[i+1] = clientDataArray[i];
            keys[i+1] = keys[i];
            i--;
        }

        // Insert the new key at found location
        keys[i+1] = k;
        clientDataArray[i+1] = clientData;
        n = n+1;
    }
    else // If this node is not leaf
    {
        // Find the child which is going to have the new key
        while (i >= 0 && keys[i] > k)
            i--;

        // See if the found child is full
        if (C[i+1]->n == 2*t-1)
        {
            // If the child is full, then split it
            splitChild(i+1, C[i+1]);

            // After split, the middle key of C[i] goes up and
            // C[i] is splitted into two. See which of the two
            // is going to have the new key
            if (keys[i+1] < k)
                i++;
        }
        C[i+1]->insertNonFull(k, clientData);
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTreeNode::splitChild(int i, BTreeNode *y)
{
    // Create a new node which is going to store (t-1) keys
    // of y
    auto *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    // Copy the last (t-1) keys of y to z
    for (int j = 0; j < t-1; j++){
        z->keys[j] = y->keys[j+t];
        z->clientDataArray[j]=y->clientDataArray[j+t];
    }

    // Copy the last t children of y to z
    if (!y->leaf)
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }

    // Reduce the number of keys in y
    y->n = t - 1;

    // Since this node is going to have a new child,
    // create space of new child
    for (int j = n; j >= i+1; j--)
        C[j+1] = C[j];

    // Link the new child to this node
    C[i+1] = z;

    // A key of y will move to this node. Find the location of
    // new key and move all greater keys one space ahead
    for (int j = n-1; j >= i; j--){
        keys[j+1] = keys[j];
        clientDataArray[j+1] = clientDataArray[j];
    }

    // Copy the middle key of y to this node
    keys[i] = y->keys[t-1];
    clientDataArray[i] = y->clientDataArray[t-1];

    // Increment count of keys in this node
    n = n + 1;
}

void ClientData::incBillingCount() {
    billingCount++;
}

void BTreeNode::getHighestBoughtValue(float &highestBoughtValue) {
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!leaf)
            C[i]->traverse();
        //cout << " " << keys[i];
        auto tmpClient = searchClient(keys[i]);
        if(tmpClient.getAmountSpent()>=highestBoughtValue){
            highestBoughtValue = tmpClient.getAmountSpent();
        }
    }

    // Print the subtree rooted with last child
    if (!leaf)
        C[i]->traverse();
}

void BTreeNode::getMostBoughtValue(int &mostBoughtValue) {
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!leaf)
            C[i]->traverse();
        auto tmpClient = searchClient(keys[i]);
        if(tmpClient.getBillingCount() >= mostBoughtValue){
            mostBoughtValue = tmpClient.getBillingCount();
        }
    }

    // Print the subtree rooted with last child
    if (!leaf)
        C[i]->traverse();
}

void BTreeNode::generateMostExpensiveBill(float &highestBoughtValue, ofstream &outfile) {
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!leaf)
            C[i]->traverse();
        auto tmpClient = searchClient(keys[i]);
        if(tmpClient.getAmountSpent()>=highestBoughtValue){
            outfile << "Client Id: " << keys[i] << " Client Name: " << tmpClient.getName() << " Amount spent: " << tmpClient.getAmountSpent() << endl;
        }
    }

    // Print the subtree rooted with last child
    if (!leaf)
        C[i]->traverse();
}

void BTreeNode::generateMostBilledClient(int &mostBoughtValue, ofstream &outfile) {
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!leaf)
            C[i]->traverse();
        auto tmpClient = searchClient(keys[i]);
        if(tmpClient.getBillingCount() >= mostBoughtValue){
            outfile << "Client Id: " << keys[i] << " Client Name: " << tmpClient.getName() << " Billing count: " << tmpClient.getBillingCount() << endl;
        }
    }

    // Print the subtree rooted with last child
    if (!leaf)
        C[i]->traverse();
}

void BTreeNode::getLowestBoughtValue(float &leastBoughtValue) {
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!leaf)
            C[i]->traverse();
        auto tmpClient = searchClient(keys[i]);
        if(tmpClient.getAmountSpent() <= leastBoughtValue){
            leastBoughtValue = tmpClient.getAmountSpent();
        }
    }

    // Print the subtree rooted with last child
    if (!leaf)
        C[i]->traverse();
}

void BTreeNode::generateLeastExpensiveBill(float &leastBoughtValue, ofstream &outfile) {
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!leaf)
            C[i]->traverse();
        auto tmpClient = searchClient(keys[i]);
        if(tmpClient.getAmountSpent()<=leastBoughtValue){
            outfile << "Client Id: " << keys[i] << " Client Name: " << tmpClient.getName() << " Amount spent: " << tmpClient.getAmountSpent() << endl;
        }
    }

    // Print the subtree rooted with last child
    if (!leaf)
        C[i]->traverse();
}

void BTreeNode::generateClients(ofstream &outfile) {
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!leaf)
            C[i]->traverse();
        auto tmpClient = searchClient(keys[i]);
        outfile << "Client Id: " << keys[i] << " Client Name: " << tmpClient.getName() << " Amount spent: " << tmpClient.getAmountSpent() << endl;
    }

    // Print the subtree rooted with last child
    if (!leaf)
        C[i]->traverse();
}

void BTreeNode::getLeastBoughtValue(int &fewestBoughtValue) {
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!leaf)
            C[i]->traverse();
        auto tmpClient = searchClient(keys[i]);
        if(tmpClient.getBillingCount() <= fewestBoughtValue){
            fewestBoughtValue = tmpClient.getBillingCount();
        }
    }

    // Print the subtree rooted with last child
    if (!leaf)
        C[i]->traverse();
}

void BTreeNode::generateLeastBilledClient(int &fewestBoughtValue, ofstream &outfile) {
    // There are n keys and n+1 children, travers through n keys
    // and first n children
    int i;
    for (i = 0; i < n; i++)
    {
        // If this is not leaf, then before printing key[i],
        // traverse the subtree rooted with child C[i].
        if (!leaf)
            C[i]->traverse();
        auto tmpClient = searchClient(keys[i]);
        if(tmpClient.getAmountSpent()<=fewestBoughtValue){
            outfile << "Client Id: " << keys[i] << " Client Name: " << tmpClient.getName() << " Amount spent: " << tmpClient.getAmountSpent() << endl;
        }
    }

    // Print the subtree rooted with last child
    if (!leaf)
        C[i]->traverse();
}

// A utility function that returns the index of the first key that is
// greater than or equal to k
int BTreeNode::findKey(int k)
{
    int idx=0;
    while (idx<n && keys[idx] < k)
        ++idx;
    return idx;
}

// A function to remove the key k from the sub-tree rooted with this node
void BTreeNode::remove(int k)
{
    int idx = findKey(k);

    // The key to be removed is present in this node
    if (idx < n && keys[idx] == k)
    {

        // If the node is a leaf node - removeFromLeaf is called
        // Otherwise, removeFromNonLeaf function is called
        if (leaf)
            removeFromLeaf(idx);
        else
            removeFromNonLeaf(idx);
    }
    else
    {

        // If this node is a leaf node, then the key is not present in tree
        if (leaf)
        {
            cout << "The key "<< k <<" is does not exist in the tree\n";
            return;
        }

        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ( (idx==n)? true : false );

        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (C[idx]->n < t)
            fill(idx);

        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && idx > n)
            C[idx-1]->remove(k);
        else
            C[idx]->remove(k);
    }
    return;
}

// A function to remove the idx-th key from this node - which is a leaf node
void BTreeNode::removeFromLeaf (int idx)
{

    // Move all the keys after the idx-th pos one place backward
    for (int i=idx+1; i<n; ++i) {
        keys[i - 1] = keys[i];
        clientDataArray[i - 1] = clientDataArray[i];
    }

    // Reduce the count of keys
    n--;

    return;
}

// A function to remove the idx-th key from this node - which is a non-leaf node
void BTreeNode::removeFromNonLeaf(int idx)
{

    int k = keys[idx];

    // If the child that precedes k (C[idx]) has atleast t keys,
    // find the predecessor 'pred' of k in the subtree rooted at
    // C[idx]. Replace k by pred. Recursively delete pred
    // in C[idx]
    if (C[idx]->n >= t)
    {
        int pred = getPred(idx);
        ClientData predAdmin = getPredClient(idx);
        keys[idx] = pred;
        clientDataArray[idx] = predAdmin;
        C[idx]->remove(pred);
    }

        // If the child C[idx] has less that t keys, examine C[idx+1].
        // If C[idx+1] has atleast t keys, find the successor 'succ' of k in
        // the subtree rooted at C[idx+1]
        // Replace k by succ
        // Recursively delete succ in C[idx+1]
    else if  (C[idx+1]->n >= t)
    {
        int succ = getSucc(idx);
        ClientData succAdmin = getSuccClient(idx);
        keys[idx] = succ;
        clientDataArray[idx] = succAdmin;
        C[idx+1]->remove(succ);
    }

        // If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
        // into C[idx]
        // Now C[idx] contains 2t-1 keys
        // Free C[idx+1] and recursively delete k from C[idx]
    else
    {
        merge(idx);
        C[idx]->remove(k);
    }
    return;
}

// A function to get predecessor of keys[idx]
int BTreeNode::getPred(int idx)
{
    // Keep moving to the right most node until we reach a leaf
    BTreeNode *cur=C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    // Return the last key of the leaf
    return cur->keys[cur->n-1];
}

// A function to get predecessor of adminData[idx]
ClientData BTreeNode::getPredClient(int idx)
{
    // Keep moving to the right most node until we reach a leaf
    BTreeNode *cur=C[idx];
    while (!cur->leaf)
        cur = cur->C[cur->n];

    // Return the last key of the leaf
    return cur->clientDataArray[cur->n-1];
}

ClientData BTreeNode::getSuccClient(int idx){

    // Keep moving the left most node starting from C[idx+1] until we reach a leaf
    BTreeNode *cur = C[idx+1];
    while (!cur->leaf)
        cur = cur->C[0];

    // Return the first key of the leaf
    return cur->clientDataArray[0];
}

int BTreeNode::getSucc(int idx)
{

    // Keep moving the left most node starting from C[idx+1] until we reach a leaf
    BTreeNode *cur = C[idx+1];
    while (!cur->leaf)
        cur = cur->C[0];

    // Return the first key of the leaf
    return cur->keys[0];
}

// A function to fill child C[idx] which has less than t-1 keys
void BTreeNode::fill(int idx)
{

    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    // from that child
    if (idx!=0 && C[idx-1]->n>=t)
        borrowFromPrev(idx);

        // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
        // from that child
    else if (idx!=n && C[idx+1]->n>=t)
        borrowFromNext(idx);

        // Merge C[idx] with its sibling
        // If C[idx] is the last child, merge it with with its previous sibling
        // Otherwise merge it with its next sibling
    else
    {
        if (idx != n)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}

// A function to borrow a key from C[idx-1] and insert it
// into C[idx]
void BTreeNode::borrowFromPrev(int idx)
{

    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx-1];

    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in C[idx]. Thus, the  loses
    // sibling one key and child gains one key

    // Moving all key in C[idx] one step ahead
    for (int i=child->n-1; i>=0; --i) {
        child->keys[i + 1] = child->keys[i];
        child->clientDataArray[i+1] = child->clientDataArray[i];
    }


    // If C[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->leaf)
    {
        for(int i=child->n; i>=0; --i)
            child->C[i+1] = child->C[i];
    }

    // Setting child's first key equal to keys[idx-1] from the current node
    child->keys[0] = keys[idx-1];
    child->clientDataArray[0] = clientDataArray[idx-1];

    // Moving sibling's last child as C[idx]'s first child
    if(!child->leaf)
        child->C[0] = sibling->C[sibling->n];

    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    keys[idx-1] = sibling->keys[sibling->n-1];
    clientDataArray[idx-1] = sibling->clientDataArray[sibling->n-1];

    child->n += 1;
    sibling->n -= 1;

    return;
}

// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
void BTreeNode::borrowFromNext(int idx)
{

    BTreeNode *child=C[idx];
    BTreeNode *sibling=C[idx+1];

    // keys[idx] is inserted as the last key in C[idx]
    child->keys[(child->n)] = keys[idx];
    child->clientDataArray[(child->n)] = clientDataArray[idx];

    // Sibling's first child is inserted as the last child
    // into C[idx]
    if (!(child->leaf))
        child->C[(child->n)+1] = sibling->C[0];

    //The first key from sibling is inserted into keys[idx]
    keys[idx] = sibling->keys[0];
    clientDataArray[idx] = sibling->clientDataArray[0];

    // Moving all keys in sibling one step behind
    for (int i=1; i<sibling->n; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
        sibling->clientDataArray[i - 1] = sibling->clientDataArray[i];
    }

    // Moving the child pointers one step behind
    if (!sibling->leaf)
    {
        for(int i=1; i<=sibling->n; ++i)
            sibling->C[i-1] = sibling->C[i];
    }

    // Increasing and decreasing the key count of C[idx] and C[idx+1]
    // respectively
    child->n += 1;
    sibling->n -= 1;

    return;
}

// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
void BTreeNode::merge(int idx)
{
    BTreeNode *child = C[idx];
    BTreeNode *sibling = C[idx+1];

    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[idx]
    child->keys[t-1] = keys[idx];
    child->clientDataArray[t-1] = clientDataArray[idx];

    // Copying the keys from C[idx+1] to C[idx] at the end
    for (int i=0; i<sibling->n; ++i) {
        child->keys[i + t] = sibling->keys[i];
        child->clientDataArray[i + t] = sibling->clientDataArray[i];
    }


    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->leaf)
    {
        for(int i=0; i<=sibling->n; ++i)
            child->C[i+t] = sibling->C[i];
    }

    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to C[idx]
    for (int i=idx+1; i<n; ++i) {
        keys[i - 1] = keys[i];
        clientDataArray[i - 1] = clientDataArray[i];
    }

    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i=idx+2; i<=n; ++i)
        C[i-1] = C[i];

    // Updating the key count of child and the current node
    child->n += sibling->n+1;
    n--;

    // Freeing the memory occupied by sibling
    delete(sibling);
    return;
}