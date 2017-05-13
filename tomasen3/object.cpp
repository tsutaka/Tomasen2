#include "object.hpp"

namespace tm2{

void Object::update(Tomasen& game){
}
void Object::draw(Tomasen& game){
}
void Object::damageHp(int damage){
	hp -= damage;
	if(hp < 0) hp = 0;
}
Vec2 Object::getCenterPos(){
	Vec2 centerPos(getPos().x + (double)getOutputW()*tipSize/2, getPos().y + (double)getOutputH()*tipSize/2);
	return centerPos;
}

} //namespace tm2