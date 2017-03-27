#ifndef INCLUDED_MUSIC_HPP
#define INCLUDED_MUSIC_HPP

#include <sstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include "common.hpp"

namespace tm2{

class Music
{
public:
	/*�R���X�g���N�^*/
	inline Music();
	/*�f�X�g���N�^*/
	inline ~Music();
	/*�y�ȃt�@�C���̃I�[�v��*/
	inline int Open(std::string filename);
	/*�y�ȃt�@�C���̍Đ�*/
	inline void Play(int ID);		//1�`�ǂݍ��ݏ��Ԃ�
	/*�y�ȃt�@�C���̑S��~*/
	inline void Stop();
	/*�y�ȃt�@�C���̍Đ�*/
	inline void Play(int ID, int from, int to);		//���[�v�Đ�
	/*���[�v�`�F�b�N*/
	inline void Check();
	/*�{�����[������*/
	inline void setTargetVol(int ID, int volume);
	/*�{�����[������*/
	inline void setVolume(int ID, int volume);
	/*���ݒn�`�F�b�N*/
	inline int getPos(int ID);

private:
	int OpenFile;//�J���Ă���t�@�C����
	std::vector<std::string> fileNameV;
	std::vector<int> loopFlag;
	std::vector<int> loopFrom;
	std::vector<int> loopTo;
	std::vector<int> volume;
	std::vector<int> targetVol;
};

Music::Music(){
	OpenFile = 0;
}
Music::~Music(){
	/*�J�����t�@�C���̃N���[�Y*/
	for(int cnt = 0; cnt < OpenFile; cnt++){
		std::ostringstream IDstr;
		IDstr << (cnt+1);
		mciSendString(("close " + IDstr.str()).c_str(), NULL, 0, NULL);
	}
}
int Music::Open(std::string filename){
	std::ostringstream IDstr;

	//�ǂݍ��ݍς݂ł��邩�m�F�A�ǂݍ��ݍς݂̏ꍇ��ID��Ԃ�
	std::vector<std::string>::iterator it;
	int ID = 1;
	for(it = fileNameV.begin(); it != fileNameV.end(); it++){
		if(filename.compare(*it) == 0){
			return ID;
		}
		ID++;
	}
	//�V�����t�@�C�����̏ꍇ�͕ێ�
	fileNameV.push_back(filename);

	OpenFile++;
	IDstr << OpenFile;
	if(mciSendString( ("open " + filename + " type mpegvideo alias " + IDstr.str()).c_str(), NULL, 0, NULL) != 0 ) { //type waveaudio
		MessageBox(NULL, TEXT("���y�t�@�C���̃I�[�v���Ɏ��s"), TEXT("�G���["), MB_OK | MB_ICONWARNING);
	}

	//���[�v�ݒ�
	loopFlag.push_back(0);
	loopFrom.push_back(0);
	loopTo.push_back(0);
	volume.push_back(10);
	targetVol.push_back(500);

	return OpenFile;
}
void Music::Play(int ID){
	std::ostringstream IDstr;
	IDstr << ID;

	//�Đ��J�n
	mciSendString(("play " + IDstr.str() + " from 0").c_str(), NULL, 0, NULL);
}
void Music::Play(int ID, int from, int to){
	std::ostringstream IDstr;
	std::ostringstream fromstr;
	std::ostringstream tostr;
	IDstr << ID;
	fromstr << from;
	tostr << to;

	//�Đ��J�n
	mciSendString(("play " + IDstr.str() + " from 0").c_str(), NULL, 0, NULL);

	//���[�v�ݒ�
	loopFlag.at(ID) = 1;
	loopFrom.at(ID) = from;
	loopTo.at(ID) = to;
}
void Music::Stop(){
	/*�J�����t�@�C���̃N���[�Y*/
	for(int cnt = 0; cnt < OpenFile; cnt++){
		std::ostringstream IDstr;
		IDstr << (cnt+1);
		mciSendString(("stop " + IDstr.str()).c_str(), NULL, 0, NULL);
	}
}
/*���[�v�`�F�b�N*/
void Music::Check(){

	//�S�Ȋm�F
	for(unsigned int cnt = 0; cnt < loopFlag.size(); cnt++){
	
		std::ostringstream IDstr;
		std::ostringstream tostr;
		IDstr << cnt;
		tostr << loopTo.at(cnt);
		
		if(loopFlag.at(cnt) == 1){
			//��Ԋm�F
			char returnStr[256];
			mciSendString(("status " + IDstr.str() + " position").c_str(), returnStr, 256, NULL);

			//���[�v����
			if( atoi(returnStr) > loopFrom.at(cnt) ){
				mciSendString(("play " + IDstr.str() + " from " + tostr.str()).c_str(), NULL, 0, NULL);
			}
		}
		
		std::ostringstream volstr;
		//���ʕ␳
		if(targetVol.at(cnt) > volume.at(cnt)){
			volume.at(cnt)++;
			//���ʕύX
			volstr << volume.at(cnt);
			mciSendString(("setaudio " + IDstr.str() + " volume to " + volstr.str()).c_str(), NULL, 0, NULL);
		}
		else if(targetVol.at(cnt) < volume.at(cnt)){
			volume.at(cnt)--;
			//���ʕύX
			volstr << volume.at(cnt);
			mciSendString(("setaudio " + IDstr.str() + " volume to " + volstr.str()).c_str(), NULL, 0, NULL);
		}
	}

}
/*�{�����[������*/
void Music::setTargetVol(int ID, int vol){
	std::ostringstream IDstr;
	IDstr << ID;
	targetVol.at(ID) = vol;
}
/*�{�����[������*/
void Music::setVolume(int ID, int vol){
	std::ostringstream IDstr;
	IDstr << ID;
	volume.at(ID) = vol;
}
/*���ݒn�`�F�b�N*/
int Music::getPos(int ID){
	std::ostringstream IDstr;
	IDstr << ID;

	char returnStr[256];
	
	//��Ԋm�F
	mciSendString(("status " + IDstr.str() + " position").c_str(), returnStr, 256, NULL);

	return atoi(returnStr);
}

} //namespace tm2
#endif//INCLUDED_IMAGE_HPP