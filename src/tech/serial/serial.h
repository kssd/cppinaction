#if !defined SERIAL_H
#define SERIAL_H

class Serializer;
class DeSerializer;

class Serializable
{
public:
	virtual void Serialize (Serializer & out) const = 0;
	virtual void DeSerialize (DeSerializer & in) = 0;
};

#endif
