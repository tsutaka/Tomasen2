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
	/*コンストラクタ*/
	inline Music();
	/*デストラクタ*/
	inline ~Music();
	/*楽曲ファイルのオープン*/
	inline int Open(std::string filename);
	/*楽曲ファイルの再生*/
	inline void Play(int ID);		//1～読み込み順番に
	/*楽曲ファイルの全停止*/
	inline void Stop();
	/*楽曲ファイルの再生*/
	inline void Play(int ID, int from, int to);		//ループ再生
	/*ループチェック*/
	inline void Check();
	/*ボリューム調整*/
	inline void setTargetVol(int ID, int volume);
	/*ボリューム調整*/
	inline void setVolume(int ID, int volume);
	/*現在地チェック*/
	inline int getPos(int ID);

private:
	int OpenFile;//開いているファイル数
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
	/*開いたファイルのクローズ*/
	for(int cnt = 0; cnt < OpenFile; cnt++){
		std::ostringstream IDstr;
		IDstr << (cnt+1);
		mciSendString(("close " + IDstr.str()).c_str(), NULL, 0, NULL);
	}
}
int Music::Open(std::string filename){
	std::ostringstream IDstr;

	//読み込み済みであるか確認、読み込み済みの場合はIDを返す
	std::vector<std::string>::iterator it;
	int ID = 1;
	for(it = fileNameV.begin(); it != fileNameV.end(); it++){
		if(filename.compare(*it) == 0){
			return ID;
		}
		ID++;
	}
	//新しいファイル名の場合は保持
	fileNameV.push_back(filename);

	OpenFile++;
	IDstr << OpenFile;
	if(mciSendString( ("open " + filename + " type mpegvideo alias " + IDstr.str()).c_str(), NULL, 0, NULL) != 0 ) { //type waveaudio
		MessageBox(NULL, TEXT("音楽ファイルのオープンに失敗"), TEXT("エラー"), MB_OK | MB_ICONWARNING);
	}

	//ループ設定
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

	//再生開始
	mciSendString(("play " + IDstr.str() + " from 0").c_str(), NULL, 0, NULL);
}
void Music::Play(int ID, int from, int to){
	std::ostringstream IDstr;
	std::ostringstream fromstr;
	std::ostringstream tostr;
	IDstr << ID;
	fromstr << from;
	tostr << to;

	//再生開始
	mciSendString(("play " + IDstr.str() + " from 0").c_str(), NULL, 0, NULL);

	//ループ設定
	loopFlag.at(ID) = 1;
	loopFrom.at(ID) = from;
	loopTo.at(ID) = to;
}
void Music::Stop(){
	/*開いたファイルのクローズ*/
	for(int cnt = 0; cnt < OpenFile; cnt++){
		std::ostringstream IDstr;
		IDstr << (cnt+1);
		mciSendString(("stop " + IDstr.str()).c_str(), NULL, 0, NULL);
	}
}
/*ループチェック*/
void Music::Check(){

	//全曲確認
	for(unsigned int cnt = 0; cnt < loopFlag.size(); cnt++){
	
		std::ostringstream IDstr;
		std::ostringstream tostr;
		IDstr << cnt;
		tostr << loopTo.at(cnt);
		
		if(loopFlag.at(cnt) == 1){
			//状態確認
			char returnStr[256];
			mciSendString(("status " + IDstr.str() + " position").c_str(), returnStr, 256, NULL);

			//ループ処理
			if( atoi(returnStr) > loopFrom.at(cnt) ){
				mciSendString(("play " + IDstr.str() + " from " + tostr.str()).c_str(), NULL, 0, NULL);
			}
		}
		
		std::ostringstream volstr;
		//音量補正
		if(targetVol.at(cnt) > volume.at(cnt)){
			volume.at(cnt)++;
			//音量変更
			volstr << volume.at(cnt);
			mciSendString(("setaudio " + IDstr.str() + " volume to " + volstr.str()).c_str(), NULL, 0, NULL);
		}
		else if(targetVol.at(cnt) < volume.at(cnt)){
			volume.at(cnt)--;
			//音量変更
			volstr << volume.at(cnt);
			mciSendString(("setaudio " + IDstr.str() + " volume to " + volstr.str()).c_str(), NULL, 0, NULL);
		}
	}

}
/*ボリューム調整*/
void Music::setTargetVol(int ID, int vol){
	std::ostringstream IDstr;
	IDstr << ID;
	targetVol.at(ID) = vol;
}
/*ボリューム調整*/
void Music::setVolume(int ID, int vol){
	std::ostringstream IDstr;
	IDstr << ID;
	volume.at(ID) = vol;
}
/*現在地チェック*/
int Music::getPos(int ID){
	std::ostringstream IDstr;
	IDstr << ID;

	char returnStr[256];
	
	//状態確認
	mciSendString(("status " + IDstr.str() + " position").c_str(), returnStr, 256, NULL);

	return atoi(returnStr);
}

} //namespace tm2
#endif//INCLUDED_IMAGE_HPP