#include "obj_parts.hpp"

#include "tomasen.hpp"
#include "obj_effect.hpp"

namespace tm2{

/*グローバルリソース定義*/
PartsAVsptr partsAList;			//パーツリスト
PartsAWptr partsAFactory(PartsASptr partsA){
		partsAList.push_back( partsA );			//リストにオブジェクト追加
		PartsAVsptr::iterator it = partsAList.end() - 1;	//直前のオブジェクトを参照
		return (*it);
}
PartsBVsptr partsBList;			//パーツリスト
PartsBWptr partsBFactory(PartsBSptr partsB){
		partsBList.push_back( partsB );			//リストにオブジェクト追加
		PartsBVsptr::iterator it = partsBList.end() - 1;	//直前のオブジェクトを参照
		return (*it);
}
PartsBWptr partsSetFactory(PartsBSptr partsB, PartsBSptr newPartsB, PartsASptr newPartsA, jointIndex jointDir){
		PartsBSptr base = partsBFactory( newPartsB ).lock();//ベースの作成
		partsB->setPartsB(jointDir, base);					//ベースの接続
		if(newPartsA != NULL){
			base->setPartsA(mainWeapon,							//兵装の作成と接続
				partsAFactory( newPartsA )
				);
		}
		return newPartsB;
}
/*コンストラクタ*/
Parts::Parts(){
	//パーツのデフォルト値
	pos = Vec2(0.0, 0.0);	//現在位置
	move = Vec2(0.0, 0.0);	//移動量
	dis = 0.0;				//移動量
	dir = 0.0;				//角度
	frameCnt = 0;			//経過フレーム数
	animeCnt = 0;			//アニメフレーム
	updateCheck = true;		//更新可否
	outputW = 1;			//出力幅
	outputH = 1;			//出力高
	maxEnergy = 50;			//最大の弾数
	energy = maxEnergy;		//現在の弾数
	chargeEnergy = 1;		//給弾する弾数
	maxMan = 10;			//最大の人員
	man = 50;				//現在の人員
	requireMan = 0;			//必要な人員
	fire = 5;				//現在の火勢
	burnFire = 20;			//発火する火勢
	maxFire = 50;			//最大の火勢
	kaihi = 0;				//変形フラグ(変形：１)
	drawPriority = 0;

}
/*add関数*/
//自機自体にも同様の関数あり
void Parts::addKaihi(int kaihi){
	const int kaihiMin = 0;
	const int kaihiMax = 80;
	Parts::kaihi += kaihi;
	if(Parts::kaihi > kaihiMax){
		Parts::kaihi = kaihiMax;
	}else if(Parts::kaihi < kaihiMin){
		Parts::kaihi = kaihiMin;
	}
}
/*報告関数*/
void Parts::tellUp(TellUpBox &box){
	box.hp += hp;
	box.maxHp += maxHp;
	box.energy += energy;
	box.chargeEnergy += chargeEnergy;
	box.maxEnergy += maxEnergy;
	box.man += man;
	box.requireMan += requireMan;
	box.maxMan += maxMan;
	box.fire += fire;
	box.burnFire += burnFire;
	box.maxFire += maxFire;
	this->subTellUp(box);
	return;
}
/*殺傷関数*/
void Parts::killMan(int damage){
	if(perCheck(25)){
		man -= damage;
	}
	//天子のわっか
	for(int cnt = 0; cnt < damage; cnt++){
		effectFactory( EffectSptr(new Wakka()), 
			getCenterPos().x, getCenterPos().y, 
			Vec2(getCenterPos().x - tipSize/2 + makeRand(0.0, 50), 
					getCenterPos().y - tipSize/2 + makeRand(-75.0, 20) )
			);
	}
}

/*コンストラクタ*/
PartsA::PartsA(){
}
/*更新関数*/
void PartsA::update(Tomasen& game){
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

	/*給弾処理*/
	if(frameCnt%2 == 0 && man >= requireMan && fire < burnFire){	//人員十分、火災なし
		if(energy < maxEnergy) energy += chargeEnergy;
	}
	else if(frameCnt%3 == 0 && man >= requireMan){					//人員十分、火災あり
		if(energy < maxEnergy) energy += chargeEnergy;
	}
}
/*描画関数*/
void PartsA::draw(Tomasen& game){
	game.IMAGE->drawRotateTip(	getPos().x + (double)tipSize * getOutputW() / 2, 
							getPos().y + (double)tipSize * getOutputH() / 2, 
							getDir(),
							game.IMAGE->tipNo(	getImageX(), 
												getImageY() ) );
}
/*アクション関数個別*/
void PartsA::action(Tomasen& game){
}
/*サブ報告関数*/
void PartsA::subTellUp(TellUpBox &box){
	return;
}

/*コンストラクタ*/
PartsB::PartsB(){
	//パーツBのデフォルト値
	weapon[mainWeapon] = weaponEmp;		//兵装有無
	weaponPosX[mainWeapon] = 0;			//兵装X座標（親からの相対）
	weaponPosY[mainWeapon] = 0;			//兵装Y座標（親からの相対）
	weapon[subWeapon] = weaponNG;		//兵装有無
	weaponPosX[subWeapon] = 0;			//兵装X座標（親からの相対）
	weaponPosY[subWeapon] = 0;			//兵装Y座標（親からの相対）
	joint[upJoint] = jointEmp;			//ジョイント有無
	jointPosX[upJoint] = 0;				//ジョイントX座標（親からの相対）
	jointPosY[upJoint] = -tipSize;		//ジョイントY座標（親からの相対）
	joint[rightJoint] = jointEmp;		//ジョイント有無
	jointPosX[rightJoint] = tipSize;	//ジョイントX座標（親からの相対）
	jointPosY[rightJoint] = 0;			//ジョイントY座標（親からの相対）
	joint[downJoint] = jointEmp;		//ジョイント有無
	jointPosX[downJoint] = 0;			//ジョイントX座標（親からの相対）
	jointPosY[downJoint] = tipSize;		//ジョイントY座標（親からの相対）
	joint[leftJoint] = jointEmp;		//ジョイント有無
	jointPosX[leftJoint] = -tipSize;	//ジョイントX座標（親からの相対）
	jointPosY[leftJoint] = 0;			//ジョイントY座標（親からの相対）
	jointParent = 1;					//親との接続状況
}
/*デストラクタ*/
PartsB::~PartsB(){
	jointParent = 0;					//親から分離
	/*下位兵装の分離*/
	for(int cnt = 0; cnt < weaponIndexEnd; cnt++){
		if(weapon[cnt] == (int)weaponExist){
			if(PartsASptr tmp = getPartsA((weaponIndex)cnt)){	
				/*下位兵装の破壊*/
				tmp->setHp(0);
			}
		}
	}
	/*下位ジョイントの分離*/
	for(int cnt = 0; cnt < jointIndexEnd; cnt++){
		if(joint[cnt] == (int)jointDownExist){
			if(PartsBSptr tmp = getPartsB((jointIndex)cnt)){
				/*下位兵装の分離*/
				tmp->setJointParent(0);
			}
		}
	}
}

/*更新関数*/
void PartsB::update(Tomasen& game){
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
		if(frameCnt % 2 == 0){
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
		}
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
				//縮小処理
				tmp->setPos(Vec2( 
					pos.x + jointPosX[cnt] * (100 - kaihi) / 100, 
					pos.y + jointPosY[cnt] * (100 - kaihi) / 100));//下位のパーツの位置をセット
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
void PartsB::draw(Tomasen& game){
	game.IMAGE->drawTip( getPos().x, getPos().y, 
					(double)tipSize * getOutputW(), 
					(double)tipSize * getOutputH(), 
					game.IMAGE->tipNo(	getImageX(), 
									getImageY() ) );
	game.IMAGE->drawAlphaBlendTip( getPos().x, getPos().y, //HP点滅
					(double)tipSize * getOutputW(), 
					(double)tipSize * getOutputH(), 
					game.IMAGE->getRed(),
					(getMaxHp() - getHp() ) * 120 / getMaxHp() );
}

/*兵装状態設定関数*/
void PartsB::setWeapon(weaponIndex index, weaponOK val){
	weapon[index] = val;
}
/*土台状態設定関数*/
void PartsB::setJoint(jointIndex index, jointOK val){
	joint[index] = val;
}
/*親接続土台状態設定関数*/
void PartsB::setJointParent(int jointParent){
	PartsB::jointParent = jointParent;
}
/*兵装取得*/
PartsASptr PartsB::getPartsA(weaponIndex index){
	if(index == mainWeapon){
		return partsA0.lock();
	}
	else{//index = subWeapon
		return partsA1.lock();
	}
}
/*土台取得*/
PartsBSptr PartsB::getPartsB(jointIndex index){
	if(index == upJoint){
		return partsB0.lock();
	}
	else if(index == rightJoint){
		return partsB1.lock();
	}
	else if(index == downJoint){
		return partsB2.lock();
	}
	else{//index = leftJoint
		return partsB3.lock();
	}
}
/*親有無取得*/
int PartsB::getJointParent(void){
	return jointParent;
}
/*兵装追加関数*/
void PartsB::setPartsA(weaponIndex pos, PartsAWptr partsA){
	weapon[pos] = weaponExist;					//下位
	switch((int)pos){
	case (int)mainWeapon:
		partsA0 = partsA;			//兵装を追加
		break;
	default://(int)subWeapon
		partsA1 = partsA;			//兵装を追加
		break;
	}
	if(PartsASptr tmp = getPartsA(pos)){	//兵装に上位層の情報を格納する場合はここ
		//tmp->setPartsB(0, 1);				//兵装の上位の設定
	}
}
/*土台追加関数*/
void PartsB::setPartsB(jointIndex pos, PartsBSptr partsB){
	jointIndex jointPos;
	joint[pos] = jointDownExist;					//下位
	switch((int)pos){
	case (int)upJoint:
		partsB0 = PartsBWptr(partsB);			//ジョイントを追加
		jointPos = downJoint;					//接続先のジョイントの指定
		break;
	case (int)rightJoint:
		partsB1 = PartsBWptr(partsB);			//ジョイントを追加
		jointPos = leftJoint;					//接続先のジョイントの指定
		break;
	case (int)downJoint:
		partsB2 = PartsBWptr(partsB);			//ジョイントを追加
		jointPos = upJoint;						//接続先のジョイントの指定
		break;
	default://(int)leftJoint
		partsB3 = PartsBWptr(partsB);			//ジョイントを追加
		jointPos = rightJoint;					//接続先のジョイントの指定
		break;
	}
}

/*サブ報告関数*/
void PartsB::subTellUp(TellUpBox &box){
	/*パーツAの探索*/
	for(int pos = (int)mainWeapon; pos < (int)weaponIndexEnd; pos++){
		if(weapon[pos] == weaponExist){	
			if( PartsASptr tmp = getPartsA((weaponIndex)pos) ){
				box.pertsANum++;
				tmp->tellUp(box);
			}
			else{
				box.pertsALost++;
				weapon[(int)pos] = weaponEmp;
			}
		}
	}
	/*パーツBの探索*/
	for(int pos = (int)upJoint; pos < (int)jointIndexEnd; pos++){
		if(joint[pos] == jointDownExist){	
			if( PartsBSptr tmp = getPartsB((jointIndex)pos) ){
				box.pertsBNum++;
				tmp->tellUp(box);
			}
			else{
				box.pertsBLost++;
				joint[(int)pos] = jointEmp;
			}
		}
	}
	return;
}

} //namespace tm2