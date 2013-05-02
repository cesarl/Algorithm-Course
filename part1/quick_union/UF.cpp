#include			"UF.hh"

template			<int N>
void				UF<N>::setUnion(int p, int q)
{
  int				i = this->root(p);
  int				j = this->root(q);
  this->list_[i] = j;
}

template			<int N>
bool				UF<N>::isConnected(int p, int q)
{
  return (this->findRoot(p) == this->findRoot(q));
}

template			<int N>
int				UF<N>::findRoot(int i)
{
  while (i != this->list_[i])
    i = this->list_[i];
  return i;
}
