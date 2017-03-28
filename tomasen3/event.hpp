#ifndef INCLUDED_EVENT_HPP
#define INCLUDED_EVENT_HPP


#include <vector>		//vector
#include <memory>		//shared_ptr

#include "common.hpp"
#include "object.hpp"

// std::tr1:: を std:: と書けるように
namespace std {
	using namespace tr1; 
}

namespace tm2{

class Event {
protected:
	/*変動パラメータ*/
	Vec2 pos;				//位置
	double dis;				//移動量
	double dir;				//角度
	long frameCnt;			//生成後の経過フレーム数
	string name;			//名称
	int phase;				//現段階
	int next;				//イベント終了フラグ
public:
	/*getter関数*/
	Vec2 getPos(){ return pos; }
	double getDis(){ return dis; }
	double getDir(){ return dir; }
	long getFrameCnt(){ return frameCnt; }
	string getName(){ return name; }
	int getPhase(){ return phase; }
	int nextEvent(){ return next; }

	/*setter関数*/
	void setPos(Vec2 pos){ Event::pos = pos; }
	void setDis(double dis){ Event::dis = dis; }
	void setDir(double dir){ Event::dir = dir; }
	void setFrameCnt(int frameCnt){ Event::frameCnt = frameCnt; }
	void setName(string name){ Event::name = name; }
	void setPhase(int phase){ Event::phase = phase; }

	/*コンストラクタ*/
	Event();
	/*更新関数*/
	void update(Tomasen& game);
	/*アクション関数（個別）*/
	virtual void action(Tomasen& game) = 0;
};

/*グローバルリソース宣言*/
typedef weak_ptr< Event > EventWptr;		//イベントのweakポインタ
typedef shared_ptr< Event > EventSptr;		//イベントのsharedポインタ
typedef vector< EventSptr > EventVsptr;		//イベントのsharedポインタの配列
extern EventVsptr eventList;				//イベントリスト
void eventFactory(EventSptr event);			//イベントファクトリー関数



class GameTitle : public Event{
public:
	/*アクション関数（個別）*/
	void action(Tomasen& game);
};

class Stage1 : public Event{
public:
	/*コンストラクタ*/
	Stage1();
	/*アクション関数（個別）*/
	void action(Tomasen& game);
};

class Stage2 : public Event{
public:
	/*コンストラクタ*/
	Stage2();
	/*アクション関数（個別）*/
	void action(Tomasen& game);
};
class Stage3 : public Event{
public:
	/*コンストラクタ*/
	Stage3();
	/*アクション関数（個別）*/
	void action(Tomasen& game);
};
class Stage4 : public Event{
public:
	/*コンストラクタ*/
	Stage4();
	/*アクション関数（個別）*/
	void action(Tomasen& game);
};
class Stage5 : public Event{
public:
	/*コンストラクタ*/
	Stage5();
	/*アクション関数（個別）*/
	void action(Tomasen& game);
};
class GameOver : public Event{
public:
	/*アクション関数（個別）*/
	void action(Tomasen& game);
};

class GameClear : public Event{
public:
	/*アクション関数（個別）*/
	void action(Tomasen& game);
};

class StaffRoll : public Event{
public:
	/*アクション関数（個別）*/
	void action(Tomasen& game);
};


} //namespace tm2
#endif//INCLUDED_EVENT_HPP