#ifndef _SglDisplay_CV_H
#define _SglDisplay_CV_H

#include <memory>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "sglviewer_exports.h"
#include "sgldisplay.h"
namespace sgl{
class APP_SGLVIEWER_TOOLS_API SglDisplay_CV :public SglDisplay
{
    int _w,_h;
    float _f;
     std::string _wname;
    int snapShotIndex=0;
    int waitKeyTime=0;
    cv::Mat _imshow;
    bool canLeave=false;
    bool bExitOnUnUnsedKey=false;

public:
    SglDisplay_CV(std::shared_ptr<sgl::SceneDrawer> drawer,int w,int h,float f){
        _sglDrawer=drawer;
        _w=w;
        _h=h;
        _f=f;
        setParams( "SglDisplay_CV");
    }
    void setParams( std::string wname){

        _imshow.create(_h,_w,CV_8UC4);
        _wname=wname;
        cv::namedWindow(_wname,cv::WINDOW_AUTOSIZE);
        cv::resizeWindow(_wname,_w,_h);
        cv::setMouseCallback(_wname, &SglDisplay_CV::mouseCallBackFunc , this);
    };



    int show( ){
        _scn.setCameraParams(_f,_w,_h,3);
        _imshow=cv::Mat(_h,_w,CV_8UC3,_scn.getBuffer());
        _sglDrawer->draw(_scn);
        int key,leaveNow=false;
        do{
            cv::imshow(_wname,_imshow);
            if (canLeave)waitKeyTime=2;
            else waitKeyTime=0;
            key=cv::waitKey(waitKeyTime);
            //            if (k!=255) cout<<"wkh="<<k<<endl;
            bool update=false,create=false;
            //shift and ctrl keys
            if (key==227 || key==225) {leaveNow=false;}
            else  if ( bExitOnUnUnsedKey  && key!=255 ) leaveNow=true;

            if (create|| update)         _sglDrawer->draw(_scn);


        } while( (!canLeave && !leaveNow) && key!=27);
        return key;
    }



    struct mouseInfo{
        sgl::Point2 pos;
        bool isTranslating=false,isZooming=false,isRotating=false;
    }mi;


    static   void mouseCallBackFunc(int event, int x, int y, int flags, void* userdata){
        SglDisplay_CV *Sv=(SglDisplay_CV*)userdata;
        bool redraw=false;
        if  ( event == cv::EVENT_LBUTTONDOWN ){
            Sv->mi.isRotating=Sv->mi.isTranslating=Sv->mi.isZooming=false;
            if ( flags&cv::EVENT_FLAG_CTRLKEY)
                Sv->mi.isZooming=true;
            else if ( flags&cv::EVENT_FLAG_SHIFTKEY) Sv->mi.isTranslating=true;
            else Sv->mi.isRotating=true;
        }
        else if  ( event == cv::EVENT_MBUTTONDOWN ) Sv->mi.isTranslating=true;
        else if ( event == cv::EVENT_LBUTTONUP ) {              Sv->mi.isRotating=Sv->mi.isTranslating=Sv->mi.isZooming=false;
        }
        else if ( event == cv::EVENT_MBUTTONUP ) Sv->mi.isTranslating=false;
        else if ( event == cv::EVENT_MOUSEMOVE )
        {
            sgl::Point2  dif(Sv->    mi.pos.x-x,Sv->   mi.pos.y-y);
            sgl::Matrix44 tm;//=Sv->_Scene.getTransformMatrix();

            if (Sv->mi.isRotating){
                Sv->_scn.rotate(-float(dif.y)/100.   , -float(dif.x)/100.);
                redraw=true;
            }
            else if (Sv->mi.isZooming){
                redraw=true;
                Sv->_scn.zoom(-dif.y*0.01);
            }
            else if (Sv->mi.isTranslating){
                Sv->_scn.translate(float(-dif.x)/100., float(-dif.y)/100);
                redraw=true;
            }
        }
        Sv->mi.pos=sgl::Point2(x,y);
        if (redraw)     {
            Sv->_sglDrawer->draw(Sv->_scn);
            cv::imshow(Sv->_wname,Sv->_imshow);
        }
    }




};
}
#endif
