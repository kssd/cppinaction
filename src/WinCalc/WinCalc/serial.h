#if !defined SERIAL_H
#define SERIAL_H
// (c) Bartosz Milewski 2000
class Serializer;
class DeSerializer;

class Serializable
{
public:
	virtual ~Serializable () {}
	virtual void Serialize (Serializer & out) const = 0;
	virtual void DeSerialize (DeSerializer & in) = 0;
};

#endif
