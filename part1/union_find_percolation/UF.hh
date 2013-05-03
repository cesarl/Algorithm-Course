#ifndef			UF_H_
# define		UF_H_

#include		<allegro5/allegro.h>
#include		<allegro5/allegro_native_dialog.h>
#include		<allegro5/allegro_primitives.h>
#include		<iostream>

# define		WIN_S 1000

template		<int N>
class UF
{
public:
  UF<N>() :
  size_(N)
  {
    //////////////////
    // allegro init //
    //////////////////
    this->display_ = NULL;
    if (!al_init())
      {
	al_show_native_message_box(NULL, NULL, NULL, "Failed to initialize allegro !\n", NULL, 0);
	abort();
      }
    this->display_ = al_create_display(WIN_S, WIN_S);
    if (!this->display_)
      {
	al_show_native_message_box(NULL, NULL, NULL, "Failed to initialize display !\n", NULL, 0);;
	abort();
      }
    al_init_primitives_addon();
    ///////////////
    // init data //
    ///////////////
    for (int i = 0; i < N * N + 2; ++i)
      {
	this->list_[i] = i;
	this->open_[i] = -1;
	this->wg_[i] = 1;
      }
    this->cellSize_ = WIN_S / N;
    this->open_[N * N] = 0;
    this->open_[N * N + 1] = 0;
    srand(time(NULL));
  }

  ~UF<N>()
  {
    al_shutdown_primitives_addon();
    al_destroy_display(this->display_);
  }


  void			setUnion(int p, int q)
  {
    int			i = this->findRoot(p);
    int			j = this->findRoot(q);

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
  }

  bool			isConnected(int p, int q)
  {
    return (this->findRoot(p) == this->findRoot(q));
  }


  int			findRoot(int i)
  {
    while (i != this->list_[i])
      {
	i = this->list_[i];
      }
    return i;
  }



  bool			open(int x, int y)
  {
    int			p = y * this->size_ + x;

    if (this->open_[p] != -1)
      return false;
    this->open_[p] = 0;

    // union left
    if (x > 0 && this->open_[p - 1] != -1)
      this->setUnion(p, p - 1);

    // union right
    if (x < this->size_ - 1 && this->open_[p + 1] != -1)
      this->setUnion(p, p + 1);

    // union up
    if (y > 0 && this->open_[p - this->size_] != -1)
      this->setUnion(p, p - this->size_);

    // union down
    if (y < this->size_ - 1 && this->open_[p + this->size_] != -1)
      this->setUnion(p, p + this->size_);

    // union start
    if (y == 0)
      this->setUnion(p, this->size_ * this->size_);

    // union end
    if (y == this->size_ - 1)
      this->setUnion(p, this->size_ * this->size_ + 1);

    return true;
  }


  void			draw()
  {
    int			x;
    int			y;

    al_clear_to_color(al_map_rgb(54, 210, 65));
    for (int i = 0; i < this->size_ * this->size_; ++i)
      {
	x = (i % this->size_) * this->cellSize_;
	y = (i / this->size_) * this->cellSize_;
	if (this->open_[i] == -1)
	  {
	    al_draw_filled_rectangle(x,
				     y,
				     x + this->cellSize_,
				     y + this->cellSize_,
				     al_map_rgb(0, 0, 0));
	    continue;
	  }
	else if (this->isConnected(i, this->size_ * this->size_))
	  {
	    al_draw_filled_rectangle(x,
				     y,
				     x + this->cellSize_,
				     y + this->cellSize_,
				     al_map_rgb(50, 10, 255));
	    continue;
	  }
	al_draw_filled_rectangle(x,
				 y,
				 x + this->cellSize_,
				 y + this->cellSize_,
				 al_map_rgb(255, 255, 255));
      }
    al_flip_display();
  }


  void			run(bool display = false)
  {
    while (!this->isConnected(this->size_ * this->size_, this->size_ * this->size_ + 1))
      {
	while (!this->open(rand() % this->size_, rand() % this->size_))
	  ;
	if (display)
	  this->draw();
      }
    this->draw();
    al_rest(6);
  }
private:
  int			size_;
  int			list_[N * N + 2];
  int			open_[N * N + 2];
  unsigned int		wg_[N * N + 2];
  float			cellSize_;
  ALLEGRO_DISPLAY	*display_;
};

#endif			/* !UF_H_ */

