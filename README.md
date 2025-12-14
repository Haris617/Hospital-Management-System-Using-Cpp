# 🏥 Hospital Patient Management System

A comprehensive C++ hospital management system implementing advanced data structures (BST, AVL Tree, Queue) from scratch without using STL containers. Built as an educational project demonstrating fundamental computer science concepts.

## ✨ Features

### Core Functionality
- 📝 **Patient Admission** - Register new patients with complete medical information
- 🔍 **Advanced Search** - Find patients by ID with O(log n) complexity
- 🚪 **Patient Discharge** - Remove patients and maintain discharge history
- 📊 **Statistics & Analytics** - Real-time hospital statistics and priority distribution
- 🗂️ **Priority Management** - Three-tier priority system (Emergency, Critical, Non-Critical)

### Data Structures Implemented
- 🌲 **Binary Search Tree (BST)** - Primary patient storage by ID
- ⚖️ **AVL Tree** - Self-balancing tree for optimized searches
- 📋 **Queue** - Level-order tree traversal
- 📦 **Dynamic Vector** - Custom resizable array implementation

### Algorithms
- ⚡ **Quick Sort** - Sort patients by priority level
- 🔀 **Merge Sort** - Sort patients by admission date
- 🔎 **Binary Search** - Efficient patient lookup
- 🔄 **Tree Rotations** - AVL balancing operations

## 🎯 Key Highlights

- ✅ **Pure C++ Implementation** - Uses only `<iostream>` and `<string>`
- ✅ **No STL Containers** - All data structures built from scratch
- ✅ **Educational Focus** - Clear code structure for learning
- ✅ **Memory Safe** - Proper memory management with destructors
- ✅ **Extensible Design** - Object-oriented architecture

## 🚀 Getting Started

### Prerequisites
- C++ compiler (GCC 4.8+, Clang 3.4+, or MSVC 2015+)
- Basic understanding of C++ and data structures

### Installation

1. **Clone the repository**
```bash
git clone https://github.com/yourusername/hospital-management-system.git
cd hospital-management-system
```

2. **Compile the program**
```bash
g++ -o hospital main.cpp
```

3. **Run the application**
```bash
./hospital
```

For Windows:
```bash
g++ -o hospital.exe main.cpp
hospital.exe
```

## 📖 Usage

### Main Menu Options
```
=== MAIN MENU ===
1. Admit New Patient
2. Search Patient
3. Discharge Patient
4. Display All Patients
5. Display Patients by Priority
6. Display Tree Structures
7. Display Statistics
8. Sort Patients
9. View Discharged Patients History
0. Exit
```

### Sample Workflow

#### 1. Admit a Patient
```
Enter Patient ID: 106
Enter Name: Sarah Johnson
Enter Age: 42
Enter Medical Condition: Asthma
Enter Priority (1=Emergency, 2=Critical, 3=Non-Critical): 2
Enter Admission Date (YYYY-MM-DD): 2024-12-14
Enter Assigned Physician: Dr. Williams
```

#### 2. Search Patient
```
Enter Patient ID to search: 106

Patient found:
ID: 106, Name: Sarah Johnson, Age: 42, Condition: Asthma, 
Priority: CRITICAL, Admission: 2024-12-14, Physician: Dr. Williams
```

#### 3. View Statistics
```
=== HOSPITAL STATISTICS ===
Total Patients: 6
Tree Height (ID BST): 3
Tree Height (Priority AVL): 2
AVL Tree Balanced: Yes

Patients by Priority:
Emergency: 2
Critical: 3
Non-Critical: 1

Average Priority: 1.83
```

## 🏗️ Project Structure
```
hospital-management-system/
├── main.cpp                 # Complete source code
├── README.md               # Project documentation
└── .gitignore             # Git ignore file
```

## 📚 Data Structures Explained

### Binary Search Tree (BST)
- Stores patients ordered by Patient ID
- Average case: O(log n) search, insert, delete
- Worst case: O(n) for skewed trees

### AVL Tree
- Self-balancing BST maintaining height balance
- Guaranteed O(log n) operations
- Uses rotation operations for balancing
- Balance factor: height(left) - height(right) ∈ {-1, 0, 1}

### Custom Vector
- Dynamic array with automatic resizing
- Doubles capacity when full
- O(1) amortized append operation

### Queue (Linked List Based)
- FIFO data structure
- Used for level-order tree traversal
- O(1) enqueue and dequeue operations

## 🎓 Learning Outcomes

This project demonstrates:
- **Data Structure Implementation** - Building fundamental structures from scratch
- **Algorithm Design** - Implementing sorting and searching algorithms
- **Memory Management** - Manual allocation and deallocation
- **Object-Oriented Programming** - Classes, inheritance, polymorphism
- **Tree Operations** - Insertions, deletions, rotations, balancing
- **Complexity Analysis** - Understanding time and space complexity

## 🔧 Code Structure

### Main Classes

#### `PatientRecord`
Stores patient information including ID, name, age, medical condition, priority, admission date, and assigned physician.

#### `PatientBST`
Binary Search Tree implementation for patient storage with insert, search, and delete operations.

#### `PatientAVL`
Self-balancing AVL Tree extending BST with automatic balancing through rotations.

#### `Vector<T>`
Custom dynamic array implementation with automatic resizing.

#### `Queue<T>`
Linked-list based FIFO queue for tree traversal.

#### `HospitalManagementSystem`
Main system class coordinating all operations and user interactions.

## 📊 Complexity Analysis

| Operation | BST | AVL Tree |
|-----------|-----|----------|
| Search | O(log n) avg, O(n) worst | O(log n) |
| Insert | O(log n) avg, O(n) worst | O(log n) |
| Delete | O(log n) avg, O(n) worst | O(log n) |
| Space | O(n) | O(n) |

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 🙏 Acknowledgments

- Inspiration from real-world hospital management systems
- Data structures and algorithms course materials
- Open source community

## 📞 Contact

Have questions or suggestions? Feel free to reach out!

- Email: toughrider617@gmail.com

---

⭐️ If you found this project helpful, please consider giving it a star!
