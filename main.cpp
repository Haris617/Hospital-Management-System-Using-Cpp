#include <iostream>
#include <string>
using namespace std;


// ============ ENUMS AND CONSTANTS ============
enum PriorityLevel {
    EMERGENCY = 1,
    CRITICAL = 2,
    NON_CRITICAL = 3
};

// ============ MANUAL VECTOR IMPLEMENTATION ============
template <typename T>
class Vector {
private:
    T* arr;
    int cap;
    int sz;

    void resize() {
        cap *= 2;
        T* temp = new T[cap];
        for (int i = 0; i < sz; i++) {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }

public:
    Vector() : cap(10), sz(0) {
        arr = new T[cap];
    }

    ~Vector() {
        delete[] arr;
    }

    void push_back(const T& val) {
        if (sz == cap) resize();
        arr[sz++] = val;
    }

    T& operator[](int idx) { return arr[idx]; }
    const T& operator[](int idx) const { return arr[idx]; }
    int size() const { return sz; }
    bool empty() const { return sz == 0; }

    void clear() { sz = 0; }

    T* begin() { return arr; }
    T* end() { return arr + sz; }
    const T* begin() const { return arr; }
    const T* end() const { return arr + sz; }
};

// ============ PATIENT RECORD CLASS ============
class PatientRecord {
private:
    int patientID;
    string name;
    int age;
    string medicalCondition;
    PriorityLevel priority;
    string admissionDate;
    string physicianAssigned;
    bool isDeleted;

public:
    PatientRecord() : patientID(0), age(0), priority(NON_CRITICAL), isDeleted(false) {}

    PatientRecord(int id, string n, int a, string cond,
        PriorityLevel p, string date, string doc)
        : patientID(id), name(n), age(a), medicalCondition(cond),
        priority(p), admissionDate(date), physicianAssigned(doc), isDeleted(false) {
    }

    int getPatientID() const { return patientID; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getMedicalCondition() const { return medicalCondition; }
    PriorityLevel getPriority() const { return priority; }
    string getAdmissionDate() const { return admissionDate; }
    string getPhysicianAssigned() const { return physicianAssigned; }
    bool getIsDeleted() const { return isDeleted; }

    void setPatientID(int id) { patientID = id; }
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setMedicalCondition(string cond) { medicalCondition = cond; }
    void setPriority(PriorityLevel p) { priority = p; }
    void setAdmissionDate(string date) { admissionDate = date; }
    void setPhysicianAssigned(string doc) { physicianAssigned = doc; }
    void markDeleted() { isDeleted = true; }

    void display() const {
        string priorityStr;
        switch (priority) {
        case EMERGENCY: priorityStr = "EMERGENCY"; break;
        case CRITICAL: priorityStr = "CRITICAL"; break;
        case NON_CRITICAL: priorityStr = "NON_CRITICAL"; break;
        }

        cout << "ID: " << patientID
            << ", Name: " << name
            << ", Age: " << age
            << ", Condition: " << medicalCondition
            << ", Priority: " << priorityStr
            << ", Admission: " << admissionDate
            << ", Physician: " << physicianAssigned;
        if (isDeleted) cout << " [DELETED]";
        cout << endl;
    }

    static bool validatePriority(int p) {
        return p >= 1 && p <= 3;
    }

    static bool validateDate(const string& date) {
        return date.length() == 10 && date[4] == '-' && date[7] == '-';
    }
};

// ============ BST NODE STRUCTURE ============
struct BSTNode {
    PatientRecord data;
    BSTNode* left;
    BSTNode* right;
    int height;

    BSTNode(PatientRecord patient)
        : data(patient), left(NULL), right(NULL), height(1) {
    }
};

// ============ QUEUE FOR TREE TRAVERSAL ============
template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(NULL) {}
    };

    Node* front;
    Node* rear;
    int sz;

public:
    Queue() : front(NULL), rear(NULL), sz(0) {}

    ~Queue() {
        while (!empty()) pop();
    }

    void push(T val) {
        Node* newNode = new Node(val);
        if (rear == NULL) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        sz++;
    }

    void pop() {
        if (empty()) return;
        Node* temp = front;
        front = front->next;
        if (front == NULL) rear = NULL;
        delete temp;
        sz--;
    }

    T getFront() const { return front->data; }
    bool empty() const { return front == NULL; }
    int size() const { return sz; }
};

// ============ BASE BST CLASS ============
class PatientBST {
protected:
    BSTNode* root;
    int sz;

    int max(int a, int b) const {
        return (a > b) ? a : b;
    }

    int getHeight(BSTNode* node) const {
        return node ? node->height : 0;
    }

    virtual BSTNode* insertHelper(BSTNode* node, PatientRecord patient) {
        if (!node) return new BSTNode(patient);

        if (patient.getPatientID() < node->data.getPatientID()) {
            node->left = insertHelper(node->left, patient);
        }
        else {
            node->right = insertHelper(node->right, patient);
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return node;
    }

    BSTNode* findMin(BSTNode* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    virtual BSTNode* deleteHelper(BSTNode* node, int patientID) {
        if (!node) return NULL;

        if (patientID < node->data.getPatientID()) {
            node->left = deleteHelper(node->left, patientID);
        }
        else if (patientID > node->data.getPatientID()) {
            node->right = deleteHelper(node->right, patientID);
        }
        else {
            if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteHelper(node->right, temp->data.getPatientID());
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return node;
    }

    BSTNode* searchHelper(BSTNode* node, int patientID) const {
        if (!node || node->data.getPatientID() == patientID) return node;
        if (patientID < node->data.getPatientID())
            return searchHelper(node->left, patientID);
        return searchHelper(node->right, patientID);
    }

    void inOrderHelper(BSTNode* node, Vector<PatientRecord>& result) const {
        if (!node) return;
        inOrderHelper(node->left, result);
        if (!node->data.getIsDeleted()) result.push_back(node->data);
        inOrderHelper(node->right, result);
    }

    void clearHelper(BSTNode* node) {
        if (!node) return;
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
    }

public:
    PatientBST() : root(NULL), sz(0) {}
    virtual ~PatientBST() { clear(); }

    virtual void insert(PatientRecord patient) {
        if (search(patient.getPatientID())) {
            cout << "Error: Patient ID " << patient.getPatientID() << " already exists!\n";
            return;
        }
        root = insertHelper(root, patient);
        sz++;
    }

    virtual void remove(int patientID) {
        PatientRecord* found = search(patientID);
        if (!found) {
            cout << "Patient with ID " << patientID << " not found!\n";
            return;
        }
        root = deleteHelper(root, patientID);
        sz--;
    }

    PatientRecord* search(int patientID) const {
        BSTNode* result = searchHelper(root, patientID);
        return (result && !result->data.getIsDeleted()) ? &result->data : NULL;
    }

    Vector<PatientRecord> inOrderTraversal() const {
        Vector<PatientRecord> result;
        inOrderHelper(root, result);
        return result;
    }

    bool isEmpty() const { return !root; }
    int getSize() const { return sz; }

    void clear() {
        clearHelper(root);
        root = NULL;
        sz = 0;
    }

    int getHeightValue() const {
        return getHeight(root);
    }

    void displayTree() const {
        if (!root) {
            cout << "Tree is empty!\n";
            return;
        }

        Queue<BSTNode*> q;
        q.push(root);
        int level = 0;

        while (!q.empty()) {
            int levelSize = q.size();
            cout << "Level " << level << ": ";

            for (int i = 0; i < levelSize; i++) {
                BSTNode* current = q.getFront();
                q.pop();

                cout << current->data.getPatientID()
                    << "(" << (current->data.getIsDeleted() ? "D" : "A") << ") ";

                if (current->left) q.push(current->left);
                if (current->right) q.push(current->right);
            }
            cout << endl;
            level++;
        }
    }

    Vector<PatientRecord> searchByAgeRange(int minAge, int maxAge) const {
        Vector<PatientRecord> allPatients = inOrderTraversal();
        Vector<PatientRecord> result;

        for (int i = 0; i < allPatients.size(); i++) {
            if (allPatients[i].getAge() >= minAge && allPatients[i].getAge() <= maxAge) {
                result.push_back(allPatients[i]);
            }
        }
        return result;
    }

    Vector<PatientRecord> searchByCondition(const string& condition) const {
        Vector<PatientRecord> allPatients = inOrderTraversal();
        Vector<PatientRecord> result;

        for (int i = 0; i < allPatients.size(); i++) {
            if (allPatients[i].getMedicalCondition().find(condition) != string::npos) {
                result.push_back(allPatients[i]);
            }
        }
        return result;
    }

    Vector<PatientRecord> searchByPriority(PriorityLevel priority) const {
        Vector<PatientRecord> allPatients = inOrderTraversal();
        Vector<PatientRecord> result;

        for (int i = 0; i < allPatients.size(); i++) {
            if (allPatients[i].getPriority() == priority) {
                result.push_back(allPatients[i]);
            }
        }
        return result;
    }

    int countPatientsByPriority(PriorityLevel priority) const {
        Vector<PatientRecord> allPatients = inOrderTraversal();
        int count = 0;

        for (int i = 0; i < allPatients.size(); i++) {
            if (allPatients[i].getPriority() == priority) {
                count++;
            }
        }
        return count;
    }

    double calculateAveragePriority() const {
        Vector<PatientRecord> allPatients = inOrderTraversal();
        if (allPatients.empty()) return 0.0;

        double sum = 0.0;
        for (int i = 0; i < allPatients.size(); i++) {
            sum += allPatients[i].getPriority();
        }
        return sum / allPatients.size();
    }
};

// ============ AVL TREE CLASS ============
class PatientAVL : public PatientBST {
private:
    int abs(int x) const {
        return x < 0 ? -x : x;
    }

    BSTNode* rotateRight(BSTNode* y) {
        BSTNode* x = y->left;
        BSTNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    BSTNode* rotateLeft(BSTNode* x) {
        BSTNode* y = x->right;
        BSTNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    int getBalanceFactor(BSTNode* node) const {
        if (!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    BSTNode* balanceNode(BSTNode* node) {
        if (!node) return NULL;

        int balance = getBalanceFactor(node);

        if (balance > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }

        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    BSTNode* insertHelperAVL(BSTNode* node, PatientRecord patient) {
        if (!node) return new BSTNode(patient);

        if (patient.getPatientID() < node->data.getPatientID()) {
            node->left = insertHelperAVL(node->left, patient);
        }
        else {
            node->right = insertHelperAVL(node->right, patient);
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return balanceNode(node);
    }

    BSTNode* deleteHelperAVL(BSTNode* node, int patientID) {
        if (!node) return NULL;

        if (patientID < node->data.getPatientID()) {
            node->left = deleteHelperAVL(node->left, patientID);
        }
        else if (patientID > node->data.getPatientID()) {
            node->right = deleteHelperAVL(node->right, patientID);
        }
        else {
            if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            BSTNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteHelperAVL(node->right, temp->data.getPatientID());
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return balanceNode(node);
    }

    bool checkBalanced(BSTNode* node) const {
        if (!node) return true;

        int balance = getBalanceFactor(node);
        if (abs(balance) > 1) return false;

        return checkBalanced(node->left) && checkBalanced(node->right);
    }

public:
    PatientAVL() : PatientBST() {}

    void insert(PatientRecord patient) {
        if (search(patient.getPatientID())) {
            cout << "Error: Patient ID " << patient.getPatientID() << " already exists!\n";
            return;
        }
        root = insertHelperAVL(root, patient);
        sz++;
    }

    void remove(int patientID) {
        PatientRecord* found = search(patientID);
        if (!found) {
            cout << "Patient with ID " << patientID << " not found!\n";
            return;
        }
        root = deleteHelperAVL(root, patientID);
        sz--;
    }

    bool isBalanced() const {
        return checkBalanced(root);
    }
};

// ============ PATIENT HISTORY MANAGER ============
class PatientHistoryManager {
private:
    Vector<PatientRecord> dischargedPatients;

public:
    void addToHistory(const PatientRecord& patient) {
        dischargedPatients.push_back(patient);
    }

    PatientRecord* searchHistory(int patientID) {
        for (int i = 0; i < dischargedPatients.size(); i++) {
            if (dischargedPatients[i].getPatientID() == patientID) {
                return &dischargedPatients[i];
            }
        }
        return NULL;
    }

    void displayHistory() const {
        cout << "\n=== DISCHARGED PATIENT HISTORY ===" << endl;
        for (int i = 0; i < dischargedPatients.size(); i++) {
            dischargedPatients[i].display();
        }
        cout << "Total: " << dischargedPatients.size() << " patients\n";
    }
};

// ============ SORTING ALGORITHMS ============
class PatientSorter {
public:
    static void swap(PatientRecord& a, PatientRecord& b) {
        PatientRecord temp = a;
        a = b;
        b = temp;
    }

    static int partitionByPriority(Vector<PatientRecord>& patients, int low, int high) {
        int pivot = patients[high].getPriority();
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (patients[j].getPriority() <= pivot) {
                i++;
                swap(patients[i], patients[j]);
            }
        }
        swap(patients[i + 1], patients[high]);
        return i + 1;
    }

    static void quickSortByPriority(Vector<PatientRecord>& patients, int low, int high) {
        if (low < high) {
            int pi = partitionByPriority(patients, low, high);
            quickSortByPriority(patients, low, pi - 1);
            quickSortByPriority(patients, pi + 1, high);
        }
    }

    static void mergeByDate(Vector<PatientRecord>& patients, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        PatientRecord* L = new PatientRecord[n1];
        PatientRecord* R = new PatientRecord[n2];

        for (int i = 0; i < n1; i++)
            L[i] = patients[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = patients[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (L[i].getAdmissionDate() <= R[j].getAdmissionDate()) {
                patients[k] = L[i];
                i++;
            }
            else {
                patients[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            patients[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            patients[k] = R[j];
            j++;
            k++;
        }

        delete[] L;
        delete[] R;
    }

    static void mergeSortByDate(Vector<PatientRecord>& patients, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortByDate(patients, left, mid);
            mergeSortByDate(patients, mid + 1, right);
            mergeByDate(patients, left, mid, right);
        }
    }
};

// ============ HOSPITAL MANAGEMENT SYSTEM ============
class HospitalManagementSystem {
private:
    PatientBST* idBST;
    PatientAVL* priorityAVL;
    PatientHistoryManager historyManager;

public:
    HospitalManagementSystem() {
        idBST = new PatientBST();
        priorityAVL = new PatientAVL();
        loadSampleData();
    }

    ~HospitalManagementSystem() {
        delete idBST;
        delete priorityAVL;
    }

    void loadSampleData() {
        PatientRecord p1(101, "John Doe", 45, "Heart Attack", EMERGENCY, "2024-01-15", "Dr. Smith");
        PatientRecord p2(102, "Jane Smith", 32, "Broken Arm", CRITICAL, "2024-01-16", "Dr. Johnson");
        PatientRecord p3(103, "Bob Wilson", 67, "Diabetes", NON_CRITICAL, "2024-01-14", "Dr. Williams");
        PatientRecord p4(104, "Alice Brown", 28, "Pneumonia", CRITICAL, "2024-01-17", "Dr. Smith");
        PatientRecord p5(105, "Charlie Davis", 55, "Stroke", EMERGENCY, "2024-01-18", "Dr. Johnson");

        idBST->insert(p1);
        idBST->insert(p2);
        idBST->insert(p3);
        idBST->insert(p4);
        idBST->insert(p5);

        priorityAVL->insert(p1);
        priorityAVL->insert(p2);
        priorityAVL->insert(p3);
        priorityAVL->insert(p4);
        priorityAVL->insert(p5);

        cout << "Sample data loaded with 5 patients." << endl;
    }

    void admitPatient() {
        PatientRecord patient;
        int id, age, priorityInt;
        string name, condition, physician, date;

        cout << "\n=== ADMIT NEW PATIENT ===" << endl;

        cout << "Enter Patient ID: ";
        cin >> id;
        patient.setPatientID(id);

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        patient.setName(name);

        cout << "Enter Age: ";
        cin >> age;
        patient.setAge(age);

        cout << "Enter Medical Condition: ";
        cin.ignore();
        getline(cin, condition);
        patient.setMedicalCondition(condition);

        cout << "Enter Priority (1=Emergency, 2=Critical, 3=Non-Critical): ";
        cin >> priorityInt;
        patient.setPriority(static_cast<PriorityLevel>(priorityInt));

        cout << "Enter Admission Date (YYYY-MM-DD): ";
        cin >> date;
        patient.setAdmissionDate(date);

        cout << "Enter Assigned Physician: ";
        cin.ignore();
        getline(cin, physician);
        patient.setPhysicianAssigned(physician);

        idBST->insert(patient);
        priorityAVL->insert(patient);

        cout << "\nPatient admitted successfully!" << endl;
        patient.display();
    }

    void searchPatient() {
        int id;
        cout << "\nEnter Patient ID to search: ";
        cin >> id;

        PatientRecord* patient = idBST->search(id);
        if (patient) {
            cout << "\nPatient found:" << endl;
            patient->display();
        }
        else {
            cout << "Patient not found!" << endl;
        }
    }

    void dischargePatient() {
        int id;
        cout << "\n=== DISCHARGE PATIENT ===" << endl;
        cout << "Enter Patient ID to discharge: ";
        cin >> id;

        PatientRecord* patient = idBST->search(id);
        if (patient) {
            cout << "Discharging patient:" << endl;
            patient->display();

            historyManager.addToHistory(*patient);
            idBST->remove(id);
            priorityAVL->remove(id);

            cout << "Patient discharged successfully!" << endl;
        }
        else {
            cout << "Patient not found!" << endl;
        }
    }

    void displayAllPatients() {
        cout << "\n=== ALL PATIENTS (Sorted by ID) ===" << endl;
        Vector<PatientRecord> patients = idBST->inOrderTraversal();
        displayPatientList(patients);
    }

    void displayByPriority() {
        cout << "\n=== PATIENTS BY PRIORITY ===" << endl;

        cout << "\nEMERGENCY PATIENTS:" << endl;
        Vector<PatientRecord> emergency = idBST->searchByPriority(EMERGENCY);
        displayPatientList(emergency);

        cout << "\nCRITICAL PATIENTS:" << endl;
        Vector<PatientRecord> critical = idBST->searchByPriority(CRITICAL);
        displayPatientList(critical);

        cout << "\nNON-CRITICAL PATIENTS:" << endl;
        Vector<PatientRecord> noncritical = idBST->searchByPriority(NON_CRITICAL);
        displayPatientList(noncritical);
    }

    void displayTrees() {
        cout << "\n=== ID BST STRUCTURE ===" << endl;
        idBST->displayTree();

        cout << "\n=== PRIORITY AVL STRUCTURE ===" << endl;
        priorityAVL->displayTree();
    }

    void displayStatistics() {
        cout << "\n=== HOSPITAL STATISTICS ===" << endl;
        cout << "Total Patients: " << idBST->getSize() << endl;
        cout << "Tree Height (ID BST): " << idBST->getHeightValue() << endl;
        cout << "Tree Height (Priority AVL): " << priorityAVL->getHeightValue() << endl;
        cout << "AVL Tree Balanced: " << (priorityAVL->isBalanced() ? "Yes" : "No") << endl;

        cout << "\nPatients by Priority:" << endl;
        cout << "Emergency: " << idBST->countPatientsByPriority(EMERGENCY) << endl;
        cout << "Critical: " << idBST->countPatientsByPriority(CRITICAL) << endl;
        cout << "Non-Critical: " << idBST->countPatientsByPriority(NON_CRITICAL) << endl;

        cout << "\nAverage Priority: " << idBST->calculateAveragePriority() << endl;
    }

    void sortPatients() {
        Vector<PatientRecord> patients = idBST->inOrderTraversal();

        cout << "\n=== SORT PATIENTS ===" << endl;
        cout << "1. Sort by Priority (Quick Sort)" << endl;
        cout << "2. Sort by Admission Date (Merge Sort)" << endl;
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            if (!patients.empty()) {
                PatientSorter::quickSortByPriority(patients, 0, patients.size() - 1);
                cout << "\nPatients sorted by priority:" << endl;
                displayPatientList(patients);
            }
        }
        else if (choice == 2) {
            if (!patients.empty()) {
                PatientSorter::mergeSortByDate(patients, 0, patients.size() - 1);
                cout << "\nPatients sorted by admission date:" << endl;
                displayPatientList(patients);
            }
        }
    }

    void displayHistory() {
        historyManager.displayHistory();
    }

private:
    void displayPatientList(const Vector<PatientRecord>& patients) {
        if (patients.empty()) {
            cout << "No patients found!" << endl;
            return;
        }

        for (int i = 0; i < patients.size(); i++) {
            patients[i].display();
        }
        cout << "Total: " << patients.size() << " patients" << endl;
    }
};

// ============ MAIN FUNCTION ============
int main() {
    HospitalManagementSystem hospital;

    cout << "=========================================" << endl;
    cout << "   HOSPITAL PATIENT MANAGEMENT SYSTEM    " << endl;
    cout << "=========================================" << endl;

    int choice;
    do {
        cout << "\n=== MAIN MENU ===" << endl;
        cout << "1. Admit New Patient" << endl;
        cout << "2. Search Patient" << endl;
        cout << "3. Discharge Patient" << endl;
        cout << "4. Display All Patients" << endl;
        cout << "5. Display Patients by Priority" << endl;
        cout << "6. Display Tree Structures" << endl;
        cout << "7. Display Statistics" << endl;
        cout << "8. Sort Patients" << endl;
        cout << "9. View Discharged Patients History" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            hospital.admitPatient();
            break;
        case 2:
            hospital.searchPatient();
            break;
        case 3:
            hospital.dischargePatient();
            break;
        case 4:
            hospital.displayAllPatients();
            break;
        case 5:
            hospital.displayByPriority();
            break;
        case 6:
            hospital.displayTrees();
            break;
        case 7:
            hospital.displayStatistics();
            break;
        case 8:
            hospital.sortPatients();
            break;
        case 9:
            hospital.displayHistory();
            break;
        case 0:
            cout << "\nExiting system. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 0);

    return 0;
}
