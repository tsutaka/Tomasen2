#include "obj_parts_B.hpp"

#include "obj_effect.hpp"

namespace tm2{

CoreA::CoreA(){
	name = TEXT("コアA");	//名前
	maxHp = 30;				//最大耐久度
	hp = maxHp;				//現在耐久度
	imageX = 0;				//画像x座標
	imageY = 4;				//画像y座標
	imageW = 1;				//画像幅
	imageH = 1;				//画像高
	animeMax = 4;			//アニメ枚数
	animeWait = 4;			//１枚当りのフレーム
	size = tipSize;			//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointEmp;

}

Base2B::Base2B(){
	name = TEXT("ベース2B");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 28;				//画像x座標
	imageY = 4;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointEmp;
}

Base1A::Base1A(){
	/*オブジェクトパラメータ*/
	name = TEXT("ベース1A");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 0;					//画像x座標
	imageY = 5;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointNG;
}

Base4::Base4(){
	name = TEXT("ベース4");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 4;				//画像x座標
	imageY = 4;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointEmp;
}

Base3A::Base3A(){
	/*オブジェクトパラメータ*/
	name = TEXT("ベース3Ａ");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 8;					//画像x座標
	imageY = 4;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointEmp;
}

Base3B::Base3B(){//右だけなし
	/*オブジェクトパラメータ*/
	name = TEXT("ベース3B");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 12;				//画像x座標
	imageY = 4;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointEmp;
}
/*更新関数*/
void Base3B::update(Tomasen& game){
	/*カウントアップ*/
	frameCnt++;
	if(frameCnt > 90000) frameCnt = 0;
	/*アニメーション処理*/
	if(frameCnt % animeWait == 0){
		animeCnt++;
		if(animeCnt % animeMax == 0){
			animeCnt = 0;
		}
	}
	/*親パーツがいない場合の脱落*/
	if(jointParent == 0){
		pos.y += 2;
		//爆炎
		effectFactory( EffectSptr(new Explosion()), 
			getCenterPos().x, getCenterPos().y, 
			Vec2(getCenterPos().x - tipSize/2 + makeRand(0.0, 50), 
				 getCenterPos().y - tipSize/2 + makeRand(-200.0, 60) )
			);
		//煙
		effectFactory( EffectSptr(new Smoke()), 
			getCenterPos().x, getCenterPos().y, 
			Vec2(getCenterPos().x - tipSize/2 + makeRand(0.0, 70), 
				 getCenterPos().y - tipSize/2 + makeRand(-100.0, 60) )
			);
		if(frameCnt % 30 == 0){//アラーム音
			game.MUSIC->Play(musicAlarm);
		}
		if(frameCnt % 50 == makeRand(30)){//破裂音
			game.MUSIC->Play(musicHaretsu);
		}
	}
	

	/*下位兵装の更新*/
	for(int cnt = 0; cnt < weaponIndexEnd; cnt++){
		if(weapon[cnt] == (int)weaponExist){
			if(PartsASptr tmp = getPartsA((weaponIndex)cnt)){	
				/*位置の更新*/
				tmp->setPos(Vec2( pos.x + weaponPosX[cnt], pos.y + weaponPosY[cnt]));//下位のパーツの位置をセット
				tmp->update(game);		//下位のパーツの更新

				/*下位から兵員の輸送*/
				if(man < maxMan && tmp->getMan() > tmp->getRequireMan()){
					//人員が最大でなく下位に余剰兵員がいるとき
					man += 1;
					tmp->addMan(-1);
				}

				/*上位から兵員の輸送*/
				else if(man > requireMan && tmp->getMan() < tmp->getRequireMan()){
					//人員が最大でなく下位に余剰兵員がいるとき
					man -= 1;
					tmp->addMan(1);
				}

				/*回避値の更新*/
				tmp->setKaihi(kaihi);
			}
		}
	}
	/*下位ジョイントの更新*/
	for(int cnt = 0; cnt < jointIndexEnd; cnt++){
		if(joint[cnt] == (int)jointDownExist){
			if(PartsBSptr tmp = getPartsB((jointIndex)cnt)){
				/*位置の更新*/
				//下位ジョイント位置の決定
				//離散処理
				tmp->setPos(Vec2( 
					pos.x + jointPosX[cnt] + kaihi, 
					pos.y + jointPosY[cnt] ));//下位のパーツの位置をセット
				tmp->update(game);		//下位のパーツの更新

				/*下位から兵員の輸送*/
				if(man < maxMan && tmp->getMan() > tmp->getRequireMan()){
					//人員が最大でなく下位に余剰兵員がいるとき
					man += 1;
					tmp->addMan(-1);
				}

				/*上位から兵員の輸送*/
				else if(man > requireMan && tmp->getMan() < tmp->getRequireMan()){
					//人員が最大でなく下位に余剰兵員がいるとき
					man -= 1;
					tmp->addMan(1);
				}

				/*回避値の更新*/
				//if(energy > 10){
					tmp->setKaihi(kaihi);
				//}
			}
		}
	}
	/*回避中*/
	if(kaihi > 0 && energy >= 10){
		energy -= 10;		//回避中はエネルギー消費
	}
	/*回避中*/
	if(kaihi > 0){
		//dir += 0.1;			//回避中は回転
	}
}
/*描画関数*/
void Base3B::draw(Tomasen& game){
	//親の描画関数呼び出し
	PartsB::draw(game);
	//びりびり表示
	for(int cnt = 0; cnt < jointIndexEnd; cnt++){
		if(joint[cnt] == (int)jointDownExist){
			if(PartsBSptr tmp = getPartsB((jointIndex)cnt)){
				if(kaihi > 0){
					//中心点表示
					game.IMAGE->drawLine(getCenterPos(), 
						tmp->getCenterPos(), 
						game.IMAGE->tipNo(42+animeCnt, 24),
						220);
					//びりびり音
					game.MUSIC->Play(musicBiribiri);
				}
			}
		}
	}
}


Base3C::Base3C(){//左だけなし
	/*オブジェクトパラメータ*/
	name = TEXT("ベース3C");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 16;				//画像x座標
	imageY = 4;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointNG;
}

/*更新関数*/
void Base3C::update(Tomasen& game){
	/*カウントアップ*/
	frameCnt++;
	if(frameCnt > 90000) frameCnt = 0;
	/*アニメーション処理*/
	if(frameCnt % animeWait == 0){
		animeCnt++;
		if(animeCnt % animeMax == 0){
			animeCnt = 0;
		}
	}
	/*親パーツがいない場合の脱落*/
	if(jointParent == 0){
		pos.y += 2;
		//爆炎
		effectFactory( EffectSptr(new Explosion()), 
			getCenterPos().x, getCenterPos().y, 
			Vec2(getCenterPos().x - tipSize/2 + makeRand(0.0, 50), 
				 getCenterPos().y - tipSize/2 + makeRand(-200.0, 60) )
			);
		//煙
		effectFactory( EffectSptr(new Smoke()), 
			getCenterPos().x, getCenterPos().y, 
			Vec2(getCenterPos().x - tipSize/2 + makeRand(0.0, 70), 
				 getCenterPos().y - tipSize/2 + makeRand(-100.0, 60) )
			);
		if(frameCnt % 30 == 0){//アラーム音
			game.MUSIC->Play(musicAlarm);
		}
		if(frameCnt % 50 == makeRand(30)){//破裂音
			game.MUSIC->Play(musicHaretsu);
		}
	}
	

	/*下位兵装の更新*/
	for(int cnt = 0; cnt < weaponIndexEnd; cnt++){
		if(weapon[cnt] == (int)weaponExist){
			if(PartsASptr tmp = getPartsA((weaponIndex)cnt)){	
				/*位置の更新*/
				tmp->setPos(Vec2( pos.x + weaponPosX[cnt], pos.y + weaponPosY[cnt]));//下位のパーツの位置をセット
				tmp->update(game);		//下位のパーツの更新

				/*下位から兵員の輸送*/
				if(man < maxMan && tmp->getMan() > tmp->getRequireMan()){
					//人員が最大でなく下位に余剰兵員がいるとき
					man += 1;
					tmp->addMan(-1);
				}

				/*上位から兵員の輸送*/
				else if(man > requireMan && tmp->getMan() < tmp->getRequireMan()){
					//人員が最大でなく下位に余剰兵員がいるとき
					man -= 1;
					tmp->addMan(1);
				}

				/*回避値の更新*/
				tmp->setKaihi(kaihi);
			}
		}
	}
	/*下位ジョイントの更新*/
	for(int cnt = 0; cnt < jointIndexEnd; cnt++){
		if(joint[cnt] == (int)jointDownExist){
			if(PartsBSptr tmp = getPartsB((jointIndex)cnt)){
				/*位置の更新*/
				//下位ジョイント位置の決定
				//離散処理
				tmp->setPos(Vec2( 
					pos.x + jointPosX[cnt] - kaihi, 
					pos.y + jointPosY[cnt] ));//下位のパーツの位置をセット
				tmp->update(game);		//下位のパーツの更新

				/*下位から兵員の輸送*/
				if(man < maxMan && tmp->getMan() > tmp->getRequireMan()){
					//人員が最大でなく下位に余剰兵員がいるとき
					man += 1;
					tmp->addMan(-1);
				}

				/*上位から兵員の輸送*/
				else if(man > requireMan && tmp->getMan() < tmp->getRequireMan()){
					//人員が最大でなく下位に余剰兵員がいるとき
					man -= 1;
					tmp->addMan(1);
				}

				/*回避値の更新*/
				//if(energy > 10){
					tmp->setKaihi(kaihi);
				//}
			}
		}
	}
	/*回避中*/
	if(kaihi > 0 && energy >= 10){
		energy -= 10;		//回避中はエネルギー消費
	}
	/*回避中*/
	if(kaihi > 0){
		//dir += 0.1;			//回避中は回転
	}
}

/*描画関数*/
void Base3C::draw(Tomasen& game){
	//親の描画関数呼び出し
	PartsB::draw(game);
	//びりびり表示
	for(int cnt = 0; cnt < jointIndexEnd; cnt++){
		if(joint[cnt] == (int)jointDownExist){
			if(PartsBSptr tmp = getPartsB((jointIndex)cnt)){
				if(kaihi > 0){
					//中心点表示
					game.IMAGE->drawLine(getCenterPos(), 
						tmp->getCenterPos(), 
						game.IMAGE->tipNo(42+animeCnt, 24),
						220);
				}
			}
		}
	}

}
Base3D::Base3D(){
	/*オブジェクトパラメータ*/
	name = TEXT("ベース3D");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 20;				//画像x座標
	imageY = 4;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointEmp;
}

Base2A::Base2A(){
	/*オブジェクトパラメータ*/
	name = TEXT("ベース2A");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 24;				//画像x座標
	imageY = 4;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointEmp;
}

Base2C::Base2C(){
	/*オブジェクトパラメータ*/
	name = TEXT("ベース2C");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 32;				//画像x座標
	imageY = 4;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointEmp;
}

Base2D::Base2D(){
	/*オブジェクトパラメータ*/
	name = TEXT("ベース2D");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 36;				//画像x座標
	imageY = 4;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointNG;
}

Base2E::Base2E(){
	/*オブジェクトパラメータ*/
	name = TEXT("ベース2E");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 40;				//画像x座標
	imageY = 4;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointEmp;
}

Base2F::Base2F(){
	/*オブジェクトパラメータ*/
	name = TEXT("ベース2F");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 44;				//画像x座標
	imageY = 4;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointEmp;
	joint[(int)leftJoint] = jointNG;
}

Base1B::Base1B(){
	/*オブジェクトパラメータ*/
	name = TEXT("ベース1B");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 4;					//画像x座標
	imageY = 5;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointEmp;
}

Base1C::Base1C(){
	/*オブジェクトパラメータ*/
	name = TEXT("ベース1C");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 8;					//画像x座標
	imageY = 5;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	/*兵装*/
	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	/*ジョイント*/
	joint[(int)upJoint] = jointNG;
	joint[(int)rightJoint] = jointEmp;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointNG;
}

Base1D::Base1D(){
	name = TEXT("ベース1D");	//名前
	maxHp = 10;					//最大耐久度
	hp = maxHp;					//現在耐久度
	imageX = 12;				//画像x座標
	imageY = 5;					//画像y座標
	imageW = 1;					//画像幅
	imageH = 1;					//画像高
	animeMax = 4;				//アニメ枚数
	animeWait = 4;				//１枚当りのフレーム
	size = tipSize;				//当たり判定直径

	weapon[(int)mainWeapon] = weaponEmp;
	weapon[(int)subWeapon] = weaponNG;

	joint[(int)upJoint] = jointEmp;
	joint[(int)rightJoint] = jointNG;
	joint[(int)downJoint] = jointNG;
	joint[(int)leftJoint] = jointNG;
}

} //namespace tm2