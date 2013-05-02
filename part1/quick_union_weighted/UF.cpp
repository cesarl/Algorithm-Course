#include			"UF.hh"

template			<int N>
void				UF<N>::setUnion(int p, int q)
{
  int				i = this->root(p);
  int				j = this->root(q);

  if (this->wg_[i] < this->wg_[j])
    {
      this->list_[i] = j;
      this->wg_[j] += this->wg_[i];
    }
  else
    {
      this->list_[j] = i;
      this->wg_[i] += this->wg_[j];
    }
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
