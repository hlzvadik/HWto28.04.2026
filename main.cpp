#include <iostream>

//Решение ДЗ начинается с 291 строки

template< class T >
struct BiTree {
  T val;
  BiTree< T >* lt, * rt, * parent;
};

template< class T >
struct BiTreeIt {
  BiTree< T >* curr;
};

template< class T >
T& value(BiTreeIt< T > it)
{
  return it.curr->val;
}

template< class T >
BiTree< T >* minimum(BiTree< T >* root);
template< class T >
BiTree< T >* maximum(BiTree< T >* root);
template< class T >
BiTreeIt< T >* next(BiTreeIt< T > it);
template< class T >
BiTreeIt< T >* prev(BiTreeIt< T > it);
template< class T >
bool hasNext(BiTreeIt< T > it);
template< class T >
bool hasPrev(BiTreeIt< T > it);
template< class T >
std::pair< size_t, BiTree< T >* > fall_left(BiTree< T >* root);
template< class T >
std::pair< size_t, BiTree< T >* > parent(BiTree< T >* root);
template< class T >
std::tuple< Dir, size_t, BiTree< T >* > nextStruct(BiTree< T >* root);
template< class T >
bool isEqualStruct(BiTree< T >* lhs, BiTree< T >* rhs);
template< class T >
bool includedStructRoot(BiTree< T >* lhs_root, BiTree< T >* pattern);
template< class T >
std::tuple< BiTree< T >*, BiTree< T >*, bool> isEqualStructStart(BiTree< T >* lhs_start, BiTree< T >* rhs_start);
template< class T >
bool includedStruct(BiTree<T>* lhs, BiTree<T>* pattern);
template< class T >
std::pair< BiTree<T>*, BiTree<T>* > inclusion(BiTree<T>* lhs, BiTree<T>* pattern);
template< class T >
BiTree< T >* prev(BiTree< T >* curr);


template< class T >
BiTree< T >* minimum(BiTree< T >* root)
{
  if (!root)
  {
    return root;
  }
  while (!root->lt)
  {
    root = root->lt;
  }
  return root;
}

template< class T >
BiTree< T >* maximum(BiTree< T >* root)
{
  if (!root)
  {
    return root;
  }
  while (!root->rt)
  {
    root = root->rt;
  }
  return root;
}

template< class T >
BiTreeIt< T >* next(BiTreeIt< T > it)
{
  BiTree< T >* next = it.curr;
  if (next->rt)
  {
    next = next->rt;
    next = minimum(next);
  }
  else
  {
    BiTree< T >* parent = next->parent;
    while (parent && parent->rt == next)
    {
      next = parent;
      parent = next->parent;
    }
    next = parent;
  }
  return {next};
}

template< class T >
BiTreeIt< T >* prev(BiTreeIt< T > it)
{
  BiTree< T >* next = it.curr;
  if (next->lt)
  {
    next = next->lt;
    next = maximum(next);
   }
  else
  {
    BiTree< T >* parent = next->parent;
    while (parent && parent->lt == next)
    {
      next = parent;
      parent = next->parent;
    }
    next = parent;
  }
  return {next};
}

template< class T >
bool hasNext(BiTreeIt< T > it)
{
  return next(it).curr;
}

template< class T >
bool hasPrev(BiTreeIt< T > it)
{
  return prev(it).curr;
}

enum Dir {fallleft, parent};

template< class T >
std::pair< size_t, BiTree< T >* > fall_left(BiTree< T >* root)
{
  if (!root)
  {
    return {0, nullptr};
  }
  size_t path = 0;
  while (root->lt)
  {
    root = root->lt;
    path++;
  }
  return {path, root};
}

template< class T >
std::pair< size_t, BiTree< T >* > parent(BiTree< T >* root)
{
  if (!root)
  {
    return {0, nullptr};
  }
  size_t path = 0;
  BiTree< T >* parent = root->parent;
  while (parent && parent->lt != root)
  {
    root = parent;
    parent = root->parent;
    path++;
  }
  return {path, parent};
}

template< class T >
std::tuple< Dir, size_t, BiTree< T >* > nextStruct(BiTree< T >* root)
{
  if (root->rt)
  {
    auto result = fall_left(root->rt);
    return (Dir::fallleft, result.first, result.second);
  }
  auto result = parent(root);
  return {Dir::parent, result.first, result.second};
}

template< class T >
bool isEqualStruct(BiTree< T >* lhs, BiTree< T >* rhs)
{
  auto lhs_begin = fallLeft(lhs);
  auto rhs_begin = fallLeft(rhs);
  if (lhs_begin.first != rhs_begin.first) {
    return false;
  }
  auto result = isEqualStructStart(lhs_begin.second, rhs_begin.second);
  return !std::get< 0 >(result) && !std::get< 1 >(result);
}

template< class T >
bool includedStructRoot(BiTree< T >* lhs_root, BiTree< T >* pattern)
{
  auto next_pattern = nextStruct(pattern);
  auto next_lhs;
  if (std::get< 0 >(next_pattern) == Dir::fall_left)
  {
    next_lhs = fall_left(lhs_root);
  }
  else
  {
    next_lhs = parent(lhs_root);
  }
  while (std::get< 1 >(next_pattern) == std::get< 1 >(next_lhs))
}

template< class T >
std::tuple< BiTree< T >*, BiTree< T >*, bool> isEqualStructStart(BiTree< T >* lhs_start, BiTree< T >* rhs_start)
{
  auto ln = nextStruct(lhs_start);
  auto rn = nextStruct(rhs_start);
  while (std::get< 0 >(ln) == std::get< 0 >(rn) &&
      std::get< 1 >(ln) == std::get< 1 >(rn) &&
      std::get< 2 >(ln) && std::get< 2 >(rn)) {
    ln = nextStruct(std::get< 2 >(ln));
    rn = nextStruct(std::get< 2 >(rn));
  }
  bool dir = std::get< 0 >(ln) == std::get< 0 >(rn) && std::get< 1 >(ln) == std::get< 1 >(rn);
  return {std::get< 2 >(ln), std::get< 2 >(rn), dir};
}

template< class T >
bool includedStruct(BiTree<T>* lhs, BiTree<T>* pattern)
{
  BiTree< T >* lhs = fallLeft(lhs).second;
  while (lhs) {
    auto result = isEqualStructStart(lhs, fallLeft(pattern).second));
    if (!std::get< 1 >(result) && std::get< 2 >(result)) {
      return true;
    }
    lhs = nextStruct(lhs).second;
  }
  return false;
}

template< class T >
std::pair< BiTree<T>*, BiTree<T>* > inclusion(BiTree<T>* lhs, BiTree<T>* pattern)
{
  BiTree< T >* lhs_curr = fall_left(lhs).second;
  while (lhs_curr) {
    auto result = isEqualStructStart(lhs_curr, fallLeft(pattern).second));
    if (!std::get< 1 >(result) && std::get< 2 >(result)) {
      BiTree< T >* last_lhs_next = std::get< 0 >(result);
      if (!last_lhs_next) {
        // lhs тоже закончился, нам нужен последний элемент
        BiTree< T >* lhs_end = lhs;
        while (lhs_end->rt) {
          lhs_end = lhs_end->rt;
        }
        return {lhs_curr, lhs_end};
      }
      BiTree< T >* lhs_end = prev(last_lhs_next);
      return {lhs_curr, lhs_end};
    }
    lhs_curr = nextStruct(lhs_curr).second;
  }
  return {nullptr, nullptr};
}

template< class T >
BiTree< T >* prev(BiTree< T >* curr)
{
  BiTree< T >* next = curr;
  if (next->lt) {
    next = next->lt;
    while (next->rt) {
      next = next->tr;
    }
  } else {
    BiTree< T >* parent = next->parent;
    while (parent && parent->rt != next) {
      next = parent;
      parent = next->parent;
    }
    next = parent;
  }
  return next;
}

//========Решение ДЗ с итераторами. Все, что выше было дано ранее========

template< class T >
std::pair< BiTree<T>*, BiTree<T>* > inclusionStart(BiTree<T>* lhs, BiTree<T>* pattern)
{
  BiTree< T >* lhs_curr = lhs;
  while (lhs_curr) {
    auto result = isEqualStructStart(lhs_curr, fallLeft(pattern).second));
    if (!std::get< 1 >(result) && std::get< 2 >(result)) {
      BiTree< T >* last_lhs_next = std::get< 0 >(result);
      if (!last_lhs_next) {
        // lhs тоже закончился, нам нужен последний элемент
        BiTree< T >* lhs_end = lhs;
        while (lhs_end->rt) {
          lhs_end = lhs_end->rt;
        }
        return {lhs_curr, lhs_end};
      }
      BiTree< T >* lhs_end = prev(last_lhs_next);
      return {lhs_curr, lhs_end};
    }
    lhs_curr = nextStruct(lhs_curr).second;
  }
  return {nullptr, nullptr};
}


template< class T > struct InclusionIt {
  std::pair< BiTree<T>*, BiTree<T>* > incl;
};

template< class T >
InclusionIt<T> begin(BiTree<T>* lhs, BiTree<T>* pattern)
{
  auto result = inclusion(lhs, pattern);
  return {{result.first, result.second}};
}

template< class T >
InclusionIt<T> next(InclusionIt<T> curr, BiTree< T >* pattern)
{
  auto result = inclusionStart(next(curr.second), pattern);
  return {{result.first, result.second}};
}

template< class T >
bool hasNext(InclusionIt<T> curr, BiTree< T >* pattern)
{
  auto result = inclusionStart(next(curr.second), pattern);
  return result.first == nullptr;
}


int main()
{}
