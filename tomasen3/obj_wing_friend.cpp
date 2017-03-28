#include <cmath>

#include "obj_wing_friend.hpp"
#include "tomasen.hpp"

namespace tm2{

/*グローバルリソース定義*/
FriendVsptr friendList;			//自機リスト
FriendWptr friendFactory(FriendSptr friendw, Vec2 pos){
		friendList.push_back( friendw );					//リストにオブジェクト追加
		FriendVsptr::iterator it = friendList.end() - 1;	//直前のオブジェクトを参照
		(*it)->setPos(pos);
		return (*it);
}

KosenWing::KosenWing(Tomasen& game){
	/*初期化*/
	name = TEXT("コーセンウィング");				//名称の設定
	maxMove = 4.0;									//最大移動量
	subMove = 0.90;									//減少移動量倍率
	maxHp = 10;										//最大耐久度
	imageX = 0;										//画像x座標
	imageY = 0;										//画像y座標
	imageW = 1;										//画像幅
	imageH = 1;										//画像高
	size = tipSize;									//当たり判定直径
	frameCnt = 0;									//経過フレーム数
	
	partsANum = 0;	//現時点パーツA数
	partsALost = 0;	//累積喪失パーツA数
	partsBNum = 0;	//現時点パーツB数
	partsBLost = 0;	//累積喪失パーツB数


	/*自機実装*/	
	core = partsBFactory( PartsBSptr(new CoreA()) );			//弱いスマポで親子関係
	if(PartsBSptr coreSptr = core.lock()){						//コアにパーツを追加する。
		/*テキストコピーここから*/
		coreSptr->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new EngineA()) )
			);					//コアにエンジン追加

		PartsBSptr base4_E18 = partsSetFactory(coreSptr, PartsBSptr(new Base4()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base1C_D18 = partsSetFactory(base4_E18, PartsBSptr(new Base1C()), PartsASptr(new SubCanonA()), leftJoint).lock();

		PartsBSptr base1B_F18 = partsSetFactory(base4_E18, PartsBSptr(new Base1B()), PartsASptr(new SubCanonA()), rightJoint).lock();

		PartsBSptr base4_E20 = partsSetFactory(base4_E18, PartsBSptr(new Base4()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base1C_D20 = partsSetFactory(base4_E20, PartsBSptr(new Base1C()), PartsASptr(new EngineA()), leftJoint).lock();

		PartsBSptr base1B_F20 = partsSetFactory(base4_E20, PartsBSptr(new Base1B()), PartsASptr(new EngineA()), rightJoint).lock();

		PartsBSptr base2B_E22 = partsSetFactory(base4_E20, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E24 = partsSetFactory(base2B_E22, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E26 = partsSetFactory(base2B_E24, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E28 = partsSetFactory(base2B_E26, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E30 = partsSetFactory(base2B_E28, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E32 = partsSetFactory(base2B_E30, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E34 = partsSetFactory(base2B_E32, PartsBSptr(new Base2B()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base1D_E36 = partsSetFactory(base2B_E34, PartsBSptr(new Base1D()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2B_E14 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock失敗のエラー処理省略
		coreSptr->setPartsB(upJoint, base2B_E14);					//コアにベース１Ａ追加
		base2B_E14->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//コアにコックピット追加

		PartsBSptr base2B_E12 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock失敗のエラー処理省略
		base2B_E14->setPartsB(upJoint, base2B_E12);					//ベース２Ｆにベース１D追加
		base2B_E12->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//ベース１ＤにマシンガンＡ追加
		
		PartsBSptr base4_E10 = partsBFactory( PartsBSptr(new Base4()) ).lock();//lock失敗のエラー処理省略
		base2B_E12->setPartsB(upJoint, base4_E10);					//ベース２Ｆにベース１D追加
		base4_E10->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//ベース１ＤにマシンガンＡ追加

		PartsBSptr base2B_E8 = partsSetFactory(base4_E10, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), upJoint).lock();

		PartsBSptr base2B_E6 = partsSetFactory(base2B_E8, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), upJoint).lock();

		PartsBSptr base1A_E4 = partsSetFactory(base2B_E8, PartsBSptr(new Base1A()), PartsASptr(new CockpitA()), upJoint).lock();

		PartsBSptr base2F_D10 = partsBFactory( PartsBSptr(new Base2F()) ).lock();//lock失敗のエラー処理省略
		base4_E10->setPartsB(leftJoint, base2F_D10);					//ベース２Ｆにベース１D追加
		base2F_D10->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new MachineGunA()) )
			);				//ベース１ＤにマシンガンＡ追加

		PartsBSptr base2C_D12 = partsBFactory( PartsBSptr(new Base2C()) ).lock();//lock失敗のエラー処理省略
		base2F_D10->setPartsB(downJoint, base2C_D12);					//ベース２Ｆにベース１D追加
		base2C_D12->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new MachineGunA()) )
			);				//ベース１ＤにマシンガンＡ追加

		PartsBSptr base3C_C12 = partsBFactory( PartsBSptr(new Base3C()) ).lock();//lock失敗のエラー処理省略
		base2C_D12->setPartsB(leftJoint, base3C_C12);					//ベース２Ｆにベース１D追加
		base3C_C12->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//ベース１ＤにマシンガンＡ追加

		PartsBSptr base2B_C10 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock失敗のエラー処理省略
		base3C_C12->setPartsB(upJoint, base2B_C10);					//ベース２Ｆにベース１D追加
		base2B_C10->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//ベース１ＤにマシンガンＡ追加

		PartsBSptr base2B_C8 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock失敗のエラー処理省略
		base2B_C10->setPartsB(upJoint, base2B_C8);					//ベース２Ｆにベース１D追加
		base2B_C8->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new MachineGunA()) )
			);				//ベース１ＤにマシンガンＡ追加

		PartsBSptr base2B_C6 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock失敗のエラー処理省略
		base2B_C8->setPartsB(upJoint, base2B_C6);					//ベース２Ｆにベース１D追加
		base2B_C6->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new LuncherR()) )
			);				//ベース２ＢにマシンガンＡ追加


		PartsBSptr base2B_C4 = partsSetFactory(base2B_C6, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), upJoint).lock();

		PartsBSptr base1A_C2 = partsSetFactory(base2B_C4, PartsBSptr(new Base2B()), PartsASptr(new HadohoA()), upJoint).lock();
		
		PartsBSptr base2B_C14 = partsSetFactory(base3C_C12, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), downJoint).lock();
		
		PartsBSptr base2C_C16 = partsSetFactory(base2B_C14, PartsBSptr(new Base2C()), PartsASptr(new CockpitA()), downJoint).lock();

		PartsBSptr base2F_B16 = partsSetFactory(base2C_C16, PartsBSptr(new Base2F()), PartsASptr(new HadohoA()), leftJoint).lock();

		PartsBSptr base2B_B18 = partsSetFactory(base2F_B16, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), downJoint).lock();

		PartsBSptr base3B_B20 = partsSetFactory(base2B_B18, PartsBSptr(new Base3B()), PartsASptr(new CockpitA()), downJoint).lock();

		PartsBSptr base1D_B22 = partsSetFactory(base3B_B20, PartsBSptr(new Base1D()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2F_A20 = partsSetFactory(base3B_B20, PartsBSptr(new Base2F()), PartsASptr(new MachineGunA()), leftJoint).lock();

		PartsBSptr base1D_A22 = partsSetFactory(base2F_A20, PartsBSptr(new Base1D()), PartsASptr(new SubCanonA()), downJoint).lock();


		PartsBSptr base2E_F10 = partsBFactory( PartsBSptr(new Base2E()) ).lock();//lock失敗のエラー処理省略
		base4_E10->setPartsB(rightJoint, base2E_F10);					//ベース２Ｆにベース１D追加
		base2E_F10->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new MachineGunA()) )
			);				//ベース１ＤにマシンガンＡ追加

		PartsBSptr base2D_F12 = partsBFactory( PartsBSptr(new Base2D()) ).lock();//lock失敗のエラー処理省略
		base2E_F10->setPartsB(downJoint, base2D_F12);					//ベース２Ｆにベース１D追加
		base2D_F12->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new MachineGunA()) )
			);				//ベース１ＤにマシンガンＡ追加

		PartsBSptr base3B_G12 = partsBFactory( PartsBSptr(new Base3B()) ).lock();//lock失敗のエラー処理省略
		base2D_F12->setPartsB(rightJoint, base3B_G12);					//ベース２Ｆにベース１D追加
		base3B_G12->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//ベース１ＤにマシンガンＡ追加

		PartsBSptr base2B_G10 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock失敗のエラー処理省略
		base3B_G12->setPartsB(upJoint, base2B_G10);					//ベース２Ｆにベース１D追加
		base2B_G10->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new CockpitA()) )
			);				//ベース１ＤにマシンガンＡ追加

		PartsBSptr base2B_G8 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock失敗のエラー処理省略
		base2B_G10->setPartsB(upJoint, base2B_G8);					//ベース２Ｆにベース１D追加
		base2B_G8->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new MachineGunA()) )
			);				//ベース１ＤにマシンガンＡ追加

		PartsBSptr base2B_G6 = partsBFactory( PartsBSptr(new Base2B()) ).lock();//lock失敗のエラー処理省略
		base2B_G8->setPartsB(upJoint, base2B_G6);					//ベース２Ｆにベース１D追加
		base2B_G6->setPartsA(mainWeapon, 
			partsAFactory( PartsASptr(new LuncherL()) )
			);				//ベース１ＤにマシンガンＡ追加


		PartsBSptr base2B_G4 = partsSetFactory(base2B_G6, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), upJoint).lock();

		PartsBSptr base1A_G2 = partsSetFactory(base2B_G4, PartsBSptr(new Base2B()), PartsASptr(new HadohoA()), upJoint).lock();
		
		PartsBSptr base2B_G14 = partsSetFactory(base3B_G12, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), downJoint).lock();
		
		PartsBSptr base2D_G16 = partsSetFactory(base2B_G14, PartsBSptr(new Base2D()), PartsASptr(new CockpitA()), downJoint).lock();

		PartsBSptr base2E_H16 = partsSetFactory(base2D_G16, PartsBSptr(new Base2E()), PartsASptr(new HadohoA()), rightJoint).lock();

		PartsBSptr base2B_H18 = partsSetFactory(base2E_H16, PartsBSptr(new Base2B()), PartsASptr(new CockpitA()), downJoint).lock();

		PartsBSptr base3C_H20 = partsSetFactory(base2B_H18, PartsBSptr(new Base3C()), PartsASptr(new CockpitA()), downJoint).lock();

		PartsBSptr base1D_H22 = partsSetFactory(base3C_H20, PartsBSptr(new Base1D()), PartsASptr(new EngineA()), downJoint).lock();

		PartsBSptr base2E_I20 = partsSetFactory(base3C_H20, PartsBSptr(new Base2E()), PartsASptr(new MachineGunA()), rightJoint).lock();

		PartsBSptr base1D_I22 = partsSetFactory(base2E_I20, PartsBSptr(new Base1D()), PartsASptr(new SubCanonA()), downJoint).lock();
		
		/*テキストコピーここまで*/

		this->update(game);			//自機更新（探索木）
		startHp = maxHp;			//初期HPの記録
		startEnergy = maxEnergy;	//初期ENの記録
		startMan = maxMan;			//初期人の記録
	}
	
}


/*更新関数*/
void KosenWing::update(Tomasen& game){
	/*各パラメータを更新する*/
	frameCnt++;										//フレームカウントの更新
	if(frameCnt > 50000) frameCnt = 0;

	/*パーツ関係の更新*/
	if(PartsBSptr tmp = core.lock()){
		/*パーツからの情報収集*/
		TellUpBox box = {
			0,0,		//hp, maxHp
			0,0,0,		//energy,maxEnergy,chargeEnergy
			0,0,0,		//man,requireMan,maxMan
			0,0,0,		//fire,burnFire,maxFire
			0,0,1,0};	//A,lostA,B,lostB				
		tmp->tellUp(box);
		hp = box.hp;
		maxHp = box.maxHp;
		energy = box.energy;
		chargeEnergy = box.chargeEnergy;
		maxEnergy = box.maxEnergy;
		man = box.man;
		requireMan = box.requireMan;
		maxMan = box.maxMan;
		fire = box.fire;
		burnFire = box.burnFire;
		maxFire = box.maxFire;
		partsANum = box.pertsANum;
		partsALost += box.pertsALost;
		partsBNum = box.pertsBNum;
		partsBLost += box.pertsBLost;

		/*回避値の更新*/
		tmp->setKaihi(kaihi);
	}
	else{//コアがやられてる
		hp = 50;
		if(game.gameResult == 0){
			game.gameResult = 1;
		}
	}
	
	/*自機移動*/
	dir = atan2(move.y, move.x);					//現在の進行角算出
	dis = sqrt(move.x * move.x + move.y * move.y);	//移動量算出
	if(dis > maxMove){
		dis = maxMove;						//移動量抑止
	}
	else{
		dis *= subMove;
	}
	move.x = cos(dir) * dis;				//移動量抑止
	move.y = sin(dir) * dis;				//移動量抑止
	pos.x = pos.x + cos(dir) * dis;			//自機移動
	pos.y = pos.y + sin(dir) * dis;			//自機移動
	/*移動取り消し*/
	if(pos.x < SCREEN_INDENT){
		pos.x = SCREEN_INDENT;
	}
	if(pos.y < 0){
		pos.y = 0;
	}
	if(pos.x > SCREEN_WIDTH - SCREEN_INDENT - size){
		pos.x = SCREEN_WIDTH - SCREEN_INDENT - size;
	}
	if(pos.y > SCREEN_HEIGHT - size){
		pos.y = SCREEN_HEIGHT - size;
	}

	/*コアの更新*/
	if(PartsBSptr tmp = core.lock()){
		tmp->setPos(Vec2(pos.x, pos.y));
		tmp->update(game);	//コア更新（探索木）
	}

	/*回避値の更新*/
	addKaihi(-4);
		
}

} //namespace tm2