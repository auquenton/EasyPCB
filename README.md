# Easy_PCB_App(Source Code)

PCB Defect Detection

A PCB defect detection application deployed using the QT and OnnxRuntime framework.

* Use C++ for deep learning model deployment.
* Use QT for application development.
* Model deployment is implemented using the OnnxRuntime framework.
* We use PKU-Market-PCB datasets.


## Install

* clone the project by ```git clone https://github.com/StudentKang/Easy_PCB_App.git```
* Download the [Onnx weight file](链接：https://pan.baidu.com/s/1ToeLm6RoXNl-TRCKkDjyiA) 48q1 
* run mainwindow.cpp

## introduction

* The defect detection for a single PCB defect picture. Displays detection speed, defect category, and the number of corresponding defect.
<img src="./examples/single.png" align="center" alt="single" />

* Click PCB sample picture to preview the picture.

<div align="center"><img src="./examples/preview.png" align="center" alt="preview" width="500" height="350" /></div>

* The defect detection for batch PCB defect pictures. Displays defect processing progress and batch defect sample number.

<div align="center"><img src="./examples/batch.png" alt="batch" width="500" height="350" /></div>
<div align="center"><img src="./examples/detection.png" alt="detection" width="500" height="350" /></div>

