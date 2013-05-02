#ifndef			UF_H_
# define		UF_H_

#include		<iostream>

template		<int N>
class UF
{
public:
  UF<N>() :
  size_(N)
  {
    for (int i = 0; i < N; ++i)
      {
	this->list_[i] = i;
	this->wg_[i] = 1;
      }
  }

  ~UF<N>()
  {}
  void			setUnion(int p, int q);
  bool			isConnected(int p, int q);
  int			findRoot(int i);
private:
  int			size_;
  unsigned int		list_[N];
  unsigned int		wg_[N];
};

#endif			/* !UF_H_ */

