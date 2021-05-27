#pragma once

#include <assert.h>
#include <stddef.h>

struct heap_node
{
    struct heap_node* parent;
    struct heap_node* left;
    struct heap_node* right;
};

typedef int (*heap_compare_fn)(const struct heap_node* lhs, const struct heap_node* rhs);

struct heap
{
    struct heap_node* root;
    int nelts;
    //if compare is less_than, root is min of heap
    //if compare is larger_than, root is max of heap
    heap_compare_fn compare;
};

static inline void heap_init(struct heap* heap, heap_compare_fn fn)
{
    heap->root = NULL;
    heap->nelts = 0;
    heap->compare = fn;
}

/*
*
*  parent                     parent
*    |                           |
*    s                           r
*  /   \                       /    \
*left  rigth                 left   right
*/

//replace s with r
static inline void heap_replace(struct heap* heap, struct heap_node* s, struct heap_node* r)
{
    if(s->parent == NULL)
    {
        heap->root = r;
    }
    else if(s->parent->left == s)
    {
        s->parent->left = r;
    }
    else if(s->parent->right == s)
    {
        s->parent->right = r;
    }

    if(s->left)
    {
        s->left->parent = r;
    }
    if(s->right)
    {
        s->right->parent = r;
    }
    if(r)
    {
        r->parent = s->parent;
        r->left = s->left;
        r->right = s->right;
    }
}
/*
*
*         PPARENT = NULL                 
*           |                         
*         parent                         
*        /      \                  
*      left     child   
*     /    \    /   \
*    L      R Lch    Rch
*              
*/
static inline void heap_swap(struct heap* heap, struct heap_node* parent, struct heap_node* child)
{
    assert(child->parent == parent && (parent->left == child || parent->right == child));
    struct heap_node* pparent = parent->parent;
    struct heap_node* lchild = child->left;
    struct heap_node* rchild = child->right;
    struct heap_node* sibling = NULL;

    if(pparent == NULL)
    {
        heap->root = child;
    }
    else if(pparent->left == parent)
    {
        pparent->left = child;
    }
    else if(pparent->right == parent)
    {
        pparent->right = child;
    }

    if(lchild)
    {
        lchild->parent = parent;
    }
    if(rchild)
    {
        rchild->parent = parent;
    }
    child->parent = pparent;
    if(parent->left == child)
    {
        sibling = parent->right;
        child->left = parent;
        child->right = sibling;
    }
    else
    {
        sibling = parent->left;
        child->right = parent;
        child->left = sibling;
    }
    if(sibling)
    {
        sibling->parent = child;
    }
    parent->left = lchild;
    parent->right = rchild;
    parent->parent = child;
}

static inline void heap_insert(struct heap* heap, struct heap_node* node)
{
    //get last => insert node = > sift up
    //0 : left, 1: right
    int path = 0;
    int n = 0;
    int d = 0; //depth 0~n
    ++heap->nelts;
    //traverse from botton to up, get path of last node
    //这里计算插入点的位置：
    //插入时要抓住子节点序号 / 2 =父节点序号的特点，所以n >> 1相当于n/2，如果插入点是右子树，该节点最后一个bit一定是1
    //插入节点是左子树，该节点值最后一bit为0，这里for循环通过n >> 1依次计算出父节点的坐标，比如插入点为7（7-3-1）
    //d用来记录树的深度，path则记录该节点坐标为左子节点还是右子节点。比如插入点坐标为7 (0001-0011)这样就是根节点的右子树的右子树
    for(d = 0, n = heap->nelts; n >= 2; ++d, n >>= 1)
    {
        path = (path << 1) | (n & 1);
    }

    //get last->parent by path
    struct heap_node* parent = heap->root;
    while (d > 1) // d - 2,because root is 0, insert node is d
    {
        parent = (path & 1) ? parent->right : parent->left;
        --d;
        path >>= 1;
    }
    // insert node
    node->parent = parent;
    if(parent == NULL)
    {
        heap->root = node;
    }
    else if(path & 1)
    {
        parent->right = node;
    }
    else
    {
        parent->left = node;
    }
    if(heap->compare)
    {
        while(node->parent && heap->compare(node, node->parent))
        {
            heap_swap(heap, node->parent, node);
        }
    }
}

static inline void heap_remove(struct heap* heap, struct heap_node* node)
{
    if(heap->nelts == 0)
    {
        return;
    }
    //get last ==> replace with last ==> sift down and sift up
    // 0: left, 1: right
    int path = 0;
    int n = 0;
    int d = 0;
    //step1: calculate path
    for(d = 0, n = heap->nelts; n >= 2; ++d, n >>= 1)
    {
        path = (path << 1) | (n & 1);
    }
    -- heap->nelts;

    //get last parent by path
    //step2: get last parent by path
    struct heap_node* parent = heap->root;
    while(d > 1)
    {
        parent = (path & 1) ? parent->right : parent->left;
        --d;
        path >>= 1;
    }
    //replce node with last
    //step3: get last node and replase tit to target node
    struct heap_node* last = NULL;
    if(parent == NULL)
    {
        return;
    }
    else if(path & 1)
    {
        last = parent->right;
        parent->right = NULL;
    }
    else
    {
        last = parent->left;
        parent->left = NULL;
    }
    if(last == NULL)
    {
        if(heap->root == node)
        {
            heap->root = NULL;
        }
        return;
    }
    heap_replace(heap, node, last);
    node->parent = node->left = node->right = NULL;

    if(!heap->compare)
    {
        return;
    }
    struct heap_node* v = last;
    struct heap_node* est = NULL;
    // sift down
    while(true)
    {
        est = v;
        if(v->left)
        {
            est = heap->compare(est, v->left) ? est : v->left;
        }
        if(v->right)
        {
            est = heap->compare(est, v->right) ? est : v->right;
        }
        if(est == v)
        {
            break;
        }
        heap_swap(heap, v, est);
    }
    //sift up
    while(v->parent && heap->compare(v, v->parent))
    {
        heap_swap(heap, v->parent, v);
    }
}

static inline void heap_dequeue(struct heap* heap)
{
    heap_remove(heap, heap->root);
}