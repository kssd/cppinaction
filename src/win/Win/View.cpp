// (c) Bartosz Milewski 2000

#include "view.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

class DrawLine
{
public:
	DrawLine (Win::Canvas & canvas, Model::Point const & p)
		: _canvas (canvas)
	{
		_canvas.MoveTo (p.X (), p.Y ());
	}
	void operator () (Model::Point const & p)
	{
		if (!p.IsStart ())
			_canvas.LineTo (p.X (), p.Y ());
		else
			_canvas.MoveTo (p.X (), p.Y ());
	}
private:
	Win::Canvas & _canvas;
};

void View::Paint (Win::Canvas & canvas, 
				  Model::iter beg, 
				  Model::iter end)
{
	Pen::Holder pen (canvas, _redPen);
	PrintPos (canvas, _x, _y);
	if (beg != end)
	{
		DrawLine draw (canvas, *beg);
		++beg;
		std::for_each (beg, end, draw);
	}
}

void View::MoveTo (Win::Canvas & canvas, int x, int y, bool visible)
{
	if (visible)
	{
		Pen::Holder pen (canvas, _bluePen);
		canvas.Line (_x, _y, x, y);
	}
	PrintPos (canvas, x, y);
}

void View::PrintPos (Win::Canvas & canvas, int x, int y)
{
	_x = x;
	_y = y;
	std::stringstream out;
	out << "Mouse at: " << std::setw (4) << x;
	out << ", " << std::setw (4) << y << " ";
	std::string s = out.str ();

	Font::Holder::Color color (canvas, 255, 255, 0);
	Font::Holder::Background bk (canvas, 0, 64, 128);
	Font::Holder::SysFixed fix (canvas);
	canvas.Text (0, 0, &s [0], s.length ());
}
