#if !defined (VIEW_H)
#define VIEW_H
// (c) Bartosz Milewski 2000

#include "Canvas.h"
#include "Model.h"
#include "tools.h"

class View
{
public:
	View () 
		: _x (0), _y (0), 
		  _redPen (128, 0, 0),
		  _bluePen (0, 0, 255)
	{}

	void MoveTo (Win::Canvas & canvas, int x, int y, bool visible = true);

	void Paint (Win::Canvas & canvas, 
				Model::iter beg, 
				Model::iter end);
	void PrintPos (Win::Canvas & canvas, int x, int y);
private:
	int _x, _y;
	Pen::Color _redPen;
	Pen::Color _bluePen;
};

#endif
