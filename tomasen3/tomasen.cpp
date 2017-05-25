
#include <cassert>
#include <cmath>

#include "tomasen.hpp"
#include "event.hpp"
#include "obj_effect.hpp"
#include "obj_wing_friend.hpp"

namespace tm2{

/*�R���X�g���N�^*/
Tomasen::Tomasen(){
	//�摜�N���X�̏�����
	IMAGE = new TipTile();

	//���y�N���X�̏�����
	MUSIC = new Music();

	return;
}

/*::::::::���C�����[�v::::::::*/
void Tomasen::runGame(HWND _hWnd){
	Tomasen::hWnd = _hWnd;

	hiscore = 9999;
	//�P�v���C���[�v
	while(gameEnd != 1){
		//�Q�[���S�̂̏�����
		Tomasen::initGame();
		
		//�t���[�����[�v
		while(gameRestart != 1){
			Tomasen::inputGame();			//���͏���
			CheckTime(0);
			Tomasen::communicationGame();	//�`�B����
			CheckTime(1);
			Tomasen::updateGame();			//�X�V����
			CheckTime(2);
			Tomasen::deleteGame();			//�폜����
			CheckTime(3);
			Tomasen::printGame();			//�`�揈��
			CheckTime(4);

			MUSIC->Check();
			CheckTime(5);

			await(15);
			CheckTime(6);
		}
	};

	return;
}

/*::::::::��������::::::::*/
void Tomasen::initGame(){

	//�Q�[���G���h�ϐ��̏�����
	gameResult = 0;
	gameClear = 0;
	gameRestart = 0;
	gameEnd = 0;
	bossFlag = 0;

	/*�O���[�o���̏�����*/
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

	/*�����\��*/
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
	

	/*�����̏�����*/
	srand((unsigned int)1);

	/*�摜�N���X�̉�����*/
	IMAGE->init(hWnd, TEXT("image/image.bmp"), SCREEN_WIDTH, SCREEN_HEIGHT);
	IMAGE->setBasicColor(	IMAGE->tipNo(9,16), IMAGE->tipNo(10,16), IMAGE->tipNo(12,16),	//R, G, B
							IMAGE->tipNo(0,16), IMAGE->tipNo(15,16));						//B, W

	/*���y�N���X�̂�������*/
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
	

	/*���y�̍Đ�*/
	MUSIC->Stop();
	MUSIC->setTargetVol(musicBGM_1, 250);
	MUSIC->setVolume(musicBGM_1, 100);
	MUSIC->Play(musicBGM_1, 81920, 42200);

	/*�e�평���ݒ�*/
	canInput = false;			//���͉ۃt���O
	stage = startStage;			//�����X�e�[�W�̐ݒ�
	mode = startMode;			//������ʂ̐ݒ�
	gold = 0;
	score = 0;
	stringV.push_back("���������@�L�[�F�ړ�");
	stringV.push_back("Shift:�k�� Z:�ˌ� X:��C");

	/*���@�z�u*/
	kosenWing = friendFactory( 
		FriendSptr(new KosenWing(*this)), Vec2(startPosX, startPosY) );	//��X�}�|���擾

	/*�Q�[�W�̏�����*/	
	hpBar = barFactory( BarSptr(new HpBar()) );			//��X�}�|���擾
	energyBar = barFactory( BarSptr(new EnergyBar()) );	//��X�}�|���擾
	manBar = barFactory( BarSptr(new ManBar()) );		//��X�}�|���擾
	fireBar = barFactory( BarSptr(new FireBar()) );		//��X�}�|���擾


	/*���x���̏�����*/
	goldLabel = labelFactory( LabelSptr(new GoldLabel()) );		//��X�}�|���擾
	scoreLabel = labelFactory( LabelSptr(new ScoreLabel()) );	//��X�}�|���擾
	hiscoreLabel = labelFactory( LabelSptr(new HiScoreLabel()) );	//��X�}�|���擾

	
	if(LabelSptr tmp = hiscoreLabel.lock()){				
		tmp->setValue( hiscore );			//�X�R�A�̍X�V
	}
	/*�C�x���g�̐ݒu*/
	eventFactory( EventSptr(new GameTitle()) );	//�C�x���g�𐶐����ă��X�g��
}

/*::::::::���͏���::::::::*/
void Tomasen::inputGame(){
	/*���@�ɑ΂������*/
	shotPerm = 0;
	if(!canInput) return;
	if(FriendSptr tmp = kosenWing.lock()){
		/*�f������*/
		if(mode == -1){
			if( (inputLog[tmp->getFrameCnt()] >> 0) & 1 ){
				tmp->setMove(Vec2(0, -moveAmount) + tmp->getMove() );	//���@����Ɉړ�
			}
			if( (inputLog[tmp->getFrameCnt()] >> 1) & 1 ) {//��
				tmp->setMove(Vec2(0, moveAmount) + tmp->getMove() );	//���@�����Ɉړ�
			}
			if( (inputLog[tmp->getFrameCnt()] >> 2) & 1 ) {//��
				tmp->setMove(Vec2(-moveAmount, 0) + tmp->getMove() );	//���@�����Ɉړ�
			}
			if( (inputLog[tmp->getFrameCnt()] >> 3) & 1 ) {//��
				tmp->setMove(Vec2(moveAmount, 0) + tmp->getMove() );	//���@���E�Ɉړ�
			}
			prevShot--;
			if( (inputLog[tmp->getFrameCnt()] >> 4) & 1 ) {//Z
				if(prevShot <= 0){
					prevShot = 5;
					shotPerm = 1;											//�ˌ�����
				}
			}
			else{
				prevShot = 2;
			}
			if( (inputLog[tmp->getFrameCnt()] >> 5) & 1 ) {//X
				shotPerm = 2;											//�ˌ�����
			}
			if( (inputLog[tmp->getFrameCnt()] >> 6) & 1 ) {//Shift
				tmp->addKaihi(23);										//���
			}
			if( (inputLog[tmp->getFrameCnt()] >> 7) & 1 || 
				GetAsyncKeyState(VK_ESCAPE) ||
				GetAsyncKeyState(VK_SPACE)) {//ESCAPE
				gameRestart = 1;		//���X�^�[�g	
				await(500);
			}
		}
		/*�L�[���͍X�V*/
		else{
			if(GetAsyncKeyState(VK_UP)){//��
				inputLog[tmp->getFrameCnt()] |= 1 << 0;
				tmp->setMove(Vec2(0, -moveAmount) + tmp->getMove() );	//���@����Ɉړ�
			}
			if(GetAsyncKeyState(VK_DOWN)) {//��
				inputLog[tmp->getFrameCnt()] |= 1 << 1;
				tmp->setMove(Vec2(0, moveAmount) + tmp->getMove() );	//���@�����Ɉړ�
			}
			if(GetAsyncKeyState(VK_LEFT)) {//��
				inputLog[tmp->getFrameCnt()] |= 1 << 2;
				tmp->setMove(Vec2(-moveAmount, 0) + tmp->getMove() );	//���@�����Ɉړ�
			}
			if(GetAsyncKeyState(VK_RIGHT)) {//��
				inputLog[tmp->getFrameCnt()] |= 1 << 3;
				tmp->setMove(Vec2(moveAmount, 0) + tmp->getMove() );	//���@���E�Ɉړ�
			}
			prevShot--;
			if(GetAsyncKeyState('Z')) {//Z
				inputLog[tmp->getFrameCnt()] |= 1 << 4;
				if(prevShot <= 0){
					prevShot = 5;
					shotPerm = 1;											//�ˌ�����
				}
			}
			else{
				prevShot = 2;
			}
			if(GetAsyncKeyState('X')) {//Z
				inputLog[tmp->getFrameCnt()] |= 1 << 5;
				shotPerm = 2;											//�ˌ�����
			}
			if(GetAsyncKeyState(VK_SHIFT)) {//Shift
				inputLog[tmp->getFrameCnt()] |= 1 << 6;
				tmp->addKaihi(23);										//���
			}
			if(GetAsyncKeyState(VK_ESCAPE)) {//ESCAPE
				inputLog[tmp->getFrameCnt()] |= 1 << 7;
				gameRestart = 1;		//���X�^�[�g	
				await(500);
			}
		}
	}

} 

/*::::::::�`�B����::::::::*/
void Tomasen::communicationGame(){

	/*�n�C�X�R�A�X�V*/
	if(score > hiscore){
		hiscore = score;
	}
	/*�Q�[�W�\���̓`�B*/
	if(FriendSptr tmp = kosenWing.lock()){		
		if(BarSptr tmp2 = hpBar.lock()){				
			tmp2->setValue( tmp->getHp() );					//����HP�̍X�V
			tmp2->setMaxValue( tmp->getMaxHp() );			//�ő�HP�̍X�V
			tmp2->setStartValue( tmp->getStartHp() );		//����HP�̍X�V
		}
		if(BarSptr tmp2 = energyBar.lock()){				
			tmp2->setValue( tmp->getEnergy() );				//����EN�̍X�V
			tmp2->setMaxValue( tmp->getMaxEnergy() );		//�ő�EN�̍X�V
			tmp2->setStartValue( tmp->getStartEnergy() );	//����EN�̍X�V
		}
		if(BarSptr tmp2 = manBar.lock()){				
			tmp2->setValue( tmp->getMan() );				//���ݐl�̍X�V
			tmp2->setMaxValue( tmp->getMaxMan() );			//�ő�l�̍X�V
			tmp2->setStartValue( tmp->getStartMan() );		//�����l�̍X�V
		}
		if(BarSptr tmp2 = fireBar.lock()){				
			tmp2->setValue( tmp->getFire() );				//���݉��̍X�V
			tmp2->setMaxValue( tmp->getBurnFire() );		//���Ή��̍X�V
			tmp2->setStartValue( tmp->getMaxFire() );		//�ő削�̍X�V
		}
	}

	/*���x���̍X�V*/
	if(LabelSptr tmp = goldLabel.lock()){				
		tmp->setValue( gold );			//�S�[���h�̍X�V
	}
	if(LabelSptr tmp = scoreLabel.lock()){				
		tmp->setValue( score );			//�X�R�A�̍X�V
	}
	if(LabelSptr tmp = hiscoreLabel.lock()){				
		tmp->setValue( hiscore );		//�n�C�X�R�A�̍X�V
	}

	/*���U���g�̕\��*/
	//�Q�[���I�[�o�[���y�уQ�[���N���A���Ƀ��U���g�t���O�𗧂Ă�
	if(gameResult == 1){
		gameResult++;
		if(FriendSptr tmp = kosenWing.lock()){
			//���@��HP���m�F���A�Q�[���I�[�o�[�ƃQ�[���N���A�𔻕�
			if(tmp->getHp() == 0){
				eventFactory( EventSptr(new GameOver()) );	//�C�x���g�𐶐����ă��X�g��
			}else{
				eventFactory( EventSptr(new GameClear()) );	//�C�x���g�𐶐����ă��X�g��
			}
		}

		//�{���͊e�C�x���g���ŏo�͂���Ηǂ����Q�[���̃f�[�^��n����������tomasen���ŃI�u�W�F�N�g�������Ă���
		resultManLabel = labelFactory( LabelSptr(new ResultManLabel()) );	//�����ҕ\��
		if(FriendSptr tmp = kosenWing.lock()){		
			if(LabelSptr tmp2 = resultManLabel.lock()){				
				tmp2->setValue( tmp->getMan() );				//���ݐl�̍X�V
			}
		}
		resultScoreLabel = labelFactory( LabelSptr(new ResultScoreLabel()) );	//�X�R�A�\��
		if(LabelSptr tmp2 = resultScoreLabel.lock()){				
			tmp2->setValue( score );				//�X�R�A�̍X�V
		}
	}
}

/*::::::::�X�V����::::::::*/
void Tomasen::updateGame(){

	/*�C�x���g�̍X�V����*/
	for(EventVsptr::iterator it = eventList.begin(); it != eventList.end(); it++){
		(*it)->update(*this);
	}
	for(EventVsptr::iterator it = eventList.begin(); it != eventList.end(); it++){
		(*it)->action(*this);
	}

	/*�G�@�̍X�V*/
	for(EnemyVsptr::iterator it = enemyList.begin(); it != enemyList.end(); it++){
		Object dummy;
		(*it)->update(*this);
		(*it)->action(dummy);
	}

	/*���@�n���̍X�V*/
	if(FriendSptr tmp = kosenWing.lock()){
		tmp->update(*this);	//���@�X�V�i�T���؁j
	}
	/*������y��p�[�c�ŗL�̏���*/
	for(PartsBVsptr::iterator it = partsBList.begin(); it != partsBList.end(); it++){
		if((*it)->getJointParent() == 0){
			(*it)->update(*this);
		}
	}
	/*�e�����p�[�c�ŗL�̏���*/
	for(PartsAVsptr::iterator it = partsAList.begin(); it != partsAList.end(); it++){
		(*it)->action(*this);
	}

	/*���e�X�V����*/
	for(FriendBulletVsptr::iterator it = friendBulletList.begin(); it != friendBulletList.end(); it++){
		(*it)->update(*this);
	}

	/*�G�e�X�V����*/
	for(EnemyBulletVsptr::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); it++){
		Object dummy;
		(*it)->update(*this);
		(*it)->action(dummy);
	}

	/*�G�t�F�N�g�X�V����*/
	for(EffectVsptr::iterator it = effectList.begin(); it != effectList.end(); it++){
		(*it)->update(*this);
	}

	/*�o�[�̍X�V*/
	for(BarVsptr::iterator it = barList.begin(); it != barList.end(); it++){
		(*it)->update(*this);
	}

	/*���x���̍X�V*/
	for(LabelVsptr::iterator it = labelList.begin(); it != labelList.end(); it++){
		(*it)->update(*this);
	}
	/*���̑��n���̍X�V*/
}

/*::::::::�폜����::::::::*/
void Tomasen::deleteGame(){

	/*�G�t�F�N�g���Ŕ���*/
	for(EffectVsptr::iterator it = effectList.begin(); it != effectList.end(); ){
		if((*it)->getTimeOfLife() == 0){	//���ԏ���
			it = effectList.erase(it);
			continue;
		}
		if(isIn(0 - wideArea, SCREEN_WIDTH + wideArea, 
				0 - wideArea, SCREEN_HEIGHT + wideArea, 
				(int)( (*it)->getPos().x + (*it)->getSize()/2 ), 
				(int)( (*it)->getPos().y + (*it)->getSize()/2 ) ) == false){	//��ʊO����
			it = effectList.erase(it);
			continue;
		}
		it++;
	}

	/*�C�x���g�I���t���O����*/
	/*�e�C�x���g����next��1�ȏオ�ݒ肳�ꂽ�ꍇ�B
	�@���̃C�x���g���I���Ƃ݂Ȃ�next�Ŏw�肳�ꂽ����փW�����v����B*/
	for(EventVsptr::iterator it = eventList.begin(); it != eventList.end(); ){
		int next = (*it)->nextEvent();
		if(next > 0){	//�t���O����
			it = eventList.erase(it);
			switch(next){
			case 1:
				if(FriendSptr tmp = kosenWing.lock()){
					tmp->setFrameCnt(0);	//���@�̃J�E���g��������
				}
				MUSIC->Stop();
				MUSIC->Play(musicBGM_2, 70000, 7000);
				//stringV.push_back("Stage1�J�n");
				eventFactory( EventSptr(new Stage1()) );
				//eventFactory(EventSptr(new GameClear()));
				break;
			case 2:
				//stringV.push_back("Stage2�J�n");
				eventFactory( EventSptr(new Stage2()) );
				break;
			case 3:
				//stringV.push_back("Stage3�J�n");
				eventFactory( EventSptr(new Stage3()) );
				break;
			case 4:
				//stringV.push_back("Stage4�J�n");
				eventFactory( EventSptr(new Stage4()) );
				break;
			case 5:
				//stringV.push_back("Stage5�J�n");
				eventFactory( EventSptr(new Stage5()) );
				break;
			case 6:
				MUSIC->Stop();
				MUSIC->Play(musicBGM_5);
				//stringV.push_back("�Q�[���N���A");
				eventFactory( EventSptr(new GameClear()) );
				break;
			case 998:
				//�Q�[��������
				gameRestart = 1;
				break;
			case 999:
				//�Q�[���I��
				gameRestart = 1;
				gameEnd = 1;
				break;
			case 1000:
				//�f�����[�h
				//stringV.push_back("�f���J�n");
				mode = -1; //�f�����[�h
				//���@�J�E���g�̏�����
				if(FriendSptr tmp = kosenWing.lock()){
					tmp->setFrameCnt(0);
				}
				eventFactory( EventSptr(new Stage1()) );
				break;
			case 1001:
				//�X�^�b�t���[��
				//stringV.push_back("�X�^�b�t���[��");
				eventFactory( EventSptr(new StaffRoll()) );
				break;
			}
			canInput = true;
			break;
		}
		it++;
	}


	/*���e�����蔻��*/
	for(FriendBulletVsptr::iterator it = friendBulletList.begin(); it != friendBulletList.end(); it++){
		double bulletX = (*it)->getPos().x + (*it)->getOutputW()*tipSize / 2;		//���eX���W
		double bulletY = (*it)->getPos().y + (*it)->getOutputH()*tipSize / 2;		//���eY���W
		int bulletSize = (*it)->getSize() / 2;	//���e�T�C�Y
		int bulletHp = (*it)->getHp();		//���e�ϋv�x
		for(EnemyVsptr::iterator it2 = enemyList.begin(); it2 != enemyList.end(); it2++){
			double enemyX = (*it2)->getPos().x + (*it2)->getOutputW()*tipSize / 2;	//�G�@X���W
			double enemyY = (*it2)->getPos().y + (*it2)->getOutputH()*tipSize / 2;	//�G�@Y���W
			int enemySize = (*it2)->getSize() / 2;//�G�@�T�C�Y
			int enemyHp = (*it2)->getHp();	//�G�@�ϋv�x
			if(	(bulletX - enemyX) * (bulletX - enemyX) + 
			(bulletY - enemyY) * (bulletY - enemyY) <
			(bulletSize + enemySize) * (bulletSize + enemySize) ){
				(*it)->damageHp(enemyHp);	//���e�ϋv�x����
				(*it2)->damageHp(bulletHp);	//�G�@�ϋv�x����
				MUSIC->Play(musicHidan);		//��e��
			}
			
		}
	}
	/*���e���Ŕ���*/
	for(FriendBulletVsptr::iterator it = friendBulletList.begin(); it != friendBulletList.end();){
		if(isIn(SCREEN_INDENT, SCREEN_WIDTH - SCREEN_INDENT, 0, SCREEN_HEIGHT, 
				(int)( (*it)->getPos().x + (*it)->getSize()/2 ), 
				(int)( (*it)->getPos().y + (*it)->getSize()/2 ) ) == false){	//��ʊO����
			it = friendBulletList.erase(it);
			continue;
		}
		if((*it)->getHp() == 0){	//�ϋv�x����
			it = friendBulletList.erase(it);
			continue;
		}
		it++;
	}

	/*�G�@�����蔻��*/
	for(EnemyVsptr::iterator it = enemyList.begin(); it != enemyList.end(); it++){
		double EnemyX = (*it)->getPos().x + (*it)->getOutputW()*tipSize / 2;		//�G�@X���W
		double EnemyY = (*it)->getPos().y + (*it)->getOutputH()*tipSize / 2;		//�G�@Y���W
		int EnemySize = (*it)->getSize() / 2;		//�G�@�T�C�Y
		int EnemyHp = (*it)->getHp();			//�G�@�ϋv�x
		/*�΃p�[�cA*/
		for(PartsAVsptr::iterator it2 = partsAList.begin(); it2 != partsAList.end(); it2++){
			double partsX = (*it2)->getPos().x + (*it2)->getOutputW()*tipSize / 2;	//�p�[�cX���W
			double partsY = (*it2)->getPos().y + (*it2)->getOutputH()*tipSize / 2;	//�p�[�cY���W
			int partsSize = (*it2)->getSize() / 2;	//�p�[�c�T�C�Y
			int partsHp = (*it2)->getHp();		//�p�[�c�ϋv�x
			if(	(EnemyX - partsX) * (EnemyX - partsX) + 
			(EnemyY - partsY) * (EnemyY - partsY) <
			(EnemySize + partsSize) * (EnemySize + partsSize) ){
				(*it)->damageHp(partsHp);			//�G�@�ϋv�x����
				(*it2)->damageHp(EnemyHp);			//�p�[�c�ϋv�x����
				MUSIC->Play(musicFriendHit);		//��e��
			}
		}
		EnemyHp = (*it)->getHp();			//�G�e�ϋv�x
		/*�΃p�[�cB*/
		for(PartsBVsptr::iterator it2 = partsBList.begin(); it2 != partsBList.end(); it2++){
			double partsX = (*it2)->getPos().x + (*it2)->getOutputW()*tipSize / 2;	//�p�[�cX���W
			double partsY = (*it2)->getPos().y + (*it2)->getOutputH()*tipSize / 2;	//�p�[�cY���W
			int partsSize = (*it2)->getSize() / 2;	//�p�[�c�T�C�Y
			int partsHp = (*it2)->getHp();		//�p�[�c�ϋv�x
			if(	(EnemyX - partsX) * (EnemyX - partsX) + 
			(EnemyY - partsY) * (EnemyY - partsY) <
			(EnemySize + partsSize) * (EnemySize + partsSize) ){
				(*it)->damageHp(partsHp);			//�G�@�ϋv�x����
				(*it2)->damageHp(EnemyHp);			//�p�[�c�ϋv�x����
				MUSIC->Play(musicFriendHit);		//��e��
			}
		}
	}
	/*�G�@���Ŕ���*/
		for(EnemyVsptr::iterator it = enemyList.begin(); it != enemyList.end(); ){
			if(isIn(0 - wideArea, SCREEN_WIDTH + wideArea, 
					0 - wideArea, SCREEN_HEIGHT + wideArea, 
					(int)( (*it)->getPos().x + (*it)->getSize()/2 ), 
					(int)( (*it)->getPos().y + (*it)->getSize()/2 ) ) == false){	//��ʊO����
				it = enemyList.erase(it);
				continue;
			}
			if((*it)->getHp() <= 0){					//�ϋv�x����
				//�{�X�폜����
				if((*it)->getBoss() == 1){
					bossFlag++;
				}

				score += (*it)->getMaxHp() * 10;		//�X�R�A���Z
				
				//����
				effectFactory(EffectSptr(new Explosion()), 
					(*it)->getPos(), Vec2( (*it)->getPos().x, (*it)->getPos().y - 100.0 )
					);
				
				switch(makeRand(3)){
				case 0://�~�`����
					for(double cnt = 0; cnt < PI*2; cnt += PI*2 / 8){
						effectFactory(EffectSptr(new Explosion()), 
							(*it)->getPos(), 
							Vec2( (*it)->getPos().x + sin(cnt) * 100.0, 
								(*it)->getPos().y + cos(cnt) * 100.0 )
							);
						MUSIC->Play(musicEnemyDown);			//���j��
					}
					break;
				case 1://�\��
					for(double cnt = 0; cnt < PI*2; cnt += PI*2 / 5){
						for(int cnt2 = 0; cnt2 < 5; cnt2++){
							effectFactory(EffectSptr(new Explosion()), 
								(*it)->getPos(), 
								Vec2( (*it)->getPos().x + sin(cnt) * 100.0, 
									(*it)->getPos().y + cos(cnt) * 100.0 )
								);
							EffectVsptr::iterator it = effectList.end() - 1;		//���O�̃I�u�W�F�N�g���Q��
							(*it)->setDis(cnt2);						//����
							(*it)->setDir(cnt);						//����
							(*it)->setMoveMode(1);						//�ړ����[�h
							MUSIC->Play(musicEnemyDown);			//���j��
						}
					}
					break;
				case 2://�����_��
						for(int cnt2 = 0; cnt2 < 5; cnt2++){
							effectFactory(EffectSptr(new Explosion()),
								(*it)->getPos(), 
								Vec2( (*it)->getPos().x + makeRand(0.0, 50), 
									(*it)->getPos().y + makeRand(0.0, 50) )
								);
							MUSIC->Play(musicEnemyDown);			//���j��
						}
					break;
				}
				//�j��
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


	/*�G�e�����蔻��*/
	for(EnemyBulletVsptr::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); it++){
		double bulletX = (*it)->getPos().x + (*it)->getOutputW()*tipSize / 2;		//�G�eX���W
		double bulletY = (*it)->getPos().y + (*it)->getOutputH()*tipSize / 2;		//�G�eY���W
		int bulletSize = (*it)->getSize() / 2;		//�G�e�T�C�Y
		int bulletHp = (*it)->getHp();			//�G�e�ϋv�x
		int bulletFire = (*it)->getFire();		//�e�̉Η�
		/*�΃p�[�cA*/
		for(PartsAVsptr::iterator it2 = partsAList.begin(); it2 != partsAList.end(); it2++){
			double partsX = (*it2)->getPos().x + (*it2)->getOutputW()*tipSize / 2;	//�p�[�cX���W
			double partsY = (*it2)->getPos().y + (*it2)->getOutputH()*tipSize / 2;	//�p�[�cY���W
			int partsSize = (*it2)->getSize() / 2;	//�p�[�c�T�C�Y
			int partsHp = (*it2)->getHp();		//�p�[�c�ϋv�x
			if(	(bulletX - partsX) * (bulletX - partsX) + 
			(bulletY - partsY) * (bulletY - partsY) <
			(bulletSize + partsSize) * (bulletSize + partsSize) ){
				(*it)->damageHp(partsHp);			//�G�e�ϋv�x����
				(*it2)->damageHp(bulletHp);			//�p�[�c�ϋv�x����
				(*it2)->killMan(bulletHp);			//�E��
				(*it2)->addFire( bulletFire );		//�Ἠ_���[�W
				//����
				effectFactory(EffectSptr(new Explosion()), 
					(*it)->getPos(), 
					Vec2( (*it)->getPos().x + makeRand(0.0, 50), 
						(*it)->getPos().y + makeRand(200.0, 60) )
					);
				//MUSIC->Play(musicDead3);		//��e��
				MUSIC->Play(musicSakebi);		//��e��
			}
		}
		bulletHp = (*it)->getHp();			//�G�e�ϋv�x
		/*�΃p�[�cB*/
		for(PartsBVsptr::iterator it2 = partsBList.begin(); it2 != partsBList.end(); it2++){
			double partsX = (*it2)->getPos().x + (*it2)->getOutputW()*tipSize / 2;	//�p�[�cX���W
			double partsY = (*it2)->getPos().y + (*it2)->getOutputW()*tipSize / 2;	//�p�[�cY���W
			int partsSize = (*it2)->getSize() / 2;	//�p�[�c�T�C�Y
			int partsHp = (*it2)->getHp();		//�p�[�c�ϋv�x
			if(	(bulletX - partsX) * (bulletX - partsX) + 
			(bulletY - partsY) * (bulletY - partsY) <
			(bulletSize + partsSize) * (bulletSize + partsSize) ){
				(*it)->damageHp(partsHp);			//�G�e�ϋv�x����
				(*it2)->damageHp(bulletHp);			//�p�[�c�ϋv�x����
				(*it2)->killMan(bulletHp);			//�E��
				(*it2)->addFire( bulletFire );		//�Ἠ_���[�W
				//����
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

				MUSIC->Play(musicDead1);		//��e��
			}
		}
	}
	/*�G�e���Ŕ���*/
	for(EnemyBulletVsptr::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ){
		if(isIn(SCREEN_INDENT, SCREEN_WIDTH - SCREEN_INDENT, 0, SCREEN_HEIGHT, 
				(int)( (*it)->getPos().x + (*it)->getSize()/2 ), 
				(int)( (*it)->getPos().y + (*it)->getSize()/2 ) ) == false){	//��ʊO����
			it = enemyBulletList.erase(it);
			continue;
		}
		if((*it)->getHp() <= 0){	//�ϋv�x����
			it = enemyBulletList.erase(it);
			continue;
		}
		it++;
	}

	/*�p�[�cA���Ŕ���*/
	for(PartsAVsptr::iterator it = partsAList.begin(); it != partsAList.end(); ){
		if((*it)->getHp() <= 0){	//�ϋv�x����
			it = partsAList.erase(it);
			MUSIC->Play(musicBakuhatsu);		//�j��
			continue;
		}
		it++;
	}
	/*�p�[�cB���Ŕ���*/
	for(PartsBVsptr::iterator it = partsBList.begin(); it != partsBList.end(); ){
		if((*it)->getHp() <= 0){	//�ϋv�x����
			it = partsBList.erase(it);
			continue;
		}
		if((*it)->getFrameCnt() >= 100 && (*it)->getPos().y >= SCREEN_HEIGHT + 200){	//��ʊO����
			it = partsBList.erase(it);
			continue;
		}
		it++;
	}


}

/*::::::::�\������::::::::*/
void Tomasen::printGame(){
	/*��ʂ̓h��Ԃ�*/
	IMAGE->drawTip(	0.0, 0.0, 
					(double)SCREEN_WIDTH, (double)SCREEN_HEIGHT, 
					IMAGE->getBlack());
	/*�G�t�F�N�g�`�揈��*/
	for(EffectVsptr::iterator it = effectList.begin(); it != effectList.end(); it++){
		(*it)->draw(*this);
	}
	/*�p�[�cB�`�揈��*/
	for(PartsBVsptr::iterator it = partsBList.begin(); it != partsBList.end(); it++){
		(*it)->draw(*this);
	}
	/*�p�[�cA�`�揈�� �D�揇��=0*/
	for(PartsAVsptr::iterator it = partsAList.begin(); it != partsAList.end(); it++){
		if( (*it)->getDrawPriority() == 0){
			(*it)->draw(*this);
		}
	}
	/*�p�[�cA�`�揈�� �D�揇��=1*/
	for(PartsAVsptr::iterator it = partsAList.begin(); it != partsAList.end(); it++){
		if( (*it)->getDrawPriority() == 1){
			(*it)->draw(*this);
		}
	}
	
	/*���e�`�揈��*/
	for(FriendBulletVsptr::iterator it = friendBulletList.begin(); it != friendBulletList.end(); it++){
		(*it)->draw(*this);
	}
	
	/*�G�@�`�揈��*/
	for(EnemyVsptr::iterator it = enemyList.begin(); it != enemyList.end(); it++){
		(*it)->draw(*this);
	}
	
	/*�G�e�`�揈��*/
	for(EnemyBulletVsptr::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); it++){
		(*it)->draw(*this);
	}
	


	/*�����h��Ԃ�*/
	IMAGE->drawTip(	0.0, 0.0, 
					(double)SCREEN_INDENT, (double)SCREEN_HEIGHT, 
					IMAGE->tipNo(4,16));
	IMAGE->drawTip(	(double)(SCREEN_WIDTH - SCREEN_INDENT), 0.0, 
					(double)SCREEN_INDENT, (double)SCREEN_HEIGHT, 
					IMAGE->tipNo(4,16));

	/*�f�o�b�O������\��*/
	if(FriendSptr tmp = kosenWing.lock()){
		char str[256];
		sprintf_s(str, "A:%03d, B:%03d, cnt:%d", partsAList.size(), partsBList.size(), tmp->getFrameCnt());
		IMAGE->printText(0, 0, str);
		sprintf_s(str, "X:%+03.3f  MoveX:%+03.3f", tmp->getPos().x, tmp->getMove().x);
		IMAGE->printText(0, 1, str);
		sprintf_s(str, "Y:%+03.3f  MoveY:%+03.3f", tmp->getPos().y, tmp->getMove().y);
		IMAGE->printText(0, 2, str);
		sprintf_s(str, "���e:%03d, �G�e:%03d", friendBulletList.size(), enemyBulletList.size());
		IMAGE->printText(0, 3, str);
		sprintf_s(str, "�G�@:%03d, Event��:%03d", enemyList.size(), eventList.size());
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
	
	/*���b�Z�[�W���g*/
	IMAGE->drawFillTip(1, 15, 11, 20, IMAGE->tipNo(21,17));
	/*�R�}���h��*/
	IMAGE->drawFillTip(1, 36, 11, 1, IMAGE->tipNo(21,17));

	/*���b�Z�[�W*/
	int cnt = 0;	//20���܂ŕ\��
	for(StringV::iterator it = stringV.begin(); it != stringV.end(); it++){
		IMAGE->printText(1, 15 + (20 - stringV.size()) + cnt, (*it).c_str());
		cnt++;
		if(cnt >= 20) break;
	}

	/*�o�[�̕\��*/
	for(BarVsptr::iterator it = barList.begin(); it != barList.end(); it++){
		(*it)->draw(*this);
	}
	
	/*���x���̕\��*/
	for(LabelVsptr::iterator it = labelList.begin(); it != labelList.end(); it++){
		(*it)->draw(*this);
	}

	/*���[�_�[�̕\��*/
	drawRader();

	/*�f�B�X�v���C�ɕ\��*/
	IMAGE->drawEnd();
}

/*::::::::���[�_�[�\������::::::::*/
void Tomasen::drawRader(){

	/*
	���� tipSize*38, tipSize*13
	�E�� tipSize*49, tipSize*13
	���� tipSize*38, tipSize*21
	�E�� tipSize*49, tipSize*21
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


	/*�������ʒu*/
	int drawCnt = 0;
	if(FriendSptr tmp = kosenWing.lock()){
		drawCnt = tmp->getFrameCnt()*2 % (int)(h*1.4);
	}

	/*���n*/
	IMAGE->drawFillTip(Vec2(lu_x, lu_y), w/tipSize, h/tipSize, IMAGE->tipNo(21,17));

	/*������*/
	if(drawCnt < h){
		IMAGE->drawTip(
			(double)ld_x, 
			(double)ld_y - drawCnt, 
			(double)w, 
			1.0, 
			IMAGE->getRed() );
		
		/*������*/
		IMAGE->drawAlphaBlendTip(
			(double)ld_x, 
			(double)ld_y - drawCnt + 1, 
			(double)w, 
			5.0, 
			IMAGE->getRed(),
			64);
		/*������*/
		IMAGE->drawAlphaBlendTip(
			(double)ld_x, 
			(double)ld_y - drawCnt + 6, 
			(double)w, 
			10.0, 
			IMAGE->getRed(),
			32);

	}

	/*�G�@�̕`��*/
	for(EnemyVsptr::iterator it = enemyList.begin(); it != enemyList.end(); it++){
		if(ld_y - drawCnt < lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT &&//��������艺����
			ld_y - drawCnt + haba > lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT){//haba�s�N�Z���ȓ�
			IMAGE->drawTip(
				(double)lu_x + (*it)->getCenterPos().x * w / SCREEN_WIDTH , 
				(double)lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT, 
				1.0, 
				1.0, 
				IMAGE->getRed() );
		}
	}
	/*�y��p�[�c�`��*/
	for(PartsBVsptr::iterator it = partsBList.begin(); it != partsBList.end(); it++){
		if(ld_y - drawCnt < lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT &&//��������艺����
			ld_y - drawCnt + haba > lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT){//haba�s�N�Z���ȓ�
			IMAGE->drawTip(
				(double)lu_x + (*it)->getCenterPos().x * w / SCREEN_WIDTH , 
				(double)lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT, 
				1.0, 
				1.0, 
				IMAGE->getBlue() );
		}
	}

	/*���e�`��*/
	for(FriendBulletVsptr::iterator it = friendBulletList.begin(); it != friendBulletList.end(); it++){
		if(ld_y - drawCnt < lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT &&//��������艺����
			ld_y - drawCnt + haba > lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT){//haba�s�N�Z���ȓ�
			IMAGE->drawTip(
				(double)lu_x + (*it)->getCenterPos().x * w / SCREEN_WIDTH , 
				(double)lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT, 
				1.0, 
				1.0, 
				IMAGE->getGreen() );
		}
	}

	/*�G�e�`��*/
	for(EnemyBulletVsptr::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); it++){
		if(ld_y - drawCnt < lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT &&//��������艺����
			ld_y - drawCnt + haba > lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT){//haba�s�N�Z���ȓ�
			IMAGE->drawTip(
				(double)lu_x + (*it)->getCenterPos().x * w / SCREEN_WIDTH , 
				(double)lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT, 
				1.0, 
				1.0, 
				IMAGE->getWhite() );
		}
	}
	/*�G�t�F�N�g�`�揈��*/
	for(EffectVsptr::iterator it = effectList.begin(); it != effectList.end(); it++){
		if(ld_y - drawCnt < lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT &&//��������艺����
			ld_y - drawCnt + haba > lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT){//haba�s�N�Z���ȓ�
			IMAGE->drawTip(
				(double)lu_x + (*it)->getCenterPos().x * w / SCREEN_WIDTH , 
				(double)lu_y + (*it)->getCenterPos().y * h / SCREEN_HEIGHT, 
				1.0, 
				1.0, 
				IMAGE->getBlack() );
		}
	}

}

/*::::::::�f�X�g���N�^::::::::*/
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