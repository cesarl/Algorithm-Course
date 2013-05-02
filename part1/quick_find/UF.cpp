#include			"UF.hh"

template			<int N>
void				UF<N>::setUnion(int p, int q)
{
  int				pid = this->list_[p];
  int				qid = this->list_[q];

  for (int i = 0; i < this->size_; ++i)
    {
      if (this->list_[i] == pid)
	{
	  this->list_[i] = qid;
	}
    }
}

template			<int N>
bool				UF<N>::isConnected(int p, int q)
{
  return (this->list_[p] == this->list_[q]);
}
