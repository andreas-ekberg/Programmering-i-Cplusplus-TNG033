#include "set.h"

// std::size_t is defined in the C++ standard library
// std::size_t is an unsigned integer type that can store the maximum size of any possible object
// sizes are non-negative integers -- i.e. unsigned integer type

// Initialize the counter of the total number of existing nodes
std::size_t Set::Node::count_nodes = 0;

// Used only for debug purposes
// Return number of existing nodes
std::size_t Set::get_count_nodes() {
    return Set::Node::count_nodes;
}

/* ******************************************************** */

// Default constructor
Set::Set()
    //Skapar ett head
    : head(new Node)
{
    //counter som räknar noder = 0
    counter = 0;
}

// Constructor for creating a set from an int
Set::Set(int v) 
    :head(new Node)
{
    counter = 0;
    //Skapar en ny node 
    Node* newNode = new Node;
    //Nodens värde blir v
    newNode->value = v;
    //Den pekar på null (eftersom det bara finns en dummy node
    newNode->next = head->next;
    //Dummy node pekar på newNode
    head->next = newNode;
    counter++;
}

// Constructor: create a set with the elements in V
// V is not sorted and may contain repeated elements
Set::Set(const std::vector<int>& V) 
:head(new Node)
{
    counter = 0;
    Node* newNode = head;
    std::size_t count1 = 0;
    while (count1 < V.size()) {
       //Ifall newNode kommer till slutet av listan
        if (newNode->next == nullptr) {
            Node* lastNode = new Node(V[count1], newNode->next);
            newNode->next = lastNode;
            counter++;
            newNode = head;
            count1++;
        
        }
        //Ifall värdet är mindre än newNodes next
        else if (V[count1] < newNode->next->value) {
            Node* middleNode = new Node(V[count1], newNode->next);
            newNode->next = middleNode;
            counter++;
            newNode = head;
            count1++;
          
        }
        //Värde är detsamma
        else if (newNode->next->value == V[count1]) {
            count1++;
        }
        else {
            newNode = newNode->next;
          
        }

    }
}

// copy constructor
Set::Set(const Set& source) 
:head(new Node)
{
    //pekar på inskickade listan head
    Node* ptr1 = source.head->next;
    //den som ska få kopian
    Node* ptr2 = head;

    while (ptr1 != nullptr) {
        ptr2->next = new Node(ptr1->value, nullptr);

        ptr1 = ptr1->next;
        ptr2 = ptr2->next;

    }
    counter = source.counter;
}

// Assignment operator: copy-and-swap idiom
// Uses the copy constructor and the destructor
Set& Set::operator=(Set s) {
    // ADD CODE
    std::swap(head, s.head);
    std::swap(counter, s.counter);

    return *this;
}

// Destructor: deallocate all nodes
Set::~Set() {
    Node* ptr = head;
    //Tar bort alla pointers
    while (ptr != nullptr) {
        head = head->next;
        delete ptr;
        ptr = head;
    }
    head = nullptr;
}


// Return number of elements in the set
std::size_t Set::cardinality() const {
    // ADD CODE

    return this->counter;  // delete if needed
}

// Test if set is empty
bool Set::empty() const {
    // ADD CODE
    if (this->counter == 0) {
        return true;
    }
    else return false;

}

// Test if x is an element of the set
bool Set::member(int x) const {
    // ADD CODE
    Node* ptr = this->head;
    while (ptr != nullptr) {
        if (ptr->value == x) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;  // delete if needed
}

bool Set::operator<=(const Set& b) const {
    // ADD CODE
    Node* ptr1 = this->head->next;
    int counter = 0;
    while (ptr1 != nullptr) {
        Node* ptr2 = b.head->next;
        while (ptr2 != nullptr) {
            if (ptr1->value == ptr2->value) {
                counter++;
                break;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    if (counter == this->counter) {
        return true;
    }
    else return false;  // delete if needed
}

// S1 == S2: if (S1 <= S2) && (S2 <= S1)
bool Set::operator==(const Set& b) const {
    // ADD CODE
    Node* ptr1 = this->head->next;
    int counter = 0;
    while (ptr1 != nullptr) {
        Node* ptr2 = b.head->next;
        while (ptr2 != nullptr) {
            if (ptr1->value == ptr2->value) {
                counter++;
                break;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    if (counter == this->counter && this->counter == b.counter) {
        return true;
    }
    else return false;  // delete if needed

}

// return (! S1 == S2);
bool Set::operator!=(const Set& b) const {
    // ADD CODE
    Node* ptr1 = this->head->next;
    int counter = 0;
    while (ptr1 != nullptr) {
        Node* ptr2 = b.head->next;
        while (ptr2 != nullptr) {
            if (ptr1->value == ptr2->value) {
                counter++;
                break;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    if (counter == this->counter && this->counter==b.counter) {
        return false;
    }
    else return true;  // delete if needed
}

bool Set::operator<(const Set& b) const {
    // ADD CODE
    Node* ptr1 = this->head->next;
    int counter = 0;
    while (ptr1 != nullptr) {
        Node* ptr2 = b.head->next;
        while (ptr2 != nullptr) {
            if (ptr1->value == ptr2->value) {
                counter++;
                break;
            }
            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
    if (counter == this->counter && this->counter < b.counter) {
        return true;
    }
    else return false;  // delete if needed
  
}

// Set union
// Repeated values are not allowed
Set Set::operator+(const Set& b) const {
    Node* ptr1 = this->head->next;
    Node* ptr2 = b.head->next;
  
    Set newSet{};
    newSet.counter = 0;
    addUnion(ptr1, newSet);
    addUnion(ptr2, newSet);

    Node* ptr = newSet.head;
    return newSet;  // delete if needed
}

// Set intersection
Set Set::operator*(const Set& b) const {
    // ADD CODE
    Set newSet{};
    Node* ptr1 = this->head->next;
    while (ptr1 != nullptr) {
        Node* newNode = newSet.head;
        Node* ptr2 = b.head->next;
        while (ptr2 != nullptr) {
            if (ptr1->value == ptr2->value) {
                Node* insertNode = new Node(ptr2->value, newNode->next);
                newSet.counter++;
                newNode->next = insertNode;
                break;
            }
            ptr2 = ptr2->next;
        }

        ptr1 = ptr1->next;
    }
    Node* ptr = newSet.head;
    return newSet;  // delete if needed
}

// Set difference
Set Set::operator-(const Set& b) const {
    Set newSet{};
    Node* ptr1 = this->head->next;
    while (ptr1 != nullptr) {
        int temp = 0;
        Node* newNode = newSet.head;
        Node* ptr2 = b.head->next;
        while (ptr2 != nullptr) {
            if (ptr1->value != ptr2->value) {
                temp++;
            }
            ptr2 = ptr2->next;
        }
        if (temp == b.counter) {
            Node* insertNode = new Node(ptr1->value, newNode->next);
            newSet.counter++;
            newNode->next = insertNode;
        }
        ptr1 = ptr1->next;
    }
    return newSet;  // delete if needed
}

// set difference with set {x}
Set Set::operator-(int x) const {
    // ADD CODE
    Set tempSet{x};
    Set A = *this - tempSet;
    return Set{A};  // delete if needed
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& os, const Set& theSet) {
    if (theSet.empty()) {
        os << "Set is empty!";
    }
    else {
        Set::Node* temp = theSet.head->next;
        os << "{ ";

        while (temp != nullptr) {
            os << temp->value << " ";
            temp = temp->next;
        }
        os << "}";
    }
    return os;
}



/********** Private member functions ************/

Set Set::addUnion(Node* temp, Set& tempSet) const {

    while (temp != nullptr) {
        Node* newNode = tempSet.head;

        while (newNode != nullptr) {
            //Ifall den blir null så läggs den till längst bak
            if (newNode->next == nullptr) {
                Node* lastNode = new Node(temp->value, newNode->next);
                newNode->next = lastNode;
                tempSet.counter++;
                break;
            }
            //Ifall den är mindre läggs den i mitten
            else if (temp->value < newNode->next->value) {
                Node* middleNode = new Node(temp->value, newNode->next);
                tempSet.counter++;
                newNode->next = middleNode;
                break;
            }
            //Ifall lika hoppa över 
            else if (newNode->next->value == temp->value) {
                break;
            }
            newNode = newNode->next;
        }
        temp = temp->next;
    }
    return tempSet;  // delete if needed


}