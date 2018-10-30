#include <iostream>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc_c.h"
#include "fstream"
#include <direct.h>
#include <io.h>
#include <Windows.h>

using namespace std;
using namespace cv;

extern int readDir(char *dirName, vector<string> &filesName);

struct rect1
{
	int x1;
	int y1;
	int x2;
	int y2;
	int label;
};

int test40_ex(int argc, char *argv[])
{

	string imgpath = "G:/F/Traffic-signs/data/TrainIJCNN2013/image-ex";
	string txtpath = "G:/F/Traffic-signs/data/TrainIJCNN2013/0ex.txt";
	string  drawpath = "G:/F/Traffic-signs/data/TrainIJCNN2013-draw";
	mkdir(drawpath.c_str());
	string  drawpathex = "G:/F/Traffic-signs/data/TrainIJCNN2013-draw/ex";
	mkdir(drawpathex.c_str());

	map<string, vector<rect1>> ms;
	fstream finRead;
	finRead.open(txtpath, ios::in);
	if (!finRead.is_open())
	{
		cout << "finRead 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	string line; int num = 0;
	while (getline(finRead, line))
	{
		num++;
		if (line.empty())
		{
			break;
		}

		cout << "1. "<<line.c_str() << endl;

		string name1; int x1, y1, x2, y2;
		stringstream str_s(line);
		str_s >> name1 >> x1 >> y1 >> x2 >> y2;
		rect1 rt; rt.x1 = x1; rt.y1 = y1; rt.x2 = x2; rt.y2 = y2;

		int npos2 = name1.find_last_of('.');
		string ne2 = name1.substr(0,npos2);

		ms[ne2].push_back(rt);

		}

	finRead.close();

	map<string, vector<rect1>>::iterator it;
	for (it = ms.begin(); it != ms.end(); it++)
	{
		string name = it->first;
		vector<rect1> rts = it->second;

		fstream finWrite;
		string str = imgpath + "/" + name+".txt";
		finWrite.open(str, ios::out);
		if (!finWrite.is_open())
		{
			cout << "finRead 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}

		
		for (int i = 0; i < rts.size();i++)
		{
			rect1 rt = rts[i];
			finWrite << rt.x1 << " " << rt.y1 << " " << rt.x2 << " " << rt.y2 << endl;
		}

		finWrite.close();
	}

	vector<string> v_img_;
	readDir((char*)imgpath.c_str(), v_img_);
	for (int i = 0; i<v_img_.size(); i++)
	{
		int npos = v_img_[i].find_last_of('/');
		int npos2 = v_img_[i].find_last_of('.');
		cout << v_img_[i]<<endl;
		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());
		if (img.data == NULL)
		{
			printf("img.data = NULL！\n");
			system("pause");
			continue;
		}

		vector<rect1> rts;
		map<string, vector<rect1>>::iterator key = ms.find(name1);
		if (key != ms.end())
		{
			rts = key->second;
		}
		else
		{
			printf("%s 没有找到!\n",name1.c_str());
			//system("pause");
			continue;
		}

		for (int j = 0; j < rts.size();j++)
		{
			rect1 rt = rts[j];
			Point pt1, pt2;
			pt1.x = rt.x1; pt1.y = rt.y1; pt2.x = rt.x2; pt2.y = rt.y2;
			rectangle(img, pt1, pt2, Scalar(0, 0, 255));

		}

		string path12 = drawpathex + "/" + name1+".jpg";
		imwrite(path12.c_str(), img);
	}
	
	return 0;
}
int test40_gt(int argc, char *argv[])
{

	string imgpath = "G:/F/Traffic-signs/data/FullIJCNN2013/image-gt";
	string txtpath = "G:/F/Traffic-signs/data/FullIJCNN2013/0gt.txt";
	string  drawpath = "G:/F/Traffic-signs/data/FullIJCNN2013-draw";
	mkdir(drawpath.c_str());
	string  drawpathex = "G:/F/Traffic-signs/data/FullIJCNN2013-draw/gt";
	mkdir(drawpathex.c_str());

	map<string, vector<rect1>> ms;
	fstream finRead;
	finRead.open(txtpath, ios::in);
	if (!finRead.is_open())
	{
		cout << "finRead 文件数据打开错误！" << endl;
		system("pause");
		return false;
	}

	string line; int num = 0;
	while (getline(finRead, line))
	{
		num++;
		if (line.empty())
		{
			break;
		}

		cout <<"1. "<< line.c_str() << endl;

		string name1; int x1, y1, x2, y2; int label;
		stringstream str_s(line);
		str_s >> name1 >> x1 >> y1 >> x2 >> y2>>label;
		rect1 rt; rt.x1 = x1; rt.y1 = y1; rt.x2 = x2; rt.y2 = y2; rt.label = label;
		
		int npos2 = name1.find_last_of('.');
		string ne2 = name1.substr(0, npos2);

		ms[ne2].push_back(rt);

	}

	finRead.close();

	map<string, vector<rect1>>::iterator it;
	for (it = ms.begin(); it != ms.end(); it++)
	{
		string name = it->first;
		vector<rect1> rts = it->second;

		fstream finWrite;
		string str = imgpath + "/" + name + ".txt";
		finWrite.open(str, ios::out);
		if (!finWrite.is_open())
		{
			cout << "finRead 文件数据打开错误！" << endl;
			system("pause");
			return false;
		}


		for (int i = 0; i < rts.size(); i++)
		{
			rect1 rt = rts[i];
			finWrite <<rt.label <<" "<< rt.x1 << " " << rt.y1 << " " << rt.x2 << " " << rt.y2 << endl;
		}

		finWrite.close();
	}

	vector<string> v_img_;
	readDir((char*)imgpath.c_str(), v_img_);
	for (int i = 0; i<v_img_.size(); i++)
	{
		int npos = v_img_[i].find_last_of('/');
		int npos2 = v_img_[i].find_last_of('.');
		cout << v_img_[i] << endl;
		string name1 = v_img_[i].substr(npos + 1, npos2 - npos - 1);
		Mat img = imread(v_img_[i].c_str());
		if (img.data == NULL)
		{
			printf("img.data = NULL！\n");
			system("pause");
			continue;
		}

		vector<rect1> rts;
		map<string, vector<rect1>>::iterator key = ms.find(name1);
		if (key != ms.end())
		{
			rts = key->second;
		}
		else
		{
			printf("%s 没有找到!\n", name1.c_str());
			//system("pause");
			continue;
		}

		for (int j = 0; j < rts.size(); j++)
		{
			rect1 rt = rts[j];
			Point pt1, pt2;
			pt1.x = rt.x1; pt1.y = rt.y1; pt2.x = rt.x2; pt2.y = rt.y2;
			rectangle(img, pt1, pt2, Scalar(0, 0, 255));

			char s[12];            
			itoa(rt.label, s, 10);           
			
			//设置绘制文本的相关参数
			string text = s;
			int font_face = cv::FONT_HERSHEY_COMPLEX;
			double font_scale = 0.5;
			int thickness = 1;
			int baseline;

			Size text_size = getTextSize(text, font_face, font_scale, thickness, &baseline);
			//将文本框居中绘制
			Point origin;
			origin.x = rt.x1 + 5;
			origin.y = rt.y1 + 5;
			putText(img, text, origin, font_face, font_scale, Scalar(0, 255, 255), thickness, 8, 0);
		}

		string path12 = drawpathex + "/" + name1 + ".jpg";
		imwrite(path12.c_str(), img);
	}

	return 0;
}

int test40(int argc, char *argv[])
{
	//test40_ex(argc, argv);
	test40_gt(argc, argv);
	return 0;
}