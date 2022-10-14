/********************************************************************************

** author:	Qing
** Date:	2022-03-10
** desc:	主窗口实现

********************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "batchwindow.h"
#include "ui_batchwindow.h"
#include <QFileDialog>
#include <QString>
#include <qdebug.h>
#include <QMessageBox>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/dnn.hpp>

#include <assert.h>
#include <stdio.h>
#include <onnxruntime_cxx_api.h>
#include <string>
#include <model.h>

#pragma execution_character_set("utf-8")

using namespace cv;
using namespace std;
using namespace Ort;



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->InputImgBox->setStyleSheet("QLabel{background-color:#D1D1D1;}");
    ui->OutputImgBox->setStyleSheet("QLabel{background-color:#D1D1D1;}");
    setFixedSize(this->width(), this->height());
    this->setWindowTitle(QObject::tr("PCB缺陷检测v1.0 (By Qing)"));
    this->setWindowIcon(QIcon(":/img/icon.jpg"));
    connect(ui->select_button, SIGNAL(clicked(bool)), this, SLOT(OpenImg()));
    connect(ui->BatchButton, SIGNAL(clicked(bool)), this, SLOT(OpenNewWindow()));
    connect(ui->CleanLog, SIGNAL(clicked(bool)), this, SLOT(LogClean()));
    connect(ui->UpLoad, SIGNAL(clicked(bool)), this, SLOT(Inference()));
}



void MainWindow::OpenImg(){
    QString Openfile,Openfilepath;
    QImage image;

    Openfile = QFileDialog::getOpenFileName(this,"please choose an image file","","Image Files(*.jpg *.png);;All(*.*)");
    if(!Openfile.contains(".jpg")&&!Openfile.contains(".png")&&Openfile !=""){
        QMessageBox::warning(NULL,tr("警告"),tr("输入文件的格式不正确，请重新选择.jpg或.png格式的图片"),QMessageBox::Yes);
    }else{
        if(Openfile !=""){
            if(image.load(Openfile))
            {
                ui->InputImgBox->setPixmap(QPixmap::fromImage((image).scaled(ui->InputImgBox->size())));
            }
            QFileInfo OpenFileInfo;
            OpenFileInfo = QFileInfo(Openfile);
            Openfilepath = OpenFileInfo.filePath();
            this->imagepath = Openfilepath;
            ui->LogBox->append("已经成功导入文件，文件路径:"+Openfilepath);
            ui->LogBox->append("-----------------------------");
        }
    }
}

void MainWindow::Inference() {
    Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "OnnxModel");
    Ort::SessionOptions session_options;
    session_options.SetIntraOpNumThreads(8);
    session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_ALL);

    //model path
    const wchar_t* model_path = L"C://Users//18338//Desktop//Qt_PCB//yolon.onnx";
    Ort::Session session(env, model_path, session_options);

    Ort::AllocatorWithDefaultOptions allocator;
    size_t num_input_nodes = session.GetInputCount();
    size_t num_output_nodes = session.GetOutputCount();
    auto input_dims = session.GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape();
    auto output_dims = session.GetOutputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape();
    const char* input_name = session.GetInputName(0, allocator);
    const char* output_name = session.GetOutputName(0, allocator);

    /*
    std::cout << "input_name:" << input_name << std::endl;
    std::cout << "output_name: " << output_name << std::endl;
    std::cout << "input_sizes:";
    for (auto i : input_dims) {
        std::cout  << i <<',';
    }
    std::cout <<endl;
    std::cout << "output_sizes:";
    for (auto i : output_dims) {
        std::cout << i << ',';
    }
    std::cout << endl;
    */

    std::vector<const char*> input_names{ input_name };
    std::vector<const char*> output_names = { output_name };
    std::vector<const char*> input_node_names = { "images" };
    std::vector<const char*> output_node_names = { "output" };

    QString imagepath = this->imagepath;
    if (imagepath == "") {
        QMessageBox::warning(NULL, tr("警告"), tr("未选择图片！请重新选择"), QMessageBox::Yes);
        return;
    }
    imagepath = imagepath.replace('/', '\\');
    string imgpath = imagepath.toStdString();
    DWORD startTime = ::GetTickCount(); //图片处理开始
    Mat img = GetImage(imgpath, 640);
    Mat blob = ProcessImg(img, 640);
    DWORD endTime = ::GetTickCount(); //图片处理结束
    /*printf("Load success!\n");*/
    DWORD process_cost_time = endTime - startTime;
    ui->LogBox->append("图片处理加载成功!(<font color=\"#7B68EE\">耗时："+QString::number(process_cost_time)+"ms)</font>");

    auto memory_info = Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtArenaAllocator, OrtMemType::OrtMemTypeDefault);
    std::vector<Ort::Value> input_tensors;
    input_tensors.emplace_back(Ort::Value::CreateTensor<float>(memory_info, blob.ptr<float>(), blob.total(), input_dims.data(), input_dims.size()));


    startTime = ::GetTickCount(); //推理开始
    auto output_tensors = session.Run(Ort::RunOptions{ nullptr }, input_node_names.data(), input_tensors.data(), input_names.size(), output_node_names.data(), output_node_names.size());
    endTime = ::GetTickCount(); //推理结束
    DWORD inference_cost_time = endTime - startTime;
    ui->LogBox->append("模型前向推理结束!<font color=\"#7B68EE\">(耗时：" + QString::number(inference_cost_time) + "ms)</font>");


    assert(output_tensors.size() == 1 && output_tensors.front().IsTensor());
    float* prob = output_tensors[0].GetTensorMutableData<float>();

    /*
    //参数配置
    int obj_count = output_tensors[0].GetTensorTypeAndShapeInfo().GetElementCount() / (class_num + 5);
    int class_num = 6;
    float conf_thres = 0.25;
    float iou_thres = 0.45;
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
    std::cout << "obj_count is " << obj_count << std::endl;

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
    cout << boxes_vec.size() << endl;
    cv::dnn::NMSBoxes(boxes_vec, scores_vec, 0.0f, iou_thres, boxIdx_vec);
    cout << boxIdx_vec.size() << endl;
    std::vector<std::vector<det_box>> det_boxes;
    det_boxes.resize(class_num);
    for (int i = 0; i < boxIdx_vec.size(); i++) {
        det_box det_box_tmp;
        det_box_tmp.x1 = boxes_vec[boxIdx_vec[i]].x - clsIdx_vec[boxIdx_vec[i]] * max_wh;
        cout << "x1:" << det_box_tmp.x1 <<endl;
        det_box_tmp.y1 = boxes_vec[boxIdx_vec[i]].y - clsIdx_vec[boxIdx_vec[i]] * max_wh;
        cout << "y1:" << det_box_tmp.y1 << endl;
        det_box_tmp.w = boxes_vec[boxIdx_vec[i]].width;
        cout << "w:" << det_box_tmp.w << endl;
        det_box_tmp.h = boxes_vec[boxIdx_vec[i]].height;
        cout << "h:" << det_box_tmp.h << endl;
        det_box_tmp.c = scores_vec[boxIdx_vec[i]];
        cout << "c:" << det_box_tmp.c << endl;
        det_boxes[clsIdx_vec[boxIdx_vec[i]]].push_back(det_box_tmp);

        Rect rect(det_box_tmp.x1, det_box_tmp.y1, det_box_tmp.w, det_box_tmp.h);
        cv::resize(img, img, cv::Size(640,640));
        cv::rectangle(img, rect, Scalar(255, 0, 0), 2, LINE_8, 0);
        imshow("1", img);
        waitKey(0);
        destroyAllWindows();

    }*/
    int class_num = 6;
    float conf_thres = 0.25;
    float iou_thres = 0.45;
    int obj_count = output_tensors[0].GetTensorTypeAndShapeInfo().GetElementCount() / (class_num + 5);
    startTime = ::GetTickCount(); //后处理开始
    std::vector<std::vector<det_box>> det_boxes = GetBoxes(prob, class_num, conf_thres, iou_thres, obj_count);
    endTime = ::GetTickCount(); //后处理结束
    DWORD wakeup_time = endTime - startTime;
    ui->LogBox->append("模型数据后处理结束!<font color=\"#7B68EE\">(耗时：" + QString::number(wakeup_time) + "ms)</font>");

    
    /*string defect_list[6] = {"missing_hole","mouse_bite","open_circuit","short","spur","spurious_copper"};*/
    ui->LogBox->append("<font color=\"#C0392B\">检测完毕！</font>");
    int cnt = 0;
    string defect_list[6] = { "missing_hole","mouse_bite","open_circuit","short","spur","spurious_copper" };
    for (int i = 0; i < det_boxes.size(); i++)
    {
        if (det_boxes[i].size() == 0) continue;
        else {
            ui->LogBox->append("<font color=\"#C0392B\">" + QString::fromStdString(defect_list[i]) + "缺陷：" + QString::number(det_boxes[i].size()) + "处</font>");
            cnt += det_boxes[i].size();
            /*cv::resize(img, img, cv::Size(640, 640));
            for (auto det_box_tmp : det_boxes[i]) {
                Rect rect(det_box_tmp.x1, det_box_tmp.y1, det_box_tmp.w, det_box_tmp.h);
                cv::rectangle(img, rect, Scalar(255, 0, 0), 2, LINE_8, 0);
                Rect box_rect(det_box_tmp.x1, det_box_tmp.y1-15, defect_list[i].size()*9, 15);
                cv::rectangle(img, box_rect, Scalar(255, 0, 0), -1, LINE_8, 0);
                cv::putText(img, defect_list[i], Point(det_box_tmp.x1, det_box_tmp.y1-3), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255), 2, 8);
            }*/
            img = DrawBox(img, det_boxes[i],i, 640);
        }
    }


    QImage ImgDisplay = MatToQImage(img);
    ui->OutputImgBox->setPixmap(QPixmap::fromImage((ImgDisplay).scaled(ui->OutputImgBox->size())));
    //图片预览
    if (cnt != 0) {
        ui->LogBox->append("<font color=\"#C0392B\">共检测到缺陷: " + QString::number(cnt) + "处</font>");
        imshow("ImageShow", img);
        waitKey(0);
        destroyAllWindows();
    }
    else if (cnt == 0) ui->LogBox->append("未检测到PCB缺陷！");
    ui->LogBox->append("-----------------------------");
}

void MainWindow::OpenNewWindow(){
    Batchwindow* bw = new Batchwindow(this);
    ui->LogBox->append("<font color=\"#7B68EE\">成功打开批处理系统!</font>");
    ui->LogBox->append("-----------------------------");
    bw->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    bw->exec();
}

void MainWindow::LogClean(){
    ui->LogBox->clear();
     QMessageBox::information(NULL,tr("提示"),tr("已经成功清除日志信息!"),QMessageBox::Yes);
}



MainWindow::~MainWindow()
{
    delete ui;
}



