#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;


void proje()
{  
	// EMRE MALTAÞ 
	string wName = "Goster";

	RNG& random = theRNG();

	Mat ilkEkran(500, 900, CV_8UC3, Scalar(255, 255, 255));
	int renk1, renk2, renk3;
	int ilkDondu = 10;
	int i, font, p = 0, a = 0;
	Point2f konum;
	Mat donusum;//affine donusumu yaptýgým matris.
	Mat uni = imread("C:\\Users\\User\\Desktop\\biomedical image\\uni.jpg");
	resize(uni, uni, Size(900, 500));
	string ekranaYaz[] = { "DUZCE","UNIVERSITESI","BIYOMEDIKAL","MUHENDISLIGI","BOLUMU", "BIYOMEDIKAL","MUHENDISI","EMRE"," MALTAS" };
	konum = Point2f(130, 400);//baslangýctaki duz yazýnýn konumu
	Point kayanYazý = Point(0, 0);
	Mat kopya;

	for (i = 0; i <= 10; i++)
	{
		font = random.uniform(1, 3);
		renk1 = random.uniform(0, 256);
		renk2 = random.uniform(0, 156);
		renk3 = random.uniform(0, 90);

		ilkEkran = Scalar(renk1, renk2, renk3);
		putText(ilkEkran, ekranaYaz[i], konum, FONT_HERSHEY_TRIPLEX, 3, Scalar::all(255), 1);
		p++;
		waitKey(20);

		if (p == 10)
		{
			for (int t= 0; t <10; t++)
			{
				renk1 = random.uniform(0, 256);
				renk2 = random.uniform(0, 255);
				renk3 = random.uniform(0, 255);
				Mat kopya(500, 900, CV_8UC3, Scalar(125, renk2, renk1));
				Mat kopya2 = kopya.clone();

				for (int y = 0; y < 400; y += 10)
				{
					a += 1;
					if (a % 2 == 0)
					{
						kopya.rowRange(50, 60).setTo(Scalar(renk1, renk2, renk3));
						kopya.colRange(50, 60).setTo(Scalar(renk2, renk1, renk3));
					}
					else if (a % 2 != 0)
					{
						kopya.rowRange(440, 450).setTo(Scalar(renk3, renk2, renk1));
						kopya.colRange(840, 850).setTo(Scalar(0, renk1, renk3));
					}

					putText(kopya, ekranaYaz[t], Point(100, y + 120), FONT_HERSHEY_TRIPLEX, 3, Scalar::all(255), 2);
					cv::imshow(wName, kopya);
					cv::waitKey(10);
					kopya = kopya2.clone();
				}

			}
		}

		cv::imshow(wName, ilkEkran);
		cv::waitKey(100);
	}
	double angle = 0;
	double scale = 1;
	Mat son;
	//affine donusumu yapýyorum
	for (int t = 1; t <= 380; t += 20)
	{
		donusum = getRotationMatrix2D(Point2f(uni.cols / 2, uni.rows / 2), t % 360, scale * 0.6);
		warpAffine(uni, son, donusum, Size(900, 500), 1, BORDER_TRANSPARENT, Scalar(0, 0, 70));
		cv::imshow(wName, son);
		cv::waitKey(30);
	}
	int scale2 = 1;
	int angle2 = 1;
	Mat danielMartin = imread("C:\\Users\\User\\Desktop\\biomedical image\\danielmartin.jpg");
	resize(danielMartin, danielMartin, Size(900, 500));
	imshow(wName, danielMartin);
	waitKey(1000);
	Mat donusum2;
	for (int x = 0; x <= 10; x++)
	{
		donusum2 = getRotationMatrix2D(Point2f(danielMartin.cols / 2, danielMartin.rows / 2), angle2 * -34, scale2 * 0.7);
		warpAffine(danielMartin, danielMartin, donusum2, danielMartin.size(), 1, BORDER_CONSTANT, Scalar::all(0));
		imshow(wName, danielMartin);

		waitKey(100);
	}

	Mat daniel = imread("C:\\Users\\User\\Desktop\\biomedical image\\daniel.jpg");

	resize(daniel, daniel, Size(900, 500));

	imshow(wName, daniel);

	waitKey(1000);
	Mat cKol = imread("C:\\Users\\User\\Desktop\\biomedical image\\ckol.jpg");

	resize(cKol, cKol, Size(900, 500));
	imshow(wName, cKol);
	waitKey(300);
	Mat rontgen = imread("C:\\Users\\User\\Desktop\\biomedical image\\rontgen.png");

	resize(rontgen, rontgen, Size(900, 500));
	Mat rontgencopy = rontgen.clone();
	Mat donusum3;

	Point2f firsPoint[] = { Point2f(0,0),Point2f(900,0),Point2f(900,500),Point2f(0,500) };
	Point2f lastPoint[4];
	for (int t = 0; t < 300; t += 20)
	{
		lastPoint[0] = { Point2f(400 + t,200 + t) };
		lastPoint[1] = { Point2f(800 + t, 200 + t) };
		lastPoint[2] = { Point2f(800 + t, 400 + t) };
		lastPoint[3] = { Point2f(400 + t, 400 + t) };
		donusum3 = getAffineTransform(firsPoint, lastPoint);
		warpAffine(cKol, rontgen, donusum3, rontgen.size(), 1, BORDER_TRANSPARENT);

		line(rontgen, lastPoint[0], lastPoint[1], Scalar(0, 0, 255), 2, 8);

		line(rontgen, lastPoint[1], lastPoint[2], Scalar(0, 255, 0), 2, 8);

		line(rontgen, lastPoint[2], lastPoint[3], Scalar(255, 0, 0), 2, 8);
		line(rontgen, lastPoint[3], lastPoint[0], Scalar(50, 100, 150), 2, 8);

		imshow(wName, rontgen);
		waitKey(50);
		rontgen = rontgencopy.clone();
	}

	Mat sagKol = imread("C:\\Users\\User\\Desktop\\biomedical image\\sagKol.png");
	resize(sagKol, sagKol, Size(900, 500));
	Point2f array1[] = { Point2f(0,0),Point2f(900,0),Point2f(900,500),Point2f(0,500) };
	Point2f  array2[4];
	Mat transport;
	Mat copySagkol = sagKol.clone();
	for (int t = 0; t < 400; t++)
	{
		array2[0] = { Point2f(0 + t,0) };
		array2[1] = { Point2f(900 + t,0) };
		array2[2] = { Point2f(900 + t,500) };
		array2[3] = { Point2f(0 + t,500) };

		transport = getAffineTransform(array1, array2);
		warpAffine(sagKol, sagKol, transport, sagKol.size(), 1, BORDER_TRANSPARENT);
		imshow(wName, sagKol);
		waitKey(1);
		sagKol = copySagkol.clone();
	}

	Mat mri = imread("C:\\Users\\User\\Desktop\\biomedical image\\mrý.jpg");
	resize(mri, mri, Size(900, 500));
	int satir = mri.rows;
	int sutun = mri.cols;

	for (int t = 0; t < satir; t++)
	{
		for (int j = 0; j < sutun; j++)
		{
			mri.at<Vec3b>(t, j)[0] = mri.at<Vec3b>(t, j)[0] * 1.2;
			mri.at<Vec3b>(t, j)[1] = mri.at<Vec3b>(t, j)[1] * 1.2;
			mri.at<Vec3b>(t, j)[2] = mri.at<Vec3b>(t, j)[2] * 1.2;

		}

		imshow(wName, mri);
		waitKey(1);
	}
	imshow(wName, mri);
	waitKey(1000);
	Mat robotandhand = imread("C:\\Users\\User\\Desktop\\biomedical image\\robotandhand.jpg");
	resize(robotandhand, robotandhand, Size(900, 500));
	imshow(wName, robotandhand);
	waitKey(1000);
	Mat rando(500, 900, CV_8UC3, Scalar::all(255));
	randu(rando, Scalar(0, 0, 0), Scalar(255, 255, 255));
	putText(rando, "THE AND", Point(300, 190), FONT_HERSHEY_TRIPLEX | FONT_ITALIC, 2, Scalar(40, 50, 70), 2, 8);

	imshow(wName, rando);

	waitKey(1050);
	putText(rando, "THANKS FOR WATCHING", Size(50, 280), FONT_HERSHEY_TRIPLEX | FONT_ITALIC, 2, Scalar(40, 50, 70), 2, 8);

	imshow(wName, rando);

	waitKey(0);
}
int main()
{
	proje();
}