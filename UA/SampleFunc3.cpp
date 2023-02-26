#include "StdAfxQt.h"
#include "SampleFunc.h"
#include "boost/foreach.hpp"

// Function: Smp3xCAM
// スキャンパスを生成するシンプルな3xCAM
//
// Parameter:
// *S - 加工面（一つの面のみ）
// *C - 生成するスキャンパスのガイドカーブ
// R - ボールエンドミル半径
// N - スキャニングライン分割数(N < 100)
// H - 素材上面のZ座標
// D - Z方向分割数（粗加工用）
void Smp3xCAM(NURBSS *S,NURBSC *C,double R,int N,double H,int D)
{
    double green[3] = {0,1,0};      // 描画するパスの色（緑）
    Coord plane_pt;                 // 分割する平面上の1点
    Coord plane_n;                  // 分割する平面の法線ベクトル
	VVCoord vvPath;
    VVVCoord vvvPath;				// 生成されたパスを格納
    int flag = 0;                   // ジグザグパス生成時の方向転換用フラグ

    // ガイドカーブに沿って垂直平面をシフトしていき，加工面との交点群を求めていく
	for(int i=0;i<=N;i++){
        double t = (double)i/(double)N;
		if(i==0) t += 0.0001;		// 特異点回避
		else if(i==N) t-= 0.0001;	// 特異点回避
        plane_pt = C->CalcNurbsCCoord(t);     // 注目中の垂直平面上の1点
        plane_n = C->CalcTanVecOnNurbsC(t);   // 注目中の垂直平面の法線ベクトル
        VCoord vPath = S->CalcIntersecPtsPlaneSearch(plane_pt,plane_n,0.5,3,RUNGE_KUTTA);  // 交点群算出
        // 得られた交点群を，加工面法線方向に工具半径分オフセットさせた点を得る
		for(int j=0;j<vPath.size();j++){
            Coord pt = S->CalcNurbsSCoord(vPath[j].x,vPath[j].y);     // 工具コンタクト点
            Coord n = S->CalcNormVecOnNurbsS(vPath[j].x,vPath[j].y);  // 法線ベクトル
            if(n.z < 0)	n = n*(-1);         // 法線ベクトルの向き調整
			vPath[j] = pt + n*R;		// 工具半径オフセット
		}
		vvPath.push_back(vPath);
	}

	// 粗加工パス生成
	for(int i=0;i<D;i++){
		VVCoord vv;
		for(int j=0;j<vvPath.size();j++){
			VCoord v;
			for(int k=0;k<vvPath[j].size();k++){
				double del = (H - vvPath[j][k].z)/(double)D;
				double Z = H - del*(double)i;
				v.push_back( Coord(vvPath[j][k].x, vvPath[j][k].y, Z) );
			}
			vv.push_back(v);
		}
		vvvPath.push_back(vv);
	}

	// path描画
	for(int i=0;i<vvvPath.size();i++){
		for(int j=0;j<vvvPath[i].size();j++){
			for(int k=0;k<vvvPath[i][j].size();k++){
				DrawPoint(vvvPath[i][j][k],1,1,green);
			}
		}
	}

    // NCコード生成(各条件は各自で変更ください)
	double ret = H + 10;		// リトラクトZ
	FILE *fp = fopen("demo.nc","w");
	fprintf(fp,"G92X0.0Y0.0Z0.0\n");
	fprintf(fp,"S4000M03\n");
	fprintf(fp,"F500\n");

	BOOST_FOREACH(auto& vv, vvvPath) {
		fprintf(fp,"G00X%.2lfY%.2lfZ%.2lf\n",vv[0][0].x,vv[0][0].y,ret);
		BOOST_FOREACH(auto& v, vv) {
			if ( flag == 0 ) {
				BOOST_FOREACH(auto& p, v) {
					fprintf(fp,"G01X%.2lfY%.2lfZ%.2lf\n",p.x,p.y,p.z);
				}
			}
			else {
				BOOST_REVERSE_FOREACH(auto& p, v) {
					fprintf(fp,"G01X%.2lfY%.2lfZ%.2lf\n",p.x,p.y,p.z);
				}
			}
			flag = 1 - flag;
		}
		fprintf(fp,"G01Z%.2lf\n",ret);
	}

	fprintf(fp,"G01Z%.2lf\n",ret);
	fprintf(fp,"M05\n");
	fprintf(fp,"M30\n");

	fclose(fp);
}
