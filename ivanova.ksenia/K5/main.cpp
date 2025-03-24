#include <iostream>
#include <limits>

template<class T>
struct BiTree
{
  T data;
  BiTree<T>* left;
  BiTree<T>* right;
};

bool compare(int a, int b)
{
    return a < b;
}

template<class T, class Cmp>
const BiTree<T>* find(const BiTree<T>* root, const T& value, Cmp cmp)
{
  if (!root)
  {
    return nullptr;
  }
  if (cmp(value, root->data))
  {
    root = root->left;
  }
  else if (cmp(root->data, value))
  {
    root = root->right;
  }
  else
  {
    return root;
  }
}

template<class T, class Cmp>
void insert(BiTree<T>*& root, const T& value, Cmp cmp)
{
  if (!root)
  {
    root = new BiTree<T>{value, nullptr, nullptr};
    return;
  }
  if (cmp(value, root->data))
  {
    root = root->left;
  }
  else
  {
    root = root->right;
  }
}

template<class T>
void clear(BiTree<T>* root)
{
  if (!root)
  {
    return;
  }
  clear(root->left);
  clear(root->right);
  delete root;
}

int main()
{
  auto cmp = [](int a, int b) { return a < b; };

  BiTree<int>* root = nullptr;

  int length;
  if (!(std::cin >> length))
  {
    std::cerr << "Failed to read the length of the sequence." << '\n';
    return 1;
  }
  for (int i = 0; i < length; ++i)
  {
    int value;
    if (!(std::cin >> value))
    {
      std::cerr << "Failed to read an element of the sequence." << '\n';
      clear(root);
      return 1;
    }
    insert(root, value, compare);
  }

  int searchValue;
  while (std::cin >> searchValue)
  {
    const BiTree<int>* result = find(root, searchValue, compare);
    if (result != nullptr)
    {
      std::cout << "<FOUND>" << '\n';
    }
    else
    {
      std::cout << "<NOT FOUND>" << '\n';
    }
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    std::cerr << "Invalid input." << '\n';
    clear(root);
    return 1;
  }

  clear(root);
  return 0;
}