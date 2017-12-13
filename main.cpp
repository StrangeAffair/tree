#include <iostream>

template<class T, size_t nClindren = 2>
class TreeNode;

template<class T, size_t nChildren>
class TreeNode{
public:
    typedef TreeNode<T, nChildren> _Self;
private:
    _Self* _parent_;
    _Self* _children_[nChildren];
public:
    T value;
private:
    void zero_children();
    void delete_children();
    void delete_this(); //set the pointer in parent Node to zero
public:
    TreeNode(const T& _value_ = T()):
        _parent_(nullptr), value(_value_)
    {zero_children();}
    TreeNode(_Self* parent, const T& _value_ = T()):
        _parent_(parent), value(_value_)
    {zero_children();}
    ~TreeNode()
    {delete_children();}

    static void swap(_Self& left, _Self& right){
        T tmp = left.value;
        left.value = right.value;
        right.value = tmp;
    }

    static _Self* construct(const T& value = T()) {
        return new _Self(value);
    }

    void set_parent(_Self* parent) {_parent_ = parent;}
    void set_child (_Self* child, size_t index)  {
        if (index >= nChildren) return;
        _children_[index] = child;
    }
    _Self* parent()             const {return _parent_;}
    _Self* child (size_t index) const {return _children_[index];}
};

template<class T>
class TreeNode<T, 2>{
public:
    typedef TreeNode<T, 2> _Self;
private:
    _Self* _parent_;
    _Self* _left_;
    _Self* _right_;
public:
    T value;
private:
    //set the pointer in parent Node to zero
    void delete_this() {
        if (_parent_ == nullptr) return;
        if (_parent_->_left_ == this)
            _parent_->_left_ == nullptr;
        else
            _parent_->_right_ == nullptr;
    }
public:
    TreeNode(const T& _value_ = T()):
        _parent_(nullptr), _left_(nullptr), _right_(nullptr), value(_value_)
    {}
    TreeNode(_Self* parent, const T& _value_ = T()):
        _parent_(parent), _left_(nullptr), _right_(nullptr), value(_value_)
    {}
    TreeNode(_Self* parent, _Self* left, _Self* right, const T& _value_ = T()):
        _parent_(parent), _left_(left), _right_(right), value(_value_)
    {}
    ~TreeNode() {
        if (left  != nullptr) delete left;
        if (right != nullptr) delete right;
        delete_this();
    }

    static void swap(_Self& left, _Self& right){
        T tmp = left.value;
        left.value = right.value;
        right.value = tmp;
    }

    static _Self* construct(const T& value = T()) {
        return new _Self(value);
    }

    void set_parent(_Self* parent) {_parent_ = parent;}
    void set_left  (_Self* left)   {_left_   = left;}
    void set_right (_Self* right)  {_right_  = right;}

    _Self* parent() const {return _parent_;}
    _Self*   left() const {return _left_;}
    _Self*  right() const {return _right_;}
};

template<class T, size_t nChildren = 2>
class Tree{
public:
    typedef TreeNode<T, nChildren> Node;
private:
    Node* _head_;
public:
    Tree(): _head_(nullptr) {}
    Tree(const T& head_value): _head_(new Node(head_value)) {}
    Tree(Node* head): _head_(head) {}

    Node* head() {return _head_;}

    static void insert(Node* root_element, Node* element, size_t position){
        if (position >= nChildren) return;
        root_element->child(position) = element;
    }
    static void remove(Node* root_element){
        delete root_element;
    }

    static size_t depth(Node* element){
        size_t counter = -1;
        while(element != nullptr){
            element = element->parent();
            ++counter;
        }
        return counter;
    }
    static Node* lca(Node* first, Node* second){
        size_t h1 = depth(first);
        size_t h2 = depth(second);
        while(h1 > h2){
            first = first->parent();
            --h1;
        }
        while(h2 > h1){
            second = second->parent();
            --h2;
        }
        while(first != second){
            first  =  first->parent();
            second = second->parent();
        }
    }


};

template<class T>
class Tree<T, 2>{
public:
    typedef TreeNode<T, 2> Node;
private:
    Node* _head_;
public:
    Tree(): _head_(nullptr) {}
    Tree(const T& head_value): _head_(new Node(head_value)) {}
    Tree(Node* head): _head_(head) {}

    Node* head() {return _head_;}

    static Node* insert(Node* root_element, Node* element, bool position){
        if (!position)
            root_element->set_left (element);
        else
            root_element->set_right(element);
        return element;
    }
};

int main()
{
    Tree<int> a(10);
    Tree<int>::Node* right = a.insert(a.head(), Tree<int>::Node::construct(5), 1);
    Tree<int>::Node* left  = a.insert(a.head(), Tree<int>::Node::construct(3), 0);
    //cout << "Hello world!" << endl;
    return 0;
}
