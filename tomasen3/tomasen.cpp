
#include <cassert>
#include <cmath>

#include "tomasen.hpp"
#include "event.hpp"
#include "obj_effect.hpp"
#include "obj_wing_friend.hpp"

namespace tm2{

/*コンストラクタ*/
Tomasen::Tomasen(){
	//画像クラスの初期化
	IMAGE = new TipTile();

	//音楽クラスの初期化
	MUSIC = new Music();

	return;
}

/*::::::::メインループ::::::::*/
void Tomasen::runGame(HWND _hWnd){
	Tomasen::hWnd = _hWnd;

	hiscore = 9999;
	//１プレイループ
	while(gameEnd != 1){
		//ゲーム全体の初期化
		Tomasen::initGame();
		
		//フレームループ
		while(gameRestart != 1){
			Tomasen::inputGame();			//入力処理
			CheckTime(0);
			Tomasen::communicationGame();	//伝達処理
			CheckTime(1);
			Tomasen::updateGame();			//更新処理
			CheckTime(2);
			Tomasen::deleteGame();			//削除処理
			CheckTime(3);
			Tomasen::printGame();			//描画処理
			CheckTime(4);

			MUSIC->Check();
			CheckTime(5);

			await(15);
			CheckTime(6);
		}
	};

	return;
}

/*::::::::初期処理::::::::*/
void Tomasen::initGame(){

	//ゲームエンド変数の初期化
	gameResult = 0;
	gameClear = 0;
	gameRestart = 0;
	gameEnd = 0;
	bossFlag = 0;

	/*グローバルの初期化*/
	eventList.clear();
	effectList.clear();
	friendBulletList.clear();
	enemyBulletList.clear();
	partsAList.clear();
	partsBList.clear();
	barList.clear();
	labelList.clear();
	friendList.clear();
	enemyList.clear();

	/*初期予約*/
	eventList.reserve(10);
	effectList.reserve(500);
	friendBulletList.reserve(500);
	enemyBulletList.reserve(500);
	partsAList.reserve(100);
	partsBList.reserve(100);
	barList.reserve(10);
	labelList.reserve(10);
	friendList.reserve(10);
	enemyList.reserve(500);

	stringV.clear();
	

	/*乱数の初期化*/
	srand((unsigned int)1);

	/*画像クラスの下準備*/
	IMAGE->init(hWnd, TEXT("image/image.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT);
	IMAGE->setBasicColor(	IMAGE->tipNo(9,16), IMAGE->tipNo(10,16), IMAGE->tipNo(12,16),	//R, G, B
							IMAGE->tipNo(0,16), IMAGE->tipNo(15,16));						//B, W

	/*音楽クラスのした準備*/
	musicBGM_1 = MUSIC->Open("music/STAGE_MAIN_1.wav");
	musicBGM_2 = MUSIC->Open("music/game.wav");
	musicBGM_3 = MUSIC->Open("music/BGM_1.wav");
	musicBGM_4 = MUSIC->Open("music/BGM_3.wav");
	musicBGM_5 = MUSIC->Open("music/BGM_5.wav");
	musicShot = MUSIC->Open("music/Shot.wav");
	musicEnemyDown = MUSIC->Open("music/EnemyDown.wav");
	musicFriendHit = MUSIC->Open("music/bomb.wav");
	musicDead1 = MUSIC->Open("music/dead1.wav");
	musicDead2 = MUSIC->Open("music/dead2.wav");
	musicDead3 = MUSIC->Open("music/dead3.wav");
	musicDead4 = MUSIC->Open("music/dead4.wav");
	musicHadou = MUSIC->Open("music/beamgun2.wav");
	musicSakebi = MUSIC->Open("music/SKB49.wav");
	musicKaiten = MUSIC->Open("music/TurnCannon.wav");
	musicAlarm = MUSIC->Open("music/Alarm.wav");
	musicBakuhatsu = MUSIC->Open("music/bombSE.wav");
	musicHaretsu = MUSIC->Open("music/CrushSE.wav");
	musicHidan = MUSIC->Open("music/EnemyDamage.wav");
	musicKikanho = MUSIC->Open("music/Machingun.wav");
	musicFami = MUSIC->Open("music/FollowMissile.wav");
	musicWarp = MUSIC->Open("music/EnemyWarp.wav");
	musicBiribiri = MUSIC->Open("music/ChangeForm.wav");
	musicMissile = MUSIC->Open("music/Missile.wav");
	

	/*音楽の再生*/
	MUSIC->Stop();
	MUSIC->setTargetVol(musicBGM_1, 250);
	MUSIC->setVolume(musicBGM_1, 100);
	MUSIC->Play(musicBGM_1, 81920, 42200);

	/*各種初期設定*/
	canInput = false;			//入力可否フラグ
	stage = startStage;			//初期ステージの設定
	mode = startMode;			//初期画面の設定
	gold = 0;
	score = 0;
	stringV.push_back("←↑↓→　キー：移動");
	stringV.push_back("Shift:縮小 Z:射撃 X:主砲");

	/*自機配置*/
	kosenWing = friendFactory( 
		FriendSptr(new KosenWing(*this)), Vec2(startPosX, startPosY) );	//弱スマポを取得

	/*ゲージの初期化*/	
	hpBar = barFactory( BarSptr(new HpBar()) );			//弱スマポを取得
	energyBar = barFactory( BarSptr(new EnergyBar()) );	//弱スマポを取得
	manBar = barFactory( BarSptr(new ManBar()) );		//弱スマポを取得
	fireBar = barFactory( BarSptr(new FireBar()) );		//弱スマポを取得


	/*ラベルの初期化*/
	goldLabel = labelFactory( LabelSptr(new GoldLabel()) );		//弱スマポを取得
	scoreLabel = labelFactory( LabelSptr(new ScoreLabel()) );	//弱スマポを取得
	hiscoreLabel = labelFactory( LabelSptr(new HiScoreLabel()) );	//弱スマポを取得

	
	if(LabelSptr tmp = hiscoreLabel.lock()){				
		tmp->setValue( hiscore );			//スコアの更新
	}
	/*イベントの設置*/
	eventFactory( EventSptr(new GameTitle()) );	//イベントを生成してリストへ
}

/*::::::::入力処理::::::::*/
void Tomasen::inputGame(){
	/*自機に対する入力*/
	shotPerm = 0;
	if(!canInput) return;
	if(FriendSptr tmp = kosenWing.lock()){
		/*デモ入力*/
		if(mode == -1){
			if( (inputLog[tmp->getFrameCnt()] >> 0) & 1 ){
				tmp->setMove(Vec2(0, -moveAmount) + tmp->getMove() );	//自機を上に移動
			}
			if( (inputLog[tmp->getFrameCnt()] >> 1) & 1 ) {//↓
				tmp->setMove(Vec2(0, moveAmount) + tmp->getMove() );	//自機を下に移動
			}
			if( (inputLog[tmp->getFrameCnt()] >> 2) & 1 ) {//←
				tmp->setMove(Vec2(-moveAmount, 0) + tmp->getMove() );	//自機を左に移動
			}
			if( (inputLog[tmp->getFrameCnt()] >> 3) & 1 ) {//→
				tmp->setMove(Vec2(moveAmount, 0) + tmp->getMove() );	//自機を右に移動
			}
			prevShot--;
			if( (inputLog[tmp->getFrameCnt()] >> 4) & 1 ) {//Z
				if(prevShot <= 0){
					prevShot = 5;
					shotPerm = 1;											//射撃許可
				}
			}
			else{
				prevShot = 2;
			}
			if( (inputLog[tmp->getFrameCnt()] >> 5) & 1 ) {//X
				shotPerm = 2;											//射撃許可
			}
			if( (inputLog[tmp->getFrameCnt()] >> 6) & 1 ) {//Shift
				tmp->addKaihi(23);										//回避
			}
			if( (inputLog[tmp->getFrameCnt()] >> 7) & 1 || 
				GetAsyncKeyState(VK_ESCAPE) ||
				GetAsyncKeyState(VK_SPACE)) {//ESCAPE
				gameRestart = 1;		//リスタート	
				await(500);
			}
		}
		/*キー入力更新*/
		else{
			if(GetAsyncKeyState(VK_UP)){//↑
				inputLog[tmp->getFrameCnt()] |= 1 << 0;
				tmp->setMove(Vec2(0, -moveAmount) + tmp->getMove() );	//自機を上に移動
			}
			if(GetAsyncKeyState(VK_DOWN)) {//↓
				inputLog[tmp->getFrameCnt()] |= 1 << 1;
				tmp->setMove(Vec2(0, moveAmount) + tmp->getMove() );	//自機を下に移動
			}
			if(GetAsyncKeyState(VK_LEFT)) {//←
				inputLog[tmp->getFrameCnt()] |= 1 << 2;
				tmp->setMove(Vec2(-moveAmount, 0) + tmp->getMove() );	//自機を左に移動
			}
			if(GetAsyncKeyState(VK_RIGHT)) {//→
				inputLog[tmp->getFrameCnt()] |= 1 << 3;
				tmp->setMove(Vec2(moveAmount, 0) + tmp->getMove() );	//自機を右に移動
			}
			prevShot--;
			if(GetAsyncKeyState('Z')) {//Z
				inputLog[tmp->getFrameCnt()] |= 1 << 4;
				if(prevShot <= 0){
					prevShot = 5;
					shotPerm = 1;											//射撃許可
				}
			}
			else{
				prevShot = 2;
			}
			if(GetAsyncKeyState('X')) {//Z
				inputLog[tmp->getFrameCnt()] |= 1 << 5;
				shotPerm = 2;											//射撃許可
			}
			if(GetAsyncKeyState(VK_SHIFT)) {//Shift
				inputLog[tmp->getFrameCnt()] |= 1 << 6;
				tmp->addKaihi(23);										//回避
			}
			if(GetAsyncKeyState(VK_ESCAPE)) {//ESCAPE
				inputLog[tmp->getFrameCnt()] |= 1 << 7;
				gameRestart = 1;		//リスタート	
				await(500);
			}
		}
	}

} 

/*::::::::伝達処理::::::::*/
void Tomasen::communicationGame(){

	/*ハイスコア更新*/
	if(score > hiscore){
		hiscore = score;
	}
	/*ゲージ表示の伝達*/
	if(FriendSptr tmp = kosenWing.lock()){		
		if(BarSptr tmp2 = hpBar.lock()){				
			tmp2->setValue( tmp->getHp() );					//現在HPの更新
			tmp2->setMaxValue( tmp->getMaxHp() );			//最大HPの更新
			tmp2->setStartValue( tmp->getStartHp() );		//初期HPの更新
		}
		if(BarSptr tmp2 = energyBar.lock()){				
			tmp2->setValue( tmp->getEnergy() );				//現在ENの更新
			tmp2->setMaxValue( tmp->getMaxEnergy() );		//最大ENの更新
			tmp2->setStartValue( tmp->getStartEnergy() );	//初期ENの更新
		}
		if(BarSptr tmp2 = manBar.lock()){				
			tmp2->setValue( tmp->getMan() );				//現在人の更新
			tmp2->setMaxValue( tmp->getMaxMan() );			//最大人の更新
			tmp2->setStartValue( tmp->getStartMan() );		//初期人の更新
		}
		if(BarSptr tmp2 = fireBar.lock()){				
			tmp2->setValue( tmp->getFire() );				//現在炎の更新
			tmp2->setMaxValue( tmp->getBurnFire() );		//発火炎の更新
			tmp2->setStartValue( tmp->getMaxFire() );		//最大炎の更新
		}
	}

	/*ラベルの更新*/
	if(LabelSptr tmp = goldLabel.lock()){				
		tmp->setValue( gold );			//ゴールドの更新
	}
	if(LabelSptr tmp = scoreLabel.lock()){				
		tmp->setValue( score );			//スコアの更新
	}
	if(LabelSptr tmp = hiscoreLabel.lock()){				
		tmp->setValue( hiscore );		//ハイスコアの更新
	}

	/*リザルトの表示*/
	//ゲームオーバー時及びゲームクリア時にリザルトフラグを立てる
	if(gameResult == 1){
		gameResult++;
		if(FriendSptr tmp = kosenWing.lock()){
			//自機のHPを確認し、ゲームオーバーとゲームクリアを判別
			if(tmp->getHp() == 0){
				eventFactory( EventSptr(new GameOver()) );	//イベントを生成してリストへ
			}else{
				eventFactory( EventSptr(new GameClear()) );	//イベントを生成してリストへ
			}
		}

		//本来は各イベント内で出力すれば良いがゲームのデータを渡したいためtomasen内でオブジェクト生成している
		resultManLabel = labelFactory( LabelSptr(new ResultManLabel()) );	//生存者表示
		if(FriendSptr tmp = kosenWing.lock()){		
			if(LabelSptr tmp2 = resultManLabel.lock()){				
				tmp2->setValue( tmp->getMan() );				//現在人の更新
			}
		}
		resultScoreLabel = labelFactory( LabelSptr(new ResultScoreLabel()) );	//スコア表示
		if(LabelSptr tmp2 = resultScoreLabel.lock()){				
			tmp2->setValue( score );				//スコアの更新
		}
	}
}

/*::::::::更新処理::::::::*/
void Tomasen::updateGame(){

	/*イベントの更新処理*/
	for(EventVsptr::iterator it = eventList.begin(); it != eventList.end(); it++){
		(*it)->update(*this);
	}
	for(EventVsptr::iterator it = eventList.begin(); it != eventList.end(); it++){
		(*it)->action(*this);
	}

	/*敵機の更新*/
	for(EnemyVsptr::iterator it = enemyList.begin(); it != enemyList.end(); it++){
		Object dummy;
		(*it)->update(*this);
		(*it)->action(dummy);
	}

	/*自機系統の更新*/
	if(FriendSptr tmp = kosenWing.lock()){
		tmp->update(*this);	//自機更新（探索木）
	}
	/*分離後土台パーツ固有の処理*/
	for(PartsBVsptr::iterator it = partsBList.begin(); it != partsBList.end(); it++){
		if((*it)->getJointParent() == 0){
			(*it)->update(*this);
		}
	}
	/*各兵装パーツ固有の処理*/
	for(PartsAVsptr::iterator it = partsAList.begin(); it != partsAList.end(); it++){
		(*it)->action(*this);
	}

	/*自弾更新処理*/
	for(FriendBulletVsptr::iterator it = friendBulletList.begin(); it != friendBulletList.end(); it++){
		(*it)->update(*this);
	}

	/*敵弾更新処理*/
	for(EnemyBulletVsptr::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); it++){
		Object dummy;
		(*it)->update(*this);
		(*it)->action(dummy);
	}

	/*エフェクト更新処理*/
	for(EffectVsptr::iterator it = effectList.begin(); it != effectList.end(); it++){
		(*it)->update(*this);
	}

	/*バーの更新*/
	for(BarVsptr::iterator it = barList.begin(); it != barList.end(); it++){
		(*it)->update(*this);
	}

	/*ラベルの更新*/
	for(LabelVsptr::iterator it = labelList.begin(); it != labelList.end(); it++){
		(*it)->update(*this);
	}
	/*その他系統の更新*/
}

/*::::::::削除処理::::::::*/
void Tomasen::deleteGame(){

	/*エフェクト消滅判定*/
	for(EffectVsptr::iterator it = effectList.begin(); it != effectList.end(); ){
		if((*it)->getTimeOfLife() == 0){	//時間消滅
			it = effectList.erase(it);
			continue;
		}
		if(isIn(0 - wideArea, SCREEN_WIDTH + wideArea, 
				0 - wideArea, SCREEN_HEIGHT + wideArea, 
				(int)( (*it)->getPos().x + (*it)->getSize()/2 ), 
				(int)( (*it)->getPos().y + (*it)->getSize()/2 ) ) == false){	//画面外消滅
			it = effectList.erase(it);
			continue;
		}
		it++;
	}

	/*イベント終了フラグ判定*/
	/*各イベント内でnextに1以上が設定された場合。
	　そのイベントを終了とみなしnextで指定された分岐へジャンプする。*/
	for(EventVsptr::iterator it = eventList.begin(); it != eventList.end(); ){
		int next = (*it)->nextEvent();
		if(next > 0){	//フラグ判定
			it = eventList.erase(it);
			switch(next){
			case 1:
				if(FriendSptr tmp = kosenWing.lock()){
					tmp->setFrameCnt(0);	//自機のカウントを初期化
				}
				MUSIC->Stop();
				MUSIC->Play(musicBGM_2, 70000, 7000);
				//stringV.push_back("Stage1開始");
				eventFactory( EventSptr(new Stage1()) );
				//eventFactory(EventSptr(new GameClear()));
				break;
			case 2:
				//stringV.push_back("Stage2開始");
				eventFactory( EventSptr(new Stage2()) );
				break;
			case 3:
				//stringV.push_back("Stage3開始");
				eventFactory( EventSptr(new Stage3()) );
				break;
			case 4:
				//stringV.push_back("Stage4開始");
				eventFactory( EventSptr(new Stage4()) );
				break;
			case 5:
				//stringV.push_back("Stage5開始");
				eventFactory( EventSptr(new Stage5()) );
				break;
			case 6:
				MUSIC->Stop();
				MUSIC->Play(musicBGM_5);
				//stringV.push_back("ゲームクリア");
				eventFactory( EventSptr(new GameClear()) );
				break;
			case 998:
				//ゲーム初期化
				gameRestart = 1;
				break;
			case 999:
				//ゲーム終了
				gameRestart = 1;
				gameEnd = 1;
				break;
			case 1000:
				//デモモード
				//stringV.push_back("デモ開始");
				mode = -1; //デモモード
				//自機カウントの初期化
				if(FriendSptr tmp = kosenWing.lock()){
					tmp->setFrameCnt(0);
				}
				eventFactory( EventSptr(new Stage1()) );
				break;
			case 1001:
				//スタッフロール
				//stringV.push_back("スタッフロール");
				eventFactory( EventSptr(new StaffRoll()) );
				break;
			}
			canInput = true;
			break;
		}
		it++;
	}


	/*自弾当たり判定*/
	for(FriendBulletVsptr::iterator it = friendBulletList.begin(); it != friendBulletList.end(); it++){
		double bulletX = (*it)->getPos().x + (*it)->getOutputW()*tipSize / 2;		//自弾X座標
		double bulletY = (*it)->getPos().y + (*it)->getOutputH()*tipSize / 2;		//自弾Y座標
		int bulletSize = (*it)->getSize() / 2;	//自弾サイズ
		int bulletHp = (*it)->getHp();		//自弾耐久度
		for(EnemyVsptr::iterator it2 = enemyList.begin(); it2 != enemyList.end(); it2++){
			double enemyX = (*it2)->getPos().x + (*it2)->getOutputW()*tipSize / 2;	//敵機X座標
			double enemyY = (*it2)->getPos().y + (*it2)->getOutputH()*tipSize / 2;	//敵機Y座標
			int enemySize = (*it2)->getSize() / 2;//敵機サイズ
			int enemyHp = (*it2)->getHp();	//敵機耐久度
			if(	(bulletX - enemyX) * (bulletX - enemyX) + 
			(bulletY - enemyY) * (bulletY - enemyY) <
			(bulletSize + enemySize) * (bulletSize + enemySize) ){
				(*it)->damageHp(enemyHp);	//自弾耐久度減少
				(*it2)->damageHp(bulletHp);	//敵機耐久度減少
				MUSIC->Play(musicHidan);		//被弾音
			}
			
		}
	}
	/*自弾消滅判定*/
	for(FriendBulletVsptr::iterator it = friendBulletList.begin(); it != friendBulletList.end();){
		if(isIn(SCREEN_INDENT, SCREEN_WIDTH - SCREEN_INDENT, 0, SCREEN_HEIGHT, 
				(int)( (*it)->getPos().x + (*it)->getSize()/2 ), 
				(int)( (*it)->getPos().y + (*it)->getSize()/2 ) ) == false){	//画面外消滅
			it = friendBulletList.erase(it);
			continue;
		}
		if((*it)->getHp() == 0){	//耐久度消滅
			it = friendBulletList.erase(it);
			continue;
		}
		it++;
	}

	/*敵機当たり判定*/
	for(EnemyVsptr::iterator it = enemyList.begin(); it != enemyList.end(); it++){
		double EnemyX = (*it)->getPos().x + (*it)->getOutputW()*tipSize / 2;		//敵機X座標
		double EnemyY = (*it)->getPos().y + (*it)->getOutputH()*tipSize / 2;		//敵機Y座標
		int EnemySize = (*it)->getSize() / 2;		//敵機サイズ
		int EnemyHp = (*it)->getHp();			//敵機耐久度
		/*対パーツA*/
		for(PartsAVsptr::iterator it2 = partsAList.begin(); it2 != partsAList.end(); it2++){
			double partsX = (*it2)->getPos().x + (*it2)->getOutputW()*tipSize / 2;	//パーツX座標
			double partsY = (*it2)->getPos().y + (*it2)->getOutputH()*tipSize / 2;	//パーツY座標
			int partsSize = (*it2)->getSize() / 2;	//パーツサイズ
			int partsHp = (*it2)->getHp();		//パーツ耐久度
			if(	(EnemyX - partsX) * (EnemyX - partsX) + 
			(EnemyY - partsY) * (EnemyY - partsY) <
			(EnemySize + partsSize) * (EnemySize + partsSize) ){
				(*it)->damageHp(partsHp);			//敵機耐久度減少
				(*it2)->damageHp(EnemyHp);			//パーツ耐久度減少
				MUSIC->Play(musicFriendHit);		//被弾音
			}
		}
		EnemyHp = (*it)->getHp();			//敵弾耐久度
		/*対パーツB*/
		for(PartsBVsptr::iterator it2 = partsBList.begin(); it2 != partsBList.end(); it2++){
			double partsX = (*it2)->getPos().x + (*it2)->getOutputW()*tipSize / 2;	//パーツX座標
			double partsY = (*it2)->getPos().y + (*it2)->getOutputH()*tipSize / 2;	//パーツY座標
			int partsSize = (*it2)->getSize() / 2;	//パーツサイズ
			int partsHp = (*it2)->getHp();		//パーツ耐久度
			if(	(EnemyX - partsX) * (EnemyX - partsX) + 
			(EnemyY - partsY) * (EnemyY - partsY) <
			(EnemySize + partsSize) * (EnemySize + partsSize) ){
				(*it)->damageHp(partsHp);			//敵機耐久度減少
				(*it2)->damageHp(EnemyHp);			//パーツ耐久度減少
				MUSIC->Play(musicFriendHit);		//被弾音
			}
		}
	}
	/*敵機消滅判定*/
		for(EnemyVsptr::iterator it = enemyList.begin(); it != enemyList.end(); ){
			if(isIn(0 - wideArea, SCREEN_WIDTH + wideArea, 
					0 - wideArea, SCREEN_HEIGHT + wideArea, 
					(int)( (*it)->getPos().x + (*it)->getSize()/2 ), 
					(int)( (*it)->getPos().y + (*it)->getSize()/2 ) ) == false){	//画面外消滅
				it = enemyList.erase(it);
				continue;
			}
			if((*it)->getHp() <= 0){					//耐久度消滅
				//ボス削除判定
				if((*it)->getBoss() == 1){
					bossFlag++;
				}

				score += (*it)->getMaxHp() * 10;		//スコア加算
				
				//爆炎
				effectFactory(EffectSptr(new Explosion()), 
					(*it)->getPos(), Vec2( (*it)->getPos().x, (*it)->getPos().y - 100.0 )
					);
				
				switch(makeRand(3)){
				case 0://円形爆炎
					for(double cnt = 0; cnt < PI*2; cnt += PI*2 / 8){
						effectFactory(EffectSptr(new Explosion()), 
							(*it)->getPos(), 
							Vec2( (*it)->getPos().x + sin(cnt) * 100.0, 
								(*it)->getPos().y + cos(cnt) * 100.0 )
							);
						MUSIC->Play(musicEnemyDown);			//爆破音
					}
					break;
				case 1://十時
					for(double cnt = 0; cnt < PI*2; cnt += PI*2 / 5){
						for(int cnt2 = 0; cnt2 < 5; cnt2++){
							effectFactory(EffectSptr(new Explosion()), 
								(*it)->getPos(), 
								Vec2( (*it)->getPos().x + sin(cnt) * 100.0, 
									(*it)->getPos().y + cos(cnt) * 100.0 )
								);
							EffectVsptr::iterator it = effectList.end() - 1;		//直前のオブジェクトを参照
							(*it)->setDis(cnt2);						//距離
							(*it)->setDir(cnt);						//距離
							(*it)->setMoveMode(1);						//移動モード
							MUSIC->Play(musicEnemyDown);			//爆破音
						}
					}
					break;
				case 2://ランダム
						for(int cnt2 = 0; cnt2 < 5; cnt2++){
							effectFactory(EffectSptr(new Explosion()),
								(*it)->getPos(), 
								Vec2( (*it)->getPos().x + makeRand(0.0, 50), 
									(*it)->getPos().y + makeRand(0.0, 50) )
								);
							MUSIC->Play(musicEnemyDown);			//爆破音
						}
					break;
				}
				//破片
				effectFactory(EffectSptr(new Dust1()), 
					(*it)->getPos(), Vec2( (*it)->getPos().x + makeRand(0.0, 100), (*it)->getPos().y + makeRand(0.0, 100))
					);
				effectFactory(EffectSptr(new Dust1()), 
					(*it)->getPos(), Vec2( (*it)->getPos().x + makeRand(0.0, 100), (*it)->getPos().y + makeRand(0.0, 100))
					);
				effectFactory(EffectSptr(new Dust1()), 
					(*it)->getPos(), Vec2( (*it)->getPos().x + makeRand(0.0, 100), (*it)->getPos().y + makeRand(0.0, 100))
					);
				effectFactory(EffectSptr(new Dust1()), 
					(*it)->getPos(), Vec2( (*it)->getPos().x + makeRand(0.0, 100), (*it)->getPos().y + makeRand(0.0, 100))
					);
				it = enemyList.erase(it);
				continue;
			}
			it++;
		}


	/*敵弾当たり判定*/
	for(EnemyBulletVsptr::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); it++){
		double bulletX = (*it)->getPos().x + (*it)->getOutputW()*tipSize / 2;		//敵弾X座標
		double bulletY = (*it)->getPos().y + (*it)->getOutputH()*tipSize / 2;		//敵弾Y座標
		int bulletSize = (*it)->getSize() / 2;		//敵弾サイズ
		int bulletHp = (*it)->getHp();			//敵弾耐久度
		int bulletFire = (*it)->getFire();		//弾の火力
		/*対パーツA*/
		for(PartsAVsptr::iterator it2 = partsAList.begin(); it2 != partsAList.end(); it2++){
			double partsX = (*it2)->getPos().x + (*it2)->getOutputW()*tipSize / 2;	//パーツX座標
			double partsY = (*it2)->getPos().y + (*it2)->getOutputH()*tipSize / 2;	//パーツY座標
			int partsSize = (*it2)->getSize() / 2;	//パーツサイズ
			int partsHp = (*it2)->getHp();		//パーツ耐久度
			if(	(bulletX - partsX) * (bulletX - partsX) + 
			(bulletY - partsY) * (bulletY - partsY) <
			(bulletSize + partsSize) * (bulletSize + partsSize) ){
				(*it)->damageHp(partsHp);			//敵弾耐久度減少
				(*it2)->damageHp(bulletHp);			//パーツ耐久度減少
				(*it2)->killMan(bulletHp);			//殺傷
				(*it2)->addFire( bulletFire );		//火力ダメージ
				//爆炎
				effectFactory(EffectSptr(new Explosion()), 
					(*it)->getPos(), 
					Vec2( (*it)->getPos().x + makeRand(0.0, 50), 
						(*it)->getPos().y + makeRand(200.0, 60) )
					);
				//MUSIC->Play(musicDead3);		//被弾音
				MUSIC->Play(musicSakebi);		//被弾音
			}
		}
		bulletHp = (*it)->getHp();			//敵弾耐久度
		/*対パーツB*/
		for(PartsBVsptr::iterator it2 = partsBList.begin(); it2 != partsBList.end(); it2++){
			double partsX = (*it2)->getPos().x + (*it2)->getOutputW()*tipSize / 2;	//パーツX座標
			double partsY = (*it2)->getPos().y + (*it2)->getOutputW()*tipSize / 2;	//パーツY座標
			int partsSize = (*it2)->getSize() / 2;	//パーツサイズ
			int partsHp = (*it2)->getHp();		//パーツ耐久度
			if(	(bulletX - partsX) * (bulletX - partsX) + 
			(bulletY - partsY) * (bulletY - partsY) <
			(bulletSize + partsSize) * (bulletSize + partsSize) ){
				(*it)->damageHp(partsHp);			//敵弾耐久度減少
				(*it2)->damageHp(bulletHp);			//パーツ耐久度減少
				(*it2)->killMan(bulletHp);			//殺傷
				(*it2)->addFire( bulletFire );		//火力ダメージ
				//爆炎
				effectFactory(EffectSptr(new Explosion()), 
					(*it)->getPos(), 
					Vec2( (*it)->getPos().x + makeRand(0.0, 30), 
						(*it)->getPos().y + makeRand(250.0, 90) )
					);
				/*for(double cnt = 0; cnt < PI*2; cnt += PI*2 / 8){
					effectFactory(EffectSptr(new Explosion()), 
						(*it)->getPos(), 
						Vec2( (*it)->getPos().x + sin(cnt) * 100.0, 
							(*it)->getPos().y + cos(cnt) * 100.0 )
						);
				}*/

				MUSIC->Play(musicDead1);		//被弾音
			}
		}
	}
	/*敵弾消滅判定*/
	for(EnemyBulletVsptr::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ){
		if(isIn(SCREEN_INDENT, SCREEN_WIDTH - SCREEN_INDENT, 0, SCREEN_HEIGHT, 
				(int)( (*it)->getPos().x + (*it)->getSize()/2 ), 
				(int)( (*it)->getPos().y + (*it)->getSize()/2 ) ) == false){	//画面外消滅
			it = enemyBulletList.erase(it);
			continue;
		}
		if((*it)->getHp() <= 0){	//耐久度消滅
			it = enemyBulletList.erase(it);
			continue;
		}
		it++;
	}

	/*パーツA消滅判定*/
	for(PartsAVsptr::iterator it = partsAList.begin(); it != partsAList.end(); ){
		if((*it)->getHp() <= 0){	//耐久度消滅
			it = partsAList.erase(it);
			MUSIC->Play(musicBakuhatsu);		//破壊音
			continue;
		}
		it++;
	}
	/*パーツB消滅判定*/
	for(PartsBVsptr::iterator it = partsBList.begin(); it != partsBList.end(); ){
		if((*it)->getHp() <= 0){	//耐久度消滅
			it = partsBList.erase(it);
			continue;
		}
		if((*it)->getFrameCnt() >= 100 && (*it)->getPos().y >= SCREEN_HEIGHT + 200){	//画面外消滅
			it = partsBList.erase(it);
			continue;
		}
		it++;
	}


}

/*::::::::表示処理::::::::*/
void Tomasen::printGame(){
	/*画面の塗りつぶし*/
	IMAGE->drawTip(	0.0, 0.0, 
					(double)SCREEN_WIDTH, (double)SCREEN_HEIGHT, 
					IMAGE->getBlack());
	/*エフェクト描画処理*/
	for(EffectVsptr::iterator it = effectList.begin(); it != effectList.end(); it++){
		(*it)->draw(*this);
	}
	/*パーツB描画処理*/
	for(PartsBVsptr::iterator it = partsBList.begin(); it != partsBList.end(); it++){
		(*it)->draw(*this);
	}
	/*パーツA描画処理 優先順位=0*/
	for(PartsAVsptr::iterator it = partsAList.begin(); it != partsAList.end(); it++){
		if( (*it)->getDrawPriority() == 0){
			(*it)->draw(*this);
		}
	}
	/*パーツA描画処理 優先順位=1*/
	for(PartsAVsptr::iterator it = partsAList.begin(); it != partsAList.end(); it++){
		if( (*it)->getDrawPriority() == 1){
			(*it)->draw(*this);
		}
	}
	
	/*自弾描画処理*/
	for(FriendBulletVsptr::iterator it = friendBulletList.begin(); it != friendBulletList.end(); it++){
		(*it)->draw(*this);
	}
	
	/*敵機描画処理*/
	for(EnemyVsptr::iterator it = enemyList.begin(); it != enemyList.end(); it++){
		(*it)->draw(*this);
	}
	
	/*敵弾描画処理*/
	for(EnemyBulletVsptr::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); it++){
		(*it)->draw(*this);
	}
	


	/*両側塗りつぶし*/
	IMAGE->drawTip(	0.0, 0.0, 
					(double)SCREEN_INDENT, (double)SCREEN_HEIGHT, 
					IMAGE->tipNo(4,16));
	IMAGE->drawTip(	(double)(SCREEN_WIDTH - SCREEN_INDENT), 0.0, 
					(double)SCREEN_INDENT, (double)SCREEN_HEIGHT, 
					IMAGE->tipNo(4,16));

	/*デバッグ文字列表示*/
	if(FriendSptr tmp = kosenWing.lock()){
		char str[256];
		sprintf_s(str, "A:%03d, B:%03d, cnt:%d", partsAList.size(), partsBList.size(), tmp->getFrameCnt());
		IMAGE->printText(0, 0, str);
		sprintf_s(str, "X:%+03.3f  MoveX:%+03.3f", tmp->getPos().x, tmp->getMove().x);
		IMAGE->printText(0, 1, str);
		sprintf_s(str, "Y:%+03.3f  MoveY:%+03.3f", tmp->getPos().y, tmp->getMove().y);
		IMAGE->printText(0, 2, str);
		sprintf_s(str, "自弾:%03d, 敵弾:%03d", friendBulletList.size(), enemyBulletList.size());
		IMAGE->printText(0, 3, str);
		sprintf_s(str, "敵機:%03d, Event数:%03d", enemyList.size(), eventList.size());
		IMAGE->printText(0, 4, str);
		sprintf_s(str, "effect:%03d, hp:%03d/%03d", effectList.size(), tmp->getHp(), tmp->getMaxHp());
		IMAGE->printText(0, 5, str);
		sprintf_s(str, "A:%03d/%03d, B:%03d/B:%03d",	tmp->getPartsANum(), tmp->getPartsANum() + tmp->getPartsALost(), 
														tmp->getPartsBNum(), tmp->getPartsBNum() + tmp->getPartsBLost());
		IMAGE->printText(0, 6, str);
		sprintf_s(str, "flag:%03d, mode:%03d", bossFlag, mode);
		IMAGE->printText(0, 7, str);
		sprintf_s(str, "time1:%03d, 2:%03d, 3:%03d, 4:%03d", checkTime[0], checkTime[1], checkTime[2], checkTime[3]);
		IMAGE->printText(0, 8, str);
		sprintf_s(str, "time5:%03d, 6:%03d, 7:%03d, 8:%03d", checkTime[4], checkTime[5], checkTime[6], checkTime[7]);
		IMAGE->printText(0, 9, str);
	}
	
	/*メッセージ欄枠*/
	IMAGE->drawFillTip(1, 15, 11, 20, IMAGE->tipNo(21,17));
	/*コマンド欄*/
	IMAGE->drawFillTip(1, 36, 11, 1, IMAGE->tipNo(21,17));

	/*メッセージ*/
	int cnt = 0;	//20件まで表示
	for(StringV::iterator it = stringV.begin(); it != stringV.end(); it++){
		IMAGE->printText(1, 15 + (20 - stringV.size()) + cnt, (*it).c_str());
		cnt++;
		if(cnt >= 20) break;
	}

	/*バーの表示*/
	for(BarVsptr::iterator it = barList.begin(); it != barList.end(); it++){
		(*it)->draw(*this);
	}
	
	/*ラベルの表示*/
	for(LabelVsptr::iterator it = labelList.begin(); it != labelList.end(); it++){
		(*it)->draw(*this);
	}

	/*レーダーの表示*/
	drawRader();

	/*ディスプレイに表示*/
	IMAGE->drawEnd();
}

/*::::::::レーダー表示処理::::::::*/
void Tomasen::drawRader(){

	/*
	左上 tipSize*38, tipSize*13
	右上 tipSize*49, tipSize*13
	左下 tipSize*38, tipSize*21
	右下 tipSize*49, tipSize*21
	*/
	const int lu_x = tipSize*38;
	const int lu_y = tipSize*13;
	const int w = tipSize*11;
	const int h = tipSize*8;
	const int haba = h * 4 / 5;
	
	const int ru_x = lu_x + w;
	const int ru_y = lu_y;
	const int ld_x = lu_x;
	const int ld_y = lu_y + h;
	const int rd_x = lu_x + w;
	const int rd_y = lu_y + h;


	/*走査線位置*/
	int drawCnt = 0;
	if(FriendSptr tmp = kosenWing.lock()){
		drawCnt = tmp->getFrameCnt()*2 % (int)(h*1.4);
	}

	/*下地*/
	IMAGE->drawFillTip(Vec2(lu_x, lu_y), w/tipSize, h/tipSize, IMAGE->tipNo(21,17));

	/*走査線*/
	if(drawCnt < h){
		IMAGE->drawTip(
			(double)ld_x, 
			(double)ld_y - drawCnt, 
			(double)w, 
			1.0, 
			IMAGE->getRed() );
		
		/*半透明*/
		IMAGE->drawAlphaBlendTip(
			(double)ld_x, 
			(double)ld_y - drawCnt + 1, 
			(double)w, 
			5.0, 
			IMAGE->getRed(),
			64);
		/*半透明*/
		IMAGE->drawAlphaBlendTip(
			(double)ld_x, 
			(double)ld_y - drawCnt + 6, 
			(double)w, 
			10.0, 
			IMAGE->getRed(),
			32);

	}

	/*敵機の描画*/
	for(EnemyVsptr::iterator it = enemyList.begin(); it != enemyList.end(); it++){
		if(ld_y - drawCnt < lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT &&//走査線より下かつ
			ld_y - drawCnt + haba > lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT){//habaピクセル以内
			IMAGE->drawTip(
				(double)lu_x + (*it)->getCenterPos().x * w / SCREEN_WIDTH , 
				(double)lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT, 
				1.0, 
				1.0, 
				IMAGE->getRed() );
		}
	}
	/*土台パーツ描画*/
	for(PartsBVsptr::iterator it = partsBList.begin(); it != partsBList.end(); it++){
		if(ld_y - drawCnt < lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT &&//走査線より下かつ
			ld_y - drawCnt + haba > lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT){//habaピクセル以内
			IMAGE->drawTip(
				(double)lu_x + (*it)->getCenterPos().x * w / SCREEN_WIDTH , 
				(double)lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT, 
				1.0, 
				1.0, 
				IMAGE->getBlue() );
		}
	}

	/*自弾描画*/
	for(FriendBulletVsptr::iterator it = friendBulletList.begin(); it != friendBulletList.end(); it++){
		if(ld_y - drawCnt < lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT &&//走査線より下かつ
			ld_y - drawCnt + haba > lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT){//habaピクセル以内
			IMAGE->drawTip(
				(double)lu_x + (*it)->getCenterPos().x * w / SCREEN_WIDTH , 
				(double)lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT, 
				1.0, 
				1.0, 
				IMAGE->getGreen() );
		}
	}

	/*敵弾描画*/
	for(EnemyBulletVsptr::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); it++){
		if(ld_y - drawCnt < lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT &&//走査線より下かつ
			ld_y - drawCnt + haba > lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT){//habaピクセル以内
			IMAGE->drawTip(
				(double)lu_x + (*it)->getCenterPos().x * w / SCREEN_WIDTH , 
				(double)lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT, 
				1.0, 
				1.0, 
				IMAGE->getWhite() );
		}
	}
	/*エフェクト描画処理*/
	for(EffectVsptr::iterator it = effectList.begin(); it != effectList.end(); it++){
		if(ld_y - drawCnt < lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT &&//走査線より下かつ
			ld_y - drawCnt + haba > lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT){//habaピクセル以内
			IMAGE->drawTip(
				(double)lu_x + (*it)->getCenterPos().x * w / SCREEN_WIDTH , 
				(double)lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT, 
				1.0, 
				1.0, 
				IMAGE->getBlack() );
		}
	}

}

/*::::::::デストラクタ::::::::*/
Tomasen::~Tomasen(){
	eventList.clear();
	effectList.clear();
	friendBulletList.clear();
	enemyBulletList.clear();
	partsAList.clear();
	partsBList.clear();
	barList.clear();
	labelList.clear();
	friendList.clear();
	enemyList.clear();
}


} //namespace tm2