template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right;
};

template< class T, class Cmp >
const BiTree< T > * find(const BiTree< T >* root, const T & value, Cmp cmp)
{
  if (root == nullptr || !cmp(root->data, value) && !cmp(value, root->data)) {
    return root;
  }
  if (cmp(value, root->data)) {
    return find(root->left, value, cmp);
  } else {
    return find(root->right, value, cmp);
  }
}

int main()
{
  return 0;
}
