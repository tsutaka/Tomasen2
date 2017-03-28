#ifndef INCLUDED_OBJ_PARTS_B_HPP
#define INCLUDED_OBJ_PARTS_B_HPP

#include "common.hpp"
#include "obj_parts.hpp"

namespace tm2{

class CoreA : public PartsB{
private:

public:
	CoreA();		//コンストラクタ
};

class Base2B : public PartsB{
private:

public:
	Base2B();		//コンストラクタ
};

class Base1A : public PartsB{
private:

public:
	Base1A();		//コンストラクタ
};

class Base4 : public PartsB{
private:

public:
	Base4();		//コンストラクタ
};

class Base3A : public PartsB{
private:

public:
	Base3A();		//コンストラクタ
};

class Base3B : public PartsB{
private:

public:
	Base3B();		//コンストラクタ
	/*更新関数*/
	void update(Tomasen& game);
	/*描画関数*/
	void draw(Tomasen& game);

};

class Base3C : public PartsB{
private:

public:
	Base3C();		//コンストラクタ
	/*更新関数*/
	void update(Tomasen& game);
	/*描画関数*/
	void draw(Tomasen& game);
};

class Base3D : public PartsB{
private:

public:
	Base3D();		//コンストラクタ
};

class Base2A : public PartsB{
private:

public:
	Base2A();		//コンストラクタ
};

class Base2C : public PartsB{
private:

public:
	Base2C();		//コンストラクタ
};

class Base2D : public PartsB{
private:

public:
	Base2D();		//コンストラクタ
};

class Base2E : public PartsB{
private:

public:
	Base2E();		//コンストラクタ
};

class Base2F : public PartsB{
private:

public:
	Base2F();		//コンストラクタ
};

class Base1B : public PartsB{
private:

public:
	Base1B();		//コンストラクタ
};

class Base1C : public PartsB{
private:

public:
	Base1C();		//コンストラクタ
};

class Base1D : public PartsB{
private:

public:
	Base1D();		//コンストラクタ
};

} //namespace tm2
#endif//INCLUDED_OBJ_PARTS_B_HPP