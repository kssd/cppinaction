#if !defined (MODEL_H)
#define MODEL_H
// (c) Bartosz Milewski 2000
#include <deque>

class Model
{
	enum { MAX_SIZE = 1000 };
public:
	class Point
	{
	public:
		Point (int x = 0, int y = 0, bool isStart = false)
			: _x (static_cast<short> (x)), 
			  _y (static_cast<short> (y)), 
			  _isStart (isStart)
		{} 
		int X () const { return _x; }
		int Y () const { return _y; }
		bool IsStart () const { return _isStart; }
	private:
		short _x;
		short _y;
		bool  _isStart;
	};

	typedef std::deque<Point>::const_iterator iter;

	void AddPoint (int x, int y, bool isStart = false)
	{
		if (_queue.size () >= MAX_SIZE)
			_queue.pop_front ();
		_queue.push_back (Point (x, y, isStart));
	}
	iter begin () const { return _queue.begin (); }
	iter end () const { return _queue.end (); }
private:
	std::deque<Point> _queue;
};

#endif
