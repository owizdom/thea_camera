#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QDateTime>
#include <QDir>
#include <QStandardPaths>
#include <QImage>
#include <QPixmap>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , camera(nullptr)
    , videoWriter(nullptr)
    , timer(new QTimer(this))
    , isCameraRunning(false)
    , isRecording(false)
    , photoCount(0)
    , videoCount(0)
    , currentWidth(800)
    , currentHeight(600)
    , currentFPS(30)
    , currentQuality(95)
    , wideMode(false)
    , currentMode("Photo")
{
    ui->setupUi(this);
    setupMenuBar();
    setupStatusBar();
    createDirectories();
    
    // Connect signals
    connect(timer, &QTimer::timeout, this, &MainWindow::updateFrame);
    connect(ui->startStopButton, &QPushButton::clicked, this, &MainWindow::startCamera);
    connect(ui->captureButton, &QPushButton::clicked, this, &MainWindow::capturePhoto);
    connect(ui->recordButton, &QPushButton::clicked, this, &MainWindow::startRecording);
    connect(ui->modeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onModeChanged);
    connect(ui->resolutionCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onResolutionChanged);
    connect(ui->fpsSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onFPSChanged);
    connect(ui->qualitySlider, &QSlider::valueChanged, this, &MainWindow::onQualityChanged);
    connect(ui->wideModeCheck, &QCheckBox::toggled, this, &MainWindow::onWideModeToggled);
    
    // Menu actions
    connect(ui->actionStartCamera, &QAction::triggered, this, &MainWindow::startCamera);
    connect(ui->actionStopCamera, &QAction::triggered, this, &MainWindow::stopCamera);
    connect(ui->actionCapturePhoto, &QAction::triggered, this, &MainWindow::capturePhoto);
    connect(ui->actionStartRecording, &QAction::triggered, this, &MainWindow::startRecording);
    connect(ui->actionStopRecording, &QAction::triggered, this, &MainWindow::stopRecording);
    connect(ui->actionOpenSettings, &QAction::triggered, this, &MainWindow::openSettings);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionExit, &QAction::triggered, this, &QWidget::close);
    
    updateStatusBar();
}

MainWindow::~MainWindow()
{
    stopCamera();
    if (camera) {
        delete camera;
    }
    if (videoWriter) {
        delete videoWriter;
    }
    delete ui;
}


void MainWindow::setupMenuBar()
{
    // Menu bar is already set up in the .ui file
}

void MainWindow::setupStatusBar()
{
    statusBar()->showMessage("Ready to start camera");
}

void MainWindow::createDirectories()
{
    photosDir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/Thea";
    videosDir = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation) + "/Thea";
    
    QDir().mkpath(photosDir);
    QDir().mkpath(videosDir);
}

void MainWindow::startCamera()
{
    if (isCameraRunning) {
        stopCamera();
        return;
    }
    
    setupCamera();
    
    if (camera && camera->isOpened()) {
        isCameraRunning = true;
        timer->start(1000 / currentFPS);
        
        ui->startStopButton->setText("Stop Camera");
        ui->startStopButton->setStyleSheet("QPushButton { background-color: #F44336; color: white; font-weight: bold; padding: 8px; }");
        ui->captureButton->setEnabled(true);
        ui->recordButton->setEnabled(true);
        
        statusBar()->showMessage("Camera started successfully");
        ui->statusText->append("Camera started at " + QDateTime::currentDateTime().toString());
    } else {
        QMessageBox::warning(this, "Camera Error", "Failed to open camera. Please check if camera is connected and not used by another application.");
    }
}

void MainWindow::stopCamera()
{
    if (isRecording) {
        stopRecording();
    }
    
    if (isCameraRunning) {
        timer->stop();
        isCameraRunning = false;
        
        if (camera) {
            camera->release();
        }
        
        ui->startStopButton->setText("Start Camera");
        ui->startStopButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; padding: 8px; }");
        ui->captureButton->setEnabled(false);
        ui->recordButton->setEnabled(false);
        
        ui->cameraLabel->setText("Camera Feed");
        ui->cameraLabel->setStyleSheet("QLabel { background-color: black; color: white; font-size: 18px; }");
        
        statusBar()->showMessage("Camera stopped");
        ui->statusText->append("Camera stopped at " + QDateTime::currentDateTime().toString());
    }
}

void MainWindow::capturePhoto()
{
    if (!isCameraRunning || !camera) return;
    
    cv::Mat frame;
    if (camera->read(frame)) {
        processFrame(frame);
        savePhoto(frame);
        
        ui->statusText->append("Photo captured: " + QString::number(++photoCount));
        statusBar()->showMessage("Photo captured successfully");
    }
}

void MainWindow::startRecording()
{
    if (!isCameraRunning || isRecording) return;
    
    setupVideoWriter();
    
    if (videoWriter && videoWriter->isOpened()) {
        isRecording = true;
        ui->recordButton->setText("Stop Recording");
        ui->recordButton->setStyleSheet("QPushButton { background-color: #FF9800; color: white; font-weight: bold; padding: 8px; }");
        ui->recordingProgress->setVisible(true);
        ui->recordingProgress->setValue(0);
        
        ui->statusText->append("Video recording started");
        statusBar()->showMessage("Recording...");
    } else {
        QMessageBox::warning(this, "Recording Error", "Failed to start video recording.");
    }
}

void MainWindow::stopRecording()
{
    if (!isRecording) return;
    
    isRecording = false;
    ui->recordButton->setText("Start Recording");
    ui->recordButton->setStyleSheet("QPushButton { background-color: #F44336; color: white; font-weight: bold; padding: 8px; }");
    ui->recordingProgress->setVisible(false);
    
    if (videoWriter) {
        videoWriter->release();
        delete videoWriter;
        videoWriter = nullptr;
    }
    
    ui->statusText->append("Video recording stopped: " + QString::number(++videoCount));
    statusBar()->showMessage("Recording stopped");
}

void MainWindow::updateFrame()
{
    if (!isCameraRunning || !camera) return;
    
    cv::Mat frame;
    if (camera->read(frame)) {
        processFrame(frame);
        
        if (isRecording && videoWriter && videoWriter->isOpened()) {
            *videoWriter << frame;
        }
    }
}

void MainWindow::onModeChanged()
{
    currentMode = ui->modeCombo->currentText();
    ui->statusText->append("Mode changed to: " + currentMode);
}

void MainWindow::onResolutionChanged()
{
    QString resolution = ui->resolutionCombo->currentText();
    if (resolution == "800x600") {
        currentWidth = 800;
        currentHeight = 600;
    } else if (resolution == "1280x720") {
        currentWidth = 1280;
        currentHeight = 720;
    } else if (resolution == "1920x1080") {
        currentWidth = 1920;
        currentHeight = 1080;
    } else if (resolution == "1000x500 (Wide)") {
        currentWidth = 1000;
        currentHeight = 500;
        wideMode = true;
    }
    
    ui->statusText->append("Resolution changed to: " + resolution);
}

void MainWindow::onFPSChanged()
{
    currentFPS = ui->fpsSpinBox->value();
    if (isCameraRunning) {
        timer->setInterval(1000 / currentFPS);
    }
    ui->statusText->append("FPS changed to: " + QString::number(currentFPS));
}

void MainWindow::onQualityChanged()
{
    currentQuality = ui->qualitySlider->value();
    ui->qualityLabel->setText(QString::number(currentQuality) + "%");
}

void MainWindow::onWideModeToggled()
{
    wideMode = ui->wideModeCheck->isChecked();
    ui->statusText->append("Wide mode: " + QString(wideMode ? "ON" : "OFF"));
}

void MainWindow::openSettings()
{
    QMessageBox::information(this, "Settings", "Camera settings can be adjusted using the controls above.");
}

void MainWindow::about()
{
    QMessageBox::about(this, "About Thea Camera", 
                      "Thea Camera App\n\n"
                      "A professional camera application built with Qt and OpenCV.\n"
                      "Features:\n"
                      "• Real-time camera feed\n"
                      "• Photo capture\n"
                      "• Video recording\n"
                      "• Multiple resolutions\n"
                      "• Wide mode support\n\n"
                      "Version 1.0");
}

void MainWindow::setupCamera()
{
    if (camera) {
        delete camera;
    }
    
    camera = new cv::VideoCapture(0);
    
    if (camera->isOpened()) {
        camera->set(cv::CAP_PROP_FRAME_WIDTH, currentWidth);
        camera->set(cv::CAP_PROP_FRAME_HEIGHT, currentHeight);
        camera->set(cv::CAP_PROP_FPS, currentFPS);
    }
}

void MainWindow::setupVideoWriter()
{
    if (videoWriter) {
        delete videoWriter;
    }
    
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    currentVideoFile = videosDir + "/Thea_" + timestamp + ".mp4";
    
    int fourcc = cv::VideoWriter::fourcc('M', 'P', '4', 'V');
    videoWriter = new cv::VideoWriter(currentVideoFile.toStdString(), fourcc, currentFPS, cv::Size(currentWidth, currentHeight));
}

void MainWindow::processFrame(cv::Mat &frame)
{
    if (wideMode) {
        // Apply wide mode processing
        cv::resize(frame, frame, cv::Size(1000, 500));
    }
    
    // Convert BGR to RGB for Qt
    cv::cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    
    // Convert to QImage
    QImage qimg(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    QPixmap pixmap = QPixmap::fromImage(qimg);
    
    // Scale to fit label while maintaining aspect ratio
    QPixmap scaledPixmap = pixmap.scaled(ui->cameraLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->cameraLabel->setPixmap(scaledPixmap);
}

void MainWindow::savePhoto(const cv::Mat &frame)
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss");
    QString filename = photosDir + "/Thea_" + timestamp + ".jpg";
    
    cv::Mat saveFrame;
    cv::cvtColor(frame, saveFrame, cv::COLOR_RGB2BGR);
    
    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_JPEG_QUALITY);
    compression_params.push_back(currentQuality);
    
    cv::imwrite(filename.toStdString(), saveFrame, compression_params);
}

void MainWindow::updateStatusBar()
{
    QString status = QString("Mode: %1 | Resolution: %2x%3 | FPS: %4 | Quality: %5%")
                    .arg(currentMode)
                    .arg(currentWidth)
                    .arg(currentHeight)
                    .arg(currentFPS)
                    .arg(currentQuality);
    
    statusBar()->showMessage(status);
}
