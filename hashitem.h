#ifndef HASHITEM_H
#define HASHITEM_H

template <class Key, class Value>
class HashItem
{
private:
    Key _key;
    Value _value;
public:
    HashItem(const Key &iKey, const Value &iValue):_key(iKey),_value(iValue){}
    const Key & getKey () const { return _key; }
    const Value & getValue() const { return _value; }

};

#endif // HASHITEM_H
