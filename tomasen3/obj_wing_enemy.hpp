#ifndef INCLUDED_OBJ_WING_ENEMY_HPP
#define INCLUDED_OBJ_WING_ENEMY_HPP



#include "common.hpp"
#include "obj_wing.hpp"

namespace tm2{

class EnemyA : public Enemy{
public:
	/*コンストラクタ*/
	EnemyA();	
	/*更新関数*/
	void update(Tomasen& game);
	/*行動関数*/
	void action(Object obj);
};

class EnemyB : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyB();	
	/*行動関数*/
	void action(Object obj);
};

class EnemyC : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyC();	
	/*行動関数*/
	void action(Object obj);
};

class EnemyD : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyD();	
	/*行動関数*/
	void action(Object obj);
};

class EnemyE : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyE();
	/*更新関数*/
	void update(Tomasen& game);	
	/*行動関数*/
	void action(Object obj);
};

class EnemyF : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyF();	
	/*行動関数*/
	void action(Object obj);
};

class EnemyG : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyG();	
	/*行動関数*/
	void action(Object obj);
};

class EnemyH : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyH();	
	/*行動関数*/
	void action(Object obj);
};

class EnemyI : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyI();	
	/*行動関数*/
	void action(Object obj);
};

class EnemyJ : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyJ();	
	/*更新関数*/
	void update(Tomasen& game);
	/*行動関数*/
	void action(Object obj);
};

class EnemyK : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyK();	
	/*行動関数*/
	void action(Object obj);
};

class EnemyL : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyL();	
	/*行動関数*/
	void action(Object obj);
};

class EnemyN : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyN();	
	/*行動関数*/
	void action(Object obj);
};


class EnemyO : public Enemy{
public:
	double shotCnt;
public:
	/*コンストラクタ*/
	EnemyO();	
	/*行動関数*/
	void action(Object obj);
};

} //namespace tm2
#endif//INCLUDED_OBJ_WING_ENEMY_HPP