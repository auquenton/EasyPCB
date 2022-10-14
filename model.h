#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/dnn.hpp>
#include <onnxruntime_cxx_api.h>
#include <vector>

using namespace cv;
using namespace std;
using namespace Ort;

/*--------------类定义--------------*/
class det_box
{
public:
    float x1;
    float y1;
    float w;
    float h;
    float c;
};


/*--------------函数定义--------------*/
void PreProcess(const Mat& image, Mat& image_blob)
{
    Mat input;
    image.copyTo(input);


    //数据处理 标准化
    std::vector<Mat> channels, channel_p;
    split(input, channels);
    Mat R, G, B;
    B = channels.at(0) / 255;
    G = channels.at(1) / 255;
    R = channels.at(2) / 255;

    channel_p.push_back(R);
    channel_p.push_back(G);
    channel_p.push_back(B);

    Mat outt;
    merge(channel_p, outt);
    image_blob = outt;
}

cv::Mat GetImage(string filepath,int size) {
    return cv::imread(filepath);
}

cv::Mat ProcessImg(cv::Mat img, int size) {
    Mat det1, det2;
    cv::resize(img, det1, Size(size, size), INTER_AREA);
    det1.convertTo(det1, CV_32FC3);
    PreProcess(det1, det2);         //标准化处理
    Mat blob = dnn::blobFromImage(det2, 1., Size(640, 640), Scalar(0, 0, 0), false, true);
    return blob;
}


std::vector<std::vector<det_box>> GetBoxes(float* prob, int class_num , float conf_thres, float iou_thres,int obj_count) {
    bool multi_label = false;
    if (class_num >= 1) {
        multi_label = true;
    }
    int max_wh = 4096;
    //解码推理数据
    //预测框数量
    std::vector<cv::Rect> boxes_vec; //目标框坐标
    std::vector<int> clsIdx_vec;//目标框类别索引
    std::vector<float> scores_vec;//目标框得分索引
    std::vector<int>boxIdx_vec; //目标框的序号索引
    std::cout << "未处理预测框数据总数：" << obj_count << "条"<<std::endl;

    for (int i = 0; i < obj_count; i++) {
        if (*(prob + i * (5 + class_num) + 4) < conf_thres) //小于置信度阈值，继续
            continue;
        if (multi_label) {
            for (int cls_idx = 0; cls_idx < class_num; cls_idx++) {
                float x1 = *(prob + i * (5 + class_num)) - *(prob + i * (5 + class_num) + 2) / 2;
                float y1 = *(prob + i * (5 + class_num) + 1) - *(prob + i * (5 + class_num) + 3) / 2;
                float x2 = *(prob + i * (5 + class_num)) + *(prob + i * (5 + class_num) + 2) / 2;
                float y2 = *(prob + i * (5 + class_num) + 1) + *(prob + i * (5 + class_num) + 3) / 2;
                // mix_conf = obj_conf * cls_conf > conf_thres
                //这里是官方的目标置信度*类别概率
                float mix_conf = (*(prob + i * (5 + class_num) + 4)) * (*(prob + i * (5 + class_num) + 5 + cls_idx));
                if (mix_conf > conf_thres) {
                    boxes_vec.push_back(cv::Rect(x1 + cls_idx * max_wh,
                        y1 + cls_idx * max_wh,
                        x2 - x1,
                        y2 - y1)
                    );
                    //scores_vec.push_back((*(prob+i*(5+class_num)+4)));
                    scores_vec.push_back(mix_conf);
                    //std::cout<<"score "<<(*(prob+i*(5+class_num)+5+cls_idx))<<std::endl;
                    clsIdx_vec.push_back(cls_idx);
                    //cv::Rect
                }
            }

        }
        else {

        }
    }//obj_count
    cout <<"经过置信度阈值处理后的候选框数据：" << boxes_vec.size()<<"条" << endl;
    cv::dnn::NMSBoxes(boxes_vec, scores_vec, 0.0f, iou_thres, boxIdx_vec);
    cout << "经过NMS处理后的候选框数据：" <<boxIdx_vec.size() << "条" << endl;
    cout << "======================================" << endl;



    std::vector<std::vector<det_box>> det_boxes;
    det_boxes.resize(class_num);


    for (int i = 0; i < boxIdx_vec.size(); i++) {
        det_box det_box_tmp;
        det_box_tmp.x1 = boxes_vec[boxIdx_vec[i]].x - clsIdx_vec[boxIdx_vec[i]] * max_wh;
        /*cout << "x1:" << det_box_tmp.x1 << endl;*/
        det_box_tmp.y1 = boxes_vec[boxIdx_vec[i]].y - clsIdx_vec[boxIdx_vec[i]] * max_wh;
        /*cout << "y1:" << det_box_tmp.y1 << endl;*/
        det_box_tmp.w = boxes_vec[boxIdx_vec[i]].width;
        /*cout << "w:" << det_box_tmp.w << endl;*/
        det_box_tmp.h = boxes_vec[boxIdx_vec[i]].height;
        /*cout << "h:" << det_box_tmp.h << endl;*/
        det_box_tmp.c = scores_vec[boxIdx_vec[i]];
        /*cout << "c:" << det_box_tmp.c << endl;*/
        det_boxes[clsIdx_vec[boxIdx_vec[i]]].push_back(det_box_tmp);
    }
    return det_boxes;
}

cv::Mat DrawBox(cv::Mat img, vector<det_box> det_boxes, int index, int size = 640) {
    cv::resize(img, img, cv::Size(size, size));
    string defect_list[6] = { "missing_hole","mouse_bite","open_circuit","short","spur","spurious_copper" };
    vector<Scalar> color_list = { Scalar(255, 0, 0),Scalar(0, 0, 255),Scalar(0, 255, 0),Scalar(0, 255, 255),Scalar(255, 0, 255) ,Scalar(255, 255, 0) };
    for (det_box det_box_tmp:det_boxes)
    {
        Rect rect(det_box_tmp.x1, det_box_tmp.y1, det_box_tmp.w, det_box_tmp.h);
        cv::rectangle(img, rect, color_list[index], 2, LINE_8, 0);
        Rect box_rect(det_box_tmp.x1, det_box_tmp.y1 - 15, defect_list[index].size() * 9, 15);
        cv::rectangle(img, box_rect, color_list[index], -1, LINE_8, 0);
        cv::putText(img, defect_list[index], Point(det_box_tmp.x1, det_box_tmp.y1 - 3), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2, 8);
    }
    return img;
}

QImage MatToQImage(cv::Mat mtx)
{
    switch (mtx.type())
    {
    case CV_8UC1:
    {
        QImage img((const unsigned char*)(mtx.data), mtx.cols, mtx.rows, mtx.cols, QImage::Format_Grayscale8);
        return img;
    }
    break;
    case CV_8UC3:
    {
        QImage img((const unsigned char*)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 3, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    break;
    case CV_8UC4:
    {
        QImage img((const unsigned char*)(mtx.data), mtx.cols, mtx.rows, mtx.cols * 4, QImage::Format_ARGB32);
        return img;
    }
    break;
    default:
    {
        QImage img;
        return img;
    }
    break;
    }
}




