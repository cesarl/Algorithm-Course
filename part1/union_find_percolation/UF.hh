#ifndef			UF_H_
# define		UF_H_

#include		<allegro5/allegro.h>
#include		<allegro5/allegro_native_dialog.h>
#include		<allegro5/allegro_primitives.h>
#include		<iostream>

# define		WIN_S 1000.0f

template		<int N>
class UF
{
public:
  UF<N>(bool improved = false) :
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
    this->start_ = N * N;
    this->end_ = N * N + 1;
    this->improved_ = improved;
    if (!(this->list_ = new int[N * N + 2])
	|| !(this->wg_ = new unsigned int[N * N + 2])
	|| !(this->open_ = new unsigned int[N * N + 2]))
      {
	std::cout << "Out of memory" << std::endl;
      }
    for (int i = 0; i < this->end_ + 1; ++i)
      {
	this->list_[i] = i;
	this->open_[i] = 0;
	this->wg_[i] = 1;
      }
    this->cellSize_ =  WIN_S / N;
    this->open_[this->start_] = 1;
    this->open_[this->end_] = 1;
    srand(time(NULL));
  }

  ~UF<N>()
  {
    delete this->list_;
    delete this->wg_;
    delete this->open_;
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
	if (this->improved_)
	  i = this->list_[this->list_[i]];
	else
	  i = this->list_[i];
      }
    return i;
  }

  bool			open(int x, int y)
  {
    int			p = y * this->size_ + x;

    if (this->open_[p])
      return false;
    this->open_[p] = 1;

    // union left
    if (x > 0 && this->open_[p - 1])
      this->setUnion(p, p - 1);

    // union right
    if (x < this->size_ - 1 && this->open_[p + 1])
      this->setUnion(p, p + 1);

    // union up
    if (y > 0 && this->open_[p - this->size_])
      this->setUnion(p, p - this->size_);

    // union down
    if (y < this->size_ - 1 && this->open_[p + this->size_])
      this->setUnion(p, p + this->size_);

    // union start
    if (y == 0)
      this->setUnion(p, this->start_);

    // union end
    if (y == this->size_ - 1)
      this->setUnion(p, this->end_);

    return true;
  }


  void			draw()
  {
    int			x;
    int			y;

    for (int i = 0; i < this->start_; ++i)
      {
	x = (i % this->size_) * this->cellSize_;
	y = (i / this->size_) * this->cellSize_;

	if (!this->open_[i])
	  {
	    al_draw_filled_rectangle(x, y, x + this->cellSize_, y + this->cellSize_, al_map_rgb(0, 0, 0));
	    continue;
	  }
	else if (this->isConnected(i, this->start_))
	  {
	    al_draw_filled_rectangle(x, y, x + this->cellSize_, y + this->cellSize_, al_map_rgb(50, 10, 255));
	    continue;
	  }
	al_draw_filled_rectangle(x, y, x + this->cellSize_, y + this->cellSize_, al_map_rgb(255, 255, 255));
      }
    al_flip_display();
  }


  void			run(bool display = false)
  {
    double		time = al_get_time();

    while (!this->isConnected(this->start_, this->end_))
      {
	while (!this->open(rand() % this->size_, rand() % this->size_))
	  ;
	if (display)
	  this->draw();
      }
    std::cout << "Map of " << this->size_ << " generated and calcutated in " << al_get_time() - time << " !" << std::endl;
    if (this->size_ <= 1000)
      {
	this->draw();
	al_rest(6);
      }
  }
private:
  int			size_;
  int			*list_;//[N * N + 2];
  unsigned int		*open_;//[N * N + 2];
  unsigned int		*wg_;//[N * N + 2];
  int			start_;
  int			end_;
  float			cellSize_;
  ALLEGRO_DISPLAY	*display_;
  bool			improved_;
};

#endif			/* !UF_H_ */

