#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <cstring>
#include <string>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/vfs.h>
#include <sys/mount.h>
#include <libgen.h>
#include <stdlib.h>
#include <dirent.h> 
#include <errno.h> 
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//현재시간 구하는 함수
char nowtime[256];
char filename[100];
int nowTime()
{
    time_t timer;  timer = time(NULL);
    struct tm t;

    t = *localtime(&timer); 
    strftime(nowtime, sizeof(nowtime), "%Y-%m-%d-%H", &t);
    strftime(filename, sizeof(filename), "%Y%m%d%H%M%S", &t);
    return 0;
}

//폴더만들기 mkdir
void mkdirs(char* pt)
{
    nowTime();
    char *buffer;
    int md;
    string ptin;

    ptin.assign(pt);
    ptin.append("/");
    ptin.append(nowtime);
    buffer=(char*)ptin.c_str();

    md = mkdir(buffer, 0777);
    if(md == -1)
        std::cout<<buffer<<"폴더생성 실패"<<"\n";
    else
        std::cout<<buffer<<"폴더생성 성공"<<"\n";
}

//디스크용량 확인
struct f_size
{
    long blocks;
    long avail;
};
long ckmemory(char *pt)
{
    FILE *fp;  //파일 스트림 포인터 
    struct statfs lstatfs;
    struct f_size size;

    if(!(fp=fopen(pt, "r")))
        std::cout<<"파일열지못함\n";

    //파일시스템의 총 할당된 크기와 사용량을 구한다.
    statfs(pt, &lstatfs);
    size.blocks = lstatfs.f_blocks * (lstatfs.f_bsize/1024);
    size.avail  = lstatfs.f_bavail * (lstatfs.f_bsize/1024);

    std::cout<<"전체용량\n"<<size.blocks;
    std::cout<<"사용가능용량\n"<<size.avail;

    fclose(fp);
}


//오래된 폴더부터 삭제
int rmdirs(char* pt)
{
    if(ckmemory(pt)<50)   // 메모리가 50 이하면 삭제시작
    {
        struct dirent **namelist;
        char tmp[256], fd_name[256], temp[256];
        int count;
        int idx;
        DIR *dir;
        struct dirent *dirs;

        if((count = scandir(tmp, &namelist, NULL, alphasort)) == -1) // 폴더 읽기 시작
            std::cout<<"파일 못 읽음\n";

        if((dir=opendir(namelist[2]->d_name))==NULL)  //폴더 열기
            std::cout<<namelist[2]->d_name<<"삭제할 디렉토리 열기 실패\n";
        else
            std::cout<<namelist[2]->d_name<<"삭제할 디렉토리 열음\n";

        while((dirs=readdir(dir))!=NULL)  //파일이 남으면 삭제가 안되기 때문에 파일먼저 삭제
        {
            strcpy(temp, fd_name);
            strcat(temp,"/");
            strcat(temp,dirs->d_name);
            int a=remove(temp);
            if(a==-1)
                std::cout<<temp<<"삭제실패"<<strerror(errno)<<"\n";
            else
                std::cout<<temp<<"삭제완료\n";
            sleep(3);
        }
        if(rmdir(namelist[3]->d_name) == -1) //파일 없는 폴더 지우기
            std::cout<<"폴더 삭제실패"<<strerror(errno)<<"\n";
        else
            std::cout<<"폴더 삭제완료\n";
        
        closedir(dir);

        for(int idx = 0; idx < count; idx++)
        {
            free(namelist[idx]);
        }

        free(namelist);
        return 0;
    }
    else
        return 0;
}

//동영상 저장
int videoRec(char *pt)
{
    Mat img_color;
    
    
    
    
    
    
    //비디오 캡쳐 초기화
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		std::cerr << "에러 - 카메라를 열 수 없습니다.\n";
		return -1;
	}

	// 동영상 파일을 저장하기 위한 준비  
	Size size = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),(int)cap.get(CAP_PROP_FRAME_HEIGHT));

	VideoWriter writer;
	double fps = 30.0;
	writer.open("output.avi", VideoWriter::fourcc('D', 'V', 'I', 'X'), fps, size, true);
	if (!writer.isOpened())
	{
		std::cout << "동영상을 저장하기 위한 초기화 작업 중 에러 발생\n";
	}

	while(1)
	{
		cap.read(img_color);
		if (img_color.empty()) {
			std::cerr << "빈 영상이 캡쳐되었습니다.\n";
			break;
		}

		//동영상 파일에 한 프레임을 저장함.  
		writer.write(img_color);
		imshow("Color", img_color);

		if (waitKey(25) >= 0)
			break;

	}

return 0;
}